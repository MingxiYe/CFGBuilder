#include<iostream>
#ifndef _SYSTEMOPCODE_H
#define _SYSTEMOPCODE_H
#include "../SystemOpcode.h"
#endif

using namespace std;

class StaticCallOpcode : public SystemOpcode{
    public:
        StaticCallOpcode(long offset) : SystemOpcode(OpcodeID::STATICCALL){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 6;
        }
};