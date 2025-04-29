#include"info.h"
#include"str.h"
#include"init.h"
#include"print.h"
#include"readable.h"

static void load_from_memmap(efifetch*ctx){
	uint32_t dv=0;
	char buff[32];
	efi_status st;
	efi_memory_descriptor*mm=NULL,*md;
	uintn_t ms=0,mk=0,ds=sizeof(efi_memory_descriptor),size;
	if(!IS_EMPTY(MEMORY))return;
	do{
		ms+=ds;
		if(mm)g_bs->free_pool(mm),mm=NULL;
		size=ms+(2*ds);
		st=g_bs->alloc_pool(efi_loader_data,size,(void**)&mm);
		if(efi_error(st)){
			dbg_printf("alloc memmap failed: %m\n",st);
			break;
		}
		memset(mm,0,size);
		st=g_bs->get_mem_map(&ms,mm,&mk,&ds,&dv);
	}while(st==EFI_BUFFER_TOO_SMALL);
	if(efi_error(st)){
		dbg_printf("get memmap failed: %m\n",st);
		return;
	}
	dbg_printf("memmap size %zu ptr %p key %zu desc size %zu desc ver %u\n",ms,mm,mk,ds,dv);
	if(ds!=sizeof(efi_memory_descriptor)){
		dbg_printf("memmap desc size mismatch: %zu != %zu\n",ds,sizeof(efi_memory_descriptor));
	}
	uint64_t total=0,avail=0;
	for(md=mm;(void*)md<(void*)mm+ms;md=(void*)md+ds)switch(md->type){
		case efi_conventional_memory:
			avail+=md->pages*EFI_PAGE_SIZE;
			//fallthrough
		case efi_loader_code:
		case efi_loader_data:
		case efi_bs_code:
		case efi_bs_data:
		case efi_rs_code:
		case efi_rs_data:
		case efi_acpi_reclaim_memory:
		case efi_acpi_memory_nvs:
		case efi_pal_code:
			total+=md->pages*EFI_PAGE_SIZE;
			//fallthrough
		default:dbg_printf(
			"memmap item phy 0x%012zx virt 0x%012zx "
			"size %llu pages (%s) type %s attrs 0x%llx\n",
			md->physical_start.uintn,md->virtual_start.uintn,md->pages,
			format_size_float(buff,md->pages*EFI_PAGE_SIZE),
			efi_memory_type_to_string(md->type),md->attribute
		);
	}
	g_bs->free_pool(mm);
	if(total==0){
		dbg_print("skip empty memmap\n");
		return;
	}
	uint64_t used=total-avail;
	char buf_used[32],buf_total[32];
	if(!format_size_float(buf_used,used)){
		dbg_print("memmap format size used failed\n");
		return;
	}
	if(!format_size_float(buf_total,total)){
		dbg_print("memmap format size total failed\n");
		return;
	}
	uint64_t percent=used*100/total;
	if(percent>100)percent=100;
	SETF(
		MEMORY,
		"%s / %s (%llu%c)",
		buf_used,buf_total,percent,'%'
	);
}

void efifetch_load_info_mem(efifetch*ctx){
	load_from_memmap(ctx);
}
