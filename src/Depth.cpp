// Author: Apostolos Chalis <achalis@csd.auth.gr> 
#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

#include "Algorithms.hpp"

void runDepth(long long start, long long target, const std::string& filename) {
    auto start_time = std::chrono::high_resolution_clock::now();

    std::stack<State> s;
    std::unordered_set<long long> visited;

    s.push({start, "", 0, 0});

    while (!s.empty()) {
        State current = s.top();
        s.pop();

        if (visited.find(current.value) != visited.end()) {
            continue;
        }
        
        visited.insert(current.value);

        if (current.value == target) {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

            std::ofstream outfile(filename);
            if (outfile.is_open()) {
                outfile << current.steps << ", " << current.totalCost << std::endl;
                outfile << current.path;
                outfile.close();
                
                std::cout << "DFS found a solution in " << duration.count() << " us" << std::endl;
            }
            return;
        }

        std::vector<Neighbor> neighbors = getNeighbors(current.value);

        for (int i = (int)neighbors.size() - 1; i >= 0; --i) {
            Neighbor n = neighbors[i];

            if (visited.find(n.value) == visited.end()) {
                State nextState;
                nextState.value = n.value;
                nextState.path = current.path + n.opName + " " + 
                                 std::to_string(current.value) + " " + 
                                 std::to_string(n.opCost) + "\n";
                nextState.totalCost = current.totalCost + n.opCost;
                nextState.steps = current.steps + 1;

                s.push(nextState);
            }
        }
    }

    std::cout << "DFS: No solution found within the explored paths." << std::endl;
}
