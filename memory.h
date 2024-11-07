#ifndef MEMORY_H
#define MEMORY_H

#include <bits\stdc++.h>

class Memory {
public:
    std::vector<std::string> M;
    Memory();
    void setmem(int n, const std::string& value);
    std::string getmem(int n);
};

#endif
