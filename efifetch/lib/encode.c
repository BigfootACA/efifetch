#include"str.h"

static efi_status proc_transfer(encode_convert_ctx*ctx,size_t*s,size_t*d){
	const convert_transfer*tr;
	uint8_t*dst=(uint8_t*)ctx->in.dst_ptr;
	const uint8_t*src=(const uint8_t*)ctx->in.src_ptr;
	for(int t=0;(tr=ctx->in.transfers[t]);t++)if(
		tr->match_size>0&&tr->replace_size>0&&
		*s+tr->match_size<=ctx->in.src_size&&
		memcmp(src+*s,tr->match,tr->match_size)==0
	){
		if(!tr->replace||tr->replace_size==0)
			return efi_out_of_resources;
		if(*d+tr->replace_size>ctx->in.dst_size)
			return efi_out_of_resources;
		memcpy(dst+*d,tr->replace,tr->replace_size);
		*s+=tr->match_size,*d+=tr->replace_size;
		return efi_success;
	}
	return efi_not_found;
}

static efi_status utf8_to_utf16_convert(encode_convert_ctx*ctx){
	efi_status st,ret=efi_success;
	if(!ctx||!ctx->in.src_ptr||!ctx->in.dst_ptr)
		return efi_invalid_parameter;
	const uint8_t*src=(const uint8_t*)ctx->in.src_ptr;
	size_t src_size=ctx->in.src_size;
	char16*dst=(char16*)ctx->in.dst_ptr;
	size_t dst_size=ctx->in.dst_size/sizeof(char16);
	size_t i=0,j=0;
	while(i<src_size&&j+1<dst_size&&src[i]){
		if(ctx->in.transfers){
			size_t si=i, dj=j*sizeof(char16);
			st=proc_transfer(ctx,&si,&dj);
			if(st==efi_out_of_resources){
				ret=efi_out_of_resources;
				break;
			}else if(st==efi_success){
				i=si,j=dj/sizeof(char16);
				continue;
			}
		}
		uint8_t c=src[i];
		if(c<0x80){
			dst[j++]=c;
			i++;
		}else if((c&0xE0)==0xC0&&i+1<src_size){
			dst[j]=((src[i]&0x1F)<<6)|(src[i+1]&0x3F);
			j++,i+=2;
		}else if((c&0xF0)==0xE0&&i+2<src_size){
			dst[j]=((src[i]&0x0F)<<12)|((src[i+1]&0x3F)<<6)|(src[i+2]&0x3F);
			j++,i+=3;
		}else if(ctx->in.allow_invalid){
			ctx->out.have_invalid=true;
			dst[j++]='?';
			i++;
		}else{
			ctx->out.have_invalid=true;
			ret=efi_warn_unknown_glyph;
			break;
		}
	}
	dst[j]=0;
	ctx->out.src_used=i;
	ctx->out.dst_wrote=j*sizeof(char16);
	ctx->out.src_end=(void*)(src+i);
	ctx->out.dst_end=(void*)(dst+j);
	return ret;
}

static efi_status utf16_to_utf8_convert(encode_convert_ctx*ctx){
	efi_status st,ret=efi_success;
	const char16*src=(const char16*)ctx->in.src_ptr;
	size_t src_size=ctx->in.src_size/sizeof(char16);
	uint8_t*dst=(uint8_t*)ctx->in.dst_ptr;
	size_t dst_size=ctx->in.dst_size;
	size_t i=0,j=0;
	while(i<src_size&&j+1<dst_size&&src[i]){
		if(ctx->in.transfers){
			size_t si=i*sizeof(char16),dj=j;
			st=proc_transfer(ctx,&si,&dj);
			if(st==efi_out_of_resources){
				ret=efi_out_of_resources;
				break;
			}else if(st==efi_success){
				i=si/sizeof(char16),j=dj;
				continue;
			}
		}
		char16 wc=src[i];
		if(wc<0x80){
			if(j+1>dst_size)break;
			dst[j++]=(uint8_t)wc;
		}else if(wc<0x800){
			if(j+2>dst_size)break;
			dst[j++]=0xC0|(wc>>6);
			dst[j++]=0x80|(wc&0x3F);
		}else if(wc>=0xD800&&wc<=0xDFFF){
			ctx->out.have_invalid=true;
			if(ctx->in.allow_invalid){
				dst[j++]='?';
			}else{
				ret=efi_warn_unknown_glyph;
				break;
			}
		}else{
			if(j+3>dst_size)break;
			dst[j++]=0xE0|(wc>>12);
			dst[j++]=0x80|((wc>>6)&0x3F);
			dst[j++]=0x80|(wc&0x3F);
		}
		i++;
	}
	if(j<dst_size)dst[j]=0;
	ctx->out.src_used=i*sizeof(char16);
	ctx->out.dst_wrote=j;
	ctx->out.src_end=(void*)(src+i);
	ctx->out.dst_end=(void*)(dst+j);
	return ret;
}

static struct encoding_convert{
	encoding src;
	encoding dst;
	efi_status(*convert)(encode_convert_ctx*ctx);
}converts[]={
	{ENC_UTF8,ENC_UTF16,utf8_to_utf16_convert},
	{ENC_UTF16,ENC_UTF8,utf16_to_utf8_convert},
	{ENC_NONE,ENC_NONE,NULL},
};

static efi_status copy_convert(encode_convert_ctx*ctx){
	size_t i=0,j=0;
	efi_status st,ret=efi_success;
	if(ctx->in.transfers){
		uint8_t*dst=(uint8_t*)ctx->in.dst_ptr;
		const uint8_t*src=(const uint8_t*)ctx->in.src_ptr;
		while(i<ctx->in.src_size&&j<ctx->in.dst_size&&!efi_error(ret)){
			st=proc_transfer(ctx,&i,&j);
			if(st==efi_out_of_resources)break;
			else if(st==efi_not_found)dst[j++]=src[i++];
			else if(st==efi_success)continue;
			else ret=st;
		}
	}else{
		size_t size=MIN(ctx->in.src_size,ctx->in.dst_size);
		memcpy(ctx->in.dst_ptr,ctx->in.src_ptr,size);
		i=size,j=size;
	}
	ctx->out.src_used=i;
	ctx->out.dst_wrote=j;
	ctx->out.src_end=(void*)ctx->in.src_ptr+i;
	ctx->out.dst_end=(void*)ctx->in.dst_ptr+j;
	return ret;
}

static efi_status center_convert(encode_convert_ctx*ctx){
	if(ctx->in.transfers)return efi_unsupported;
	size_t tmp_buf_size=ctx->in.src_size*4;
	uint8_t*tmp_buf=(uint8_t*)malloc(tmp_buf_size);
	if(!tmp_buf)return efi_out_of_resources;
	encode_convert_ctx src_ctx=*ctx;
	src_ctx.in.dst=ENC_UTF8;
	src_ctx.in.dst_ptr=tmp_buf;
	src_ctx.in.dst_size=tmp_buf_size;
	memset(&src_ctx.out,0,sizeof(src_ctx.out));
	efi_status ret=encode_convert(&src_ctx);
	if(ret!=efi_success&&ret!=efi_warn_unknown_glyph){
		free(tmp_buf);
		return ret;
	}
	encode_convert_ctx dst_ctx=*ctx;
	dst_ctx.in.src=ENC_UTF8;
	dst_ctx.in.src_ptr=tmp_buf;
	dst_ctx.in.src_size=src_ctx.out.dst_wrote;
	memset(&dst_ctx.out,0,sizeof(dst_ctx.out));
	ret=encode_convert(&dst_ctx);
	ctx->out=dst_ctx.out;
	ctx->out.src_used=src_ctx.out.src_used;
	ctx->out.have_invalid=src_ctx.out.have_invalid||dst_ctx.out.have_invalid;
	free(tmp_buf);
	return ret;
}

efi_status encode_convert(encode_convert_ctx*ctx){
	if(!ctx||!ctx->in.src_ptr||!ctx->in.dst_ptr)
		return efi_invalid_parameter;
	if(ctx->in.src==ENC_NONE||ctx->in.dst==ENC_NONE)
		return efi_invalid_parameter;
	memset(&ctx->out,0,sizeof(ctx->out));
	if(ctx->in.src==ctx->in.dst)
		return copy_convert(ctx);
	for(int i=0;converts[i].src!=ENC_NONE;i++)
		if(ctx->in.src==converts[i].src&&ctx->in.dst==converts[i].dst)
			return converts[i].convert(ctx);
	if(ctx->in.src!=ENC_UTF8&&ctx->in.dst!=ENC_UTF8)
		return center_convert(ctx);
	return efi_unsupported;
}
