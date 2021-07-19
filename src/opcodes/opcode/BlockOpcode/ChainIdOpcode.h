#include<iostream>
#ifndef _BLOCKOPCODE_H
#define _BLOCKOPCODE_H
#include "../BlockOpcode.h"
#endif

using namespace std;

class ChainIdOpcode : public BlockOpcode{
    public:
        ChainIdOpcode(long offset) : BlockOpcode(OpcodeID::CHAINID){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 0;
        }
};