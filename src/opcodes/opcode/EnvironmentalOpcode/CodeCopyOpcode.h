#include<iostream>
#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../EnvironmentalOpcode.h"
#endif

using namespace std;

class CodeCopyOpcode : public EnvironmentalOpcode{
    public:
        CodeCopyOpcode(long offset) : EnvironmentalOpcode(OpcodeID::CODECOPY){
            this->offset = offset;
        }

        int getStackGenerated() const{
            return 0;
        }

        int getStackConsumed() const{
            return 3;
        }
};