#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <random>


class GraphB {
private:
    int numNodes;
    std::vector<std::vector<int>> adjacencyMatrix;

public:
    GraphB(int nodes) : numNodes(nodes), adjacencyMatrix(nodes, std::vector<int>(nodes, 0)) {};

    void addEdge(int source, int destination);

    void printGraphB() const;

    int getNumNodes() const {
        return numNodes;
    }

    const std::vector<int>& getNeighbors(int node) const {
        return adjacencyMatrix[node];
    }
};

class BlissAlgorithm {
private:
    std::vector<std::vector<int>> adjMatrix1;
    std::vector<std::vector<int>> adjMatrix2;
    std::unordered_map<int, int> vertexMapping;
    int numNodes;

public:
    BlissAlgorithm(const GraphB& graph1, const GraphB& graph2) : adjMatrix1(graph1.getNumNodes(), std::vector<int>(graph1.getNumNodes(), 0)),
        adjMatrix2(graph2.getNumNodes(), std::vector<int>(graph2.getNumNodes(), 0)),
        numNodes(graph1.getNumNodes()) {
        for (int i = 0; i < numNodes; ++i) {
            for (int j = 0; j < numNodes; ++j) {
                adjMatrix1[i][j] = graph1.getNeighbors(i)[j];
                adjMatrix2[i][j] = graph2.getNeighbors(i)[j];
            }
        }
    }

    bool isIsomorphic();

    bool isIsomorphicUtil(std::vector<int>& permutation, int index);

    bool isEqual(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2) const;

    void printMapping() const;
};

GraphB generateRandomGraph(int numVertices, int numEdges);

void Bliss();