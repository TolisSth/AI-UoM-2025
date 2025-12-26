#include <iostream>
#include <stack>
#include <queue>
#include <unordered_set>
#include <vector>
#include <string>
#include <fstream>

#include "Algorithms.hpp" 

void runBreadth(long long start, long long target, const std::string& filename) {
    std::queue<State> q;
    std::unordered_set<long long> visited;

    q.push({start, "", 0, 0});
    visited.insert(start);

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        if (current.value == target) {
            std::ofstream outfile(filename);
            if (outfile.is_open()) {
                outfile << current.steps << ", " << current.totalCost << std::endl;
                outfile << current.path;
                outfile.close();
            }
            return;
        }

        std::vector<Neighbor> neighbors = getNeighbors(current.value);
        for (const auto& n : neighbors) {
            if (visited.find(n.value) == visited.end()) {
                visited.insert(n.value);
                
                State nextState;
                nextState.value = n.value;
                nextState.path = current.path + n.opName + " " + std::to_string(current.value) + " " + std::to_string(n.opCost) + "\n";
                nextState.totalCost = current.totalCost + n.opCost;
                nextState.steps = current.steps + 1;
                
                q.push(nextState);
            }
        }
    }
}
