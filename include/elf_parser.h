#ifndef ELF_PARSER_H
#define ELF_PARSER_H

#include <stdint.h>
#include "elf.h"


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

void parse_elf(const char *filename);

#endif