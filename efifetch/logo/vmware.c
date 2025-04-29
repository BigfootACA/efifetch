#include"logo.h"

static const char*logo_vmware_data[]={
	"             ++++++++++++++++++++++++   ",
	"           ++++++++++++++++++++++++++++ ",
	"          ++++++++++++++++++++++++++++++",
	"          ++++++                  ++++++",
	"          +++++                    +++++",
	"  **************************.      +++++",
	" *****************************     +++++",
	"*******************************    +++++",
	"*******   +++++        ********    +++++",
	"******    +++++          ******    +++++",
	"******    +++++          ******    +++++",
	"******    +++++          ******    +++++",
	"******    ++++++         ******   ++++++",
	"******    ++++++++++++++++++++++++++++++",
	"******     ++++++++++++++++++++++++++++ ",
	"******      ++++++++++++++++++++++++++  ",
	"******                  ******          ",
	"*******                *******          ",
	"******************************          ",
	"******************************          ",
	"  **************************            ",
	NULL
};

static attr_map logo_vmware_attr_map[]={
	{'+', EFI_BLUE},
	{'*', EFI_YELLOW},
	{0,0}
};

static const char*logo_vmware_matchs[]={
	"VMware",
	"@vmware",
	NULL,
};

logo_desc logo_vmware={
	.main_color=EFI_YELLOW,
	.width=40,
	.lines=logo_vmware_data,
	.lines_count=sizeof(logo_vmware_data)/sizeof(logo_vmware_data[0])-1,
	.attr_map=logo_vmware_attr_map,
	.attr_map_count=sizeof(logo_vmware_attr_map)/sizeof(logo_vmware_attr_map[0])-1,
	.matchs=logo_vmware_matchs,
};
