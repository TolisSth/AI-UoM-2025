#ifndef ALGOS_HPP
#define ALGOS_HPP

#include <string>
#include <vector>

void runBreadth(int start, int end, const std::string& filename);
void runDepth(int start, int end, const std::string& filename);
void runAStar(int start, int end, const std::string& filename);
void runBest(int start, int end, const std::string& filename);

struct State {
    long long value;
    string path;
    int cost;
    int steps;
};

struct Neighbor {
    long long value;
    string opName;
    int opCost;
};

vector<Neighbor> getNeighbors(long long x) {
    vector<Neighbor> res;

    // 1. Increase
    if (x + 1 <= 1000000000) 
        res.push_back({x + 1, "increase", 2});

    // 2. Decrease
    if (x - 1 >= 0) 
        res.push_back({x - 1, "decrease", 2});

    // 3. Double
    if (x > 0 && x * 2 <= 1000000000) 
        res.push_back({x * 2, "double", (int)(x / 2) + 1});

    // 4. Half
    if (x > 0) 
        res.push_back({x / 2, "half", (int)(x / 4) + 1});

    // 5. Square
    if (x > 1 && x <= 31622) { // 31622^2 ~ 10^9
        long long sq = x * x;
        res.push_back({sq, "square", (int)((sq - x) / 4) + 1});
    }

    // 6. Root
    if (x > 1) {
        long long r = round(sqrt(x));
        if (r * r == x) 
            res.push_back({r, "root", (int)((x - r) / 4) + 1});
    }

    return res;
}

#endif
