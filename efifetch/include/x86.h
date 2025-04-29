#ifndef X86_H
#define X86_H
#include"efi.h"
typedef union eflags_data eflags_data;
union eflags_data{
	struct{
		bool CF:1;
		uint8_t:1;
		bool PF:1;
		uint8_t:1;
		bool AF:1;
		uint8_t:1;
		bool ZF:1;
		bool SF:1;
		bool TF:1;
		bool IF:1;
		bool DF:1;
		bool OF:1;
		bool IOPL:2;
		bool NT:1;
		uint8_t:1;
		bool RF:1;
		bool VM:1;
		bool AC:1;
		bool VIF:1;
		bool VIP:1;
		bool ID:1;
		uint16_t:10;
	}__packed;
	uint32_t value;
}__packed;
#endif
