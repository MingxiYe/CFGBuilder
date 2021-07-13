#include<iostream>
#ifndef _BLOCKOPCODE_H
#define _BLOCKOPCODE_H
#include "../BlockOpcode.h"
#endif

using namespace std;

class TimeStampOpcode : public BlockOpcode{
    public:
        TimeStampOpcode(long offset) : BlockOpcode(OpcodeID::TIMESTAMP){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 0;
        }
};