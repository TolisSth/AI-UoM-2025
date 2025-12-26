#ifndef ALGOS_HPP
#define ALGOS_HPP

#include <string>
#include <vector>
#include <cmath>   
#include <algorithm>

void runBreadth(long long start, long long end, const std::string& filename);
void runDepth(long long start, long long end, const std::string& filename);
void runAStar(long long start, long long end, const std::string& filename);
void runBest(long long start, long long end, const std::string& filename);

struct State {
    long long value;
    std::string path; 
    int cost;
    int steps;
};

struct Neighbor {
    long long value;
    std::string opName; 
    int opCost;
};

inline std::vector<Neighbor> getNeighbors(long long x) {
    std::vector<Neighbor> res;

    // 1. Increase
    if (x < 1000000000) 
        res.push_back({x + 1, "increase", 2});

    // 2. Decrease
    if (x > 0) 
        res.push_back({x - 1, "decrease", 2});

    // 3. Double
    if (x > 0 && x * 2 <= 1000000000) 
        res.push_back({x * 2, "double", (int)(x / 2) + 1});

    // 4. Half
    if (x > 0) 
        res.push_back({x / 2, "half", (int)(x / 4) + 1});

    // 5. Square
    if (x > 1 && x <= 31622) { 
        long long sq = x * x;
        if (sq <= 1000000000)
            res.push_back({sq, "square", (int)((sq - x) / 4) + 1});
    }

    // 6. Root
    if (x > 1) {
        long long r = (long long)std::round(std::sqrt(x));
        if (r * r == x) 
            res.push_back({r, "root", (int)((x - r) / 4) + 1});
    }

    return res;
}

#endif
