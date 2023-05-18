#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>

class GraphW {
private:
    int V;
    std::vector<std::vector<int>> adjList;

public:
    GraphW(int vertices) : V(vertices), adjList(vertices) {}

    int getV() const;

    void addEdge(int u, int v);

    bool isIsomorphic(const GraphW& other) const;

    void printGraph() const;

    void printVertexMatching(const std::unordered_map<int, int>& mapping) const;


private:
    bool isIsomorphicUtil(const GraphW& other, std::unordered_map<int, int>& mapping, int level) const;

    bool isMappingValid(const std::unordered_map<int, int>& mapping, int v, int u, const GraphW& other) const;
};

GraphW generateRandomGraph();

void Weisfeiler_Lehmann();