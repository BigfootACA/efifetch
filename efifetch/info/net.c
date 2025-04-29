#include"info.h"
#include"network.h"
#include"print.h"
#include"net.h"
#include"init.h"
#include"str.h"

void efifetch_load_info_net_ipv4(efifetch*ctx){
	efi_status st;
	efi_handle*hands=NULL;
	uintn_t data_size=0,hand_cnt=0;
	efi_ip4_config2_protocol*cfg=NULL;
	efi_ip4_config2_interface_info*info=NULL;
	if(!IS_EMPTY(IP4))return;
	st=g_bs->locate_handle_buffer(
		search_by_protocol,
		&gEfiIp4ServiceBindingProtocolGuid,
		NULL,&hand_cnt,&hands
	);
	if(efi_error(st)||!hands){
		dbg_printf("locate ip4 handles failed: %m\n",st);
		return;
	}
	dbg_printf("found %zu ip4 handles\n",hand_cnt);
	for(uintn_t i=0;i<hand_cnt&&IS_EMPTY(IP4);i++){
		st=g_bs->handle_proto(hands[i],&gEfiIp4Config2ProtocolGuid,(void**)&cfg);
		if(efi_error(st)||!cfg){
			dbg_printf("handle %p ip4 cfg failed: %m\n",hands[i],st);
			continue;
		}
		st=cfg->get_data(cfg,ip4cfg2_type_int_info,&data_size,NULL);
		if(st!=efi_buffer_too_small){
			dbg_printf("handle %p ip4 cfg get size failed: %m\n",hands[i],st);
			continue;
		}
		if(data_size<sizeof(efi_ip4_config2_interface_info)){
			dbg_printf("handle %p ip4 cfg data size %zu invalid: %m\n",hands[i],data_size);
			continue;
		}
		st=g_bs->alloc_pool(efi_loader_data,data_size,(void**)&info);
		if(efi_error(st)||!info){
			dbg_printf("handle %p ip4 cfg alloc data %zu failed: %m\n",hands[i],data_size,st);
			continue;
		}
		memset(info,0,data_size);
		st=cfg->get_data(cfg,ip4cfg2_type_int_info,&data_size,info);
		if(!efi_error(st)&&info->station_addr.raw!=0){
			char buff[64]={};
			int prefix=ipv4_to_prefix(&info->subnet_mask);
			int ret=ipv4_to_string(&info->station_addr,buff,sizeof(buff));
			if(prefix>=0&&ret>=0){
				SETF(IP4,"%s/%u",buff,prefix);
				uintn_t l=utf16_to_utf8(info->name,sizeof(info->name),buff,sizeof(buff));
				if(l>0)APPENDF(IP4," (%s)",buff);
			}
		}else dbg_printf(
			"handle %p ip4 cfg get interface failed or no address: %m\n",
			hands[i],st
		);
		g_bs->free_pool(info);
	}
	g_bs->free_pool(hands);
}

void efifetch_load_info_net_ipv6(efifetch*ctx){
	efi_status st;
	efi_handle*hands=NULL;
	uintn_t data_size=0,hand_cnt=0;
	efi_ip6_config_protocol*cfg=NULL;
	efi_ip6_config_interface_info*info=NULL;
	if(!IS_EMPTY(IP6))return;
	st=g_bs->locate_handle_buffer(
		search_by_protocol,
		&gEfiIp4ServiceBindingProtocolGuid,
		NULL,&hand_cnt,&hands
	);
	if(efi_error(st)||!hands){
		dbg_printf("locate ip6 handles failed: %m\n",st);
		return;
	}
	for(uintn_t i=0;i<hand_cnt&&IS_EMPTY(IP6);i++){
		st=g_bs->handle_proto(hands[i],&gEfiIp6ConfigProtocolGuid,(void**)&cfg);
		if(efi_error(st)||!cfg){
			dbg_printf("handle %p ip6 cfg failed: %m\n",hands[i],st);
			continue;
		}
		st=cfg->get_data(cfg,ip6cfg_type_int_info,&data_size,NULL);
		if(st!=efi_buffer_too_small){
			dbg_printf("handle %p ip6 cfg get size failed: %m\n",hands[i],st);
			continue;
		}
		if(data_size<sizeof(efi_ip6_config_interface_info)){
			dbg_printf("handle %p ip6 cfg data size %llu invalid: %m\n",hands[i],data_size);
			continue;
		}
		st=g_bs->alloc_pool(efi_loader_data,data_size,(void**)&info);
		if(efi_error(st)||!info){
			dbg_printf("handle %p ip6 cfg alloc data %llu failed: %m\n",hands[i],data_size,st);
			continue;
		}
		memset(info,0,data_size);
		st=cfg->get_data(cfg,ip6cfg_type_int_info,&data_size,info);
		if(!efi_error(st)&&info->addr_info_count>0){
			char buff[64]={};
			if(ipv6_to_string(&info->addr_info[0].addr,buff,sizeof(buff))>0)
				SET(IP6,buff);
			uintn_t l=utf16_to_utf8(info->name,sizeof(info->name),buff,sizeof(buff));
			if(l>0)APPENDF(IP6," (%s)",buff);
		}else dbg_printf(
			"handle %p ip6 cfg get interface failed or no address: %m\n",
			hands[i],st
		);
		g_bs->free_pool(info);
	}
	g_bs->free_pool(hands);
}

void efifetch_load_info_net(efifetch*ctx){
	efifetch_load_info_net_ipv4(ctx);
	efifetch_load_info_net_ipv6(ctx);
}
