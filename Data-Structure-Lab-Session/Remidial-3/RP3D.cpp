#include <bits/stdc++.h>
using namespace std;

struct graph{
    long vertexCount, edgeCount;
    vector<vector<pair<long, long>>> adjList;
    
    void init(long v){
        vertexCount = v;
        edgeCount = 0;

        for(int i=0; i<vertexCount; i++){
            adjList.push_back({});
        }
    }

    void add_edge(long vertex1, long vertex2, long weight){
        adjList[vertex1].push_back(make_pair(vertex2, weight));
        edgeCount++;
    }

    void dijkstra(vector<long> &result, long start){
        vector<bool> visited(vertexCount, false);
        priority_queue <pair<long, long>, 
                        vector <pair<long, long>>, 
                        greater <pair<long, long>> > pq;
        result = vector<long>(vertexCount, LONG_MAX);
        
        pq.push(make_pair(0, start));
        result[start] = 0;

        while(!pq.empty()){
            auto temp = pq.top();
            pq.pop();

            visited[temp.second] = true;

            for(auto vertex:adjList[temp.second]){
                long nextVertex = vertex.first;
                long weight = vertex.second;

                if(!visited[nextVertex]){
                    if(temp.first + weight < result[nextVertex]) {
                        result[nextVertex] = temp.first + weight;
                        pq.push(make_pair(result[nextVertex], nextVertex));
                    }
                }
            }
        }
    }
};

int main(){
    graph g;
    vector<long> result;
    long N, K;
    cin >> N >> K;
    g.init(N);
    K--;
    long U, V, W;
    long maxWeight = 0;
    while (true) {
        cin >> U >> V >> W;
        if(U == 0 && V == 0 && W == 0) break;
        g.add_edge(U-1, V-1, W);
        maxWeight += W;
    }
    g.dijkstra(result, K);
    long max = -1;
    bool reachable = true;
    for(auto it : result) {
        if (it > maxWeight || it < 0) {
            reachable = false;
            break;
        }
        if (max < it) max = it;
    }
    if(reachable) {
        cout << max << endl;
    } else {
        cout << "-1" << endl;
    }
}
