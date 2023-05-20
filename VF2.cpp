#include "VF2.h"

void GraphV::add_edge(int u, int v) {
    adjacency_list[u].push_back(v);
    adjacency_list[v].push_back(u);
}

void GraphV::print() const {
    for (int u = 0; u < num_vertices; ++u) {
        std::cout << "Vertex " << u << ": ";
        for (int v : adjacency_list[u]) {
            std::cout << u << " -- " << v << ", ";
        }
        std::cout << "\n";
    }

    // Visual representation
    std::cout << "Graph Visualization:\n";
    for (int u = 0; u < num_vertices; ++u) {
        std::cout << "Vertex " << u << ": ";
        for (int v = 0; v < num_vertices; ++v) {
            if (std::find(adjacency_list[u].begin(), adjacency_list[u].end(), v) != adjacency_list[u].end()) {
                std::cout << "1 ";
            }
            else {
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }
}

void VF2Isomorphism::findIsomorphism(const GraphV& graph1, const GraphV& graph2) {
    std::vector<int> domain(graph1.num_vertices);
    std::iota(domain.begin(), domain.end(), 0);
    std::vector<bool> visited(graph2.num_vertices, false);
    std::vector<int> in_domain(graph2.num_vertices, -1);
    std::map<int, int> vertex_mapping;

    match(graph1, graph2, domain, visited, in_domain, 0, vertex_mapping);

    if (is_isomorphic) {
        std::cout << "Graphs are isomorphic.\n";
        for (const auto& entry : final_vertex_mapping) {
            std::cout << "Vertex " << entry.first << " in graph 1 corresponds to vertex " << entry.second << " in graph 2.\n";
        }
    }
    else {
        std::cout << "Graphs are not isomorphic.\n";
    }
}

void VF2Isomorphism::match(const GraphV& graph1, const GraphV& graph2, std::vector<int>& domain, std::vector<bool>& visited,
    std::vector<int>& in_domain, int depth, std::map<int, int>& vertex_mapping) {
    if (depth == graph1.num_vertices) {
        is_isomorphic = true;
        final_vertex_mapping = vertex_mapping;
        return;
    }

    int u = domain[depth];
    for (int v = 0; v < graph2.num_vertices; ++v) {
        if (!visited[v] && is_feasible(graph1, graph2, u, v, in_domain)) {
            visited[v] = true;
            in_domain[u] = v;
            vertex_mapping[u] = v;

            match(graph1, graph2, domain, visited, in_domain, depth + 1, vertex_mapping);

            visited[v] = false;
            in_domain[u] = -1;
            vertex_mapping.erase(u);

            if (is_isomorphic)
                return;
        }
    }
}

bool VF2Isomorphism::is_feasible(const GraphV& graph1, const GraphV& graph2, int u, int v, const std::vector<int>& in_domain) {
    if (graph1.adjacency_list[u].size() != graph2.adjacency_list[v].size())
        return false;

    for (int neighbor : graph1.adjacency_list[u]) {
        int mapped_neighbor = in_domain[neighbor];
        if (mapped_neighbor != -1 && std::find(graph2.adjacency_list[v].begin(), graph2.adjacency_list[v].end(),
            mapped_neighbor) == graph2.adjacency_list[v].end())
            return false;
    }

    return true;
}

GraphV generate_random_graph(int num_vertices, int num_edges) {
    GraphV graph(num_vertices);

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(0, num_vertices - 1);

    int generated_edges = 0;
    while (generated_edges < num_edges) {
        int u = uni(rng);
        int v = uni(rng);
        if (u != v &&
            std::find(graph.adjacency_list[u].begin(), graph.adjacency_list[u].end(), v) == graph.adjacency_list[u].end()) {
            graph.add_edge(u, v);
            generated_edges++;
        }
    }

    return graph;
}

void VF2() {
    std::cout << "Choose one option:\n";
    std::cout << "1. Generate a random graphs;\n";
    std::cout << "2. Show exaple of isomorphic graphs;\n";
    std::cout << "3. Show exaple of not isomorphic graphs.\n";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> uni(4, 8);

        // Generate random graphs
        int num_vertices1 = uni(rng);
        int num_edges1 = uni(rng);
        GraphV graph1 = generate_random_graph(num_vertices1, num_edges1);

        int num_vertices2 = uni(rng);
        int num_edges2 = uni(rng);
        GraphV graph2 = generate_random_graph(num_vertices2, num_edges2);

        // Print the generated graphs
        std::cout << "Graph 1:\n";
        graph1.print();

        std::cout << "Graph 2:\n";
        graph2.print();

        VF2Isomorphism vf2;
        vf2.findIsomorphism(graph1, graph2);
    }
    if (choice == 2) {

        GraphV g1(4);
        g1.add_edge(0, 1);
        g1.add_edge(0, 2);
        g1.add_edge(0, 3);
        g1.add_edge(1, 2);

        GraphV g2(4);
        g2.add_edge(3, 2);
        g2.add_edge(3, 1);
        g2.add_edge(3, 0);
        g2.add_edge(2, 1);
        // Print the generated graphs
        std::cout << "Graph 1:\n";
        g1.print();

        std::cout << "Graph 2:\n";
        g2.print();

        VF2Isomorphism vf2;
        vf2.findIsomorphism(g1, g2);
    }
    if (choice == 3)
    {
        GraphV g1(4);
        g1.add_edge(0, 1);
        g1.add_edge(1, 2);
        g1.add_edge(2, 3);
        g1.add_edge(3, 0);

        GraphV g2(4);
        g2.add_edge(0, 1);
        g2.add_edge(0, 2);
        g2.add_edge(0, 3);

        // Print the generated graphs
        std::cout << "Graph 1:\n";
        g1.print();

        std::cout << "Graph 2:\n";
        g2.print();

        VF2Isomorphism vf2;
        vf2.findIsomorphism(g1, g2);
    }
}