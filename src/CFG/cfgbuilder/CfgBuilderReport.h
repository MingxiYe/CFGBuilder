#include<iostream>
#include<ctime>
#ifndef _SYMBOLICEXECUTIONSTACK_H
#define _SYMBOLICEXECUTIONSTACK_H
#include "../SymbolicExecution/SymbolicExecutionStack.h"
#endif
using namespace std;

class CfgBuilderReport{
    private:
        int directJumpTargetErrors;
        int orphanJumpTargetNullErrors;
        int orphanJumpTargetUnknownErrors;
        int loopDepthExceededErrors;
        int multipleRootNodesErrors;
        int stackExceededErrors;
        int blockLimitErrors;
        int criticalErrors;
        string errorLog;
        long buildTimeMillis;

    public:
        /**
         * Default constructor which sets all values to 0
         */
        CfgBuilderReport(){
            buildTimeMillis = time(0);
            directJumpTargetErrors = 0;
            orphanJumpTargetNullErrors = 0;
            orphanJumpTargetUnknownErrors = 0;
            loopDepthExceededErrors = 0;
            multipleRootNodesErrors = 0;
            stackExceededErrors = 0;
            blockLimitErrors = 0;
            criticalErrors = 0;
            errorLog = "";
        }

        /**
         * Adds a direct jump error. They are caused by a jump to an offset which is not a basic block
         * @param sourceOffset offset of the opcode that generated the error
         * @param destinationOffset destination offset for the jump
         */
        void addDirectJumpError(long sourceOffset, long destinationOffset){
            directJumpTargetErrors++;
            errorLog += "Direct jump unresolvable at " + to_string(sourceOffset) + ", block " + to_string(destinationOffset) + " does not exists\n";
        }

        /**
         * Adds an orphan jump target null error. They are caused by a jump to an offset which is not a basic block
         * @param sourceOffset offset of the opcode that generated the error
         * @param destinationOffset destination offset for the jump
         */
        void addOrphanJumpTargetNullError(long sourceOffset, long destinationOffset){
            orphanJumpTargetNullErrors++;
            errorLog += "Orphan jump unresolvable at " + to_string(sourceOffset) + ", block " + to_string(destinationOffset) + " does not exists\n";
        }

        /**
         * Adds an orphan jump target unknown error. They are caused by a jump with an unknown value on the symbolic execution stack
         * @param sourceOffset offset of the opcode that generated the error
         * @param stack current state of the symbolic execution stack
         */
        void addOrphanJumpTargetUnknownError(long sourceOffset, SymbolicExecutionStack &stack){
            orphanJumpTargetUnknownErrors++;
            errorLog += "Orphan jump unresolvable at " + to_string(sourceOffset) + ", symbolic execution found an unknown value\nStack: " + stack.toString() + "\n";
        }

        /**
         * Adds a loop depth exceeded error. They are caused by the DFS if it becomes too deep
         * @param offset offset of the opcode that generated the error
         */
        void addLoopDepthExceededError(long offset){
            loopDepthExceededErrors++;
            errorLog += "Loop depth exceeded at " + to_string(offset) + "\n";
        }

        /**
         * Adds a multiple root nodes error. They are caused by the cfg validator if there are more root nodes (a.k.a. nodes without predecessors)
         * @param trees the number of roots in the cfg
         */
        void addMultipleRootNodesError(int trees) {
            multipleRootNodesErrors++;
            errorLog += "Warning: the CFG has " + to_string(trees) + " root nodes (a.k.a. nodes without predecessors)\n";
        }

        /**
         * Adds a stack exceeded error. They are caused if the symbolic execution stack exceeded the 1024 limit
         * @param offset offset of the opcode that generated the error
         */
        void addStackExceededError(long offset) {
            stackExceededErrors++;
            errorLog += "Symbolic stack exceeded the limit at " + to_string(offset) + "\n";
        }

        /**
         * Adds a block limit error. It's caused if the DFS explores too many nodes
         * @param blockLimit the number of explored blocks
         */
        void addBlockLimitError(int blockLimit) {
            blockLimitErrors++;
            errorLog += "Symbolic execution explored too many blocks: " + to_string(blockLimit) + "\n";
        }

        /**
         * Adds a critical error. They are caused by any exception
         * @param exception the critical error
         */
        // unsolved
        void addCriticalError(){
            criticalErrors++;
        }

        /**
         * Stops the timer and updates the build time
         */
        void stopTimer(){
            buildTimeMillis = time(0) - buildTimeMillis;
        }

        /**
         * Prints all the errors
         * @return errors count for each one
         */
        string toString(){
            return "Direct jump target errors: " + to_string(directJumpTargetErrors) +
                    "\nOrphan jump target null errors: " + to_string(orphanJumpTargetNullErrors) +
                    "\nOrphan jump target unknown errors: " + to_string(orphanJumpTargetUnknownErrors) +
                    "\nMultiple root nodes errors: " + to_string(multipleRootNodesErrors) +
                    "\nSymbolic execution stack limit exceeded errors: " + to_string(stackExceededErrors) +
                    "\nBlock limit errors: " + to_string(blockLimitErrors) +
                    "\nCritical errors: " + to_string(criticalErrors);
        }

        /**
         * gets the sum of the jump-related error
         * @return the sum of the errors
         */
        int getTotalJumpError(){
            return directJumpTargetErrors +
                    orphanJumpTargetUnknownErrors +
                    orphanJumpTargetNullErrors +
                    loopDepthExceededErrors +
                    blockLimitErrors;
        }

        int getTotalErrors(){
            return directJumpTargetErrors +
                    orphanJumpTargetNullErrors +
                    orphanJumpTargetUnknownErrors +
                    loopDepthExceededErrors +
                    multipleRootNodesErrors +
                    stackExceededErrors +
                    criticalErrors +
                    blockLimitErrors;
        }

        /**
         * gets the multiple root nodes errors counter
         * @return the errors count
         */
        int getMultipleRootNodesErrors() {
            return multipleRootNodesErrors;
        }

        int getBlockLimitErrors() {
            return blockLimitErrors;
        }

        int getCriticalErrors() {
            return criticalErrors;
        }

        long getBuildTimeMillis() {
            return buildTimeMillis;
        }

        int getDirectJumpTargetErrors() {
            return directJumpTargetErrors;
        }

        int getOrphanJumpTargetNullErrors() {
            return orphanJumpTargetNullErrors;
        }

        int getOrphanJumpTargetUnknownErrors() {
            return orphanJumpTargetUnknownErrors;
        }

        int getLoopDepthExceededErrors() {
            return loopDepthExceededErrors;
        }

        int getStackExceededErrors() {
            return stackExceededErrors;
        }

        /**
        * Gets the complete error log
        * @return complete error log
        * lack of CriticalError
        */
        string getLog(){
            return errorLog;
        }
};