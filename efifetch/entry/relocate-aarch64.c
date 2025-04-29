#include"efi.h"
#include"elf.h"

efi_status relocate(uintn_t b,Elf64_Dyn*d){
	intn_t relsz=0,relent=0;
	Elf64_Rela *rel=NULL;
	uintn_t*addr;
	int i;
	for(i=0;d[i].d_tag!=DT_NULL;++i)switch(d[i].d_tag){
		case DT_RELA:rel=(Elf64_Rela*)((uintn_t)d[i].d_un.d_ptr+b);break;
		case DT_RELASZ:relsz=d[i].d_un.d_val;break;
		case DT_RELAENT:relent=d[i].d_un.d_val;break;
		default:break;
	}
	if(!rel&&relent==0)return EFI_SUCCESS;
	if(!rel||relent==0)return EFI_LOAD_ERROR;
	while(relsz>0){
		switch(ELF64_R_TYPE(rel->r_info)){
			case R_AARCH64_NONE:break;
			case R_AARCH64_RELATIVE:
				addr=(uintn_t*)(b+rel->r_offset);
				*addr=b+rel->r_addend;
			break;
			default:break;
		}
		rel=(Elf64_Rela*)((char*)rel+relent);
		relsz-=relent;
	}
	return EFI_SUCCESS;
}
