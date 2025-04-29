#include"efi.h"
#include"elf.h"

efi_status relocate(uintn_t b,Elf32_Dyn*d){
	intn_t relsz=0,relent=0;
	Elf32_Rel*rel=NULL;
	uintn_t*addr;
	int i;
	for(i=0;d[i].d_tag!=DT_NULL;++i)switch(d[i].d_tag){
		case DT_REL:rel=(Elf32_Rel*)((uintn_t)d[i].d_un.d_ptr+b);break;
		case DT_RELSZ:relsz=d[i].d_un.d_val;break;
		case DT_RELENT:relent=d[i].d_un.d_val;break;
		case DT_RELA:break;
		default:break;
	}
	if(!rel&&relent==0)return EFI_SUCCESS;
	if(!rel||relent==0)return EFI_LOAD_ERROR;
	while(relsz>0){
		switch(ELF32_R_TYPE(rel->r_info)){
			case R_386_NONE:break;
			case R_386_RELATIVE:
				addr=(uintn_t*)(b+rel->r_offset);
				*addr+=b;
			break;
			default:break;
		}
		rel=(Elf32_Rel*)((char*)rel+relent);
		relsz-=relent;
	}
	return EFI_SUCCESS;
}
