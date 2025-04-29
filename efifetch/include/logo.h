#ifndef LOGO_H
#define LOGO_H
#include"efi.h"

typedef struct attr_map{
	char ch;
	uintn_t attr;
}attr_map;

typedef struct logo_desc{
	uintn_t main_color;
	uintn_t width;
	const char*const*lines;
	uintn_t lines_count;
	attr_map*attr_map;
	uintn_t attr_map_count;
	const char*const*matchs;
}logo_desc;

typedef struct logo_context{
	efi_simple_text_output_protocol*con;
	logo_desc*target_logo;
	uintn_t cur_line;
	int margin;
}logo_context;

extern logo_desc*logos[];
extern logo_desc logo_uefi;

extern efi_status logo_desc_print(efi_simple_text_output_protocol*con,logo_desc*logo);
extern efi_status logo_desc_print_line(efi_simple_text_output_protocol*con,logo_desc*logo,uintn_t line);
extern efi_status logo_ctx_init(logo_context*ctx,efi_simple_text_output_protocol*con,logo_desc*logo,uintn_t margin);
extern efi_status logo_ctx_print_line(logo_context*ctx);
extern efi_status logo_ctx_print_line(logo_context*ctx);
extern efi_status logo_ctx_print_remain(logo_context*ctx);
extern logo_desc*logo_find(const char*name);
#endif
