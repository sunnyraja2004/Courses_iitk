#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    vector<int> color(n + 1, 0);
    bool possible = true;
    
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            queue<int> q;
            q.push(i);
            color[i] = 1;  // Color the first apple red (color 1)
            
            while (!q.empty()) {
                 int apple = q.front();
                q.pop();
                
                for (int neighbor : graph[apple]) {
                    if (color[neighbor] == 0) {
                        color[neighbor] = 3 - color[apple];  // Assign the opposite color
                        q.push(neighbor);
                    } else if (color[neighbor] == color[apple]) {
                        possible = false;  // Samarth's claim is violated
                        break;
                    }
                }
                
                if (!possible) {
                    break;
                }
            }
        }
        
        if (!possible) {
            break;
            }
    }
    
    if (possible) {
        cout << "YES\n";
        for (int i = 1; i <= n; i++) {
            cout << color[i] << " ";
        }
    } else {
        cout << "NO";
    }
    
    return 0;
}
