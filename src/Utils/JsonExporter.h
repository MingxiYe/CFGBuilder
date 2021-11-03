#include<iostream>
#include<json.hpp>
#include "fifo_map.hpp"
//#include <c++/v1/bitset>

using namespace std;
using namespace nlohmann;
using json = nlohmann::json;
// jsoncpp使用string类型数据给Json::Value赋值有问题
// json for modern C++的add不方便，目前想着就用遍历了

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
//            result.Add("solidityVersion",contract.getSolidityVersion());
        } catch (const char* e) {
            if (contract.getSolidityVersion() == SolidityVersion::UNKNOWN) {
                result["solidityVersion"] = "unknown";
//                result.Add("solidityVersion","unknown");
            } else {
                result["solidityVersion"] = "<0.5.9";
//                result.Add("solidityVersion", "<0.5.9");
            }
        }
//        result.Add("constructorRemainingData", contract.getConstructorRemainingData());
        result["constructorRemainingData"] =  contract.getConstructorRemainingData();
//        result.Add("constructorCfg", cfgJsonWriter(contract.getConstructorCfg(), result));
        result["constructorCfg"] = cfgJsonWriter(contract.getConstructorCfg());
        result["runtimeCfg"] = cfgJsonWriter(contract.getRuntimeCfg());
//        cout<<result.dump(4)<<endl;
        return result;
    }



    static my_json cfgJsonWriter(Cfg *cfg) {
        my_json result;

        result["bytecode"] = cfg->getBytecode().getBytes();
        result["remainingData"] = cfg->getRemainingData();
        vector<BasicBlock*> i = cfg->getBasicBlocksForIteration();
        // 裂开，一直测试原来发现我的*m没带括号，C++丢干净了
        int count = 0;
        for (vector<BasicBlock*>::iterator m = i.begin(); m != i.end(); m++) {
//            cout<< (*m)->getOffset()<<endl;
//            result = nodeJsonWriter(*m, result["nodes"][count]);
            result["nodes"][count]["offset"] = (*m)->getOffset();
            result["nodes"][count]["length"] = (*m)->getLength();
            result["nodes"][count]["type"] = (*m)->getType();
            result["nodes"][count]["stackBalance"] = (*m)->getStackBalance();
            result["nodes"][count]["bytecodeHex"] = (*m)->getBytes();
            result["nodes"][count]["parsedOpcodes"] = (*m)->toString();
            count++;
//            nodeJsonWriter(*m).dump(4);
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


};

