#include <bits/stdc++.h>
#include "GraphGenerator.hpp"
#include "BellmanFordAlgorithm.hpp"
#include "DijkstraAlgorithm.hpp"
#include "KruskalAlgorithm.hpp"
#include "PrimAlgorithm.hpp"
#include "FordFulkerson.hpp"
#include "DinicAlgorithm.hpp"

using namespace std;

void activateBellmanFord(Graph& graph, int starting_point) {
    // Run the Bellman-Ford algorithm from a given starting vertex.
    vector<int> distances = bellmanFord(graph, starting_point);

    cout << "\nBellman-Ford distances from vertex " << starting_point << ":\n";
    for (int i = 1; i <= graph.vertexCount; i++) {
        cout << "Vertex " << i << ": " << distances[i] << "\n";
    }
}

void activateDijkstra(Graph& graph, int starting_point) {
    vector<int> distances = dijkstra(graph, starting_point);

    cout << "\nDijkstra distances from vertex " << starting_point << ":\n";
    for (int i = 1; i <= graph.vertexCount; i++) {
        cout << "Vertex " << i << ": " << distances[i] << "\n";
    }
}


void activateKruskal(Graph& graph) {
    auto result = kruskal(graph);
    int totalWeight = result.first;
    vector<tuple<int, int, int>> mstEdges = result.second;

    cout << "\nKruskal's MST total weight: " << totalWeight << "\n";
    cout << "Edges in MST:\n";
    for (int i = 1; i <= mstEdges.size(); i++) {
        cout << get<0>(mstEdges[i-1]) << " - " << get<1>(mstEdges[i-1]) << "[weight: " << get<2>(mstEdges[i-1]) << "]\n";
    }
}

void activatePrim(Graph& graph) {
    auto result = prim(graph);
    int totalWeight = result.first;
    vector<tuple<int, int, int>> mstEdges = result.second;

    cout << "\nPrim's MST total weight: " << totalWeight << "\n";
    cout << "Edges in MST:\n";
    for (int i = 1; i <= mstEdges.size(); i++) {
        cout << get<0>(mstEdges[i-1]) << " - " << get<1>(mstEdges[i-1]) << "[weight: " << get<2>(mstEdges[i-1]) << "]\n";
    }
}

void activateFordFulkerson(Graph& graph, int source, int sink) {
    auto network = buildFlowNetwork(graph);
    int maxFlow = edmondsKarp(network, source, sink);
    cout << "\n(Edmonds Karp) Maximum flow from vertex " << source << " to vertex " << sink << " is: " << maxFlow << "\n";
}

void activateDinic(Graph& graph, int source, int sink) {
    auto network = buildFlowNetwork(graph);
    Dinic dinic(network);
    int maxFlow = dinic.maxFlow(source, sink);
    cout << "\n(Dinic) Maximum flow from vertex " << source << " to vertex " << sink << " is: " << maxFlow << "\n";
}

int main() {
    // Define graph generation parameters.
    GraphInputs inputs = {
        5,    // minVertexCount
        8,    // maxVertexCount
        false, // isTree
        false, // isDirected
        true, // isConnected
        false,// isWeaklyConnected
        false,// isSemiConnected
        true, // isStronglyConnected
        0,  // minEdgeWeight (allows negative weights)
        10,   // maxEdgeWeight
        5,    // minEdgeCount
        15     // maxEdgeCount
    };

    try {
        // Generate the graph using GraphGenerator.
        GraphGenerator generator(inputs);
        Graph graph = generator.generate();

        cout << "Generated Graph:\n";
        bool weighted = (inputs.minEdgeWeight != 0 || inputs.maxEdgeWeight != 0);
        graph.print(weighted);

        int starting_point = 1;
        activateBellmanFord(graph, starting_point);
        activateDijkstra(graph, starting_point);
        activateKruskal(graph);
        activatePrim(graph);
        int source = 1;
        int sink = graph.vertexCount;
        activateFordFulkerson(graph, source, sink);
        activateDinic(graph, source, sink);
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
