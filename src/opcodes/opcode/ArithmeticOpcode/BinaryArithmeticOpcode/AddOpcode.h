#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class AddOpcode : public BinaryArithmeticOpcode{
    public:
        AddOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::ADD){
            this->offset = offset;
        }
};