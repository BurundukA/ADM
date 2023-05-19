#include "Weisfeiler_Lehmann.h"


int GraphW::getV() const {
    return V;
}

void GraphW::addEdge(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

bool GraphW::isIsomorphic(const GraphW& other) const {
    if (V != other.V)
        return false;

    std::unordered_map<int, int> mapping;

    return isIsomorphicUtil(other, mapping, 0);
}

void GraphW::printGraph() const {
    for (int i = 0; i < V; i++) {
        std::cout << "Vertex " << i << ": ";
        for (int j = 0; j < adjList[i].size(); j++) {
            std::cout << adjList[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void GraphW::printVertexMatching(const std::unordered_map<int, int>& mapping) const {
    std::cout << "Vertex Matching:\n ";
    for (const auto& pair : mapping) {
        std::cout << pair.first << " -> " << pair.second << "\n";
    }
}

//check isomorphic of each level
bool GraphW::isIsomorphicUtil(const GraphW& other, std::unordered_map<int, int>& mapping, int level) const {
    if (level == V)
        return true;

    for (int i = 0; i < V; i++) {
        if (isMappingValid(mapping, level, i, other)) {
            mapping[level] = i;
            if (isIsomorphicUtil(other, mapping, level + 1))
                return true;
            mapping.erase(level);
        }
    }

    return false;
}

//Comparasing edges and verteces
bool GraphW::isMappingValid(const std::unordered_map<int, int>& mapping, int v, int u, const GraphW& other) const {
    if (adjList[v].size() != other.adjList[u].size())
        return false;

    std::unordered_map<int, int> reverseMapping;
    for (const auto& pair : mapping) {
        reverseMapping[pair.second] = pair.first;
    }

    for (int i = 0; i < adjList[v].size(); i++) {
        int neighbor = adjList[v][i];
        int mappedNeighbor = reverseMapping.count(neighbor) > 0 ? reverseMapping[neighbor] : -1;

        if (mappedNeighbor != -1 && other.adjList[u][i] != mappedNeighbor)
            return false;
    }

    return true;
}

GraphW generateRandomGraph() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> verticesDist(3, 10);
    std::uniform_int_distribution<int> edgesDist(2, 10);

    int vertices = verticesDist(gen);
    int edges = edgesDist(gen);

    GraphW g(vertices);

    std::uniform_int_distribution<int> vertexDist(0, vertices - 1);

    while (edges > 0) {
        int u = vertexDist(gen);
        int v = vertexDist(gen);

        if (u != v) {
            g.addEdge(u, v);
            edges--;
        }
    }

    return g;
}

void Weisfeiler_Lehmann()
{
    std::cout << "Choose one option:\n";
    std::cout << "1. Generate a random graphs;\n";
    std::cout << "2. Show exaple of isomorphic graphs;\n";
    std::cout << "3. Show exaple of not isomorphic graphs.\n";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        GraphW g1 = generateRandomGraph();
        GraphW g2 = generateRandomGraph();

        std::cout << "Graph 1:\n";
        g1.printGraph();
        std::cout << std::endl;

        std::cout << "Graph 2\n:";
        g2.printGraph();
        std::cout << "\n";

        if (g1.isIsomorphic(g2)) {
            std::cout << "Graphs are isomorphic.\n";
            std::unordered_map<int, int> matching;
            for (int i = 0; i < g1.getV(); i++) {
                matching[i] = i;
            }

            g1.printVertexMatching(matching);
        }
        else {
            std::cout << "Graphs are not isomorphic.\n";
        }
    }

    if (choice == 2) {
        GraphW g1(4);
        g1.addEdge(0, 1);
        g1.addEdge(0, 2);
        g1.addEdge(0, 3);
        g1.addEdge(1, 2);

        GraphW g2(4);
        g2.addEdge(3, 2);
        g2.addEdge(3, 1);
        g2.addEdge(3, 0);
        g2.addEdge(2, 1);

        std::cout << "Graph 1:\n";
        g1.printGraph();
        std::cout << std::endl;

        std::cout << "Graph 2:\n" << std::endl;
        g2.printGraph();
        std::cout << std::endl;

        if (g1.isIsomorphic(g2)) {
            std::cout << "Graphs are isomorphic.\n";

            std::unordered_map<int, int> mapping;
            for (int i = 0; i < g1.getV(); i++) {
                mapping[i] = g2.getV() - 1 - i;
            }

            g1.printVertexMatching(mapping);
        }
        else {
            std::cout << "Graphs are not isomorphic.\n";
        }
    }
    if (choice == 3)
    {
        GraphW g1(4);
        g1.addEdge(0, 1);
        g1.addEdge(1, 2);
        g1.addEdge(2, 3);
        g1.addEdge(3, 0);

        GraphW g2(4);
        g2.addEdge(0, 1);
        g2.addEdge(0, 2);
        g2.addEdge(0, 3);

        std::cout << "Graph 1:\n";
        g1.printGraph();
        std::cout << "\n";

        std::cout << "Graph 2:\n";
        g2.printGraph();
        std::cout << "\n";

        if (g1.isIsomorphic(g2)) {
            std::cout << "Graphs are isomorphic.\n";

            std::unordered_map<int, int> mapping;
            for (int i = 0; i < g1.getV(); i++) {
                mapping[i] = g2.getV() - 1 - i;
            }

            g1.printVertexMatching(mapping);
        }
        else {
            std::cout << "Graphs are not isomorphic.\n";
        }
    }
}