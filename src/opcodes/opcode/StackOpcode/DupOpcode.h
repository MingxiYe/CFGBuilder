#include<iostream>
#ifndef _STACKOPCODE_H
#define _STACKOPCODE_H
#include "../StackOpcode.h"
#endif

using namespace std;

class DupOpcode : public StackOpcode{
    private:
        int value;

    public:
        DupOpcode(long offset, int value) : StackOpcode(OpcodeID::DUP){
            if(value < 1 || value > 16)
                throw "DUP number must be between 1 and 16";
            this->offset = offset;
            this->value = value;
        }

        int getStackConsumed() const{
            return value;
        }

        int getStackGenerated() const{
            return Opcode::getStackGenerated() + value;
        }

        string getBytes() const{
            stringstream byte;
            byte << hex << OpcodeID::DUP + value - 1;
            return byte.str();
        }

        string toString() const{
            return Opcode::toString() + to_string(value);
        }

        int getValue() const{
            return value;
        }

        bool isSameOpcode(Opcode* other){
            return this->opcodeID == other->getOpcodeID() && other->getValue() == this->value;
        }
};