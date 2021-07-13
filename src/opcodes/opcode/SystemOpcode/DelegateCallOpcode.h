#include<iostream>
#ifndef _SYSTEMOPCODE_H
#define _SYSTEMOPCODE_H
#include "../SystemOpcode.h"
#endif

using namespace std;

class DelegateCallOpcode : public SystemOpcode{
    public:
        DelegateCallOpcode(long offset) : SystemOpcode(OpcodeID::DELEGATECALL){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 6;
        }
};