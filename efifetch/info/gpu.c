#include"data.h"
#include"info.h"
#include"init.h"
#include"str.h"
#include"print.h"
#include"pci.h"
#include"utils.h"

static void load_display(efifetch*ctx,efi_handle hand){
	efi_status st;
	efi_graphics_output_protocol*gop=NULL;
	if(!IS_EMPTY(DISPLAY))return;
	st=hand?g_bs->handle_proto(
		hand,&gEfiGraphicsOutputProtocolGuid,(void**)&gop
	):g_bs->locate_proto(
		&gEfiGraphicsOutputProtocolGuid,NULL,(void**)&gop
	);
	if(efi_error(st)){
		dbg_printf("get gop failed: %m\n",st);
		return;
	}
	if(!gop||!gop->mode||!gop->mode->info){
		dbg_print("invalid gop\n");
		return;
	}
	SETF(
		DISPLAY,"%ux%u",
		gop->mode->info->width,
		gop->mode->info->height
	);
	if(gop->mode->fb_base.ptr)
		APPENDF(DISPLAY," at 0x%llx",gop->mode->fb_base.uint64);
	else if(gop->mode->info->format==PIXEL_BLT_ONLY)
		APPEND(DISPLAY," blt-only");

}

static bool find_pci_gpu(efi_handle*orig,efi_handle*pci){
	efi_status st;
	efi_handle*hands=NULL;
	uintn_t hand_cnt=0;
	st=g_bs->locate_handle_buffer(
		search_by_protocol,
		&gEfiGraphicsOutputProtocolGuid,
		NULL,&hand_cnt,&hands
	);
	if(efi_error(st)||!hands){
		dbg_printf("locate gpu handle failed: %m\n",st);
		return false;
	}
	dbg_printf("found %zu gpu handles\n",hand_cnt);
	for(uintn_t i=0;i<hand_cnt;i++){
		efi_handle hand=hands[i];
		dbg_printf("start detect handle %zu %p\n",i,hand);
		do{
			dbg_printf("try handle %p\n",hand);
			efi_pci_io_protocol*pci_io=NULL;
			st=g_bs->handle_proto(hand,&gEfiPciIoProtocolGuid,(void**)&pci_io);
			if(!efi_error(st)&&pci_io){
				*pci=hand;
				*orig=hands[i];
				dbg_printf("found gpu handle %p\n",*pci);
				g_bs->free_pool(hands);
				return true;
			}
			dbg_printf("handle %p pci io failed: %m\n",hand,st);
			dbg_printf("try handle %p parent\n",hand);
		}while((hand=efi_get_parent_device(hand)));
	}
	dbg_print("no gpu handle found\n");
	g_bs->free_pool(hands);
	return false;
}

static void load_gpu(efifetch*ctx,efi_handle gpu,efi_handle pci){
	efi_status st;
	gpu_item*ven_item=NULL,*dev_item=NULL;
	efi_pci_io_protocol*pci_io=NULL;
	pci_device_independent_region dir;
	if(!pci||!IS_EMPTY(GPU))return;
	memset(&dir,0,sizeof(dir));
	st=g_bs->handle_proto(pci,&gEfiPciIoProtocolGuid,(void**)&pci_io);
	if(efi_error(st)||!pci_io){
		dbg_printf("handle %p pci io failed: %m\n",pci,st);
		return;
	}
	dbg_printf("gpu pci io protocol %p\n",pci_io);
	st=pci_io->pci.read(pci_io,pciw_u16,0,sizeof(dir),&dir);
	if(efi_error(st)){
		dbg_printf("read pci config failed: %m\n",st);
		return;
	}
	dbg_printf(
		"found gpu vendor 0x%04x device 0x%04x\n",
		dir.vendor_id,dir.device_id
	);
	if(!dir.vendor_id||!dir.device_id)return;
	for(uintn_t i=0;gpu_db[i].name;i++){
		if(gpu_db[i].vendor!=dir.vendor_id)continue;
		if(gpu_db[i].device==dir.device_id){
			dev_item=&gpu_db[i];
			dbg_printf("found gpu device in database: %s\n",gpu_db[i].name);
		}
		if(gpu_db[i].device==0xFFFF){
			ven_item=&gpu_db[i];
			dbg_printf("found gpu vendor in database: %s\n",gpu_db[i].name);
		}
		if(ven_item&&dev_item)break;
	}
	SET(GPU,"PCIe /");
	if(ven_item||dev_item){
		if(ven_item){
			if(!IS_EMPTY(GPU))APPEND(GPU," ");
			APPEND(GPU,ven_item->name);
		}
		if(dev_item){
			if(!IS_EMPTY(GPU))APPEND(GPU," ");
			APPEND(GPU,dev_item->name);
		}
	}else APPENDF(GPU," %04x:%04x",dir.vendor_id,dir.device_id);
}

void efifetch_load_info_gpu(efifetch*ctx){
	efi_handle gpu=NULL,pci=NULL;
	find_pci_gpu(&gpu,&pci);
	load_display(ctx,gpu);
	load_gpu(ctx,gpu,pci);
}
