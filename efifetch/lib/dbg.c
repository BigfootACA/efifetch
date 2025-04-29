#define STB_SPRINTF_NOFLOAT
#include"efi.h"
#include"print.h"
#include"stb_sprintf.h"

efi_simple_text_output_protocol*debug_output=NULL;

efi_status dbg_printf(const char*str,...){
	va_list va;
	if(!debug_output)return efi_success;
	va_start(va,str);
	efi_status st=text_vprintf(debug_output,str,va);
	va_end(va);
	return st;
}

efi_status dbg_vprintf(const char*str,va_list va){
	if(!debug_output)return efi_success;
	return text_vprintf(debug_output,str,va);
}

efi_status dbg_print(const char*str){
	if(!debug_output)return efi_success;
	return text_print(debug_output,str);
}

efi_status dbg_printn(const char*str,size_t len){
	if(!debug_output)return efi_success;
	return text_printn(debug_output,str,len);
}
