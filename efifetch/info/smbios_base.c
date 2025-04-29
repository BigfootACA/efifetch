#include"info.h"
#include"init.h"
#include"print.h"
#include"str.h"

static uint8_t sum8(const void*data,uintn_t size){
	uint8_t sum=0;
	const uint8_t*buff=data;
	for(uintn_t i=0;i<size;i++)
		sum=(uint8_t)(sum+buff[i]);
	return sum;
}

static bool check_smbios2(smbios_table2_entry_point*smbios){
	if(!smbios)return false;
	if(memcmp(
		smbios->magic,SMBIOS_MAGIC,
		sizeof(smbios->magic))!=0
	){
		dbg_print("smbios2 magic mismatch\n");
		return false;
	}
	if(
		smbios->entry_point_length!=0x1E&&
		smbios->entry_point_length!=sizeof(smbios_table2_entry_point)
	){
		dbg_printf(
			"smbios2 entry point length mismatch %u\n",
			smbios->entry_point_length
		);
		return false;
	}
	if(smbios->major_version<2){
		dbg_printf("smbios2 major invalid %u\n",smbios->major_version);
		return false;
	}
	if(memcmp(
		smbios->intermediate_magic,"_DMI_",
		sizeof(smbios->intermediate_magic)
	)!=0){
		dbg_print("smbios2 intermediate magic mismatch\n");
		return false;
	}
	if(sum8(smbios,smbios->entry_point_length)!=0){
		dbg_print("smbios2 checksum mismatch\n");
		return false;
	}
	uintn_t xs=offsetof(smbios_table2_entry_point,intermediate_magic);
	if(sum8((void*)smbios+xs,smbios->entry_point_length-xs)!=0){
		dbg_print("smbios2 intermediate checksum mismatch\n");
		return false;
	}
	return true;
}

static bool check_smbios3(smbios_table3_entry_point*smbios){
	if(!smbios)return false;
	if(memcmp(smbios->magic,SMBIOS3_MAGIC,sizeof(smbios->magic))!=0){
		dbg_print("smbios3 magic mismatch\n");
		return false;
	}
	if(smbios->entry_point_length<sizeof(smbios_table3_entry_point)){
		dbg_printf(
			"smbios3 entry point length mismatch %u\n",
			smbios->entry_point_length
		);
		return false;
	}
	if(smbios->major_version<3){
		dbg_printf("smbios3 major invalid %u\n",smbios->major_version);
		return false;
	}
	if(sum8(smbios,sizeof(smbios_table3_entry_point))!=0){
		dbg_print("smbios3 checksum mismatch\n");
		return false;
	}
	return true;
}

void efifetch_init_info_smbios(efifetch*ctx){
	smbios_table2_entry_point*smbios2=NULL;
	smbios_table3_entry_point*smbios3=NULL;
	ctx->smbios2=NULL;
	ctx->smbios3=NULL;
	for(uintn_t i=0;i<g_st->entries;i++){
		efi_guid*g=&g_st->cfg_table[i].guid;
		void*t=g_st->cfg_table[i].table;
		if(memcmp(g,&gEfiSmbiosTableGuid,sizeof(efi_guid))==0)smbios2=t;
		if(memcmp(g,&gEfiSmbios3TableGuid,sizeof(efi_guid))==0)smbios3=t;
	}
	if(smbios2&&check_smbios2(smbios2))ctx->smbios2=smbios2;
	if(smbios3&&check_smbios3(smbios3))ctx->smbios3=smbios3;
}

static bool smbios_get_range(efifetch*ctx,uintn_t*start,uintn_t*end){
	if(!ctx||!start||!end)return false;
	if(ctx->smbios2)*start=ctx->smbios2->table_address,*end=*start+ctx->smbios2->table_length;
	if(ctx->smbios3)*start=ctx->smbios3->table_address,*end=*start+ctx->smbios3->table_max_size;
	if(!*start||!*end||*start>=*end)return false;
	return true;
}

static bool smbios_walk(efifetch*ctx,smbios_structure_pointer*p){
	uintn_t start=0,end=0;
	if(!p||!smbios_get_range(ctx,&start,&end))return false;
	if(!p->value){
		p->value=start;
		if(p->header->length<sizeof(smbios_structure))return false;
		return true;
	}
	if(p->header->type==127)return false;
	if(p->value+p->header->length>end)return false;
	if(p->header->length<sizeof(smbios_structure))return false;
	smbios_structure_pointer next=*p;
	next.value+=p->header->length;
	do{
		for(;*next.raw;next.raw++);
		next.raw++;
	}while(*next.raw);
	next.raw++;
	if(next.value+p->header->length>end)return false;
	if(next.header->length<sizeof(smbios_structure))return false;
	*p=next;
	return true;
}

smbios_structure_pointer efifetch_get_smbios_by_type(efifetch*ctx,uint8_t type,smbios_handle handle){
	smbios_structure_pointer smbios={},nil={};
	while(smbios_walk(ctx,&smbios)){
		if(smbios.header->type!=type)continue;
		if(handle==0xFFFF)return smbios;
		if(smbios.header->handle>handle)return smbios;
	}
	return nil;
}

smbios_structure_pointer efifetch_get_smbios_by_handle(efifetch*ctx,smbios_handle handle){
	smbios_structure_pointer smbios={},nil={};
	while(smbios_walk(ctx,&smbios))
		if(smbios.header->handle==handle)return smbios;
	return nil;
}

const char*efifetch_get_smbios_string(
	efifetch*ctx,
	smbios_structure_pointer p,
	smbios_table_string id
){
	uintn_t start=0,end=0;
	if(id==0||!p.value||!smbios_get_range(ctx,&start,&end))return NULL;
	if(p.header->type==127)return NULL;
	if(p.value+p.header->length>end)return NULL;
	if(p.header->length<sizeof(smbios_structure))return NULL;
	const char*str=p.pointer+p.header->length;
	for(smbios_table_string cur_id=1;*str&&cur_id<=id;cur_id++){
		if(cur_id==id)return str;
		for(;*str;str++);
		str++;
	}
	return NULL;
}

bool efifetch_load_smbios_string(
	efifetch*ctx,
	smbios_structure_pointer p,
	smbios_table_string id,
	char*buff,
	size_t size
){
	memset(buff,0,size);
	if(!ctx||!buff||size==0)return false;
	const char*v=efifetch_get_smbios_string(ctx,p,id);
	if(
		!v||!v[0]||
		strcasestr(v,"unknown")||
		strcasestr(v,"to be filled by")
	)return false;
	strncpy(buff,v,size-1);
	trim(buff);
	return true;
}
