#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class SGTOpcode : public BinaryArithmeticOpcode{
    public:
        SGTOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::SGT){
            this->offset = offset;
        }
};