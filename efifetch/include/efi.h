#ifndef EFI_H
#define EFI_H
#ifndef __cplusplus
#ifndef static_assert
#define static_assert _Static_assert
#endif
#define bool    unsigned char
#define true    1
#define false   0
#ifndef NULL
#define NULL ((void*)0)
#endif
#endif
#ifndef __weak
#define __weak __attribute__((weak))
#endif
#ifndef __used
#define __used __attribute__((used))
#endif
#ifndef __unused
#define __unused __attribute__((unused))
#endif
#ifndef __packed
#define __packed __attribute__((packed))
#endif
#define SWAP16(_v) ((((_v)&0xFF00)>>8)|(((_v)&0x00FF)<<8))
#define SWAP32(_v) SWAP16(((_v)&0xFFFF0000)>>16)|SWAP16((_v)&0x0000FFFF)
#define SWAP64(_v) SWAP32(((_v)&0xFFFFFFFF00000000)>>32)|SWAP32((_v)&0x00000000FFFFFFFF)
#ifndef MIN
#define MIN(a,b)({\
	typeof(a)_a=(a);\
	typeof(b)_b=(b);\
	(_b)>(_a)?(_a):(_b);\
})
#endif
#ifndef MAX
#define MAX(a,b)({\
	typeof(a)_a=(a);\
	typeof(b)_b=(b);\
	(_b)<(_a)?(_a):(_b);\
})
#endif
#define CHAR_MIN INT8_MIN
#define CHAR_MAX INT8_MAX
#define UCHAR_MAX UINT8_MAX
#define SHORT_MIN INT16_MIN
#define SHORT_MAX INT16_MAX
#define USHORT_MAX UINT16_MAX
#if __SIZEOF_INT__==4
#define INT_MIN INT32_MIN
#define INT_MAX INT32_MAX
#define UINT_MAX UINT32_MAX
#else
#error unknown int size
#endif
#if __SIZEOF_LONG__==4
#define LONG_MIN INT32_MIN
#define LONG_MAX INT32_MAX
#define ULONG_MAX UINT32_MAX
#elif __SIZEOF_LONG__==8
#define LONG_MIN INT64_MIN
#define LONG_MAX INT64_MAX
#define ULONG_MAX UINT64_MAX
#else
#error unknown long size
#endif
#if __SIZEOF_LONG_LONG__==8
#define LONGLONG_MIN INT64_MIN
#define LONGLONG_MAX INT64_MAX
#define ULONGLONG_MAX UINT64_MAX
#else
#error unknown long long size
#endif
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;
typedef char char8;
typedef unsigned short char16;
#define UINT8_MAX 0xFF
#define UINT16_MAX 0xFFFF
#define UINT32_MAX 0xFFFFFFFF
#define UINT64_MAX 0xFFFFFFFFFFFFFFFF
#define INT8_MAX 0x7F
#define INT16_MAX 0x7FFF
#define INT32_MAX 0x7FFFFFFF
#define INT64_MAX 0x7FFFFFFFFFFFFFFF
#define INT8_MIN 0x80
#define INT16_MIN 0x8000
#define INT32_MIN 0x80000000
#define INT64_MIN 0x8000000000000000
#if __SIZEOF_POINTER__==8
typedef uint64_t uintn_t;
typedef uint64_t uintptr_t;
typedef int64_t intn_t;
typedef int64_t intptr_t;
typedef int64_t ptrdiff_t;
#define INTN_MAX INT64_MAX
#define INTN_MIN INT64_MIN
#define UINTN_MAX UINT64_MAX
#elif __SIZEOF_POINTER__==4
typedef uint32_t uintn_t;
typedef uint32_t uintptr_t;
typedef int32_t intn_t;
typedef int32_t intptr_t;
typedef int32_t ptrdiff_t;
#define INTN_MAX INT32_MAX
#define INTN_MIN INT32_MIN
#define UINTN_MAX UINT32_MAX
#else
#error unknown pointer size
#endif
#if __SIZEOF_SIZE_T__==8
typedef uint64_t size_t;
typedef int64_t ssize_t;
#elif __SIZEOF_SIZE_T__==4
typedef uint32_t size_t;
typedef int32_t ssize_t;
#else
#error unknown size_t size
#endif
#ifdef EFIAPI
#define efiapi EFIAPI
#elif defined(__x86_64__)||defined(__amd64__)
#define efiapi __attribute__((ms_abi))
#else
#define efiapi
#endif
#ifndef VA_START
#if defined(__x86_64__)||defined(__amd64__)
typedef __builtin_ms_va_list VA_LIST;
#define VA_START(va,param)      __builtin_ms_va_start(va,param)
#define VA_ARG(va,type)         ((sizeof(type)<sizeof(uintn_t))?(type)(__builtin_va_arg(va,uintn_t)):(type)(__builtin_va_arg(va,type)))
#define VA_END(va)              __builtin_ms_va_end(va)
#define VA_COPY(dest,start)     __builtin_ms_va_copy(dest, start)
#else
typedef __builtin_va_list VA_LIST;
#define VA_START(va,param)      __builtin_va_start(va,param)
#define VA_ARG(va,type)         __builtin_va_arg(va,type)
#define VA_END(va)              __builtin_va_end(va)
#define VA_COPY(dest,start)     __builtin_va_copy(dest,start)
#endif
#endif
#ifndef va_start
typedef __builtin_va_list va_list;
#define va_start(va,param)      __builtin_va_start(va,param)
#define va_arg(va,type)         __builtin_va_arg(va,type)
#define va_end(va)              __builtin_va_end(va)
#define va_copy(dest,start)     __builtin_va_copy(dest,start)
#endif
#ifndef EFI_PAGE_SIZE
#define EFI_PAGE_SIZE 0x1000
#else
static_assert(EFI_PAGE_SIZE==0x1000,"page size mismatch");
#endif
#ifndef SIGNATURE_16
#define SIGNATURE_16(A,B)((A)|(B<<8))
#endif
#ifndef SIGNATURE_32
#define SIGNATURE_32(A,B,C,D)(SIGNATURE_16(A,B)|(SIGNATURE_16(C,D)<<16))
#endif
#ifndef SIGNATURE_64
#define SIGNATURE_64(A,B,C,D,E,F,G,H)(SIGNATURE_32(A,B,C,D)|((uint64_t)(SIGNATURE_32(E,F,G,H))<<32))
#endif
#ifndef EVT_TIMER
#define EVT_TIMER                               0x80000000
#define EVT_RUNTIME                             0x40000000
#define EVT_NOTIFY_WAIT                         0x00000100
#define EVT_NOTIFY_SIGNAL                       0x00000200
#define EVT_SIGNAL_EXIT_BOOT_SERVICES           0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE       0x60000202
#endif
#ifndef TPL_APPLICATION
#define TPL_APPLICATION         0x04
#define TPL_CALLBACK            0x08
#define TPL_NOTIFY              0x10
#define TPL_HIGH_LEVEL          0x1F
#endif
#define EFI_MEMORY_UC               0x0000000000000001ULL
#define EFI_MEMORY_WC               0x0000000000000002ULL
#define EFI_MEMORY_WT               0x0000000000000004ULL
#define EFI_MEMORY_WB               0x0000000000000008ULL
#define EFI_MEMORY_UCE              0x0000000000000010ULL
#define EFI_MEMORY_WP               0x0000000000001000ULL
#define EFI_MEMORY_RP               0x0000000000002000ULL
#define EFI_MEMORY_XP               0x0000000000004000ULL
#define EFI_MEMORY_RO               0x0000000000020000ULL
#define EFI_MEMORY_NV               0x0000000000008000ULL
#define EFI_MEMORY_MORE_RELIABLE    0x0000000000010000ULL
#define EFI_MEMORY_SP               0x0000000000040000ULL
#define EFI_MEMORY_CPU_CRYPTO       0x0000000000080000ULL
#define EFI_MEMORY_RUNTIME          0x8000000000000000ULL
#define EFI_CACHE_ATTRIBUTE_MASK (EFI_MEMORY_UC | EFI_MEMORY_WC | EFI_MEMORY_WT | EFI_MEMORY_WB | EFI_MEMORY_UCE | EFI_MEMORY_WP)
#define EFI_MEMORY_ACCESS_MASK (EFI_MEMORY_RP | EFI_MEMORY_XP | EFI_MEMORY_RO)
#define EFI_MEMORY_ATTRIBUTE_MASK (EFI_MEMORY_ACCESS_MASK | EFI_MEMORY_SP | EFI_MEMORY_CPU_CRYPTO)
#define EFI_VARIABLE_NON_VOLATILE                            0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS                      0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS                          0x00000004
#define EFI_VARIABLE_HARDWARE_ERROR_RECORD                   0x00000008
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS   0x00000020
#define EFI_VARIABLE_APPEND_WRITE                            0x00000040
#define EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS              0x00000010
#define EFI_VARIABLE_ATTRIBUTE_NV_BS (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS)
#define EFI_VARIABLE_ATTRIBUTE_BS_RT (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS)
#define EFI_VARIABLE_ATTRIBUTE_BS_RT_AT (VARIABLE_ATTRIBUTE_BS_RT | EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS)
#define EFI_VARIABLE_ATTRIBUTE_NV_BS_RT (VARIABLE_ATTRIBUTE_BS_RT | EFI_VARIABLE_NON_VOLATILE)
#define EFI_VARIABLE_ATTRIBUTE_NV_BS_RT_HR (VARIABLE_ATTRIBUTE_NV_BS_RT | EFI_VARIABLE_HARDWARE_ERROR_RECORD)
#define EFI_VARIABLE_ATTRIBUTE_NV_BS_RT_AT (VARIABLE_ATTRIBUTE_NV_BS_RT | EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS)
#define EFI_VARIABLE_ATTRIBUTE_AT EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS
#define EFI_VARIABLE_ATTRIBUTE_NV_BS_RT_HR_AT (VARIABLE_ATTRIBUTE_NV_BS_RT_HR | VARIABLE_ATTRIBUTE_AT)
#define EFI_VARIABLE_ATTRIBUTE_AT_AW (EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS | EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS)
#define EFI_VARIABLE_ATTRIBUTE_NV_BS_RT_AW (VARIABLE_ATTRIBUTE_NV_BS_RT | EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS)
#define EFI_VARIABLE_ATTRIBUTE_NV_BS_RT_HR_AT_AW (VARIABLE_ATTRIBUTE_NV_BS_RT_HR | VARIABLE_ATTRIBUTE_AT_AW)
#define EFI_VARIABLE_ATTRIBUTES_MASK (\
	EFI_VARIABLE_NON_VOLATILE|\
	EFI_VARIABLE_BOOTSERVICE_ACCESS|\
	EFI_VARIABLE_RUNTIME_ACCESS|\
	EFI_VARIABLE_HARDWARE_ERROR_RECORD|\
	EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS|\
	EFI_VARIABLE_APPEND_WRITE\
)
#if (defined(__GNUC__)&&__GNUC__>=4)||defined(__clang__)
#define offsetof(t,f) ((uintn_t)__builtin_offsetof(t,f))
#endif
#ifndef offsetof
#define offsetof(type,field)((uintn_t)&(((type*)0)->field))
#endif
typedef union{uint8_t v[sizeof(float)];float d;}float_t;
typedef union{uint8_t v[sizeof(double)];double d;}double_t;
typedef union{uint8_t v[sizeof(long double)];long double d;}longdouble_t;
static_assert(sizeof(float)==sizeof(float_t),"float_t mimatch");
static_assert(sizeof(double)==sizeof(double_t),"double_t mimatch");
static_assert(sizeof(long double)==sizeof(longdouble_t),"longdouble_t mimatch");
typedef uint16_t uchar16;
typedef uintn_t efi_tpl;
typedef uint64_t efi_lba;
typedef void*efi_event;
typedef void*efi_handle;
static_assert(sizeof(char8)==1,"char8 not 8-bits");
static_assert(sizeof(char16)==2,"char16 not 16-bits");
struct __packed_check{
	uint64_t a;
	uint8_t b;
	uint64_t c;
};
static_assert(sizeof(struct __packed_check)==24,"packed check failed");
typedef struct guid{
	uint32_t data1;
	uint16_t data2;
	uint16_t data3;
	uint8_t  data4[8];
}guid;
static_assert(sizeof(guid)==16,"efi guid size mismatch");
typedef struct efi_time{
	uint16_t year;
	uint8_t  month;
	uint8_t  day;
	uint8_t  hour;
	uint8_t  minute;
	uint8_t  second;
	uint8_t  pad1;
	uint32_t nanosecond;
	int16_t  timezone;
	uint8_t  daylight;
	uint8_t  pad2;
}efi_time;
static_assert(sizeof(efi_time)==16,"efi time size mismatch");
typedef struct efi_table_header{
	uint64_t sign;
	union{
		struct{
			uint16_t rev_minor;
			uint16_t rev_major;
		};
		uint32_t revision;
	};
	uint32_t header_size;
	uint32_t crc32;
	uint32_t reserved;
}efi_table_header;
static_assert(sizeof(efi_table_header)==24,"efi table header size mismatch");
typedef enum efi_memory_type{
	efi_reserved_memory_type,
	efi_loader_code,
	efi_loader_data,
	efi_bs_code,
	efi_bs_data,
	efi_rs_code,
	efi_rs_data,
	efi_conventional_memory,
	efi_unusable_memory,
	efi_acpi_reclaim_memory,
	efi_acpi_memory_nvs,
	efi_mmio,
	efi_mmio_port_space,
	efi_pal_code,
	efi_persistent_memory,
	efi_max_memory_type,
	efi_memory_type_max = UINT32_MAX,
}efi_memory_type;
typedef enum efi_allocate_type{
	allocate_any_pages,
	allocate_max_address,
	allocate_address,
	allocate_max
}efi_allocate_type;
typedef union efi_address{
	uint64_t  uint64;
	uintn_t   uintn;
	uintptr_t uintptr;
	intptr_t  intptr;
	void      *ptr;
}efi_address;
static_assert(sizeof(efi_address)==sizeof(uint64_t),"efi address size mismatch");
typedef struct efi_memory_descriptor{
	efi_memory_type type:32;
	efi_address     physical_start;
	efi_address     virtual_start;
	uint64_t        pages;
	uint64_t        attribute;
}efi_memory_descriptor;
static_assert(sizeof(efi_memory_descriptor)==40,"efi memory descriptor size mismatch");
typedef struct efi_mac_address{
	uint8_t addr[32];
}efi_mac_address;
typedef struct efi_ipv4_address{
	union{
		uint8_t addr[4];
		uint16_t u16[2];
		uint32_t u32[1];
		uint32_t raw;
	};
}efi_ipv4_address;
typedef struct efi_ipv6_address{
	union{
		uint8_t addr[16];
		uint16_t u16[8];
		uint32_t u32[4];
		uint64_t u64[2];
	};
}efi_ipv6_address;
typedef union efi_ip_address{
	uint32_t          addr[4];
	efi_ipv4_address  v4;
	efi_ipv6_address  v6;
}efi_ip_address;
#ifdef __UEFI_SPEC_H__
typedef EFI_GUID efi_guid;
#else
typedef guid efi_guid;
#endif
#ifndef EFI_SPECIFICATION_VERSION
#define EFI_2_80_REVISION ((2<<16)|(80))
#define EFI_2_70_REVISION ((2<<16)|(70))
#define EFI_2_60_REVISION ((2<<16)|(60))
#define EFI_2_50_REVISION ((2<<16)|(50))
#define EFI_2_40_REVISION ((2<<16)|(40))
#define EFI_2_31_REVISION ((2<<16)|(31))
#define EFI_2_30_REVISION ((2<<16)|(30))
#define EFI_2_20_REVISION ((2<<16)|(20))
#define EFI_2_10_REVISION ((2<<16)|(10))
#define EFI_2_00_REVISION ((2<<16)|(00))
#define EFI_1_10_REVISION ((1<<16)|(10))
#define EFI_1_02_REVISION ((1<<16)|(02))
#define EFI_LATEST_VERSION EFI_2_80_REVISION
#define EFI_SPECIFICATION_VERSION EFI_2_70_REVISION
#endif
#define return_error(code) (code!=return_success)
#define efi_error(code) (code!=efi_success)
#ifndef MAX_BIT
#define MAX_BIT ((uintn_t)((1ULL<<(sizeof(uintn_t)*8-1))))
#endif
#ifndef RETURN_SUCCESS
#define RETURN_SUCCESS               0
#define RETURN_LOAD_ERROR            (MAX_BIT|1)
#define RETURN_INVALID_PARAMETER     (MAX_BIT|2)
#define RETURN_UNSUPPORTED           (MAX_BIT|3)
#define RETURN_BAD_BUFFER_SIZE       (MAX_BIT|4)
#define RETURN_BUFFER_TOO_SMALL      (MAX_BIT|5)
#define RETURN_NOT_READY             (MAX_BIT|6)
#define RETURN_DEVICE_ERROR          (MAX_BIT|7)
#define RETURN_WRITE_PROTECTED       (MAX_BIT|8)
#define RETURN_OUT_OF_RESOURCES      (MAX_BIT|9)
#define RETURN_VOLUME_CORRUPTED      (MAX_BIT|10)
#define RETURN_VOLUME_FULL           (MAX_BIT|11)
#define RETURN_NO_MEDIA              (MAX_BIT|12)
#define RETURN_MEDIA_CHANGED         (MAX_BIT|13)
#define RETURN_NOT_FOUND             (MAX_BIT|14)
#define RETURN_ACCESS_DENIED         (MAX_BIT|15)
#define RETURN_NO_RESPONSE           (MAX_BIT|16)
#define RETURN_NO_MAPPING            (MAX_BIT|17)
#define RETURN_TIMEOUT               (MAX_BIT|18)
#define RETURN_NOT_STARTED           (MAX_BIT|19)
#define RETURN_ALREADY_STARTED       (MAX_BIT|20)
#define RETURN_ABORTED               (MAX_BIT|21)
#define RETURN_ICMP_ERROR            (MAX_BIT|22)
#define RETURN_TFTP_ERROR            (MAX_BIT|23)
#define RETURN_PROTOCOL_ERROR        (MAX_BIT|24)
#define RETURN_INCOMPATIBLE_VERSION  (MAX_BIT|25)
#define RETURN_SECURITY_VIOLATION    (MAX_BIT|26)
#define RETURN_CRC_ERROR             (MAX_BIT|27)
#define RETURN_END_OF_MEDIA          (MAX_BIT|28)
#define RETURN_END_OF_FILE           (MAX_BIT|31)
#define RETURN_INVALID_LANGUAGE      (MAX_BIT|32)
#define RETURN_COMPROMISED_DATA      (MAX_BIT|33)
#define RETURN_HTTP_ERROR            (MAX_BIT|35)
#define RETURN_WARN_UNKNOWN_GLYPH    1
#define RETURN_WARN_DELETE_FAILURE   2
#define RETURN_WARN_WRITE_FAILURE    3
#define RETURN_WARN_BUFFER_TOO_SMALL 4
#define RETURN_WARN_STALE_DATA       5
#define RETURN_WARN_FILE_SYSTEM      6
#endif
#ifndef EFI_SUCCESS
#define EFI_SUCCESS                  RETURN_SUCCESS
#define EFI_LOAD_ERROR               RETURN_LOAD_ERROR
#define EFI_INVALID_PARAMETER        RETURN_INVALID_PARAMETER
#define EFI_UNSUPPORTED              RETURN_UNSUPPORTED
#define EFI_BAD_BUFFER_SIZE          RETURN_BAD_BUFFER_SIZE
#define EFI_BUFFER_TOO_SMALL         RETURN_BUFFER_TOO_SMALL
#define EFI_NOT_READY                RETURN_NOT_READY
#define EFI_DEVICE_ERROR             RETURN_DEVICE_ERROR
#define EFI_WRITE_PROTECTED          RETURN_WRITE_PROTECTED
#define EFI_OUT_OF_RESOURCES         RETURN_OUT_OF_RESOURCES
#define EFI_VOLUME_CORRUPTED         RETURN_VOLUME_CORRUPTED
#define EFI_VOLUME_FULL              RETURN_VOLUME_FULL
#define EFI_NO_MEDIA                 RETURN_NO_MEDIA
#define EFI_MEDIA_CHANGED            RETURN_MEDIA_CHANGED
#define EFI_NOT_FOUND                RETURN_NOT_FOUND
#define EFI_ACCESS_DENIED            RETURN_ACCESS_DENIED
#define EFI_NO_RESPONSE              RETURN_NO_RESPONSE
#define EFI_NO_MAPPING               RETURN_NO_MAPPING
#define EFI_TIMEOUT                  RETURN_TIMEOUT
#define EFI_NOT_STARTED              RETURN_NOT_STARTED
#define EFI_ALREADY_STARTED          RETURN_ALREADY_STARTED
#define EFI_ABORTED                  RETURN_ABORTED
#define EFI_ICMP_ERROR               RETURN_ICMP_ERROR
#define EFI_TFTP_ERROR               RETURN_TFTP_ERROR
#define EFI_PROTOCOL_ERROR           RETURN_PROTOCOL_ERROR
#define EFI_INCOMPATIBLE_VERSION     RETURN_INCOMPATIBLE_VERSION
#define EFI_SECURITY_VIOLATION       RETURN_SECURITY_VIOLATION
#define EFI_CRC_ERROR                RETURN_CRC_ERROR
#define EFI_END_OF_MEDIA             RETURN_END_OF_MEDIA
#define EFI_END_OF_FILE              RETURN_END_OF_FILE
#define EFI_INVALID_LANGUAGE         RETURN_INVALID_LANGUAGE
#define EFI_COMPROMISED_DATA         RETURN_COMPROMISED_DATA
#define EFI_HTTP_ERROR               RETURN_HTTP_ERROR
#define EFI_WARN_UNKNOWN_GLYPH       RETURN_WARN_UNKNOWN_GLYPH
#define EFI_WARN_DELETE_FAILURE      RETURN_WARN_DELETE_FAILURE
#define EFI_WARN_WRITE_FAILURE       RETURN_WARN_WRITE_FAILURE
#define EFI_WARN_BUFFER_TOO_SMALL    RETURN_WARN_BUFFER_TOO_SMALL
#define EFI_WARN_STALE_DATA          RETURN_WARN_STALE_DATA
#define EFI_WARN_FILE_SYSTEM         RETURN_WARN_FILE_SYSTEM
#endif
typedef enum return_status{
	return_success               = RETURN_SUCCESS,
	return_load_error            = RETURN_LOAD_ERROR,
	return_invalid_parameter     = RETURN_INVALID_PARAMETER,
	return_unsupported           = RETURN_UNSUPPORTED,
	return_bad_buffer_size       = RETURN_BAD_BUFFER_SIZE,
	return_buffer_too_small      = RETURN_BUFFER_TOO_SMALL,
	return_not_ready             = RETURN_NOT_READY,
	return_device_error          = RETURN_DEVICE_ERROR,
	return_write_protected       = RETURN_WRITE_PROTECTED,
	return_out_of_resources      = RETURN_OUT_OF_RESOURCES,
	return_volume_corrupted      = RETURN_VOLUME_CORRUPTED,
	return_volume_full           = RETURN_VOLUME_FULL,
	return_no_media              = RETURN_NO_MEDIA,
	return_media_changed         = RETURN_MEDIA_CHANGED,
	return_not_found             = RETURN_NOT_FOUND,
	return_access_denied         = RETURN_ACCESS_DENIED,
	return_no_response           = RETURN_NO_RESPONSE,
	return_no_mapping            = RETURN_NO_MAPPING,
	return_timeout               = RETURN_TIMEOUT,
	return_not_started           = RETURN_NOT_STARTED,
	return_already_started       = RETURN_ALREADY_STARTED,
	return_aborted               = RETURN_ABORTED,
	return_icmp_error            = RETURN_ICMP_ERROR,
	return_tftp_error            = RETURN_TFTP_ERROR,
	return_protocol_error        = RETURN_PROTOCOL_ERROR,
	return_incompatible_version  = RETURN_INCOMPATIBLE_VERSION,
	return_security_violation    = RETURN_SECURITY_VIOLATION,
	return_crc_error             = RETURN_CRC_ERROR,
	return_end_of_media          = RETURN_END_OF_MEDIA,
	return_end_of_file           = RETURN_END_OF_FILE,
	return_invalid_language      = RETURN_INVALID_LANGUAGE,
	return_compromised_data      = RETURN_COMPROMISED_DATA,
	return_http_error            = RETURN_HTTP_ERROR,
	return_warn_unknown_glyph    = RETURN_WARN_UNKNOWN_GLYPH,
	return_warn_delete_failure   = RETURN_WARN_DELETE_FAILURE,
	return_warn_write_failure    = RETURN_WARN_WRITE_FAILURE,
	return_warn_buffer_too_small = RETURN_WARN_BUFFER_TOO_SMALL,
	return_warn_stale_data       = RETURN_WARN_STALE_DATA,
	return_warn_file_system      = RETURN_WARN_FILE_SYSTEM,
}return_status;
typedef enum efi_status{
	efi_success               = EFI_SUCCESS,
	efi_load_error            = EFI_LOAD_ERROR,
	efi_invalid_parameter     = EFI_INVALID_PARAMETER,
	efi_unsupported           = EFI_UNSUPPORTED,
	efi_bad_buffer_size       = EFI_BAD_BUFFER_SIZE,
	efi_buffer_too_small      = EFI_BUFFER_TOO_SMALL,
	efi_not_ready             = EFI_NOT_READY,
	efi_device_error          = EFI_DEVICE_ERROR,
	efi_write_protected       = EFI_WRITE_PROTECTED,
	efi_out_of_resources      = EFI_OUT_OF_RESOURCES,
	efi_volume_corrupted      = EFI_VOLUME_CORRUPTED,
	efi_volume_full           = EFI_VOLUME_FULL,
	efi_no_media              = EFI_NO_MEDIA,
	efi_media_changed         = EFI_MEDIA_CHANGED,
	efi_not_found             = EFI_NOT_FOUND,
	efi_access_denied         = EFI_ACCESS_DENIED,
	efi_no_response           = EFI_NO_RESPONSE,
	efi_no_mapping            = EFI_NO_MAPPING,
	efi_timeout               = EFI_TIMEOUT,
	efi_not_started           = EFI_NOT_STARTED,
	efi_already_started       = EFI_ALREADY_STARTED,
	efi_aborted               = EFI_ABORTED,
	efi_icmp_error            = EFI_ICMP_ERROR,
	efi_tftp_error            = EFI_TFTP_ERROR,
	efi_protocol_error        = EFI_PROTOCOL_ERROR,
	efi_incompatible_version  = EFI_INCOMPATIBLE_VERSION,
	efi_security_violation    = EFI_SECURITY_VIOLATION,
	efi_crc_error             = EFI_CRC_ERROR,
	efi_end_of_media          = EFI_END_OF_MEDIA,
	efi_end_of_file           = EFI_END_OF_FILE,
	efi_invalid_language      = EFI_INVALID_LANGUAGE,
	efi_compromised_data      = EFI_COMPROMISED_DATA,
	efi_http_error            = EFI_HTTP_ERROR,
	efi_warn_unknown_glyph    = EFI_WARN_UNKNOWN_GLYPH,
	efi_warn_delete_failure   = EFI_WARN_DELETE_FAILURE,
	efi_warn_write_failure    = EFI_WARN_WRITE_FAILURE,
	efi_warn_buffer_too_small = EFI_WARN_BUFFER_TOO_SMALL,
	efi_warn_stale_data       = EFI_WARN_STALE_DATA,
	efi_warn_file_system      = EFI_WARN_FILE_SYSTEM,
}efi_status;
static_assert(sizeof(efi_status)==sizeof(uintn_t),"efi_status size mismatch");
static_assert(sizeof(return_status)==sizeof(uintn_t),"return_status size mismatch");
typedef struct efi_device_path_protocol{
	uint8_t type;
	uint8_t sub_type;
	uint16_t length;
}efi_device_path_protocol;
#define EFI_BOOT_SERVICES_SIGNATURE   SIGNATURE_64 ('B','O','O','T','S','E','R','V')
#define EFI_BOOT_SERVICES_REVISION    EFI_SPECIFICATION_VERSION
#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL  0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL        0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL       0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER           0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE           0x00000020
typedef enum efi_timer_delay{
	timer_cancel   = 0x00,
	timer_periodic = 0x01,
	timer_relative = 0x02,
}efi_timer_delay;
#define HAVE_efi_timer_delay
typedef enum efi_interface_type{
	efi_native_interface = 0x00
}efi_interface_type;
#define HAVE_efi_interface_type
typedef enum efi_locate_search_type{
	search_all_handles        = 0x00,
	search_by_register_notify = 0x01,
	search_by_protocol        = 0x02,
}efi_locate_search_type;
#define HAVE_efi_locate_search_type
typedef struct efi_open_proto_info{
	efi_handle  agent;
	efi_handle  controller;
	uint32_t    attrs;
	uint32_t    count;
}efi_open_proto_info;
#define HAVE_efi_open_proto_info
typedef efiapi efi_status(*efi_allocate_pages)(
	efi_allocate_type type,
	efi_memory_type   memory_type,
	uintn_t           pages,
	efi_address       *memory
);
typedef efiapi efi_status(*efi_free_pages)(
	efi_address memory,
	uintn_t     pages
);
typedef efiapi efi_status(*efi_get_memory_map)(
	uintn_t               *map_size,
	efi_memory_descriptor *map,
	uintn_t               *key,
	uintn_t               *desc_size,
	uint32_t              *desc_ver
);
typedef efiapi efi_status(*efi_allocate_pool)(
	efi_memory_type type,
	uintn_t         size,
	void            **buffer
);
typedef efiapi efi_status(*efi_free_pool)(void*buffer);
typedef efiapi efi_status(*efi_connect_controller)(
	efi_handle               controller_handle,
	efi_handle               *driver_image_handle,
	efi_device_path_protocol *remaining_device_path,
	bool                     recursive
);
typedef efiapi efi_status(*efi_disconnect_controller)(
	efi_handle controller_handle,
	efi_handle driver_image_handle,
	efi_handle child_handle
);
typedef efiapi void(*efi_event_notify)(
	efi_event event,
	void      *context
);
typedef efiapi efi_status(*efi_create_event)(
	uint32_t         type,
	efi_tpl          tpl,
	efi_event_notify func,
	void             *context,
	efi_event        *event
);
typedef efiapi efi_status(*efi_create_event_ex)(
	uint32_t         type,
	efi_tpl          tpl,
	efi_event_notify func,
	const void       *context,
	const efi_guid   *group,
	efi_event        *event
);
typedef efiapi efi_status(*efi_set_timer)(
	efi_event       event,
	efi_timer_delay type,
	uint64_t        trigger_time
);
typedef efiapi efi_status(*efi_signal_event)(efi_event event);
typedef efiapi efi_status(*efi_wait_for_event)(
	uintn_t   events,
	efi_event *event,
	uintn_t   *index
);
typedef efiapi efi_status(*efi_close_event)(efi_event event);
typedef efiapi efi_status(*efi_check_event)(efi_event event);
typedef efiapi efi_tpl(*efi_raise_tpl)(efi_tpl new_tpl);
typedef efiapi void(*efi_restore_tpl)(efi_tpl old_tpl);
typedef efiapi efi_status(*efi_image_load)(
	bool                      boot_policy,
	efi_handle                parent_image_handle,
	efi_device_path_protocol  *device_path,
	void                      *source_buffer,
	uintn_t                   source_size,
	efi_handle                *image_handle
);
typedef efiapi efi_status(*efi_image_start)(
	efi_handle image_handle,
	uintn_t    *exit_data_size,
	char16     **exit_data
);
typedef efiapi efi_status(*efi_exit)(
	efi_handle image_handle,
	efi_status exit_status,
	uintn_t    exit_data_size,
	char16     *exit_data
);
typedef efiapi efi_status(*efi_image_unload)(efi_handle image_handle);
typedef efiapi efi_status(*efi_exit_boot_services)(
	efi_handle image_handle,
	uintn_t    map_key
);
typedef efiapi efi_status(*efi_get_next_monotonic_count)(uint64_t*count);
typedef efiapi efi_status(*efi_stall)(uintn_t microseconds);
typedef efiapi efi_status(*efi_set_watchdog_timer)(
	uintn_t  timeout,
	uint64_t watchdog_code,
	uintn_t  data_size,
	char16   *watchdog_data
);
typedef efiapi efi_status(*efi_calculate_crc32)(
	void     *data,
	uintn_t  size,
	uint32_t *crc32
);
typedef efiapi void(*efi_copy_mem)(
	void    *dst,
	void    *src,
	uintn_t len
);
typedef efiapi void(*efi_set_mem)(
	void    *buffer,
	uintn_t size,
	uint8_t value
);
typedef efiapi efi_status(*efi_install_protocol_interface)(
	efi_handle         *handle,
	const efi_guid     *protocol,
	efi_interface_type type,
	void               *interface
);
typedef efiapi efi_status(*efi_install_multiple_protocol_interfaces)(
	efi_handle*handle,
	...
);
typedef efiapi efi_status(*efi_reinstall_protocol_interface)(
	efi_handle       handle,
	const efi_guid   *protocol,
	void             *old_interface,
	void             *new_interface
);
typedef efiapi efi_status(*efi_uninstall_protocol_interface)(
	efi_handle       handle,
	const efi_guid   *protocol,
	void             *interface
);
typedef efiapi efi_status(*efi_uninstall_multiple_protocol_interfaces)(
	efi_handle handle,
	...
);
typedef efiapi efi_status(*efi_handle_protocol)(
	efi_handle handle,
	const efi_guid*protocol,
	void**interface
);
typedef efiapi efi_status(*efi_open_protocol)(
	efi_handle     handle,
	const efi_guid *protocol,
	void           **interface,
	efi_handle     agent_handle,
	efi_handle     controller_handle,
	uint32_t       attributes
);
typedef efiapi efi_status(*efi_close_protocol)(
	efi_handle     handle,
	const efi_guid *protocol,
	efi_handle     agent_handle,
	efi_handle     controller_handle
);
typedef efiapi efi_status(*efi_open_protocol_information)(
	efi_handle          handle,
	const efi_guid      *protocol,
	efi_open_proto_info **buffer,
	uintn_t             *count
);
typedef efiapi efi_status(*efi_protocols_per_handle)(
	efi_handle handle,
	efi_guid   ***protocol_buffer,
	uintn_t    *protocol_buffer_count
);
typedef efiapi efi_status(*efi_register_protocol_notify)(
	const efi_guid*protocol,
	efi_event event,
	void**registration
);
typedef efiapi efi_status(*efi_locate_handle)(
	efi_locate_search_type type,
	const efi_guid         *protocol,
	void                   *key,
	uintn_t                *size,
	efi_handle             *buffer
);
typedef efiapi efi_status(*efi_locate_device_path)(
	const efi_guid           *protocol,
	efi_device_path_protocol **device_path,
	efi_handle               *device
);
typedef efiapi efi_status(*efi_install_configuration_table)(
	const efi_guid*guid,
	void*table
);
typedef efiapi efi_status(*efi_locate_handle_buffer)(
	efi_locate_search_type type,
	const efi_guid         *protocol,
	void                   *key,
	uintn_t                *handles,
	efi_handle             **buffer
);
typedef efiapi efi_status(*efi_locate_protocol)(
	const efi_guid*protocol,
	void*registration,
	void**interface
);
typedef struct efi_boot_services{
	efi_table_header                           header;
	efi_raise_tpl                              raise_tpl;
	efi_restore_tpl                            restore_tpl;
	efi_allocate_pages                         alloc_pages;
	efi_free_pages                             free_pages;
	efi_get_memory_map                         get_mem_map;
	efi_allocate_pool                          alloc_pool;
	efi_free_pool                              free_pool;
	efi_create_event                           create_event;
	efi_set_timer                              set_timer;
	efi_wait_for_event                         wait_for_event;
	efi_signal_event                           signal_event;
	efi_close_event                            close_event;
	efi_check_event                            check_event;
	efi_install_protocol_interface             install_proto_interface;
	efi_reinstall_protocol_interface           reinstall_proto_interface;
	efi_uninstall_protocol_interface           uninstall_proto_interface;
	efi_handle_protocol                        handle_proto;
	void                                       *reserved;
	efi_register_protocol_notify               register_proto_notify;
	efi_locate_handle                          locate_handle;
	efi_locate_device_path                     locate_device_path;
	efi_install_configuration_table            install_cfg_table;
	efi_image_load                             load_image;
	efi_image_start                            start_image;
	efi_exit                                   exit;
	efi_image_unload                           unload_image;
	efi_exit_boot_services                     exit_boot_services;
	efi_get_next_monotonic_count               get_next_mono_count;
	efi_stall                                  stall;
	efi_set_watchdog_timer                     set_watchdog_timer;
	efi_connect_controller                     connect_controller;
	efi_disconnect_controller                  disconnect_controller;
	efi_open_protocol                          open_proto;
	efi_close_protocol                         close_proto;
	efi_open_protocol_information              open_proto_info;
	efi_protocols_per_handle                   proto_per_handle;
	efi_locate_handle_buffer                   locate_handle_buffer;
	efi_locate_protocol                        locate_proto;
	efi_install_multiple_protocol_interfaces   install_multiple_proto_interfaces;
	efi_uninstall_multiple_protocol_interfaces uninstall_multiple_proto_interfaces;
	efi_calculate_crc32                        calculate_crc32;
	efi_copy_mem                               copy_mem;
	efi_set_mem                                set_mem;
	efi_create_event_ex                        create_event_ex;
}efi_boot_services;
#define EFI_RUNTIME_SERVICES_SIGNATURE  SIGNATURE_64 ('R','U','N','T','S','E','R','V')
#define EFI_RUNTIME_SERVICES_REVISION   EFI_SPECIFICATION_VERSION
#define CAPSULE_FLAGS_PERSIST_ACROSS_RESET          0x00010000
#define CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE         0x00020000
#define CAPSULE_FLAGS_INITIATE_RESET                0x00040000
typedef enum efi_reset_type{
	RESET_COLD                 = 0x00,
	RESET_WARM                 = 0x01,
	RESET_SHUTDOWN             = 0x02,
	RESET_PLATFORM_SPECIFIC    = 0x03,
}efi_reset_type;
#define HAVE_efi_reset_type
typedef struct efi_time_capabilities{
	uint32_t    resolution;
	uint32_t    accuracy;
	bool        sets_to_zero;
}efi_time_capabilities;
#define HAVE_efi_time_capabilities
typedef struct efi_capsule_block_descriptor{
	uint64_t length;
	union {
		efi_address data_block;
		efi_address continuation_pointer;
	}unions;
}efi_capsule_block_descriptor;
#define HAVE_efi_capsule_block_descriptor
typedef struct efi_capsule_header{
	efi_guid guid;
	uint32_t header_size;
	uint32_t flags;
	uint32_t image_size;
}efi_capsule_header;
#define HAVE_efi_capsule_header
typedef struct efi_capsule_table{
	uint32_t capsule_array_number;
	void*    capsule_ptr[1];
}efi_capsule_table;
#define HAVE_efi_capsule_table
typedef efiapi efi_status(*efi_get_time)(
	efi_time              *time,
	efi_time_capabilities *caps
);
typedef efiapi efi_status(*efi_set_time)(efi_time*time);
typedef efiapi efi_status(*efi_get_wakeup_time)(
	bool     *enabled,
	bool     *pending,
	efi_time *time
);
typedef efiapi efi_status(*efi_set_wakeup_time)(
	bool     enable,
	efi_time *time
);
typedef efiapi efi_status(*efi_set_virtual_address_map)(
	uintn_t                map_size,
	uintn_t                desc_size,
	uint32_t               desc_ver,
	efi_memory_descriptor  *virt_map
);
typedef efiapi efi_status(*efi_convert_pointer)(
	uintn_t debug_disposition,
	void    **address
);
typedef efiapi efi_status(*efi_get_variable)(
	const char16   *variable_name,
	const efi_guid *vendor_guid,
	uint32_t       *attributes,
	uintn_t        *data_size,
	void           *data
);
typedef efiapi efi_status(*efi_get_next_variable_name)(
	uintn_t  *variable_name_size,
	char16   *variable_name,
	const efi_guid *vendor_guid
);
typedef efiapi efi_status(*efi_set_variable)(
	const char16   *variable_name,
	const efi_guid *vendor_guid,
	uint32_t       attributes,
	uintn_t        data_size,
	void           *data
);
typedef efiapi void(*efi_reset_system)(
	efi_reset_type type,
	efi_status     status,
	uintn_t        size,
	void           *data
);
typedef efiapi efi_status(*efi_get_next_high_mono_count)(uint32_t*count);
typedef efiapi efi_status(*efi_update_capsule)(
	efi_capsule_header**header_array,
	uintn_t count,
	efi_address scatter_gather_list
);
typedef efiapi efi_status(*efi_query_capsule_capabilities)(
	efi_capsule_header **header_array,
	uintn_t            count,
	uint64_t           *max_size,
	efi_reset_type     *reset_type
);
typedef efiapi efi_status(*efi_query_variable_info)(
	uint32_t attributes,
	uint64_t *max_var_storage,
	uint64_t *remain_var_storage,
	uint64_t *max_var_size
);
typedef struct efi_runtime_services{
	  efi_table_header                header;
	  efi_get_time                    get_time;
	  efi_set_time                    set_time;
	  efi_get_wakeup_time             get_wakeup_time;
	  efi_set_wakeup_time             set_wakeup_time;
	  efi_set_virtual_address_map     set_va_map;
	  efi_convert_pointer             convert_pointer;
	  efi_get_variable                get_var;
	  efi_get_next_variable_name      get_next_var_name;
	  efi_set_variable                set_var;
	  efi_get_next_high_mono_count    get_next_high_mono_count;
	  efi_reset_system                reset_system;
	  efi_update_capsule              update_capsule;
	  efi_query_capsule_capabilities  query_capsule_caps;
	  efi_query_variable_info         query_var_info;
}efi_runtime_services;
#ifndef CHAR_NULL
#define CHAR_NULL             0x0000
#define CHAR_BACKSPACE        0x0008
#define CHAR_TAB              0x0009
#define CHAR_LINEFEED         0x000A
#define CHAR_CARRIAGE_RETURN  0x000D
#define SCAN_NULL             0x0000
#define SCAN_UP               0x0001
#define SCAN_DOWN             0x0002
#define SCAN_RIGHT            0x0003
#define SCAN_LEFT             0x0004
#define SCAN_HOME             0x0005
#define SCAN_END              0x0006
#define SCAN_INSERT           0x0007
#define SCAN_DELETE           0x0008
#define SCAN_PAGE_UP          0x0009
#define SCAN_PAGE_DOWN        0x000A
#define SCAN_F1               0x000B
#define SCAN_F2               0x000C
#define SCAN_F3               0x000D
#define SCAN_F4               0x000E
#define SCAN_F5               0x000F
#define SCAN_F6               0x0010
#define SCAN_F7               0x0011
#define SCAN_F8               0x0012
#define SCAN_F9               0x0013
#define SCAN_F10              0x0014
#define SCAN_ESC              0x0017
#endif
typedef struct efi_simple_text_input_protocol efi_simple_text_input_protocol;
typedef struct efi_input_key{
	uint16_t scan_code;
	char16   unicode_char;
}efi_input_key;
typedef efiapi efi_status(*efi_input_reset)(
	efi_simple_text_input_protocol*proto,
	bool ext_verify
);
typedef efiapi efi_status(*efi_input_read_key)(
	efi_simple_text_input_protocol*proto,
	efi_input_key*key
);
struct efi_simple_text_input_protocol{
	efi_input_reset     reset;
	efi_input_read_key  read_key_stroke;
	efi_event           wait_for_key;
};
#ifndef EFI_TEXT_ATTR
#define BOXDRAW_HORIZONTAL                  0x2500
#define BOXDRAW_VERTICAL                    0x2502
#define BOXDRAW_DOWN_RIGHT                  0x250c
#define BOXDRAW_DOWN_LEFT                   0x2510
#define BOXDRAW_UP_RIGHT                    0x2514
#define BOXDRAW_UP_LEFT                     0x2518
#define BOXDRAW_VERTICAL_RIGHT              0x251c
#define BOXDRAW_VERTICAL_LEFT               0x2524
#define BOXDRAW_DOWN_HORIZONTAL             0x252c
#define BOXDRAW_UP_HORIZONTAL               0x2534
#define BOXDRAW_VERTICAL_HORIZONTAL         0x253c
#define BOXDRAW_DOUBLE_HORIZONTAL           0x2550
#define BOXDRAW_DOUBLE_VERTICAL             0x2551
#define BOXDRAW_DOWN_RIGHT_DOUBLE           0x2552
#define BOXDRAW_DOWN_DOUBLE_RIGHT           0x2553
#define BOXDRAW_DOUBLE_DOWN_RIGHT           0x2554
#define BOXDRAW_DOWN_LEFT_DOUBLE            0x2555
#define BOXDRAW_DOWN_DOUBLE_LEFT            0x2556
#define BOXDRAW_DOUBLE_DOWN_LEFT            0x2557
#define BOXDRAW_UP_RIGHT_DOUBLE             0x2558
#define BOXDRAW_UP_DOUBLE_RIGHT             0x2559
#define BOXDRAW_DOUBLE_UP_RIGHT             0x255a
#define BOXDRAW_UP_LEFT_DOUBLE              0x255b
#define BOXDRAW_UP_DOUBLE_LEFT              0x255c
#define BOXDRAW_DOUBLE_UP_LEFT              0x255d
#define BOXDRAW_VERTICAL_RIGHT_DOUBLE       0x255e
#define BOXDRAW_VERTICAL_DOUBLE_RIGHT       0x255f
#define BOXDRAW_DOUBLE_VERTICAL_RIGHT       0x2560
#define BOXDRAW_VERTICAL_LEFT_DOUBLE        0x2561
#define BOXDRAW_VERTICAL_DOUBLE_LEFT        0x2562
#define BOXDRAW_DOUBLE_VERTICAL_LEFT        0x2563
#define BOXDRAW_DOWN_HORIZONTAL_DOUBLE      0x2564
#define BOXDRAW_DOWN_DOUBLE_HORIZONTAL      0x2565
#define BOXDRAW_DOUBLE_DOWN_HORIZONTAL      0x2566
#define BOXDRAW_UP_HORIZONTAL_DOUBLE        0x2567
#define BOXDRAW_UP_DOUBLE_HORIZONTAL        0x2568
#define BOXDRAW_DOUBLE_UP_HORIZONTAL        0x2569
#define BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE  0x256a
#define BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL  0x256b
#define BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL  0x256c
#define BLOCKELEMENT_FULL_BLOCK             0x2588
#define BLOCKELEMENT_LIGHT_SHADE            0x2591
#define GEOMETRICSHAPE_UP_TRIANGLE          0x25b2
#define GEOMETRICSHAPE_RIGHT_TRIANGLE       0x25ba
#define GEOMETRICSHAPE_DOWN_TRIANGLE        0x25bc
#define GEOMETRICSHAPE_LEFT_TRIANGLE        0x25c4
#define ARROW_LEFT                          0x2190
#define ARROW_UP                            0x2191
#define ARROW_RIGHT                         0x2192
#define ARROW_DOWN                          0x2193
#define EFI_BLACK                           0x00
#define EFI_BLUE                            0x01
#define EFI_GREEN                           0x02
#define EFI_CYAN                            (EFI_BLUE|EFI_GREEN)
#define EFI_RED                             0x04
#define EFI_MAGENTA                         (EFI_BLUE|EFI_RED)
#define EFI_BROWN                           (EFI_GREEN|EFI_RED)
#define EFI_LIGHTGRAY                       (EFI_BLUE|EFI_GREEN|EFI_RED)
#define EFI_BRIGHT                          0x08
#define EFI_DARKGRAY                        (EFI_BLACK|EFI_BRIGHT)
#define EFI_LIGHTBLUE                       (EFI_BLUE|EFI_BRIGHT)
#define EFI_LIGHTGREEN                      (EFI_GREEN|EFI_BRIGHT)
#define EFI_LIGHTCYAN                       (EFI_CYAN|EFI_BRIGHT)
#define EFI_LIGHTRED                        (EFI_RED|EFI_BRIGHT)
#define EFI_LIGHTMAGENTA                    (EFI_MAGENTA|EFI_BRIGHT)
#define EFI_YELLOW                          (EFI_BROWN|EFI_BRIGHT)
#define EFI_WHITE                           (EFI_BLUE|EFI_GREEN|EFI_RED|EFI_BRIGHT)
#define EFI_TEXT_ATTR(fg,bg)                ((fg)|((bg)<<4))
#define EFI_BACKGROUND_BLACK                0x00
#define EFI_BACKGROUND_BLUE                 0x10
#define EFI_BACKGROUND_GREEN                0x20
#define EFI_BACKGROUND_CYAN                 (EFI_BACKGROUND_BLUE|EFI_BACKGROUND_GREEN)
#define EFI_BACKGROUND_RED                  0x40
#define EFI_BACKGROUND_MAGENTA              (EFI_BACKGROUND_BLUE|EFI_BACKGROUND_RED)
#define EFI_BACKGROUND_BROWN                (EFI_BACKGROUND_GREEN|EFI_BACKGROUND_RED)
#define EFI_BACKGROUND_LIGHTGRAY            (EFI_BACKGROUND_BLUE|EFI_BACKGROUND_GREEN|EFI_BACKGROUND_RED)
#define EFI_WIDE_ATTRIBUTE                  0x80
#endif

typedef struct efi_simple_text_output_protocol efi_simple_text_output_protocol;
typedef efiapi efi_status(*efi_text_reset)(
	efi_simple_text_output_protocol*proto,
	bool ext_verify
);
typedef efiapi efi_status(*efi_text_string)(
	efi_simple_text_output_protocol*proto,
	char16*string
);
typedef efiapi efi_status(*efi_text_test_string)(
	efi_simple_text_output_protocol*proto,
	char16*string
);
typedef efiapi efi_status(*efi_text_query_mode)(
	efi_simple_text_output_protocol*proto,
	uintn_t mode,
	uintn_t*cols,
	uintn_t*rows
);
typedef efiapi efi_status(*efi_text_set_mode)(
	efi_simple_text_output_protocol*proto,
	uintn_t mode
);
typedef efiapi efi_status(*efi_text_set_attribute)(
	efi_simple_text_output_protocol*proto,
	uintn_t attribute
);
typedef efiapi efi_status(*efi_text_clear_screen)(
	efi_simple_text_output_protocol*proto
);
typedef efiapi efi_status(*efi_text_set_cursor_position)(
	efi_simple_text_output_protocol*proto,
	uintn_t col,
	uintn_t row
);
typedef efiapi efi_status(*efi_text_enable_cursor)(
	efi_simple_text_output_protocol*proto,
	bool visible
);
typedef struct efi_simple_text_output_mode{
	int32_t max_mode;
	int32_t mode;
	union{
		int32_t num:32;
		struct{
			int16_t fg:4;
			int16_t bg:4;
			int32_t _r:24;
		}data;
	}attribute;
	int32_t cursor_col;
	int32_t cursor_row;
	bool cursor_visible;
}efi_simple_text_output_mode;
struct efi_simple_text_output_protocol{
	efi_text_reset                reset;
	efi_text_string               output_string;
	efi_text_test_string          test_string;
	efi_text_query_mode           query_mode;
	efi_text_set_mode             set_mode;
	efi_text_set_attribute        set_attribute;
	efi_text_clear_screen         clear_screen;
	efi_text_set_cursor_position  set_cursor_position;
	efi_text_enable_cursor        enable_cursor;
	efi_simple_text_output_mode   *mode;
};
#ifndef EFI_SYSTEM_TABLE_SIGNATURE
#define EFI_SYSTEM_TABLE_SIGNATURE      SIGNATURE_64 ('I','B','I',' ','S','Y','S','T')
#endif
#ifndef EFI_SYSTEM_TABLE_REVISION
#define EFI_SYSTEM_TABLE_REVISION       EFI_SPECIFICATION_VERSION
#endif
typedef struct efi_configuration_table{
	efi_guid guid;
	void     *table;
}efi_configuration_table;
typedef struct efi_system_table{
	efi_table_header                  header;
	char16                            *firmware_vendor;
	uint32_t                          firmware_revision;
	efi_handle                        con_stdin_handle;
	efi_simple_text_input_protocol    *con_stdin;
	efi_handle                        con_stdout_handle;
	efi_simple_text_output_protocol   *con_stdout;
	efi_handle                        con_stderr_handle;
	efi_simple_text_output_protocol   *con_stderr;
	efi_runtime_services              *runtime_services;
	efi_boot_services                 *boot_services;
	uintn_t                           entries;
	efi_configuration_table           *cfg_table;
}efi_system_table;
typedef efiapi efi_status(*efi_image_entry_point)(
	efi_handle image_handle,
	efi_system_table*system_table
);
typedef struct efi_graphics_output_protocol efi_graphics_output_protocol;
typedef struct efi_pixel_bitmask{
	uint32_t red_mask;
	uint32_t green_mask;
	uint32_t blue_mask;
	uint32_t reserved_mask;
}efi_pixel_bitmask;
typedef enum efi_graphics_pixel_format{
	PIXEL_RGBA8888,
	PIXEL_BGRA8888,
	PIXEL_BIT_MASK,
	PIXEL_BLT_ONLY,
	PIXEL_MAX
}efi_graphics_pixel_format;
typedef struct efi_graphics_output_mode_information{
	uint32_t                   version;
	uint32_t                   width;
	uint32_t                   height;
	efi_graphics_pixel_format  format;
	efi_pixel_bitmask          mask;
	uint32_t                   scan;
}efi_graphics_output_mode_information;
typedef efi_status(efiapi*efi_graphics_output_protocol_query_mode)(
	efi_graphics_output_protocol          *proto,
	uint32_t                              num,
	uintn_t                               *size,
	efi_graphics_output_mode_information  **info
);
typedef efi_status(efiapi*efi_graphics_output_protocol_set_mode)(
	efi_graphics_output_protocol *proto,
	uint32_t                     num
);
typedef struct efi_graphics_output_blt_pixel{
	uint8_t blue;
	uint8_t green;
	uint8_t red;
	uint8_t reserved;
}efi_graphics_output_blt_pixel;
typedef union efi_graphics_output_blt_pixel_union{
	efi_graphics_output_blt_pixel pixel;
	uint32_t                      raw;
}efi_graphics_output_blt_pixel_union;
typedef enum efi_graphics_output_blt_operation{
	efi_blt_video_fill,
	efi_blt_video_to_blt_buffer,
	efi_blt_buffer_to_video,
	efi_blt_video_to_video,
	efi_graphics_output_blt_operation_max
}efi_graphics_output_blt_operation;
typedef efi_status(efiapi*efi_graphics_output_protocol_blt)(
	efi_graphics_output_protocol      *proto,
	efi_graphics_output_blt_pixel     *buffer,
	efi_graphics_output_blt_operation operation,
	uintn_t                           src_x,
	uintn_t                           src_y,
	uintn_t                           dst_x,
	uintn_t                           dst_y,
	uintn_t                           width,
	uintn_t                           height,
	uintn_t                           delta
);
typedef struct efi_graphics_output_protocol_mode{
	uint32_t                             max_mode;
	uint32_t                             mode;
	efi_graphics_output_mode_information *info;
	uintn_t                              size;
	efi_address                          fb_base;
	uintn_t                              fb_size;
}efi_graphics_output_protocol_mode;
struct efi_graphics_output_protocol{
	efi_graphics_output_protocol_query_mode  query_mode;
	efi_graphics_output_protocol_set_mode    set_mode;
	efi_graphics_output_protocol_blt         blt;
	efi_graphics_output_protocol_mode        *mode;
};
typedef struct efi_simple_file_system_protocol efi_simple_file_system_protocol;
typedef struct efi_file_protocol efi_file_protocol;
typedef struct efi_file_protocol*efi_file_handle;
typedef efi_simple_file_system_protocol efi_file_io_interface;
typedef efi_status(efiapi*efi_simple_file_system_protocol_open_volume)(
	efi_simple_file_system_protocol*proto,
	efi_file_protocol**root
);
#ifndef EFI_FILE_IO_INTERFACE_REVISION
#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION1  0x00010000
#define EFI_FILE_IO_INTERFACE_REVISION EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION1
#endif
struct efi_simple_file_system_protocol{
	uint64_t revision;
	efi_simple_file_system_protocol_open_volume open_volume;
};
typedef efi_status(efiapi*efi_file_open)(
	efi_file_protocol*proto,
	efi_file_protocol**handle,
	char16*file,
	uint64_t mode,
	uint64_t attrs
);
#ifndef EFI_FILE_MODE_READ
#define EFI_FILE_MODE_READ    0x0000000000000001ULL
#define EFI_FILE_MODE_WRITE   0x0000000000000002ULL
#define EFI_FILE_MODE_CREATE  0x8000000000000000ULL
#define EFI_FILE_READ_ONLY    0x0000000000000001ULL
#define EFI_FILE_HIDDEN       0x0000000000000002ULL
#define EFI_FILE_SYSTEM       0x0000000000000004ULL
#define EFI_FILE_RESERVED     0x0000000000000008ULL
#define EFI_FILE_DIRECTORY    0x0000000000000010ULL
#define EFI_FILE_ARCHIVE      0x0000000000000020ULL
#define EFI_FILE_VALID_ATTR   0x0000000000000037ULL
#endif
typedef efi_status(efiapi*efi_file_close)(
	efi_file_protocol*proto
);
typedef efi_status(efiapi*efi_file_delete)(
	efi_file_protocol*proto
);
typedef efi_status(efiapi*efi_file_read)(
	efi_file_protocol*proto,
	uintn_t*size,
	void*buffer
);
typedef efi_status(efiapi*efi_file_write)(
	efi_file_protocol*proto,
	uintn_t*size,
	void*buffer
);
typedef efi_status(efiapi*efi_file_set_position)(
	efi_file_protocol*proto,
	uint64_t pos
);
typedef efi_status(efiapi*efi_file_get_position)(
	efi_file_protocol*proto,
	uint64_t*pos
);
typedef efi_status(efiapi*efi_file_get_info)(
	efi_file_protocol *proto,
	const efi_guid    *type,
	uintn_t           *size,
	void              *buffer
);
typedef efi_status(efiapi*efi_file_set_info)(
	efi_file_protocol *proto,
	const efi_guid    *type,
	uintn_t           size,
	void              *buffer
);
typedef efi_status(efiapi*efi_file_flush)(
	efi_file_protocol*proto
);
typedef struct efi_file_io_token{
	efi_event  event;
	efi_status status;
	uintn_t    size;
	void       *buffer;
}efi_file_io_token;
typedef efi_status(efiapi*efi_file_open_ex)(
	efi_file_protocol *proto,
	efi_file_protocol **handle,
	char16            *file,
	uint64_t          mode,
	uint64_t          attrs,
	efi_file_io_token *token
);
typedef efi_status(efiapi*efi_file_read_ex)(
	efi_file_protocol*proto,
	efi_file_io_token*token
);
typedef efi_status(efiapi*efi_file_write_ex)(
	efi_file_protocol*proto,
	efi_file_io_token*token
);
typedef efi_status(efiapi*efi_file_flush_ex)(
	efi_file_protocol*proto,
	efi_file_io_token*token
);
#ifndef EFI_FILE_REVISION
#define EFI_FILE_PROTOCOL_REVISION1       0x00010000
#define EFI_FILE_PROTOCOL_REVISION2       0x00020000
#define EFI_FILE_PROTOCOL_LATEST_REVISION EFI_FILE_PROTOCOL_REVISION2
#define EFI_FILE_REVISION EFI_FILE_PROTOCOL_REVISION
#endif
struct efi_file_protocol{
	uint64_t              revision;
	efi_file_open         open;
	efi_file_close        close;
	efi_file_delete       delete;
	efi_file_read         read;
	efi_file_write        write;
	efi_file_get_position get_pos;
	efi_file_set_position set_pos;
	efi_file_get_info     get_info;
	efi_file_set_info     set_info;
	efi_file_flush        flush;
	efi_file_open_ex      open_ex;
	efi_file_read_ex      read_ex;
	efi_file_write_ex     write_ex;
	efi_file_flush_ex     flush_ex;
};
typedef struct efi_file_info{
	uint64_t size;
	uint64_t file_size;
	uint64_t physical_size;
	efi_time ctime;
	efi_time atime;
	efi_time mtime;
	uint64_t attr;
	char16 file_name[0];
}efi_file_info;
typedef struct efi_file_system_info{
	uint64_t size;
	bool read_only;
	uint64_t vol_size;
	uint64_t free_space;
	uint32_t block_size;
	char16 vol_label[0];
}efi_file_system_info;
#ifndef EFI_LOADED_IMAGE_INFORMATION_REVISION
#define EFI_LOADED_IMAGE_PROTOCOL_REVISION1 0x1000
#define EFI_LOADED_IMAGE_INFORMATION_REVISION EFI_LOADED_IMAGE_PROTOCOL_REVISION1
#endif
typedef struct efi_loaded_image_protocol{
	uint32_t                 revision;
	efi_handle               parent_handle;
	efi_system_table         *system_table;
	efi_handle               device_handle;
	efi_device_path_protocol *file_path;
	void                     *reserved;
	uint32_t                 load_options_size;
	void                     *load_options;
	void                     *image_base;
	uint64_t                 image_size;
	efi_memory_type          image_code_type;
	efi_memory_type          image_data_type;
	efi_image_unload         unload;
}efi_loaded_image_protocol;
typedef efi_loaded_image_protocol efi_loaded_image;
typedef struct efi_disk_info_protocol efi_disk_info_protocol;
typedef efi_status(efiapi*efi_disk_info_inquiry)(
	efi_disk_info_protocol  *proto,
	void                    *data,
	uint32_t                *size
);
typedef efi_status(efiapi*efi_disk_info_identify)(
	efi_disk_info_protocol  *proto,
	void                    *data,
	uint32_t                *size
);
typedef efi_status(efiapi*efi_disk_info_sense_data)(
	efi_disk_info_protocol  *proto,
	void                    *data,
	uint32_t                *size,
	uint8_t                 *num
);
typedef efi_status(efiapi*efi_disk_info_which_ide)(
	efi_disk_info_protocol  *proto,
	uint32_t                *channel,
	uint32_t                *device
);
struct efi_disk_info_protocol{
	efi_guid                  interface;
	efi_disk_info_inquiry     inquiry;
	efi_disk_info_identify    identify;
	efi_disk_info_sense_data  sense_data;
	efi_disk_info_which_ide   which_ide;
};
typedef struct efi_disk_io2_protocol efi_disk_io2_protocol;
typedef struct efi_disk_io_protocol efi_disk_io_protocol;
typedef efi_disk_io_protocol efi_disk_io;
typedef struct efi_disk_io2_token{
	efi_event  event;
	efi_status status;
}efi_disk_io2_token;
typedef efi_status(efiapi*efi_disk_read)(
	efi_disk_io_protocol *proto,
	uint32_t             media_id,
	uint64_t             offset,
	uintn_t              size,
	void                 *buffer
);
typedef efi_status(efiapi*efi_disk_write)(
	efi_disk_io_protocol *proto,
	uint32_t             media_id,
	uint64_t             offset,
	uintn_t              size,
	void                 *buffer
);

typedef efi_status(efiapi*efi_disk_cancel_ex)(
	efi_disk_io2_protocol*proto
);
typedef efi_status(efiapi*efi_disk_read_ex)(
	efi_disk_io2_protocol *proto,
	uint32_t              media_id,
	uint64_t              offset,
	efi_disk_io2_token    *token,
	uintn_t               size,
	void                  *buffer
);
typedef efi_status(efiapi*efi_disk_write_ex)(
	efi_disk_io2_protocol *proto,
	uint32_t              media_id,
	uint64_t              offset,
	efi_disk_io2_token    *token,
	uintn_t               size,
	void                  *buffer
);
typedef efi_status(efiapi*efi_disk_flush_ex)(
	efi_disk_io2_protocol*proto,
	efi_disk_io2_token*token
);
#ifndef EFI_DISK_IO_INTERFACE_REVISION
#define EFI_DISK_IO_PROTOCOL_REVISION1 0x00010000
#define EFI_DISK_IO_INTERFACE_REVISION EFI_DISK_IO_PROTOCOL_REVISION1
#define EFI_DISK_IO2_PROTOCOL_REVISION 0x00020000
#endif
struct efi_disk_io_protocol{
	uint64_t        revision;
	efi_disk_read   read_disk;
	efi_disk_write  write_disk;
};
struct efi_disk_io2_protocol{
	uint64_t           revision;
	efi_disk_cancel_ex cancel;
	efi_disk_read_ex   read_disk_ex;
	efi_disk_write_ex  write_disk_ex;
	efi_disk_flush_ex  flush_disk_ex;
};
typedef struct efi_block_io_protocol efi_block_io_protocol;
typedef struct efi_block_io2_protocol efi_block_io2_protocol;
typedef efi_block_io_protocol efi_block_io;
typedef struct efi_block_io2_token{
	efi_event event;
	efi_status status;
}efi_block_io2_token;
typedef efi_status(efiapi*efi_block_reset)(
	efi_block_io_protocol*proto,
	bool ext_verify
);
typedef efi_status(efiapi*efi_block_read)(
	efi_block_io_protocol *proto,
	uint32_t              Media_Id,
	efi_lba               lba,
	uintn_t               size,
	void                  *buffer
);
typedef efi_status(efiapi*efi_block_write)(
	efi_block_io_protocol *proto,
	uint32_t              media_id,
	efi_lba               lba,
	uintn_t               size,
	void                  *buffer
);
typedef efi_status(efiapi*efi_block_flush)(
	efi_block_io_protocol  *proto
);
typedef struct efi_block_io_media{
	uint32_t media_id;
	bool     removable_media;
	bool     media_present;
	bool     logical_partition;
	bool     read_only;
	bool     write_caching;
	uint32_t block_size;
	uint32_t io_align;
	efi_lba  last_block;
	efi_lba  lowest_aligned_lba;
	uint32_t logical_blocks_per_physical_block;
	uint32_t optimal_transfer_length_granularity;
}efi_block_io_media;
#ifndef EFI_BLOCK_IO_INTERFACE_REVISION
#define EFI_BLOCK_IO_PROTOCOL_REVISION1 0x00010000
#define EFI_BLOCK_IO_PROTOCOL_REVISION2 0x00020001
#define EFI_BLOCK_IO_PROTOCOL_REVISION3 0x0002001F
#define EFI_BLOCK_IO_INTERFACE_REVISION EFI_BLOCK_IO_PROTOCOL_REVISION1
#endif
typedef efi_status(efiapi*efi_block_reset_ex)(
	efi_block_io2_protocol*proto,
	bool ext_verify
);
typedef efi_status(efiapi*efi_block_read_ex)(
	efi_block_io2_protocol *proto,
	uint32_t               media_id,
	efi_lba                lba,
	efi_block_io2_token    *token,
	uintn_t                size,
	void                   *buffer
);
typedef efi_status(efiapi*efi_block_write_ex)(
	efi_block_io2_protocol *proto,
	uint32_t               media_id,
	efi_lba                lba,
	efi_block_io2_token    *token,
	uintn_t                size,
	void                   *buffer
);
typedef efi_status(efiapi*efi_block_flush_ex)(
	efi_block_io2_protocol*proto,
	efi_block_io2_token*token
);
struct efi_block_io_protocol{
	uint64_t            revision;
	efi_block_io_media  *media;
	efi_block_reset     reset;
	efi_block_read      read_blocks;
	efi_block_write     write_blocks;
	efi_block_flush     flush_blocks;
};
struct efi_block_io2_protocol{
	efi_block_io_media *media;
	efi_block_reset_ex reset;
	efi_block_read_ex  read_blocks_ex;
	efi_block_write_ex write_blocks_ex;
	efi_block_flush_ex flush_blocks_ex;
};
typedef struct efi_timestamp_protocol efi_timestamp_protocol;
typedef struct efi_timestamp_properties{
	uint64_t frequency;
	uint64_t end_value;
}efi_timestamp_properties;
typedef uint64_t(efiapi*timestamp_get)(void);
typedef efi_status(efiapi*timestamp_get_properties)(efi_timestamp_properties*prop);
struct efi_timestamp_protocol{
	timestamp_get            get_timestamp;
	timestamp_get_properties get_properties;
};
extern efi_guid gEfiTimestampProtocolGuid;
extern efi_guid gEfiFileInfoGuid;
extern efi_guid gEfiFileSystemInfoGuid;
extern efi_guid gEfiFileSystemVolumeLabelInfoIdGuid;
extern efi_guid gEfiSimpleTextOutProtocolGuid;
extern efi_guid gEfiEventMemoryMapChangeGuid;
extern efi_guid gEfiEventVirtualAddressChangeGuid;
extern efi_guid gEfiEventExitBootServicesGuid;
extern efi_guid gEfiSimpleTextInProtocolGuid;
extern efi_guid gEfiGraphicsOutputProtocolGuid;
extern efi_guid gEfiSimpleFileSystemProtocolGuid;
extern efi_guid gEfiLoadedImageProtocolGuid;
extern efi_guid gEfiLoadedImageDevicePathProtocolGuid;
extern efi_guid gEfiBlockIoProtocolGuid;
extern efi_guid gEfiBlockIo2ProtocolGuid;
extern efi_guid gEfiDiskIoProtocolGuid;
extern efi_guid gEfiDiskIo2ProtocolGuid;
extern efi_guid gEfiDiskInfoProtocolGuid;
extern efi_guid gEfiDiskInfoIdeInterfaceGuid;
extern efi_guid gEfiDiskInfoScsiInterfaceGuid;
extern efi_guid gEfiDiskInfoUsbInterfaceGuid;
extern efi_guid gEfiDiskInfoAhciInterfaceGuid;
extern efi_guid gEfiDiskInfoNvmeInterfaceGuid;
extern efi_guid gEfiDiskInfoUfsInterfaceGuid;
extern efi_guid gEfiDiskInfoSdMmcInterfaceGuid;
extern efi_guid gEfiGlobalVariableGuid;
extern efi_guid gEfiDevicePathProtocolGuid;
#endif
