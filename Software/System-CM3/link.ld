ENTRY( handler_reset )

_Min_Heap_Size = 0;
_Min_Stack_Size = 0x200;

MEMORY
{
	FLASH ( rx ) : ORIGIN = 0x08000000 , LENGTH = 32K
	RAM ( xrw ) : ORIGIN = 0x20000000 , LENGTH = 32K
	MEMORY_B1 ( rx ) : ORIGIN = 0x60000000 , LENGTH = 0K
}

_estack = ORIGIN(RAM)+LENGTH(RAM);

SECTIONS
{
	.text :
	{
		. = ALIGN(0x80);
		_interrupt_vector_offs = . - 0x08000000;
		KEEP(*(.interrupt_vector))
		. = ALIGN(4);
		*(.text)
		*(.text*)
		*(.rodata)
		*(.rodata*)
		. = ALIGN(4);
	} > FLASH

        .ARM.exidx : {
            __exidx_start = .;
            *(.ARM.exidx* .gnu.linkonce.armexidx.*)
            __exidx_end = .;
        } > FLASH
	_data_flash = .;

	.data : AT (_data_flash)
	{
		. = ALIGN(4);
		_data_begin = .;
		*(.data)
		*(.data*)
		. = ALIGN(4);
		_data_end = .;
	} > RAM

	.bss :
	{
		_bss_begin = .;
		__bss_start__ = _bss_begin;
		*(.bss)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		_bss_end = .;
		__bss_end__ = _bss_end;
	} > RAM

	_stack_size = 1024;
	_stack_end = ORIGIN(RAM)+LENGTH(RAM);
	_stack_begin = _stack_end - _stack_size;
	. = _stack_begin;
	.stack :
	{
		. = . + _stack_size;
	} > RAM
}

PROVIDE(_bss_end = _bss_end);
PROVIDE(_stack_begin = _stack_begin);
