#include<iostream>
#ifndef _CONTROLFLOWOPCODE_H
#define _CONTROLFLOWOPCODE_H
#include "../ControlFlowOpcode.h"
#endif

using namespace std;

class JumpIOpcode : public ControlFlowOpcode{
    public:
        JumpIOpcode(long offset) : ControlFlowOpcode(OpcodeID::JUMPI){
            this->offset = offset;
        }

        int getStackGenerated() const{
            return 0;
        }

        int getStackConsumed() const{
            return 2;
        }
};