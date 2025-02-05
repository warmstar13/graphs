#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP

#include "GraphGenerator.hpp"
#include <vector>
#include <tuple>
using namespace std;

const int INF_1 = 1e9;

inline vector<int> bellmanFord(const Graph &graph, int start) {
    int n = graph.vertexCount;
    vector<int> dist(n + 1, INF_1);
    dist[start] = 0;

    for (int i = 1; i < n; i++) {
        for (const auto& edge : graph.edges) {
            int u, v, w;
            tie(u, v, w) = edge;
            if (dist[u] < INF_1 && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
            if (!graph.isDirected && dist[v] < INF_1 && dist[u] > dist[v] + w) {
                dist[u] = dist[v] + w;
            }
        }
    }
    return dist;
}

#endif // BELLMAN_FORD_HPP
