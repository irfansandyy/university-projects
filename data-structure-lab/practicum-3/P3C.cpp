#include <iostream>
#include <vector>
#include <set>

struct graph {
    std::vector<std::vector<std::pair<long, long>>> adjList;
    bool found = false;

    graph() : adjList(201) {};

    void dfs(long node, long current, long target, std::set<std::pair<long, long>> &visited, std::vector<long> &result) {
        if (current > target || found) return;
        if (current == target) {
            found = true;
            return;
        }

        result.push_back(node);

        for (auto &neighbor : adjList[node]) {
            long next = neighbor.first;
            long weight = neighbor.second;
            std::pair<long, long> edge = {std::min(node, next), std::max(node, next)};
            if (visited.find(edge) == visited.end()) {
                visited.insert(edge);
                dfs(next, current + weight, target, visited, result);
                if (found) return;
                visited.erase(edge);
            }
        }
        result.pop_back();
    }
};

int main() {
    long T;
    std::cin >> T;

    for(int it = 0; it < T; it++) {
        graph g;
        long i, j, w, search, maxnode = 0;
        
        while (true) {
            std::cin >> i >> j >> w;
            if(i == 0 && j == 0 && w == 0) break;
            g.adjList[i].push_back(std::make_pair(j, w));
            g.adjList[j].push_back(std::make_pair(i, w));
            maxnode = std::max(maxnode, std::max(i, j));
        }
        std::cin >> search;

        for(int i = 0; i <= maxnode && !g.found; i++) {
            std::set<std::pair<long, long>> visited;
            std::vector<long> result;
            g.dfs(i, 0, search, visited, result);
        }

        std::cout << (g.found ? "YES" : "NO") << std::endl;
    }
}