#include "efi.h"
#include"info.h"
#include"init.h"
#include "print.h"
#include"str.h"

static void efifetch_load_info_sys_firmware(efifetch*ctx){
	if(!IS_EMPTY(FIRMWARE))return;
	if(g_st->firmware_vendor||!g_st->firmware_vendor[0]){
		dbg_print("system table firmware vendor is empty\n");
		return;
	}
	char buff[64];
	encode_convert_ctx conv={};
	conv.in.src=ENC_UTF16;
	conv.in.dst=ENC_UTF8;
	conv.in.src_ptr=(void*)g_st->firmware_vendor;
	conv.in.src_size=40*sizeof(char16);
	conv.in.dst_ptr=buff;
	conv.in.dst_size=sizeof(buff);
	conv.in.allow_invalid=true;
	encode_convert(&conv);
	if(conv.out.dst_wrote==0)return;
	APPENDF(
		FIRMWARE,"%s %u.%u",buff,
		(g_st->firmware_revision>>0x10)&0xFFFF,
		(g_st->firmware_revision>>0x00)&0xFFFF
	);
}

static void efifetch_load_info_sys_secureboot(efifetch*ctx){
	uintn_t var_size;
	efi_status st;
	uint8_t secureboot=0,setup=0;
	if(!IS_EMPTY(SECURE_BOOT))return;
	var_size=sizeof(secureboot);
	st=g_rt->get_var(
		L"SecureBoot",
		&gEfiGlobalVariableGuid,
		NULL,
		&var_size,
		&secureboot
	);
	if(efi_error(st)){
		dbg_printf("variable get secure boot failed: %m\n",st);
		SET(SECURE_BOOT,"unsupported");
		return;
	}
	if(secureboot==0)SET(SECURE_BOOT,"disabled");
	if(secureboot==1)SET(SECURE_BOOT,"enabled");
	var_size=sizeof(setup);
	st=g_rt->get_var(
		L"SetupMode",
		&gEfiGlobalVariableGuid,
		NULL,
		&var_size,
		&setup
	);
	if(efi_error(st)){
		dbg_printf("variable get setup mode failed: %m\n",st);
		return;
	}
	if(setup==0)APPEND(SECURE_BOOT," (user)");
	if(setup==1)APPEND(SECURE_BOOT," (setup)");
}

void efifetch_load_info_sys(efifetch*ctx){
	efifetch_load_info_sys_firmware(ctx);
	efifetch_load_info_sys_secureboot(ctx);
	SETF(
		SPEC,"UEFI v%u.%u",
		g_st->header.rev_major,
		g_st->header.rev_minor
	);
}
