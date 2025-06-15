#include <bits/stdc++.h>

struct Edge {
    int to;
    int weight;
    bool is_risky;
};

struct State {
    long distance;
    int vertex;
    long prev_edge_weight;
    long start_edge_weight;
    bool path_is_risky;

    bool operator>(const State& other) const {
        return distance > other.distance;
    }
};

int main() {
    int n_vertices, n_edges;
    std::cin >> n_vertices >> n_edges;

    std::vector<std::vector<Edge>> adj(n_vertices);
    for (int i = 0; i < n_edges; ++i) {
        int u, v, w;
        bool risky;
        std::cin >> u >> v >> w >> risky;
        adj[u].push_back({v, w, risky});
    }

    int start_node, finish_node;
    long max_weight;
    std::cin >> start_node >> finish_node >> max_weight;

    std::vector<std::vector<long>> distances(n_vertices, std::vector<long>(2, __LONG_MAX__));

    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;

    if (adj[start_node].empty()) {
        std::cout << "Increase lift and coast please max, just try to stay in front of Lando";
        return 0;
    }
    
    Edge first_edge = adj[start_node][0];
    long start_edge_weight = first_edge.weight;
    int first_neighbor = first_edge.to;

    distances[start_node][0] = 0;
    distances[first_neighbor][0] = start_edge_weight;
    pq.push({start_edge_weight, first_neighbor, start_edge_weight, start_edge_weight, false});

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        long dist = current.distance;
        int u = current.vertex;
        long prev_w = current.prev_edge_weight;
        long start_w = current.start_edge_weight;
        bool is_path_risky = current.path_is_risky;

        if (dist > distances[u][is_path_risky]) continue;

        for (const auto& edge : adj[u]) {
            int v = edge.to;
            long current_edge_weight;

            if (edge.is_risky) current_edge_weight = prev_w + start_w;
            else  current_edge_weight = edge.weight;

            long new_dist = dist + current_edge_weight;
            bool new_path_is_risky = is_path_risky || edge.is_risky;

            if (new_dist < distances[v][new_path_is_risky]) {
                distances[v][new_path_is_risky] = new_dist;
                pq.push({new_dist, v, current_edge_weight, start_w, new_path_is_risky});
            }
        }
    }

    long dist_normal = distances[finish_node][0];
    long dist_risky = distances[finish_node][1];
    long best_dist = std::min(dist_normal, dist_risky);

    if (best_dist > max_weight || best_dist == __LONG_MAX__) {
        std::cout << "Increase lift and coast please max, just try to stay in front of Lando";
    } else {
        if (dist_risky <= dist_normal) {
            std::cout << "Press to overtake and dive bomb please max";
        } else {
            std::cout << "Decrease lift and coast please max, oscar is slower in front of you";
        }
    }

    return 0;
}
