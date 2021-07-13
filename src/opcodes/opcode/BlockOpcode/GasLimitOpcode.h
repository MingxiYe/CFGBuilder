#include<iostream>
#ifndef _BLOCKOPCODE_H
#define _BLOCKOPCODE_H
#include "../BlockOpcode.h"
#endif

using namespace std;

class GasLimitOpcode : public BlockOpcode{
    public:
        GasLimitOpcode(long offset) : BlockOpcode(OpcodeID::GASLIMIT){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 0;
        }
};