#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class SignExtendOpcode : public BinaryArithmeticOpcode{
    public:
        SignExtendOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::SIGNEXTEND){
            this->offset = offset;
        }
};