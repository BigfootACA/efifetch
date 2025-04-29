#define STB_SPRINTF_NOFLOAT
#include"efi.h"
#include"str.h"
#include"print.h"
#include"stb_sprintf.h"

__weak int vsprintf(char*buf,const char*fmt,va_list va){
	return stbsp_vsprintf(buf,fmt,va);
}

__weak int vsnprintf(char*buf,size_t size,const char*fmt,va_list va){
	return stbsp_vsnprintf(buf,size,fmt,va);
}

__weak int vprintf(const char*fmt,va_list va){
	return out_vprintf(fmt,va);
}

__weak int vscprintf(char*buf,size_t size,const char*fmt,va_list va){
	size_t len=strnlen(buf,size);
	if(len>=size)return 0;
	return stbsp_vsnprintf(buf+len,size-len,fmt,va);
}

__weak int vasprintf(char**buf,const char*fmt,va_list va){
	if(!buf)return -1;
	*buf=NULL;
	int ret=vsnprintf(NULL,0,fmt,va);
	if(ret<=0)return ret;
	size_t size=ret+4;
	if(!(*buf=zalloc(size)))return -1;
	return vsnprintf(*buf,size,fmt,va);
}

__weak int sprintf(char*buf,const char*fmt,...){
	va_list va;
	va_start(va,fmt);
	int ret=vsprintf(buf,fmt,va);
	va_end(va);
	return ret;
}

__weak int snprintf(char*buf,size_t size,const char*fmt,...){
	va_list va;
	va_start(va,fmt);
	int ret=vsnprintf(buf,size,fmt,va);
	va_end(va);
	return ret;
}

__weak int scprintf(char*buf,size_t size,const char*fmt,...){
	va_list va;
	va_start(va,fmt);
	int ret=vscprintf(buf,size,fmt,va);
	va_end(va);
	return ret;
}

__weak int asprintf(char**buf,const char*fmt,...){
	va_list va;
	va_start(va,fmt);
	int ret=vasprintf(buf,fmt,va);
	va_end(va);
	return ret;
}

__weak int printf(const char*fmt,...){
	va_list va;
	va_start(va,fmt);
	int ret=vprintf(fmt,va);
	va_end(va);
	return ret;
}

__weak int puts(const char*str){
	return out_printf("%s\n",str);
}

__weak int putchar(int ch){
	char buff[2]={ch,0};
	return out_print(buff);
}
