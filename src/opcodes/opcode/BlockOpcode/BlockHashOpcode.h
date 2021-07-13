#include<iostream>
#ifndef _BLOCKOPCODE_H
#define _BLOCKOPCODE_H
#include "../BlockOpcode.h"
#endif

using namespace std;

class BlockHashOpcode : public BlockOpcode{
    public:
        BlockHashOpcode(long offset) : BlockOpcode(OpcodeID::BLOCKHASH){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 1;
        }
};