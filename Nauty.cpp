#include "Nauty.h"

void GraphN::addEdge(int u, int v) {
    adjacencyMatrix[u][v] = 1;
    adjacencyMatrix[v][u] = 1;
}

bool GraphN::isIsomorphic(const GraphN& other) const {
    if (numVertices != other.numVertices)
        return false;

    std::vector<int> perm(numVertices);
    std::iota(perm.begin(), perm.end(), 0);  // Initialize permutation

    do {
        if (isMappingValid(perm, other)) {
            if (isIsomorphicUtil(other, perm, 0)) {
                printVertexMappings(perm);
                return true;
            }
        }
    } while (std::next_permutation(perm.begin(), perm.end()));

    return false;
}

void GraphN::printGraph() const {
    std::cout << "Adjacency Matrix:\n";
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

bool GraphN::isMappingValid(const std::vector<int>& perm, const GraphN& other) const {
    std::unordered_map<int, int> vertexMapping;

    for (int v1 = 0; v1 < numVertices; v1++) {
        int v2 = perm[v1];
        vertexMapping[v1] = v2;
    }

    for (int v1 = 0; v1 < numVertices; v1++) {
        int v2 = perm[v1];
        if (!isValidMappingForVertex(v1, v2, other, vertexMapping))
            return false;
    }

    return true;
}

bool GraphN::isValidMappingForVertex(int v1, int v2, const GraphN& other, const std::unordered_map<int, int>& vertexMapping) const {
    for (int u1 = 0; u1 < numVertices; u1++) {
        if (adjacencyMatrix[v1][u1]) {
            int u2 = vertexMapping.at(u1);
            if (!other.adjacencyMatrix[v2][u2])
                return false;
        }
    }
    return true;
}

bool GraphN::isIsomorphicUtil(const GraphN& other, std::vector<int>& perm, int level) const {
    if (level == numVertices)
        return true;

    int u1 = perm[level];

    for (int i = level; i < numVertices; i++) {
        int v1 = perm[i];

        std::swap(perm[level], perm[i]);  // Swap vertices in permutation

        if (isMappingValid(perm, other)) {
            if (isIsomorphicUtil(other, perm, level + 1))
                return true;
        }

        std::swap(perm[level], perm[i]);  // Revert the swap
    }

    return false;
}

void GraphN::printVertexMappings(const std::vector<int>& perm) const {
    std::cout << "Vertex Mappings:\n";
    for (int i = 0; i < numVertices; i++) {
        std::cout << "Vertex " << i << " maps to " << perm[i] << "\n";
    }
    std::cout << "\n";
}

static GraphN generateRandomGraphN() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> verticesDist(3, 10);
    std::uniform_int_distribution<int> edgesDist(2, 10);

    int vertices = verticesDist(gen);
    int edges = edgesDist(gen);

    GraphN g(vertices);

    std::uniform_int_distribution<int> vertexDist(0, vertices - 1);

    while (edges > 0) {
        int u = vertexDist(gen);
        int v = vertexDist(gen);

        if (u != v && g.returnadjacencyMatrix()[u][v] == 0) {
            g.addEdge(u, v);
            edges--;
        }
    }

    return g;
}

void Nauty() {
    std::cout << "Choose one option:\n";
    std::cout << "1. Generate a random graphs;\n";
    std::cout << "2. Show exaple of isomorphic graphs;\n";
    std::cout << "3. Show exaple of not isomorphic graphs.\n";
    int choice;
    std::cin >> choice;
    if (choice == 1)
    {
        GraphN g1 = generateRandomGraphN();
        GraphN g2 = generateRandomGraphN();

        std::cout << "Graph1:\n";
        g1.printGraph();
        std::cout << "Graph2:\n";
        g2.printGraph();

        if (g1.isIsomorphic(g2)) {
            std::cout << "Graphs are isomorphic.\n";
        }
        else {
            std::cout << "Graphs are not isomorphic.\n";
        }
    }
    if (choice == 2)
    {
        GraphN g1(4);
        g1.addEdge(0, 1);
        g1.addEdge(0, 2);
        g1.addEdge(0, 3);
        g1.addEdge(1, 2);

        GraphN g2(4);
        g2.addEdge(3, 2);
        g2.addEdge(3, 1);
        g2.addEdge(3, 0);
        g2.addEdge(2, 1);

        std::cout << "Graph1:\n";
        g1.printGraph();
        std::cout << "Graph2:\n";
        g2.printGraph();

        if (g1.isIsomorphic(g2)) {
            std::cout << "Graphs are isomorphic.\n";
        }
        else {
            std::cout << "Graphs are not isomorphic.\n";
        }
    }
    if (choice == 3)
    {
        GraphN g1(4);
        g1.addEdge(0, 1);
        g1.addEdge(1, 2);
        g1.addEdge(2, 3);
        g1.addEdge(3, 0);

        GraphN g2(4);
        g2.addEdge(0, 1);
        g2.addEdge(0, 2);
        g2.addEdge(0, 3);

        std::cout << "Graph1:\n";
        g1.printGraph();
        std::cout << "Graph2:\n";
        g2.printGraph();

        if (g1.isIsomorphic(g2)) {
            std::cout << "Graphs are isomorphic.\n";
        }
        else {
            std::cout << "Graphs are not isomorphic.\n";
        }
    }
}