ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx)     : ORIGIN = 0x8000000, LENGTH = 2048K
  RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 192K
}

SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
         *(.text)
         *(.text.*)
        *(.rodata)
        _sidata = .;
        . = ALIGN(4);
    } >FLASH

    /* Initialized data will initially be loaded in FLASH at the end of the .text section. */
    .data : 
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)        /* Initialized data */
        _edata = .;
        . = ALIGN(4);
    } >RAM AT> FLASH

    .bss : {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)         /* Zero-filled run time allocate data memory */
        _ebss = .;
        . = ALIGN(4);
    } >RAM
    
    _estack = ORIGIN(RAM) + LENGTH(RAM);
}
