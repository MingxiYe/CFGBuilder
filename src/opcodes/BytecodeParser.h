#include<iostream>
#ifndef _UTILS_H
#define _UTILS_H
#include "../Utils/utils.h"
#endif
#ifndef _BYTECODE_H
#define _BYTECODE_H
#include "Bytecode.h"
#endif

class BytecodeParser{
    private:
        static Opcode* parseOpcode(string byteOpcode, int offset){
            uint8_t byte = stol(byteOpcode, 0, 16);
            // DUP
            if(byte >= OpcodeID::DUP && byte <= OpcodeID::DUP + 15){
                int value = byte - OpcodeID::DUP + 1;
                return new DupOpcode(offset, value);
            }

            // SWAP
            if(byte >= OpcodeID::SWAP && byte <= OpcodeID::SWAP + 15){
                int value = byte - OpcodeID::SWAP + 1;
                return new SwapOpcode(offset, value);
            }

            // LOG
            if(byte >= OpcodeID::LOG && byte <= OpcodeID::LOG + 4){
                int topicNumber = byte - OpcodeID::LOG;
                return new LogOpcode(offset, topicNumber);
            }

            switch(byte){
                case 0x00:
                    return new StopOpcode(offset);
                case 0x01:
                    return new AddOpcode(offset);
                case 0x02:
                    return new MulOpcode(offset);
                case 0x03:
                    return new SubOpcode(offset);
                case 0x04:
                    return new DivOpcode(offset);
                case 0x05:
                    return new SDivOpcode(offset);
                case 0x06:
                    return new ModOpcode(offset);
                case 0x07:
                    return new SModOpcode(offset);
                case 0x08:
                    return new AddModOpcode(offset);
                case 0x09:
                    return new MulModOpcode(offset);
                case 0x0a:
                    return new ExpOpcode(offset);
                case 0x0b:
                    return new SignExtendOpcode(offset);
                case 0x10:
                    return new LTOpcode(offset);
                case 0x11:
                    return new GTOpcode(offset);
                case 0x12:
                    return new SLTOpcode(offset);
                case 0x13:
                    return new SGTOpcode(offset);
                case 0x14:
                    return new EQOpcode(offset);
                case 0x15:
                    return new IsZeroOpcode(offset);
                case 0x16:
                    return new AndOpcode(offset);
                case 0x17:
                    return new OrOpcode(offset);
                case 0x18:
                    return new XorOpcode(offset);
                case 0x19:
                    return new NotOpcode(offset);
                case 0x1a:
                    return new ByteOpcode(offset);
                case 0x1b:
                    return new SHLOpcode(offset);
                case 0x1c:
                    return new SHROpcode(offset);
                case 0x1d:
                    return new SAROpcode(offset);
                case 0x20:
                    return new SHA3Opcode(offset);
                case 0x30:
                    return new AddressOpcode(offset);
                case 0x31:
                    return new BalanceOpcode(offset);
                case 0x32:
                    return new OriginOpcode(offset);
                case 0x33:
                    return new CallerOpcode(offset);
                case 0x34:
                    return new CallValueOpcode(offset);
                case 0x35:
                    return new CallDataLoadOpcode(offset);
                case 0x36:
                    return new CallDataSizeOpcode(offset);
                case 0x37:
                    return new CallDataCopyOpcode(offset);
                case 0x38:
                    return new CodeSizeOpcode(offset);
                case 0x39:
                    return new CodeCopyOpcode(offset);
                case 0x3a:
                    return new GasPriceOpcode(offset);
                case 0x3b:
                    return new ExtCodeSizeOpcode(offset);
                case 0x3c:
                    return new ExtCodeCopyOpcode(offset);
                case 0x3d:
                    return new ReturnDataSizeOpcode(offset);
                case 0x3e:
                    return new ReturnDataCopyOpcode(offset);
                case 0x3f:
                    return new ExtCodeHashOpcode(offset);
                case 0x40:
                    return new BlockHashOpcode(offset);
                case 0x41:
                    return new CoinBaseOpcode(offset);
                case 0x42:
                    return new TimeStampOpcode(offset);
                case 0x43:
                    return new NumberOpcode(offset);
                case 0x44:
                    return new DifficultyOpcode(offset);
                case 0x45:
                    return new GasLimitOpcode(offset);
                case 0x46:
                    return new ChainIdOpcode(offset);
                case 0x47:
                    return new SelfBalanceOpcode(offset);
                case 0x50:
                    return new PopOpcode(offset);
                case 0x51:
                    return new MLoadOpcode(offset);
                case 0x52:
                    return new MStoreOpcode(offset);
                case 0x53:
                    return new MStore8Opcode(offset);
                case 0x54:
                    return new SLoadOpcode(offset);
                case 0x55:
                    return new SStoreOpcode(offset);
                case 0x56:
                    return new JumpOpcode(offset);
                case 0x57:
                    return new JumpIOpcode(offset);
                case 0x58:
                    return new PCOpcode(offset);
                case 0x59:
                    return new MSizeOpcode(offset);
                case 0x5a:
                    return new GasOpcode(offset);
                case 0x5b:
                    return new JumpDestOpcode(offset);
                case 0xf0:
                    return new CreateOpcode(offset);
                case 0xf1:
                    return new CallOpcode(offset);
                case 0xf2:
                    return new CallCodeOpcode(offset);
                case 0xf3:
                    return new ReturnOpcode(offset);
                case 0xf4:
                    return new DelegateCallOpcode(offset);
                case 0xfa:
                    return new StaticCallOpcode(offset);
                case 0xfd:
                    return new RevertOpcode(offset);
                case 0xff:
                    return new SelfDestructOpcode(offset);
                default:
                    return new InvalidOpcode(offset, byteOpcode);
            }
        }

    public:
        /**
         * Parse a string with the hexadecimal representation of the bytecode and generates both bytecode and remaining data
         *
         * If there is a PUSH-n but not enough bytes to build the argument then they become remaining data
         * @param binary the hexadecimal code
         * @return A pair with the bytecode and the remaining data
         */
        static pair<Bytecode*, string> parse(string binary){
            Bytecode* bytecode = new Bytecode();
            string  remainingData = "";
            uint8_t PUSH_OPCODE = OpcodeID::PUSH;

            // Read two bytes for each opcode
            for(int i = 0; i < binary.length(); i += 2){
                // Cast the 2 hex char to one byte
                string temp = binary.substr(i, 2);
                uint8_t byteOpcode = stol(temp, 0, 16);
                // Pase all the opcodes except for the PUSH
                if(byteOpcode < PUSH_OPCODE || byteOpcode > PUSH_OPCODE + 31){
                    // the offset is the half of the string index
                    bytecode->addOpcode(parseOpcode(temp, i/2));
                }
                else{
                    // Treat the PUSH in different ways

                    int argumentNumber = byteOpcode - PUSH_OPCODE + 1;
                    // get teh arguments of  the PUSH
                    if(i + 2 + argumentNumber * 2 <= binary.length()){
                        string strArgument = binary.substr(i + 2, argumentNumber * 2);
                        bytecode->addOpcode(new PushOpcode(i/2, argumentNumber, strArgument));
                        i += argumentNumber * 2;
                    }
                    else{
                        // The push has not enough data, then all the remaining bytes become remainingData
                        remainingData = binary.substr(i);
                        // breaks the loop
                        i = binary.length();
                    }
                }
            }
            return make_pair(bytecode, remainingData);
        }
};
