#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <map>
#include <numeric>

class GraphV {
public:
    int num_vertices;
    std::vector<std::vector<int>> adjacency_list;

    GraphV(int n) : num_vertices(n), adjacency_list(n) {}

    void add_edge(int u, int v);

    void print() const;
};

class VF2Isomorphism {
public:
    bool is_isomorphic;
    std::map<int, int> final_vertex_mapping;

    VF2Isomorphism() : is_isomorphic(false) {};

    void findIsomorphism(const GraphV& graph1, const GraphV& graph2);

private:
    void match(const GraphV& graph1, const GraphV& graph2, std::vector<int>& domain, std::vector<bool>& visited,
        std::vector<int>& in_domain, int depth, std::map<int, int>& vertex_mapping);

    bool is_feasible(const GraphV& graph1, const GraphV& graph2, int u, int v, const std::vector<int>& in_domain);
};

GraphV generate_random_graph(int num_vertices, int num_edges);

void VF2();