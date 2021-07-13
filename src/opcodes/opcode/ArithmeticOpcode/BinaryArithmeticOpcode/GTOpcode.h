#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class GTOpcode : public BinaryArithmeticOpcode{
    public:
        GTOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::GT){
            this->offset = offset;
        }
};