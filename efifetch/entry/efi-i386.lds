OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)
SECTIONS {
	. = 0;
	ImageBase = .;
	.hash : { *(.hash) }
	.gnu.hash : { *(.gnu.hash) }
	.eh_frame : { *(.eh_frame) }
	.eh_frame_hdr : { *(.eh_frame_hdr) }
	.gcc_except_table : { *(.gcc_except_table*) }
	. = ALIGN(4096);
	.text : {
		_text = .;
		*(.text)
		*(.text.*)
		*(.gnu.linkonce.t.*)
		*(.plt)
		. = ALIGN(16);
	}
	_etext = .;
	_text_size = _etext - _text;
	. = DATA_SEGMENT_ALIGN (CONSTANT (MAXPAGESIZE), CONSTANT (COMMONPAGESIZE));
	.data : {
		_data = .;
		*(.got.plt)
		*(.got)
		*(.data)
		*(.data1)
		*(.data.*)
		. = ALIGN(16);
		__init_array_start = .;
		*(SORT(.init_array.*))
		*(.init_array)
		__init_array_end = .;
		. = ALIGN(16);
		__CTOR_LIST__ = .;
		*(SORT(.ctors.*))
		*(.ctors)
		__CTOR_END__ = .;
		. = ALIGN(16);
		__DTOR_LIST__ = .;
		*(SORT(.dtors.*))
		*(.dtors)
		__DTOR_END__ = .;
		. = ALIGN(16);
		__fini_array_start = .;
		*(SORT(.fini_array.*))
		*(.fini_array)
		__fini_array_end = .;
		*(.dynbss)
		*(.bss*)
		*(COMMON)
	}
	.note.gnu.build-id : { *(.note.gnu.build-id) }
	. = ALIGN(4096);
	_DYNAMIC = .;
	.dynamic  : { *(.dynamic) }
	. = ALIGN(4096);
	.rel : {
		*(.rel.text*)
		*(.rel.data*)
		*(.rel.got)
		*(.rel.dyn)
		*(.rel.stab)
		*(.rel.init_array*)
		*(.rel.fini_array*)
		*(.rel.ctors*)
		*(.rel.dtors*)
		*(.data.rel.ro.local)
		*(.data.rel.local)
		*(.data.rel.ro)
		*(.data.rel*)
	}
	. = ALIGN(4096);
	.rel.plt : { *(.rel.plt) }
	. = ALIGN(4096);
	.rodata : { *(.rodata*) }
	_edata = .;
	_data_size = _edata - _etext;
	. = ALIGN(4096);
	.reloc : {
		KEEP (*(.reloc))
	}
	. = ALIGN(4096);
	.dynsym   : { *(.dynsym) }
	. = ALIGN(4096);
	.dynstr   : { *(.dynstr) }
	. = ALIGN(4096);
	. = DATA_SEGMENT_END (.);
	/DISCARD/ : {
		*(.rel.reloc)
		*(.note.GNU-stack)
	}
	.comment 0 : { *(.comment) }
}
