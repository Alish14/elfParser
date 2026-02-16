#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "elf_sec_parser.h"

/**
 * @brief Parse ELF64 section header.
 *
 * @param filename Path to ELF file.
 * @param elfHeader Output parsed ELF header.
 */
void get_sec_headers(const char* filename,ElfHeader* elfHeader)
{
    FILE *fptr=fopen(filename,"rb");

    if(!fptr){
        perror("fopen");
        return;
    }

    Elf64_Shdr *sections =
    malloc(elfHeader->shnum * sizeof(Elf64_Shdr));
    
    /* Move to start of section header */
    fseek(fptr,elfHeader->shoff,SEEK_SET);

    fread(sections,sizeof(Elf64_Shdr),elfHeader->shnum,fptr);

    Elf64_Shdr shstr = sections[elfHeader->shstrndx];

    char *shstrtab = malloc(shstr.sh_size);

    fseek(fptr, shstr.sh_offset, SEEK_SET);

    fread(shstrtab, 1, shstr.sh_size, fptr);

printf("\n");
printf("====================================================\n");
printf("                 Section Headers                   \n");
printf("====================================================\n");


    for(int i=0;i < elfHeader->shnum;i++)
    {
        char *name=shstrtab+sections[i].sh_name;


        printf("[%d] %s\n", i, name);
        printf("  Address: 0x%lx\n", sections[i].sh_addr);
        printf("  Offset:  0x%lx\n", sections[i].sh_offset);
        printf("  Size:    0x%lx\n", sections[i].sh_size);

    }
    fclose(fptr);


}