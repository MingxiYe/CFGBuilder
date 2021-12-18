## Building from source (Linux)

### Get the source code

Git and GitHub are used to maintain the source code. Clone the repository by:

```shell
git clone https://github.com/MingxiYe/CFGBuilder.git
cd CFGBuilder
```

### Install CMake

CMake is used to control the build configuration of the project. 
We strongly recommend you to install CMake by downloading and unpacking the binary
distribution  of the latest version available on the
[**CMake download page**](https://cmake.org/download/).

The CMake package available in your operating system can also be installed
and used if it meets the minimum version requirement.

### Install dependencies (Linux)

To be continued

### Build

Configure the project build with the following command to create the
`build` directory with the configuration.

```shell
mkdir build; cd build  # Create a build directory.
cmake ..               # Configure the project.
make                   # Build fuzzer targets.
```

## construct the CFG of contracts
Place contracts to `contracts/`

```shell
./main -g && chmod +x cfgCon && ./cfgCon
```
The CFG will be stored in `outpus/` in the form of json