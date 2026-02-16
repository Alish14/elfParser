#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "elf_phdr_parser.h"

/**
 * @brief Decode segment type to string.
 * 
 * @param tpye e_type from ELF Header
 */
const char* get_segment_type(uint32_t type)
{
    switch (type) {
        case 0: return "PT_NULL";
        case 1: return "PT_LOAD";
        case 2: return "PT_DYNAMIC";
        case 3: return "PT_INTERP";
        case 4: return "PT_NOTE";
        case 6: return "PT_PHDR";
        case 7: return "PT_TLS";
        default: return "UNKNOWN";
    }
}


/**
 * 
 * @brief Parse all program headers in ELF64 file.
 * 
 * @param filename path to the binary file
 * @param elfHeader pointer to Elfheader for using its parameters
 */

void get_program_headers(const char* filename,ElfHeader* elfHeader)
{
    FILE *fptr=fopen(filename,"rb");
    if(!fptr){
        perror("fopen");
        return;
    }
    /* Move to start of program header table */
    fseek(fptr,elfHeader->phoff,SEEK_SET);
printf("\n");
printf("====================================================\n");
printf("                 Program Headers                   \n");
printf("====================================================\n");

    for(uint16_t i=0; i < elfHeader->phnum;i++){
        
        Elf64_Phdr phdr;

        fread(&phdr,sizeof(Elf64_Phdr),1,fptr);

        printf("\nProgram Header [%d]\n", i);
        printf("Type: %s\n", get_segment_type(phdr.p_type));
        printf("Offset: 0x%" PRIx64 "\n", phdr.p_offset);
        printf("Virtual Address: 0x%" PRIx64 "\n", phdr.p_vaddr);
        printf("File Size: %" PRIu64 "\n", phdr.p_filesz);
        printf("Memory Size: %" PRIu64 "\n", phdr.p_memsz);
        printf("Flags: 0x%x\n", phdr.p_flags);
        printf("Align: %" PRIu64 "\n", phdr.p_align);
    }

    fclose(fptr);
}