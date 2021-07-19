#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class MulOpcode : public BinaryArithmeticOpcode{
    public:
        MulOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::MUL){
            this->offset = offset;
        }
};