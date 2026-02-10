#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "elf_parser.h"

/**
 * @brief Decode ELF file type.
 *
 * @param type Raw e_type value from ELF header.
 * @return ElfType Decoded ELF file type.
 */
ElfType get_elf_type(uint16_t type)
{
    switch (type) {
        case ET_NONE:
            printf("File Type: None\n");
            return ET_NONE;
        case ET_REL:
            printf("File Type: Relocatable\n");
            return ET_REL;
        case ET_EXEC:
            printf("File Type: Executable\n");
            return ET_EXEC;
        case ET_DYN:
            printf("File Type: DYN (PIE / Shared Object)\n");
            return ET_DYN;
        case ET_CORE:
            printf("File Type: Core Dump\n");
            return ET_CORE;
        default:
            printf("File Type: Unknown (0x%x)\n", type);
            return ET_NONE;
    }
}

/**
 * @brief Decode ELF target architecture.
 *
 * @param machine Raw e_machine value.
 * @return ElfArch Decoded architecture.
 */
ElfArch get_elf_machine(uint16_t machine)
{
    switch (machine) {
        case ARCH_X86:
            printf("Machine: x86\n");
            return ARCH_X86;
        case ARCH_X86_64:
            printf("Machine: x86_64\n");
            return ARCH_X86_64;
        case ARCH_ARM:
            printf("Machine: ARM\n");
            return ARCH_ARM;
        case ARCH_ARM64:
            printf("Machine: AArch64\n");
            return ARCH_ARM64;
        case ARCH_MIPS:
            printf("Machine: MIPS\n");
            return ARCH_MIPS;
        case ARCH_RISCV:
            printf("Machine: RISC-V\n");
            return ARCH_RISCV;
        default:
            printf("Machine: Unknown (0x%x)\n", machine);
            return ARCH_UNKNOWN;
    }
}

/**
 * @brief Parse remaining ELF64 header fields after e_machine.
 *
 * @param header Parsed ELF header output.
 * @param fptr Opened ELF file pointer.
 * @param offset Offset pointing right after e_machine.
 */
void get_other_data(ElfHeader *header, FILE *fptr, size_t offset)
{
    /* e_version */
    fread(&header->version, sizeof(uint32_t), 1, fptr);
    printf("Version:\t\t 0x%x\n", header->version);
    offset += 4;

    /* e_entry */
    fread(&header->entry, sizeof(uint64_t), 1, fptr);
    printf("Entry point:\t 0x%" PRIx64 "\n", header->entry);
    offset += 8;

    /* e_phoff */
    fread(&header->phoff, sizeof(uint64_t), 1, fptr);
    printf("Program header offset:\t %" PRIu64 "\n", header->phoff);
    offset += 8;

    /* e_shoff */
    fread(&header->shoff, sizeof(uint64_t), 1, fptr);
    printf("Section header offset:\t %" PRIu64 "\n", header->shoff);
    offset += 8;

    /* e_flags */
    fread(&header->flags, sizeof(uint32_t), 1, fptr);
    printf("Flags:\t\t 0x%x\n", header->flags);
    offset += 4;

    /* e_ehsize */
    fread(&header->ehsize, sizeof(uint16_t), 1, fptr);
    printf("ELF header size:\t %u\n", header->ehsize);
    offset += 2;

    /* e_phentsize */
    fread(&header->phentsize, sizeof(uint16_t), 1, fptr);
    printf("Program header size:\t %u\n", header->phentsize);
    offset += 2;

    /* e_phnum */
    fread(&header->phnum, sizeof(uint16_t), 1, fptr);
    printf("Program headers:\t %u\n", header->phnum);
    offset += 2;

    /* e_shentsize */
    fread(&header->shentsize, sizeof(uint16_t), 1, fptr);
    printf("Section header size:\t %u\n", header->shentsize);
    offset += 2;

    /* e_shnum */
    fread(&header->shnum, sizeof(uint16_t), 1, fptr);
    printf("Section headers:\t %u\n", header->shnum);
    offset += 2;

    /* e_shstrndx */
    fread(&header->shstrndx, sizeof(uint16_t), 1, fptr);
    printf("Section string index:\t %u\n", header->shstrndx);
}

/**
 * @brief Parse ELF64 main header.
 *
 * @param filename Path to ELF file.
 * @param header Output parsed ELF header.
 */
void parse_elf_header(const char *filename, ElfHeader *header)
{
    uint16_t e_type;
    uint16_t e_machine;
    size_t offset = 16; /* e_ident size */

    FILE *fptr = fopen(filename, "rb");
    if (!fptr) {
        perror("fopen");
        return;
    }

    fseek(fptr, offset, SEEK_SET);

    fread(&e_type, sizeof(uint16_t), 1, fptr);
    fread(&e_machine, sizeof(uint16_t), 1, fptr);

    header->type = get_elf_type(e_type);
    header->arch = get_elf_machine(e_machine);

    get_other_data(header, fptr, offset + 4);

    fclose(fptr);
}
