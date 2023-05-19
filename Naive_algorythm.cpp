#include "Naive_algorythm.h"

// Graph class
Graph::Graph(int V) {
    this->V = V;
    adj.resize(V, std::vector<int>());
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

bool Graph::isIsomorphic(const Graph& g) {
    // Check if the number of vertices is the same
    if (V != g.V) {
        return false;
    }

    // Check if the number of edges is the same
    int E = 0, gE = 0;
    for (int u = 0; u < V; u++) {
        E += adj[u].size();
        gE += g.adj[u].size();
    }
    if (E != gE) {
        return false;
    }

    // Try all possible vertex mappings
    std::vector<int> perm(V);
    for (int i = 0; i < V; i++) {
        perm[i] = i;
    }
    do {
        bool match = true;
        for (int u = 0; u < V && match; u++) {
            for (int v : adj[u]) {
                if (g.adj[perm[u]].empty() || !contains(g.adj[perm[u]], perm[v])) {
                    match = false;
                    break;
                }
            }
        }
        if (match) {
            for (int i = 0; i < V; i++) {
                std::cout << "Vertex " << i << " in Graph 1 is matched with Vertex " << perm[i] << " in Graph 2.\n";
            }
            return true;
        }
    } while (next_permutation(perm.begin(), perm.end()));

    return false;
}

void Graph::print() const {
    for (int u = 0; u < V; u++) {
        std::cout << u << ": ";
        for (int v : adj[u]) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }
}

bool Graph::contains(const std::vector<int>& vec, int val) const {
    for (int x : vec) {
        if (x == val) {
            return true;
        }
    }
    return false;
}

// Generate a random graph with n vertices
Graph generateRandomGraph(int n) {
    Graph g(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rand() % 2 == 0) {
                g.addEdge(i, j);
            }
        }
    }
    return g;
}

void Naive_algorythm()
{
    std::cout << "Choose one option:\n";
    std::cout << "1. Generate a random graphs;\n";
    std::cout << "2. Show exaple of isomorphic graphs;\n";
    std::cout << "3. Show exaple of not isomorphic graphs.\n";
    int choice;
    std::cin >> choice;
    if (choice == 1)
    {
        // Generate two random graphs
        int n1 = 6 + rand() % 5; // generate size between 6 and 10
        int n2 = 6 + rand() % 5; // generate size between 6 and 10
        Graph g1 = generateRandomGraph(n1);
        Graph g2 = generateRandomGraph(n2);

        // Print the initial graphs
        std::cout << "Graph 1:\n";
        g1.print();
        std::cout << "\n";

        std::cout << "Graph 2:\n";
        g2.print();
        std::cout << "\n";

        // Check if the graphs are isomorphic
        if (g1.isIsomorphic(g2)) {
            std::cout << "Graphs are isomorphic.\n";
        }
        else {
            std::cout << "Graphs are not isomorphic.\n";
        }
    }
    if (choice == 2)
    {
        // Example of isomorphic graphs
        Graph g1(4);
        g1.addEdge(0, 1);
        g1.addEdge(0, 2);
        g1.addEdge(0, 3);
        g1.addEdge(1, 2);

        Graph g2(4);
        g2.addEdge(3, 2);
        g2.addEdge(3, 1);
        g2.addEdge(3, 0);
        g2.addEdge(2, 1);

        // Print the initial graphs
        std::cout << "Graph 1:\n";
        g1.print();
        std::cout << "\n";

        std::cout << "Graph 2:\n";
        g2.print();
        std::cout << "\n";

        // Check if the graphs are isomorphic
        if (g1.isIsomorphic(g2)) {
            std::cout << "Graphs are isomorphic.\n";
        }
        else {
            std::cout << "Graphs are not isomorphic.\n";
        }
    }
    if (choice == 3)
    {
        // Example of non-isomorphic graphs
        Graph g1(4);
        g1.addEdge(0, 1);
        g1.addEdge(1, 2);
        g1.addEdge(2, 3);
        g1.addEdge(3, 0);

        Graph g2(4);
        g2.addEdge(0, 1);
        g2.addEdge(0, 2);
        g2.addEdge(0, 3);

        // Print the initial graphs
        std::cout << "Graph 1:\n";
        g1.print();
        std::cout << "\n";

        std::cout << "Graph 2:\n";
        g2.print();
        std::cout << "\n";

        // Check if the graphs are isomorphic
        if (g1.isIsomorphic(g2)) {
            std::cout << "Graphs are isomorphic.\n";
        }
        else {
            std::cout << "Graphs are not isomorphic.\n";
        }

    }
}