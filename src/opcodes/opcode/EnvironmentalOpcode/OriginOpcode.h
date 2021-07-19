#include<iostream>
#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../EnvironmentalOpcode.h"
#endif

using namespace std;

class OriginOpcode : public EnvironmentalOpcode{
    public:
        OriginOpcode(long offset) : EnvironmentalOpcode(OpcodeID::ORIGIN){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 0;
        }
};