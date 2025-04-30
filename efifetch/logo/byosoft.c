#include"logo.h"

static const char*logo_byosoft_data[]={
"                                        ",
"            #####      #######          ",
"           #####      #########         ",
"          #####      ###########        ",
"         #####      #############       ",
"        ##########################      ",
"       ################*##### #####     ",
"        ##############*#####   ######   ",
"               ######*#####   # ######  ",
"   ####       ######*#####   ### #####* ",
"  #################*#####   #########*  ",
" #################*#####      ######*   ",
"  ###############*#####   ##   ####*    ",
"   ###############*###   ####   ##*     ",
"     ######  ######*####  #####         ",
"       #####  ######*####  #####        ",
"         #####  ######*########*        ",
"          #####  #############*         ",
"            #################*          ",
"              ##############*           ",
"                                        ",
	NULL
};

static attr_map logo_byosoft_attr_map[]={
	{'#', EFI_RED},
	{'*', EFI_LIGHTRED},
	{0,0}
};

static const char*logo_byosoft_matchs[]={
	"@byosoft",
	NULL,
};

logo_desc logo_byosoft={
	.main_color=EFI_RED,
	.width=40,
	.lines=logo_byosoft_data,
	.lines_count=sizeof(logo_byosoft_data)/sizeof(logo_byosoft_data[0])-1,
	.attr_map=logo_byosoft_attr_map,
	.attr_map_count=sizeof(logo_byosoft_attr_map)/sizeof(logo_byosoft_attr_map[0])-1,
	.matchs=logo_byosoft_matchs,
};
