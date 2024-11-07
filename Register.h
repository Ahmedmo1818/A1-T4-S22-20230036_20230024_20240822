#ifndef REGISTER_H
#define REGISTER_H

#include <bits\stdc++.h>

class Register {
public:
    std::vector<std::string> R;
    Register();
    void setReg(int r, const std::string& value);
    std::string getReg(int r);
};

#endif
