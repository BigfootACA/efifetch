#include"efi.h"
#include"init.h"
#include"print.h"
#include"utils.h"
#include"str.h"

efi_loaded_image_protocol*efi_get_loaded_image(void){
	efi_status st;
	efi_loaded_image_protocol*li=NULL;
	st=g_bs->handle_proto(g_ih,&gEfiLoadedImageProtocolGuid,(void**)&li);
	if(efi_error(st))return NULL;
	return li;
}

efi_handle efi_get_current_device(void){
	efi_loaded_image_protocol*li=efi_get_loaded_image();
	return li?li->device_handle:NULL;
}

efi_device_path_protocol*efi_device_path_next(efi_device_path_protocol*dp){
	if(!dp||dp->length==0)return NULL;
	efi_device_path_protocol*next_dp=(void*)dp+dp->length;
	if(next_dp->length==0)return NULL;
	return next_dp;
}

uintn_t efi_device_path_len(efi_device_path_protocol*dp){
	uintn_t dp_len=0;
	if(dp)do{
		dp_len+=dp->length;
		if(dp->type==0x7f)break;
	}while((dp=efi_device_path_next(dp)));
	return dp_len;
}

uintn_t efi_device_path_count(efi_device_path_protocol*dp){
	uintn_t cnt=0;
	if(dp)do{
		if(dp->type==0x7f)break;
		cnt++;
	}while((dp=efi_device_path_next(dp)));
	return cnt;
}

efi_handle efi_get_parent_device(efi_handle handle){
	efi_status st;
	efi_device_path_protocol*dp=NULL;
	if(!handle)return NULL;
	st=g_bs->handle_proto(handle,&gEfiDevicePathProtocolGuid,(void**)&dp);
	if(efi_error(st)||!dp)return NULL;
	uintn_t dp_len=0,cnt=0;
	dp_len=efi_device_path_len(dp);
	cnt=efi_device_path_count(dp);
	if(cnt<=1)return NULL;
	efi_device_path_protocol*par_dp=NULL;
	if(!(par_dp=memdup(dp,dp_len)))return NULL;
	efi_device_path_protocol*last_dp=NULL,*next_dp=NULL;
	last_dp=par_dp;
	while(true){
		next_dp=efi_device_path_next(last_dp);
		if(!next_dp||next_dp->type==0x7f){
			last_dp->type=0x7f;
			last_dp->sub_type=0xff;
			last_dp->length=sizeof(efi_device_path_protocol);
			break;
		}
		last_dp=next_dp;
	}
	efi_handle parent=NULL;
	efi_device_path_protocol*loc_dp=par_dp;
	st=g_bs->locate_device_path(&gEfiDevicePathProtocolGuid,&loc_dp,&parent);
	g_bs->free_pool(par_dp);
	if(efi_error(st)||!parent)return NULL;
	if(parent==handle)return NULL;
	return parent;
}

void*efi_file_get_info_by(efi_file_protocol*f,const efi_guid*guid){
	void*info=NULL;
	uintn_t size=0;
	efi_status st;
	if(!f||!guid)return NULL;
	st=f->get_info(f,guid,&size,NULL);
	if(st!=EFI_BUFFER_TOO_SMALL||size==0)return NULL;
	st=g_bs->alloc_pool(efi_loader_data,size,(void**)&info);
	if(efi_error(st)||!info)return NULL;
	st=f->get_info(f,guid,&size,info);
	if(efi_error(st)){
		g_bs->free_pool(info);
		return NULL;
	}
	return info;
}

efi_file_system_info*efi_get_fs_info(efi_simple_file_system_protocol*fs){
	efi_status st;
	efi_file_protocol*root=NULL;
	efi_file_system_info*info=NULL;
	if(!fs)return NULL;
	st=fs->open_volume(fs,&root);
	if(efi_error(st)||!root)return NULL;
	info=efi_file_get_info_by(root,&gEfiFileSystemInfoGuid);
	if(root)root->close(root);
	return info;
}

efi_simple_file_system_protocol*efi_get_current_fs(void){
	efi_status st;
	efi_simple_file_system_protocol*fs=NULL;
	efi_handle dev=efi_get_current_device();
	if(!dev)return NULL;
	st=g_bs->handle_proto(dev,&gEfiSimpleFileSystemProtocolGuid,(void**)&fs);
	if(efi_error(st)||!fs)return NULL;
	return fs;
}
