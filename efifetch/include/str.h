#ifndef STR_H
#define STR_H
#include"efi.h"
extern void*memset(void*dest,int c,size_t n);
extern void*memchr(const void*src,int c,size_t n);
extern void*memrchr(const void*m,int c,size_t n);
extern void*memmem(const void*h,size_t hl,const void*n,size_t nl);
extern void*memcpy(void*dest,const void*src,size_t n);
extern void*memmove(void*dest,const void*src,size_t n);
extern int memcmp(const void*vl,const void*vr,size_t n);
extern int strcmp(const char*l,const char*r);
extern int strncmp(const char*_l,const char*_r,size_t n);
extern char*stpcpy(char*d,const char*s);
extern char*stpncpy(char*d,const char*s,size_t n);
extern char*strcpy(char*d,const char*s);
extern char*strncpy(char*d,const char*s,size_t n);
extern size_t strlen(const char*s);
extern size_t strnlen(const char*s,size_t n);
extern char*strchrnul(const char*s,int c);
extern char*strchr(const char*s,int c);
extern char*strrchr(const char*s,int c);
extern size_t strlcat(char*d,const char*s,size_t n);
extern size_t strlcpy(char*d,const char*s,size_t n);
extern size_t strlncat(char*d,const char*s,size_t n,size_t c);
extern int strcasecmp(const char*_l,const char*_r);
extern char*strcasestr(const char*h,const char*n);
extern char*strcat(char*dest,const char*src);
extern int strcoll(const char*l,const char*r);
extern size_t strcspn(const char*s,const char*c);
extern int strncasecmp(const char*_l,const char*_r,size_t n);
extern char*strpbrk(const char*s,const char*b);
extern char*strsep(char**str,const char*sep);
extern size_t strspn(const char*s,const char*c);
extern char*strstr(const char*h,const char*n);
extern char*strtok(char*s,const char*sep);
extern bool startwith(const char*str,char c);
extern bool startwiths(const char*str,const char*s);
extern bool startnwith(const char*str,size_t len,char c);
extern bool startnwiths(const char*str,size_t len,const char*s);
extern bool endwith(const char*str,char c);
extern bool endwiths(const char*str,const char*s);
extern bool endnwith(const char*str,size_t len,char c);
extern bool endnwiths(const char*str,size_t len,const char*s);
extern bool removeend(char*str,char c);
extern bool removeends(char*str,const char*s);
extern void trimleft(char*str);
extern void trimright(char*str);
extern void trim(char*str);
extern void*realloc(void*old,size_t size);
extern void*malloc(size_t size);
extern void free(void*buffer);
extern char*strdup(const char*str);
extern char*strndup(const char*str,size_t max);
extern void*memdup(const void*mem,size_t len);
extern void*zalloc(size_t size);
extern void*calloc(size_t nmemb,size_t size);
extern int isspace(int c);
extern int isalpha(int c);
extern int islower(int c);
extern int isupper(int c);
extern int tolower(int c);
extern int toupper(int c);
extern int isdigit(int c);
extern int isprint(int c);
extern unsigned long long strtoull(const char*str,char**end,int base);
extern long long strtoll(const char*str,char**end,int base);
extern unsigned long strtoul(const char*str,char**end,int base);
extern long strtol(const char*str,char**end,int base);
extern int puts(const char*str);
extern int putchar(int ch);
extern int printf(const char*fmt,...);
extern int asprintf(char**buf,const char*fmt,...);
extern int sprintf(char*buf,const char*fmt,...);
extern int snprintf(char*buf,size_t size,const char*fmt,...);
extern int scprintf(char*buf,size_t size,const char*fmt,...);
extern int vprintf(const char*fmt,va_list va);
extern int vasprintf(char**buf,const char*fmt,va_list va);
extern int vsprintf(char*buf,const char*fmt,va_list va);
extern int vsnprintf(char*buf,size_t size,const char*fmt,va_list va);
extern int vscprintf(char*buf,size_t size,const char*fmt,va_list va);
extern const char*efi_status_to_string(efi_status st);
extern const char*efi_status_to_short_string(efi_status st);
extern const char*efi_memory_type_to_string(efi_memory_type type);
extern const char*efi_guid_to_string(const efi_guid*guid,char*buff,size_t len);
#define efi_strerr efi_status_to_string
typedef enum encoding{
	ENC_NONE,
	ENC_UTF8,
	ENC_UTF16,
}encoding;
typedef struct convert_transfer{
	const void*match;
	size_t match_size;
	const void*replace;
	size_t replace_size;
}convert_transfer;
typedef struct encode_convert_ctx{
	struct{
		encoding src;
		encoding dst;
		const void*src_ptr;
		void*dst_ptr;
		size_t src_size;
		size_t dst_size;
		convert_transfer**transfers;
		bool allow_invalid;
	}in;
	struct{
		void*src_end;
		void*dst_end;
		size_t src_used;
		size_t dst_wrote;
		bool have_invalid;
	}out;
}encode_convert_ctx;
extern efi_status encode_convert(encode_convert_ctx*ctx);
#endif
