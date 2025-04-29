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
	char buff[40];
	uintn_t ret=utf16_to_utf8(g_st->firmware_vendor,80,buff,sizeof(buff));
	if(ret==0)return;
	buff[ret]=0;
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
