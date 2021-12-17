#include<iostream>
#include "CFG/contract/Contract.h"
#include "Utils/JsonExporter.h"
#include<fstream>
#include "Message.h"
#include "Utils.h"

using namespace std;

string Message::ANSI_RESET = "\u001B[0m";
string Message::ANSI_YELLOW = "\u001B[33m";
bool Message::printDebug = false;
static string DEFAULT_CONTRACTS_FOLDER = "/home/yemx6/CFGBuilder/contracts/";
static string DEFAULT_OUTPUTS = "/home/yemx6/CFGBuilder/outputs/";

int main(int argc, char* argv[]){
    string contractsFolder = DEFAULT_CONTRACTS_FOLDER;
    string outputs = DEFAULT_OUTPUTS;
    string jsonFile = "";
    string contractName = "";

    po::options_description desc("Allowed options");
    po::variables_map vm;
    desc.add_options()
        ("help,h", "produce help message")
        ("generate,g", "generate CFG construction script")
        ("file,f", po::value(&jsonFile), "construct CFG for a single contract")
        ("name,n", po::value(&contractName), "contract name");
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    /* Show help message */
    if(vm.count("help")){
        stringstream output;
        output << desc << endl;
        cout << output.str();
    }
    /* Generate CFG construction scripts */
    if(vm.count("generate")){
        std::ofstream cfgCon("cfgCon");
        cfgCon << "#!/bin/bash" << endl;
        /* Generate compiling scripts */
        forEachFile(contractsFolder, ".sol", [&](directory_entry file) {
            string filePath = file.path().string();
            cfgCon << "solc";
            cfgCon << " --combined-json abi,bin,bin-runtime,srcmap,srcmap-runtime,ast " + filePath;
            cfgCon << " > " + filePath + ".json";
            cfgCon << endl;
        });
        /* Generate CFG construction scripts */
        forEachFile(contractsFolder, ".sol", [&](directory_entry file) {
            string filePath = file.path().string();
            string fileName = file.path().filename().string();
            string thisContractName = fileName.substr(41, fileName.length() - 41);
            cfgCon << "./main";
            cfgCon << " --file " + filePath + ".json";
            cfgCon << " --name " + thisContractName;
            cfgCon << endl;
        });
        cfgCon.close();
    }
    /* Construct CFG of a single json file*/
    if(vm.count("file") && vm.count("name")){
        string bytecode = parseJson(jsonFile, contractName);
        Contract contract(contractName, bytecode);
        my_json output;
        try {
            output = JsonExporter::contractJsonWriter(contract);
            fstream _file;
            _file.open("../../outputs/json/" + contractName + ".json", ios::in);
            if(!_file) {
                Message::printDebugFun("Output file will be created");
                try {
                    ofstream ofs;
                    ofs.open("../../outputs/json/" + contractName + ".json", ios::out);
                    ofs << output.dump(4) << endl;
                    ofs.close();
                    cout << "Contract analysis exported in " << contractName + ".json" << endl;
                } catch (exception e) {
                    cerr << "Error writing file" + contractName + ": " + e.what();
                }
            }
        } catch (exception e) {
            cerr << "error occurred: " << e.what() << endl;
        }
    }

    return 0;
}