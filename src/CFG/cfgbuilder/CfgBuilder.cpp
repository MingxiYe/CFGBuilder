#include<iostream>
#include<math.h>
#include "CfgBuilder.h"

#include <algorithm>
#include <boost/regex.hpp>

using namespace std;


int CfgBuilder::LOOP_DEPTH = 1000;
bool CfgBuilder::REMOVE_ORPHAN_BLOCKS = true; // TODO experimental
int CfgBuilder::BLOCK_LIMIT = 200000; // TODO experimental: if a contract is too big we run the symbolic execution at most on this number of blocks

OpcodeID CfgBuilder::BASIC_BLOCK_DELIMITERS[7] = {
        OpcodeID::JUMP,
        OpcodeID::JUMPI,
        OpcodeID::STOP,
        OpcodeID::REVERT,
        OpcodeID::RETURN,
        OpcodeID::INVALID,
        OpcodeID::SELFDESTRUCT
};

vector<string> CfgBuilder::divide(const string& in, const string& delim, const int share) {
    boost::regex re{ delim };
    vector<string> result = {
            boost::sregex_token_iterator(in.begin(), in.end(), re, -1),
            boost::sregex_token_iterator()
    };
    for(int i = share; i < result.size(); i++)
        result[share - 1] += result[i];
    while(result.size() > share)
        result.pop_back();
    return result;
}


BasicBlock* CfgBuilder::getByOffset(vector<BasicBlock*> &basicBlocks, long offset){
    BasicBlock* target = NULL;
    for(int i = 0; i < basicBlocks.size(); i ++)
        if(basicBlocks[i]->getOffset() == offset){
            target = basicBlocks[i];
            break;
        }
    return target;
}

bool CfgBuilder::isContainEdge(vector<Edge> &visited, Edge &edge){
    bool isContained = false;
    for(Edge visitedEdge : visited){
        if(visitedEdge == edge){
            isContained = true;
            break;
        }
    }
    return isContained;
}

vector<BasicBlock*> CfgBuilder::generateBasicBlocks(Bytecode &bytecode){
    vector<BasicBlock*> result;
    BasicBlock *current = new BasicBlock();
    for(Opcode* opcode : bytecode.getOpcodes()){
        if(isContainDelimiters(opcode->getOpcodeID())){
            current->addOpcode(opcode);
            result.push_back(current);
            current = new BasicBlock(opcode->getOffset() + 1);
        }
        else if(opcode->getOpcodeID() == OpcodeID::JUMPDEST && current->getLength() != 0){
            result.push_back(current);
            current = new BasicBlock(opcode->getOffset());
            current->addOpcode(opcode);
        }
        else{
            current->addOpcode(opcode);
        }
    }
    if(current->getOpcodes().size() != 0)
        result.push_back(current);
    return result;
}

void CfgBuilder::calculateSuccessors(vector<BasicBlock*> &basicBlocks, CfgBuilderReport &buildReport){
    for(int i = 0; i < basicBlocks.size(); i++){
        BasicBlock* thisBlock = basicBlocks[i];
        vector<Opcode*> opcodes = thisBlock->getOpcodes();
        Opcode* lastOpcode = opcodes[opcodes.size() - 1];

        // Jump
        if(lastOpcode->getOpcodeID() == OpcodeID::JUMP && opcodes.size() > 1){
            // check if there is a push before
            if(opcodes[opcodes.size() - 2]->getOpcodeID() == OpcodeID::PUSH){
                Opcode* secondLastOpcode = opcodes[opcodes.size() - 2];
                long destinationOffset = 0;
                string parameter = secondLastOpcode->getParameter();
                destinationOffset = stol(parameter, 0, 16);
                bool temp = false;
                for(int j = 0; j < basicBlocks.size(); j++)
                    if(basicBlocks[j]->getOffset() == destinationOffset){
                        thisBlock->addSuccessor(basicBlocks[j]);
                        temp = true;
                        break;
                    }
                if(!temp)
                    buildReport.addDirectJumpError(lastOpcode->getOffset(), destinationOffset);
            }
        }
        // JUMPI
        else if(lastOpcode->getOpcodeID() == OpcodeID::JUMPI && opcodes.size() > 1){
            // Add the next one
            long nextOffset = lastOpcode->getOffset() + lastOpcode->getLength();
            BasicBlock* nextBasicBlock = getByOffset(basicBlocks, nextOffset);
            if(nextBasicBlock != NULL)
                thisBlock->addSuccessor(nextBasicBlock);
            // if there is a push before
            if(opcodes[opcodes.size() - 2]->getOpcodeID() == OpcodeID::PUSH){
                Opcode* secondLastOpcode = opcodes[opcodes.size() - 2];
                long destinationOffset = 0;
                string parameter = secondLastOpcode->getParameter();
                destinationOffset = stol(parameter, 0, 16);
                bool temp = false;
                for(int j = 0; j < basicBlocks.size(); j++)
                    if(basicBlocks[j]->getOffset() == destinationOffset){
                        thisBlock->addSuccessor(basicBlocks[j]);
                        temp = true;
                        break;
                    }
                if(!temp)
                    buildReport.addDirectJumpError(lastOpcode->getOffset(), destinationOffset);
            }
        }
        // Other delimiters
        else if(isContainDelimiters(lastOpcode->getOpcodeID())){
            // there is a control flow break, no successor added
        }
        // Exclude the last block which has no sequent
        else if(i == basicBlocks.size() - 1){
            // skip
        }
        // Else
        else{
            // It's a common operation, add the next
            BasicBlock* nextBasicBlock = basicBlocks[i + 1];
            thisBlock->addSuccessor(nextBasicBlock);
        }
    }
}

void CfgBuilder::resolveOrphanJumps(vector<BasicBlock*> &basicBlocks, CfgBuilderReport &buildReport){
    int blockCount = 0;
    // DFS on nodes visiting each edge only once
    vector<Edge> visited;
    BasicBlock* current = basicBlocks[0];
    SymbolicExecutionStack stack;
    int dfs_depth = 0;
    vector<QueueItem> queue;
    queue.push_back({current, stack, dfs_depth});

    while(queue.size()){
        QueueItem element = queue[queue.size() - 1];
        queue.pop_back();
        current = element.basicBlock;
        stack = element.stack;
        dfs_depth = element.dfsDepth;

        // Execute all opcodes except for the last
        for(int i = 0; i < current->getOpcodes().size() - 1; i++){
            Opcode* o = current->getOpcodes()[i];
            try{
                stack.executeOpcode(o);
            } catch(const char* msg){
                buildReport.addStackExceededError(o->getOffset());
            }
        }

        Opcode* lastOpcode = current->getLastOpcode();
        long nextOffset = 0;

        // Check for orphan jump and resolve
        if(lastOpcode->getOpcodeID() == OpcodeID::JUMP){
            try{
                nextOffset = stol(stack.peek(), 0, 16);
                BasicBlock* nextBB = getByOffset(basicBlocks, nextOffset);
                if(nextBB != NULL)
                    current->addSuccessor(nextBB);
                else
                    buildReport.addOrphanJumpTargetNullError(lastOpcode->getOffset(), nextOffset);
            } catch(const char* msg){
                buildReport.addOrphanJumpTargetUnknownError(lastOpcode->getOffset(), stack);
            }
        }

        // Execute last opcode
        blockCount++;
        if(blockCount >= CfgBuilder::BLOCK_LIMIT){
            buildReport.addBlockLimitError(CfgBuilder::BLOCK_LIMIT);
            return;
        }
        try{
            stack.executeOpcode(current->getOpcodes()[current->getOpcodes().size() - 1]);
        } catch(const char* msg){
            buildReport.addStackExceededError(lastOpcode->getOffset());
        }

        // Add next element for DFS
        if(dfs_depth < CfgBuilder::LOOP_DEPTH){
            if(lastOpcode->getOpcodeID() != OpcodeID::JUMP){
                for(BasicBlock* successor : current->getSuccessors()){
                    Edge edge = {current->getOffset(), successor->getOffset(), stack};
                    if(!isContainEdge(visited, edge)){
                        visited.push_back(edge);
                        queue.push_back({successor, stack.copy(), dfs_depth + 1});
                    }
                }
            }else if(nextOffset != 0){
                Edge edge = {current->getOffset(), nextOffset, stack};
                if(!isContainEdge(visited, edge)){
                    visited.push_back(edge);
                    BasicBlock* nextBB = getByOffset(basicBlocks, nextOffset);
                    if(nextBB != NULL)
                        queue.push_back({nextBB, stack.copy(), dfs_depth + 1});
                }
            }
        } else {
            buildReport.addLoopDepthExceededError(current->getOffset());
        }
    }
}

string CfgBuilder::removeRemainingData(vector<BasicBlock*> &basicBlocks, CfgBuilderReport &buildReport, Bytecode &bytecode){
    long firstInvalidBlock = basicBlocks[basicBlocks.size() - 1]->getOffset();
    vector<long> offsetList;
    for(BasicBlock* basicBlock : basicBlocks)
        offsetList.push_back(basicBlock->getOffset());

    for(long offset : offsetList){
        if(getByOffset(basicBlocks, offset)->getPredecessors().size() == 0 && getByOffset(basicBlocks, offset)->getBytes() == "fe")
            firstInvalidBlock = offset;
        if(offset >= firstInvalidBlock){
            int target;
            for(int i = 0; i < basicBlocks.size(); i++)
                if(basicBlocks[i]->getOffset() == offset)
                    target = i;
            basicBlocks.erase(basicBlocks.begin() + target);
        }
    }
    return bytecode.getBytes().substr((int)firstInvalidBlock * 2);
}

string CfgBuilder::removeOrphanBlocks(vector<BasicBlock*> &basicBlocks, CfgBuilderReport &buildReport, Bytecode &bytecode){
    long firstOffset = basicBlocks[basicBlocks.size() - 1]->getOffset() + basicBlocks[basicBlocks.size() - 1]->getLength();
    if(buildReport.getTotalErrors() == 0){
        // DFS to get the offset of the highest block connected to the root
        long candidateOffset = 0;
        vector<long> visited;
        vector<BasicBlock*> queue;
        queue.push_back(basicBlocks[0]);

        while(queue.size() != 0){
            BasicBlock* candidate = queue[queue.size() - 1];
            queue.pop_back();
            visited.push_back(candidate->getOffset());
            candidateOffset = candidate->getOffset() > candidateOffset ? candidate->getOffset() : candidateOffset;
            for(BasicBlock* successor : candidate->getSuccessors())
                if(find(visited.begin(), visited.end(), successor->getOffset()) == visited.end())
                    queue.push_back(successor);
        }

        // Every block with an higher offset than the candidate is removed
        vector<long> offsetList;
        for(BasicBlock* basicBlock : basicBlocks)
            offsetList.push_back(basicBlock->getOffset());
        for(long offset : offsetList){
            if(offset > candidateOffset){
                int target;
                for(int i = 0; i < basicBlocks.size(); i--)
                    if(basicBlocks[i]->getOffset() == offset)
                        target = i;
                basicBlocks.erase(basicBlocks.begin() + target);
            }
        }
    }
    return bytecode.getBytes().substr((int) firstOffset * 2);
}

void CfgBuilder::detectDispatcher(vector<BasicBlock*> &basicBlocks){
    long lastOffset = 0;
    for(BasicBlock* bb : basicBlocks) {
        if ((bb->getLastOpcode()->getOpcodeID() == OpcodeID::RETURN ||
            bb->getLastOpcode()->getOpcodeID() == OpcodeID::STOP) && bb->getOffset() > lastOffset)
            lastOffset = bb->getOffset();
    }
    long finalLastBlockOffset = lastOffset;
    for(BasicBlock* bb: basicBlocks)
        if(bb->getOffset() <= finalLastBlockOffset)
            bb->setType(BasicBlockType::DISPATCHER);

}

void CfgBuilder::detectFallBack(vector<BasicBlock*> &basicBlocks){
    // It's the highest successor of the highest successor
    // the fallback function exists iff it ends with a stop
    long maxSuccessorOffset = 0;
    for(BasicBlock* successor : basicBlocks[0]->getSuccessors())
        maxSuccessorOffset = successor->getOffset() > maxSuccessorOffset ? successor->getOffset() : maxSuccessorOffset;

    long maxSecondSuccessorOffset = maxSuccessorOffset;
    for(BasicBlock* secondSuccessor : getByOffset(basicBlocks, maxSuccessorOffset)->getSuccessors())
        maxSuccessorOffset = secondSuccessor->getOffset() > maxSuccessorOffset ? secondSuccessor->getOffset() : maxSuccessorOffset;

    // If it is a JumpDest only block the skip and mark the next one
    // If the block ends with a Revert then it's not a declared fallback
    BasicBlock* fallbackCandidate = getByOffset(basicBlocks, maxSecondSuccessorOffset);
    if(fallbackCandidate->getLength() == 1){
        for(BasicBlock* bb : fallbackCandidate->getSuccessors())
            if(bb->getLastOpcode()->getOpcodeID() != OpcodeID::REVERT)
                bb->setType(BasicBlockType::FALLBACK);
    }
    else if(fallbackCandidate->getLastOpcode()->getOpcodeID() != OpcodeID::REVERT)
        fallbackCandidate->setType(BasicBlockType::FALLBACK);
}

void CfgBuilder::validateCfg(vector<BasicBlock*> &basicBlocks, CfgBuilderReport &buildReport){
    // check whether there is only a tree
    int trees = 0;
    for(BasicBlock* basicBlock : basicBlocks)
        if(basicBlock->getPredecessors().size() == 0)
            trees++;
    if(trees != 1)
        buildReport.addMultipleRootNodesError(trees);
}

void CfgBuilder::addSuperNode(vector<BasicBlock*> &basicBlocks){
    BasicBlock* superNode = new BasicBlock(basicBlocks[basicBlocks.size() - 1]->getOffset() + basicBlocks[basicBlocks.size() - 1]->getLength());
    superNode->setType(BasicBlockType::EXIT);
    for(BasicBlock* bb : basicBlocks)
        if(bb->getSuccessors().size() == 0)
            bb->addSuccessor(superNode);
    basicBlocks.push_back(superNode);
}

Cfg* CfgBuilder::emptyCfg(){
    string data = "";
    return new Cfg(*(new Bytecode()), *(new vector<BasicBlock*>()), data, *(new CfgBuilderReport()));
}

Cfg* CfgBuilder::buildCfg(string binary){
    if(binary == "")
        return emptyCfg();

    CfgBuilderReport* buildReport = new CfgBuilderReport();
    // Remove child contracts
    string libraryPrefix = "";
    if(boost::regex_match(binary,boost::regex("^73[0-9a-fA-F]{40}3014[0-9a-fA-F]*$"))){
        libraryPrefix = binary.substr(0, 46);
        binary = binary.substr(46);
    }

    vector<string> mid = CfgBuilder::divide(binary, "(?=(60(60|80)604052))", 3);
    string childrenContracts = mid.size() > 2 ? mid[2] : "";

    // Parse and get remaining data
    pair<Bytecode*, string> sourceParsed = BytecodeParser::parse(libraryPrefix + mid[1]);
    Bytecode* bytecode = sourceParsed.first;
    string remainingData = sourceParsed.second + childrenContracts;

    // Begin building operations
    vector<BasicBlock*> basicBlocks = generateBasicBlocks(*bytecode);
    calculateSuccessors(basicBlocks, *buildReport);
    try{
        resolveOrphanJumps(basicBlocks, *buildReport);
    } catch (const char* msg){
        buildReport->addCriticalError();
    }
    string removedData = removeRemainingData(basicBlocks, *buildReport, *bytecode);
    if(CfgBuilder::REMOVE_ORPHAN_BLOCKS)
        removedData = removeOrphanBlocks(basicBlocks, *buildReport, *bytecode);

    detectDispatcher(basicBlocks);
    detectFallBack(basicBlocks);
    validateCfg(basicBlocks, *buildReport);
    addSuperNode(basicBlocks);

    // CREATE ADN RETURN THE CFG
    buildReport->stopTimer();
    string data = removedData + remainingData;
    return new Cfg(*bytecode, basicBlocks, data, *buildReport);
}

