#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class SModOpcode : public BinaryArithmeticOpcode{
    public:
        SModOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::SMOD){
            this->offset = offset;
        }
};