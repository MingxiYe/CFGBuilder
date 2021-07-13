#include<iostream>
#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../EnvironmentalOpcode.h"
#endif

using namespace std;

class CodeSizeOpcode : public EnvironmentalOpcode{
    public:
        CodeSizeOpcode(long offset) : EnvironmentalOpcode(OpcodeID::CODESIZE){
            this->offset = offset;
        }
        
        int getStackConsumed() const{
            return 0;
        }
};