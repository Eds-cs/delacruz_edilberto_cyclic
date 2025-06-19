// dfs
#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
using namespace std;

// Adjacency list to represent the graph
unordered_map<char, vector<char>> graph;

// Set to keep track of visited nodes
unordered_set<char> visited;

// Recursive DFS function to detect cycle
bool dfs(char node, char parent) {
    visited.insert(node); // Mark current node as visited

    // Traverse all adjacent nodes
    for (char neighbor : graph[node]) {
        if (!visited.count(neighbor)) {
            // If neighbor is unvisited, recurse
            if (dfs(neighbor, node)) return true;
        } else if (neighbor != parent || node == neighbor) {
            // Found a back edge or a self-loop, which means a cycle exists
            return true;
        }
    }

    return false; // No cycle found in this path
}

int main() {
    // Manually construct the undirected graph based on the image
    graph['A'] = {'C', 'D', 'E'};
    graph['C'] = {'A', 'E', 'G', 'F', 'B'};
    graph['E'] = {'A', 'C'};
    graph['D'] = {'A'};
    graph['G'] = {'C'};
    graph['F'] = {'C', 'B'};
    graph['B'] = {'C', 'F', 'B'}; // Self-loop on B

    bool isCyclic = false;

    // Check every unvisited node to handle disconnected graphs
    for (auto &[node, _] : graph) {
        if (!visited.count(node)) {
            if (dfs(node, '\0')) {
                isCyclic = true;
                break; // Stop early if cycle found
            }
        }
    }

    // Output the result
    cout << "Is cyclic: " << (isCyclic ? "True" : "False") << endl;
    return 0;
}
