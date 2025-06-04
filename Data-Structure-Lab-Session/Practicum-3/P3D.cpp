#include <iostream>
#include <vector>
#include <algorithm>

struct graph {
    long vertexCount, edgeCount;
    std::vector<std::vector<long>> adjList;
    std::vector<long> parent;
    std::vector<bool> visited;
    std::vector<long> path;

    void init(long v) {
        vertexCount = v;
        edgeCount = 0;
        adjList.resize(vertexCount);
        parent.resize(vertexCount, -1);
        visited.resize(vertexCount, false);
    }

    void add_edge(long vertex1, long vertex2) {
        adjList[vertex1].push_back(vertex2);
        adjList[vertex2].push_back(vertex1);
        edgeCount++;
    }

    bool cycleCheck(long v, long p) {
        visited[v] = true;
        for (auto neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                parent[neighbor] = v;
                if (cycleCheck(neighbor, v)) {
                    return true;
                }
            } else if (neighbor != p) {
                long current = v;
                while (current != neighbor) {
                    path.push_back(current);
                    current = parent[current];
                }
                path.push_back(neighbor);
                return true;
            }
        }
        return false;
    }

    bool hasCycle() {
        for (long i = 0; i < vertexCount; ++i) {
            if (!visited[i] && cycleCheck(i, -1)) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    int T;
    std::cin >> T;

    for (int i = 0; i < T; i++) {
        long V, N;
        std::cin >> V >> N;

        graph g;
        g.init(V);

        for (long i = 0; i < N; ++i) {
            long j, k;
            std::cin >> j >> k;
            g.add_edge(j, k);
        }

        if (g.hasCycle()) {
            sort(g.path.begin(), g.path.end());
            std::cout << "VOCALOID CYCLE PROGRAM (VCP) : CYCLE DETECTED";
            for (auto v : g.path) {
                std::cout << " " << v;
            }
            std::cout << "\n";
        } 
        else std::cout << "VOCALOID CYCLE PROGRAM (VCP) : NO CYCLE DETECTED\n";
    }
}