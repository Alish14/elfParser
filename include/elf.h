#pragma once

/***************************************************
* e_ident marcros
****************************************************/
#define ELF_MAGIC_0 0x7f
#define ELF_MAGIC_1 'E'
#define ELF_MAGIC_2 'L'
#define ELF_MAGIC_3 'F'
#define ELF_EICLASS_INDEX 4
#define EI_NIDENT (16)
#define ELF_DATA_FORMAT_INDEX 5
#define EI_NIDENT_VERSION 6
#define EI_NIDENT_OSABI 7
#define EI_NIDENT_ABIVERSION 8

/***************************************************
* ELF header marcros
****************************************************/
#define START_ELF_HEADER_AFTER_IDENT_IDX 16