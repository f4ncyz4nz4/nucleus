# Nucleus

![GitHub all releases](https://img.shields.io/github/downloads/f4ncyz4nz4/nucleus/total)
![GitHub issues](https://img.shields.io/github/issues/f4ncyz4nz4/nucleus)

This [VU Sec project](https://www.vusec.net/projects/function-detection/) on function detection focuses on the automatic identification of functions in binary code. It aims to develop techniques and tools to analyze binary executables and identify individual functions within them.

Based on the paper ["Compiler-Agnostic Function Detection in Binaries"](https://danielandriesse.com/papers/eurosp-2017.pdf), published at EuroS&P 2017.

Contents
========

- [Nucleus](#nucleus)
- [Contents](#contents)
  - [Quick start](#quick-start)
  - [Installation](#installation)
    - [Requirements](#requirements)
    - [How to install](#how-to-install)
  - [Usage](#usage)
  - [Acknowledgements](#acknowledgements)
  - [License](#license)

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
To analyse a raw file with an arch x86:32 and the *best offset search* option and output a list of function addresses and sizes, use:
```bash
nucleus -d linear -f -t raw -a x86 -l 32 -o -e <binary> 
```
To list all the possible commands, use:
```bash
nucleus -h
```

## Acknowledgements
This work was supported by the Netherlands Organisation for Scientific Research through grant NWO 639.023.309 VICI “Dowsing” project. The public artifacts reflect only the authors’ view. The funding agencies are not responsible for any use that may be made of the information they contain.

## License
![GitHub](https://img.shields.io/github/license/f4ncyz4nz4/nucleus)