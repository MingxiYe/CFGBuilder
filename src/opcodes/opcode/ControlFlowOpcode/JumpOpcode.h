#include<iostream>
#ifndef _CONTROLFLOWOPCODE_H
#define _CONTROLFLOWOPCODE_H
#include "../ControlFlowOpcode.h"
#endif

using namespace std;

class JumpOpcode : public ControlFlowOpcode{
    public:
        JumpOpcode(long offset) : ControlFlowOpcode(OpcodeID::JUMP){
            this->offset = offset;
        }

        int getStackGenerated() const{
            return 0;
        }

        int getStackConsumed() const{
            return 1;
        }
};