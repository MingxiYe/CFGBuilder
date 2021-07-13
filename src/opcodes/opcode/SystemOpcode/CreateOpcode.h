#include<iostream>
#ifndef _SYSTEMOPCODE_H
#define _SYSTEMOPCODE_H
#include "../SystemOpcode.h"
#endif

using namespace std;

class CreateOpcode : public SystemOpcode{
    public:
        CreateOpcode(long offset) : SystemOpcode(OpcodeID::CREATE){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 3;
        }
};