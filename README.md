# Nucleus

![GitHub all releases](https://img.shields.io/github/downloads/f4ncyz4nz4/nucleus/total)
![GitHub issues](https://img.shields.io/github/issues/f4ncyz4nz4/nucleus)

This [VU Sec project](https://www.vusec.net/projects/function-detection/) on function detection focuses on the automatic identification of functions in binary code. It aims to develop techniques and tools to analyze binary executables and identify individual functions within them.

Based on the paper ["Compiler-Agnostic Function Detection in Binaries"](https://danielandriesse.com/papers/eurosp-2017.pdf), published at EuroS&P 2017.

Contents
========

- [Nucleus](#nucleus)
- [Contents](#contents)
  - [\[FORENSIC\]What I did](#forensicwhat-i-did)
    - [New features added](#new-features-added)
    - [Test on different archs](#test-on-different-archs)
  - [Quick start](#quick-start)
  - [Installation](#installation)
    - [Requirements](#requirements)
    - [How to install](#how-to-install)
  - [Usage](#usage)
  - [Acknowledgements](#acknowledgements)
  - [License](#license)

## \[FORENSIC\]What I did
**(this section will be deleted after the evaluation)**
### New features added
1. Adding support for Mini DuMP files
    - Now is possible to launch the command `nucleus -d linear -f -t dmp -e <binary>` to analyze Mini DuMP file (Windows format)
2. New support for raw files
    - Now is possible to launch the command `nucleus -d linear -f -t dmp -a x86 -l 32 -o -e <binary>` to use Nucleus with 20 different offsets, Nucleus will start disassembly from different offsets, choosing the best offset according to the number of error generated during the disassembly phase

### Test on different archs
This dataset analysis has been performed using the Nucleus tool on a dataset sourced from "https://github.com/Cisco-Talos/binary_function_similarity" (I used dataset1).


The analysis involved examining the dataset for each of the six architecture categories available: x32, arm64, x64, mips32, mips64, and arm32. The aim was to gain insights into the dataset's properties across different architectures.


**For each category, 100 executables were analyzed**


I first used a script to extract how many functions were founded by Nucleus, creating a file for each category with this output:
```
IDBs/Dataset-1/openssl/arm64-clang-9-O1_libcrypto.so.3.i64
450 - 564
IDBs/Dataset-1/openssl/arm64-clang-5.0-Os_libcrypto.so.3.i64
432 - 547
IDBs/Dataset-1/openssl/arm64-clang-9-O0_libcrypto.so.3.i64
679 - 709
IDBs/Dataset-1/openssl/arm64-clang-7-Os_libcrypto.so.3.i64
344 - 474
...etc...
```
Final results:
```
arch
functions detected - functions to detect
ratio

arm32
6190 - 26661
0.2321

arm64
21109 - 25987
0.8122

mips32
18002 - 20923
0.8603

mips64
0 - 26998
0.0

x32
28541 - 29021
0.9834

x64
27182 - 28661
0.9483
```
As we can see from the result Nucleus seems to work an all the tested archs except for `mips64`.

Overall the ranking for the different architectures, starting from the best result, is:
1. x32
2. x64
3. mips32
4. arm64
5. arm32
6. mips64

## Quick start
```bash
docker build -t nucleus . 
docker run -it nucleus
```

## Installation

### Requirements
  - libcapstone
  - libbfd-multiarch

### How to install
```bash
git clone https://github.com/f4ncyz4nz4/nucleus.git
cd nucleus
make setup
make
```

## Usage
To reproduce the configuration from VU Sec paper and output a list of function addresses and sizes, use:
```bash
nucleus -d linear -f -e <binary>
```
To analyse a Mini DuMP file with an arch x86:32 and output a list of function addresses and sizes, use:
```bash
nucleus -d linear -f -t dmp -a x86 -l 32 -e <binary>
```
To list all the possible commands, use:
```bash
nucleus -h
```

## Acknowledgements
This work was supported by the Netherlands Organisation for Scientific Research through grant NWO 639.023.309 VICI “Dowsing” project. The public artifacts reflect only the authors’ view. The funding agencies are not responsible for any use that may be made of the information they contain.

## License
![GitHub](https://img.shields.io/github/license/f4ncyz4nz4/nucleus)