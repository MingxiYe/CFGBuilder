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
            }
        } catch (exception e) {
            cerr << "error occurred: " << e.what() << endl;
        }
    }

    return 0;
}