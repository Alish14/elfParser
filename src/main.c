
#include <stdio.h>
#include "elf_parser.h"

int main(int argc,char **argv)
{
    if(argc != 2){
        printf("usage: %s <elf_file>\n",argv[0]);
        return 1;
    }
    parse_ident_elf(argv[1]);
}