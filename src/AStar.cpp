#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <queue>
#include <unordered_map>
#include "Algorithms.hpp"

// Ορισμός δομής για την Priority Queue
struct AStarState {
    State state;
    long long fScore; // g(n) + h(n)

    // Ο Comparator επιστρέφει true αν το πρώτο έχει ΜΕΓΑΛΥΤΕΡΟ fScore
    // Έτσι η priority_queue θα μας δίνει το ΜΙΚΡΟΤΕΡΟ (Min-Heap)
    bool operator>(const AStarState& other) const {
        return fScore > other.fScore;
    }
};

void runAStar(long long start, long long target, const std::string& filename) {
    auto start_time = std::chrono::high_resolution_clock::now();

    // Priority Queue που επιστρέφει πάντα το State με το μικρότερο fScore
    std::priority_queue<AStarState, std::vector<AStarState>, std::greater<AStarState>> pq;

    // Το unordered_map εδώ κρατάει το καλύτερο g(n) που έχουμε βρει για κάθε αριθμό
    std::unordered_map<long long, long long> min_cost;

    // Αρχικοποίηση
    long long start_h = heuristic(start, target);
    pq.push({{start, "", 0, 0}, start_h});
    min_cost[start] = 0;

    while (!pq.empty()) {
        AStarState currentA = pq.top();
        pq.pop();
        
        State current = currentA.state;

        // Αν φτάσαμε στον στόχο, βρήκαμε τη βέλτιστη λύση!
        if (current.value == target) {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

            std::ofstream outfile(filename);
            if (outfile.is_open()) {
                outfile << current.steps << ", " << current.totalCost << std::endl;
                outfile << current.path;
                outfile.close();
                std::cout << "A* found optimal solution in " << duration.count() << " us" << std::endl;
            }
            return;
        }

        // Αν βρήκαμε ήδη φθηνότερο δρόμο για αυτόν τον αριθμό, προσπέρνα
        if (current.totalCost > min_cost[current.value]) continue;

        std::vector<Neighbor> neighbors = getNeighbors(current.value);
        for (const auto& n : neighbors) {
            long long new_g = current.totalCost + n.opCost;

            // Αν ο νέος δρόμος είναι φθηνότερος από ό,τι ξέραμε
            if (min_cost.find(n.value) == min_cost.end() || new_g < min_cost[n.value]) {
                min_cost[n.value] = new_g;
                
                State nextState;
                nextState.value = n.value;
                nextState.path = current.path + n.opName + " " + std::to_string(current.value) + " " + std::to_string(n.opCost) + "\n";
                nextState.totalCost = new_g;
                nextState.steps = current.steps + 1;

                long long f = new_g + heuristic(n.value, target);
                pq.push({nextState, f});
            }
        }
    }
    std::cout << "A*: No solution found." << std::endl;
}
