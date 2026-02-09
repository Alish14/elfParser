#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "elf_parser.h"

int get_magic_number(unsigned char *magic_chars,FILE* file_ptr){
    fread(magic_chars,sizeof(char),EI_NIDENT,file_ptr);
    if(magic_chars[0] != ELF_MAGIC_0 ||
       magic_chars[1] != ELF_MAGIC_1 ||
       magic_chars[2] != ELF_MAGIC_2 ||
       magic_chars[3] != ELF_MAGIC_3
    ){
        fclose(file_ptr);
        return -1;
    }
    return 0;

}

int get_elf_format(unsigned char *magic_chars,Class *elf){
    switch(magic_chars[ELF_EICLASS_INDEX]){
        case ELF_CLASS_NONE:
            *elf=ELF_CLASS_NONE;
            printf("file type is: None\n");
            break;
        case ELF_CLASS_32:
            *elf=ELF_CLASS_32;
            printf("file type is: 32bit\n");
            break;
        case ELF_CLASS_64:
            *elf=ELF_CLASS_64;
            printf("file type is: 64bit\n");
            break;
        default:
            return -1;
    }
    return 0;
}


void parse_elf(const char *filename)
{
    Class elf_format;
    FILE *fptr=fopen(filename,"rb");
    if(!fptr){
        printf("fopen");
        return;
    }
    unsigned char e_ident[EI_NIDENT];
    if(get_magic_number(e_ident,fptr)<0){
        printf("Not an ELF file \n");
        return;
    }
    printf("ELF file detected!\n");
    if(get_elf_format(e_ident,&elf_format) < 0){
        printf("error on detecting elf format closing peacefully");
        return;
    }
}