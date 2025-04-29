#include"str.h"

__weak void*memset(void*dest,int c,size_t n){
	uint8_t*d=dest;
	if(!dest)return NULL;
	for(;n;n--)*d++=c;
	return dest;
}

__weak void*memchr(const void*src,int c,size_t n){
	const unsigned char*s=src;
	if(!src)return NULL;
	c=(unsigned char)c;
	for(;n&&*s!=c;s++,n--);
	return n?(void*)s:NULL;
}

__weak void*memrchr(const void*m,int c,size_t n){
	const unsigned char*s=m;
	if(!m)return NULL;
	c=(unsigned char)c;
	while(n--)if(s[n]==c)return(void*)(s+n);
	return 0;
}

__weak void*memmem(const void*h,size_t hl,const void*n,size_t nl){
        char*s=(void*)h,*p=(void*)n;
        if(!h||!n)return NULL;
        if(nl==0)return s;
        if(hl<nl)return NULL;
        for(;s<=(char*)h+hl-nl;s++)
                if(*s==*p&&memcmp(s+1,p+1,nl-1)==0)
                        return s;
        return NULL;
}

__weak void*memcpy(void*dest,const void*src,size_t n){
	uint8_t*d=dest;
	const uint8_t*s=src;
	if(!dest||!src)return NULL;
	for(;n;n--)*d++=*s++;
	return dest;
}

__weak void*memmove(void*dest,const void*src,size_t n){
	char*d=dest;
	const char*s=src;
	if(!dest||!src)return NULL;
	if(d==s)return d;
	if((uintptr_t)s-(uintptr_t)d-n<=-2*n)
		return memcpy(d,s,n);
	if(d<s){
		for(;n;n--)*d++=*s++;
	}else{
		while(n)n--,d[n]=s[n];
	}
	return dest;
}

__weak int memcmp(const void*vl,const void*vr,size_t n){
	const unsigned char*l=vl,*r=vr;
	if(vl==vr)return 0;
	if(!vl||!vr)return 1;
	for(;n&&*l==*r;n--,l++,r++);
	return n?*l-*r:0;
}

__weak int strcmp(const char*l,const char*r){
	if(l==r)return 0;
	if(!l||!r)return 1;
	for(;*l==*r&&*l;l++,r++);
	return *(unsigned char*)l-*(unsigned char*)r;
}

__weak int strncmp(const char*_l,const char*_r,size_t n){
	const unsigned char*l=(void*)_l,*r=(void*)_r;
	if(l==r)return 0;
	if(!l||!r)return 1;
	if(!n--)return 0;
	for(;*l&&*r&&n&&*l==*r;l++,r++,n--);
	return*l -*r;
}
