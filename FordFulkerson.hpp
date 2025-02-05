#ifndef FORD_FULKERSON_HPP
#define FORD_FULKERSON_HPP

#include <bits/stdc++.h>
#include "FlowEdge.hpp"

const int INF_2 = 1e9;


inline int edmondsKarp(FlowNetwork& network, int source, int sink) {
    int max_flow = 0;

    while(true) {
        vector<int> parent(network.n + 1, -1);
        vector<int> parentEdge(network.n + 1, -1);
        queue<int> q;

        q.push(source);
        parent[source] = source;

        while (!q.empty() && parent[sink] == -1) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < network.adj[u].size(); i++) {
                FlowEdge& e= network.adj[u][i];

                if (parent[e.v] == -1 && (e.capacity - e.flow) > 0) {
                    parent[e.v] = u;
                    parentEdge[e.v] = i;
                    q.push(e.v);
                }
            }
        }

        if (parent[sink] == -1) {
            break;
        }

        int path_flow = INF_2;
        int v = sink;

        while (v != source) {
            int u = parent[v];
            int idx = parentEdge[v];
            FlowEdge& e = network.adj[u][idx];
            path_flow = min(path_flow, e.capacity - e.flow);
            v = u;
        }

        v = sink;
        while (v != source) {
            int u = parent[v];
            int idx = parentEdge[v];
            FlowEdge &e = network.adj[u][idx];
            e.flow += path_flow;
            // Обновляем обратное ребро.
            network.adj[v][e.rev].flow -= path_flow;
            v = u;
        }

        max_flow += path_flow;
    }
    return max_flow;
}

#endif // FORD_FULKERSON_HPP
