#include "instructions.h"

bool Instructions::readfile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << std::endl;
        std::cout << "Please try another File ";
        return false;
    }

    std::string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            Instruct.push_back(line);
        }
    }
    file.close();

    if (Instruct.empty() || Instruct.back() != "C000") {
        Instruct.push_back("C000");

        std::ofstream outfile(filename, std::ios_base::app);
        if (outfile.is_open()) {
            outfile << "\nC000";
            outfile.close();
        }
    }
    return true;
}
