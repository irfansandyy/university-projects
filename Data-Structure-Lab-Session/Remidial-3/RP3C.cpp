#include <bits/stdc++.h>
using namespace std;
 
struct graph{
    long vertexCount, edgeCount;
    vector<vector<pair<long, long>>> adjList;
   
    void init(long v){
        vertexCount = v;
        edgeCount = 0;
        adjList.resize(vertexCount);
    }
 
    void add_edge(long vertex1, long vertex2, long weight){
        adjList[vertex1].push_back(make_pair(vertex2, weight));
        adjList[vertex2].push_back(make_pair(vertex1, weight));
        edgeCount++;
    }
 
    void dijkstra(vector<long> &result, vector<long> &predecessor, long start){
        vector<bool> visited(vertexCount, false);
        priority_queue <pair<long, long>, vector <pair<long, long>>, greater <pair<long, long>> > pq;
        result = vector<long>(vertexCount, LONG_MAX);
        predecessor = vector<long>(vertexCount, -1);
       
        pq.push(make_pair(0, start));
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
                    pq.push(make_pair(result[nextVertex], nextVertex));
                    predecessor[nextVertex] = u;
                }
            }
        }
    }
 
    vector<long> trace_path(long start, long end, const vector<long>& predecessor) {
        vector<long> path;
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
    graph g;
    long A, B, N;

    cin >> A >> B;
    g.init(A);
    for(long i = 0; i < B; i++) {
        long v1, v2, weight;
        cin >> v1 >> v2 >> weight;
        g.add_edge(v1, v2, weight);
    }

    cin >> N;
    vector<long> sources;
    for(long i = 0; i < N; i++) {
        long s;
        cin >> s;
        sources.push_back(s);
    }

    for(long i = 0; i < N; i++) {
        vector<long> result;
        vector<long> predecessor;

        if(sources[i] >= A || sources[i] < 0) {
            cout << "Invalid starting point\n";
            continue;
        }
        g.dijkstra(result, predecessor, sources[i]);
        for(long j = 0; j < A; j++) {
            if(j == sources[i]) continue;
            vector<long> path = g.trace_path(sources[i], j, predecessor);
            cout << "---From " << sources[i] << " to " << j << "---\n";
            long unsigned int k;
            for(k = 0; k < path.size() - 1; k++) {
                cout << path[k] << " - ";
            }
            cout << path[k] << "\n";
        }
    }
    return 0;
}

