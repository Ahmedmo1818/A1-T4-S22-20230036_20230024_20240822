#include "machine.h"
#include <bits\stdc++.h>

Machine::Machine(int indx) : nn(indx) {}

float Machine::handleFloat(const std::string& hexVal) {
    int val = std::stoi(hexVal, nullptr, 16);
    int sign = (val & 0x80) >> 7;
    int exponent = (val & 0x70) >> 4;
    int mantissa = val & 0x0F;

    float mantissaVal = 1.0 + mantissa / 16.0;
    float decimalValue = std::pow(2, exponent - 4) * mantissaVal;
    return sign ? -decimalValue : decimalValue;
}

std::string Machine::encodeFloat(float value) {
    if (value == 0) return "00";
    int sign = (value < 0) ? 1 : 0;
    value = std::fabs(value);

    int exponent = std::floor(std::log2(value)) + 4;
    float mantissa = value / std::pow(2, exponent - 4) - 1;
    int mantissaBits = static_cast<int>(mantissa * 16);

    int encodedVal = (sign << 7) | (exponent << 4) | mantissaBits;
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << encodedVal;
    return ss.str();
}

int Machine::towscomplement(const std::string& hexVal) {
    int val = std::stoi(hexVal, nullptr, 16);
    if (val & 0x80) {
        val -= 256;  // handle negative values
    }
    return val;
}

std::string Machine::decimalToTwosComplement(int decimal) {
    std::stringstream ss; 
    if (decimal >= 0) {
        ss << std::hex << std::setw(2) << std::setfill('0') << decimal;
    } else if (decimal > 256) {
        decimal %= 256;
    } else {
        decimal += 256; 
        ss << std::hex << std::setw(2) << std::setfill('0') << decimal;
    }
    return ss.str(); 
}

void Machine::Run(const std::string& instruction) {
    char op_code = instruction[0];
    int r = std::stoi(instruction.substr(1, 1), nullptr, 16);
    int x = std::stoi(instruction.substr(2, 1), nullptr, 16);
    int y = std::stoi(instruction.substr(3, 1), nullptr, 16);
    int address = (x << 4) | y;

    memo.setmem(nn++, instruction.substr(0, 2));
    memo.setmem(nn++, instruction.substr(2, 2));

    switch (op_code) {
        case '1': {  // LOAD  register R with memory address XY
            std::string memContent = memo.getmem(address); 
            Reg.setReg(r, memContent); 
            std::cout << "Loaded Register [" << r << "] with memory[" << std::hex << address << "]: " << memContent << std::endl;
            break;
        }
        case '2':   // LOAD value XY into register R
            Reg.setReg(r, instruction.substr(2, 2));
            std::cout << "=============================\n";
            std::cout << "Register [" << r << "] loaded with: " << Reg.getReg(r) << std::endl;
            break;
        case '3':  // STORE register R to memory address XY
            if (address == 0) {
                memo.setmem(0, Reg.getReg(1));
                char asciiChar = stoi(Reg.getReg(1), nullptr, 16);
                //std::cout << "Printed (ASCII): " << asciiChar << " = " << Reg.getReg(1) << std::endl;
            }
            else {
                memo.setmem(address, Reg.getReg(r));
                std::cout << "Stored in memory[" << std::hex << address << "]: " << Reg.getReg(r) << std::endl;
            }
            break;
        case '4':  // MOVE
            Reg.setReg(y, Reg.getReg(r));
            std::cout << "=============================\n";
            std::cout << "Register [" << y << "] set to: " << Reg.getReg(r) << std::endl;
            break;
        case '5': {  // ADD two's complement
            int regSVal = towscomplement(Reg.getReg(x));
            int regTVal = towscomplement(Reg.getReg(y));
            int result = regSVal + regTVal;
            Reg.setReg(r, decimalToTwosComplement(result));
            std::cout << "=============================\n";
            std::cout << "R" << r << " = " << regSVal << " + " << regTVal << " = " << result << std::endl;
            break;
        }
        case '6': {  // ADD floating
            float regR0Val = handleFloat(Reg.getReg(y));
            float regR1Val = handleFloat(Reg.getReg(x));
            float result = regR0Val + regR1Val;
            Reg.setReg(r, encodeFloat(result));
            std::cout << "=============================\n";
            std::cout << "R" << r << " = " << regR0Val << " + " << regR1Val << " = " << result << std::endl;
            break;
        }
        case '7':   // OR
            Reg.setReg(r, decimalToTwosComplement(towscomplement(Reg.getReg(x)) | towscomplement(Reg.getReg(y))));
            std::cout << "=============================\n";
            std::cout << "OR of registers R" << x << " and R" << y << ", storing in R" << r << ": " << Reg.getReg(r) << std::endl;
            break;  // AND
        case '8':
            Reg.setReg(r, decimalToTwosComplement(towscomplement(Reg.getReg(x)) & towscomplement(Reg.getReg(y))));
            std::cout << "=============================\n";
            std::cout << "AND of registers R" << x << " and R" << y << ", storing in R" << r << ": " << Reg.getReg(r) << std::endl;
            break;
        case '9':    // XOR
            Reg.setReg(r, decimalToTwosComplement(towscomplement(Reg.getReg(x)) ^ towscomplement(Reg.getReg(y))));
            std::cout << "=============================\n";
            std::cout << "XOR of registers R" << x << " and R" << y << ", storing in R" << r << ": " << Reg.getReg(r) << std::endl;
            break;
        case 'A': {  // Rotating
            int rotateSteps = std::stoi(instruction.substr(2, 2), nullptr, 16);
            int regVal = std::stoi(Reg.getReg(r), nullptr, 16);
            regVal = (regVal >> rotateSteps) | (regVal << (8 - rotateSteps));
            regVal &= 0xFF;
            Reg.setReg(r, decimalToTwosComplement(regVal));
            std::cout << "=============================\n";
            std::cout << "Rotating register R" << r << " right by " << rotateSteps << " steps: " << decimalToTwosComplement(regVal) << std::endl;
            break;
        }
        case 'B': // Jump
            if (Reg.getReg(r) == Reg.getReg(0)) {
                programCount = address ;
            } 
            break;
        case 'C': // Stop
            programCount = instruct.Instruct.size();
            break;
        case 'D':  //Jump if register i > register 0
            if (towscomplement(Reg.getReg(r)) > towscomplement(Reg.getReg(0))) {
                programCount = address - 1;
                std::cout << "Jump to " << address << std::endl;
            }
            break;
        default:
            std::cout << "Unknown instruction: " << instruction << std::endl;
    }
    programCount++;
}

void Machine::loadInstruct(const std::string& filename) {
    if (instruct.readfile(filename)) {
        while (programCount < instruct.Instruct.size()) {
            Run(instruct.Instruct[programCount]);
        }
        Display_Registers();
        Display_Memory();
    }
}

void Machine::Display_Registers() {
    std::cout << "Register contents:\n";
    for (int i = 0; i < Reg.R.size(); ++i) {
        std::cout << "R" << i << " --> " << Reg.R[i] << std::endl;
    }
}

void Machine::Display_Memory() {
    std::cout << "Memory Cells:\n";
    for (int i = 0; i < memo.M.size(); ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << i << "): " << memo.M[i] << "  ";
        if (i % 16 == 15) std::cout << "\n";
    }
}
