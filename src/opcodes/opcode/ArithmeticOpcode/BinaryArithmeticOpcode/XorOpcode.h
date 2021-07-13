#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class XorOpcode : public BinaryArithmeticOpcode{
    public:
        XorOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::XOR){
            this->offset = offset;
        }
};