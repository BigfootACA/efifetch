#include"logo.h"

static const char*logo_tianocore_data[]={
	"                 :+++=:                 ",
	"                 -++++-                 ",
	"                 -++++:                 ",
	"                 :++++:                 ",
	".-=-.            :++++:            .-=-.",
	"++++++-.         :++++.         .-++++++",
	"=++++++++-..     :++++.     ..-++++++++=",
	" ..:+++++++=-.   .++++.   .-=+++++++:.. ",
	"     ..=+++++++-..++++..-+++++++=..     ",
	"         .:++++++++++++++++++:.         ",
	"            ..-++++++++++-..            ",
	"            ..:=++++++++=:..            ",
	"         ..=++++++++++++++++=..         ",
	"     ..-=++++++=:.++++.:=++++++=-..     ",
	" ..:=+++++++=.   .++++.   .=+++++++=... ",
	"-=+++++++=..     :++++.     ..=+++++++=-",
	"=+++++=.         :++++.         .=+++++=",
	".=+=.            :++++:            .=+=.",
	"                 :++++:                 ",
	"                 -++++:                 ",
	"                 -++++-                 ",
	"                 :+++=:                 ",
	NULL
};

static attr_map logo_tianocore_attr_map[]={
	{'+', EFI_RED},
	{'-', EFI_RED},
	{'=', EFI_RED},
	{':', EFI_RED},
	{'.', EFI_RED},
	{0,0}
};

static const char*logo_tianocore_matchs[]={
	"EDK II",
	"EFI Development Kit II",
	"@EFI Development Kit",
	"@EDK",
	NULL,
};

logo_desc logo_tianocore={
	.main_color=EFI_RED,
	.width=40,
	.lines=logo_tianocore_data,
	.lines_count=sizeof(logo_tianocore_data)/sizeof(logo_tianocore_data[0])-1,
	.attr_map=logo_tianocore_attr_map,
	.attr_map_count=sizeof(logo_tianocore_attr_map)/sizeof(logo_tianocore_attr_map[0])-1,
	.matchs=logo_tianocore_matchs,
};
