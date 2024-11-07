#include "Register.h"

Register::Register() {
    R.resize(16, "00");
}

void Register::setReg(int r, const std::string& value) {
    if (r >= 0 && r < R.size()) R[r] = value;
}

std::string Register::getReg(int r) {
    if (r >= 0 && r < R.size()) return R[r];
    return "out of scope, please try with another register";
}
