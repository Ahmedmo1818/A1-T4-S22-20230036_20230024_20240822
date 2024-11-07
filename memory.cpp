#include "memory.h"

Memory::Memory() {
    M.resize(256, "00");
}

void Memory::setmem(int n, const std::string& value) {
    if (n >= 0 && n < M.size()) {
        M[n] = value;
    }
}

std::string Memory::getmem(int n) {
    if (n >= 0 && n < M.size()) {
        return M[n];
    }
    return "";
}
