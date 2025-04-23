#include "ripgrep.h"
#include <cstdio> 
#include <iostream> 
#include <stdexcept> 

std::vector<std::string> Ripgrep::search(const std::string& pattern, const std::string& path) {
    std::vector<std::string> results;
    std::string command = "rg --color never --line-number --no-heading \"" + pattern + "\" \"" + path + "\"";
    
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        results.push_back(buffer);
        
        if (!results.empty() && results.back().back() == '\n') {
            results.back().pop_back();
        }
    }

    int status = pclose(pipe);
    if (status == -1) {
         
         std::cerr << "Warning: pclose() failed." << std::endl;
    } else {
         if (status != 0) {
         }
    }

    return results;
}
