#include"str.h"

__weak unsigned long long strtoull(const char*str,char**end,int base){
	const char *s=str;
	uint64_t acc,cutoff,xo;
	int neg,any,cutlim,c;
	if(!str)return 0;
	do{c=(unsigned char)*s++;}while(isspace(c));
	if(c=='-'||c=='+')c=*s++;
	neg=c=='-'?1:0;
	if((base==0||base==16)&&c=='0'&&(*s=='x'||*s=='X'))
		c=s[1],s+=2,base=16;
	if(base==0)base=c=='0'?8:10;
	xo=(uint64_t)base;
	cutoff=UINT64_MAX/xo;
	cutlim=UINT64_MAX%xo;
	for(acc=0,any=0;;c=(unsigned char)*s++){
		if(isdigit(c))c-='0';
		else if(isalpha(c))c=toupper(c)-'A'+10;
		else break;
		if(c>=base)break;
		if(any<0)continue;
		if(acc>cutoff||(acc==cutoff&&c>cutlim)){
			if(end)*end=(char*)str;
			return UINT64_MAX;
		}else any=1,acc*=(uint64_t)base,acc+=c;
	}
	if(neg&&any>0)acc=(uint64_t)(-((int64_t)acc));
	if(end)*end=(char*)(any?s-1:str);
	return acc;
}

__weak long long strtoll(const char*str,char**end,int base){
	const char *s=str;
	uint64_t acc,cutoff,xo;
	int neg,any,cutlim,c;
	if(!str)return 0;
	do{c=(unsigned char)*s++;}while(isspace(c));
	if(c=='-'||c=='+')c=*s++;
	neg=c=='-'?1:0;
	if((base==0||base==16)&&c=='0'&&(*s=='x'||*s=='X'))
		c=s[1],s+=2,base=16;
	if(base==0)base=c=='0'?8:10;
	xo=(uint64_t)base;
	cutoff=UINT64_MAX/xo;
	cutlim=UINT64_MAX%xo;
	for(acc=0,any=0;;c=(unsigned char)*s++){
		if(isdigit(c))c-='0';
		else if(isalpha(c))c=toupper(c)-'A'+10;
		else break;
		if(c>=base)break;
		if(any<0)continue;
		if(acc>cutoff||(acc==cutoff&&c>cutlim)){
			if(end)*end=(char*)str;
			return INT64_MAX;
		}else any=1,acc*=(uint64_t)base,acc+=c;
	}
	if(neg&&any>0)acc=(uint64_t)(-((int64_t)acc));
	if(end)*end=(char*)(any?s-1:str);
	return acc;
}

__weak unsigned long strtoul(const char*str,char**end,int base){
	return strtoull(str,end,base);
}

__weak long strtol(const char*str,char**end,int base){
	return strtoll(str,end,base);
}
