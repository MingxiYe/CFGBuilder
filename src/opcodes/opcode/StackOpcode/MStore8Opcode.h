#include<iostream>
#ifndef _STACKOPCODE_H
#define _STACKOPCODE_H
#include "../StackOpcode.h"
#endif

using namespace std;

class MStore8Opcode : public StackOpcode{
    public:
        MStore8Opcode(long offset) : StackOpcode(OpcodeID::MSTORE8){
            this->offset = offset;
        }

        int getStackGenerated() const{
            return 0;
        }

        int getStackConsumed() const{
            return 2;
        }
};