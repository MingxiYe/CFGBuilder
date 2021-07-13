#include<iostream>
#ifndef _UNARYARITHMETICOPCODE_H
#define _UNARYARITHMETICOPCODE_H
#include "../UnaryArithmeticOpcode.h"
#endif

using namespace std;

class NotOpcode : public UnaryArithmeticOpcode{
    public:
        NotOpcode(long offset) : UnaryArithmeticOpcode(OpcodeID::NOT){
            this->offset = offset;
        }
};