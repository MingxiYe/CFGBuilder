#include<iostream>

#ifndef _OPCODE_H
#define _OPCODE_H
#include "../Opcode.h"
#endif

using namespace std;

class StackOpcode : public Opcode{
    public:
        StackOpcode(OpcodeID opcodeID) : Opcode(opcodeID){}
};