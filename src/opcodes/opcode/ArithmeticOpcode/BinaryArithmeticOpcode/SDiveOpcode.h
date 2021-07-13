#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class SDivOpcode : public BinaryArithmeticOpcode{
    public:
        SDivOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::SDIV){
            this->offset = offset;
        }
};