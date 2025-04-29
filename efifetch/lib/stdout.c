#define STB_SPRINTF_NOFLOAT
#include"efi.h"
#include"init.h"
#include"print.h"
#include"stb_sprintf.h"

uintn_t con_stdout_def_attr=EFI_WHITE|EFI_BACKGROUND_BLACK;

efi_status out_printf(const char*str,...){
	va_list va;
	if(!stdout)return efi_device_error;
	va_start(va,str);
	efi_status st=text_vprintf(stdout,str,va);
	va_end(va);
	return st;
}

efi_status out_vprintf(const char*str,va_list va){
	if(!stdout)return efi_device_error;
	return text_vprintf(stdout,str,va);
}

efi_status out_print(const char*str){
	if(!stdout)return efi_device_error;
	return text_print(stdout,str);
}

efi_status out_printn(const char*str,size_t len){
	if(!stdout)return efi_device_error;
	return text_printn(stdout,str,len);
}

efi_status out_setattr(uintn_t attr){
	if(!stdout)return efi_device_error;
	return stdout->set_attribute(stdout,attr);
}

efi_status out_resetattr(void){
	return out_setattr(con_stdout_def_attr);
}
