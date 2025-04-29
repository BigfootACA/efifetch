#include"logo.h"

static const char*logo_huawei_data[]={
	"              :++=    ---.              ",
	"             **++=-  .:::::             ",
	"        =   =**++==  --::---   -        ",
	"      :***. .***++=. ------. .=++:      ",
	"      *****- +***++-:=====- :+++**      ",
	"      ******+ +****=-++++= =++****      ",
	"      :*******.****==**+*.+******-      ",
	"   =#*. :****** ***--*** ******: .**=   ",
	"   -###**-.-**** =*. *+ ****=.:*****-   ",
	"    =####***=.:+*.-  -.*+:.=*******=    ",
	"      =####*****        +********=      ",
	"      .-====++++-      :+++====--:      ",
	"       .*####=            -*****.       ",
	"                                        ",
	NULL
};

static attr_map logo_huawei_attr_map[]={
	{'*', EFI_RED},
	{'=', EFI_RED},
	{'-', EFI_RED},
	{'+', EFI_RED},
	{':', EFI_RED},
	{0,0}
};

static const char*logo_huawei_matchs[]={
	"HUAWEI",
	"@huawei",
	NULL,
};

logo_desc logo_huawei={
	.main_color=EFI_RED,
	.width=40,
	.lines=logo_huawei_data,
	.lines_count=sizeof(logo_huawei_data)/sizeof(logo_huawei_data[0])-1,
	.attr_map=logo_huawei_attr_map,
	.attr_map_count=sizeof(logo_huawei_attr_map)/sizeof(logo_huawei_attr_map[0])-1,
	.matchs=logo_huawei_matchs,
};
