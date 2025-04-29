#include"str.h"

uintn_t utf8_to_utf16(const char*src,uintn_t src_size,char16*dst,uintn_t dst_size){
	uintn_t i=0;
	if(!src||!dst)return 0;
	memset(dst,0,dst_size);
	while(*src&&i<dst_size/2-1&&i<src_size-1){
		if(*src&0x80){
			if((*src&0xE0)==0xC0){
				dst[i]=*src++&0x1F;
				dst[i]<<=6;
				dst[i]|=*src++&0x3F;
				i++;
			}else if((*src&0xF0)==0xE0){
				dst[i]=*src++&0xF;
				dst[i]<<=6;
				dst[i]|=*src++&0x3F;
				dst[i]<<=6;
				dst[i]|=*src++&0x3F;
				i++;
			}else{
				dst[i++]=*src++;
			}
		}else{
			dst[i++]=*src++;
		}
	}
	dst[i]=0;
	return i;
}

uintn_t utf16_to_utf8(const char16*src,uintn_t src_size,char*dst,uintn_t dst_size){
	uintn_t i=0;
	if(!src||!dst)return 0;
	memset(dst,0,dst_size);
	while(*src&&i<dst_size-1&&i<src_size/2-1){
		if(*src<0x80){
			dst[i++]=*src++;
		}else if(*src<0x800){
			dst[i++]=0xC0|(*src>>6);
			dst[i++]=0x80|(*src&0x3F);
			src++;
		}else{
			dst[i++]=0xE0|(*src>>12);
			dst[i++]=0x80|((*src>>6)&0x3F);
			dst[i++]=0x80|(*src&0x3F);
			src++;
		}
	}
	dst[i]=0;
	return i;
}
