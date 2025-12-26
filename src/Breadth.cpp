#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include <string>
#include <fstream>
#include <chrono> 

#include "Algorithms.hpp" 

void runBreadth(long long start, long long target, const std::string& filename) {
    auto start_time = std::chrono::high_resolution_clock::now();

    std::queue<State> q;
    std::unordered_set<long long> visited;

    q.push({start, "", 0, 0});
    visited.insert(start);
    
    while (!q.empty()) {
        State current = q.front();
        q.pop();

        if (current.value == target) {
            auto end_time = std::chrono::high_resolution_clock::now();
            
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

            std::ofstream outfile(filename);
            if (outfile.is_open()) {
                outfile << current.steps << ", " << current.totalCost << std::endl;
                outfile << current.path;
                outfile.close();
                
                std::cout << "BFS Found solution in " << duration.count() << " ms" << std::endl;
                std::cout << "Steps: " << current.steps << ", Total Cost: " << current.totalCost << std::endl;
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
    
    std::cout << "No solution found." << std::endl;
}
