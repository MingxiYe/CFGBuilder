#include<iostream>
#include "Cfg.h"
#include "../../opcodes/BytecodeParser.h"
#ifndef _SYMBOLICEXECUTIONSTACK_H
#define _SYMBOLICEXECUTIONSTACK_H
#include "../SymbolicExecution/SymbolicExecutionStack.h"
#endif
#include<vector>
using namespace std;

struct Edge
{
    long currentOffset;
    long successorOffset;
    SymbolicExecutionStack stack;

    bool operator ==(const Edge &other){
        return currentOffset == other.currentOffset && successorOffset == other.successorOffset && stack == other.stack;
    }
};

struct QueueItem
{
    BasicBlock* basicBlock;
    SymbolicExecutionStack stack;
    int dfsDepth;
};

class CfgBuilder{
    private:
        /**
         * Set of delimiters: the Opcodes ID which represents the end of a basic block
         */
        static OpcodeID BASIC_BLOCK_DELIMITERS[7];
        static int LOOP_DEPTH;
        static bool REMOVE_ORPHAN_BLOCKS; // TODO experimental
        static int BLOCK_LIMIT; // TODO experimental: if a contract is too big we run the symbolic execution at most on this number of blocks



        static bool isContainDelimiters(OpcodeID opcodeID){
            for(int i = 0; i < 7; i++)
                if(opcodeID == CfgBuilder::BASIC_BLOCK_DELIMITERS[i])
                    return true;
            return false;
        }

        static BasicBlock* getByOffset(vector<BasicBlock*> &basicBlocks, long offset);

        static bool isContainEdge(vector<Edge> &visited, Edge &edge);

        static vector<BasicBlock*> generateBasicBlocks(Bytecode &bytecode);
        static void calculateSuccessors(vector<BasicBlock*> &basicBlocks, CfgBuilderReport &buildReport);
        static void resolveOrphanJumps(vector<BasicBlock*> &basicBlocks, CfgBuilderReport &buildReport);
        static string removeRemainingData(vector<BasicBlock*> &basicBlocks, CfgBuilderReport &buildReport, Bytecode &bytecode);
        static string removeOrphanBlocks(vector<BasicBlock*> &basicBlocks, CfgBuilderReport &buildReport, Bytecode &bytecode);
        static void detectDispatcher(vector<BasicBlock*> &basicBlocks);
        static void detectFallBack(vector<BasicBlock*> &basicBlocks);
        static void validateCfg(vector<BasicBlock*> &basicBlocks, CfgBuilderReport &buildReport);
        static void addSuperNode(vector<BasicBlock*> &basicBlocks);
    public:
        /**
         * Builds an empty cfg
         * @return an empty cfg
         */
        static Cfg* emptyCfg();

        /**
         * Builds a cfg from the opcodes.
         * <br>
         * The process to generate it consists of this phases:
         * <ul>
         *     <li>Bytecode parsing</li>
         *     <li>Basic block generation</li>
         *     <li>Fist successors calculation, for easy resolvable jumps</li>
         *     <li>Advanced successors calculation, with the symbolic execution stack</li>
         *     <li>Remaining data removal</li>
         *     <li>Detached blocks removal</li>
         *     <li>Dispatcher detection</li>
         *     <li>Fallback function detection</li>
         *     <li>Super node creation</li>
         * 
         *     <li>Cfg validation</li>
         * </ul>
         * The built cfg contains also a build report, which counts all the errors occurred during the building process.
         * @param binary hexadecimal string representing the bytecode
         * @return the built cfg
         */
        static Cfg* buildCfg(string binary);

        static vector<string> divide(const string& in, const string& delim, const int share);
};