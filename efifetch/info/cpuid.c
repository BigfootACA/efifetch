#include"info.h"
#include"data.h"
#include"arm64.h"
#include"print.h"
#include"str.h"

#if defined (__aarch64__)
static void efifetch_load_info_cpuid_arch(efifetch*ctx){
	midr_data midr={};
	current_el_data el={};
	asm volatile("mrs %0,midr_el1":"=r"(midr.value));
	asm volatile("mrs %0,CurrentEL":"=r"(el.value));
	dbg_printf("midr: 0x%016llx\n",midr.value);
	const arm_cpuid_item*impl=NULL,*part=NULL;
	for(uintn_t i=0;arm_cpuid_items[i].name;i++){
		if(arm_cpuid_items[i].implementer!=midr.Implementer)continue;
		if(arm_cpuid_items[i].part==0xFFFF){
			impl=&arm_cpuid_items[i];
			dbg_printf("found arm64 cpuid implementer %s\n",impl->name);
		}else if(arm_cpuid_items[i].part==midr.PartNum){
			part=&arm_cpuid_items[i];
			dbg_printf("found arm64 cpuid part %s\n",part->name);
		}
		if(impl&&part)break;
	}
	if(impl)SET(CPUID,impl->name);
	else SETF(CPUID,"implementer 0x%02x",midr.Implementer);
	if(!IS_EMPTY(CPUID))APPEND(CPUID," ");
	if(part)APPEND(CPUID,part->name);
	else APPENDF(CPUID,"part 0x%04x",midr.PartNum);
	if(midr.Revision>0){
		if(!IS_EMPTY(CPUID))APPEND(CPUID," ");
		APPENDF(CPUID,"rev %u",midr.Revision);
	}
	if(!IS_EMPTY(CPUID))APPEND(CPUID," ");
	APPENDF(CPUID,"(EL%u)",el.EL);
}

#elif defined(__x86_64__) || defined(__i386__)

static void read_cpuid_brand(char*buff,size_t len){
	if(!buff||len<64)return;
	memset(buff,0,len);
	uint32_t cmd=0x80000002;
	for(uint32_t i=0;i<3;i++){
		uint32_t eax=0,ebx=0,ecx=0,edx=0;
		asm volatile(
			"cpuid":"=a"(eax),"=b"(ebx),
			"=c"(ecx),"=d"(edx):"a"(cmd)
		);
		memcpy(&buff[i*16+0],&eax,4);
		memcpy(&buff[i*16+4],&ebx,4);
		memcpy(&buff[i*16+8],&ecx,4);
		memcpy(&buff[i*16+12],&edx,4);
		cmd++;
	}
}

static void efifetch_load_info_cpuid_arch(efifetch*ctx){
	char buff[64]={};
	read_cpuid_brand(buff,sizeof(buff));
	if(buff[0]){
		if(!IS_EMPTY(CPUID))APPEND(CPUID," ");
		trim(buff);
		APPENDN(CPUID,buff,sizeof(buff));
	}
}

#else

static void efifetch_load_info_cpuid_arch(efifetch*ctx){}

#endif

static void efifetch_load_info_arch(efifetch*ctx){
	const char*arch=NULL;
	#if defined(__i386__)
	arch="x86";
	#elif defined(__x86_64__)
	arch="x86_64";
	#elif defined(__aarch64__)
	arch="ARM64";
	#elif defined(__arm__)
	arch="ARM32";
	#elif defined(__riscv__)
	arch="RISC-V";
	#elif defined(__mips__)
	arch="MIPS";
	#elif defined(__loongarch__)
	arch="LoongArch";
	#else
	arch="Unknown";
	#endif
	SETF(ARCH,"%s (%ubits)",arch,sizeof(void*)*8);
}

void efifetch_load_info_cpuid(efifetch*ctx){
	if(IS_EMPTY(CPUID)){
		RESET(CPUID);
		efifetch_load_info_cpuid_arch(ctx);
	}
	if(IS_EMPTY(ARCH)){
		RESET(ARCH);
		efifetch_load_info_arch(ctx);
	}
}
