#include <bits/stdc++.h>
 
struct graph{
    long vertexCount, edgeCount;
    std::vector<std::vector<std::pair<long, long>>> adjList;
   
    void init(long v){
        vertexCount = v;
        edgeCount = 0;
        adjList.resize(vertexCount);
    }
 
    void add_edge(long vertex1, long vertex2, long weight){
        adjList[vertex1].push_back(std::make_pair(vertex2, weight));
        edgeCount++;
    }
 
    void dijkstra(std::vector<long> &result, std::vector<long> &predecessor, long start){
        std::vector<bool> visited(vertexCount, false);
        std::priority_queue <std::pair<long, long>, std::vector <std::pair<long, long>>, std::greater <std::pair<long, long>> > pq;
        result = std::vector<long>(vertexCount, LONG_MAX);
        predecessor = std::vector<long>(vertexCount, -1);
       
        pq.push(std::make_pair(0, start));
        result[start] = 0;
 
        while(!pq.empty()){
            auto temp = pq.top();
            pq.pop();

            long u = temp.second;
            if (visited[u]) continue;
            visited[u] = true; 

            for(auto vertex:adjList[u]){
                long nextVertex = vertex.first;
                long weight = vertex.second;
 
                if(!visited[nextVertex] && result[u] + weight < result[nextVertex]){
                    result[nextVertex] = result[u] + weight;
                    pq.push(std::make_pair(result[nextVertex], nextVertex));
                    predecessor[nextVertex] = u;
                }
            }
        }
    }
 
    std::vector<long> trace_path(long start, long end, const std::vector<long>& predecessor) {
        std::vector<long> path;
        for (long at = end; at != -1; at = predecessor[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        if (path.front() == start) {
            return path;
        }
        return {};
    }
};
 
 
int main(){
    graph city;
    int V, N, S, E;

    std::cin >> V >> N;
    city.init(V);
    for(int i = 0; i < N; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        city.add_edge(a, b, c);
    }
    std::cin >> S >> E;
 
    std::vector<long> dijkstra_result;
    std::vector<long> predecessor;

    city.dijkstra(dijkstra_result, predecessor, S);
    std::vector<long> path = city.trace_path(S, E, predecessor);
   
    if (!path.empty()) {
        std::cout << "Path found with cost " << dijkstra_result[E] << ": ";
        for (auto node : path) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Impossible to find the path" << std::endl;
    }
    return 0;
}
 
