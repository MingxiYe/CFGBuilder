#include<iostream>
#ifndef _ARITHMETICOPCODE_H
#define _ARITHMETICOPCODE_H
#include "../ArithmeticOpcode.h"
#endif

using namespace std;

class TernaryArithmeticOpcode : public ArithmeticOpcode {
    public:
        TernaryArithmeticOpcode(OpcodeID opcodeID):ArithmeticOpcode(opcodeID){}

        int getStackConsumed() const{
            return 3;
        }
};