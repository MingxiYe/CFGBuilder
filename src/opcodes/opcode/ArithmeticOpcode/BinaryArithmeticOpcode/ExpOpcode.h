#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class ExpOpcode : public BinaryArithmeticOpcode{
    public:
        ExpOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::EXP){
            this->offset = offset;
        }
};