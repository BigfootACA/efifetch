#include"logo.h"

static const char*logo_quanta_data[]={
	"            #########                   ",
	"        ##################              ",
	"     #######################            ",
	"    ##########      ##########          ",
	"  ########             ########         ",
	" #######                 #######        ",
	" ######                   #######       ",
	"######                     ######       ",
	"######                     ######       ",
	"######                                  ",
	"######          ************************",
	" ######          ***********************",
	" #######                                ",
	"  ########         *********************",
	"    ##########      ********************",
	"      ###########                       ",
	"        #########       ****************",
	"             ####        ***************",
	NULL
};

static attr_map logo_quanta_attr_map[]={
	{'#', EFI_BLUE},
	{'*', EFI_RED},
	{0,0}
};

static const char*logo_quanta_matchs[]={
	"QUANTA",
	"@QUANTA",
	NULL,
};

logo_desc logo_quanta={
	.main_color=EFI_BLUE,
	.width=40,
	.lines=logo_quanta_data,
	.lines_count=sizeof(logo_quanta_data)/sizeof(logo_quanta_data[0])-1,
	.attr_map=logo_quanta_attr_map,
	.attr_map_count=sizeof(logo_quanta_attr_map)/sizeof(logo_quanta_attr_map[0])-1,
	.matchs=logo_quanta_matchs,
};
