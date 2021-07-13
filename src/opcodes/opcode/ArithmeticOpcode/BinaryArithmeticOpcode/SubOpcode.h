#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class SubOpcode : public BinaryArithmeticOpcode{
    public:
        SubOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::SUB){
            this->offset = offset;
        }
};