import heapq

class Graph:
    def __init__(self):
        self.__graph: dict[str, dict[str, int]] = {}
    
    def __add_node(self, node: str) -> None:
        if node not in self.__graph:
            self.__graph[node] = {}
            
    def add_edge(self, u: str, v: str, weight: int = 1) -> None:
        self.__add_node(u)
        self.__add_node(v)
        self.__graph[u][v] = weight
        self.__graph[v][u] = weight
    
    def bfs(self, start: str, target: str) -> list[str]:
        if start not in self.__graph or target not in self.__graph:
            return []

        visited = set([start])
        q = [start]
        parent: dict[str, str | None] = {start: None}

        while q:
            u = q.pop(0)
            if u == target:
                break
            for v in self.__graph[u]:
                if v not in visited:
                    visited.add(v)
                    parent[v] = u
                    q.append(v)

        path = []
        node = target
        while node is not None:
            path.append(node)
            node = parent.get(node)
        path.reverse()

        if path[0] == start:
            return path
        return []

    def dfs(self, start: str, target: str) -> list[str]:
        if start not in self.__graph or target not in self.__graph:
            return []

        visited = set()
        q = [start]
        parent: dict[str, str | None] = {start : None}

        while q:
            u = q.pop(0)
            if u == target:
                break
            if u not in visited:
                visited.add(u)
                for v in self.__graph[u]:
                    if v not in visited and v not in parent:
                        parent[v] = u
                        q.append(v)

        path = []
        node = target
        while node is not None:
            path.append(node)
            node = parent.get(node)
        path.reverse()

        if path[0] == start:
            return path
        return []


    def ucs(self, start: str, target: str) -> tuple[list[str], int]:
        if start not in self.__graph or target not in self.__graph:
            return [], float("inf")

        pq: list[tuple[int, str]] = [(0, start)]
        heapq.heapify(pq)

        parent: dict[str, str | None] = {start: None}
        cost: dict[str, int] = {start: 0}

        while pq:
            current_cost, u = heapq.heappop(pq)

            if u == target:
                break

            for v, w in self.__graph[u].items():
                new_cost = current_cost + w
                if v not in cost or new_cost < cost[v]:
                    cost[v] = new_cost
                    parent[v] = u
                    heapq.heappush(pq, (new_cost, v))

        if target not in parent:
            return [], float("inf")

        path = []
        node = target
        while node is not None:
            path.append(node)
            node = parent[node]
        path.reverse()

        return path, cost[target]

g = Graph()
g.add_edge("Arad", "Zerind", 75)
g.add_edge("Arad", "Sibiu", 140)
g.add_edge("Arad", "Timisoara", 118)
g.add_edge("Zerind", "Oradea", 71)
g.add_edge("Oradea", "Sibiu", 151)
g.add_edge("Timisoara", "Lugoj", 111)
g.add_edge("Lugoj", "Mehadia", 70)
g.add_edge("Mehadia", "Dobreta", 75)
g.add_edge("Dobreta", "Craiova", 120)
g.add_edge("Craiova", "Rimnicu Vilcea", 146)
g.add_edge("Craiova", "Pitesti", 138)
g.add_edge("Rimnicu Vilcea", "Sibiu", 80)
g.add_edge("Rimnicu Vilcea", "Pitesti", 97)
g.add_edge("Sibiu", "Fagaras", 99)
g.add_edge("Fagaras", "Bucharest", 211)
g.add_edge("Pitesti", "Bucharest", 101)
g.add_edge("Bucharest", "Giurgiu", 90)
g.add_edge("Bucharest", "Urziceni", 85)
g.add_edge("Urziceni", "Hirsova", 98)
g.add_edge("Urziceni", "Vaslui", 142)
g.add_edge("Hirsova", "Eforie", 86)
g.add_edge("Vaslui", "Iasi", 92)
g.add_edge("Iasi", "Neamt", 87)

print(g.bfs("Arad", "Bucharest"))
print(g.dfs("Arad", "Bucharest"))
print(g.ucs("Arad", "Bucharest"))