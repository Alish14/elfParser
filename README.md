# ELF64 Parser (Learning Project)

## Overview

This project is a simple ELF64 binary parser written in C.
It is built for learning purposes while studying binary analysis and ELF internals.

The parser currently supports:

* Reading the ELF header
* Parsing Program Headers (Segments)
* Parsing Section Headers
* Printing basic information similar to `readelf`

This project focuses only on **ELF64** binaries.

---

## Goals

The purpose of this project is to:

* Understand the ELF file format
* Learn how loaders work (Program Headers)
* Understand the difference between Segments and Sections
* Practice low-level file parsing in C

---

## Features

### Phase 1

* Read and validate ELF magic bytes

### Phase 2

* Parse and print ELF header fields

### Phase 3

* Parse Program Headers
* Identify `PT_LOAD` segments
* Print segment permissions and memory layout

### Phase 4

* Parse Section Header Table
* Extract section names using `.shstrtab`
* Print section information

---

## Build

Compile using gcc:

```bash
make
```

---

## Usage

```bash
./elf_parser <binary_file>
```

Example:

```bash
./elf_parser ./a.out
```

---

## Notes

* This parser only supports **64-bit ELF files**.
* It assumes little-endian architecture.
* It is intended for educational use only.

---

## Future Improvements

* Symbol table parsing (`.symtab`)
* Relocation parsing
* Dynamic section parsing
* Support for stripped binaries
* Add better formatted output

---
