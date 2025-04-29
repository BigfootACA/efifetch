#include"info.h"
#include"efifetch.h"
#include"print.h"
#include"str.h"

void efifetch_load_info(efifetch*ctx){
	efifetch_init_info_fdt(ctx);
	efifetch_init_info_smbios(ctx);
	efifetch_load_info_gpu(ctx);
	efifetch_load_info_mem(ctx);
	efifetch_load_info_net(ctx);
	efifetch_load_info_fs(ctx);
	efifetch_load_info_disk(ctx);
	efifetch_load_info_fdt(ctx);
	efifetch_load_info_smbios(ctx);
	efifetch_load_info_sys(ctx);
	efifetch_load_info_cpuid(ctx);
	efifetch_load_info_time(ctx);
}

static const char*fields_key[]={
	[EFIFETCH_FIELD_NAME]        = NULL,
	[EFIFETCH_FIELD_FIRMWARE]    = "Firmware",
	[EFIFETCH_FIELD_HOST]        = "Host",
	[EFIFETCH_FIELD_SPEC]        = "Specification",
	[EFIFETCH_FIELD_UPTIME]      = "Uptime",
	[EFIFETCH_FIELD_DISPLAY]     = "Display",
	[EFIFETCH_FIELD_ARCH]        = "Architecture",
	[EFIFETCH_FIELD_CPUID]       = "CPUID",
	[EFIFETCH_FIELD_CPU]         = "CPU",
	[EFIFETCH_FIELD_GPU]         = "GPU",
	[EFIFETCH_FIELD_MEMORY]      = "Memory",
	[EFIFETCH_FIELD_FILESYSTEM]  = "Filesystem",
	[EFIFETCH_FIELD_DISK]        = "Disk",
	[EFIFETCH_FIELD_IP4]         = "IPv4",
	[EFIFETCH_FIELD_IP6]         = "IPv6",
	[EFIFETCH_FIELD_SECURE_BOOT] = "Secure Boot",
};

void efifetch_print_all(efifetch*ctx){
	if(IS_EMPTY(NAME))SET(NAME,"efifetch");
	logo_ctx_print_line(&ctx->logo);
	const char*name=ctx->fields[EFIFETCH_FIELD_NAME].value;
	text_printf(ctx->logo.con,"%s\r\n",name);
	logo_ctx_print_line(&ctx->logo);
	text_print_repeat(ctx->logo.con,'-',strlen(name));
	out_print("\r\n");
	for(int i=EFIFETCH_FIELD_MIN;i<EFIFETCH_FIELD_MAX;i++){
		efifetch_print_field(ctx,i);
	}
	logo_ctx_print_remain(&ctx->logo);
}

void efifetch_print_field(efifetch*ctx,enum efifetch_field field){
	if(!fields_key[field]||efifetch_field_is_empty(ctx,field))return;
	efi_simple_text_output_protocol*con=ctx->logo.con;
	logo_ctx_print_line(&ctx->logo);
	uintn_t orig_attr=ctx->logo.con->mode->attribute.num;
	con->set_attribute(con,ctx->logo.target_logo->main_color);
	text_print(con,fields_key[field]);
	con->set_attribute(con,orig_attr);
	text_printf(con,": %s\r\n",ctx->fields[field].value);
}

bool efifetch_field_is_empty(efifetch*ctx,enum efifetch_field field){
	if(field<EFIFETCH_FIELD_MIN||field>=EFIFETCH_FIELD_MAX)return true;
	return !ctx->fields[field].value[0];
}

void efifetch_field_reset(efifetch*ctx,enum efifetch_field field){
	if(field<EFIFETCH_FIELD_MIN||field>=EFIFETCH_FIELD_MAX)return;
	memset(ctx->fields[field].value,0,sizeof(ctx->fields[field].value));
}

void efifetch_field_set(efifetch*ctx,enum efifetch_field field,const char*value){
	efifetch_field_setn(ctx,field,value,UINT32_MAX);
}

void efifetch_field_setn(efifetch*ctx,enum efifetch_field field,const char*value,size_t len){
	if(field<EFIFETCH_FIELD_MIN||field>=EFIFETCH_FIELD_MAX)return;
	efifetch_field_reset(ctx,field);
	size_t l=strnlen(value,MIN(sizeof(ctx->fields[field].value),len));
	strncpy(ctx->fields[field].value,value,l);
}

void efifetch_field_setf(efifetch*ctx,enum efifetch_field field,const char*fmt,...){
	va_list va;
	if(field<EFIFETCH_FIELD_MIN||field>=EFIFETCH_FIELD_MAX)return;
	efifetch_field_reset(ctx,field);
	va_start(va,fmt);
	vsnprintf(ctx->fields[field].value,sizeof(ctx->fields[field].value),fmt,va);
	va_end(va);
}

void efifetch_field_appendn(efifetch*ctx,enum efifetch_field field,const char*value,size_t len){
	if(field<EFIFETCH_FIELD_MIN||field>=EFIFETCH_FIELD_MAX)return;
	size_t origlen=strlen(ctx->fields[field].value);
	size_t remain=sizeof(ctx->fields[field].value)-origlen;
	size_t l=strnlen(value,MIN(remain,len));
	strncpy(ctx->fields[field].value+origlen,value,l);
}

void efifetch_field_append(efifetch*ctx,enum efifetch_field field,const char*value){
	efifetch_field_appendn(ctx,field,value,UINT32_MAX);
}

void efifetch_field_appendf(efifetch*ctx,enum efifetch_field field,const char*fmt,...){
	va_list va;
	if(field<EFIFETCH_FIELD_MIN||field>=EFIFETCH_FIELD_MAX)return;
	va_start(va,fmt);
	vscprintf(ctx->fields[field].value,sizeof(ctx->fields[field].value),fmt,va);
	va_end(va);
}
