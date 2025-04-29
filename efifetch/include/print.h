#ifndef PRINT_H
#define PRINT_H
#include"efi.h"
extern efi_simple_text_output_protocol*debug_output;
extern efi_status text_print_repeat(efi_simple_text_output_protocol*con,char ch,uintn_t cnt);
extern efi_status text_print(efi_simple_text_output_protocol*con,const char*str);
extern efi_status text_printn(efi_simple_text_output_protocol*con,const char*str,size_t len);
extern efi_status text_printf(efi_simple_text_output_protocol*con,const char*str,...);
extern efi_status text_vprintf(efi_simple_text_output_protocol*con,const char*str,va_list va);
extern efi_status dbg_print(const char*str);
extern efi_status dbg_printn(const char*str,size_t len);
extern efi_status dbg_printf(const char*str,...);
extern efi_status dbg_vprintf(const char*str,va_list va);
extern efi_status out_print(const char*str);
extern efi_status out_printn(const char*str,size_t len);
extern efi_status out_printf(const char*str,...);
extern efi_status out_vprintf(const char*str,va_list va);
extern efi_status err_print(const char*str);
extern efi_status err_printn(const char*str,size_t len);
extern efi_status err_printf(const char*str,...);
extern efi_status err_vprintf(const char*str,va_list va);
extern efi_status out_setattr(uintn_t attr);
extern efi_status err_setattr(uintn_t attr);
extern efi_status out_resetattr(void);
extern efi_status err_resetattr(void);
extern void print_init();
#endif
