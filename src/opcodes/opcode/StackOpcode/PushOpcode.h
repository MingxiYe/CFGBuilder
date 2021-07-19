#include<iostream>
#ifndef _STACKOPCODE_H
#define _STACKOPCODE_H
#include "../StackOpcode.h"
#endif
#include<vector>
using namespace std;

class PushOpcode : public StackOpcode{
    protected:
        int parameterLength;
        string parameter; //this is a big integer in hex

    public:
        /**
         * Basic constructor for all Push opcodes
         * @param offset the offset in the bytecode, expressed in bytes
         * @param parameter_length the number of the PUSH. It must be between 1 and 32
         * @param parameter the number pushed to the stack.
         */
        PushOpcode(long offset, int parameter_length, string parameter) : StackOpcode(OpcodeID::PUSH){
            if(parameter_length < 1 || parameter_length > 32)
                throw "Push parameter length must be between 1 and 32 bytes";
            this->offset = offset;
            this->parameterLength = parameter_length;
            this->parameter = parameter;
        }

        PushOpcode(long offset, int parameterLength) : StackOpcode(OpcodeID::PUSH){
            this->offset = offset;
            this->parameterLength = parameterLength;
        }

        string getParameter() const{
            return parameter;
        }

        int getParameterLength() const{
            return parameterLength;
        }

        int getLength() const{
            return StackOpcode::getLength() + parameterLength;
        }

        int getStackConsumed() const{
            return 0;
        }

        string toString() const{
            return to_string(offset) + ": " + Opcode::getName() + to_string(parameterLength) + " 0x" + getBytes().substr(2);
        }

        string getBytes() const{
            OpcodeID pushX = Opcode::getOpcodeID();
            stringstream byte;
            byte << hex << int(pushX) + parameterLength - 1;
            string result = byte.str();
            // print the argument with the right number of leading zeros
            int zeros = parameterLength * 2 - parameter.size();
            for(int i = 0; i < zeros; i++)
                result += "0";
            for(int i = 0; i < parameter.size(); i++)
                result += parameter[i];
            return result;
        }

        bool isSameOpcode(const Opcode &other) const{
            return this->opcodeID == other.getOpcodeID() && other.getParameterLength() == this->parameterLength;
        }
};