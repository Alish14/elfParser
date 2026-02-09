#ifndef ELF_PARSER_H
#define ELF_PARSER_H

#include <stdint.h>
#include "elf.h"

/**
* ident parser structures
*/
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

/**
* ident parser functions
*/
void parse_ident_elf(const char *filename);
int get_magic_number(unsigned char *magic_chars,FILE* file_ptr);
int get_elf_format(unsigned char *magic_chars,ElfIdent *elf);
int get_ident_data_format(unsigned char *magic_chars,ElfIdent *elf);
void get_ident_other_data(unsigned char *magic_chars,ElfIdent *elf);
void get_ident_dump(unsigned char *magic_chars);
void parse_ident_elf(const char *filename);
#endif