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
//   pt::ptree::path_type binPath("contracts|"+ fullContractName +"|bin", '|');
  pt::ptree::path_type binRuntimePath("contracts|" + fullContractName + "|bin-runtime", '|');
//   pt::ptree::path_type srcmapPath("contracts|" + fullContractName + "|srcmap", '|');
//   pt::ptree::path_type srcmapRuntimePath("contracts|" + fullContractName + "|srcmap-runtime", '|');
  return root.get<string>(binRuntimePath);
}