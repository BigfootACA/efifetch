#include"efi.h"
#include"init.h"
#include"print.h"

efi_handle g_ih=NULL;
efi_system_table*g_st=NULL;
efi_boot_services*g_bs=NULL;
efi_runtime_services*g_rt=NULL;

void efiapi initialize(efi_handle ih,efi_system_table*st){
	g_ih=ih,g_st=st;
	if(st){
		g_bs=st->boot_services,
		g_rt=st->runtime_services;
	}
	print_init();
}
