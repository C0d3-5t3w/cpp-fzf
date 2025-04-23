#ifndef RIPGREP_H
#define RIPGREP_H

#include <string>
#include <vector>

class Ripgrep {
public:
    std::vector<std::string> search(const std::string& pattern, const std::string& path);
};

#endif 
