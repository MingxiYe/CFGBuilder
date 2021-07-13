#include<iostream>
#include "SymbolicExecutionStack.h"

using namespace std;

// initializing static class menber
int SymbolicExecutionStack::MAX_STACK_SIZE = 1024;
int SymbolicExecutionStack::STACK_TAIL_SIZE = 48;
int SymbolicExecutionStack::STACK_TAIL_THRESHOLD = 200;

string SymbolicExecutionStack::stringAnd(string pa, string pb){
    long inta = 0, intb = 0;
    inta = stoi(pa, 0, 16);
    intb = stoi(pb, 0, 16);
    long intresult = inta&intb;
    string stringresult = "";
    int temp = 1;
    while(intresult/temp != 0){
        temp = temp * 16;
        if(intresult % temp < 10)
            stringresult = to_string(intresult % temp) + stringresult;
        else
            stringresult = char(intresult % temp + 87) + stringresult;
    }
    return stringresult;
}

SymbolicExecutionStack SymbolicExecutionStack::copy(){
    SymbolicExecutionStack result;
    result.stack = stack;
    return result;
}

string SymbolicExecutionStack::toString(){
    string result = "[";
    for(int i = 0; i < stack.size() - 1; i ++)
        result += stack[i] + ", ";
    result += stack[stack.size() - 1] + "]";
    return result;
}

void SymbolicExecutionStack::executeOpcode(Opcode* opcode){
    if(stack.size() > SymbolicExecutionStack::MAX_STACK_SIZE)
        throw "StackExceededException";
    if(opcode->getOpcodeID() == OpcodeID::PUSH)
        executePush(opcode);
    else if(opcode->getOpcodeID() == OpcodeID::DUP)
        executeDup(opcode);
    else if(opcode->getOpcodeID() == OpcodeID::SWAP)
        executeSwap(opcode);
    else if(opcode->getOpcodeID() == OpcodeID::POP)
        executePop(opcode);
    else if(opcode->getOpcodeID() == OpcodeID::AND)
        executeAnd(opcode);
    else{
        for(int i = 0; i < opcode->getStackConsumed(); i++)
            stack.pop_back();
        for(int i = 0; i < opcode->getStackGenerated(); i++)
            stack.push_back("");
    }
}

void SymbolicExecutionStack::executePush(Opcode* opcode){
    stack.push_back(opcode->getParameter());
}

void SymbolicExecutionStack::executeDup(Opcode* opcode){
    stack.push_back(stack[stack.size() - opcode->getValue()]);
}

void SymbolicExecutionStack::executeSwap(Opcode* opcode){
    int i = stack.size() - opcode->getValue() - 1;
    int j = stack.size() - 1;
    string tmp = stack[i];
    stack[i] = stack[j];
    stack[j] = tmp;
}

void SymbolicExecutionStack::executePop(Opcode* opcode){
    pop();
}

void SymbolicExecutionStack::executeAnd(Opcode* opcode){
    string a = pop();
    string b = pop();
    if(a != "" && b != "")
        stack.push_back(stringAnd(a,b));
    else
        stack.push_back("");
}

string SymbolicExecutionStack::peek(int position){
    string value = stack[stack.size() - 1 - position];
    if(value != "")
        return value;
    else
        throw "UnknownStackElementException";
}

string SymbolicExecutionStack::peek(){
    return peek(0);
}

bool SymbolicExecutionStack::operator ==(const SymbolicExecutionStack &other){
    if(this == &other) return true;
    if(this->stack.size() != other.stack.size()) return false;
    int stackTailSize = this->stack.size() >= SymbolicExecutionStack::STACK_TAIL_THRESHOLD + 100 ? SymbolicExecutionStack::STACK_TAIL_SIZE / ((this->stack.size() - SymbolicExecutionStack::STACK_TAIL_THRESHOLD) / 100) : SymbolicExecutionStack::STACK_TAIL_SIZE;
    if(this->stack.size() < stackTailSize && other.stack.size() < stackTailSize){
        for(int i = 0; i < this->stack.size(); i ++)
            if(this->stack[i] != other.stack[i])
                return false;
        return true;
    } else {
        for(int i = this->stack.size() - 1; i >= this->stack.size() - stackTailSize; i--)
            if(this->stack[i] != other.stack[i])
                return false;
        return true;
    }
}

string SymbolicExecutionStack::pop(){
    string value = stack[stack.size() - 1];
    stack.pop_back();
    return value;
}

int SymbolicExecutionStack::currentSize(){
    return stack.size();
}