#ifndef EFIFETCH_H
#define EFIFETCH_H
#include"efi.h"
#include"logo.h"
#include"smbios.h"
enum efifetch_field{
	EFIFETCH_FIELD_MIN=0,
	EFIFETCH_FIELD_NAME=0,
	EFIFETCH_FIELD_FIRMWARE,
	EFIFETCH_FIELD_HOST,
	EFIFETCH_FIELD_SPEC,
	EFIFETCH_FIELD_UPTIME,
	EFIFETCH_FIELD_DISPLAY,
	EFIFETCH_FIELD_ARCH,
	EFIFETCH_FIELD_CPUID,
	EFIFETCH_FIELD_CPU,
	EFIFETCH_FIELD_GPU,
	EFIFETCH_FIELD_MEMORY,
	EFIFETCH_FIELD_FILESYSTEM,
	EFIFETCH_FIELD_DISK,
	EFIFETCH_FIELD_IP4,
	EFIFETCH_FIELD_IP6,
	EFIFETCH_FIELD_SECURE_BOOT,
	EFIFETCH_FIELD_MAX,

};
typedef struct efifetch{
	logo_context logo;
	void*fdt;
	smbios_table2_entry_point*smbios2;
	smbios_table3_entry_point*smbios3;
	struct{
		char value[80];
	}fields[EFIFETCH_FIELD_MAX];
}efifetch;
extern void efifetch_load_info(efifetch*ctx);
extern void efifetch_print_all(efifetch*ctx);
extern void efifetch_print_field(efifetch*ctx,enum efifetch_field field);
#endif
