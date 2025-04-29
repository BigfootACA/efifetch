#include"info.h"
#include"init.h"
#include"print.h"
#include"str.h"
#include"utils.h"
#include"readable.h"

static efi_file_system_info*find_cur_fs_info(void){
	return efi_get_fs_info(efi_get_current_fs());
}

static efi_file_system_info*find_largest_fs_info(void){
	efi_status st;
	uintn_t hand_cnt=0,max=0;
	efi_handle*hands=NULL;
	efi_file_system_info**infos=NULL,*ret=NULL;
	st=g_bs->locate_handle_buffer(
		search_by_protocol,
		&gEfiSimpleFileSystemProtocolGuid,
		NULL,&hand_cnt,&hands
	);
	if(efi_error(st)||!hands){
		dbg_printf("locate fs handle failed: %m\n",st);
		return NULL;
	}
	for(uintn_t i=0;i<hand_cnt;i++){
		efi_simple_file_system_protocol*fs=NULL;
		st=g_bs->handle_proto(hands[i],&gEfiSimpleFileSystemProtocolGuid,(void**)&fs);
		if(efi_error(st)||!fs){
			dbg_printf("handle fs %p failed: %m\n",hands[i],st);
			continue;
		}
		infos[i]=efi_get_fs_info(fs);
		if(!infos[i])continue;
		max=MAX(max,infos[i]->vol_size);
	}
	for(uintn_t i=0;i<hand_cnt;i++){
		if(!infos[i])continue;
		if(infos[i]->vol_size!=max)continue;
		ret=infos[i];
		infos[i]=NULL;
		break;
	}
	if(infos){
		if(hand_cnt>0)for(uintn_t i=0;i<hand_cnt;i++)
			if(infos[i]&&infos[i]!=ret)
				g_bs->free_pool(infos[i]);
		g_bs->free_pool(infos);
	}
	if(hands)g_bs->free_pool(hands);
	return ret;
}

static efi_file_system_info*find_first_fs_info(void){
	efi_status st;
	efi_simple_file_system_protocol*fs=NULL;
	st=g_bs->locate_proto(&gEfiSimpleFileSystemProtocolGuid,NULL,(void**)&fs);
	if(efi_error(st)||!fs){
		dbg_printf("locate first fs failed: %m\n",st);
		return NULL;
	}
	return efi_get_fs_info(fs);
}

void efifetch_load_info_fs(efifetch*ctx){
	efi_file_system_info*info;
	if(!IS_EMPTY(FILESYSTEM))return;
	info=find_cur_fs_info();
	if(!info)info=find_largest_fs_info();
	if(!info)info=find_first_fs_info();
	char buf_used[32],buf_total[32];
	uint64_t total=info->vol_size;
	uint64_t avail=info->free_space;
	g_bs->free_pool(info);
	uint64_t used=total-avail;
	if(!format_size_float(buf_used,used)){
		dbg_print("filesystem format size used failed\n");
		return;
	}
	if(!format_size_float(buf_total,total)){
		dbg_print("filesystem format size used failed\n");
		return;
	}
	uint64_t percent=used*100/total;
	if(percent>100)percent=100;
	SETF(
		FILESYSTEM,
		"%s / %s (%llu%c)",
		buf_used,buf_total,percent,'%'
	);
}
