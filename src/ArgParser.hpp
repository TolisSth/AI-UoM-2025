#include <iostream>
#include <vector>
#include <string>

class ArgParser {
public:
    ArgParser(long long argc, char** argv) {
        // Store all arguments except the executable name (argv[0])
        for (long long i = 1; i < argc; ++i) {
            tokens.push_back(std::string(argv[i]));
        }
    }

    // Get argument by index (0-based)
    std::string get(size_t index) const {
        if (index < tokens.size()) {
            return tokens[index];
        }
        return "";
    }

    // Returns how many arguments were actually passed
    size_t count() const {
        return tokens.size();
    }

private:
    std::vector<std::string> tokens;
};
