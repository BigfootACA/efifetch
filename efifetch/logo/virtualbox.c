#include"logo.h"

static const char*logo_virtualbox_data[]={
	"***************           +++++++++++++ ",
	"****************         +++++++++++++++",
	" ***************         +++++++++++++++",
	"  *****    ******       +++++      +++++",
	"  ******    *****       +++++      +++++",
	"   *****    ******     +++++++++++++++++",
	"    *****    ******    +++++++++++++++++",
	"    *****                               ",
	"    ******                              ",
	"     *****                              ",
	"     ******         ********************",
	"      *****        *********************",
	"      ******       *****           *****",
	"       ******     ******           *****",
	"        *****     *****            *****",
	"        ***************    *************",
	"        **************    **************",
	"          ***********     ************* ",
	NULL
};

static attr_map logo_virtualbox_attr_map[]={
	{'*', EFI_BLUE},
	{'+', EFI_YELLOW},
	{0,0}
};

static const char*logo_virtualbox_matchs[]={
	"virtualbox",
	"@virtualbox",
	NULL,
};

logo_desc logo_virtualbox={
	.main_color=EFI_BLUE,
	.width=40,
	.lines=logo_virtualbox_data,
	.lines_count=sizeof(logo_virtualbox_data)/sizeof(logo_virtualbox_data[0])-1,
	.attr_map=logo_virtualbox_attr_map,
	.attr_map_count=sizeof(logo_virtualbox_attr_map)/sizeof(logo_virtualbox_attr_map[0])-1,
	.matchs=logo_virtualbox_matchs,
};
