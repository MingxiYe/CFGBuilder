#include<iostream>
#include "../../opcodes/BasicBlock.h"
#include "CfgBuilderReport.h"

using namespace std;

class Cfg{
private:
    vector<BasicBlock*> basicBlocks;
    Bytecode bytecode;
    CfgBuilderReport buildReport;
    string remainingData;

public:
    Cfg(Bytecode &bytecode, vector<BasicBlock*> &basicBlocks, string &remainingData, CfgBuilderReport &buildReport){
        this->bytecode = bytecode;
        this->basicBlocks = basicBlocks;
        this->remainingData = remainingData;
        this->buildReport = buildReport;
    }

    /**
     * Default iterator over the basic blocks
     * @return vector<BasicBlock*> basicBlocks
     */
    vector<BasicBlock*> getBasicBlocksForIteration() {
        return basicBlocks;
    }

    /**
     * Default getter for the bytecode
     * @return bytecode
     */
    Bytecode getBytecode(){
        return bytecode;
    }

    /**
     * Default getter for the block with a certain offset
     * @param offset the offset of the block
     * @return the block with that offset
     */
    BasicBlock* getBasicBlock(long offset){
        for(BasicBlock* basicBlock : basicBlocks){
            if(basicBlock->getOffset() == offset)
                return basicBlock;
        }
        return NULL;
    }

    /**
     * Default getter for the build report
     * @return build report
     */
    CfgBuilderReport getBuildReport(){
        return buildReport;
    }

    /**
     * Default getter for the remaining data
     * @return remaining data
     */
    string getRemainingData() {
        return remainingData;
    }

    /**
     * Generates the adjacency list for the graph. It is a map which associates to each offset a list with the offsets of the successors.
     * @return the adjacency list
     */
    vector<pair<long, vector<long>>> getSuccessorsMap(){
        vector<pair<long, vector<long>>> successors;
        for(BasicBlock* basicBlock : basicBlocks){
            vector<long> temp;
            for(BasicBlock* successor : basicBlock->getSuccessors())
                temp.push_back(successor->getOffset());
            successors.push_back(make_pair(basicBlock->getOffset(), temp));
        }
        return successors;
    }
};