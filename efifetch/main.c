#include"efi.h"
#include"efifetch.h"
#include"str.h"
#include"init.h"
#include"print.h"
#include"utils.h"
#include"logo.h"

static efifetch ctx;

static logo_desc*logo_find_firmware(void){
	char buff[512];
	logo_desc*d;
	memset(buff,0,sizeof(buff));
	const char*firm=ctx.fields[EFIFETCH_FIELD_FIRMWARE].value;
	if(firm[0]){
		dbg_printf("find logo by %s\n",firm);
		if((d=logo_find(firm))){
			dbg_printf("found logo %p\n",d);
			return d;
		}
		dbg_printf("no logo match with %s\n",firm);
	}
	if(g_st&&g_st->firmware_vendor)
		utf16_to_utf8(g_st->firmware_vendor,80,buff,sizeof(buff));
	if(buff[0]){
		dbg_printf("find logo by %s\n",buff);
		if((d=logo_find(buff))){
			dbg_printf("found logo %p\n",d);
			return d;
		}
		dbg_printf("no logo match with %s\n",buff);
	}
	dbg_print("using fallback default logo\n");
	return &logo_uefi;
}

static void load_options(void){
	char options[512]={};
	efi_loaded_image_protocol*li=NULL;
	li=efi_get_loaded_image();
	if(!li||!li->load_options)return;
	utf16_to_utf8(
		li->load_options,
		li->load_options_size,
		options,sizeof(options)
	);
	if(!options[0])return;
	if(strcasestr(options,"--debug"))
		debug_output=stderr;
}

efi_status efiapi uefi_main(
	efi_handle image_handle,
	efi_system_table*system_table
){
	memset(&ctx,0,sizeof(ctx));
	load_options();
	efifetch_load_info(&ctx);
	logo_desc*logo=logo_find_firmware();
	logo_ctx_init(&ctx.logo,stdout,logo,2);
	efifetch_print_all(&ctx);
	out_resetattr();
	err_resetattr();
	return efi_success;
}
