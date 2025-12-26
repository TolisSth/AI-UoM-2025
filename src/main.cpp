#include <iostream>
#include <fstream> 

#include "ArgParser.hpp"
#include "Algorithms.hpp"

int main(int argc, char** argv) {
	std::string algo; 
	int starting_value;
	int ending_value;
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
        // 3. Write data to the file (just like using std::cout)
        outFile << "This is the content of my solution file." << std::endl;

        // 4. Close the file (important to save changes!)
        outFile.close();
        std::cout << "File created successfully." << std::endl;
    } else {
        std::cerr << "Error: Could not create the file." << std::endl;
    }

	return 0;
} 
	
