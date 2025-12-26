// Author: Apostolos Chalis <achalis@csd.auth.gr> 
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <queue>
#include <unordered_set>
#include "Algorithms.hpp"

struct BestState {
    State state;
    long long hScore; 

    bool operator>(const BestState& other) const {
        return hScore > other.hScore;
    }
};

void runBest(long long start, long long target, const std::string& filename) {
    auto start_time = std::chrono::high_resolution_clock::now();

    std::priority_queue<BestState, std::vector<BestState>, std::greater<BestState>> pq;
    std::unordered_set<long long> visited;

    pq.push({{start, "", 0, 0}, heuristic(start, target)});
    visited.insert(start);

    while (!pq.empty()) {
        BestState currentB = pq.top();
        pq.pop();
        
        State current = currentB.state;

        if (current.value == target) {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

            std::ofstream outfile(filename);
            if (outfile.is_open()) {
                outfile << current.steps << ", " << current.totalCost << std::endl;
                outfile << current.path;
                outfile.close();
                std::cout << "Best-First found a solution in " << duration.count() << " us" << std::endl;
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

                pq.push({nextState, heuristic(n.value, target)});
            }
        }
    }
}
