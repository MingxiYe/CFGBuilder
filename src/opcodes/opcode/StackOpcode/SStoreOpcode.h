#include<iostream>
#ifndef _STACKOPCODE_H
#define _STACKOPCODE_H
#include "../StackOpcode.h"
#endif

using namespace std;

class SStoreOpcode : public StackOpcode{
    public:
        SStoreOpcode(long offset) : StackOpcode(OpcodeID::SSTORE){
            this->offset = offset;
        }

        int getStackGenerated() const{
            return 0;
        }

        int getStackConsumed() const{
            return 2;
        }
};