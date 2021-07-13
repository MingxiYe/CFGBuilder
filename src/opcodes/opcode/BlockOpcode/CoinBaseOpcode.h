#include<iostream>
#ifndef _BLOCKOPCODE_H
#define _BLOCKOPCODE_H
#include "../BlockOpcode.h"
#endif

using namespace std;

class CoinBaseOpcode : public BlockOpcode{
    public:
        CoinBaseOpcode(long offset) : BlockOpcode(OpcodeID::COINBASE){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 0;
        }
};