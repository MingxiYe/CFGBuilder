#include<iostream>
#ifndef _SYSTEMOPCODE_H
#define _SYSTEMOPCODE_H
#include "../SystemOpcode.h"
#endif

using namespace std;

class ReturnOpcode : public SystemOpcode{
    public:
        ReturnOpcode(long offset) : SystemOpcode(OpcodeID::RETURN){
            this->offset = offset;
        }

        int getStackGenerated() const{
            return 0;
        }

        int getStackConsumed() const{
            return 2;
        }
};