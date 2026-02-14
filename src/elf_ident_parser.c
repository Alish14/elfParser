#include <stdio.h>
#include <stdlib.h>
#include "elf_header_parser.h"

/**
*
*@brief Reads the ELF magic number from a file and validate it.
*
*@param magic_chars buffer to store the first EI_NIDENT bytes
*@param file_ptr File pointer to the opened binary
*@return int returns 0 if magic is valid , -1 otherwise
*/

int
get_magic_number(unsigned char *magic_chars,FILE* file_ptr)
{
    size_t n=fread(magic_chars,sizeof(unsigned char),EI_NIDENT,file_ptr);
    if( n != EI_NIDENT ){
        return -1;
    }

    if(magic_chars[0] != ELF_MAGIC_0 ||
       magic_chars[1] != ELF_MAGIC_1 ||
       magic_chars[2] != ELF_MAGIC_2 ||
       magic_chars[3] != ELF_MAGIC_3
    ){
        return -1;
    }
    return 0;

}


/**
*@brief Determines the ELF class (32bit/64bit) from the e_ident bytes 
* 
* 
* @param magic_chars e_ident array ELF header
* @param elf Pointer to ElfIdent struct to store the class
* @return int 0 on success, -1 if class is invalid
* 
*/
int
get_elf_format(unsigned char *magic_chars,ElfIdent *elf)
{
    switch(magic_chars[ELF_EICLASS_INDEX]){
        case ELF_CLASS_NONE:
            elf->elf_class=ELF_CLASS_NONE;
            printf("file type is: None\n");
            break;
        case ELF_CLASS_32:
            elf->elf_class=ELF_CLASS_32;
            printf("file type is: 32bit\n");
            break;
        case ELF_CLASS_64:
            elf->elf_class=ELF_CLASS_64;
            printf("file type is: 64bit\n");
            break;
        default:
            return -1;
    }
    return 0;
}

/**
*@brief Determines the ELF data format (endiannes) from the e_ident bytes 
* 
* @param magic_chars e_ident array from ELF header.
* @param elf Pointer to ElfIdent struct to store data format
* @return int 0 on success, -1 if format is invalid
* 
*/
int 
get_ident_data_format(unsigned char *magic_chars,ElfIdent *elf)
{
    switch(magic_chars[ELF_DATA_FORMAT_INDEX]){
        case ELF_DATA_NONE:
            elf->elf_data=ELF_DATA_NONE;
            printf("Data format is: None\n");
            break;
        case ELF_DATA_LSB:
            elf->elf_data=ELF_DATA_LSB;
            printf("Data format is: LSB\n");
            break;
        case ELF_DATA_MSB:
            elf->elf_data=ELF_DATA_MSB;
            printf("Data format is: MSB\n");
            break;
        default:
            return -1;
        }
        return 0;
}

/**
*@brief Extracts version, OS/ABI, and ABI version from e_ident 
* 
* 
* @param magic_chars e_ident array from ELF header
* @param elf Pointer to ElfIdent struct to store these values.
* 
*/
void
get_ident_other_data(unsigned char *magic_chars,ElfIdent *elf){
    elf->version=magic_chars[EI_NIDENT_VERSION];
    printf("Version is 0x%02x\n",elf->version);

    elf->osabi=magic_chars[EI_NIDENT_OSABI];
    printf("OS/ABI is 0x%02x\n",elf->version);

    elf->abi_version=magic_chars[EI_NIDENT_ABIVERSION];
    printf("ABI Version is: 0x%02x\n",elf->abi_version);

}

/**
 * @brief Dumps the raw ELF identification bytes
 * 
 * 
 * @param magic_chars e_ident array from ELF header
 * 
*/

void
get_ident_dump(unsigned char *magic_chars){
    printf("Magic\t");
    for(unsigned int data=0;data<EI_NIDENT;data++){
        printf("%02x ",magic_chars[data]);
    }
    printf("\n");
}

/**
 * @brief Main ELF parser for Phase 1: validate ELF and reads e_ident
 * 
 * 
 * @param filename path to the binary file
 * 
*/
void 
parse_ident_elf(const char *filename,ElfIdent *eident_values)
{
    FILE *fptr=fopen(filename,"rb");
    if(!fptr){
        printf("fopen");
        return;
    }

    if(get_magic_number(eident_values->e_ident,fptr)<0){
        printf("Not an ELF file \n");
        fclose(fptr);
        return;
    }
    printf("ELF file detected!\n");

    get_ident_dump(eident_values->e_ident);

    if(get_elf_format(eident_values->e_ident,eident_values) < 0){
        printf("error on detecting elf format closing peacefully");
        fclose(fptr);
        return;
    }
    if(get_ident_data_format(eident_values->e_ident,eident_values)<0){
        printf("error on extract data format on eident");
        fclose(fptr);
        return;
    }
    get_ident_other_data(eident_values->e_ident,eident_values);

    fclose(fptr);
}