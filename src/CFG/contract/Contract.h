#include <iostream>
#include "../../SolidityInfo/SolidityVersion.h"
#include "../cfgbuilder/CfgBuilder.h"
#include "../../Utils/Tools.h"
#include <boost/regex.hpp>

using namespace std;

class Contract{
private:
    string name;
    string address;
    string binarySource;
    string contractHash;
    bool isOnlyRuntime;
    string metadata;
    SolidityVersion solidityVersion;
    string constructorRemainingData;

    Cfg* constructorCfg;
    Cfg* runtimeCfg;

    /**
     * Removes the final part of the string with contains Solidity metadata and constructor remaining data
     *
     * It cycles through a list of regexp which represents the changes from version 0.4.17 on
     * @param binary the bytecode string
     * @return the stripped string and the constructor remaining data
     */
    pair<string, string> removeCompilationInfo(string binary){
        // From version solc-0.4.17
        // 0xa1
        // 0x65 'b' 'z' 'z' 'r' '0' 0x58 0x20 <32 bytes swarm hash>
        // 0x00 0x29
        if(boost::regex_match(binary, boost::regex("^[0-9a-f]*a165627a7a72305820[0-9a-f]{64}0029[0-9a-f]*$"))){
            solidityVersion = SolidityVersion::FROM_0_4_17_TO_0_5_8;
            vector<string> splitString = CfgBuilder::divide(binary, "(?=a165627a7a72305820[0-9a-f]{64}0029)", 2);
            string second = splitString.size() > 1 ? splitString[1] : "";
//            metadata = binary.substr(splitString[0].size() - 86);
            metadata = second;
            return make_pair(splitString[0], second.substr(86));
        }
            // Experimental option in Solidity due to ABIEncoderV2
            // example: a265627a7a723058201e1bfc77d507025cf70760b0848f01673dd1fb26af9d47b555da548df16224066c6578706572696d656e74616cf50037
            // 0xa2
            // 0x65 'b' 'z' 'z' 'r' '0' 0x58 0x20 <32 bytes swarm hash>
            // 0x6c 'e' 'x' 'p' 'e' 'r' 'i' 'm' 'e' 'n' 't' 'a' 'l' 0xf5
            // 0x00 0x37
        else if(boost::regex_match(binary, boost::regex("^[0-9a-f]*a265627a7a72305820[0-9a-f]{64}6c6578706572696d656e74616cf50037[0-9a-f]*$"))){
            solidityVersion = SolidityVersion::FROM_0_4_17_TO_0_5_8_EXPERIMENTAL;
            vector<string> splitString = CfgBuilder::divide(binary, "(?=a265627a7a72305820[0-9a-f]{64}6c6578706572696d656e74616cf50037)", 2);
            string second = splitString.size() > 1 ? splitString[1] : "";
//            metadata = binary.substr(splitString[0].size() - 114);
            metadata = second;
            return make_pair(splitString[0], second.substr(114));
        }
            // From version solc-0.5.9
            // 0xa2
            // 0x65 'b' 'z' 'z' 'r' '0' 0x58 0x20 <32 bytes swarm hash>
            // 0x64 's' 'o' 'l' 'c' 0x43 <3 byte version encoding>
            // 0x00 0x32
        else if(boost::regex_match(binary, boost::regex("^[0-9a-f]*a265627a7a72305820[0-9a-f]{64}64736f6c6343[0-9a-f]{6}0032[0-9a-f]*$"))){
            solidityVersion = SolidityVersion::FROM_0_5_9_TO_0_5_11;
            vector<string> splitString = CfgBuilder::divide(binary, "(?=a265627a7a72305820[0-9a-f]{64}64736f6c6343[0-9a-f]{6}0032)", 2);
            string second = splitString.size() > 1 ? splitString[1] : "";
//            metadata = binary.substr(splitString[0].size() - 104);
            metadata = second;
            return make_pair(splitString[0], second.substr(104));
        }
            // Experimental option in Solidity due to ABIEncoderV2
            // example: a365627a7a7230582022316da6de015a68fad6ca8a732898f553832e95b48e9f39b85fe694b2264db26c6578706572696d656e74616cf564736f6c634300050a0040
            // 0xa3
            // 0x65 'b' 'z' 'z' 'r' '0' 0x58 0x20 <32 bytes swarm hash>
            // 0x6c 'e' 'x' 'p' 'e' 'r' 'i' 'm' 'e' 'n' 't' 'a' 'l' 0xf5
            // 0x64 's' 'o' 'l' 'c' 0x43 <3 byte version encoding>
            // 0x00 0x40
        else if(boost::regex_match(binary, boost::regex("^[0-9a-f]*a365627a7a72305820[0-9a-f]{64}6c6578706572696d656e74616cf564736f6c6343[0-9a-f]{6}0040[0-9a-f]*$"))){
            solidityVersion = SolidityVersion::FROM_0_5_9_TO_0_5_11_EXPERIMENTAL;
            vector<string> splitString = CfgBuilder::divide(binary, "(?=a365627a7a72305820[0-9a-f]{64}6c6578706572696d656e74616cf564736f6c6343[0-9a-f]{6}0040)", 2);
            string second = splitString.size() > 1 ? splitString[1] : "";
//            metadata = binary.substr(splitString[0].size() - 132);
            metadata = second;
            return make_pair(splitString[0], second.substr(132));
        }
            // From version solc-0.5.12
            // 0xa2
            // 0x65 'b' 'z' 'z' 'r' '1' 0x58 0x20 <32 bytes swarm hash>
            // 0x64 's' 'o' 'l' 'c' 0x43 <3 byte version encoding>
            // 0x00 0x32
        else if(boost::regex_match(binary, boost::regex("^[0-9a-f]*a265627a7a72315820[0-9a-f]{64}64736f6c6343[0-9a-f]{6}0032[0-9a-f]*$"))){
            solidityVersion = SolidityVersion::FROM_0_5_12_TO_0_5_15;
            vector<string> splitString = CfgBuilder::divide(binary, "(?=a265627a7a72315820[0-9a-f]{64}64736f6c6343[0-9a-f]{6}0032)", 2);
            string second = splitString.size() > 1 ? splitString[1] : "";
//            metadata = binary.substr(splitString[0].size() - 104);
            metadata = second;
            return make_pair(splitString[0], second.substr(104));
        }
            // Experimental option in Solidity due to ABIEncoderV2
            // example: a365627a7a7231582076f04f08ed9ab2d9078ead8a728e5e444700aed42abb0cd3bd94a1ae5612d38f6c6578706572696d656e74616cf564736f6c63430005110040
            // 0xa3
            // 0x65 'b' 'z' 'z' 'r' '1' 0x58 0x20 <32 bytes swarm hash>
            // 0x6c 'e' 'x' 'p' 'e' 'r' 'i' 'm' 'e' 'n' 't' 'a' 'l' 0xf5
            // 0x64 's' 'o' 'l' 'c' 0x43 <3 byte version encoding>
            // 0x00 0x40
        else if(boost::regex_match(binary, boost::regex("^[0-9a-f]*a365627a7a72315820[0-9a-f]{64}6c6578706572696d656e74616cf564736f6c6343[0-9a-f]{6}0040[0-9a-f]*$"))){
            solidityVersion = SolidityVersion::FROM_0_5_12_TO_0_5_15_EXPERIMENTAL;
            vector<string> splitString = CfgBuilder::divide(binary, "(?=a365627a7a72315820[0-9a-f]{64}6c6578706572696d656e74616cf564736f6c6343[0-9a-f]{6}0040)", 2);
            string second = splitString.size() > 1 ? splitString[1] : "";
//            metadata = binary.substr(splitString[0].size() - 132);
            metadata = second;
            return make_pair(splitString[0], second.substr(132));
        }
            // From version solc-0.6.0
            // 0xa2
            // 0x64 'i' 'p' 'f' 's' 0x58 0x22 <34 bytes IPFS hash>
            // 0x64 's' 'o' 'l' 'c' 0x43 <3 byte version encoding>
            // 0x00 0x32
        else if(boost::regex_match(binary, boost::regex("^[0-9a-f]*a264697066735822[0-9a-f]{68}64736f6c6343[0-9a-f]{6}0032[0-9a-f]*$"))){
            solidityVersion = SolidityVersion::FROM_0_6_0_TO_0_6_1;
            vector<string> splitString = CfgBuilder::divide(binary, "(?=a264697066735822[0-9a-f]{68}64736f6c6343[0-9a-f]{6}0032)", 2);
            string second = splitString.size() > 1 ? splitString[1] : "";
//            metadata = binary.substr(splitString[0].size() - 132);
            metadata = second;
            return make_pair(splitString[0], second.substr(132));
        }
            // From version solc-0.6.2
            // 0xa2
            // 0x64 'i' 'p' 'f' 's' 0x58 0x22 <34 bytes IPFS hash>
            // 0x64 's' 'o' 'l' 'c' 0x43 <3 byte version encoding>
            // 0x00 0x33
        else if(boost::regex_match(binary, boost::regex("^[0-9a-f]*a264697066735822[0-9a-f]{68}64736f6c6343[0-9a-f]{6}0033[0-9a-f]*$"))){
            solidityVersion = SolidityVersion::FROM_0_6_2_TO_LATEST;
            vector<string> splitString = CfgBuilder::divide(binary, "(?=a264697066735822[0-9a-f]{68}64736f6c6343[0-9a-f]{6}0033)", 2);
//                cout<<splitString[0]<<endl;
//                cout<<splitString[1]<<endl;
//                cout<<splitString.size()<<endl;
            string second = splitString.size() > 1 ? splitString[1] : "";
//                metadata = binary.substr(splitString[0].length() - 106);
            metadata = second;
//                cout<<metadata<<endl;
//                cout<<"secondsbstr"<<second.substr(106)<<endl;
            return make_pair(splitString[0], second.substr(106));
        }

        solidityVersion = SolidityVersion::UNKNOWN;
        return make_pair(binary, "");
    }

public:
    /**
     * Default printer with name and code
     * @return a string with name and code
     */
    string toString(){ return name; }

    /**
     * Default getter
     * @return binary source code
     */
    string getBytes(){ return binarySource; }

    /**
     * Default getter
     * @return contract name
     */
    string getName(){ return this->name; }

    /**
     * Default getter
     * @return address
     */
    string getAddress() { return address; }

    /**
     * Default getter
     * @return binary source code
     */
    string getBinarySource() { return binarySource; }

    /**
     * Default getter. The contract hash is the hashcode of the binary source code
     * @return contract hash
     */
    string getContractHash() { return contractHash; }

    /**
     * Default getter
     * @return if the contract has only runtime code or creation code
     */
    bool getIsOnlyRuntime() { return isOnlyRuntime; }

    /**
     * Default getter
     * @return metadata
     */
    string getMetadata() { return metadata; }

    /**
     * Default getter
     * @return constructor cfg
     */
    Cfg* getConstructorCfg() { return constructorCfg; }

    /**
     * Default getter
     * @return runtime cfg
     */
    Cfg* getRuntimeCfg() { return runtimeCfg; }

    SolidityVersion getSolidityVersion() { return solidityVersion; }

    /**
     * Default getter
     * @return bytecode of the constructor
     */
    Bytecode getConstructor(){ return constructorCfg->getBytecode(); }

    /**
     * Default getter
     * @return bytecode of the runtime
     */
    Bytecode getRuntime(){ return runtimeCfg->getBytecode(); }

    /**
     * Default getter
     * @return constructor remaining data
     */
    string getConstructorRemainingData(){ return constructorRemainingData; }

    /**
     * Creates a contract with the given inputs.
     *
     * The bytecode is divided between metadata, constructor, runtime and remaining data. Then the cfg is built.
     * @param name contract name
     * @param binary hexadecimal string with the bytecode
     * @param isOnlyRuntime if it is only runtime code or creation code
     * @param address address of the contract if it's deployed in the blockchain
     * @throws NotSolidityContractException If the bytecode has not been generated by solc
     */
    Contract(string name, string binary, bool isOnlyRuntime = false, string address = ""){
        // the first part is for the libraries
        if(!boost::regex_match(binary, boost::regex("^(73[0-9a-fA-F]{40}3014)?60(60|80)604052[0-9a-fA-F]*$")))
            throw "NotSolidityContractException";
        this->name = name;
        this->address = address;
        this->binarySource = binary;
        this->isOnlyRuntime = isOnlyRuntime;
        // C++实现java hashCode()
        stringstream byte;
        Tools tools;
        int32_t hash = tools.hashCode(binary);
        byte << hex << hash;
        string hashCode;
        byte >> hashCode;
        this->contractHash = hashCode;
//        cout<<"contractHash"<<this->contractHash<<endl;
        pair<string, string> strippedCode = removeCompilationInfo(binary);
        constructorRemainingData = strippedCode.second;
        string remainingCode = strippedCode.first;
        string constructor, runtime = "";
        if(!isOnlyRuntime){
            vector<string> splitCode = CfgBuilder::divide(remainingCode, "(?=(60(60|80)604052))", 3);
            runtime = splitCode[2];
            constructor = splitCode[1];
        } else {
            constructor = "";
            runtime = remainingCode;
        }
        this->constructorCfg = CfgBuilder::buildCfg(constructor);
        this->runtimeCfg = CfgBuilder::buildCfg(runtime);
    }

    string getExactSolidityVersion(){
        if(solidityVersion == SolidityVersion::UNKNOWN || solidityVersion == SolidityVersion::FROM_0_4_17_TO_0_5_8 || solidityVersion == SolidityVersion::FROM_0_4_17_TO_0_5_8_EXPERIMENTAL)
            throw "Version unknown or before 0.5.9";
        string version = metadata.substr(metadata.size() - 10, 6);
        int v1, v2, v3;
        v1 = stol(version.substr(0, 2), 0, 16);
        v2 = stol(version.substr(2, 2), 0, 16);
        v3 = stol(version.substr(4), 0, 16);
        string experimental = "";
        if (solidityVersion == SolidityVersion::FROM_0_4_17_TO_0_5_8_EXPERIMENTAL || solidityVersion == SolidityVersion::FROM_0_5_9_TO_0_5_11_EXPERIMENTAL || solidityVersion == SolidityVersion::FROM_0_5_12_TO_0_5_15_EXPERIMENTAL)
            experimental = " - experimental";
        return to_string(v1) + "." + to_string(v2) + "." + to_string(v3) + experimental;
    }
};