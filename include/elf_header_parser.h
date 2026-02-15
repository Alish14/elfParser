#ifndef ELF_HEADER_PARSER_H
#define ELF_HEADER_PARSER_H

#include <stdint.h>
#include "elf.h"

/************************************************
*           ident parser structures
************************************************/
typedef enum{
    ELF_CLASS_NONE = 0,
    ELF_CLASS_32 = 1,
    ELF_CLASS_64 = 2
}ElfClass;

typedef enum {
    ELF_DATA_NONE = 0,
    ELF_DATA_LSB  = 1,
    ELF_DATA_MSB  = 2
} ElfData;


typedef struct{
    unsigned char    e_ident[EI_NIDENT]; /* raw bytes */
    ElfClass elf_class;
    ElfData  elf_data;
    
    unsigned char version;
    unsigned char osabi;
    unsigned char abi_version;

}ElfIdent;

/**********************************************
*           ident parser functions            *
**********************************************/
int get_magic_number(unsigned char *magic_chars,FILE* file_ptr);
int get_elf_format(unsigned char *magic_chars,ElfIdent *elf);
int get_ident_data_format(unsigned char *magic_chars,ElfIdent *elf);
void get_ident_other_data(unsigned char *magic_chars,ElfIdent *elf);
void get_ident_dump(unsigned char *magic_chars);
void parse_ident_elf(const char *filename,ElfIdent *eident_values);

/* =========================
 * ELF file type
 * ========================= */
typedef enum{
    ET_NONE=0,
    ET_REL=1,
    ET_EXEC=2,
    ET_DYN=3,
    ET_CORE=4,
}ElfType;

typedef enum {
    ARCH_UNKNOWN = 0,
    ARCH_X86     = 3,    // EM_386
    ARCH_X86_64  = 62,   // EM_X86_64
    ARCH_ARM     = 40,   // EM_ARM
    ARCH_ARM64   = 183,  // EM_AARCH64
    ARCH_MIPS    = 8,
    ARCH_RISCV   = 243
} ElfArch;

/* =========================
 *          ELF Header
 * ========================= */
typedef struct
{
    ElfIdent   ident;
    ElfType    type;
    ElfArch    arch;
    uint32_t   version;
    uint64_t   entry;
    uint64_t   phoff;
    uint64_t   shoff;
    uint32_t   flags;
    uint16_t   ehsize;
    uint16_t   phentsize;
    uint16_t   phnum;
    uint16_t   shentsize;
    uint16_t   shnum;
    uint16_t   shstrndx;
}ElfHeader;

/* =========================
 * ELF Header API
 * ========================= 
 * */

void parse_elf_header(const char *filename, ElfHeader *header);
ElfType get_elf_type(uint16_t type);
ElfArch get_elf_machine(uint16_t type);
#endif

