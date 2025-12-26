#ifndef ALGOS_HPP
#define ALGOS_HPP

#include <string>

void runBreadth(int start, int end, const std::string& filename);
void runDepth(int start, int end, const std::string& filename);
void runAStar(int start, int end, const std::string& filename);
void runBest(int start, int end, const std::string& filename);

#endif
