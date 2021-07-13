#include<iostream>
#ifndef _ARITHMETICOPCODE_H
#define _ARITHMETICOPCODE_H
#include "../ArithmeticOpcode.h"
#endif

using namespace std;

class BinaryArithmeticOpcode : public ArithmeticOpcode {
    public:
        BinaryArithmeticOpcode(OpcodeID opcodeID):ArithmeticOpcode(opcodeID){}

        int getStackConsumed() const{
            return 2;
        }
};