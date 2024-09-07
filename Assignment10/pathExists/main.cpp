#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        if (source == destination) return true;

        std::vector<std::vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        stack<int> toVisit;
        unordered_map<int, bool> visited;
        visited[source] = true;
        toVisit.push(source);
        
        while(!toVisit.empty()){
    		int currentVertex = toVisit.top();
    		toVisit.pop();
    		vector<int> adjV = graph.at(currentVertex);
    		
    		if(currentVertex == destination) return true;
    		
    		for(auto& v : adjV){
                if (!visited[v]){
                	visited[v] = true;
                	toVisit.push(v);
                }
    		}
	    }
	    return false;
    }
};

void testValidPath(Solution& sol, int n, vector<vector<int>>& edges, int source, int destination, bool expected) {
    bool result = sol.validPath(n, edges, source, destination);
    cout << "Test " << (result == expected ? "PASSED" : "FAILED") << " | Expected: " << expected << " | Got: " << result << endl;
}

int main() {
    Solution sol;

    // Edge case 1: Single node, path to itself
    vector<vector<int>> edges1 = {};
    testValidPath(sol, 1, edges1, 0, 0, true);

    // Edge case 2: Two nodes with no edge
    vector<vector<int>> edges2 = {};
    testValidPath(sol, 2, edges2, 0, 1, false);

    // Edge case 3: Two nodes with an edge
    vector<vector<int>> edges3 = {{0, 1}};
    testValidPath(sol, 2, edges3, 0, 1, true);

    // Edge case 4: Larger graph with multiple paths
    vector<vector<int>> edges4 = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
    testValidPath(sol, 5, edges4, 0, 4, true);

    // Edge case 5: Disconnected graph
    vector<vector<int>> edges5 = {{0, 1}, {2, 3}};
    testValidPath(sol, 4, edges5, 0, 3, false);

    // Edge case 6: Larger connected graph
    vector<vector<int>> edges6 = {{0, 1}, {0, 2}, {2, 3}, {3, 4}, {4, 5}};
    testValidPath(sol, 6, edges6, 0, 5, true);
    
    return 0;
}