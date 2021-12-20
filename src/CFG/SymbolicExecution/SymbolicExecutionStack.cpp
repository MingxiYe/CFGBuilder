#include<iostream>
#include<bitset>
#include "SymbolicExecutionStack.h"

using namespace std;

// initializing static class menber
int SymbolicExecutionStack::MAX_STACK_SIZE = 1024;
int SymbolicExecutionStack::STACK_TAIL_SIZE = 48;
int SymbolicExecutionStack::STACK_TAIL_THRESHOLD = 200;

string SymbolicExecutionStack::stringAnd(string pa, string pb){
    int size = pa.size() > pb.size() ? pb.size() : pa.size();
    string stringresult = "";
    for(int i = 0; i < size; i++){
        int paa = pa[i] > 96 ? pa[i] - 87 : pa[i] - 48;
        int pbb = pb[i] > 96 ? pb[i] - 87 : pb[i] - 48;
        string temp = bitset<4>(paa&pbb).to_string();
        stringresult = temp + stringresult;
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
    string temp1 = ", ";
    string temp2 = "]";
    if(stack.size() == 0)
        return string("[]");
    for(int i = 0; i < stack.size() - 1; i ++){
        string temp3 = stack[i] == "" ? "null" : stack[i];
        result = result + temp3;
        result = result + temp1;
    }
    string temp = stack[stack.size() - 1] == "" ? "null" : stack[stack.size() - 1];
    result += temp;
    result += temp2;
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

string SymbolicExecutionStack::peek(int position = 0){
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
    for(int i = 0; i < this->stack.size(); i++)
        if(this->stack[i] != other.stack[i])
            return false;
    return true;
}

string SymbolicExecutionStack::pop(){
    string value = stack[stack.size() - 1];
    stack.pop_back();
    return value;
}

int SymbolicExecutionStack::currentSize(){
    return stack.size();
}