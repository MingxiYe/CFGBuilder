#include<iostream>
#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../BinaryArithmeticOpcode.h"
#endif

using namespace std;

class DivOpcode : public BinaryArithmeticOpcode{
    public:
        DivOpcode(long offset) : BinaryArithmeticOpcode(OpcodeID::DIV){
            this->offset = offset;
        }
};