#include"logo.h"

static const char*logo_insyde_data[]={
	"               .:-=++++=-..             ",
	"           .=++++++++++++++++=.         ",
	"         -++++++++=:.       .-=+:       ",
	"       -+++++++-     ..::::.     =-     ",
	"     .-=+++++.   .----===+++++=:.  :.   ",
	"    .--++++-   -----++++=--=++++++. .   ",
	"   .--=+++:  :---=+-.           :=+=    ",
	"   ---=++:  ----=:     -------.   .+=   ",
	"  .---=+=  .----       ...:-=----.  -=  ",
	"  :---=+-  ----              .==--.  -. ",
	"  -----+: .---.                :++=.  . ",
	"  :----=-  :-.                  :++-    ",
	"  .------                        +++.   ",
	"   :----=.                       =+=    ",
	"   .------.                     .++-    ",
	"    .------.                   .++-     ",
	"      -------                 :++.      ",
	"       .------:.           .-=:.        ",
	"         .------                        ",
	"            .:.                         ",
	NULL
};

static attr_map logo_insyde_attr_map[]={
	{'=', EFI_GREEN},
	{'-', EFI_GREEN},
	{'+', EFI_GREEN},
	{':', EFI_GREEN},
	{'.', EFI_GREEN},
	{0,0}
};

static const char*logo_insyde_matchs[]={
	"INSYDE Corp.",
	"@INSYDE",
	NULL,
};

logo_desc logo_insyde={
	.main_color=EFI_GREEN,
	.width=40,
	.lines=logo_insyde_data,
	.lines_count=sizeof(logo_insyde_data)/sizeof(logo_insyde_data[0])-1,
	.attr_map=logo_insyde_attr_map,
	.attr_map_count=sizeof(logo_insyde_attr_map)/sizeof(logo_insyde_attr_map[0])-1,
	.matchs=logo_insyde_matchs,
};
