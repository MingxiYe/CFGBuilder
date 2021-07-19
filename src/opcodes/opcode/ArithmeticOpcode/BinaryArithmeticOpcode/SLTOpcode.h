#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif
using namespace std;

class SLTOpcode : public BinaryArithmeticOpcode{
    public:
        SLTOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::SLT){
            this->offset = offset;
        }
};