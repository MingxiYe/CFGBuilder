#include<iostream>
#include "CFG/contract/Contract.h"
#include "Utils/JsonExporter.h"
#include<fstream>
#include "Message.h"
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;
namespace pt = boost::property_tree;
namespace po = boost::program_options;

void forEachFile(string folder, string extension, function<void (directory_entry)> cb) {
  path folderPath(folder);
  for (auto& file : boost::make_iterator_range(directory_iterator(folderPath), {})) {
    if (is_directory(file.status())) forEachFile(file.path().string(), extension, cb);
    if (!is_directory(file.status()) && boost::ends_with(file.path().string(), extension)) cb(file);
  }
}

string toContractName(directory_entry file) {
  string fileName = file.path().filename().string();
  string fileNameWithoutExtension = fileName.find(".") != string::npos
  ? fileName.substr(0, fileName.find("."))
  : fileName;
  string contractName = fileNameWithoutExtension.find("_0x") != string::npos
  ? fileNameWithoutExtension.substr(0, fileNameWithoutExtension.find("_0x"))
  : fileNameWithoutExtension;
  return contractName;
}

string parseJson(string jsonFile, string contractName) {
  std::ifstream file(jsonFile);
  if (!file.is_open()) {
    stringstream output;
    output << "[x] File " + jsonFile + " is not found" << endl;
    cout << output.str();
    exit(0);
  }
  pt::ptree root;
  pt::read_json(jsonFile, root);
  string fullContractName = "";
  for (auto key : root.get_child("contracts")) {
    if (boost::ends_with(key.first, contractName)) {
      fullContractName = key.first;
      break;
    }
  }
  if (!fullContractName.length()) {
    cout << "[x] No contract " << contractName << endl;
    exit(0);
  }
//   pt::ptree::path_type abiPath("contracts|"+ fullContractName +"|abi", '|');
  pt::ptree::path_type binPath("contracts|"+ fullContractName +"|bin", '|');
//   pt::ptree::path_type binRuntimePath("contracts|" + fullContractName + "|bin-runtime", '|');
//   pt::ptree::path_type srcmapPath("contracts|" + fullContractName + "|srcmap", '|');
//   pt::ptree::path_type srcmapRuntimePath("contracts|" + fullContractName + "|srcmap-runtime", '|');
  return root.get<string>(binPath);
}

string Message::ANSI_RESET = "\u001B[0m";
string Message::ANSI_YELLOW = "\u001B[33m";
bool Message::printDebug = false;
static string DEFAULT_CONTRACTS_FOLDER = "/home/yemx6/CFGBuilder/contracts/";
static string DEFAULT_OUTPUTS = "/home/yemx6/CFGBuilder/outputs/";

<<<<<<< HEAD
int main(){
    string bytecode = "608060405234801561001057600080fd5b50610422806100206000396000f30060806040526004361061004c576000357c0100000000000000000000000000000000000000000000000000000000900463ffffffff168063af294a3614610051578063f121e5e71461007c575b600080fd5b34801561005d57600080fd5b5061006661009a565b6040518082815260200191505060405180910390f35b610084610219565b6040518082815260200191505060405180910390f35b6000806000738316b082621cfedab95bf4a44a1d4b64a6ffc33691508173ffffffffffffffffffffffffffffffffffffffff1663667e93946305f5e1006040518263ffffffff167c010000000000000000000000000000000000000000000000000000000002815260040180806020018060200180602001858152602001848103845260038152602001807f4554480000000000000000000000000000000000000000000000000000000000815250602001848103835260038152602001807f4441490000000000000000000000000000000000000000000000000000000000815250602001848103825260078152602001807f44454641554c5400000000000000000000000000000000000000000000000000815250602001945050505050602060405180830381600087803b1580156101d457600080fd5b505af11580156101e8573d6000803e3d6000fd5b505050506040513d60208110156101fe57600080fd5b81019080805190602001909291905050509050809250505090565b600080600080600080732a1530c4c41db0b0b2bb646cb5eb1a67b715866794508493503492508373ffffffffffffffffffffffffffffffffffffffff1663f39b5b9b846001426040518463ffffffff167c010000000000000000000000000000000000000000000000000000000002815260040180838152602001828152602001925050506020604051808303818588803b1580156102b757600080fd5b505af11580156102cb573d6000803e3d6000fd5b50505050506040513d60208110156102e257600080fd5b81019080805190602001909291905050509150736b175474e89094c44da98b954eedeac495271d0f90508073ffffffffffffffffffffffffffffffffffffffff1663a9059cbb33846040518363ffffffff167c0100000000000000000000000000000000000000000000000000000000028152600401808373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200182815260200192505050602060405180830381600087803b1580156103af57600080fd5b505af11580156103c3573d6000803e3d6000fd5b505050506040513d60208110156103d957600080fd5b8101908080519060200190929190505050508195505050505050905600a165627a7a72305820bf6b8829749ca20117d7f17d255882579fae1f255a3888f03502e4891e5da9660029";
    string name = "Sample";
    Contract contract(name, bytecode);

    my_json output_test;
    try {
        output_test = JsonExporter::contractJsonWriter(contract);
        fstream _file;

        _file.open("../../outputs/json/"+contract.getContractHash()+".json", ios::in);
        if(!_file) {
            Message::printDebugFun("Output file will be created");
            try {
                ofstream ofs;
                ofs.open("../../outputs/json/"+contract.getContractHash()+".json", ios::out);
                ofs<<output_test.dump(4)<<endl;
                ofs.close();
                cout<<"Contract analysis exported in "<<contract.getContractHash()+".json"<<endl;
            } catch (exception e) {
                cerr<<"Error writing file"+contract.getContractHash()+": "+e.what();
=======
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
            string thisContractName = fileName.substr(41, fileName.length() - 45);
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
            std::fstream _file;
            _file.open("../../outputs/json/" + contractName + ".json", ios::in);
            if(!_file) {
                Message::printDebugFun("Output file will be created");
                try {
                    std::ofstream ofs;
                    ofs.open("../../outputs/json/" + contractName + ".json", ios::out);
                    ofs << output.dump(4) << endl;
                    ofs.close();
                    cout << "Contract analysis exported in " << contractName + ".json" << endl;
                } catch (exception e) {
                    cerr << "Error writing file" + contractName + ": " + e.what();
                }
>>>>>>> dev
            }
        } catch (exception e) {
            cerr << "error occurred: " << e.what() << endl;
        }
    }

    return 0;
}