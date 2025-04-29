#include"efi.h"
#include"str.h"
#include"net.h"

int ipv4_to_string(efi_ipv4_address*ip,char*buff,size_t len){
	if(!ip||!buff||len<8)return -1;
	return snprintf(buff,len,"%u.%u.%u.%u",
		ip->addr[0],ip->addr[1],
		ip->addr[2],ip->addr[3]
	);
}

int ipv4_to_prefix(efi_ipv4_address*msk){
	if(!msk)return -1;
	int prefix=0;
	uint32_t mask_val=msk->raw;
	unsigned long m=0x80000000;
	while(prefix<32&&m){
		if(mask_val&m)prefix++;
		m>>=1;
	}
	return prefix;
}

int ipv6_to_string(efi_ipv6_address*ip,char*buff,size_t len){
	if(!ip||!buff||len<39)return -1;
	memset(buff,0,len);
	if(ip->u64[0]==0&&ip->u16[4]==0&&ip->u16[5]==0xFFFF){
		strlcat(buff,"::ffff:",len);
		efi_ipv4_address addr={.raw=ip->u32[3]};
		int r=ipv4_to_string(&addr,buff+7,len-7);
		return r<0?-1:r+7;
	}
	bool zeroed=false,in_zero=false;
	for(int i=0;i<8;i++){
		if(ip->u16[i]==0){
			if(!zeroed){
				zeroed=true;
				in_zero=true;
				strlcat(buff,"::",len);
				continue;
			}else if(in_zero)continue;
		}else if(in_zero){
			in_zero=false;
		}else if(i>0)strlcat(buff,":",len);
		scprintf(buff,len,"%x",SWAP16(ip->u16[i]));
	}
	return strlen(buff);
}
