#include<iostream>
#include<json.hpp>
#include<fifo_map.hpp>

using namespace std;
using namespace nlohmann;

// use json for modern C++
// define template for right order
template<class K, class V, class dummy_compare, class A>
using my_workaround_fifo_map = fifo_map<K, V, fifo_map_compare<K>, A>;
using my_json = basic_json<my_workaround_fifo_map>;

class JsonExporter{

private:

public:
    JsonExporter() {
        ;
    }

public:

    static my_json contractJsonWriter(Contract& contract) {
        my_json result;
        result["name"] = contract.toString();
        result["address"] = contract.getAddress();
        result["binarySource"] = contract.getBinarySource();
        result["binaryHash"] = contract.getContractHash();
        result["isOnlyRuntime"] = contract.getIsOnlyRuntime();
        result["metadata"] = contract.getMetadata();
        try {
            result["solidityVersion"] = contract.getExactSolidityVersion();
        } catch (const char* e) {
            if (contract.getSolidityVersion() == SolidityVersion::UNKNOWN) {
                result["solidityVersion"] = "unknown";
            } else {
                result["solidityVersion"] = "<0.5.9";
            }
        }

        result["constructorRemainingData"] =  contract.getConstructorRemainingData();
        result["constructorCfg"] = cfgJsonWriter(contract.getConstructorCfg());
        result["runtimeCfg"] = cfgJsonWriter(contract.getRuntimeCfg());
        return result;
    }



    static my_json cfgJsonWriter(Cfg *cfg) {
        my_json result;
        result["bytecode"] = cfg->getBytecode().getBytes();
        result["remainingData"] = cfg->getRemainingData();
        vector<BasicBlock*> i = cfg->getBasicBlocksForIteration();
        int count = 0;
        for (vector<BasicBlock*>::iterator m = i.begin(); m != i.end(); m++) {
            result["nodes"][count]["offset"] = (*m)->getOffset();
            result["nodes"][count]["length"] = (*m)->getLength();
            result["nodes"][count]["type"] = genStringByEnumInt((*m)->getType());
            result["nodes"][count]["stackBalance"] = (*m)->getStackBalance();
            result["nodes"][count]["bytecodeHex"] = (*m)->getBytes();
            result["nodes"][count]["parsedOpcodes"] = (*m)->toString();
            count++;
        }
        vector<my_json> result_node;
        result["successors"] = cfg->getSuccessorsMap();
        my_json successors = successorsWriter(cfg->getSuccessorsMap());
        result["successors"] = successors;
        result["buildReport"]["directJumpTargetErrors"] = cfg->getBuildReport().getDirectJumpTargetErrors();
        result["buildReport"]["orphanJumpTargetNullErrors"] = cfg->getBuildReport().getOrphanJumpTargetNullErrors();
        result["buildReport"]["orphanJumpTargetUnknownErrors"] = cfg->getBuildReport().getOrphanJumpTargetUnknownErrors();
        result["buildReport"]["loopDepthExceededErrors"] = cfg->getBuildReport().getLoopDepthExceededErrors();
        result["buildReport"]["multipleRootNodesErrors"] = cfg->getBuildReport().getMultipleRootNodesErrors();
        result["buildReport"]["stackExceededErrorss"] = cfg->getBuildReport().getStackExceededErrors();
        result["buildReport"]["blockLimitErrors"] = cfg->getBuildReport().getBlockLimitErrors();
        result["buildReport"]["criticalErrors"] = cfg->getBuildReport().getCriticalErrors();
        result["buildReport"]["errorLog"] = cfg->getBuildReport().getLog();
        result["buildReport"]["buildTimeMillis"] = cfg->getBuildReport().getBuildTimeMillis();
        return result;
    }

    static my_json successorsWriter(vector<pair<long, vector<long>>> suc) {
        my_json res;
        int count = 0;
        for (vector<pair<long, vector<long>>>::iterator m = suc.begin(); m != suc.end(); m++) {
            res[count]["from"] = (*m).first;
            res[count]["to"] = (*m).second;
            count++;
        }
        return res;
    }

    static string genStringByEnumInt(BasicBlockType type) {
        switch(type) {
            case BasicBlockType::COMMON : return "common";
            case BasicBlockType::DISPATCHER : return "dispatcher";
            case BasicBlockType::FALLBACK :  return "fallback";
            case BasicBlockType::EXIT :  return "exit";
            default: return "error";
        }
    }


};

