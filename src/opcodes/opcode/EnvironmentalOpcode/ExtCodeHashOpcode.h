#include<iostream>
#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../EnvironmentalOpcode.h"
#endif

using namespace std;

class ExtCodeHashOpcode : public EnvironmentalOpcode{
    public:
        ExtCodeHashOpcode(long offset) : EnvironmentalOpcode(OpcodeID::EXTCODEHASH){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 1;
        }
};