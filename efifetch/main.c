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
	if(g_st&&g_st->firmware_vendor){
		encode_convert_ctx conv={};
		conv.in.src=ENC_UTF16;
		conv.in.dst=ENC_UTF8;
		conv.in.src_ptr=(void*)g_st->firmware_vendor;
		conv.in.src_size=80*sizeof(char16);
		conv.in.dst_ptr=buff;
		conv.in.dst_size=sizeof(buff);
		conv.in.allow_invalid=true;
		encode_convert(&conv);
	}
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
	encode_convert_ctx ctx={};
	ctx.in.src=ENC_UTF16;
	ctx.in.dst=ENC_UTF8;
	ctx.in.src_ptr=li->load_options;
	ctx.in.src_size=li->load_options_size;
	ctx.in.dst_ptr=options;
	ctx.in.dst_size=sizeof(options);
	ctx.in.allow_invalid=true;
	encode_convert(&ctx);
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
