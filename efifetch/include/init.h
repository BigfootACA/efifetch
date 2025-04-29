#ifndef INIT_H
#define INIT_H
#include"efi.h"
extern efi_handle g_ih;
extern efi_system_table*g_st;
extern efi_boot_services*g_bs;
extern efi_runtime_services*g_rt;
#ifdef stdin
#undef stdin
#endif
#ifdef stdout
#undef stdout
#endif
#ifdef stderr
#undef stderr
#endif
#define stdin  (g_st?g_st->con_stdin:NULL)
#define stdout (g_st?g_st->con_stdout:NULL)
#define stderr (g_st?g_st->con_stderr:NULL)
extern void efiapi initialize(efi_handle ih,efi_system_table*st);
#endif
