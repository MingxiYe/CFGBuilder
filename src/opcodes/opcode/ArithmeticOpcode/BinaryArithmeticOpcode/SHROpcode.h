#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class SHROpcode : public BinaryArithmeticOpcode{
    public:
        SHROpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::SHR){
            this->offset = offset;
        }
};