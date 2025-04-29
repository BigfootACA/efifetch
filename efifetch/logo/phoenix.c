#include"logo.h"

static const char*logo_phoenix_data[]={
	"                ...                     ",
	"         -**************+               ",
	"      +*+-..    .:=*********:           ",
	"   .*:                =*******-         ",
	"  +         +********-  .*******.       ",
	".       =:.       .-*****-:******=      ",
	"      .               .********+**+     ",
	"                        .******++**-  : ",
	"                          +***** ***  -.",
	"                           +****.-**: =-",
	"                            ****  **=.*-",
	"                            ****  **+**.",
	"                            +**   ****- ",
	"                            **   =***-  ",
	"                            :    **+    ",
	"                                +-      ",
	"                                        ",
	NULL
};

static attr_map logo_phoenix_attr_map[]={
	{'*', EFI_RED},
	{'=', EFI_RED},
	{'-', EFI_RED},
	{'+', EFI_RED},
	{':', EFI_RED},
	{0,0}
};

static const char*logo_phoenix_matchs[]={
	"Phoenix",
	"@Phoenix",
	NULL,
};

logo_desc logo_phoenix={
	.main_color=EFI_RED,
	.width=40,
	.lines=logo_phoenix_data,
	.lines_count=sizeof(logo_phoenix_data)/sizeof(logo_phoenix_data[0])-1,
	.attr_map=logo_phoenix_attr_map,
	.attr_map_count=sizeof(logo_phoenix_attr_map)/sizeof(logo_phoenix_attr_map[0])-1,
	.matchs=logo_phoenix_matchs,
};
