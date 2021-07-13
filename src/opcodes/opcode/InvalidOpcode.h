#include<iostream>

#ifndef _OPCODE_H
#define _OPCODE_H
#include "../Opcode.h"
#endif



using namespace std;

class InvalidOpcode : public Opcode{
    private:
        string realOpcode;
    public:
        InvalidOpcode(long offset, string realOpcode) : Opcode(OpcodeID::INVALID){
            this->offset = offset;
            this->realOpcode = realOpcode;
        }

        int getStackGenerated() const{
            return 0;
        }

        int getStackConsumed() const{
            return 0;
        }

        string getBytes() const{
            return realOpcode;
        }
};