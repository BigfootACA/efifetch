#include"logo.h"

static const char*logo_ami_data[]={
	"                   .*#.                 ",
	"                  -####-                ",
	"                :########               ",
	"               ***********-             ",
	"             :::::::::-----:.           ",
	"             ..........:****+.          ",
	"          +####**********#####*         ",
	"        :#######:       .#######:       ",
	"       :::::-----:     :::::-----:      ",
	"             =****=         .=****+.    ",
	"    ..........:#####=..........#####-   ",
	"  :+++++++++++++++++++++++++++++*#####: ",
	":######################################-",
	NULL
};

static attr_map logo_ami_attr_map[]={
	{'+', EFI_RED},
	{'-', EFI_RED},
	{'=', EFI_RED},
	{':', EFI_RED},
	{'.', EFI_RED},
	{'*', EFI_RED},
	{0,0}
};

static const char*logo_ami_matchs[]={
	"American Megatrends",
	"@American Megatrends",
	"@AMI",
	NULL,
};

logo_desc logo_ami={
	.main_color=EFI_RED,
	.width=40,
	.lines=logo_ami_data,
	.lines_count=sizeof(logo_ami_data)/sizeof(logo_ami_data[0])-1,
	.attr_map=logo_ami_attr_map,
	.attr_map_count=sizeof(logo_ami_attr_map)/sizeof(logo_ami_attr_map[0])-1,
	.matchs=logo_ami_matchs,
};
