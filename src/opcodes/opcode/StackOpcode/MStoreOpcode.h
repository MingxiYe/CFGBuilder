#include<iostream>
#ifndef _STACKOPCODE_H
#define _STACKOPCODE_H
#include "../StackOpcode.h"
#endif

using namespace std;

class MStoreOpcode : public StackOpcode{
    public:
        MStoreOpcode(long offset) : StackOpcode(OpcodeID::MSTORE){
            this->offset = offset;
        }

        int getStackGenerated() const{
            return 0;
        }

        int getStackConsumed() const{
            return 2;
        }
};