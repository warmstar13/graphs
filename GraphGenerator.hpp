#ifndef GRAPH_GENERATOR_HPP
#define GRAPH_GENERATOR_HPP

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------------------------------------
// Graph Generator Description:
// 1. The minimum and maximum number of vertices.
// 2. Whether the graph is a tree (true/false).
// 3. Whether the graph is directed (true/false).
// 4. Whether the graph is connected (true/false). For directed graphs, one of the following is required:
//    weak, semi, or strong connectivity.
// 5. The minimum and maximum edge weights (0,0 indicates no weights).
// 6. The minimum and maximum number of edges.
// -----------------------------------------------------------------------------

// Structure describing the graph
struct Graph {
    int vertexCount;                     // Number of vertices
    int edgeCount;                       // Number of edges
    bool isDirected;
    vector<tuple<int, int, int>> edges;  // Edges in the format (from, to, weight)

    void print(bool weighted) const {
        cout << "Number of vertices: " << vertexCount << "\n";
        cout << "Number of edges: " << edgeCount << "\n";
        for (const auto& edge : edges) {
            int u = get<0>(edge);
            int v = get<1>(edge);
            int w = get<2>(edge);
            if (weighted)
                cout << u << " -> " << v << " [weight: " << w << "]\n";
            else
                cout << u << " -> " << v << "\n";
        }
    }
};

// Structure with input parameters for graph generation
struct GraphInputs {
    int minVertexCount, maxVertexCount;
    bool isTree;
    bool isDirected;
    bool isConnected;
    bool isWeaklyConnected;
    bool isSemiConnected;
    bool isStronglyConnected;
    int minEdgeWeight, maxEdgeWeight;
    int minEdgeCount, maxEdgeCount;
};

// -----------------------------------------------------------------------------
// GraphGenerator class that encapsulates the graph generation logic.
// -----------------------------------------------------------------------------
class GraphGenerator {
public:
    explicit GraphGenerator(const GraphInputs& inputs)
        : inputs_(inputs),
          gen_(chrono::system_clock::now().time_since_epoch().count())
    {
        // Initialize the number of vertices and edges
        vertexCount_ = randomInt(inputs_.minVertexCount, inputs_.maxVertexCount);
        if (inputs_.isTree)
            edgeCount_ = vertexCount_ - 1;
        else
            edgeCount_ = randomInt(inputs_.minEdgeCount, inputs_.maxEdgeCount);

        minWeight_ = inputs_.minEdgeWeight;
        maxWeight_ = inputs_.maxEdgeWeight;
        isDirected_ = inputs_.isDirected;
    }

    // Generates a graph based on the input parameters
    Graph generate() {
        int maxPossibleEdges = inputs_.isDirected ?
            vertexCount_ * (vertexCount_ - 1) : (vertexCount_ * (vertexCount_ - 1)) / 2;
        if (edgeCount_ > maxPossibleEdges) {
            throw runtime_error("Too many edges requested!");
        }

        // Build the basic connectivity structure (tree or connected graph)
        if (inputs_.isTree || inputs_.isConnected) {
            buildBasicConnectivity();
        }

        // Add additional edges until the required number is reached
        addRemainingEdges();

        return Graph{vertexCount_, edgeCount_, isDirected_, edges_};
    }

private:
    GraphInputs inputs_;
    int vertexCount_;
    int edgeCount_;
    bool isDirected_;
    int minWeight_;
    int maxWeight_;

    vector<tuple<int, int, int>> edges_;
    set<pair<int, int>> edgeSet_; // To ensure edge uniqueness

    mt19937 gen_;

    // Returns a random integer in the range [low, high]
    int randomInt(int low, int high) {
        uniform_int_distribution<int> dis(low, high);
        return dis(gen_);
    }

    // Returns a vector of numbers from 1 to count, randomly shuffled
    vector<int> generateShuffledVertices(int count) {
        vector<int> vertices(count);
        iota(vertices.begin(), vertices.end(), 1);
        shuffle(vertices.begin(), vertices.end(), gen_);
        return vertices;
    }

    // Methods for creating various connectivity types for directed graphs

    // Creates weak connectivity by generating a spanning tree with arbitrary edge directions.
    void makeWeakConnectivity() {
        vector<int> vertices = generateShuffledVertices(vertexCount_);
        // For each vertex, starting from the second, select a random connection from the already processed vertices.
        for (int i = 2; i <= vertexCount_; i++) {
            int u = vertices[randomInt(0, i - 2)];
            int weight = randomInt(minWeight_, maxWeight_);
            if (randomInt(0, 1) == 0) {
                edges_.emplace_back(u, vertices[i - 1], weight);
                edgeSet_.insert({u, vertices[i - 1]});
            } else {
                edges_.emplace_back(vertices[i - 1], u, weight);
                edgeSet_.insert({vertices[i - 1], u});
            }
        }
    }

    // Creates a semi-connected graph by generating a Hamiltonian path.
    void makeSemiConnectivity() {
        vector<int> vertices = generateShuffledVertices(vertexCount_);
        // Generate a Hamiltonian path by connecting consecutive vertices.
        for (int i = 1; i < vertexCount_; i++) {
            int weight = randomInt(minWeight_, maxWeight_);
            edges_.emplace_back(vertices[i - 1], vertices[i], weight);
            edgeSet_.insert({vertices[i - 1], vertices[i]});
        }
    }

    // Creates a strongly connected graph: a Hamiltonian path plus an edge that closes the cycle.
    void makeStrongConnectivity() {
        vector<int> vertices = generateShuffledVertices(vertexCount_);
        // Generate a Hamiltonian path
        for (int i = 1; i < vertexCount_; i++) {
            int weight = randomInt(minWeight_, maxWeight_);
            edges_.emplace_back(vertices[i - 1], vertices[i], weight);
            edgeSet_.insert({vertices[i - 1], vertices[i]});
        }
        // Add an edge to close the cycle (last vertex -> first vertex)
        int weight = randomInt(minWeight_, maxWeight_);
        edges_.emplace_back(vertices[vertexCount_ - 1], vertices[0], weight);
        edgeSet_.insert({vertices[vertexCount_ - 1], vertices[0]});
    }

    // Builds the basic connectivity structure of the graph.
    void buildBasicConnectivity() {
        if (!inputs_.isDirected) {
            // For undirected graphs: build a spanning tree.
            for (int i = 2; i <= vertexCount_; i++) {
                int u = randomInt(1, i - 1);
                int weight = randomInt(minWeight_, maxWeight_);
                edges_.emplace_back(u, i, weight);
                edgeSet_.insert({u, i});
                edgeSet_.insert({i, u});
            }
        } else if (inputs_.isTree) {
            // For a directed tree.
            for (int i = 2; i <= vertexCount_; i++) {
                int u = randomInt(1, i - 1);
                int weight = randomInt(minWeight_, maxWeight_);
                edges_.emplace_back(u, i, weight);
                edgeSet_.insert({u, i});
            }
        } else if (inputs_.isStronglyConnected) {
            makeStrongConnectivity();
        } else if (inputs_.isSemiConnected) {
            makeSemiConnectivity();
        } else if (inputs_.isWeaklyConnected) {
            makeWeakConnectivity();
        }
    }

    // Adds random edges until the total number of edges reaches the required count.
    void addRemainingEdges() {
        while (static_cast<int>(edges_.size()) < edgeCount_) {
            int u = randomInt(1, vertexCount_);
            int v = randomInt(1, vertexCount_);
            if (u == v || edgeSet_.count({u, v}))
                continue;

            int weight = randomInt(minWeight_, maxWeight_);
            edges_.emplace_back(u, v, weight);
            edgeSet_.insert({u, v});
            if (!inputs_.isDirected)
                edgeSet_.insert({v, u});
        }
    }
};

#endif // GRAPH_GENERATOR_HPP
