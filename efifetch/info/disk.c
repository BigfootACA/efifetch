#include"info.h"
#include"readable.h"
#include"print.h"
#include"utils.h"
#include"init.h"
#include"disk.h"
#include"str.h"

static bool get_cur_disk_info(efi_handle*hand,efi_disk_info_protocol**di){
	efi_status st;
	efi_handle h=efi_get_current_device();
	while(h){
		efi_disk_info_protocol*info=NULL;
		st=g_bs->handle_proto(h,&gEfiDiskInfoProtocolGuid,(void**)&info);
		if(!efi_error(st)&&info){
			*hand=h,*di=info;
			return true;
		}
		dbg_printf("disk %p get disk info protocol: %m\n",h,st);
		h=efi_get_parent_device(h);
	}
	return false;
}

struct disk_info{
	char type[64];
	char vendor[64];
	char model[64];
	uint64_t size;
};

static efi_status disk_fill_size_block_io(efi_handle hand,struct disk_info*info){
	efi_status st;
	efi_block_io_protocol*bio=NULL;
	st=g_bs->handle_proto(hand,&gEfiBlockIoProtocolGuid,(void**)&bio);
	if(efi_error(st)){
		dbg_printf("disk %p get block io failed: %m\n",hand,st);
		return st;
	}
	dbg_printf("disk %p found block io %p\n",hand,bio);
	dbg_printf("disk %p last blocks %llu\n",hand,bio->media->last_block);
	dbg_printf("disk %p last blocks 0x%llx\n",hand,bio->media->last_block);
	uint64_t blocks=bio->media->last_block+1;
	dbg_printf("disk %p blocks %llu\n",hand,blocks);
	dbg_printf("disk %p block size %u\n",hand,bio->media->block_size);
	info->size=bio->media->block_size*blocks;
	dbg_printf("disk %p size %llu\n",hand,info->size);
	return efi_success;
}

static efi_status disk_get_scsi(efi_handle hand,efi_disk_info_protocol*proto,struct disk_info*info){
	efi_status st;
	scsi_inquiry_data data;
	uint32_t size=sizeof(data);
	memset(&data,0,size);
	st=proto->inquiry(proto,&data,&size);
	if(efi_error(st)){
		dbg_printf("disk %p usb inquiry failed: %m\n",hand,st);
		return st;
	}
	memcpy(info->vendor,data.vendor_id,sizeof(data.vendor_id));
	memcpy(info->model,data.product_id,sizeof(data.product_id));
	return efi_success;
}

static efi_status disk_get_usb(efi_handle hand,efi_disk_info_protocol*proto,struct disk_info*info){
	efi_status st;
	usb_boot_inquiry_data data;
	uint32_t size=sizeof(data);
	memset(&data,0,size);
	st=proto->inquiry(proto,&data,&size);
	if(efi_error(st)){
		dbg_printf("disk %p usb inquiry failed: %m\n",hand,st);
		return st;
	}
	memcpy(info->vendor,data.vendor_id,sizeof(data.vendor_id));
	memcpy(info->model,data.product_id,sizeof(data.product_id));
	return efi_success;
}

static efi_status disk_get_ata(efi_handle hand,efi_disk_info_protocol*proto,struct disk_info*info){
	efi_status st;
	ata_identify_data data;
	uint32_t size=sizeof(data);
	memset(&data,0,size);
	st=proto->identify(proto,&data,&size);
	if(efi_error(st)){
		dbg_printf("disk %p ata inquiry failed: %m\n",hand,st);
		return st;
	}
	for(uintn_t i=0;i+1<sizeof(data.model_name);i+=2){
		info->model[i]=data.model_name[i+1];
		info->model[i+1]=data.model_name[i];
	}
	return efi_success;
}

static efi_status disk_get_nvme(efi_handle hand,efi_disk_info_protocol*proto,struct disk_info*info){
	efi_status st;
	nvme_admin_controller_data data;
	efi_nvme_passthru_protocol*pt=NULL;
	efi_nvme_passthru_cmd_pkt cmdpkt;
	efi_nvme_completion comp;
	efi_device_path_protocol*dp;
	efi_handle handle=hand;
	efi_nvme_cmd cmd;
	memset(&cmd,0,sizeof(cmd));
	memset(&cmdpkt,0,sizeof(cmdpkt));
	memset(&comp,0,sizeof(comp));
	memset(&data,0,sizeof(data));
	st=g_bs->handle_proto(hand,&gEfiDevicePathProtocolGuid,(void**)&dp);
	if (efi_error (st)) {
		dbg_printf("disk %p handle device path failed: %m\n",hand,st);
		return st;
	}
	st=g_bs->locate_device_path(&gEfiNvmExpressPassThruProtocolGuid,&dp,&handle);
	if(efi_error(st)||!handle){
		dbg_printf("disk %p handle get controller failed: %m\n",hand,st);
		return st;
	}
	if(dp->type!=3||dp->sub_type!=0x17){
		dbg_printf("disk %p device path type mismatch %x %x\n",hand,dp->type,dp->sub_type);
		return efi_unsupported;
	}
	dbg_printf("disk %p found nvme controller handle %p\n",hand,handle);
	st=g_bs->handle_proto(handle,&gEfiNvmExpressPassThruProtocolGuid,(void**)&pt);
	if(efi_error(st)||!pt){
		dbg_printf("disk %p handle get passthru protocol failed: %m\n",handle,st);
		return st;
	}
	cmd.cdw0.opcode=6;
	cmd.nsid=0;
	cmdpkt.nvme_cmd=&cmd;
	cmdpkt.nvme_completion=&comp;
	cmdpkt.transfer_buffer=&data;
	cmdpkt.transfer_length=sizeof(data);
	cmdpkt.cmd_timeout=50000000;
	cmdpkt.queue_type=NVME_ADMIN_QUEUE;
	cmd.cdw10=1;
	cmd.flags=CDW10_VALID;
	st=pt->passthru(pt,0,&cmdpkt,NULL);
	if(efi_error(st)){
		dbg_printf("disk %p nvme passthru failed: %m\n",handle,st);
		return st;
	}
	memcpy(info->model,data.mn,sizeof(data.mn));
	return efi_success;
}

static efi_status disk_get_sdmmc(efi_handle hand,efi_disk_info_protocol*proto,struct disk_info*info){
	return efi_unsupported;
}

static struct disk_type{
	const char*name;
	const efi_guid*intf;
	efi_status(*get_info)(efi_handle hand,efi_disk_info_protocol*proto,struct disk_info*info);
}disk_types[]={
	{"IDE",    &gEfiDiskInfoIdeInterfaceGuid,   disk_get_ata},
	{"SCSI",   &gEfiDiskInfoScsiInterfaceGuid,  disk_get_scsi},
	{"USB",    &gEfiDiskInfoUsbInterfaceGuid,   disk_get_usb},
	{"SATA",   &gEfiDiskInfoAhciInterfaceGuid,  disk_get_ata},
	{"NVMe",   &gEfiDiskInfoNvmeInterfaceGuid,  disk_get_nvme},
	{"UFS",    &gEfiDiskInfoUfsInterfaceGuid,   disk_get_scsi},
	{"SD/MMC", &gEfiDiskInfoSdMmcInterfaceGuid, disk_get_sdmmc},
	{NULL,NULL,NULL}
};

void efifetch_load_info_disk(efifetch*ctx){
	efi_status st;
	efi_handle handle=NULL;
	efi_disk_info_protocol*info=NULL;
	if(!IS_EMPTY(DISK))return;
	get_cur_disk_info(&handle,&info);
	if(!handle||!info){
		dbg_print("skip disk because no handle or info\n");
		return;
	}
	RESET(DISK);
	struct disk_type*t;
	for(uintn_t i=0;disk_types[i].intf;i++)
		if(memcmp(&info->interface,disk_types[i].intf,sizeof(efi_guid))==0)
			t=&disk_types[i];
	SET(DISK,t->name);
	struct disk_info dinfo={};
	st=t->get_info(handle,info,&dinfo);
	if(efi_error(st)){
		dbg_printf("disk %p get info failed: %m\n",handle,st);
		return;
	}
	char str_size[32]={};
	trim(dinfo.type);
	trim(dinfo.vendor);
	trim(dinfo.model);
	if(dinfo.type[0])SET(DISK,dinfo.type);
	if(dinfo.vendor[0]){
		if(!IS_EMPTY(DISK))APPEND(DISK," / ");
		APPEND(DISK,dinfo.vendor);
	}
	if(dinfo.model[0]){
		if(!IS_EMPTY(DISK))APPEND(DISK," / ");
		APPEND(DISK,dinfo.model);
	}
	if(dinfo.size==0)disk_fill_size_block_io(handle,&dinfo);
	if(dinfo.size>0){
		format_size_float_ex(
			str_size,sizeof(str_size),
			dinfo.size,size_units_b,1000,2
		);
		if(!IS_EMPTY(DISK))APPEND(DISK," / ");
		APPEND(DISK,str_size);
	}
}
