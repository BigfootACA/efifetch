#include"efi.h"
#include"init.h"
#include"print.h"

#if __SIZEOF_POINTER__==8
void*__stack_chk_guard=(void*)(uintptr_t)0xDEADBEEFDEADFEED;
#elif __SIZEOF_POINTER__==4
void*__stack_chk_guard=(void*)(uintptr_t)0xDEADBEEF;
#else
#error unknown pointer size
#endif

__attribute__((noreturn))
void abort(void){
	if(g_bs)g_bs->exit(g_ih,EFI_ABORTED,0,NULL);
	while(1);
}

__attribute__((noreturn))
void __assert_fail(const char*expr,const char*file,int line,const char*func){
	err_printf("assert failed at %s:%d: %s: %s\n",file,line,func,expr);
	abort();
}

__attribute__((noreturn))
void __stack_chk_fail(void){
	if(g_st)g_st->con_stderr->output_string(
		g_st->con_stderr,
		L"stack smashing detected\n"
	);
	abort();
}

__attribute__((noreturn)) 
void __stack_chk_fail_local(void){
	__stack_chk_fail();
}
