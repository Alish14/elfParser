
#include <stdio.h>
#include "elf_header_parser.h"
#include "elf_phdr_parser.h"
int main(int argc,char **argv)
{
    ElfIdent eident_values;
    ElfHeader elf_hdr; // elf header struct
    
    if(argc != 2){
        printf("usage: %s <elf_file>\n",argv[0]);
        return 1;
    }
    parse_ident_elf(argv[1],&eident_values);
    elf_hdr.ident=eident_values;
    parse_elf_header(argv[1],&elf_hdr);
    printf("%lu\n", sizeof(Elf64_Phdr));
    get_program_headers(argv[1],&elf_hdr);
    return 0;
}