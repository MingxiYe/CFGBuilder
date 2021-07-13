#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class ModOpcode : public BinaryArithmeticOpcode{
    public:
        ModOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::MOD){
            this->offset = offset;
        }
};