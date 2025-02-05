#ifndef DINIC_ALGORITHM_HPP
#define DINIC_ALGORITHM_HPP

#include "GraphGenerator.hpp"
#include "FlowEdge.hpp"
#include <bits/stdc++.h>

const int INF_3 = 1e9;

class Dinic {
  private:
    FlowNetwork& network;
    int n;
    vector<int> level;
    vector<int> start;

  public:
    Dinic(FlowNetwork& network) : network(network), n(network.n) {
        level.resize(n + 1);
        start.resize(n + 1);
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto &edge : network.adj[u]) {
                if (level[edge.v] < 0 && edge.flow < edge.capacity) {
                    level[edge.v] = level[u] + 1;
                    q.push(edge.v);
                }
            }
        }
        return level[t] >= 0;
    }

    int dfs(int u, int t, int flow) {

        if (flow == 0) {
            return 0;
        }
        if (u == t) {
            return flow;
        }

        for (; start[u] < network.adj[u].size(); start[u]++) {
            FlowEdge& edge = network.adj[u][start[u]];
            if (level[edge.v] == level[u] + 1 && edge.flow < edge.capacity) {
                int curr_flow = min(flow, edge.capacity - edge.flow);
                int temp_flow = dfs(edge.v, t, curr_flow);
                if (temp_flow > 0) {
                    edge.flow += temp_flow;
                    network.adj[edge.v][edge.rev].flow -= temp_flow;
                    return temp_flow;
                }
            }
        }
        return 0;
    }

    int maxFlow(int s, int t) {
        int total = 0;
        while (bfs(s, t)) {
            fill(start.begin(), start.end(), 0);
            while (int flow = dfs(s, t, INF))
                total += flow;
        }
        return total;
    }
};

#endif // DINIC_ALGORITHM_HPP
