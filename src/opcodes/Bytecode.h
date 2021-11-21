#include<iostream>
#ifndef _OPCODE_H
#define _OPCODE_H
#include "Opcode.h"
#endif
#include<vector>

using namespace std;

class Bytecode{
    protected:
        vector<Opcode*> opcodes;
        long offset = 0;
        long length = 0;
    public:
        /**
         * Creates an empty bytecode with offset 0
         */
        Bytecode(){ 
            new(this)Bytecode(0);
        }

        /**
         * Creates an empty bytecode with no opcodes
         * @param offset the offset of the bytecode, a.k.a. begin of the code
         */
        Bytecode(long offset){
            new(this)Bytecode(offset, *(new vector<Opcode*>()));
        }

        /**
         * Creates a bytecode with the given opcodes
         * @param opcodes The opcodes of the bytecode
         * @param offset the offset of the bytecode, a.k.a. begin of the code
         */
        Bytecode(long offset, vector<Opcode*> &opcodes){
            this->opcodes = opcodes;
            this->offset = offset;
            this->length = 0;
            for(Opcode* o : opcodes)
                this->length += o->getLength();
        }

        /**
         * Add a new Opcode to the bytecode
         * @param opcode the opcode to add
         */
        void addOpcode(Opcode *opcode){
            this->opcodes.push_back(opcode);
            this->length += opcode->getLength();
        }

        /**
         * Builds a hex string representing the bytecode
         * @return bytecode string
         */
        string getBytes() const{
            string result = "";
            for(int i = 0; i < opcodes.size(); i++)
                result += opcodes[i]->getBytes();
            return result;
        }

        /**
         * Creates a string representing the disassembled opcodes separated with a new line
         * @return output string
         */
        string toString() const {
            string result;
            for(int i = 0; i < opcodes.size(); i++)
                result += opcodes[i]->toString() + "\n";
            return result;
        }

        /**
         * Adds many opcode to the bytecode
         * @param opcodes opcodes to be added
         */
        void addAll(vector<Opcode*> &tempOpcodes){
            for(int i = 0; i < tempOpcodes.size(); i++)
                addOpcode(tempOpcodes[i]);
        }

        /**
        * Default getter for the length
        * @return length of the bytecode expressed in bytes
        */
        long getLength() const {
            return length;
        }

        Opcode* getOpcode(long i) const{
            return opcodes[i];
        }

        /**
        * Compares two instances bytecode based on their offset
        * @param other other bytecode to compare
        * @return the comparison of the offset
        */
        int comapreTo(const Bytecode &other) const {
            if(this->offset == other.offset)
                return 0;
            else if(this->offset > other.offset)
                return 1;
            else
                return -1;
        }

        /**
         * Default getter for the offset
         * @return the offset of the bytecode
         */
        long getOffset() const{
            return offset;
        }

        /**
         * Default getter for the opcodes
         * @return opcodes
         */
        vector<Opcode*> getOpcodes() const{
            return opcodes;
        }

        /**
         * Gets the last opcode of the bytecode.
         * @return the last opcode
         */
        Opcode* getLastOpcode() const{
            return opcodes[opcodes.size() - 1];
        }

        /**
         * Check if pattern is a sub-list of opcodes inside the bytecode. A null opcode stands for a generic opcode
         * @param pattern the list of opcode
         * @return if the bytecode contains the pattern
         */
        bool checkPattern(const vector<Opcode*> &pattern) const{
            int checkPointer = 0;
            if(pattern.size() == 0)
                return true;
            for(Opcode* opcode : opcodes){
                if(opcode->isSameOpcode(pattern[checkPointer]))
                    checkPointer += 1;
                else
                    checkPointer = 0;
                if(checkPointer == pattern.size())
                    return true;
            }
        }
};