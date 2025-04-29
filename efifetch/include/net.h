#ifndef NET_H
#define NET_H
#include"efi.h"
extern int ipv4_to_string(efi_ipv4_address*ip,char*buff,size_t len);
extern int ipv4_to_prefix(efi_ipv4_address*msk);
extern int ipv6_to_string(efi_ipv6_address*ip,char*buff,size_t len);
#endif
