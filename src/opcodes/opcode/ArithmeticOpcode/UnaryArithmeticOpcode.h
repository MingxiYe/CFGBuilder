#include<iostream>
#ifndef _ARITHMETICOPCODE_H
#define _ARITHMETICOPCODE_H
#include "../ArithmeticOpcode.h"
#endif
using namespace std;

class UnaryArithmeticOpcode : public ArithmeticOpcode {
    public:
        UnaryArithmeticOpcode(OpcodeID opcodeID):ArithmeticOpcode(opcodeID){}

        int getStackConsumed() const{
            return 1;
        }
};