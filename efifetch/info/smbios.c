#include"info.h"
#include"str.h"
#include"print.h"
#include"readable.h"

static void efifetch_load_info_smbios_firmware(efifetch*ctx){
	if(!IS_EMPTY(FIRMWARE))return;
	smbios_structure_pointer ptr;
	char str_vendor[64]={};
	char str_version[64]={};
	char str_date[64]={};
	ptr=efifetch_get_smbios_by_type(ctx,0,0xFFFF);
	if(!ptr.value){
		dbg_print("smbios type0 not found\n");
		return;
	}
	SMBIOS_VAR(ptr,0,vendor,0);
	SMBIOS_VAR(ptr,0,bios_release_date,0);
	SMBIOS_VAR(ptr,0,bios_version,0);
	efifetch_load_smbios_string(
		ctx,ptr,vendor,
		str_vendor,sizeof(str_vendor)
	);
	efifetch_load_smbios_string(
		ctx,ptr,bios_version,
		str_version,sizeof(str_version)
	);
	efifetch_load_smbios_string(
		ctx,ptr,bios_release_date,
		str_date,sizeof(str_date)
	);
	if(!str_vendor[0]&&!str_date[0]&&!str_version[0]){
		dbg_print("smbios type0 no vendor,version,date\n");
		return;
	}
	if(str_vendor[0]){
		if(!IS_EMPTY(FIRMWARE))APPEND(FIRMWARE," ");
		APPEND(FIRMWARE,str_vendor);
	}
	if(str_version[0]){
		if(!IS_EMPTY(FIRMWARE))APPEND(FIRMWARE," ");
		APPEND(FIRMWARE,str_version);
	}
	if(str_date[0]){
		if(!IS_EMPTY(FIRMWARE))APPEND(FIRMWARE," ");
		APPEND(FIRMWARE,str_date);
	}
}

static void efifetch_load_info_smbios_cpu(efifetch*ctx){
	if(!IS_EMPTY(CPU))return;
	smbios_handle handle;
	smbios_structure_pointer ptr;
	char version[64]={};
	uint64_t cpus=0,cores=0,threads=0,max_freq=0;
	handle=0xFFFF;
	while((ptr=efifetch_get_smbios_by_type(ctx,4,handle)).value){
		SMBIOS_VAR(ptr,4,core_count,0);
		SMBIOS_VAR(ptr,4,core_count2,0);
		SMBIOS_VAR(ptr,4,enabled_core_count,0);
		SMBIOS_VAR(ptr,4,enabled_core_count2,0);
		SMBIOS_VAR(ptr,4,thread_count,0);
		SMBIOS_VAR(ptr,4,thread_count2,0);
		SMBIOS_VAR(ptr,4,thread_enabled,0);
		SMBIOS_VAR(ptr,4,max_speed,0);
		SMBIOS_VAR(ptr,4,current_speed,0);
		SMBIOS_VAR(ptr,4,processor_version,0);
		uint32_t real_cores=0,real_threads=0;
		if(core_count!=0xFF)
			real_cores=MAX(real_cores,core_count);
		else if(core_count2!=0xFFFF)
			real_cores=MAX(real_cores,core_count2);
		if(enabled_core_count!=0xFF)
			real_cores=MAX(real_cores,enabled_core_count);
		else if(enabled_core_count2!=0xFFFF)
			real_cores=MAX(real_cores,enabled_core_count2);
		if(thread_count!=0xFF)
			real_threads=MAX(real_threads,thread_count);
		else if(thread_count2!=0xFFFF)
			real_threads=MAX(real_threads,thread_count2);
		if(thread_enabled!=0xFFFF)
			real_threads=MAX(real_threads,thread_enabled);
		cores+=real_cores,threads+=real_threads;
		max_freq=MAX(max_freq,MAX(current_speed,max_speed));
		if(processor_version!=0)efifetch_load_smbios_string(
			ctx,ptr,processor_version,version,sizeof(version)
		);
		cpus++;
		handle=ptr.header->handle;
	}
	if(cpus==0||!version[0]){
		dbg_print("smbios type4 no cpus\n");
		return;
	}
	RESET(CPU);
	if(cpus>1)APPENDF(CPU,"%llu x ",cpus);
	APPEND(CPU,version);
	if(cores>0&&cores!=0xFFFF){
		if(cores==threads||threads==0)APPENDF(CPU," (%llu)",cores);
		else APPENDF(CPU," (%lluC%lluT)",cores,threads);
	}
	if(max_freq>0&&max_freq!=0xFFFF){
		char buf_freq[32];
		format_size_float_hz(buf_freq,max_freq*1000000);
		APPENDF(CPU," @ %s",buf_freq);
	}
}

static void efifetch_load_info_smbios_sys(efifetch*ctx){
	if(!IS_EMPTY(HOST))return;
	smbios_structure_pointer ptr;
	char str_manufacturer[64]={};
	char str_product[64]={};
	char str_version[64]={};
	ptr=efifetch_get_smbios_by_type(ctx,1,0xFFFF);
	if(!ptr.value){
		dbg_print("smbios type1 not found\n");
		return;
	}
	SMBIOS_VAR(ptr,1,manufacturer,0);
	SMBIOS_VAR(ptr,1,product,0);
	SMBIOS_VAR(ptr,1,version,0);
	efifetch_load_smbios_string(
		ctx,ptr,manufacturer,
		str_manufacturer,sizeof(str_manufacturer)
	);
	efifetch_load_smbios_string(
		ctx,ptr,product,
		str_product,sizeof(str_product)
	);
	efifetch_load_smbios_string(
		ctx,ptr,version,
		str_version,sizeof(str_version)
	);
	if(!str_manufacturer[0]&&!str_product[0]&&!str_version[0]){
		dbg_print("smbios type1 no manufacturer,product,version\n");
		return;
	}
	if(str_manufacturer[0]){
		if(!IS_EMPTY(HOST))APPEND(HOST," ");
		APPEND(HOST,str_manufacturer);
	}
	if(str_product[0]){
		if(!IS_EMPTY(HOST))APPEND(HOST," ");
		APPEND(HOST,str_product);
	}
	if(str_version[0]){
		if(!IS_EMPTY(HOST))APPEND(HOST," ");
		APPEND(HOST,str_version);
	}
}

void efifetch_load_info_smbios(efifetch*ctx){
	efifetch_load_info_smbios_firmware(ctx);
	efifetch_load_info_smbios_cpu(ctx);
	efifetch_load_info_smbios_sys(ctx);
}
