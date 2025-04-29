#define STB_SPRINTF_NOFLOAT
#include"efi.h"
#include"init.h"
#include"print.h"
#include"stb_sprintf.h"

uintn_t con_stderr_def_attr=EFI_WHITE|EFI_BACKGROUND_BLACK;

efi_status err_printf(const char*str,...){
	va_list va;
	if(!stderr)return efi_device_error;
	va_start(va,str);
	efi_status st=text_vprintf(stderr,str,va);
	va_end(va);
	return st;
}

efi_status err_vprintf(const char*str,va_list va){
	if(!stderr)return efi_device_error;
	return text_vprintf(stderr,str,va);
}

efi_status err_print(const char*str){
	if(!stderr)return efi_device_error;
	return text_print(stderr,str);
}

efi_status err_printn(const char*str,size_t len){
	if(!stderr)return efi_device_error;
	return text_printn(stderr,str,len);
}

efi_status err_setattr(uintn_t attr){
	if(!stderr)return efi_device_error;
	return stderr->set_attribute(stderr,attr);
}

efi_status err_resetattr(void){
	return err_setattr(con_stderr_def_attr);
}
