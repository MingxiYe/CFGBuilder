#include<iostream>
#ifndef _BLOCKOPCODE_H
#define _BLOCKOPCODE_H
#include "../BlockOpcode.h"
#endif

using namespace std;

class DifficultyOpcode : public BlockOpcode{
    public:
        DifficultyOpcode(long offset) : BlockOpcode(OpcodeID::DIFFICULTY){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 0;
        }
};