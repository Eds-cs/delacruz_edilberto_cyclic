// bfs
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
using namespace std;

// Adjacency list representation of the graph
unordered_map<char, vector<char>> graph;

// BFS function to detect cycle in undirected graph
bool bfs(char start) {
    unordered_map<char, char> parent;    // Store parent of each node
    unordered_set<char> visited;         // Track visited nodes
    queue<char> q;

    // Initialize BFS
    q.push(start);
    visited.insert(start);
    parent[start] = '\0'; // Root has no parent

    // Standard BFS loop
    while (!q.empty()) {
        char node = q.front(); q.pop();

        // Check all neighbors
        for (char neighbor : graph[node]) {
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                parent[neighbor] = node;
                q.push(neighbor);
            } else if (parent[node] != neighbor || node == neighbor) {
                // Found a cycle: either via back-edge or self-loop
                return true;
            }
        }
    }

    return false; // No cycle found
}

int main() {
    // Construct the undirected graph
    graph['A'] = {'C', 'D', 'E'};
    graph['C'] = {'A', 'E', 'G', 'F', 'B'};
    graph['E'] = {'A', 'C'};
    graph['D'] = {'A'};
    graph['G'] = {'C'};
    graph['F'] = {'C', 'B'};
    graph['B'] = {'C', 'F', 'B'}; // Self-loop on B

    unordered_set<char> visited;
    bool isCyclic = false;

    // Check each connected component
    for (auto &[node, _] : graph) {
        if (!visited.count(node)) {
            if (bfs(node)) {
                isCyclic = true;
                break;
            }
        }
    }

    // Output the result
    cout << "Is cyclic: " << (isCyclic ? "True" : "False") << endl;
    return 0;
}
