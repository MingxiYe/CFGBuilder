#include<iostream>
#ifndef _BYTECODE_H
#define _BYTECODE_H
#include "Bytecode.h"
#endif

#include "BasicBlockType.h"

using namespace std;

class BasicBlock : public Bytecode{
private:
    vector<BasicBlock*> predecessors;
    vector<BasicBlock*> successors;
    int stackBalance = 0;
    BasicBlockType type;

    int calculateStackBalance() const{
        int balance = 0;
        for(Opcode* o : this->getOpcodes()){
            balance -= o->getStackConsumed();
            balance += o->getStackGenerated();
        }
        return balance;
    }

public:
    /**
     * Default constructor with offset 0 and no opcodes
     */
    BasicBlock(){
        new(this)BasicBlock( 0);
    }

    /**
     * Default constructor with no opcodes
     * @param offset position in the bytecode
     */
    BasicBlock(long offset){
        new(this)BasicBlock(offset, *(new vector<Opcode*>()));
    }

    /**
     * Default constructor with offset and opcodes
     * @param offset position in the code
     * @param opcodes list of opcodes
     */
    BasicBlock(long offset, vector<Opcode*> &opcodes) : Bytecode(offset, opcodes){
        // Bytecode(offset, opcodes);
        this->type = BasicBlockType::COMMON;
    }

    /**
     * Default getter for the successors of the block
     * @return successors blocks
     */
    vector<BasicBlock*> getSuccessors() const{
        return successors;
    }

    /**
     * Default getter for the predecessors of the block
     * @return predecessors blocks
     */
    vector<BasicBlock*> getPredecessors() const{
        return predecessors;
    }

    /**
     * Default getter for the stack balance. It represents the number of elements added/removed to the stack if the entire block is executed
     * @return the stack balance
     */
    int getStackBalance() const{
        return stackBalance;
    }

    /**
     * Adds a successor to the block. The block is also added to the successor block as a predecessor
     * @param next the next block
     */
    void addSuccessor(BasicBlock* next){
        this->successors.push_back(next);
        next->predecessors.push_back(this);
    }

    /**
     * Adds the opcode and updates the stack balance
     * @param opcode the opcode to add
     */
    void addOpcode(Opcode* opcode){
        Bytecode::addOpcode(opcode);
        this->stackBalance -= opcode->getStackConsumed();
        this->stackBalance += opcode->getStackGenerated();
    }

    /**
     * Adds the opcodes and updates the stack balance
     * @param opcodes opcodes to be added
     */
    void addAll(vector<Opcode*> &opcodes){
        Bytecode::addAll(opcodes);
        this->stackBalance = calculateStackBalance();
    }

    /**
     * Default setter for the type
     * @param type block's type
     */
    void setType(BasicBlockType type){
        this->type = type;
    }

    /**
     * Default getter for the type
     * @return block's type
     */
    BasicBlockType getType() const{
        return type;
    }

    /**
     * Default representation of the block as bytecode. The special case is the exit block
     * @return block's string representation
     */
    string toString() const{
        if(type == BasicBlockType::EXIT) {
            return to_string(getOffset()) + ": EXIT BLOCK";
        }else{
            return Bytecode::toString();
        }

    }
};