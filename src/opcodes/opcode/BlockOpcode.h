#include<iostream>

#ifndef _OPCODE_H
#define _OPCODE_H
#include "../Opcode.h"
#endif


using namespace std;

class BlockOpcode : public Opcode{
    public:
        BlockOpcode(OpcodeID opcodeID) : Opcode(opcodeID){}
};