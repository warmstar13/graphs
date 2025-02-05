#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "GraphGenerator.hpp"  // This header defines Graph and GraphInputs.
#include <queue>
#include <vector>
#include <tuple>
using namespace std;

const int INF = 1e9;

// Dijkstra algorithm that computes shortest paths from a given start vertex.
// Assumes the graph is directed (or uses only one direction of edges for undirected graphs).
// The algorithm first builds an adjacency list from the edge list contained in graph.edges.
inline vector<int> dijkstra(const Graph &graph, int start) {
    int n = graph.vertexCount;
    // Build an adjacency list (1-indexed)
    vector<vector<pair<int, int>>> adj(n + 1);
    for (const auto &edge : graph.edges) {
        int u, v, w;
        tie(u, v, w) = edge;
        adj[u].push_back({v, w});
        if (!graph.isDirected) {
            adj[v].push_back({u, w});
        }
        // Если граф неориентированный, можно добавить:
        // adj[v].push_back({u, w});
    }

    vector<int> dist(n + 1, INF);
    dist[start] = 0;

    // Min-heap: (distance, vertex)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto temp = pq.top();
        int cur_dist = temp.first;
        int u = temp.second;
        pq.pop();

        // If the current distance doesn't match the stored distance, skip.
        if (cur_dist != dist[u])
            continue;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (cur_dist + weight < dist[v]) {
                dist[v] = cur_dist + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

#endif // DIJKSTRA_HPP
