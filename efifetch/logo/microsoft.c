#include"logo.h"

static const char*logo_microsoft_data[]={
	"###################  *******************",
	"###################  *******************",
	"###################  *******************",
	"###################  *******************",
	"###################  *******************",
	"###################  *******************",
	"###################  *******************",
	"###################  *******************",
	"                                        ",
	"@@@@@@@@@@@@@@@@@@@  %%%%%%%%%%%%%%%%%%%",
	"@@@@@@@@@@@@@@@@@@@  %%%%%%%%%%%%%%%%%%%",
	"@@@@@@@@@@@@@@@@@@@  %%%%%%%%%%%%%%%%%%%",
	"@@@@@@@@@@@@@@@@@@@  %%%%%%%%%%%%%%%%%%%",
	"@@@@@@@@@@@@@@@@@@@  %%%%%%%%%%%%%%%%%%%",
	"@@@@@@@@@@@@@@@@@@@  %%%%%%%%%%%%%%%%%%%",
	"@@@@@@@@@@@@@@@@@@@  %%%%%%%%%%%%%%%%%%%",
	"@@@@@@@@@@@@@@@@@@@  %%%%%%%%%%%%%%%%%%%",
	NULL
};

static attr_map logo_microsoft_attr_map[]={
	{'#', EFI_RED},
	{'*', EFI_GREEN},
	{'@', EFI_BLUE},
	{'%', EFI_YELLOW},
	{0,0}
};

static const char*logo_microsoft_matchs[]={
	"Microsoft",
	"Surface",
	"MSFT",
	"@microsoft",
	"@surface",
	"@msft",
	NULL,
};

logo_desc logo_microsoft={
	.main_color=EFI_GREEN,
	.width=40,
	.lines=logo_microsoft_data,
	.lines_count=sizeof(logo_microsoft_data)/sizeof(logo_microsoft_data[0])-1,
	.attr_map=logo_microsoft_attr_map,
	.attr_map_count=sizeof(logo_microsoft_attr_map)/sizeof(logo_microsoft_attr_map[0])-1,
	.matchs=logo_microsoft_matchs,
};
