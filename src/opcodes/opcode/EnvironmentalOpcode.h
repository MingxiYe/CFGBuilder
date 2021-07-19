#include<iostream>

#ifndef _OPCODE_H
#define _OPCODE_H
#include "../Opcode.h"
#endif


using namespace std;

class EnvironmentalOpcode : public Opcode{
    public:
        EnvironmentalOpcode(OpcodeID opcodeID) : Opcode(opcodeID){}
};