#include<iostream>
#ifndef _UNARYARITHMETICOPCODE_H
#define _UNARYARITHMETICOPCODE_H
#include "../UnaryArithmeticOpcode.h"
#endif


using namespace std;

class IsZeroOpcode : public UnaryArithmeticOpcode{
    public:
        IsZeroOpcode(long offset) : UnaryArithmeticOpcode(OpcodeID::ISZERO){
            this->offset = offset;
        }
};