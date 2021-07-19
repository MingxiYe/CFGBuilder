#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class SHLOpcode : public BinaryArithmeticOpcode{
    public:
        SHLOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::SHL){
            this->offset = offset;
        }
};