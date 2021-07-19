#include<iostream>
#ifndef _CONTROLFLOWOPCODE_H
#define _CONTROLFLOWOPCODE_H
#include "../ControlFlowOpcode.h"
#endif

using namespace std;

class StopOpcode : public ControlFlowOpcode{
    public:
        StopOpcode(long offset) : ControlFlowOpcode(OpcodeID::STOP){
            this->offset = offset;
        }

        int getStackGenerated() const{
            return 0;
        }

        int getStackConsumed() const{
            return 0;
        }
};