#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class SAROpcode : public BinaryArithmeticOpcode{
    public:
        SAROpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::SAR){
            this->offset = offset;
        }
};