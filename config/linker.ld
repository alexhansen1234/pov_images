ENTRY(start)

SECTIONS
{
    . = 0x0000;    
    .text : 
    {
        *(.interrupt);
        *(.text) ;
    }

    .data : 
    { 
        *(.data);
    }

    .bss  : 
    { 
        *(.bss);
    }
}
