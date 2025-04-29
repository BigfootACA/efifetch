#include"logo.h"
#include"str.h"
#include"regexp.h"
#include"print.h"

static bool logo_desc_lookup_attr(logo_desc*logo,char ch,uintn_t*attr){
	if(!logo||!logo->attr_map||!attr)return false;
	for(uintn_t i=0;i<logo->attr_map_count;i++){
		if(logo->attr_map[i].ch!=ch)continue;
		*attr=logo->attr_map[i].attr;
		return true;
	}
	return false;
}

efi_status logo_desc_print_line(
	efi_simple_text_output_protocol*con,
	logo_desc*logo,
	uintn_t line
){
	efi_status status=efi_success;
	if(!con||!logo)return efi_invalid_parameter;
	if(line>=logo->lines_count)return efi_invalid_parameter;
	if(!logo->lines[line])return efi_invalid_parameter;
	uintn_t orig_attr=con->mode->attribute.num;
	uintn_t cur_attr=orig_attr;
	char buff[128],ch;
	uintn_t buff_pos=0,total=0;
	con->set_attribute(con,orig_attr);
	for(uintn_t ch_id=0;(ch=logo->lines[line][ch_id]);ch_id++){
		bool have_ch_attr=false;
		uintn_t ch_attr=0;
		have_ch_attr=logo_desc_lookup_attr(logo,ch,&ch_attr);
		if(
			(have_ch_attr&&ch_attr!=cur_attr)||
			buff_pos>=sizeof(buff)-1
		){
			if(buff_pos>0){
				buff[buff_pos]=0;
				status=text_print(con,buff);
				if(efi_error(status))goto fail;
				buff_pos=0;
			}
			status=con->set_attribute(con,ch_attr);
			if(efi_error(status))goto fail;
			cur_attr=ch_attr;
		}
		buff[buff_pos++]=ch;
		total++;
	}
	if(buff_pos>0){
		buff[buff_pos]=0;
		status=text_print(con,buff);
		if(efi_error(status))goto fail;
	}
	if(total<logo->width){
		status=text_print_repeat(con,' ',logo->width-total);
		if(efi_error(status))goto fail;
	}
fail:
	con->set_attribute(con,orig_attr);
	return status;
}

efi_status logo_desc_print(
	efi_simple_text_output_protocol*con,
	logo_desc*logo
){
	efi_status status;
	if(!con||!logo)return efi_invalid_parameter;
	if(!logo->lines)return efi_invalid_parameter;
	for(uintn_t line=0;line<logo->lines_count;line++){
		status=logo_desc_print_line(con,logo,line);
		if(efi_error(status))return status;
		status=text_print(con,"\n");
		if(efi_error(status))return status;
	}
	return efi_success;
}

efi_status logo_ctx_init(
	logo_context*ctx,
	efi_simple_text_output_protocol*con,
	logo_desc*logo,
	uintn_t margin
){
	if(!ctx||!con||!logo)return efi_invalid_parameter;
	if(!logo->lines)return efi_invalid_parameter;
	if(!logo->attr_map)return efi_invalid_parameter;
	memset(ctx,0,sizeof(logo_context));
	ctx->con=con;
	ctx->target_logo=logo;
	ctx->cur_line=0;
	ctx->margin=margin;
	return efi_success;
}

efi_status logo_ctx_print_line(logo_context*ctx){
	if(!ctx)return efi_invalid_parameter;
	// uintn_t attr=ctx->con->mode->attribute.num;
	// uintn_t row=ctx->con->mode->cursor_row;
	// ctx->con->set_attribute(ctx->con,attr);
	// ctx->con->set_cursor_position(ctx->con,0,row);
	// text_print_repeat(ctx->con,' ',80);
	// ctx->con->set_cursor_position(ctx->con,0,row);
	if(ctx->cur_line>=ctx->target_logo->lines_count){
		uintn_t orig_attr=ctx->con->mode->attribute.num,ch_attr=0;
		bool have_attr=logo_desc_lookup_attr(ctx->target_logo,' ',&ch_attr);
		if(have_attr)ctx->con->set_attribute(ctx->con,ch_attr);
		text_print_repeat(ctx->con,' ',ctx->target_logo->width+ctx->margin);
		if(have_attr)ctx->con->set_attribute(ctx->con,orig_attr);
		return efi_success;
	}
	efi_status status=logo_desc_print_line(
		ctx->con,ctx->target_logo,ctx->cur_line
	);
	if(efi_error(status))return status;
	ctx->cur_line++;
	if(ctx->margin>0)text_print_repeat(ctx->con,' ',ctx->margin);
	return efi_success;
}

efi_status logo_ctx_print_remain(logo_context*ctx){
	if(!ctx)return efi_invalid_parameter;
	while(ctx->cur_line<ctx->target_logo->lines_count){
		efi_status status=logo_ctx_print_line(ctx);
		if(efi_error(status))return status;
		status=text_print(ctx->con,"\r\n");
		if(efi_error(status))return status;
	}
	return efi_success;
}

logo_desc*logo_find(const char*name){
	if(!name||!name[0])return NULL;
	for(uintn_t i=0;logos[i];i++){
		if(!logos[i]->matchs)continue;
		for(uintn_t m=0;logos[i]->matchs[m];m++){
			const char*s=logos[i]->matchs[m];
			if(!s[0])continue;
			switch(s[0]){
				case '$':if(regexp_match(s+1,name,REG_ICASE))continue;break;
				case '@':if(!strcasestr(name,s+1))continue;break;
				default:if(strcasecmp(name,s)!=0)continue;break;
			}
			return logos[i];
		}
	}
	return NULL;
}
