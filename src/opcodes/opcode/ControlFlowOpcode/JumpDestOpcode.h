#include<iostream>
#ifndef _CONTROLFLOWOPCODE_H
#define _CONTROLFLOWOPCODE_H
#include "../ControlFlowOpcode.h"
#endif

using namespace std;

class JumpDestOpcode : public ControlFlowOpcode{
    public:
        JumpDestOpcode(long offset) : ControlFlowOpcode(OpcodeID::JUMPDEST){
            this->offset = offset;
        }

        int getStackGenerated() const{
            return 0;
        }

        int getStackConsumed() const{
            return 0;
        }
};