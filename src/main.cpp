// Author: Apostolos Chalis <achalis@csd.auth.gr> 
#include <iostream>
#include <fstream> 

#include "ArgParser.hpp"
#include "Algorithms.hpp"

int main(long long argc, char** argv) {
	std::string algo; 
	long long starting_value;
	long long ending_value;
	std::string filename;

	ArgParser args(argc, argv); 

	if (args.count() > 0) {
		algo = args.get(0);
		starting_value = std::stoi(args.get(1));
		ending_value = std::stoi(args.get(2));
		filename = args.get(3);
	}

	std::ofstream outFile(filename);

	if (outFile.is_open()) {
        	outFile.close();
        	std::cout << "File created successfully." << std::endl;
    	} else {
        std::cerr << "Error: Could not create the file." << std::endl;
    	}

	if (algo == "breadth") {
		runBreadth(starting_value, ending_value, filename);
	} else if (algo == "depth") {
		runDepth(starting_value, ending_value, filename);
	} else if (algo == "astar") {
		runAStar(starting_value, ending_value, filename);
	} else if (algo == "best") {
		runBest(starting_value, ending_value, filename);
	} else {
		std::cerr << "Error: Unknown algorithm specified." << std::endl;
	}

	return 0;
} 
	
