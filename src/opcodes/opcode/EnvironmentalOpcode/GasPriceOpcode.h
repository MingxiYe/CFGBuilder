#include<iostream>
#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../EnvironmentalOpcode.h"
#endif

using namespace std;

class GasPriceOpcode : public EnvironmentalOpcode{
    public:
        GasPriceOpcode(long offset) : EnvironmentalOpcode(OpcodeID::GASPRICE){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 0;
        }
};