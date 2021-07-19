#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class SHA3Opcode : public BinaryArithmeticOpcode{
    public:
        SHA3Opcode(long offset) : BinaryArithmeticOpcode(OpcodeID::SHA3){
            this->offset = offset;
        }
};