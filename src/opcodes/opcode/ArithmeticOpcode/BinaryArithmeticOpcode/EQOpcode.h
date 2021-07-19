#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class EQOpcode : public BinaryArithmeticOpcode{
    public:
        EQOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::EQ){
            this->offset = offset;
        }
};