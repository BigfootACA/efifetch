#include"logo.h"

static const char*logo_qualcomm_data[]={
	"           #****************#           ",
	"        ***********************#        ",
	"      ****************************      ",
	"    ************#      *************    ",
	"   *********#               *********   ",
	"  ********#                  #********  ",
	" #*******                      ******** ",
	" *******                        *******#",
	"*******#                        #*******",
	"*******                          *******",
	"*******                          *******",
	"*******                          *******",
	"*******                          *******",
	"********           #******#     ********",
	" *******            *******     *******#",
	" ********            *******   *******# ",
	"  ********#          *******#********#  ",
	"   *********#         ***************   ",
	"    #************#    #************#    ",
	"      #**************************#      ",
	"        #***********************        ",
	"            ********************#       ",
	"                          *******       ",
	"                          #*******      ",
	"                           *******      ",
	NULL
};

static attr_map logo_qualcomm_attr_map[]={
	{'*', EFI_BLUE},
	{'#', EFI_BLUE},
	{0,0}
};

static const char*logo_qualcomm_matchs[]={
	"Qualcomm Technologies, Inc.",
	"@Qualcomm",
	NULL,
};

logo_desc logo_qualcomm={
	.main_color=EFI_BLUE,
	.width=40,
	.lines=logo_qualcomm_data,
	.lines_count=sizeof(logo_qualcomm_data)/sizeof(logo_qualcomm_data[0])-1,
	.attr_map=logo_qualcomm_attr_map,
	.attr_map_count=sizeof(logo_qualcomm_attr_map)/sizeof(logo_qualcomm_attr_map[0])-1,
	.matchs=logo_qualcomm_matchs,
};
