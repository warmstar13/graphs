# Graph Algorithms Project

This project is a comprehensive implementation of various graph algorithms in C++. It includes modules for graph generation, shortest path algorithms, minimum spanning tree (MST) algorithms, and maximum flow algorithms. The project is designed in a modular fashion, with each algorithm implemented in its own header file.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Dependencies](#dependencies)
- [How to Build](#how-to-build)
- [How to Run](#how-to-run)
- [Customization and Usage](#customization-and-usage)
- [Future Improvements](#future-improvements)

## Overview

This project demonstrates key graph algorithms by generating random graphs based on user-defined parameters and then applying several algorithms to solve common graph problems. The implemented algorithms include:

- **Shortest Path Algorithms:**
  - **Bellman–Ford:** Handles graphs with possibly negative edge weights.
  - **Dijkstra:** Efficient for graphs with non-negative weights.
- **Minimum Spanning Tree (MST) Algorithms:**
  - **Kruskal:** Uses union-find (disjoint set) to build the MST.
  - **Prim:** Greedily builds the MST using a priority queue.
- **Maximum Flow Algorithms:**
  - **Ford–Fulkerson (Edmonds–Karp variant):** Finds maximum flow using BFS to locate augmenting paths.
  - **Dinic's Algorithm:** Uses a level graph (BFS) combined with DFS to find blocking flows efficiently.

## Features

- **Graph Generation:** Random graphs can be generated with parameters such as the number of vertices, number of edges, connectivity, and whether the graph is directed or undirected.
- **Modular Design:** Each algorithm is encapsulated in its own module (header file) for clear separation of concerns.
- **Multiple Algorithms:** Compare the results of different algorithms (e.g., shortest path, MST, maximum flow) on the same generated graph.
- **Error Handling:** Runtime errors are caught and reported (e.g., when an algorithm is used on an incompatible graph type).

## Project Structure

- **main.cpp:**  
  The entry point of the project. It generates a random graph using `GraphGenerator` and then activates each algorithm, printing the results to the console.
  
- **GraphGenerator.hpp:**  
  Contains the definitions for the `Graph` structure, `GraphInputs` parameters, and the `GraphGenerator` class which generates random graphs.
  
- **BellmanFordAlgorithm.hpp:**  
  Contains the implementation of the Bellman–Ford algorithm for finding shortest paths.
  
- **DijkstraAlgorithm.hpp:**  
  Contains the implementation of Dijkstra's algorithm for finding shortest paths.
  
- **KruskalAlgorithm.hpp:**  
  Contains the implementation of Kruskal's algorithm for constructing a minimum spanning tree (MST).  
  It also includes the `DisjointSet` class for union-find operations.
  
- **PrimAlgorithm.hpp:**  
  Contains the implementation of Prim's algorithm for constructing an MST.
  
- **FlowEdge.hpp:**  
  Contains the definition of the `FlowEdge` structure and the `FlowNetwork` class used by the maximum flow algorithms.
  
- **FordFulkerson.hpp:**  
  Contains the implementation of the Ford–Fulkerson method (using the Edmonds–Karp variant) for computing maximum flow.
  
- **DinicAlgorithm.hpp:**  
  Contains the implementation of Dinic's algorithm for computing maximum flow.

## Dependencies

- C++11 or higher  
- Standard C++ libraries (e.g., `<iostream>`, `<vector>`, `<queue>`, `<tuple>`, `<algorithm>`, `<stdexcept>`)  
- Note: The project currently uses `<bits/stdc++.h>` for simplicity. For production use, replace it with individual header includes for better portability.

## How to Build

Using **g++** from the command line (assuming all header files and main.cpp are in the same directory):

```bash
g++ main.cpp -o graph_algorithms -std=c++11
```

Alternatively, you can use any modern C++ compiler that supports C++11 or higher.

## How to Run

After building the project, run the executable:

```bash
./graph_algorithms
```

The program will:
1. Generate a random graph based on parameters defined in `main.cpp`.
2. Print the generated graph.
3. Run and display the results of:
   - Bellman–Ford and Dijkstra's shortest path algorithms.
   - Kruskal's and Prim's algorithms for the MST.
   - Ford–Fulkerson (Edmonds–Karp) and Dinic's algorithms for maximum flow.

## Customization and Usage

- **Graph Generation:**  
  Modify the parameters in the `GraphInputs` structure in `main.cpp` to change the characteristics of the generated graph (number of vertices, edge count, connectivity, etc.).

- **Algorithm Activation:**  
  The functions `activateBellmanFord`, `activateDijkstra`, `activateKruskal`, `activatePrim`, `activateFordFulkerson`, and `activateDinic` in `main.cpp` demonstrate how to call each algorithm. You can adjust the starting vertex, source, and sink as required.

- **Extending the Project:**  
  Consider adding new algorithms (e.g., Tarjan's algorithm for strongly connected components, topological sorting, or even graph visualization) to further expand the project.

## Future Improvements

- Replace `<bits/stdc++.h>` with explicit header includes.
- Split implementation code from headers into separate .cpp files for faster compilation in larger projects.
- Add unit tests to validate each algorithm against known graphs.
- Implement additional graph algorithms for a more comprehensive library.
- Improve error handling and input validation.
- Consider adding a graphical interface or visualization module.
