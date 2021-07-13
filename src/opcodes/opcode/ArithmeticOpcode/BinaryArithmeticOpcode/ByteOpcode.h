#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class ByteOpcode : public BinaryArithmeticOpcode{
    public:
        ByteOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::BYTE){
            this->offset = offset;
        }
};