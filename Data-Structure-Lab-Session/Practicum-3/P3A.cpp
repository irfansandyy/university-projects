#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct graph {
    long vertexCount, edgeCount;
    std::vector<std::vector<std::pair<long, long>>> adjList;
    std::vector<std::pair<long, std::pair<long, long>>> edgeList;

    void init(long v) {
        vertexCount = v;
        edgeCount = 0;

        for (int i = 0; i < vertexCount; i++) {
            adjList.push_back({});
        }
    }

    void add_edge(long vertex1, long vertex2, long weight) {
        adjList[vertex1].push_back(std::make_pair(vertex2, weight));
        adjList[vertex2].push_back(std::make_pair(vertex1, weight));

        edgeList.push_back(std::make_pair(weight, std::make_pair(vertex1, vertex2)));
        edgeCount++;
    }

    void bfs(long mulai, long L, std::vector<long> &result) {
        std::vector<bool> visited(this->vertexCount, false);
        std::vector<long> distance(this->vertexCount, -1);
        std::queue<long> q;

        q.push(mulai);
        visited[mulai] = true;
        distance[mulai] = 0;

        while(!q.empty()) {
            long temp = q.front();
            q.pop();

            for(auto neighbor : this->adjList[temp]) {
                long next = neighbor.first;
                if (!visited[next]) {
                    visited[next] = true;
                    distance[next] = distance[temp] + 1;
                    q.push(next);
                }
            }
        }

        for(long i = 0; i < this->vertexCount; ++i) {
            if(distance[i] == L) result.push_back(i);
        }
    }
};

int main() {
    graph g;
    long n, m, L, s;
    std::vector<long> hasil;
    
    std::cin >> n >> m >> L;
    std::cin >> s;
    g.init(n);

    for(long i = 0; i < m; ++i) {
        long u, v;
        std::cin >> u >> v;
        g.add_edge(u, v, 1); 
    }

    g.bfs(s, L, hasil);

    if (hasil.empty()) std::cout << "Not Found" << std::endl;
    else {
        sort(hasil.begin(), hasil.end());
        for (auto node : hasil){
            std::cout << node << std::endl;
        }
    }

    return 0;
}
