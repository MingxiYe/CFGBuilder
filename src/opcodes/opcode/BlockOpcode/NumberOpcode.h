#include<iostream>
#ifndef _BLOCKOPCODE_H
#define _BLOCKOPCODE_H
#include "../BlockOpcode.h"
#endif

using namespace std;

class NumberOpcode : public BlockOpcode{
    public:
        NumberOpcode(long offset) : BlockOpcode(OpcodeID::NUMBER){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 0;
        }
};