#ifndef DISK_H
#define DISK_H
#include"efi.h"
typedef struct ata_identify_data{
	uint16_t config;
	uint16_t obsolete_1;
	uint16_t specific_config;
	uint16_t obsolete_3;
	uint16_t retired_4_5[2];
	uint16_t obsolete_6;
	uint16_t cfa_reserved_7_8[2];
	uint16_t retired_9;
	char serial_no[20];
	uint16_t retired_20_21[2];
	uint16_t obsolete_22;
	char firmware_ver[8];
	char model_name[40];
	uint16_t multi_sector_cmd_max_sct_cnt;
	uint16_t trusted_computing_support;
	uint16_t capabilities_49;
	uint16_t capabilities_50;
	uint16_t obsolete_51_52[2];
	uint16_t field_validity;
	uint16_t obsolete_54_58[5];
	uint16_t multi_sector_setting;
	uint16_t user_addressable_sectors_lo;
	uint16_t user_addressable_sectors_hi;
	uint16_t obsolete_62;
	uint16_t multi_word_dma_mode;
	uint16_t advanced_pio_modes;
	uint16_t min_multi_word_dma_cycle_time;
	uint16_t rec_multi_word_dma_cycle_time;
	uint16_t min_pio_cycle_time_without_flow_control;
	uint16_t min_pio_cycle_time_with_flow_control;
	uint16_t additional_supported;
	uint16_t reserved_70;
	uint16_t reserved_71_74[4];
	uint16_t queue_depth;
	uint16_t serial_ata_capabilities;
	uint16_t reserved_77;
	uint16_t serial_ata_features_supported;
	uint16_t serial_ata_features_enabled;
	uint16_t major_version_no;
	uint16_t minor_version_no;
	uint16_t cmd_set_supported_82;
	uint16_t cmd_set_supported_83;
	uint16_t cmd_set_feature_extn;
	uint16_t cmd_set_feature_enb_85;
	uint16_t cmd_set_feature_enb_86;
	uint16_t cmd_set_feature_default;
	uint16_t ultra_dma_mode;
	uint16_t time_for_security_erase_unit;
	uint16_t time_for_enhanced_security_erase_unit;
	uint16_t advanced_power_management_level;
	uint16_t master_password_identifier;
	uint16_t hardware_configuration_test_result;
	uint16_t obsolete_94;
	uint16_t stream_minimum_request_size;
	uint16_t streaming_transfer_time_for_dma;
	uint16_t streaming_access_latency_for_dma_and_pio;
	uint16_t streaming_performance_granularity[2];
	uint16_t maximum_lba_for_48bit_addressing[4];
	uint16_t streaming_transfer_time_for_pio;
	uint16_t max_no_of_512byte_blocks_per_data_set_cmd;
	uint16_t phy_logic_sector_support;
	uint16_t interseek_delay_for_iso7779;
	uint16_t world_wide_name[4];
	uint16_t reserved_for_128bit_wwn_112_115[4];
	uint16_t reserved_for_technical_report;
	uint16_t logic_sector_size_lo;
	uint16_t logic_sector_size_hi;
	uint16_t features_and_cmd_sets_supported_ext;
	uint16_t features_and_cmd_sets_enabled_ext;
	uint16_t reserved_121_126[6];
	uint16_t obsolete_127;
	uint16_t security_status;
	uint16_t vendor_specific_129_159[31];
	uint16_t cfa_power_mode;
	uint16_t reserved_for_compactflash_161_167[7];
	uint16_t device_nominal_form_factor;
	uint16_t is_data_set_cmd_supported;
	char additional_product_identifier[8];
	uint16_t reserved_174_175[2];
	char media_serial_number[60];
	uint16_t sct_cmd_transport;
	uint16_t reserved_207_208[2];
	uint16_t alignment_logic_in_phy_blocks;
	uint16_t write_read_verify_sector_count_mode3[2];
	uint16_t verify_sector_count_mode2[2];
	uint16_t nv_cache_capabilities;
	uint16_t nv_cache_size_in_logical_block_lsw;
	uint16_t nv_cache_size_in_logical_block_msw;
	uint16_t nominal_media_rotation_rate;
	uint16_t reserved_218;
	uint16_t nv_cache_options;
	uint16_t write_read_verify_mode;
	uint16_t reserved_221;
	uint16_t transport_major_revision_number;
	uint16_t transport_minor_revision_number;
	uint16_t reserved_224_229[6];
	uint64_t extended_no_of_addressable_sectors;
	uint16_t min_number_per_download_microcode_mode3;
	uint16_t max_number_per_download_microcode_mode3;
	uint16_t reserved_236_254[19];
	uint16_t integrity_word;
}ata_identify_data;
typedef struct scsi_inquiry_data{
	uint8_t peripheral_type:5;
	uint8_t peripheral_qualifier:3;
	uint8_t device_type_modifier:7;
	uint8_t rmb:1;
	uint8_t version;
	uint8_t response_data_format;
	uint8_t addnl_length;
	uint8_t reserved0[3];
	char vendor_id[8];
	char product_id[16];
	uint8_t reserved1[64];
}scsi_inquiry_data;
typedef struct usb_boot_inquiry_data{
	uint8_t periph_device_type;
	uint8_t removable;
	uint8_t reserved0[2];
	uint8_t add_len;
	uint8_t reserved1[3];
	uint8_t vendor_id[8];
	uint8_t product_id[16];
	uint8_t product_revision[4];
}usb_boot_inquiry_data;
typedef struct nvme_psdescriptor{
	uint16_t mp;
	uint8_t rsvd1;
	uint8_t mps:1;
	uint8_t nops:1;
	uint8_t rsvd2:6;
	uint32_t enlat;
	uint32_t exlat;
	uint8_t rrt:5;
	uint8_t rsvd3:3;
	uint8_t rrl:5;
	uint8_t rsvd4:3;
	uint8_t rwt:5;
	uint8_t rsvd5:3;
	uint8_t rwl:5;
	uint8_t rsvd6:3;
	uint8_t rsvd7[16];
}nvme_psdescriptor;
typedef struct nvme_sanicap{
	uint32_t ces:1;
	uint32_t bes:1;
	uint32_t ows:1;
	uint32_t rsvd1:26;
	uint32_t ndi:1;
	uint32_t nodmmas:2;
}nvme_sanicap;
typedef struct nvme_admin_controller_data{
	uint16_t vid;
	uint16_t ssvid;
	uint8_t sn[20];
	uint8_t mn[40];
	uint8_t fr[8];
	uint8_t rab;
	uint8_t ieee_oui[3];
	uint8_t cmic;
	uint8_t mdts;
	uint8_t cntlid[2];
	uint32_t ver;
	uint32_t rtd3r;
	uint32_t rtd3e;
	uint32_t oaes;
	uint32_t ctratt;
	uint16_t rrls;
	uint8_t rsvd1[9];
	uint8_t cntrltype;
	uint8_t fguid[16];
	uint16_t crdt1;
	uint16_t crdt2;
	uint16_t crdt3;
	uint8_t rsvd2[106];
	uint8_t rsvd3[16];
	uint16_t oacs;
	uint8_t acl;
	uint8_t aerl;
	uint8_t frmw;
	uint8_t lpa;
	uint8_t elpe;
	uint8_t npss;
	uint8_t avscc;
	uint8_t apsta;
	uint16_t wctemp;
	uint16_t cctemp;
	uint16_t mtfa;
	uint32_t hmpre;
	uint32_t hmmin;
	uint8_t tnvmcap[16];
	uint8_t unvmcap[16];
	uint32_t rpmbs;
	uint16_t edstt;
	uint8_t dsto;
	uint8_t fwug;
	uint16_t kas;
	uint16_t hctma;
	uint16_t mntmt;
	uint16_t mxtmt;
	nvme_sanicap sanicap;
	uint32_t hmminds;
	uint16_t hmmaxd;
	uint16_t nsetidmax;
	uint16_t endgidmax;
	uint8_t anatt;
	uint8_t anacap;
	uint32_t anagrpmax;
	uint32_t nanagrpid;
	uint32_t pels;
	uint8_t rsvd4[156];
	uint8_t sqes;
	uint8_t cqes;
	uint16_t maxcmd;
	uint32_t nn;
	uint16_t oncs;
	uint16_t fuses;
	uint8_t fna;
	uint8_t vwc;
	uint16_t awun;
	uint16_t awupf;
	uint8_t nvscc;
	uint8_t nwpc;
	uint16_t acwu;
	uint16_t rsvd5;
	uint32_t sgls;
	uint32_t mnan;
	uint8_t rsvd6[224];
	uint8_t subnqn[256];
	uint8_t rsvd7[768];
	uint8_t rsvd8[256];
	nvme_psdescriptor ps_descriptor[32];
	uint8_t vendor_data[1024];
}nvme_admin_controller_data;
typedef struct nvme_lbaformat{
	uint16_t ms;
	uint8_t lbads;
	uint8_t rp:2;
	#define LBAF_RP_BEST      00b
	#define LBAF_RP_BETTER    01b
	#define LBAF_RP_GOOD      10b
	#define LBAF_RP_DEGRADED  11b
	uint8_t rsvd1:6;
}nvme_lbaformat;
typedef struct nvme_admin_namespace_data{
	uint64_t nsze;
	uint64_t ncap;
	uint64_t nuse;
	uint8_t nsfeat;
	uint8_t nlbaf;
	uint8_t flbas;
	uint8_t mc;
	uint8_t dpc;
	uint8_t dps;
	uint8_t nmic;
	uint8_t rescap;
	uint8_t rsvd1[88];
	uint64_t eui64;
	nvme_lbaformat lba_format[16];
	uint8_t rsvd2[192];
	uint8_t vendor_data[3712];
}nvme_admin_namespace_data;
typedef struct nvme_cdw0{
	uint32_t opcode:8;
	uint32_t fused_op:2;
	uint32_t reserved:22;
}nvme_cdw0;
typedef struct efi_nvme_cmd{
	nvme_cdw0 cdw0;
	uint8_t flags;
	uint32_t nsid;
	uint32_t cdw2;
	uint32_t cdw3;
	uint32_t cdw10;
	uint32_t cdw11;
	uint32_t cdw12;
	uint32_t cdw13;
	uint32_t cdw14;
	uint32_t cdw15;
}efi_nvme_cmd;
typedef struct efi_nvme_completion{
	uint32_t dw0;
	uint32_t dw1;
	uint32_t dw2;
	uint32_t dw3;
}efi_nvme_completion;
typedef struct efi_nvme_passthru_cmd_pkt{
	uint64_t            cmd_timeout;
	void                *transfer_buffer;
	uint32_t            transfer_length;
	void                *metadata_buffer;
	uint32_t            metadata_length;
	uint8_t             queue_type;
	efi_nvme_cmd        *nvme_cmd;
	efi_nvme_completion *nvme_completion;
}efi_nvme_passthru_cmd_pkt;
typedef struct efi_nvme_passthru_protocol efi_nvme_passthru_protocol;
typedef struct efi_nvme_passthru_mode{
	uint32_t attributes;
	uint32_t io_align;
	uint32_t nvme_version;
}efi_nvme_passthru_mode;
#define EFI_NVME_PASS_THRU_ATTRIBUTES_PHYSICAL     0x0001
#define EFI_NVME_PASS_THRU_ATTRIBUTES_LOGICAL      0x0002
#define EFI_NVME_PASS_THRU_ATTRIBUTES_NONBLOCKIO   0x0004
#define EFI_NVME_PASS_THRU_ATTRIBUTES_CMD_SET_NVM  0x0008
#define NORMAL_CMD        0x00
#define FUSED_FIRST_CMD   0x01
#define FUSED_SECOND_CMD  0x02
#define CDW2_VALID        0x01
#define CDW3_VALID        0x02
#define CDW10_VALID       0x04
#define CDW11_VALID       0x08
#define CDW12_VALID       0x10
#define CDW13_VALID       0x20
#define CDW14_VALID       0x40
#define CDW15_VALID       0x80
#define NVME_ADMIN_QUEUE  0x00
#define NVME_IO_QUEUE     0x01
typedef efi_status(efiapi*efi_nvme_passthru_passthru)(
	efi_nvme_passthru_protocol*this,
	uint32_t nid,
	efi_nvme_passthru_cmd_pkt*pkt,
	efi_event event
);
typedef efi_status(efiapi*efi_nvme_passthru_get_next_namespace)(
	efi_nvme_passthru_protocol*this,
	uint32_t*nid
);
typedef efi_status(efiapi*efi_nvme_passthru_build_device_path)(
	efi_nvme_passthru_protocol*this,
	uint32_t nid,
	efi_device_path_protocol**dp
);
typedef efi_status(efiapi*efi_nvme_passthru_get_namespace)(
	efi_nvme_passthru_protocol*this,
	efi_device_path_protocol*dp,
	uint32_t*nid
);
struct efi_nvme_passthru_protocol{
	efi_nvme_passthru_mode                  *mode;
	efi_nvme_passthru_passthru              passthru;
	efi_nvme_passthru_get_next_namespace    get_next_namespace;
	efi_nvme_passthru_build_device_path     build_device_path;
	efi_nvme_passthru_get_namespace         get_namespace;
};
extern efi_guid gEfiNvmExpressPassThruProtocolGuid;
#endif
