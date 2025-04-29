#include"efi.h"
#include"init.h"

extern efi_status efiapi uefi_main(
	efi_handle image_handle,
	efi_system_table*system_table
);

static_assert(sizeof(efi_status)       == sizeof(EFI_STATUS),       "efi_status mismatch");
static_assert(sizeof(efi_handle)       == sizeof(EFI_HANDLE),       "efi_handle mismatch");
static_assert(sizeof(efi_system_table) == sizeof(EFI_SYSTEM_TABLE), "efi_system_table mismatch");

EFI_STATUS EFIAPI UefiMain(
	IN EFI_HANDLE        ImageHandle,
	IN EFI_SYSTEM_TABLE  *SystemTable
){
	initialize(
		(efi_handle)ImageHandle,
		(efi_system_table*)SystemTable
	);
	return (efi_status)uefi_main(
		(efi_handle)ImageHandle,
		(efi_system_table*)SystemTable
	);
}
