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
	efi_status status=efi_success;
	char16 buffer[128];
	if(!con||!str)return efi_invalid_parameter;
	do{
		uintn_t ret=utf8_to_utf16(str,len,buffer,sizeof(buffer));
		if(ret==0)break;
		buffer[ret]=0;
		str+=ret,len-=ret;
		status=con->output_string(con,buffer);
	}while(*str&&!efi_error(status));
	return status;
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
