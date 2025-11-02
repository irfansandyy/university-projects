from flask import Flask, request, jsonify, send_from_directory
from time import perf_counter
import copy
from flask_cors import CORS

app = Flask(__name__, static_folder='static', static_url_path='/static')
CORS(app)

def pretty(grid):
    return "\n".join(" ".join(str(x) for x in row) for row in grid)

def in_row(grid, r, num): return any(grid[r][j]==num for j in range(9))
def in_col(grid, c, num): return any(grid[i][c]==num for i in range(9))
def in_box(grid, r, c, num):
    br, bc = (r//3)*3, (c//3)*3
    for i in range(br, br+3):
        for j in range(bc, bc+3):
            if grid[i][j]==num: return True
    return False

def is_valid(grid, r, c, num):
    if in_row(grid, r, num): return False
    if in_col(grid, c, num): return False
    if in_box(grid, r, c, num): return False
    return True

def solve_csp_with_steps(grid):
    steps = []
    g = copy.deepcopy(grid)
    start = perf_counter()

    def solve():
        for r in range(9):
            for c in range(9):
                if g[r][c] == 0:
                    for num in range(1, 10):
                        if is_valid(g, r, c, num):
                            g[r][c] = num
                            steps.append({"type":"set","r":r,"c":c,"v":num})
                            if solve():
                                return True
                            # backtrack
                            g[r][c] = 0
                            steps.append({"type":"backtrack","r":r,"c":c})
                    return False
        return True

    ok = solve()
    duration = perf_counter() - start
    return {"success": ok, "solution": g, "steps": steps, "time": duration}

def min_conflicts_with_steps(grid, max_restarts=50, max_iters_per_restart=5000, acceptance_prob=0.01):
    import copy, random, math, time
    steps = []
    fixed = [[(grid[r][c] != 0) for c in range(9)] for r in range(9)]
    rng = random.Random()

    def total_conflicts(state):
        conflicts = 0
        for c in range(9):
            cnt = {}
            for r in range(9):
                v = state[r][c]
                cnt[v] = cnt.get(v, 0) + 1
            for v, n in cnt.items():
                if n > 1:
                    conflicts += n - 1
        for br in range(0, 9, 3):
            for bc in range(0, 9, 3):
                cnt = {}
                for r in range(br, br + 3):
                    for c in range(bc, bc + 3):
                        v = state[r][c]
                        cnt[v] = cnt.get(v, 0) + 1
                for v, n in cnt.items():
                    if n > 1:
                        conflicts += n - 1
        return conflicts

    def conflicted_cells(state):
        out = []
        for r in range(9):
            for c in range(9):
                if fixed[r][c]:
                    continue
                v = state[r][c]
                col_dup = sum(1 for rr in range(9) if rr != r and state[rr][c] == v) > 0
                br, bc = (r // 3) * 3, (c // 3) * 3
                box_dup = any((rr != r or cc != c) and state[rr][cc] == v
                              for rr in range(br, br+3) for cc in range(bc, bc+3))
                if col_dup or box_dup:
                    out.append((r, c))
        return out

    def init_state_from_grid():
        state = copy.deepcopy(grid)
        for r in range(9):
            present = set(state[r][c] for c in range(9) if state[r][c] != 0)
            missing = [n for n in range(1, 10) if n not in present]
            rng.shuffle(missing)
            for c in range(9):
                if not fixed[r][c]:
                    state[r][c] = missing.pop()
                    steps.append({"type": "set", "r": r, "c": c, "v": state[r][c]})
        return state

    total_iterations = 0
    best_solution = None
    best_cost = math.inf
    start_time = time.perf_counter()

    for restart in range(max_restarts):
        state = init_state_from_grid()
        cur_cost = total_conflicts(state)
        if cur_cost < best_cost:
            best_cost = cur_cost
            best_solution = copy.deepcopy(state)
        if cur_cost == 0:
            return {"success": True, "solution": state, "steps": steps, "time": time.perf_counter()-start_time, "iterations": total_iterations, "final_cost": 0}

        stagnation = 0
        for it in range(max_iters_per_restart):
            total_iterations += 1
            conflicted = conflicted_cells(state)
            if not conflicted:
                cur_cost = 0
                best_solution = copy.deepcopy(state)
                best_cost = 0
                return {"success": True, "solution": state, "steps": steps, "time": time.perf_counter()-start_time, "iterations": total_iterations, "final_cost": 0}

            r, c = rng.choice(conflicted)
            candidate_cols = [cc for cc in range(9) if not fixed[r][cc] and cc != c]
            if not candidate_cols:
                stagnation += 1
                if stagnation > 1000:
                    break
                continue

            best_swap = None
            best_swap_cost = math.inf

            for cc in candidate_cols:
                state[r][c], state[r][cc] = state[r][cc], state[r][c]
                cost = total_conflicts(state)
                state[r][c], state[r][cc] = state[r][cc], state[r][c]
                if cost < best_swap_cost:
                    best_swap_cost = cost
                    best_swap = cc

            if best_swap is None:
                stagnation += 1
                continue

            if best_swap_cost < cur_cost or rng.random() < acceptance_prob:
                cc = best_swap
                v1 = state[r][c]
                v2 = state[r][cc]
                state[r][c], state[r][cc] = v2, v1
                cur_cost = best_swap_cost
                steps.append({"type": "swap", "r": r, "c": c, "with_c": cc, "v1": state[r][c], "v2": state[r][cc], "cost": cur_cost})
                stagnation = 0
                if cur_cost < best_cost:
                    best_cost = cur_cost
                    best_solution = copy.deepcopy(state)
                if cur_cost == 0:
                    return {"success": True, "solution": state, "steps": steps, "time": time.perf_counter()-start_time, "iterations": total_iterations, "final_cost": 0}
            else:
                stagnation += 1

            if stagnation > 2000:
                break

        steps.append({"type": "restart", "restart_index": restart})
    elapsed = time.perf_counter() - start_time
    return {"success": False, "solution": best_solution, "steps": steps, "time": elapsed, "iterations": total_iterations, "final_cost": best_cost, "message": f"Min-conflicts ended without full solution; final_cost={best_cost}"}

@app.route('/')
def index():
    return send_from_directory('static','index.html')

@app.route('/solve_csp', methods=['POST'])
def solve_csp():
    data = request.get_json()
    grid = data.get("grid")
    res = solve_csp_with_steps(grid)
    return jsonify(res)

@app.route('/solve_minconflict', methods=['POST'])
def solve_minconflict():
    data = request.get_json()
    grid = data.get("grid")
    iteration_limit = int(float(data.get("iteration_limit", 5000)))
    acceptance_prob = float(data.get("acceptance_prob", 0.01))
    res = min_conflicts_with_steps(grid, max_restarts=200, max_iters_per_restart=iteration_limit, acceptance_prob=acceptance_prob)
    return jsonify(res)

if __name__ == '__main__':
    app.run(debug=True)
