#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include "OpcodeID.h"

using namespace std;

class Opcode{
    protected:
        OpcodeID opcodeID;
        long offset;
    public:
        Opcode(OpcodeID opcodeID){
            this->opcodeID = opcodeID; 
        }

        /**
         * Get the bytecode length of the opcode.
         *
         * Default value is 1, but the PUSH statement overrides this method.
         * @return length in byte of the opcode.
         */
        virtual int getLength() const {
            return 1;
        }

        /**
         * Get the number of elements that the opcode consumes. They have to be already in the stack.
         * @return consumed stack elements.
         */
        virtual int getStackConsumed() const = 0;

        /**
         * Get the number of elements that the opcode generates on the stack.
         *
         * Default value is 1, but some opcodes override this method
         * @return generated stack elements.
         */
        virtual int getStackGenerated() const {
            return 1;
        }

        /**
         * Default getter for opcodeID
         * @return opcodeID
         */
        OpcodeID getOpcodeID() const {
            return opcodeID;
        }

        /**
         * Default getter for Name
         * @return name of the opcode
         */
        string getName() const {
            switch(opcodeID){
            case 0x00: return "STOP"; break;
            case 0x01: return "ADD"; break;    
            case 0x02: return "MUL"; break;
            case 0x03: return "SUB"; break;
            case 0x04: return "DIV"; break;
            case 0x05: return "SDIV"; break;
            case 0x06: return "MOD"; break;
            case 0x07: return "SMOD"; break;
            case 0x08: return "ADDMOD"; break;
            case 0x09: return "MULMOD"; break;
            case 0x0a: return "EXP"; break;
            case 0x0b: return "SIGNEXTEND"; break;
            case 0x10: return "LT"; break;
            case 0x11: return "GT"; break;
            case 0x12: return "SLT"; break;
            case 0x13: return "SGT"; break;
            case 0x14: return "EQ"; break;
            case 0x15: return "ISZERO"; break;
            case 0x16: return "AND"; break;
            case 0x17: return "OR"; break;
            case 0x18: return "XOR"; break;
            case 0x19: return "NOT"; break;
            case 0x1a: return "BYTE"; break;
            case 0x1b: return "SHL"; break;
            case 0x1c: return "SHR"; break;
            case 0x1d: return "SAR"; break;
            case 0x20: return "SHA3"; break;
            case 0x30: return "ADDRESS"; break;
            case 0x31: return "BALANCE"; break;
            case 0x32: return "ORIGIN"; break;
            case 0x33: return "CALLER"; break;
            case 0x34: return "CALLVALUE"; break;
            case 0x35: return "CALLDATALOAD"; break;
            case 0x36: return "CALLDATASIZE"; break;
            case 0x37: return "CALLDATACOPY"; break;
            case 0x38: return "CODESIZE"; break;
            case 0x39: return "CODECOPY"; break;
            case 0x3a: return "GASPRICE"; break;
            case 0x3b: return "EXTCODESIZE"; break;
            case 0x3c: return "EXTCODECOPY"; break;
            case 0x3d: return "RETURNDATASIZE"; break;
            case 0x3e: return "RETURNDATACOPY"; break;
            case 0x3f: return "EXTCODEHASH"; break;
            case 0x40: return "BLOCKHASH"; break;
            case 0x41: return "COINBASE"; break;
            case 0x42: return "TIMESTAMP"; break;
            case 0x43: return "NUMBER"; break;
            case 0x44: return "DIFFICULTY"; break;
            case 0x45: return "GASLIMIT"; break;
            case 0x46: return "CHAINID"; break;
            case 0x47: return "SELFBALANCE"; break;
            case 0x50: return "POP"; break;
            case 0x51: return "MLOAD"; break;
            case 0x52: return "MSTORE"; break;
            case 0x53: return "MSTORE8"; break;
            case 0x54: return "SLOAD"; break;
            case 0x55: return "SSTORE"; break;
            case 0x56: return "JUMP"; break;
            case 0x57: return "JUMPI"; break;
            case 0x58: return "PC"; break;
            case 0x59: return "MSIZE"; break;
            case 0x5a: return "GAS"; break;
            case 0x5b: return "JUMPDEST"; break;
            case 0x60: return "PUSH"; break;
            case 0x80: return "DUP"; break;
            case 0x90: return "SWAP"; break;
            case 0xa0: return "LOG"; break;
            case 0xf0: return "CREATE"; break;
            case 0xf1: return "CALL"; break;
            case 0xf2: return "CALLCODE"; break;
            case 0xf3: return "RETURN"; break;
            case 0xf4: return "DELEGATECALL"; break;
            case 0xfa: return "STATICCALL"; break;
            case 0xfd: return "REVERT"; break;
            case 0xfe: return "INVALID"; break;
            case 0xff: return "SELFDESTRUCT"; break;
            
            default:
                return "unknown";
            };
        }

        /**
         * Assembles the opcode giving the bytes representation
         * @return bytes representation
         */
        virtual string getBytes() const {
            stringstream byte;
            byte << hex << opcodeID;
            if(opcodeID < 16)
                return "0" + byte.str();
            return byte.str();
        }

        /**
         * Default getter for the offset, the position in the code
         * @return offset of the opcode
         */
        virtual long getOffset() const {
            return offset;
        }

        /**
         * String representation of the opcode, with offset and name
         *
         * e.g. "0: PUSH1 60"
         * @return "offset: opcode"
         */
        virtual string toString() const {
            return to_string(offset) + ": " + this->getName();
        }

        /**
         * Checks whether the other opcode represents the same one, even if with a different offset
         * @param other opcode to test
         * @return if they represents the same opcode
         */
        virtual bool isSameOpcode(const Opcode* other) const {
            return this->opcodeID == other->opcodeID;
        }


        // for PushOpcode.h
        virtual string getParameter() const{
            return string();
        }
        
        virtual int getParameterLength() const{return -1;}

        // for LogOpcode.h
        virtual int getTopicNumber() const{return -1;}

        // for DupOpcode.h and SwapOpcode.h
        virtual int getValue() const{return -1;}
};