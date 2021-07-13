#include<iostream>

#ifndef _OPCODE_H
#define _OPCODE_H
#include "../Opcode.h"
#endif


using namespace std;

class ControlFlowOpcode : public Opcode{
    public:
        ControlFlowOpcode(OpcodeID opcodeID) : Opcode(opcodeID){}
};