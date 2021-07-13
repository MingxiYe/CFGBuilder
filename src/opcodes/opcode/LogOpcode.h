#include<iostream>

#ifndef _OPCODE_H
#define _OPCODE_H
#include "../Opcode.h"
#endif



using namespace std;

class LogOpcode : public Opcode{
    private:
        int topicNumber;
    public:
        /**
         * Basic constructor for all LOG opcodes.
         * @param offset the offset in the bytecode, expressed in bytes.
         * @param topic_number the number of the event's topics. It must be between 0 and 4.
         */
        LogOpcode(long offset, int topic_number) : Opcode(OpcodeID::LOG){
            if(topic_number < 0 || topic_number > 4)
                throw "Events can have up to 4 topics";
            this->offset = offset;
            this->topicNumber = topic_number;
        }

        int getStackConsumed() const{
            return 2 + topicNumber;
        }

        int getStackGenerated() const{
            return 0;
        }

        string toString() const{
            return Opcode::toString() + to_string(topicNumber);
        }

        string getBytes() const{
            stringstream byte;
            byte << hex << int(Opcode::getOpcodeID()) + topicNumber;
            return byte.str();
        }

        int getTopicNumber() const{
            return topicNumber;
        }

        bool isSameOpcode(const Opcode* other) const{
            return this->opcodeID == other->getOpcodeID() && other->getTopicNumber() == this->topicNumber;
        }
};