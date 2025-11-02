"""
Bug-fixed Maze Treasure Game
- Fixes:
  * Path overlay now reliably visible (drawn on semi-transparent overlay surface)
  * Ability to remove guards: Middle-click on a guard to remove it; Right-click adds a guard; Shift+Right-click removes guard as alternative
  * A* returns immediate path if start==goal
  * Minor robustness fixes (defensive checks)

Controls:
- Left-click: toggle wall
- Right-click: add guard (Shift+Right-click to remove guard at click)
- Middle-click: remove guard at clicked cell
- G: regenerate maze
- A: run A* (avoids guards)
- C: run CSP (avoids guards)
- R: toggle realtime mode

"""

import pygame
import random
import time
import heapq
from collections import deque

# CONFIG
CELL = 28
GRID_W = 23
GRID_H = 17
WIDTH = CELL * GRID_W
HEIGHT = CELL * GRID_H
PANEL_W = 320
WIN_W = WIDTH + PANEL_W
FPS = 30

# COLORS (pleasant palette)
BG = (18, 24, 38)
CELL_BG = (235, 241, 248)
WALL = (40, 53, 71)
START_COL = (88, 172, 142)
GOAL_COL = (250, 173, 20)
PLAYER_COL = (45, 115, 255)
GUARD_COL = (235, 84, 84)
PATH_COL = (144, 202, 249)
PANEL_COL = (28, 34, 48)
TEXT_COL = (220, 230, 240)
BUTTON_COL = (60, 85, 120)
BUTTON_ACTIVE = (90, 120, 170)

pygame.init()
screen = pygame.display.set_mode((WIN_W, HEIGHT))
pygame.display.set_caption("Maze Treasure: A* vs CSP — Minimax Guards (bug-fixed)")
clock = pygame.time.Clock()
font = pygame.font.SysFont("Segoe UI", 16)
font_small = pygame.font.SysFont("Segoe UI", 14)
large = pygame.font.SysFont("Segoe UI", 20, bold=True)

# Grid: 0 free, 1 wall

def make_empty_grid(w,h):
    return [[1 for _ in range(w)] for _ in range(h)]

# Maze generator: randomized DFS (recursive backtracker)

def generate_maze(w, h):
    gw = w//2
    gh = h//2
    grid = make_empty_grid(w,h)
    visited = [[False]*gw for _ in range(gh)]
    dirs = [(0,-1),(1,0),(0,1),(-1,0)]
    def carve(cx,cy):
        visited[cy][cx] = True
        gx, gy = cx*2+1, cy*2+1
        grid[gy][gx] = 0
        order = dirs[:]
        random.shuffle(order)
        for dx,dy in order:
            nx, ny = cx+dx, cy+dy
            if 0 <= nx < gw and 0 <= ny < gh and not visited[ny][nx]:
                wx, wy = gx+dx, gy+dy
                grid[wy][wx] = 0
                carve(nx, ny)
    carve(random.randrange(gw), random.randrange(gh))
    return grid

# Helpers

def in_bounds(x,y):
    return 0 <= x < GRID_W and 0 <= y < GRID_H

def neighbors(x,y,grid):
    for dx,dy in [(1,0),(-1,0),(0,1),(0,-1)]:
        nx, ny = x+dx, y+dy
        if in_bounds(nx,ny) and grid[ny][nx]==0:
            yield nx,ny

def heuristic(a,b):
    return abs(a[0]-b[0])+abs(a[1]-b[1])

# A* with guard-inflation avoidance: inflate guard positions (current + predicted steps)

def astar(grid, start, goal, guards=None, avoid_radius=0):
    if start==goal:
        return [start]
    blocked = set()
    if guards:
        for g in guards:
            blocked.add(g.pos)
            for p in g.predict_positions(avoid_radius):
                blocked.add(p)
    open_set = []
    heapq.heappush(open_set, (0, start))
    came_from = {start: None}
    gscore = {start:0}
    visited_nodes = set()
    while open_set:
        _, current = heapq.heappop(open_set)
        if current == goal:
            path = []
            cur = current
            while cur is not None:
                path.append(cur)
                cur = came_from[cur]
            path.reverse()
            return path
        if current in visited_nodes:
            continue
        visited_nodes.add(current)
        for nb in neighbors(current[0], current[1], grid):
            if nb in blocked:
                continue
            tentative = gscore[current] + 1
            if nb not in gscore or tentative < gscore[nb]:
                gscore[nb] = tentative
                f = tentative + heuristic(nb, goal)
                heapq.heappush(open_set, (f, nb))
                came_from[nb] = current
    return None

# CSP path solver that avoids guard positions by removing them from domains

def csp_path(grid, start, goal, max_len=200, time_limit=1.2, guards=None):
    start_time = time.time()
    if start==goal:
        return [start]
    guard_block = set()
    if guards:
        for g in guards:
            guard_block.add(g.pos)
            for p in g.predict_positions(1):
                guard_block.add(p)
    free_cells = [(x,y) for y in range(GRID_H) for x in range(GRID_W) if grid[y][x]==0 and (x,y) not in guard_block]
    if not free_cells:
        return None
    for k in range(1, max_len+1):
        domains = [set(free_cells) for _ in range(k+1)]
        domains[0] = {start}
        domains[k] = {goal}
        assignment = {}
        def consistent(var, val, assign):
            if val in assign.values():
                return False
            if var>0 and (var-1) in assign:
                px = assign[var-1]
                if abs(px[0]-val[0])+abs(px[1]-val[1])!=1:
                    return False
            if var<k and (var+1) in assign:
                nx = assign[var+1]
                if abs(nx[0]-val[0])+abs(nx[1]-val[1])!=1:
                    return False
            return True
        order = list(range(k+1))
        found = None
        def backtrack(i=0):
            nonlocal found
            if time.time()-start_time>time_limit:
                return False
            if i==len(order):
                found = [assignment[j] for j in range(k+1)]
                return True
            var = order[i]
            for val in list(domains[var]):
                if consistent(var, val, assignment):
                    assignment[var]=val
                    saved = []
                    for nbvar in (var-1,var+1):
                        if 0<=nbvar<=k and nbvar not in assignment:
                            to_remove = set()
                            for d in domains[nbvar]:
                                if abs(d[0]-val[0])+abs(d[1]-val[1])!=1:
                                    to_remove.add(d)
                            if to_remove:
                                domains[nbvar] -= to_remove
                                saved.append((nbvar,to_remove))
                    if backtrack(i+1):
                        return True
                    for nbvar,rem in saved:
                        domains[nbvar] |= rem
                    del assignment[var]
            return False
        if backtrack(0):
            return found
    return None

# Minimax-based guard: simple adversarial move where guard assumes player will try to move away

class Guard:
    def __init__(self,pos):
        self.pos = pos
        self.patrol = []
        self.patrol_idx = 0
    def set_patrol(self, pts):
        self.patrol = pts
    def predict_positions(self, steps=1):
        preds = []
        if self.patrol:
            idx = self.patrol_idx
            pos = self.pos
            for s in range(steps):
                target = self.patrol[idx]
                if pos==target:
                    idx = (idx+1)%len(self.patrol)
                    target = self.patrol[idx]
                dx = (target[0]-pos[0])
                dy = (target[1]-pos[1])
                step = pos
                if abs(dx)>abs(dy) and dx!=0:
                    step = (pos[0]+(1 if dx>0 else -1), pos[1])
                elif dy!=0:
                    step = (pos[0], pos[1]+(1 if dy>0 else -1))
                preds.append(step)
                pos = step
        else:
            for nx,ny in neighbors(self.pos[0], self.pos[1], grid):
                preds.append((nx,ny))
        return preds
    def get_moves(self, grid):
        moves = [(self.pos[0]+dx, self.pos[1]+dy) for dx,dy in [(0,0),(1,0),(-1,0),(0,1),(0,-1)]]
        valid = [m for m in moves if in_bounds(m[0],m[1]) and grid[m[1]][m[0]]==0]
        return valid
    def minimax_move(self, grid, player_pos, depth=3):
        goal = current_goal
        def eval_state(gpos, ppos):
            if gpos==ppos:
                return 1e6
            return 1000 - heuristic(gpos, ppos) - 0.05*heuristic(ppos, goal)
        def max_value(gpos, ppos, d):
            if d==0 or gpos==ppos:
                return eval_state(gpos, ppos), None
            v = -1e9; best=None
            for gm in [(gpos[0]+dx, gpos[1]+dy) for dx,dy in [(1,0),(-1,0),(0,1),(0,-1),(0,0)]]:
                if not (in_bounds(gm[0],gm[1]) and grid[gm[1]][gm[0]]==0):
                    continue
                val, _ = min_value(gm, ppos, d-1)
                if val>v:
                    v=val; best=gm
            return v,best
        def min_value(gpos, ppos, d):
            if d==0 or gpos==ppos:
                return eval_state(gpos, ppos), None
            v = 1e9; best=None
            for pm in [(ppos[0]+dx, ppos[1]+dy) for dx,dy in [(1,0),(-1,0),(0,1),(0,-1),(0,0)]]:
                if not (in_bounds(pm[0],pm[1]) and grid[pm[1]][pm[0]]==0):
                    continue
                val,_ = max_value(gpos, pm, d-1)
                if val<v:
                    v=val; best=pm
            return v,best
        _, move = max_value(self.pos, player_pos, depth)
        if move is None:
            return self.pos
        return move
    def update(self, grid, player_pos):
        try:
            newpos = self.minimax_move(grid, player_pos, depth=3)
            self.pos = newpos
        except Exception:
            # fallback: stay
            pass

# Game state

grid = generate_maze(GRID_W, GRID_H)
start = (1,1)
current_goal = (GRID_W-2, GRID_H-2)
player = start
guards = []

# UI helpers

def draw_grid(surface):
    for y in range(GRID_H):
        for x in range(GRID_W):
            rect = pygame.Rect(x*CELL,y*CELL,CELL,CELL)
            if grid[y][x]==1:
                pygame.draw.rect(surface, WALL, rect)
            else:
                pygame.draw.rect(surface, CELL_BG, rect)
            pygame.draw.rect(surface, (220,220,220), rect,1)

def draw_panel(surface, last_compare, realtime):
    panel = pygame.Rect(WIDTH, 0, PANEL_W, HEIGHT)
    pygame.draw.rect(surface, PANEL_COL, panel)
    x0 = WIDTH + 12
    y = 14
    surface.blit(large.render("Maze Treasure", True, TEXT_COL), (x0, y)); y+=36
    surface.blit(font.render("Controls:", True, TEXT_COL), (x0, y)); y+=20
    surface.blit(font_small.render("Left click: toggle wall", True, TEXT_COL), (x0, y)); y+=18
    surface.blit(font_small.render("Right click: add guard (Shift+Right to remove)", True, TEXT_COL), (x0, y)); y+=18
    surface.blit(font_small.render("Middle click: remove guard", True, TEXT_COL), (x0, y)); y+=18
    surface.blit(font_small.render("G: regenerate | A: run A* | C: run CSP | R: realtime", True, TEXT_COL), (x0, y)); y+=28
    surface.blit(font.render(f"Player: {player}", True, TEXT_COL), (x0, y)); y+=20
    surface.blit(font.render(f"Goal: {current_goal}", True, TEXT_COL), (x0, y)); y+=20
    surface.blit(font.render(f"Guards: {len(guards)}", True, TEXT_COL), (x0, y)); y+=28
    if last_compare:
        alg, t, ln = last_compare
        surface.blit(font.render(f"Last: {alg}", True, TEXT_COL), (x0, y)); y+=20
        surface.blit(font_small.render(f"Time: {t:.4f}s  Length: {ln}", True, TEXT_COL), (x0, y)); y+=22
    surface.blit(font_small.render(f"Realtime: {'ON' if realtime else 'OFF'}", True, TEXT_COL), (x0, y)); y+=26

# Draw path onto semi-transparent overlay so it's always visible

def draw_path_overlay(surface, path):
    if not path:
        return
    overlay = pygame.Surface((WIDTH, HEIGHT), pygame.SRCALPHA)
    overlay.set_alpha(200)
    for p in path:
        r = pygame.Rect(p[0]*CELL+6, p[1]*CELL+6, CELL-12, CELL-12)
        pygame.draw.rect(overlay, PATH_COL + (200,), r, border_radius=6)
    surface.blit(overlay, (0,0))


def draw():
    screen.fill(BG)
    draw_grid(screen)
    # path overlay first so it's visible under player/guards but above cells
    if result_path:
        draw_path_overlay(screen, result_path)
    # start/goal
    pygame.draw.rect(screen, START_COL, (start[0]*CELL,start[1]*CELL,CELL,CELL), border_radius=6)
    pygame.draw.rect(screen, GOAL_COL, (current_goal[0]*CELL,current_goal[1]*CELL,CELL,CELL), border_radius=6)
    # player
    pygame.draw.circle(screen, PLAYER_COL, (player[0]*CELL+CELL//2, player[1]*CELL+CELL//2), CELL//2-3)
    # guards
    for g in guards:
        pygame.draw.circle(screen, GUARD_COL, (g.pos[0]*CELL+CELL//2, g.pos[1]*CELL+CELL//2), CELL//2-5)
    # panel
    draw_panel(screen, last_compare, realtime_mode)
    pygame.display.flip()

# Toggle wall

def toggle_wall_at(mx,my):
    if mx >= WIDTH:
        return
    x = mx//CELL; y = my//CELL
    if in_bounds(x,y) and (x,y)!=start and (x,y)!=current_goal:
        grid[y][x] = 1-grid[y][x]

# Remove guard at cell

def remove_guard_at(cell):
    global guards
    gx, gy = cell
    for i,g in enumerate(guards):
        if g.pos==(gx,gy):
            del guards[i]
            return True
    return False

# Main loop
running = True
last_compare = None
result_path = []
realtime_mode = False

while running:
    dt = clock.tick(FPS)
    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            running=False
        elif event.type==pygame.MOUSEBUTTONDOWN:
            mx,my = pygame.mouse.get_pos()
            if event.button==1:
                toggle_wall_at(mx,my)
            elif event.button==3:
                x = mx//CELL; y = my//CELL
                mods = pygame.key.get_mods()
                # Shift+Right-click removes guard if present
                if mods & pygame.KMOD_SHIFT:
                    removed = remove_guard_at((x,y))
                else:
                    if in_bounds(x,y) and grid[y][x]==0:
                        guards.append(Guard((x,y)))
            elif event.button==2:
                # middle-click: remove guard at clicked cell
                x = mx//CELL; y = my//CELL
                remove_guard_at((x,y))
        elif event.type==pygame.KEYDOWN:
            if event.key==pygame.K_g:
                grid = generate_maze(GRID_W, GRID_H)
                start = (1,1)
                current_goal = (GRID_W-2, GRID_H-2)
                player = start
                guards = []
                result_path = []
            if event.key==pygame.K_a:
                t0 = time.time()
                path = astar(grid, player, current_goal, guards=guards, avoid_radius=1)
                t1 = time.time()
                last_compare = ("A*", t1-t0, len(path) if path else None)
                result_path = path or []
            if event.key==pygame.K_c:
                t0 = time.time()
                path = csp_path(grid, player, current_goal, max_len=400, time_limit=2.0, guards=guards)
                t1 = time.time()
                last_compare = ("CSP", t1-t0, len(path) if path else None)
                result_path = path or []
            if event.key==pygame.K_r:
                realtime_mode = not realtime_mode
    # realtime updates: guards and optional replanning
    if realtime_mode:
        # guards move (minimax)
        for g in guards:
            g.update(grid, player)
            if g.pos==player:
                player = start
                result_path = []
        # simple auto-replan: A* avoids guards
        path = astar(grid, player, current_goal, guards=guards, avoid_radius=1)
        if path:
            if len(path)>1:
                player = path[1]
            else:
                player = path[0]
            result_path = path
    draw()

pygame.quit()
