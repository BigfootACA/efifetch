#ifndef DATA_H
#define DATA_H
#include"efi.h"
struct efi_guid_item{
	const efi_guid*guid;
	const char*name;
};
extern struct efi_guid_item efi_guid_table[];
typedef struct arm_cpuid_item{
	uint8_t implementer;
	uint16_t part;
	const char*name;
}arm_cpuid_item;
extern arm_cpuid_item arm_cpuid_items[];
#define DECL_CPUID_ARM_START arm_cpuid_item arm_cpuid_items[]={
#define DECL_CPUID_ARM_END {0,0,NULL}};
#define DECL_CPUID_ARM_PART(_imp,_part,_name) \
	{.implementer=_imp,.part=_part,.name=_name},
#define DECL_CPUID_ARM_IMPL(_imp,_name) \
	DECL_CPUID_ARM_PART(_imp,0xFFFF,_name)
typedef struct gpu_item{
	uint16_t vendor;
	uint16_t device;
	const char*name;
}gpu_item;
extern gpu_item gpu_db[];
#define GPU_DB_START gpu_item gpu_db[]={
#define GPU_DB_END {0,0,NULL}};
#define GPU_DB_ITEM(_vendor,_device,_name) {.vendor=(_vendor),.device=(_device),.name=(_name)},
#define GPU_DB_VENDOR(_vendor,_name) GPU_DB_ITEM(_vendor,0xFFFF,_name)
#endif
