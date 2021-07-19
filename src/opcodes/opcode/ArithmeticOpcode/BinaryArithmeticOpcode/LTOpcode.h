#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class LTOpcode : public BinaryArithmeticOpcode{
    public:
        LTOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::LT){
            this->offset = offset;
        }
};