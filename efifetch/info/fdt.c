#include"info.h"
#include"init.h"
#include"libfdt.h"
#include"print.h"

extern efi_guid gFdtTableGuid;

void efifetch_init_info_fdt(efifetch*ctx){
	int r;
	void*fdt=NULL;
	ctx->fdt=NULL;
	for(uintn_t i=0;i<g_st->entries;i++){
		if(memcmp(&g_st->cfg_table[i].guid,&gFdtTableGuid,sizeof(efi_guid))==0){
			dbg_printf("found fdt cfg table %p\n",fdt);
			fdt=g_st->cfg_table[i].table;
		}
	}
	if(!fdt){
		dbg_print("fdt not found\n");
		return;
	}
	if((r=fdt_check_header(fdt))){
		dbg_printf(
			"fdt check header failed: %s\n",
			fdt_strerror(r)
		);
		return;
	}
	ctx->fdt=fdt;
}

void efifetch_load_info_fdt(efifetch*ctx){
	int len=0;
	const char*data;
	if(!ctx->fdt)return;
	int root=fdt_path_offset(ctx->fdt,"/");
	if(root<0)return;
	if(IS_EMPTY(HOST)&&(data=fdt_getprop(ctx->fdt,root,"model",&len)))
		SETN(HOST,data,len);
	if(IS_EMPTY(NAME)&&(data=fdt_getprop(ctx->fdt,root,"compatible",&len)))
		SETN(NAME,data,len);
}
