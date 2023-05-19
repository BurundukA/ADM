#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <numeric>
#include <random>

class GraphN {
private:
    int numVertices;
    std::vector<std::vector<int>> adjacencyMatrix;

public:
    GraphN(int vertices) : numVertices(vertices), adjacencyMatrix(vertices, std::vector<int>(vertices, 0)) {};

    void addEdge(int u, int v);

    std::vector<std::vector<int>> returnadjacencyMatrix()
    {
        return adjacencyMatrix;
    }

    bool isIsomorphic(const GraphN& other) const;

    void printGraph() const;

private:
    bool isMappingValid(const std::vector<int>& perm, const GraphN& other) const;

    bool isValidMappingForVertex(int v1, int v2, const GraphN& other, const std::unordered_map<int, int>& vertexMapping) const;

    bool isIsomorphicUtil(const GraphN& other, std::vector<int>& perm, int level) const;

    void printVertexMappings(const std::vector<int>& perm) const;
};

static GraphN generateRandomGraphN();

void Nauty();