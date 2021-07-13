#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class OrOpcode : public BinaryArithmeticOpcode{
    public:
        OrOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::OR){
            this->offset = offset;
        }
};