#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
     int numCheckpoints, numRoads;
    cin >> numCheckpoints >> numRoads;

    vector<vector<int>> connections(numCheckpoints);
    vector<int> checkpointA(numRoads), checkpointB(numRoads);

    for (int i = 0; i < numRoads; i++) {
        cin >> checkpointA[i];
    }

    for (int i = 0; i < numRoads; i++) {
        cin >> checkpointB[i];
    }

    for (int i = 0; i < numRoads; i++) {
        connections[checkpointA[i] - 1].push_back(checkpointB[i] - 1);
        connections[checkpointB[i] - 1].push_back(checkpointA[i] - 1);
    }

    vector<int> isPartOfCycle(numCheckpoints, 0);
    vector<int> nodeStatus(numCheckpoints, 0);
    
    // Define the findCycles function
    function<int(vector<vector<int>>&, vector<int>&, vector<int>&, int, int)> findCycles;
    findCycles = [&](vector<vector<int>>& adjacency, vector<int>& cycleMarker, vector<int>& visited, int current, int parent) -> int {
        int ancestors = 0;
        visited[current] = 1;  // Mark the current node as visited.

        for (int neighbor : adjacency[current]) {
            if (visited[neighbor] == 1 || visited[neighbor] == 2) {
                // If the neighbor is in progress or already visited (excluding the parent), it's part of a cycle.
                if (neighbor != parent) {
                    ancestors += 1;
                    visited[neighbor] = 2;
                }
                } else if (visited[neighbor] == 0) {
                // If the neighbor is not visited, continue the DFS.
                ancestors += findCycles(adjacency, cycleMarker, visited, neighbor, current);
                if (visited[current] == 2) {
                    visited[current] = 1;
                    cycleMarker[current] = 1;
                    ancestors--;
                }
            }
        }

        if (ancestors) {
            cycleMarker[current] = 1;
            visited[current] = 3;
        }

        return ancestors;
    };

    if (numRoads > 2) {
        for (int i = 0; i < numCheckpoints; i++) {
            if (nodeStatus[i] == 0) {
                int ancestors = findCycles(connections, isPartOfCycle, nodeStatus, i, -1);
            }
        }
    }

    for (int i = 0; i < numCheckpoints; i++) {
        cout << isPartOfCycle[i] << " ";
    }
    
    return 0;
}