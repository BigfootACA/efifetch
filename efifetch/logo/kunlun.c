#include"logo.h"

static const char*logo_kunlun_data[]={
	"                                        ",
	"            ####################        ",
	"        #########            ######     ",
	"     ######                       ###   ",
	"   #####    ##                      ### ",
	" ####    #######    ###              ## ",
	"####   #####   ######  #####         ###",
	"### ########      ###  #   #####     ## ",
	"############    # ## ###    ## ##   ### ",
	"### #########   ########    ##  #   ##  ",
	"#### #########   #########   ######     ",
	"############### ###################     ",
	"  ##############################        ",
	"     #######################            ",
	"                                        ",
	NULL
};

static attr_map logo_kunlun_attr_map[]={
	{'#', EFI_BLUE},
	{0,0}
};

static const char*logo_kunlun_matchs[]={
	"$zdtech",
	"$zd-tech",
	"$kunlun",
	NULL,
};

logo_desc logo_kunlun={
	.main_color=EFI_RED,
	.width=40,
	.lines=logo_kunlun_data,
	.lines_count=sizeof(logo_kunlun_data)/sizeof(logo_kunlun_data[0])-1,
	.attr_map=logo_kunlun_attr_map,
	.attr_map_count=sizeof(logo_kunlun_attr_map)/sizeof(logo_kunlun_attr_map[0])-1,
	.matchs=logo_kunlun_matchs,
};
