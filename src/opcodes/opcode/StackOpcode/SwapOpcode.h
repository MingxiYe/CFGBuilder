#include<iostream>
#ifndef _STACKOPCODE_H
#define _STACKOPCODE_H
#include "../StackOpcode.h"
#endif

using namespace std;

class SwapOpcode : public StackOpcode{
    private:
        int value;
    
    /**
     * Basic constructor for all SWAP opcodes.
     * @param offset the offset in the bytecode, expressed in bytes.
     * @param value the number of the stack value to be swapped with the last. It must be between 1 and 16.
     */
    public:
        SwapOpcode(long offset, int value) : StackOpcode(OpcodeID::SWAP){
            if(value < 1 || value > 16)
                throw "swap number must be between 1 and 16";
            this->offset = offset;
            this->value = value;
        }

        int getStackConsumed() const{
            return value + 1;
        }

        int getStackGenerated() const{
            return Opcode::getStackGenerated() + value;
        }

        string toString() const{
            return to_string(offset) + ": " + Opcode::getName() + to_string(value);
        }

        string getBytes() const{
            stringstream byte;
            byte << hex << int(Opcode::getOpcodeID()) + value - 1;
            return byte.str();
        }

        int getValue() const{
            return value;
        }

        bool isSameOpcode(Opcode* other){
            return this->opcodeID == other->getOpcodeID() && other->getValue() == this->value;
        }
};