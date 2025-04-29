#ifndef UTILS_H
#define UTILS_H
#include"efi.h"
extern efi_handle efi_get_parent_device(efi_handle handle);
extern efi_loaded_image_protocol*efi_get_loaded_image(void);
extern efi_handle efi_get_current_device(void);
extern void*efi_file_get_info_by(efi_file_protocol*f,const efi_guid*guid);
extern efi_file_system_info*efi_get_fs_info(efi_simple_file_system_protocol*fs);
extern efi_simple_file_system_protocol*efi_get_current_fs(void);
#endif
