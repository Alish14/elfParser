#ifndef ELF_PARSER_H
#define ELF_PARSER_H

#include <stdint.h>

typedef enum{
    ELF_CLASS_NONE,
    ELF_CLASS_32,
    ELF_CLASS_64
}Class;

void parse_elf(const char *filename);

#endif