#include"data.h"
#define DECL_GUID(name,guid...) __unused __weak efi_guid name=guid;
#include"guids.h"
#undef DECL_GUID
__unused __weak struct efi_guid_item efi_guid_table[]={
	#define DECL_GUID(_name,_guid...) {.guid=&_name,.name=#_name},
	#include"guids.h"
	#undef DECL_GUID
	{NULL,NULL}
};
