#include "Bliss.h"


void GraphB::addEdge(int source, int destination) {
    if (source >= 0 && source < numNodes && destination >= 0 && destination < numNodes) {
        adjacencyMatrix[source][destination] = 1;
        adjacencyMatrix[destination][source] = 1;
    }
}

void GraphB::printGraphB() const {
    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool BlissAlgorithm::isIsomorphic() {

    std::vector<int> permutation(numNodes);
    for (int i = 0; i < numNodes; ++i) {
        permutation[i] = i;
    }

    return isIsomorphicUtil(permutation, 0);
}

bool BlissAlgorithm::isIsomorphicUtil(std::vector<int>& permutation, int index) {
    if (index == numNodes) {
        std::vector<std::vector<int>> permutedAdjMatrix(numNodes, std::vector<int>(numNodes, 0));

        for (int i = 0; i < numNodes; ++i) {
            for (int j = 0; j < numNodes; ++j) {
                permutedAdjMatrix[i][j] = adjMatrix1[permutation[i]][permutation[j]];
            }
        }

        if (isEqual(adjMatrix2, permutedAdjMatrix)) {
            for (int i = 0; i < numNodes; ++i) {
                vertexMapping[i] = permutation[i];
            }
            return true;
        }

        return false;
    }

    for (int i = index; i < numNodes; ++i) {
        std::swap(permutation[i], permutation[index]);
        if (isIsomorphicUtil(permutation, index + 1))
            return true;
        std::swap(permutation[i], permutation[index]);
    }

    return false;
}

bool BlissAlgorithm::isEqual(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2) const {
    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            if (matrix1[i][j] != matrix2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void BlissAlgorithm::printMapping() const {
    for (const auto& mapping : vertexMapping) {
        std::cout << mapping.first << " -> " << mapping.second << "\n";
    }
}

GraphB generateRandomGraph(int numVertices, int numEdges) {
    std::vector<int> nodes(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        nodes[i] = i;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(nodes.begin(), nodes.end(), gen);

    GraphB graph(numVertices);

    int edgesAdded = 0;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            if (edgesAdded == numEdges)
                break;
            graph.addEdge(nodes[i], nodes[j]);
            edgesAdded++;
        }
    }

    return graph;
}

void Bliss() {
    std::cout << "Choose one option:\n";
    std::cout << "1. Generate a random graphs;\n";
    std::cout << "2. Show exaple of isomorphic graphs;\n";
    std::cout << "3. Show exaple of not isomorphic graphs.\n";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        // Generate random graphs
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> numVerticesDistribution(5, 10);
        std::uniform_int_distribution<> numEdgesDistribution(5, 20);

        int numVertices1 = numVerticesDistribution(gen);
        int numEdges1 = numEdgesDistribution(gen);
        GraphB graph1 = generateRandomGraph(numVertices1, numEdges1);

        int numVertices2 = numVerticesDistribution(gen);
        int numEdges2 = numEdgesDistribution(gen);
        GraphB graph2 = generateRandomGraph(numVertices2, numEdges2);

        // Print the generated graphs
        std::cout << "Graph 1:" << std::endl;
        graph1.printGraphB();

        std::cout << "Graph 2:" << std::endl;
        graph2.printGraphB();

        if (graph1.getNumNodes() != graph2.getNumNodes())
        {
            std::cout << "Graph are not isomorphic\n";
            exit(0);
        }

        // Run the Bliss algorithm and check if graphs are isomorphic
        BlissAlgorithm blissAlgorithm(graph1, graph2);
        bool isIsomorphic = blissAlgorithm.isIsomorphic();

        if (isIsomorphic == true)
        {
            std::cout << "Graphs are isomorphic\n";
            std::cout << std::endl << "Vertex Mapping:\n";
            blissAlgorithm.printMapping();
        }
        else
        {
            std::cout << "Graphs are not isomorphic\n";
        }
    }
    if (choice == 2) {
        GraphB g1(4);
        g1.addEdge(0, 1);
        g1.addEdge(0, 2);
        g1.addEdge(0, 3);
        g1.addEdge(1, 2);

        GraphB g2(4);
        g2.addEdge(3, 2);
        g2.addEdge(3, 1);
        g2.addEdge(3, 0);
        g2.addEdge(2, 1);

        // Print the generated graphs
        std::cout << "Graph 1:" << std::endl;
        g1.printGraphB();

        std::cout << "Graph 2:" << std::endl;
        g2.printGraphB();

        // Run the Bliss algorithm and check if graphs are isomorphic
        BlissAlgorithm blissAlgorithm(g1, g2);
        bool isIsomorphic = blissAlgorithm.isIsomorphic();

        if (isIsomorphic == true)
        {
            std::cout << "Graphs are isomorphic\n";
            std::cout << std::endl << "Vertex Mapping:\n";
            blissAlgorithm.printMapping();
        }
        else
        {
            std::cout << "Graphs are not isomorphic\n";
        }
    }
    if (choice == 3)
    {
        GraphB g1(4);
        g1.addEdge(0, 1);
        g1.addEdge(1, 2);
        g1.addEdge(2, 3);
        g1.addEdge(3, 0);

        GraphB g2(4);
        g2.addEdge(0, 1);
        g2.addEdge(0, 2);
        g2.addEdge(0, 3);

        // Print the generated graphs
        std::cout << "Graph 1:" << std::endl;
        g1.printGraphB();

        std::cout << "Graph 2:" << std::endl;
        g2.printGraphB();

        // Run the Bliss algorithm and check if graphs are isomorphic
        BlissAlgorithm blissAlgorithm(g1, g2);
        bool isIsomorphic = blissAlgorithm.isIsomorphic();

        if (isIsomorphic == true)
        {
            std::cout << "Graphs are isomorphic\n";
            std::cout << std::endl << "Vertex Mapping:\n";
            blissAlgorithm.printMapping();
        }
        else
        {
            std::cout << "Graphs are not isomorphic\n";
        }
    }
}