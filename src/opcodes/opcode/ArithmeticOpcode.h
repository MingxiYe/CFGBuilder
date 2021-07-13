#include<iostream>

#ifndef _OPCODE_H
#define _OPCODE_H
#include "../Opcode.h"
#endif

using namespace std;

class ArithmeticOpcode : public Opcode{
    public:
        ArithmeticOpcode(OpcodeID opcodeID) : Opcode(opcodeID){}
};