#include<iostream>
#ifndef _SYSTEMOPCODE_H
#define _SYSTEMOPCODE_H
#include "../SystemOpcode.h"
#endif

using namespace std;

class SelfDestructOpcode : public SystemOpcode{
    public:
        SelfDestructOpcode(long offset) : SystemOpcode(OpcodeID::SELFDESTRUCT){
            this->offset = offset;
        }

        int getStackGenerated() const{
            return 0;
        }

        int getStackConsumed() const{
            return 1;
        }
};