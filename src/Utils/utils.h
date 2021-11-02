#ifndef _ARITHMETICOPCODE_H
#define _ARITHMETICOPCODE_H
#include "../opcodes/opcode/ArithmeticOpcode.h"
#endif

#ifndef _BINARYARITHMETICOPCODE_H
#define _BINARYARITHMETICOPCODE_H
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode.h"
#endif
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/AddOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/AndOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/ByteOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/DivOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/EQOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/ExpOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/GTOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/LTOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/ModOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/MulOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/OrOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/SAROpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/SDiveOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/SGTOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/SHA3Opcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/SHLOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/SHROpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/SignExtendOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/SLTOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/SModeOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/SubOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/XorOpcode.h"

#ifndef _TERNARYARITHMETICOPCODE_H
#define _TERNARYARITHMETICOPCODE_H
#include "../opcodes/opcode/ArithmeticOpcode/TernaryArithmeticOpcode.h"
#endif
#include "../opcodes/opcode/ArithmeticOpcode/TernaryArithmeticOpcode/AddModOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/TernaryArithmeticOpcode/MulModOpcode.h"

#ifndef _UNARYARITHMETICOPCODE_H
#define _UNARYARITHMETICOPCODE_H
#include "../opcodes/opcode/ArithmeticOpcode/UnaryArithmeticOpcode.h"
#endif
#include "../opcodes/opcode/ArithmeticOpcode/UnaryArithmeticOpcode/IsZeroOpcode.h"
#include "../opcodes/opcode/ArithmeticOpcode/UnaryArithmeticOpcode/NotOpcode.h"

#ifndef _BLOCKOPCODE_H
#define _BLOCKOPCODE_H
#include "../opcodes/opcode/BlockOpcode.h"
#endif
#include "../opcodes/opcode/BlockOpcode/BlockHashOpcode.h"
#include "../opcodes/opcode/BlockOpcode/ChainIdOpcode.h"
#include "../opcodes/opcode/BlockOpcode/CoinBaseOpcode.h"
#include "../opcodes/opcode/BlockOpcode/DifficultyOpcode.h"
#include "../opcodes/opcode/BlockOpcode/GasLimitOpcode.h"
#include "../opcodes/opcode/BlockOpcode/NumberOpcode.h"
#include "../opcodes/opcode/BlockOpcode/TimeStampOpcode.h"

#ifndef _CONTROLFLOWOPCODE_H
#define _CONTROLFLOWOPCODE_H
#include "../opcodes/opcode/ControlFlowOpcode.h"
#endif
#include "../opcodes/opcode/ControlFlowOpcode/JumpDestOpcode.h"
#include "../opcodes/opcode/ControlFlowOpcode/JumpIOpcode.h"
#include "../opcodes/opcode/ControlFlowOpcode/JumpOpcode.h"
#include "../opcodes/opcode/ControlFlowOpcode/StopOpcode.h"

#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../opcodes/opcode/EnvironmentalOpcode.h"
#endif
#include "../opcodes/opcode/EnvironmentalOpcode/AddressOpcode.h"
#include "../opcodes/opcode/EnvironmentalOpcode/BalanceOpcode.h"
#include "../opcodes/opcode/EnvironmentalOpcode/CallDataCopyOpcode.h"
#include "../opcodes/opcode/EnvironmentalOpcode/CallDataLoadOpcode.h"
#include "../opcodes/opcode/EnvironmentalOpcode/CallDataSizeOpcode.h"
#include "../opcodes/opcode/EnvironmentalOpcode/CallerOpcode.h"
#include "../opcodes/opcode/EnvironmentalOpcode/CallValueOpcode.h"
#include "../opcodes/opcode/EnvironmentalOpcode/CodeCopyOpcode.h"
#include "../opcodes/opcode/EnvironmentalOpcode/CodeSizeOpcode.h"
#include "../opcodes/opcode/EnvironmentalOpcode/ExtCodeCopyOpcode.h"
#include "../opcodes/opcode/EnvironmentalOpcode/ExtCodeHashOpcode.h"
#include "../opcodes/opcode/EnvironmentalOpcode/ExtCodeSizeOpcode.h"
#include "../opcodes/opcode/EnvironmentalOpcode/GasPriceOpcode.h"
#include "../opcodes/opcode/EnvironmentalOpcode/OriginOpcode.h"
#include "../opcodes/opcode/EnvironmentalOpcode/ReturnDataCopyOpcode.h"
#include "../opcodes/opcode/EnvironmentalOpcode/ReturnDataSizeOpcode.h"
#include "../opcodes/opcode/EnvironmentalOpcode/SelfBalanceOpcode.h"

#ifndef _STACKOPCODE_H
#define _STACKOPCODE_H
#include "../opcodes/opcode/StackOpcode.h"
#endif
#include "../opcodes/opcode/StackOpcode/DupOpcode.h"
#include "../opcodes/opcode/StackOpcode/GasOpcode.h"
#include "../opcodes/opcode/StackOpcode/MLoadOpcode.h"
#include "../opcodes/opcode/StackOpcode/MSizeOpcode.h"
#include "../opcodes/opcode/StackOpcode/MStore8Opcode.h"
#include "../opcodes/opcode/StackOpcode/MStoreOpcode.h"
#include "../opcodes/opcode/StackOpcode/PCOpcode.h"
#include "../opcodes/opcode/StackOpcode/PopOpcode.h"
#include "../opcodes/opcode/StackOpcode/PushOpcode.h"
#include "../opcodes/opcode/StackOpcode/SLoadOpcode.h"
#include "../opcodes/opcode/StackOpcode/SStoreOpcode.h"
#include "../opcodes/opcode/StackOpcode/SwapOpcode.h"

#ifndef _SYSTEMOPCODE_H
#define _SYSTEMOPCODE_H
#include "../opcodes/opcode/SystemOpcode.h"
#endif
#include "../opcodes/opcode/SystemOpcode/CallCodeOpcode.h"
#include "../opcodes/opcode/SystemOpcode/CallOpcode.h"
#include "../opcodes/opcode/SystemOpcode/CreateOpcode.h"
#include "../opcodes/opcode/SystemOpcode/DelegateCallOpcode.h"
#include "../opcodes/opcode/SystemOpcode/ReturnOpcode.h"
#include "../opcodes/opcode/SystemOpcode/RevertOpcode.h"
#include "../opcodes/opcode/SystemOpcode/SelfDestructOpcode.h"
#include "../opcodes/opcode/SystemOpcode/StaticCallOpcode.h"
#include "../opcodes/opcode/InvalidOpcode.h"
#include "../opcodes/opcode/LogOpcode.h"

class utils {


};