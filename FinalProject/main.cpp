#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <cctype>
#include <algorithm>

using namespace std;

void readFlightData(const string& filename, unordered_map<string, vector<string>>& directed_graph, unordered_map<string, vector<string>>& undirected_graph);
void bfsCheckWeakConnection(unordered_map<string, vector<string>>& graph);
bool isValidAirport(const unordered_map<string, vector<string>>& graph, const string& airport);
void getAirport(const unordered_map<string, vector<string>>& undirected_graph, string& airport);
pair<vector<string>, int> shortestPathAndStops(unordered_map<string, vector<string>>& graph, const string& start, const string& stop);
void printResult(const pair<vector<string>, int>& result);

int main(){
    unordered_map<string, vector<string>> directed_graph;
    unordered_map<string, vector<string>> undirected_graph;
    
    // Milestone 1: Call the function to read flight data and construct graphs
    readFlightData("Airlines.txt", directed_graph, undirected_graph);
    
    // Milestone 2: See if graph is weakly connected using BFS
    bfsCheckWeakConnection(undirected_graph);
    
    // Milestone 3: Collect user inputs and find the shortest path & num of stops
    // User input for departure and destination airports
    string departure, destination;
    
    // Get valid departure airport from user
    cout << "Enter departure airport: ";
    getAirport(undirected_graph, departure);
    
    // Get valid destination airport from user
    cout << "Enter destination airport: ";
    getAirport(undirected_graph, destination);
    
    auto result = shortestPathAndStops(directed_graph, departure, destination);
    
    printResult(result);
    
    return 0;
}

void readFlightData(const string& filename, unordered_map<string, vector<string>>& directed_graph, unordered_map<string, vector<string>>& undirected_graph){
    // Reading file
    ifstream Airlines(filename);
    
    // Checks if file is open
    if(!Airlines.is_open()){
        cout << "File is not opened!" << endl;
        return;
    }
    
    string text;
    vector<vector<string>> edges;
    while(getline(Airlines, text)){
        stringstream ss(text);
        vector<string> data;
        
        string item;
        // Parse the long string into vector
        while(getline(ss, item, ',')) {
            data.push_back(item);
        }
        
        vector<string> flight;
        flight.push_back(data[2]);
        flight.push_back(data[4]);
        
        edges.push_back(flight);
    }
    
    // Closes file
    Airlines.close();
    
    // Turning edges into directed graph
    for(const auto& flight : edges){
        directed_graph[flight[0]].push_back(flight[1]);
    }
    
    // Creates an undirected graph which has the reverse edge
    for(const auto& flight : edges){
        undirected_graph[flight[0]].push_back(flight[1]);
        undirected_graph[flight[1]].push_back(flight[0]);
    }
}

void bfsCheckWeakConnection(unordered_map<string, vector<string>>& graph){
    if(graph.empty()){
        cout << "Graph is empty!" << endl; // Added edge case handling
        return;
    }
    
    queue<string> queue;
    unordered_map<string, bool> visited;
    
    // Declare every vertex unvisited
    for(auto& node : graph){
        visited[node.first] = false;
    }
    
    // Push first node of the graph
    queue.push(graph.begin()->first);
    visited[graph.begin()->first] = true;
    
    // Goes through all the nodes until there is none left
    while(!queue.empty()){
        string s1 = queue.front();
        queue.pop();
        
        for(auto& destination : graph[s1]){
            if(!visited[destination]){
                visited[destination] = true;
                queue.push(destination);
            }
        }
    }
    
    // Check if all nodes are visited
    bool connected = true;
    for(const auto& node : visited){
        if(!node.second){
            connected = false;
        }
    }
    
    if(connected){
        cout << "Graph is weakly connected!" << endl;
    } else {
        cout << "Graph is not weakly connected!" << endl;
    }
}

bool isValidAirport(const unordered_map<string, vector<string>>& graph, const string& airport){
    return graph.find(airport) != graph.end();
}

void getAirport(const unordered_map<string, vector<string>>& undirected_graph, string& airport){
    bool validInput = false;
    do {
        cin >> airport;
        
        for (char& c : airport) {
            c = toupper(c);
        }
        
        if (!isValidAirport(undirected_graph, airport)) {
            cout << "Invalid airport code or airport not found. Please try again: ";
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore/Clear all characters
        } else {
            validInput = true;
        }
    } while (!validInput);
};

pair<vector<string>, int> shortestPathAndStops(unordered_map<string, vector<string>>& graph, const string& start, const string& stop){
    if(graph.empty()){
        cout << "Graph is empty!" << endl; // Added edge case handling
        return {{}, -1};
    }
    
    queue<pair<string, int>> queue; // Track number of stops
    unordered_map<string, bool> visited;
    unordered_map<string, string> parent; // Track path using parent & child nodes
    
    // Declare every vertex unvisited
    for(auto& node : graph){
        visited[node.first] = false;
    }
    
    queue.push({start, -1});
    visited[start] = true;
    parent[start] = "NULL";
    
    // Goes through all the nodes until there is none left
    while(!queue.empty()){
        auto [currentStop, stops] = queue.front();
        queue.pop();
        
        if(currentStop == stop){
            // Reconstruct path
            string node = stop;
            vector<string> path;
            while(node != "NULL"){
                path.push_back(node);
                node = parent[node];
            }
            reverse(path.begin(), path.end());
            return {path, stops};
        }
        
        for(auto& destination : graph[currentStop]){
            if(!visited[destination]){
                visited[destination] = true;
                parent[destination] = currentStop;
                queue.push({destination, stops + 1});
            }
        }
    }
    
    return {{}, -1};
}

void printResult(const pair<vector<string>, int>& result){
    if(!result.first.empty()){
        cout << "Shortest Path: ";
        for(int i = 0; i < result.first.size(); ++i){
            cout << result.first[i];
            if (i != result.first.size() - 1) { // Check to avoid printing "->" after the last element
                cout << " -> ";
            }
        }
        cout << endl;  // Print number of stops
        cout << "Number of stops: " << result.second << endl;
    } else {
        cout << "No path found. " << endl;
    }
}