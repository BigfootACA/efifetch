#include"logo.h"

static const char*logo_hp_data[]={
	"             **   *********             ",
	"         *****    *************         ",
	"       *******   ****************       ",
	"     ********   *******************     ",
	"    ********    *********************   ",
	"  **********   ***********************  ",
	" **********        *******       ****** ",
	" *********           ****           *** ",
	"**********   ****    +***   ****   *****",
	"*********    ***    ****   +***    *****",
	"********    ****   ****    ****   ******",
	"********   ****   *****   ****   *******",
	"*******   *****   ****   ****    *******",
	"*******   ****   ****    ****   ********",
	" *****   ****   ****+    ***   ******** ",
	" ****   +****   ****         ********** ",
	"  *****************    ***************  ",
	"    **************    ***************   ",
	"     *************   **************     ",
	"       **********    ************       ",
	"         ********   ***********         ",
	"             ***   +*******             ",
	NULL
};

static attr_map logo_hp_attr_map[]={
	{'*', EFI_BLUE},
	{'+', EFI_BLUE},
	{0,0}
};

static const char*logo_hp_matchs[]={
	"HP",
	"HPE",
	"@Hewlett Packard",
	"@Hewlett-Packard",
	NULL,
};

logo_desc logo_hp={
	.main_color=EFI_BLUE,
	.width=40,
	.lines=logo_hp_data,
	.lines_count=sizeof(logo_hp_data)/sizeof(logo_hp_data[0])-1,
	.attr_map=logo_hp_attr_map,
	.attr_map_count=sizeof(logo_hp_attr_map)/sizeof(logo_hp_attr_map[0])-1,
	.matchs=logo_hp_matchs,
};
