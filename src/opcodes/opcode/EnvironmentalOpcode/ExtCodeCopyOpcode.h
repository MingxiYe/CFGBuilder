#include<iostream>
#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../EnvironmentalOpcode.h"
#endif

using namespace std;

class ExtCodeCopyOpcode : public EnvironmentalOpcode{
    public:
        ExtCodeCopyOpcode(long offset) : EnvironmentalOpcode(OpcodeID::EXTCODECOPY){
            this->offset = offset;
        }
        
        int getStackGenerated() const{
            return 0;
        }

        int getStackConsumed() const{
            return 4;
        }
};