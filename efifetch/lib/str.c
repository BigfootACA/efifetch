#include"str.h"

__weak char*stpcpy(char*d,const char*s){
	if(!d||!s)return NULL;
	for(;(*d=*s);s++,d++);
	*d=0;
	return d;
}

__weak char*stpncpy(char*d,const char*s,size_t n){
	if(!d||!s)return NULL;
	for(;n&&(*d=*s);n--,s++,d++);
	memset(d,0,n);
	return d;
}

__weak char*strcpy(char*d,const char*s){
	stpcpy(d,s);
	return d;
}

__weak char*strncpy(char*d,const char*s,size_t n){
	stpncpy(d,s,n);
	return d;
}

__weak size_t strlen(const char*s){
	const char*a=s;
	if(!s)return 0;
	for(;*s;s++);
	return s-a;
}

__weak size_t strnlen(const char*s,size_t n){
	if(!s)return 0;
	const char*p=memchr(s,0,n);
	return p?(size_t)(p-s):n;
}

__weak char*strchrnul(const char*s,int c){
	if(!s)return NULL;
	c=(unsigned char)c;
	if(!c)return (char*)s+strlen(s);
	for(;*s&&*(unsigned char*)s!=c;s++);
	return (char*)s;
}

__weak char*strchr(const char*s,int c){
	if(!s)return NULL;
	char*r=strchrnul(s,c);
	return*(unsigned char*)r==(unsigned char)c?r:0;
}

__weak char*strrchr(const char*s,int c){
	if(!s)return NULL;
	return memrchr(s,c,strlen(s)+1);
}

__weak size_t strlcat(char*d,const char*s,size_t n){
	if(!d||!s)return 0;
	size_t l=strnlen(d,n);
	if(l==n)return l+strlen(s);
	return l+strlcpy(d+l,s,n-l);
}

__weak size_t strlcpy(char*d,const char*s,size_t n){
	if(!d||!s)return 0;
	char*d0=d;
	if(n--)strncpy(d,s,n);
	return d-d0+strlen(s);
}

__weak size_t strlncat(char*d,const char*s,size_t n,size_t c){
	if(!d||!s)return 0;
	size_t l=strnlen(d,n);
	size_t x=strnlen(s,c);
	if(l==n)return l+x;
	return l+strlcpy(d+l,s,MIN(n-l,x+1));
}

__weak int strcasecmp(const char*_l,const char*_r){
	const unsigned char*l=(void*)_l,*r=(void*)_r;
	if(l==r)return 0;
	if(!l||!r)return 1;
	for(;*l&&*r&&(*l==*r||tolower(*l)==tolower(*r));l++,r++);
	return tolower(*l)-tolower(*r);
}

__weak char*strcasestr(const char*h,const char*n){
	if(!h||!n)return NULL;
	size_t l=strlen(n);
	for(;*h;h++)if(!strncasecmp(h,n,l))return (char*)h;
	return 0;
}

__weak char*strcat(char*dest,const char*src){
	if(!dest||!src)return NULL;
	strcpy(dest+strlen(dest),src);
	return dest;
}

__weak int strcoll(const char*l,const char*r){
	return strcmp(l,r);
}

__weak size_t strcspn(const char*s,const char*c){
	if(!s||!c)return 0;
	const char*a=s;
	size_t byteset[32/sizeof(size_t)];
	if(!c[0]||!c[1])return strchrnul(s,*c)-a;
	memset(byteset,0,sizeof(byteset));
	#define BITOP(a,b,op)((a)[(size_t)(b)/(8*sizeof*(a))] op(size_t)1<<((size_t)(b)%(8*sizeof*(a))))
	for(;*c&&BITOP(byteset,*(unsigned char*)c,|=);c++);
	for(;*s&&!BITOP(byteset,*(unsigned char*)s,&);s++);
	#undef BITOP
	return s-a;
}

__weak int strncasecmp(const char*_l,const char*_r,size_t n){
	const unsigned char*l=(void*)_l,*r=(void*)_r;
	if(l==r)return 0;
	if(!l||!r)return 1;
	if(!n--)return 0;
	for(;*l&&*r&&n&&(*l==*r||tolower(*l)==tolower(*r));l++,r++,n--);
	return tolower(*l)-tolower(*r);
}

__weak char*strpbrk(const char*s,const char*b){
	if(!s)return NULL;
	s+=strcspn(s,b);
	return *s?(char*)s:0;
}

__weak char*strsep(char**str,const char*sep){
	char *s=*str,*end;
	if(!s)return NULL;
	end=s+strcspn(s,sep);
	if(*end)*end++=0;
	else end=0;
	*str=end;
	return s;
}

__weak size_t strspn(const char*s,const char*c){
	const char *a=s;
	size_t byteset[32/sizeof(size_t)]={0};
	if(!s||!c)return 0;
	if(!c[0])return 0;
	if(!c[1]){
		for(;*s==*c;s++);
		return s-a;
	}
	#define BITOP(a,b,op) ((a)[(size_t)(b)/(8*sizeof*(a))]op(size_t)1<<((size_t)(b)%(8*sizeof*(a))))
	for(;*c&&BITOP(byteset,*(unsigned char*)c,|=);c++);
	for(;*s&&BITOP(byteset,*(unsigned char*)s,&);s++);
	#undef BITOP
	return s-a;
}

__weak char*strstr(const char*h,const char*n){
	if(!h||!n||!*n)return (char*)h;
	size_t hl=strlen(h),nl=strlen(n);
	return memmem(h,hl,n,nl);
}

__weak char*strtok(char*s,const char*sep){
	static char *p;
	if(!s&&!(s=p))return NULL;
	s+=strspn(s,sep);
	if(!*s)return p=0;
	p=s+strcspn(s,sep);
	if(*p)*p++=0;
	else p=0;
	return s;
}

__weak bool startwith(const char*str,char c){
	if(!str)return false;
	return str[0]==c;
}

__weak bool startwiths(const char*str,const char*s){
	if(!str||!s)return false;
	return strncmp(str,s,strlen(s))==0;
}

__weak bool startnwith(const char*str,size_t len,char c){
	if(!str||len<=0)return false;
	return str[0]==c;
}

__weak bool startnwiths(const char*str,size_t len,const char*s){
	if(!str||len<=0)return false;
	return strncmp(str,s,strnlen(s,len))==0;
}

__weak bool endwith(const char*str,char c){
	if(!str)return false;
	size_t l=strlen(str);
	return l>0&&str[l-1]==c;
}

__weak bool endwiths(const char*str,const char*s){
	if(!str||!s)return false;
	size_t ll=strlen(str),rl=strlen(s);
	if(rl==0)return true;
	if(rl>ll)return false;
	return strncmp(str+ll-rl,s,rl)==0;
}

__weak bool endnwith(const char*str,size_t len,char c){
	if(!str||len<=0)return false;
	size_t l=strnlen(str,len);
	return l>0&&str[l-1]==c;
}

__weak bool endnwiths(const char*str,size_t len,const char*s){
	if(!str||len<=0)return false;
	size_t ll=strnlen(str,len),rl=strlen(s);
	if(rl==0)return true;
	if(rl>ll)return false;
	return strncmp(str+ll-rl,s,rl)==0;
}

__weak bool removeend(char*str,char c){
	if(!str)return false;
	size_t l=strlen(str);
	bool r=(l>0&&str[l-1]==c);
	if(r)str[l-1]=0;
	return r;
}

__weak bool removeends(char*str,const char*s){
	if(!str||!s)return false;
	size_t ll=strlen(str),rl=strlen(s);
	if(rl==0)return true;
	if(rl>ll)return false;
	bool r=strncmp(str+ll-rl,s,rl)==0;
	if(r)memset(str+ll-rl,0,rl);
	return r;
}

__weak void trimleft(char*str){
	if(!str||!str[0])return;
	char*start=str;
	while(*start&&isspace(*start))start++;
	if(start!=str){
		if(!*start)str[0]=0;
		memmove(str,start,strlen(start)+1);
	}
}

__weak void trimright(char*str){
	if(!str||!str[0])return;
	char*end=str+strlen(str);
	while(end>str&&isspace(end[-1]))end--;
	*end=0;
}

__weak void trim(char*str){
	if(!str||!str[0])return;
	trimright(str);
	trimleft(str);
}
