#ifndef PRIM_HPP
#define PRIM_HPP

#include <bits/stdc++.h>

typedef tuple<int, int, int> Edge;

pair<int, vector<tuple<int, int, int>>> prim(const Graph& graph) {
    if (graph.isDirected) {
        throw runtime_error("Prim only for undirected!");
    }

    int n = graph.vertexCount;
    vector<vector<pair<int, int>>> adj(n + 1);
    for (const auto& edge : graph.edges) {
        int u, v, w;
        tie(u, v, w) = edge;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<tuple<int, int, int>> mst;
    int totalWeight = 0;

    vector<bool> inMST(n + 1, false);

    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    int start = 1;
    inMST[start] = true;

    for (const auto &p : adj[start]) {
        int to = p.first;
        int weight = p.second;
        pq.push(make_tuple(weight, start, to));
    }

    int counter = 1;

    while (!pq.empty() && counter < n) {
        int weight, u, v;
        tie(weight, u, v) = pq.top();
        pq.pop();

        if (inMST[v]) continue;

        inMST[v] = true;
        totalWeight += weight;
        mst.push_back(make_tuple(u, v, weight));
        counter++;

        for (const auto &p : adj[v]) {
            int to = p.first;
            int w = p.second;
            if (!inMST[to]) {
                pq.push(make_tuple(w, v, to));
            }
        }
    }

    return {totalWeight, mst};
}

#endif // PRIM_HPP
