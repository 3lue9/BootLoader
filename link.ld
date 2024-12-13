ENTRY(start)

SECTIONS
{
    . = 0x00100000;          /* Start of the kernel at 1 MB */

    .multiboot : {
        *(.multiboot)        /* Multiboot header section */
    }

    .text : {
        *(.text)             /* Code section */
    }

    .data : {
        *(.data)             /* Data section */
    }

    .bss : {
        *(.bss)              /* Uninitialized data */
    }
}

