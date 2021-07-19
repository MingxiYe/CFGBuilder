#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class AndOpcode : public BinaryArithmeticOpcode{
    public:
        AndOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::AND){
            this->offset = offset;
        }
};