#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP

#include <bits/stdc++.h>

class DisjointSet {
  public:
    DisjointSet(int n): parent(n + 1) {
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unionSets(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        parent[b] = a;
        return true;
    }
  private:
    vector<int> parent;
};



pair<int, vector<tuple<int, int, int>>> kruskal(const Graph& graph) {
    if (graph.isDirected) {
        throw runtime_error("Kruskal only for undirected!");
    }
    int n = graph.vertexCount;
    auto edges = graph.edges;
    sort(edges.begin(), edges.end(), [](const tuple<int, int, int>& a,
                                        const tuple<int, int, int>& b){
        return get<2>(a) < get<2>(b);
         });
    DisjointSet ds(n);
    int totalWeight = 0;
    vector<tuple<int, int, int>> result;
     for (const auto &edge : edges) {
        int u, v, w;
        tie(u, v, w) = edge;
        if (ds.unionSets(u, v)) {
            result.push_back(edge);
            totalWeight += w;
        }
    }
    return {totalWeight, result};
}

#endif // KRUSKAL_HPP
