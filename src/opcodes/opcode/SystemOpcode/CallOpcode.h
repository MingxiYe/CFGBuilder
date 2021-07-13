#include<iostream>
#ifndef _SYSTEMOPCODE_H
#define _SYSTEMOPCODE_H
#include "../SystemOpcode.h"
#endif

using namespace std;

class CallOpcode : public SystemOpcode{
    public:
        CallOpcode(long offset) : SystemOpcode(OpcodeID::CALL){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 7;
        }
};