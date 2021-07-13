#include<iostream>
#ifndef _TERNARYARITHMETICOPCODE_H
#define _TERNARYARITHMETICOPCODE_H
#include "../TernaryArithmeticOpcode.h"
#endif

using namespace std;

class AddModOpcode : public TernaryArithmeticOpcode{
    public:
        AddModOpcode(long offset) : TernaryArithmeticOpcode(OpcodeID::ADDMOD){
            this->offset = offset;
        }
};