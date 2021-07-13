#include<iostream>

#ifndef _OPCODE_H
#define _OPCODE_H
#include "../Opcode.h"
#endif

using namespace std;

class SystemOpcode : public Opcode{
    public:
        SystemOpcode(OpcodeID opcodeID) : Opcode(opcodeID){}
};