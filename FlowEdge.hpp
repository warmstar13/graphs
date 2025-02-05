#ifndef FLOW_EDGE_HPP
#define FLOW_EDGE_HPP

struct FlowEdge {
    int u, v;
    int capacity;
    int flow;
    int rev;
};

class FlowNetwork {
  public:
    int n;
    vector<vector<FlowEdge>> adj;

    FlowNetwork(int n) : n(n) {
        adj.resize(n + 1);
    }

    void addEdge(int u, int v, int capacity, bool isDirected) {
        FlowEdge a, b;
        if (isDirected) {
            a = {u, v, capacity, 0, (int)adj[v].size()};
            b = {v, u, 0, 0, (int)adj[u].size()};
        } else {
            a = {u, v, capacity, 0, (int)adj[v].size()};
            b = {v, u, capacity, 0, (int)adj[u].size()};
        }
        adj[u].push_back(a);
        adj[v].push_back(b);
    }
};

inline FlowNetwork buildFlowNetwork(const Graph& graph) {
    int n = graph.vertexCount;
    FlowNetwork network(n);
    for (const auto &edge : graph.edges) {
        int u, v, capacity;
        tie(u, v, capacity) = edge;
        network.addEdge(u, v, capacity, graph.isDirected);
    }
    return network;
}

#endif // FLOW_EDGE_HPP

