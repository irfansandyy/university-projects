#include <bits/stdc++.h>
using namespace std;

struct graph{
    long vertexCount, edgeCount;
    vector<vector<long>> adjList;
    
    void init(long v){
        vertexCount = v;
        edgeCount = 0;

        for(int i=0; i<vertexCount; i++){
            adjList.push_back({});
        }
    }

    void add_edge(long vertex1, long vertex2){
        adjList[vertex1].push_back(vertex2);
        adjList[vertex2].push_back(vertex1);
        edgeCount++;
    }

    void bfs(vector<long> &result, long start, vector<long> &distance){
        vector<bool> visited(vertexCount, false);
        queue<long> q;

        q.push(start);
        visited[start] = true;
        distance[start] = 0;
        result.push_back(start);

        while(!q.empty()){
            long temp = q.front();
            q.pop();

            for(auto vertex:adjList[temp]){
                if (!visited[vertex]){
                    visited[vertex] = true;
                    distance[vertex] = distance[temp] + 1;
                    q.push(vertex);
                    result.push_back(vertex);
                }
            }
        }
    }
};

int main(){
    graph g;
    long N, M, S, T;
    cin >> N >> M >> S >> T;
    vector<long> result;
    vector<long> distance(N, -1);
    g.init(N);
    for(int i = 0; i < M; i++) {
        long u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }

    g.bfs(result, S, distance);
    cout << distance[T] << endl;
    return 0;
}