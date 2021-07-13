#include<iostream>
#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../EnvironmentalOpcode.h"
#endif

using namespace std;

class AddressOpcode : public EnvironmentalOpcode{
    public:
        AddressOpcode(long offset) : EnvironmentalOpcode(OpcodeID::ADDRESS){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 0;
        }
};