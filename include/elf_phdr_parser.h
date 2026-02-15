#ifndef ELF_PHDR_PARSER_H
#define ELF_PHDR_PARSER_H
#include "elf_header_parser.h"
#include <stdint.h>

typedef enum{
    PT_NULL=0,
    PT_LOAD,
    PT_DYNAMIC, 
    PT_INTERP,
    PT_NOTE,
}segment_type;

/**
 * @brief ELF64 Program Header structure.
 *
 * Matches the exact layout defined in the ELF64 specification.
 */
// typedef struct
// {
//     segment_type p_type;     /**< Segment type */
//     uint32_t p_flags;    /**< Segment flags */
//     uint64_t p_offset;   /**< Offset in file */
//     uint64_t p_vaddr;    /**< Virtual address in memory */
//     uint64_t p_paddr;    /**< Physical address (unused on most systems) */
//     uint64_t p_filesz;   /**< Size of segment in file */
//     uint64_t p_memsz;    /**< Size of segment in memory */
//     uint64_t p_align;    /**< Alignment */
// } Elf64_Phdr;

typedef struct
{
    uint32_t p_type;     /**< Segment type */
    uint32_t p_flags;    /**< Segment flags */
    uint64_t p_offset;   /**< Offset in file */
    uint64_t p_vaddr;    /**< Virtual address in memory */
    uint64_t p_paddr;    /**< Physical address (unused on most systems) */
    uint64_t p_filesz;   /**< Size of segment in file */
    uint64_t p_memsz;    /**< Size of segment in memory */
    uint64_t p_align;    /**< Alignment */
} Elf64_Phdr;

void get_program_headers(const char* filename,ElfHeader* elfHeader);
const char* get_segment_type(uint32_t type);


#endif
