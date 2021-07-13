#include<iostream>
#ifndef _TERNARYARITHMETICOPCODE_H
#define _TERNARYARITHMETICOPCODE_H
#include "../TernaryArithmeticOpcode.h"
#endif

using namespace std;

class MulModOpcode : public TernaryArithmeticOpcode{
    public:
        MulModOpcode(long offset) : TernaryArithmeticOpcode(OpcodeID::MULMOD){
            this->offset = offset;
        }
};