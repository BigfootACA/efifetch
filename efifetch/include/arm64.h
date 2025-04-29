#ifndef ARM64_H
#define ARM64_H
#include"efi.h"
typedef enum current_el_val current_el_val;
typedef union current_el_data current_el_data;
enum current_el_val{
	CURR_EL0 = 0,
	CURR_EL1 = 1,
	CURR_EL2 = 2,
	CURR_EL3 = 3,
};
union current_el_data{
	struct{
		uint64_t:2;
		current_el_val EL:2;
		uint64_t:60;
	}__packed;
	uint64_t value;
}__packed;
typedef enum mpidr_u mpidr_u;
typedef union mpidr_data mpidr_data;
enum mpidr_u{
	MPIDR_MP=0,
	MPIDR_UP=1,
};
union mpidr_data{
	struct{
		uint8_t AFF0;
		uint8_t AFF1;
		uint8_t AFF2;
		bool MT:1;
		uint8_t:5;
		mpidr_u U:1;
		uint8_t:1;
		uint8_t AFF3;
		uint32_t:24;
	}__packed;
	uint64_t value;
}__packed;
typedef union midr_data midr_data;
union midr_data{
	struct{
		uint8_t Revision:4;
		uint16_t PartNum:12;
		uint8_t Arch:4;
		uint8_t Variant:4;
		uint8_t Implementer;
		uint32_t:32;
	}__packed;
	uint64_t value;
}__packed;
#endif
