#ifndef INFO_H
#define INFO_H
#include"efi.h"
#include"efifetch.h"
extern void efifetch_init_info_fdt(efifetch*ctx);
extern void efifetch_init_info_smbios(efifetch*ctx);
extern void efifetch_load_info(efifetch*ctx);
extern void efifetch_load_info_gpu(efifetch*ctx);
extern void efifetch_load_info_mem(efifetch*ctx);
extern void efifetch_load_info_smbios(efifetch*ctx);
extern void efifetch_load_info_sys(efifetch*ctx);
extern void efifetch_load_info_fdt(efifetch*ctx);
extern void efifetch_load_info_net(efifetch*ctx);
extern void efifetch_load_info_fs(efifetch*ctx);
extern void efifetch_load_info_time(efifetch*ctx);
extern void efifetch_load_info_disk(efifetch*ctx);
extern void efifetch_load_info_cpuid(efifetch*ctx);
extern smbios_structure_pointer efifetch_get_smbios_by_type(efifetch*ctx,uint8_t type,smbios_handle handle);
extern smbios_structure_pointer efifetch_get_smbios_by_handle(efifetch*ctx,smbios_handle handle);
extern const char*efifetch_get_smbios_string(efifetch*ctx,smbios_structure_pointer p,smbios_table_string id);
extern bool efifetch_load_smbios_string(efifetch*ctx,smbios_structure_pointer p,smbios_table_string id,char*buff,size_t size);
extern bool efifetch_field_is_empty(efifetch*ctx,enum efifetch_field field);
extern void efifetch_field_reset(efifetch*ctx,enum efifetch_field field);
extern void efifetch_field_set(efifetch*ctx,enum efifetch_field field,const char*value);
extern void efifetch_field_setn(efifetch*ctx,enum efifetch_field field,const char*value,size_t len);
extern void efifetch_field_setf(efifetch*ctx,enum efifetch_field field,const char*fmt,...);
extern void efifetch_field_append(efifetch*ctx,enum efifetch_field field,const char*value);
extern void efifetch_field_appendn(efifetch*ctx,enum efifetch_field field,const char*value,size_t len);
extern void efifetch_field_appendf(efifetch*ctx,enum efifetch_field field,const char*fmt,...);
#define SMBIOS_GET(_ptr,_type,_field,_def)({\
	smbios_structure_pointer _p=(_ptr);\
	uintn_t _min_len=offsetof(smbios_table_type##_type,_field)+sizeof(_p.type##_type->_field);\
	_p.header->length>_min_len?_p.type##_type->_field:(_def);\
})
#define SMBIOS_VARX(_name,_ptr,_type,_field,_def)\
	typeof((_ptr).type##_type->_field) _name=SMBIOS_GET(_ptr,_type,_field,_def)
#define SMBIOS_VAR(_ptr,_type,_field,_def) SMBIOS_VARX(_field,_ptr,_type,_field,_def)
#define IS_EMPTY(_type) efifetch_field_is_empty(ctx,EFIFETCH_FIELD_##_type)
#define SET(_type,_value) efifetch_field_set(ctx,EFIFETCH_FIELD_##_type,_value)
#define SETN(_type,_value,_len) efifetch_field_setn(ctx,EFIFETCH_FIELD_##_type,_value,_len)
#define SETF(_type,_value...) efifetch_field_setf(ctx,EFIFETCH_FIELD_##_type,_value)
#define APPEND(_type,_value) efifetch_field_append(ctx,EFIFETCH_FIELD_##_type,_value)
#define APPENDN(_type,_value,_len) efifetch_field_appendn(ctx,EFIFETCH_FIELD_##_type,_value,_len)
#define APPENDF(_type,_value...) efifetch_field_appendf(ctx,EFIFETCH_FIELD_##_type,_value)
#define RESET(_type) efifetch_field_reset(ctx,EFIFETCH_FIELD_##_type)
#endif
