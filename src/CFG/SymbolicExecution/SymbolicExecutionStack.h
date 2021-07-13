#include<iostream>
#include<math.h>
#ifndef _UTILS_H
#define _UTILS_H
#include "../../Utils/utils.h"
#endif

using namespace std;

class SymbolicExecutionStack{
    private:
        static int MAX_STACK_SIZE;
        static int STACK_TAIL_SIZE;
        static int STACK_TAIL_THRESHOLD;
        vector<string> stack;

        string stringAnd(string pa, string pb);

    public:

        SymbolicExecutionStack(){}

        SymbolicExecutionStack copy();

        string toString();

        void executeOpcode(Opcode* opcode);

        void executePush(Opcode* opcode);

        void executeDup(Opcode* opcode);

        void executeSwap(Opcode* opcode);

        void executePop(Opcode* opcode);

        void executeAnd(Opcode* opcode);

        string peek(int position);

        string peek();

        bool operator ==(const SymbolicExecutionStack &other);

        string pop();

        int currentSize();
};
