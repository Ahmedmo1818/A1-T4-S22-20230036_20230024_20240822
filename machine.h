#ifndef MACHINE_H
#define MACHINE_H

#include "Register.h"
#include "memory.h"
#include "instructions.h"
#include <bits\stdc++.h>

class Machine {
private:
    Register Reg;
    Memory memo;
    Instructions instruct;
    int programCount = 0;
    int nn;

public:
    Machine(int indx);
    float handleFloat(const std::string& hexVal);
    std::string encodeFloat(float value);
    int towscomplement(const std::string& hexVal);
    std::string decimalToTwosComplement(int decimal);
    void Run(const std::string& instruction);
    void loadInstruct(const std::string& filename);
    void Display_Registers();
    void Display_Memory();
};

#endif
