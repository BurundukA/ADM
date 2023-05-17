#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class Graph {
private:
    int V;
    std::vector<std::vector<int>> adj;

public:
    Graph(int V);
    void addEdge(int u, int v);
    bool isIsomorphic(const Graph& g);
    void print() const;
private:
    bool contains(const std::vector<int>& vec, int val) const;
};


void Naive_algorythm();