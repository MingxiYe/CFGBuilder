#include<iostream>
#ifndef _SYSTEMOPCODE_H
#define _SYSTEMOPCODE_H
#include "../SystemOpcode.h"
#endif

using namespace std;

class CallCodeOpcode : public SystemOpcode{
    public:
        CallCodeOpcode(long offset) : SystemOpcode(OpcodeID::CALLCODE){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 7;
        }
};