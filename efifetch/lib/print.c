#define STB_SPRINTF_NOFLOAT
#include"efi.h"
#include"str.h"
#include"init.h"
#include"print.h"
#include"stb_sprintf.h"

efi_status text_printn(
	efi_simple_text_output_protocol*con,
	const char*str,size_t len
){
	if(!con||!str)return efi_invalid_parameter;
	efi_status st=efi_success;
	char16 buffer[128]={};
	while(len>0){
		encode_convert_ctx ctx={};
		ctx.in.src=ENC_UTF8;
		ctx.in.dst=ENC_UTF16;
		ctx.in.src_ptr=(void*)str;
		ctx.in.src_size=len;
		ctx.in.dst_ptr=buffer;
		ctx.in.dst_size=sizeof(buffer)-2;
		ctx.in.allow_invalid=true;
		ctx.in.transfers=NULL;
		st=encode_convert(&ctx);
		if(efi_error(st))break;
		if(ctx.out.dst_wrote==0)break;
		buffer[sizeof(buffer)/sizeof(char16)-1]=0;
		st=con->output_string(con,buffer);
		if(efi_error(st))break;
		str=(const char*)ctx.out.src_end;
		len-=ctx.out.src_used;
	}
	return st;
}

efi_status text_print(
	efi_simple_text_output_protocol*con,
	const char*str
){
	if(!con||!str)return efi_invalid_parameter;
	return text_printn(con,str,strlen(str)+1);
}

efi_status text_print_repeat(
	efi_simple_text_output_protocol*con,
	char ch,uintn_t cnt
){
	uintn_t i;
	efi_status status=efi_success;
	char16 buffer[128];
	if(!con)return efi_invalid_parameter;
	if(cnt>0)do{
		for(i=0;cnt>0&&i<sizeof(buffer)-1;)
			buffer[i++]=ch,cnt--;
		buffer[i]=0;
		status=con->output_string(con,buffer);
	}while(cnt>0&&!efi_error(status));
	return status;
}

struct printf_context{
	char buff[STB_SPRINTF_MIN*3/2];
	efi_simple_text_output_protocol*con;
	efi_status status;
};

static char*printf_callback(const char*buf,void*user,int len){
	struct printf_context*ctx=user;
	ctx->status=text_print(ctx->con,buf);
	return efi_error(ctx->status)?NULL:ctx->buff;
}

efi_status text_vprintf(
	efi_simple_text_output_protocol*con,
	const char*str,va_list va
){
	struct printf_context ctx={
		.con=con,
		.status=efi_success,
	};
	if(!con||!str)return efi_invalid_parameter;
	stbsp_vsprintfcb(printf_callback,&ctx,ctx.buff,str,va);
	return ctx.status;
}

efi_status text_printf(
	efi_simple_text_output_protocol*con,
	const char*str,
	...
){
	va_list va;
	va_start(va,str);
	efi_status st=text_vprintf(con,str,va);
	va_end(va);
	return st;
}

void print_init(){
	if(!g_st)return;
	extern uintn_t con_stdout_def_attr;
	extern uintn_t con_stderr_def_attr;
	if(stdout)
		con_stdout_def_attr=stdout->mode->attribute.num;
	if(stderr)
		con_stderr_def_attr=stderr->mode->attribute.num;	
}
