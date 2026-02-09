#ifndef ELF_PARSER_H
#define ELF_PARSER_H

#include <stdint.h>

#define ELF_MAGIC_0 0x7f
#define ELF_MAGIC_1 'E'
#define ELF_MAGIC_2 'L'
#define ELF_MAGIC_3 'F'
#define ELF_EICLASS_INDEX 4

typedef enum{
    ELF_CLASS_NONE,
    ELF_CLASS_32,
    ELF_CLASS_64
}Class;

void parse_elf(const char *filename);

#endif