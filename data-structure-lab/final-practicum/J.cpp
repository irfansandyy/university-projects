#include <bits/stdc++.h>
using namespace std;

struct graph{
    long vertexCount;
    vector<vector<pair<long, long>>> adjList;
    
    void init(long v){
        vertexCount = v;
        adjList.assign(v + 1, vector<pair<long, long>>());
    }

    void add_edge(long vertex1, long vertex2, long weight){
        adjList[vertex1].push_back(make_pair(vertex2, weight));
    }

    long djikstra(int n, int start_node, int end_node){
        priority_queue<tuple<long, int, int, int>,
                       vector<tuple<long, int, int, int>>,
                       greater<tuple<long, int, int, int>>> pq;

        vector<vector<vector<long>>> dist(n + 1, vector<vector<long>>(n + 1, vector<long>(2, LONG_MAX)));

        dist[start_node][1][0] = 0;
        pq.push({0, start_node, 1, 0});

        while(!pq.empty()){
            auto [current_cost, u, path_len, code_used] = pq.top();
            pq.pop();

            if(current_cost > dist[u][path_len][code_used]) continue;
            
            for(auto& edge : adjList[u]){
                int v = edge.first;
                long weight = edge.second;
                
                if (path_len >= n) continue;
                int next_path_len = path_len + 1;

                long new_cost_normal = current_cost + weight;
                if (new_cost_normal < dist[v][next_path_len][code_used]){
                    dist[v][next_path_len][code_used] = new_cost_normal;
                    pq.push({new_cost_normal, v, next_path_len, code_used});
                }

                if(code_used == 0){
                    long new_cost_special = current_cost + (weight / 2);
                    if (new_cost_special < dist[v][next_path_len][1]){
                        dist[v][next_path_len][1] = new_cost_special;
                        pq.push({new_cost_special, v, next_path_len, 1});
                    }
                }
            }
        }

        long min_total_cost = LONG_MAX;

        for(int i = 1; i <= n; i++){
            if (dist[end_node][i][0] != LONG_MAX) {
                min_total_cost = min(min_total_cost, dist[end_node][i][0]);
            }
            
            if(i >= (n/2) && dist[end_node][i][1] != LONG_MAX){
                min_total_cost = min(min_total_cost, dist[end_node][i][1]);
            }
        }

        return min_total_cost;
    }
};

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    graph g;
    g.init(n);

    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }

    cout << g.djikstra(n, s, t) << endl;

    return 0;
}
