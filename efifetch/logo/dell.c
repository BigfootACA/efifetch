#include"logo.h"

static const char*logo_dell_data[]={
	"             **************             ",
	"         **********************         ",
	"       ****                  *****      ",
	"     ****                      *****    ",
	"   ****                           ****  ",
	" ****                              **** ",
	" ***                                ****",
	"***  ****    ******   *       *      ***",
	"***  *   **  *        *       *      ***",
	"***  *    *  ******   *       *      ***",
	"***  *   **  *        *       *      ***",
	"***  ****    ******   *****   *****  ***",
	" ***                                ****",
	" ****                              **** ",
	"  ****                            ****  ",
	"   ****                          ****   ",
	"      *****                   *****     ",
	"         **********************         ",
	"             **************             ",
	NULL
};

static attr_map logo_dell_attr_map[]={
	{'*', EFI_BLUE},
	{0,0}
};

static const char*logo_dell_matchs[]={
	"Dell Inc.",
	"Dell Inc",
	"Dell",
	"$^.*Dell.*$",
	NULL,
};

logo_desc logo_dell={
	.main_color=EFI_BLUE,
	.width=40,
	.lines=logo_dell_data,
	.lines_count=sizeof(logo_dell_data)/sizeof(logo_dell_data[0])-1,
	.attr_map=logo_dell_attr_map,
	.attr_map_count=sizeof(logo_dell_attr_map)/sizeof(logo_dell_attr_map[0])-1,
	.matchs=logo_dell_matchs,
};
