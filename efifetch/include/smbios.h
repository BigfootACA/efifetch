#ifndef SMBIOS_H
#define SMBIOS_H
#include"efi.h"
typedef uint8_t smbios_type;
typedef uint16_t smbios_handle;
#ifndef SMBIOS_MAGIC
#define SMBIOS_MAGIC "_SM_"
#endif
#ifndef SMBIOS3_MAGIC
#define SMBIOS3_MAGIC "_SM3_"
#endif
typedef struct smbios_table2_entry_point{
	uint8_t  magic[4];
	uint8_t  entry_point_structure_checksum;
	uint8_t  entry_point_length;
	uint8_t  major_version;
	uint8_t  minor_version;
	uint16_t max_structure_size;
	uint8_t  entry_point_revision;
	uint8_t  formatted_area[5];
	uint8_t  intermediate_magic[5];
	uint8_t  intermediate_checksum;
	uint16_t table_length;
	uint32_t table_address;
	uint16_t smbios_structures_cnt;
	uint8_t  smbios_bcd_revision;
}__packed smbios_table2_entry_point;
static_assert(sizeof(smbios_table2_entry_point)==0x1F,"smbios table 2 entry point size mismatch");
typedef struct smbios_table3_entry_point{
	uint8_t  magic[5];
	uint8_t  entry_point_structure_checksum;
	uint8_t  entry_point_length;
	uint8_t  major_version;
	uint8_t  minor_version;
	uint8_t  doc_rev;
	uint8_t  entry_point_revision;
	uint8_t  reserved;
	uint32_t table_max_size;
	uint64_t table_address;
}__packed smbios_table3_entry_point;
static_assert(sizeof(smbios_table3_entry_point)==0x18,"smbios table 3 entry point size mismatch");
typedef struct smbios_structure{
	smbios_type    type;
	uint8_t        length;
	smbios_handle  handle;
}__packed smbios_structure;
typedef uint8_t smbios_table_string;
typedef struct misc_bios_flags{
	uint32_t reserved                             :2;
	uint32_t unknown                              :1;
	uint32_t bios_flags_not_supported             :1;
	uint32_t isa_is_supported                     :1;
	uint32_t mca_is_supported                     :1;
	uint32_t eisa_is_supported                    :1;
	uint32_t pci_is_supported                     :1;
	uint32_t pcmcia_is_supported                  :1;
	uint32_t plug_and_play_is_supported           :1;
	uint32_t apm_is_supported                     :1;
	uint32_t bios_is_upgradable                   :1;
	uint32_t bios_shadowing_allowed               :1;
	uint32_t vl_vesa_is_supported                 :1;
	uint32_t escd_support_is_available            :1;
	uint32_t boot_from_cd_is_supported            :1;
	uint32_t selectable_boot_is_supported         :1;
	uint32_t rom_bios_is_socketed                 :1;
	uint32_t boot_from_pcmcia_is_supported        :1;
	uint32_t edd_specification_is_supported       :1;
	uint32_t japanese_nec_floppy_is_supported     :1;
	uint32_t japanese_toshiba_floppy_is_supported :1;
	uint32_t floppy525_360_is_supported           :1;
	uint32_t floppy525_12_is_supported            :1;
	uint32_t floppy35_720_is_supported            :1;
	uint32_t floppy35_288_is_supported            :1;
	uint32_t print_screen_is_supported            :1;
	uint32_t keyboard8042_is_supported            :1;
	uint32_t serial_is_supported                  :1;
	uint32_t printer_is_supported                 :1;
	uint32_t cga_mono_is_supported                :1;
	uint32_t nec_pc98                             :1;
	uint32_t reserved_for_vendor                  :32;
}__packed misc_bios_flags;
typedef struct mbce_bios_reserved{
	uint8_t acpi_is_supported                 :1;
	uint8_t usb_legacy_is_supported           :1;
	uint8_t agp_is_supported                  :1;
	uint8_t i2o_boot_is_supported             :1;
	uint8_t ls120_boot_is_supported           :1;
	uint8_t atapi_zip_drive_boot_is_supported :1;
	uint8_t boot1394_is_supported             :1;
	uint8_t smart_battery_is_supported        :1;
}__packed mbce_bios_reserved;
typedef struct mbce_system_reserved{
	uint8_t bios_boot_spec_is_supported            :1;
	uint8_t function_key_network_boot_is_supported :1;
	uint8_t target_content_distribution_enabled    :1;
	uint8_t uefi_specification_supported           :1;
	uint8_t virtual_machine_supported              :1;
	uint8_t manufacturing_mode_supported           :1;
	uint8_t manufacturing_mode_enabled             :1;
	uint8_t extension_byte2_reserved               :1;
}__packed mbce_system_reserved;
typedef struct misc_bios_flags_extension{
	mbce_bios_reserved   bios_reserved;
	mbce_system_reserved system_reserved;
}__packed misc_bios_flags_extension;
typedef struct ext_bios_rom_size{
	uint16_t size:14;
	uint16_t unit:2;
}__packed ext_bios_rom_size;
typedef struct smbios_table_type0{
	smbios_structure    header;
	smbios_table_string vendor;
	smbios_table_string bios_version;
	uint16_t            bios_segment;
	smbios_table_string bios_release_date;
	uint8_t             bios_size;
	misc_bios_flags     bios_flags;
	uint8_t             bios_flags_ext[2];
	uint8_t             system_bios_major;
	uint8_t             system_bios_minor;
	uint8_t             ec_fw_major;
	uint8_t             ec_fw_minor;
	ext_bios_rom_size ext_bios_size;
}__packed smbios_table_type0;
typedef enum misc_system_wakeup_type{
	wakeup_reserved          = 0x00,
	wakeup_other             = 0x01,
	wakeup_unknown           = 0x02,
	wakeup_apm_timer         = 0x03,
	wakeup_modem_ring        = 0x04,
	wakeup_lan_remote        = 0x05,
	wakeup_power_switch      = 0x06,
	wakeup_pci_pme           = 0x07,
	wakeup_ac_power_restored = 0x08
}__packed misc_system_wakeup_type;
typedef struct smbios_table_type1{
	smbios_structure    header;
	smbios_table_string manufacturer;
	smbios_table_string product;
	smbios_table_string version;
	smbios_table_string serial_number;
	guid                uuid;
	uint8_t             wakeup;
	smbios_table_string sku;
	smbios_table_string family;
}__packed smbios_table_type1;
typedef struct base_board_feature_flags{
	uint8_t motherboard            :1;
	uint8_t requires_daughter_card :1;
	uint8_t removable              :1;
	uint8_t replaceable            :1;
	uint8_t hot_swappable          :1;
	uint8_t reserved               :3;
}__packed base_board_feature_flags;
typedef enum base_board_type{
	board_unknown                  = 0x1,
	board_other                    = 0x2,
	board_server_blade             = 0x3,
	board_connectivity_switch      = 0x4,
	board_system_management_module = 0x5,
	board_processor_module         = 0x6,
	board_io_module                = 0x7,
	board_memory_module            = 0x8,
	board_daughter_board           = 0x9,
	board_mother_board             = 0xa,
	board_processor_memory_module  = 0xb,
	board_processor_io_module      = 0xc,
	board_interconnect_board       = 0xd,
}__packed base_board_type;
typedef struct smbios_table_type2{
	smbios_structure         header;
	smbios_table_string      manufacturer;
	smbios_table_string      product;
	smbios_table_string      version;
	smbios_table_string      serial_number;
	smbios_table_string      asset_tag;
	base_board_feature_flags feature_flag;
	smbios_table_string      location;
	smbios_handle            chassis_handle;
	uint8_t                  board_type;
	uint8_t                  contained_object_handles_cnt;
	smbios_handle            contained_object_handles[1];
}__packed smbios_table_type2;
typedef enum misc_chassis_type{
	chassis_other                 = 0x01,
	chassis_unknown               = 0x02,
	chassis_desk_top              = 0x03,
	chassis_low_profile_desktop   = 0x04,
	chassis_pizza_box             = 0x05,
	chassis_mini_tower            = 0x06,
	chassis_tower                 = 0x07,
	chassis_portable              = 0x08,
	chassis_lap_top               = 0x09,
	chassis_notebook              = 0x0a,
	chassis_hand_held             = 0x0b,
	chassis_docking_station       = 0x0c,
	chassis_all_in_one            = 0x0d,
	chassis_sub_notebook          = 0x0e,
	chassis_space_saving          = 0x0f,
	chassis_lunch_box             = 0x10,
	chassis_main_server_chassis   = 0x11,
	chassis_expansion_chassis     = 0x12,
	chassis_sub_chassis           = 0x13,
	chassis_bus_expansion_chassis = 0x14,
	chassis_peripheral_chassis    = 0x15,
	chassis_raid_chassis          = 0x16,
	chassis_rack_mount_chassis    = 0x17,
	chassis_sealed_case_pc        = 0x18,
	chassis_multi_system_chassis  = 0x19,
	chassis_compact_pci           = 0x1a,
	chassis_advanced_tca          = 0x1b,
	chassis_blade                 = 0x1c,
	chassis_blade_enclosure       = 0x1d,
	chassis_tablet                = 0x1e,
	chassis_convertible           = 0x1f,
	chassis_detachable            = 0x20,
	chassis_io_t_gateway          = 0x21,
	chassis_embedded_pc           = 0x22,
	chassis_mini_pc               = 0x23,
	chassis_stick_pc              = 0x24,
}__packed misc_chassis_type;
typedef enum misc_chassis_state{
	state_other           = 0x01,
	state_unknown         = 0x02,
	state_safe            = 0x03,
	state_warning         = 0x04,
	state_critical        = 0x05,
	state_non_recoverable = 0x06
}__packed misc_chassis_state;
typedef enum misc_chassis_security_state{
	security_other                  = 0x01,
	security_unknown                = 0x02,
	security_none                   = 0x03,
	security_extintf_locked_out     = 0x04,
	security_extintf_locked_enabled = 0x05
}__packed misc_chassis_security_state;
typedef struct contained_element{
	uint8_t type;
	uint8_t min;
	uint8_t max;
}__packed contained_element;
typedef struct smbios_table_type3{
	smbios_structure     header;
	smbios_table_string  manufacturer;
	uint8_t              type;
	smbios_table_string  version;
	smbios_table_string  serial_number;
	smbios_table_string  asset_tag;
	uint8_t              bootup_state;
	uint8_t              power_supply_state;
	uint8_t              thermal_state;
	uint8_t              security_status;
	uint8_t              oem_defined[4];
	uint8_t              height;
	uint8_t              numberof_power_cords;
	uint8_t              contained_element_count;
	uint8_t              contained_element_record_length;
	contained_element    contained_elements[1];
}__packed smbios_table_type3;
typedef enum processor_type{
	processor_other   = 0x01,
	processor_unknown = 0x02,
	central_processor = 0x03,
	math_processor    = 0x04,
	dsp_processor     = 0x05,
	video_processor   = 0x06
}__packed processor_type;
typedef enum processor_family_data{
	family_other                                  = 0x01,
	family_unknown                                = 0x02,
	family_8086                                   = 0x03,
	family_80286                                  = 0x04,
	family_intel386                               = 0x05,
	family_intel486                               = 0x06,
	family_8087                                   = 0x07,
	family_80287                                  = 0x08,
	family_80387                                  = 0x09,
	family_80487                                  = 0x0a,
	family_pentium                                = 0x0b,
	family_pentium_pro                            = 0x0c,
	family_pentium_ii                             = 0x0d,
	family_pentium_mmx                            = 0x0e,
	family_celeron                                = 0x0f,
	family_pentium_ii_xeon                        = 0x10,
	family_pentium_iii                            = 0x11,
	family_m1                                     = 0x12,
	family_m2                                     = 0x13,
	family_intel_celeron_m                        = 0x14,
	family_intel_pentium4_ht                      = 0x15,
	family_intel                                  = 0x16,
	family_amd_duron                              = 0x18,
	family_k5                                     = 0x19,
	family_k6                                     = 0x1a,
	family_k6_2                                   = 0x1b,
	family_k6_3                                   = 0x1c,
	family_amd_athlon                             = 0x1d,
	family_amd29000                               = 0x1e,
	family_k6_2_plus                              = 0x1f,
	family_power_pc                               = 0x20,
	family_power_pc601                            = 0x21,
	family_power_pc603                            = 0x22,
	family_power_pc603_plus                       = 0x23,
	family_power_pc604                            = 0x24,
	family_power_pc620                            = 0x25,
	family_power_p_cx704                          = 0x26,
	family_power_pc750                            = 0x27,
	family_intel_core_duo                         = 0x28,
	family_intel_core_duo_mobile                  = 0x29,
	family_intel_core_solo_mobile                 = 0x2a,
	family_intel_atom                             = 0x2b,
	family_intel_core_m                           = 0x2c,
	family_intel_corem3                           = 0x2d,
	family_intel_corem5                           = 0x2e,
	family_intel_corem7                           = 0x2f,
	family_alpha                                  = 0x30,
	family_alpha21064                             = 0x31,
	family_alpha21066                             = 0x32,
	family_alpha21164                             = 0x33,
	family_alpha21164pc                           = 0x34,
	family_alpha21164a                            = 0x35,
	family_alpha21264                             = 0x36,
	family_alpha21364                             = 0x37,
	family_amd_turion_ii_ultra_dual_core_mobile_m = 0x38,
	family_amd_turion_ii_dual_core_mobile_m       = 0x39,
	family_amd_athlon_ii_dual_core_m              = 0x3a,
	family_amd_opteron6100_series                 = 0x3b,
	family_amd_opteron4100_series                 = 0x3c,
	family_amd_opteron6200_series                 = 0x3d,
	family_amd_opteron4200_series                 = 0x3e,
	family_amd_fx_series                          = 0x3f,
	family_mips                                   = 0x40,
	family_mipsr4000                              = 0x41,
	family_mipsr4200                              = 0x42,
	family_mipsr4400                              = 0x43,
	family_mipsr4600                              = 0x44,
	family_mipsr10000                             = 0x45,
	family_amd_c_series                           = 0x46,
	family_amd_e_series                           = 0x47,
	family_amd_a_series                           = 0x48,
	family_amd_g_series                           = 0x49,
	family_amd_z_series                           = 0x4a,
	family_amd_r_series                           = 0x4b,
	family_amd_opteron4300                        = 0x4c,
	family_amd_opteron6300                        = 0x4d,
	family_amd_opteron3300                        = 0x4e,
	family_amd_fire_pro_series                    = 0x4f,
	family_sparc                                  = 0x50,
	family_68040                                  = 0x60,
	family_68xxx                                  = 0x61,
	family_68000                                  = 0x62,
	family_68010                                  = 0x63,
	family_68020                                  = 0x64,
	family_68030                                  = 0x65,
	family_amd_athlon_x4_quad_core                = 0x66,
	family_amd_opteron_x1000_series               = 0x67,
	family_amd_opteron_x2000_series               = 0x68,
	family_amd_opteron_a_series                   = 0x69,
	family_amd_opteron_x3000_series               = 0x6a,
	family_amd_zen                                = 0x6b,
	family_hobbit                                 = 0x70,
	family_crusoe_tm5000                          = 0x78,
	family_crusoe_tm3000                          = 0x79,
	family_efficeon_tm8000                        = 0x7a,
	family_weitek                                 = 0x80,
	family_itanium                                = 0x82,
	family_amd_athlon64                           = 0x83,
	family_amd_opteron                            = 0x84,
	family_amd_sempron                            = 0x85,
	family_amd_turion64_mobile                    = 0x86,
	family_dual_core_amd_opteron                  = 0x87,
	family_amd_athlon64x2_dual_core               = 0x88,
	family_amd_turion64x2_mobile                  = 0x89,
	family_quad_core_amd_opteron                  = 0x8a,
	family_third_generation_amd_opteron           = 0x8b,
	family_amd_phenom_fx_quad_core                = 0x8c,
	family_amd_phenom_x4_quad_core                = 0x8d,
	family_amd_phenom_x2_dual_core                = 0x8e,
	family_amd_athlon_x2_dual_core                = 0x8f,
	family_parisc                                 = 0x90,
	family_pa_risc8500                            = 0x91,
	family_pa_risc8000                            = 0x92,
	family_pa_risc7300lc                          = 0x93,
	family_pa_risc7200                            = 0x94,
	family_pa_risc7100lc                          = 0x95,
	family_pa_risc7100                            = 0x96,
	family_v30                                    = 0xa0,
	family_quad_core_intel_xeon3200_series        = 0xa1,
	family_dual_core_intel_xeon3000_series        = 0xa2,
	family_quad_core_intel_xeon5300_series        = 0xa3,
	family_dual_core_intel_xeon5100_series        = 0xa4,
	family_dual_core_intel_xeon5000_series        = 0xa5,
	family_dual_core_intel_xeon_lv                = 0xa6,
	family_dual_core_intel_xeon_ulv               = 0xa7,
	family_dual_core_intel_xeon7100_series        = 0xa8,
	family_quad_core_intel_xeon5400_series        = 0xa9,
	family_quad_core_intel_xeon                   = 0xaa,
	family_dual_core_intel_xeon5200_series        = 0xab,
	family_dual_core_intel_xeon7200_series        = 0xac,
	family_quad_core_intel_xeon7300_series        = 0xad,
	family_quad_core_intel_xeon7400_series        = 0xae,
	family_multi_core_intel_xeon7400_series       = 0xaf,
	family_pentium_iii_xeon                       = 0xb0,
	family_pentium_iii_speed_step                 = 0xb1,
	family_pentium4                               = 0xb2,
	family_intel_xeon                             = 0xb3,
	family_as400                                  = 0xb4,
	family_intel_xeon_mp                          = 0xb5,
	family_amd_athlon_xp                          = 0xb6,
	family_amd_athlon_mp                          = 0xb7,
	family_intel_itanium2                         = 0xb8,
	family_intel_pentium_m                        = 0xb9,
	family_intel_celeron_d                        = 0xba,
	family_intel_pentium_d                        = 0xbb,
	family_intel_pentium_ex                       = 0xbc,
	family_intel_core_solo                        = 0xbd,
	family_reserved                               = 0xbe,
	family_intel_core2                            = 0xbf,
	family_intel_core2_solo                       = 0xc0,
	family_intel_core2_extreme                    = 0xc1,
	family_intel_core2_quad                       = 0xc2,
	family_intel_core2_extreme_mobile             = 0xc3,
	family_intel_core2_duo_mobile                 = 0xc4,
	family_intel_core2_solo_mobile                = 0xc5,
	family_intel_core_i7                          = 0xc6,
	family_dual_core_intel_celeron                = 0xc7,
	family_ibm390                                 = 0xc8,
	family_g4                                     = 0xc9,
	family_g5                                     = 0xca,
	family_g6                                     = 0xcb,
	family_z_architecture                         = 0xcc,
	family_intel_core_i5                          = 0xcd,
	family_intel_core_i3                          = 0xce,
	family_intel_core_i9                          = 0xcf,
	family_intel_xeon_d                           = 0xd0,
	family_via_c7m                                = 0xd2,
	family_via_c7d                                = 0xd3,
	family_via_c7                                 = 0xd4,
	family_via_eden                               = 0xd5,
	family_multi_core_intel_xeon                  = 0xd6,
	family_dual_core_intel_xeon3_series           = 0xd7,
	family_quad_core_intel_xeon3_series           = 0xd8,
	family_via_nano                               = 0xd9,
	family_dual_core_intel_xeon5_series           = 0xda,
	family_quad_core_intel_xeon5_series           = 0xdb,
	family_dual_core_intel_xeon7_series           = 0xdd,
	family_quad_core_intel_xeon7_series           = 0xde,
	family_multi_core_intel_xeon7_series          = 0xdf,
	family_multi_core_intel_xeon3400_series       = 0xe0,
	family_amd_opteron3000_series                 = 0xe4,
	family_amd_sempron_ii                         = 0xe5,
	family_embedded_amd_opteron_quad_core         = 0xe6,
	family_amd_phenom_triple_core                 = 0xe7,
	family_amd_turion_ultra_dual_core_mobile      = 0xe8,
	family_amd_turion_dual_core_mobile            = 0xe9,
	family_amd_athlon_dual_core                   = 0xea,
	family_amd_sempron_si                         = 0xeb,
	family_amd_phenom_ii                          = 0xec,
	family_amd_athlon_ii                          = 0xed,
	family_six_core_amd_opteron                   = 0xee,
	family_amd_sempron_m                          = 0xef,
	family_i860                                   = 0xfa,
	family_i960                                   = 0xfb,
	family_indicator_family2                      = 0xfe,
	family_reserved1                              = 0xff
}__packed processor_family_data;
typedef enum processor_family2_data{
	family_ar_mv7                = 0x0100,
	family_ar_mv8                = 0x0101,
	family_ar_mv9                = 0x0102,
	family_sh3                   = 0x0104,
	family_sh4                   = 0x0105,
	family_arm                   = 0x0118,
	family_strong_arm            = 0x0119,
	family_6x86                  = 0x012c,
	family_media_gx              = 0x012d,
	family_mii                   = 0x012e,
	family_win_chip              = 0x0140,
	family_dsp                   = 0x015e,
	family_video_processor       = 0x01f4,
	family_riscv_rv32            = 0x0200,
	family_risc_vrv64            = 0x0201,
	family_risc_vrv128           = 0x0202,
	family_loong_arch            = 0x0258,
	family_loongson1             = 0x0259,
	family_loongson2             = 0x025a,
	family_loongson3             = 0x025b,
	family_loongson2k            = 0x025c,
	family_loongson3a            = 0x025d,
	family_loongson3b            = 0x025e,
	family_loongson3c            = 0x025f,
	family_loongson3d            = 0x0260,
	family_loongson3e            = 0x0261,
	family_dual_core_loongson2k  = 0x0262,
	family_quad_core_loongson3a  = 0x026c,
	family_multi_core_loongson3a = 0x026d,
	family_quad_core_loongson3b  = 0x026e,
	family_multi_core_loongson3b = 0x026f,
	family_multi_core_loongson3c = 0x0270,
	family_multi_core_loongson3d = 0x0271,
	family_intel_core3           = 0x0300,
	family_intel_core5           = 0x0301,
	family_intel_core7           = 0x0302,
	family_intel_core9           = 0x0303,
	family_intel_core_ultra3     = 0x0304,
	family_intel_core_ultra5     = 0x0305,
	family_intel_core_ultra7     = 0x0306,
	family_intel_core_ultra9     = 0x0307
}__packed processor_family2_data;
typedef struct processor_voltage{
	uint8_t volt_cap_5v          :1;
	uint8_t volt_cap_3v3         :1;
	uint8_t volt_cap_2v9         :1;
	uint8_t volt_cap_reserved    :1;
	uint8_t volt_reserved        :3;
	uint8_t volt_indicate_legacy :1;
}__packed processor_voltage;
typedef enum processor_upgrade{
	upgrade_other            = 0x01,
	upgrade_unknown          = 0x02,
	upgrade_daughter_board   = 0x03,
	upgrade_zif_socket       = 0x04,
	upgrade_piggy_back       = 0x05,
	upgrade_none             = 0x06,
	upgrade_lif_socket       = 0x07,
	upgrade_slot1            = 0x08,
	upgrade_slot2            = 0x09,
	upgrade370_pin_socket    = 0x0a,
	upgrade_slot_a           = 0x0b,
	upgrade_slot_m           = 0x0c,
	upgrade_socket423        = 0x0d,
	upgrade_socket_a         = 0x0e,
	upgrade_socket478        = 0x0f,
	upgrade_socket754        = 0x10,
	upgrade_socket940        = 0x11,
	upgrade_socket939        = 0x12,
	upgrade_socketm_pga604   = 0x13,
	upgrade_socket_lga771    = 0x14,
	upgrade_socket_lga775    = 0x15,
	upgrade_socket_s1        = 0x16,
	upgrade_am2              = 0x17,
	upgrade_f1207            = 0x18,
	upgrade_socket_lga1366   = 0x19,
	upgrade_socket_g34       = 0x1a,
	upgrade_socket_am3       = 0x1b,
	upgrade_socket_c32       = 0x1c,
	upgrade_socket_lga1156   = 0x1d,
	upgrade_socket_lga1567   = 0x1e,
	upgrade_socket_pga988a   = 0x1f,
	upgrade_socket_bga1288   = 0x20,
	upgrade_socketr_pga988b  = 0x21,
	upgrade_socket_bga1023   = 0x22,
	upgrade_socket_bga1224   = 0x23,
	upgrade_socket_lga1155   = 0x24,
	upgrade_socket_lga1356   = 0x25,
	upgrade_socket_lga2011   = 0x26,
	upgrade_socket_fs1       = 0x27,
	upgrade_socket_fs2       = 0x28,
	upgrade_socket_fm1       = 0x29,
	upgrade_socket_fm2       = 0x2a,
	upgrade_socket_lga2011_3 = 0x2b,
	upgrade_socket_lga1356_3 = 0x2c,
	upgrade_socket_lga1150   = 0x2d,
	upgrade_socket_bga1168   = 0x2e,
	upgrade_socket_bga1234   = 0x2f,
	upgrade_socket_bga1364   = 0x30,
	upgrade_socket_am4       = 0x31,
	upgrade_socket_lga1151   = 0x32,
	upgrade_socket_bga1356   = 0x33,
	upgrade_socket_bga1440   = 0x34,
	upgrade_socket_bga1515   = 0x35,
	upgrade_socket_lga3647_1 = 0x36,
	upgrade_socket_sp3       = 0x37,
	upgrade_socket_sp3r2     = 0x38,
	upgrade_socket_lga2066   = 0x39,
	upgrade_socket_bga1392   = 0x3a,
	upgrade_socket_bga1510   = 0x3b,
	upgrade_socket_bga1528   = 0x3c,
	upgrade_socket_lga4189   = 0x3d,
	upgrade_socket_lga1200   = 0x3e,
	upgrade_socket_lga4677   = 0x3f,
	upgrade_socket_lga1700   = 0x40,
	upgrade_socket_bga1744   = 0x41,
	upgrade_socket_bga1781   = 0x42,
	upgrade_socket_bga1211   = 0x43,
	upgrade_socket_bga2422   = 0x44,
	upgrade_socket_lga1211   = 0x45,
	upgrade_socket_lga2422   = 0x46,
	upgrade_socket_lga5773   = 0x47,
	upgrade_socket_bga5773   = 0x48,
	upgrade_socket_am5       = 0x49,
	upgrade_socket_sp5       = 0x4a,
	upgrade_socket_sp6       = 0x4b,
	upgrade_socket_bga883    = 0x4c,
	upgrade_socket_bga1190   = 0x4d,
	upgrade_socket_bga4129   = 0x4e,
	upgrade_socket_lga4710   = 0x4f,
	upgrade_socket_lga7529   = 0x50,
	upgrade_socket_bga1964   = 0x51,
	upgrade_socket_bga1792   = 0x52,
	upgrade_socket_bga2049   = 0x53,
	upgrade_socket_bga2551   = 0x54,
	upgrade_socket_lga1851   = 0x55,
	upgrade_socket_bga2114   = 0x56,
	upgrade_socket_bga2833   = 0x57,
	upgrade_invalid          = 0xff
}__packed processor_upgrade;
typedef struct processor_signature{
	uint32_t stepping  :4;
	uint32_t model      :4;
	uint32_t family     :4;
	uint32_t type       :2;
	uint32_t reserved1  :2;
	uint32_t x_model    :4;
	uint32_t x_family   :8;
	uint32_t reserved2  :4;
}__packed processor_signature;
typedef struct processor_feature_flags{
	uint32_t fpu       :1;
	uint32_t vme       :1;
	uint32_t de        :1;
	uint32_t pse       :1;
	uint32_t tsc       :1;
	uint32_t msr       :1;
	uint32_t pae       :1;
	uint32_t mce       :1;
	uint32_t cx8       :1;
	uint32_t apic      :1;
	uint32_t reserved1 :1;
	uint32_t sep       :1;
	uint32_t mtrr      :1;
	uint32_t pge       :1;
	uint32_t mca       :1;
	uint32_t cmov      :1;
	uint32_t pat       :1;
	uint32_t pse36     :1;
	uint32_t psn       :1;
	uint32_t clfsh     :1;
	uint32_t reserved2 :1;
	uint32_t ds        :1;
	uint32_t acpi      :1;
	uint32_t mmx       :1;
	uint32_t fxsr      :1;
	uint32_t sse       :1;
	uint32_t sse2      :1;
	uint32_t ss        :1;
	uint32_t reserved3 :1;
	uint32_t tm        :1;
	uint32_t reserved4 :2;
}__packed processor_feature_flags;
typedef struct processor_flags{
	uint16_t reserved1       :1;
	uint16_t unknown         :1;
	uint16_t cpu64bit        :1;
	uint16_t multi_core      :1;
	uint16_t hw_thread       :1;
	uint16_t execute_prot    :1;
	uint16_t enhanced_virt   :1;
	uint16_t power_perf_ctrl :1;
	uint16_t cpu128bit       :1;
	uint16_t arm64_soc_id    :1;
	uint16_t reserved2       :6;
}__packed processor_flags;
typedef union processor_status_data{
	struct {
		uint8_t cpu_status       :3;
		uint8_t reserved1        :3;
		uint8_t socket_populated :1;
		uint8_t reserved2        :1;
	}__packed bits;
	uint8_t data;
}__packed processor_status_data;
typedef struct processor_id_data{
	processor_signature        signature;
	processor_feature_flags    feature_flags;
}__packed processor_id_data;
typedef struct smbios_table_type4{
	smbios_structure     header;
	smbios_table_string  socket;
	uint8_t              processor_type;
	uint8_t              family;
	smbios_table_string  processor_manufacturer;
	processor_id_data    processor_id;
	smbios_table_string  processor_version;
	processor_voltage    voltage;
	uint16_t             external_clock;
	uint16_t             max_speed;
	uint16_t             current_speed;
	uint8_t              status;
	uint8_t              processor_upgrade;
	smbios_handle        l1_cache_handle;
	smbios_handle        l2_cache_handle;
	smbios_handle        l3_cache_handle;
	smbios_table_string  serial_number;
	smbios_table_string  asset_tag;
	smbios_table_string  part_number;
	uint8_t              core_count;
	uint8_t              enabled_core_count;
	uint8_t              thread_count;
	uint16_t             processor_flags;
	uint16_t             family_2;
	uint16_t             core_count2;
	uint16_t             enabled_core_count2;
	uint16_t             thread_count2;
	uint16_t             thread_enabled;
	smbios_table_string  socket_type;
}__packed smbios_table_type4;
typedef enum memory_error_detect_method{
	detect_other   = 0x01,
	detect_unknown = 0x02,
	detect_none    = 0x03,
	detect_parity  = 0x04,
	detect_32ecc   = 0x05,
	detect_64ecc   = 0x06,
	detect_128ecc  = 0x07,
	detect_crc     = 0x08
}__packed memory_error_detect_method;
typedef struct memory_error_corr_cap{
	uint8_t other           :1;
	uint8_t unknown         :1;
	uint8_t none            :1;
	uint8_t single_bit_ecc  :1;
	uint8_t double_bit_ecc  :1;
	uint8_t error_scrubbing :1;
	uint8_t reserved        :2;
}__packed memory_error_corr_cap;
typedef enum memory_support_interleave_type{
	interleave_other       = 0x01,
	interleave_unknown     = 0x02,
	interleave_one_way     = 0x03,
	interleave_two_way     = 0x04,
	interleave_four_way    = 0x05,
	interleave_eight_way   = 0x06,
	interleave_sixteen_way = 0x07
}__packed memory_support_interleave_type;
typedef struct {
	uint16_t other      :1;
	uint16_t unknown    :1;
	uint16_t seventy_ns :1;
	uint16_t sixty_ns   :1;
	uint16_t fifty_ns   :1;
	uint16_t reserved   :11;
}__packed memory_speed_typememory_speed_type;
typedef struct memory_current_typememory_current_type{
	uint16_t other           :1;
	uint16_t unknown         :1;
	uint16_t standard        :1;
	uint16_t fast_page_mode  :1;
	uint16_t edo             :1;
	uint16_t parity          :1;
	uint16_t ecc             :1;
	uint16_t simm            :1;
	uint16_t dimm            :1;
	uint16_t burst_edo       :1;
	uint16_t sdram           :1;
	uint16_t reserved        :5;
}__packed memory_current_typememory_current_type;
typedef struct memory_installed_enabled_size{
	uint8_t installed_or_enabled_size :7;
	uint8_t single_or_double_bank     :1;
}__packed memory_installed_enabled_size;
typedef struct cache_sram_type{
	uint16_t other         :1;
	uint16_t unknown       :1;
	uint16_t non_burst      :1;
	uint16_t burst         :1;
	uint16_t pipeline_burst :1;
	uint16_t synchronous   :1;
	uint16_t asynchronous  :1;
	uint16_t reserved      :9;
}__packed cache_sram_type;
typedef enum cache_error_type{
	cache_error_other     = 0x01,
	cache_error_unknown   = 0x02,
	cache_error_none      = 0x03,
	cache_error_parity    = 0x04,
	cache_error_single_bit = 0x05,
	cache_error_multi_bit  = 0x06
}__packed cache_error_type;
typedef enum cache_type{
	cache_other       = 0x01,
	cache_unknown     = 0x02,
	cache_instruction = 0x03,
	cache_data        = 0x04,
	cache_unified     = 0x05
}__packed cache_type;
typedef enum cache_associativity_data{
	assoc_other   = 0x01,
	assoc_unknown = 0x02,
	assoc_direct  = 0x03,
	assoc_2way    = 0x04,
	assoc_4way    = 0x05,
	assoc_fully   = 0x06,
	assoc_8way    = 0x07,
	assoc_16way   = 0x08,
	assoc_12way   = 0x09,
	assoc_24way   = 0x0a,
	assoc_32way   = 0x0b,
	assoc_48way   = 0x0c,
	assoc_64way   = 0x0d,
	assoc_20way   = 0x0e
}__packed cache_associativity_data;
typedef struct smbios_table_type7{
	smbios_structure    header;
	smbios_table_string socket_designation;
	uint16_t            cache_configuration;
	uint16_t            max_cache_size;
	uint16_t            installed_size;
	cache_sram_type     supported_sram_type;
	cache_sram_type     current_sram_type;
	uint8_t             cache_speed;
	uint8_t             error_correction_type;
	uint8_t             system_cache_type;
	uint8_t             associativity;
	uint32_t            max_cache_size2;
	uint32_t            installed_size2;
}__packed smbios_table_type7;
typedef enum misc_port_connector_type{
	conn_none                   = 0x00,
	conn_centronics             = 0x01,
	conn_mini_centronics        = 0x02,
	conn_proprietary            = 0x03,
	conn_db25_male              = 0x04,
	conn_db25_female            = 0x05,
	conn_db15_male              = 0x06,
	conn_db15_female            = 0x07,
	conn_db9_male               = 0x08,
	conn_db9_female             = 0x09,
	conn_rj11                   = 0x0a,
	conn_rj45                   = 0x0b,
	conn_50_pin_mini_scsi       = 0x0c,
	conn_mini_din               = 0x0d,
	conn_micro_din              = 0x0e,
	conn_ps2                    = 0x0f,
	conn_infrared               = 0x10,
	conn_hp_hil                 = 0x11,
	conn_usb                    = 0x12,
	conn_ssa_scsi               = 0x13,
	conn_circular_din8_male     = 0x14,
	conn_circular_din8_female   = 0x15,
	conn_onboard_ide            = 0x16,
	conn_onboard_floppy         = 0x17,
	conn_9_pin_dual_inline      = 0x18,
	conn_25_pin_dual_inline     = 0x19,
	conn_50_pin_dual_inline     = 0x1a,
	conn_68_pin_dual_inline     = 0x1b,
	conn_onboard_sound_input    = 0x1c,
	conn_mini_centronics_type14 = 0x1d,
	conn_mini_centronics_type26 = 0x1e,
	conn_head_phone_mini_jack   = 0x1f,
	conn_bnc                    = 0x20,
	conn_1394                   = 0x21,
	conn_sas_sata               = 0x22,
	conn_usb_type_c             = 0x23,
	conn_pc98                   = 0xa0,
	conn_pc98_hireso            = 0xa1,
	conn_pch98                  = 0xa2,
	conn_pc98_note              = 0xa3,
	conn_pc98_full              = 0xa4,
	conn_other                  = 0xff
}__packed misc_port_connector_type;
typedef enum misc_port_type{
	port_none                      = 0x00,
	port_parallel_xt_at_compatible = 0x01,
	port_parallel_port_ps2         = 0x02,
	port_parallel_port_ecp         = 0x03,
	port_parallel_port_epp         = 0x04,
	port_parallel_port_ecp_epp     = 0x05,
	port_serial_xt_at_compatible   = 0x06,
	port_serial16450_compatible    = 0x07,
	port_serial16550_compatible    = 0x08,
	port_serial16550a_compatible   = 0x09,
	port_scsi                      = 0x0a,
	port_midi                      = 0x0b,
	port_joy_stick                 = 0x0c,
	port_keyboard                  = 0x0d,
	port_mouse                     = 0x0e,
	port_ssa_scsi                  = 0x0f,
	port_usb                       = 0x10,
	port_fire_wire                 = 0x11,
	port_pcmcia_type_i             = 0x12,
	port_pcmcia_type_ii            = 0x13,
	port_pcmcia_type_iii           = 0x14,
	port_card_bus                  = 0x15,
	port_access_bus_port           = 0x16,
	port_scsi_ii                   = 0x17,
	port_scsi_wide                 = 0x18,
	port_pc98                      = 0x19,
	port_pc98_hireso               = 0x1a,
	port_pch98                     = 0x1b,
	port_video_port                = 0x1c,
	port_audio_port                = 0x1d,
	port_modem_port                = 0x1e,
	port_network_port              = 0x1f,
	port_sata                      = 0x20,
	port_sas                       = 0x21,
	port_mfdp                      = 0x22,
	port_thunderbolt               = 0x23,
	port_8251_compatible           = 0xa0,
	port_8251_fifo_compatible      = 0xa1,
	port_other                     = 0xff,
}__packed misc_port_type;
typedef struct smbios_table_type8{
	smbios_structure    header;
	smbios_table_string intref;
	uint8_t             intconn_type;
	smbios_table_string extref;
	uint8_t             extconn_type;
	uint8_t             port_type;
}__packed smbios_table_type8;
typedef enum misc_slot_type{
	slot_other                 = 0x01,
	slot_unknown               = 0x02,
	slot_isa                   = 0x03,
	slot_mca                   = 0x04,
	slot_eisa                  = 0x05,
	slot_pci                   = 0x06,
	slot_pcmcia                = 0x07,
	slot_vl_vesa               = 0x08,
	slot_proprietary           = 0x09,
	slot_processor_card_slot   = 0x0a,
	slot_prop_mem_card_slot    = 0x0b,
	slot_io_riser_card_slot    = 0x0c,
	slot_nu_bus                = 0x0d,
	slot_pci66_mhz_capable     = 0x0e,
	slot_agp                   = 0x0f,
	slot_apg2x                 = 0x10,
	slot_agp4x                 = 0x11,
	slot_pci_x                 = 0x12,
	slot_agp8x                 = 0x13,
	slot_m2_socket1_dp         = 0x14,
	slot_m2_socket1_sd         = 0x15,
	slot_m2_socket2            = 0x16,
	slot_m2_socket3            = 0x17,
	slot_mxm_type_i            = 0x18,
	slot_mxm_type_ii           = 0x19,
	slot_mxm_type_iii_standard = 0x1a,
	slot_mxm_type_iii_he       = 0x1b,
	slot_mxm_type_iv           = 0x1c,
	slot_mxm30_type_a          = 0x1d,
	slot_mxm30_type_b          = 0x1e,
	slot_pcie_gen2_sff_8639    = 0x1f,
	slot_pcie_gen3_sff_8639    = 0x20,
	slot_pcie_mini52pin_bsko   = 0x21,
	slot_pcie_mini52pin_nobsko = 0x22,
	slot_pcie_mini76pin        = 0x23,
	slot_pcie_gen4sff_8639     = 0x24,
	slot_pcie_gen5sff_8639     = 0x25,
	slot_ocpnic30_small        = 0x26,
	slot_ocpnic30_large        = 0x27,
	slot_ocpnic_priorto30      = 0x28,
	slot_cxl_flexbus10         = 0x30,
	slot_pc98c20               = 0xa0,
	slot_pc98c24               = 0xa1,
	slot_pc98e                 = 0xa2,
	slot_pc98_local_bus        = 0xa3,
	slot_pc98_card             = 0xa4,
	slot_pci_express           = 0xa5,
	slot_pcie_x1               = 0xa6,
	slot_pcie_x2               = 0xa7,
	slot_pcie_x4               = 0xa8,
	slot_pcie_x8               = 0xa9,
	slot_pcie_x16              = 0xaa,
	slot_pcie_gen2             = 0xab,
	slot_pcie_gen2x1           = 0xac,
	slot_pcie_gen2x2           = 0xad,
	slot_pcie_gen2x4           = 0xae,
	slot_pcie_gen2x8           = 0xaf,
	slot_pcie_gen2x16          = 0xb0,
	slot_pcie_gen3             = 0xb1,
	slot_pcie_gen3x1           = 0xb2,
	slot_pcie_gen3x2           = 0xb3,
	slot_pcie_gen3x4           = 0xb4,
	slot_pcie_gen3x8           = 0xb5,
	slot_pcie_gen3x16          = 0xb6,
	slot_pcie_gen4             = 0xb8,
	slot_pcie_gen4x1           = 0xb9,
	slot_pcie_gen4x2           = 0xba,
	slot_pcie_gen4x4           = 0xbb,
	slot_pcie_gen4x8           = 0xbc,
	slot_pcie_gen4x16          = 0xbd,
	slot_pcie_gen5             = 0xbe,
	slot_pcie_gen5x1           = 0xbf,
	slot_pcie_gen5x2           = 0xc0,
	slot_pcie_gen5x4           = 0xc1,
	slot_pcie_gen5x8           = 0xc2,
	slot_pcie_gen5x16          = 0xc3,
	slot_pcie_gen6and_beyond   = 0xc4,
	slot_edc1ue1_slot          = 0xc5,
	slot_edc3e3_slot           = 0xc6
}__packed misc_slot_type;
typedef enum misc_slot_data_bus_width{
	slot_data_bus_width_other   = 0x01,
	slot_data_bus_width_unknown = 0x02,
	slot_data_bus_width8_bit    = 0x03,
	slot_data_bus_width16_bit   = 0x04,
	slot_data_bus_width32_bit   = 0x05,
	slot_data_bus_width64_bit   = 0x06,
	slot_data_bus_width128_bit  = 0x07,
	slot_data_bus_width1x       = 0x08,
	slot_data_bus_width2x       = 0x09,
	slot_data_bus_width4x       = 0x0a,
	slot_data_bus_width8x       = 0x0b,
	slot_data_bus_width12x      = 0x0c,
	slot_data_bus_width16x      = 0x0d,
	slot_data_bus_width32x      = 0x0e
}__packed misc_slot_data_bus_width;
typedef enum misc_slot_physical_width{
	phyw_other   = 0x01,
	phyw_unknown = 0x02,
	phyw8_bit    = 0x03,
	phyw16_bit   = 0x04,
	phyw32_bit   = 0x05,
	phyw64_bit   = 0x06,
	phyw128_bit  = 0x07,
	phyw1x       = 0x08,
	phyw2x       = 0x09,
	phyw4x       = 0x0a,
	phyw8x       = 0x0b,
	phyw12x      = 0x0c,
	phyw16x      = 0x0d,
	phyw32x      = 0x0e
}__packed misc_slot_physical_width;
typedef enum misc_slot_information{
	slot_others = 0x00,
	slot_gen1   = 0x01,
	slot_gen2   = 0x01,
	slot_gen3   = 0x03,
	slot_gen4   = 0x04,
	slot_gen5   = 0x05,
	slot_gen6   = 0x06
}__packed misc_slot_information;
typedef enum misc_slot_usage{
	usage_other       = 0x01,
	usage_unknown     = 0x02,
	usage_available   = 0x03,
	usage_in_use      = 0x04,
	usage_unavailable = 0x05
}__packed misc_slot_usage;
typedef enum misc_slot_length{
	slot_len_other   = 0x01,
	slot_len_unknown = 0x02,
	slot_len_short   = 0x03,
	slot_len_long    = 0x04
}__packed misc_slot_length;
typedef struct misc_slot_flags1{
	uint8_t flags_unknown     :1;
	uint8_t provides5v0       :1;
	uint8_t provides3v3       :1;
	uint8_t shared_slot       :1;
	uint8_t pc_card16         :1;
	uint8_t card_bus          :1;
	uint8_t zoom_video        :1;
	uint8_t modem_ring_resume :1;
}__packed misc_slot_flags1;
typedef struct misc_slot_flags2{
	uint8_t pme_signal_supported       :1;
	uint8_t hot_plug_devices_supported :1;
	uint8_t smbus_signal_supported     :1;
	uint8_t bifurcation_supported      :1;
	uint8_t async_surprise_removal     :1;
	uint8_t flexbus_slot_cxl10_capable :1;
	uint8_t flexbus_slot_cxl20_capable :1;
	uint8_t flexbus_slot_cxl30_capable :1;
}__packed misc_slot_flags2;
typedef enum misc_slot_height{
	slot_height_none        = 0x00,
	slot_height_other       = 0x01,
	slot_height_unknown     = 0x02,
	slot_height_full_height = 0x03,
	slot_height_low_profile = 0x04
}__packed misc_slot_height;
typedef struct misc_slot_peer_group{
	uint16_t segment_group_num;
	uint8_t  bus_num;
	uint8_t  dev_func_num;
	uint8_t  data_bus_width;
}__packed misc_slot_peer_group;
typedef struct smbios_table_type9{
	smbios_structure     header;
	smbios_table_string  slot_designation;
	uint8_t              slot_type;
	uint8_t              slot_data_bus_width;
	uint8_t              current_usage;
	uint8_t              slot_length;
	uint16_t             slot_id;
	misc_slot_flags1     slot_flags1;
	misc_slot_flags2     slot_flags2;
	uint16_t             segment_group_num;
	uint8_t              bus_num;
	uint8_t              dev_func_num;
	uint8_t              data_bus_width;
	uint8_t              peer_grouping_count;
	misc_slot_peer_group peer_groups[1];
}__packed smbios_table_type9;
typedef struct smbios_table_type9_ext{
	uint8_t  slot_information;
	uint8_t  slot_physical_width;
	uint16_t slot_pitch;
	uint8_t  slot_height;
}__packed smbios_table_type9_ext;
typedef enum misc_onboard_device_type{
	onboard_other      = 0x01,
	onboard_unknown    = 0x02,
	onboard_video      = 0x03,
	onboard_scsi_ctrl  = 0x04,
	onboard_ethernet   = 0x05,
	onboard_token_ring = 0x06,
	onboard_sound      = 0x07,
	onboard_pata_ctrl  = 0x08,
	onboard_sata_ctrl  = 0x09,
	onboard_sas_ctrl   = 0x0a
}__packed misc_onboard_device_type;
typedef enum memory_array_location{
	location_other                     = 0x01,
	location_unknown                   = 0x02,
	location_system_board              = 0x03,
	location_isa_addon_card            = 0x04,
	location_eisa_addon_card           = 0x05,
	location_pci_addon_card            = 0x06,
	location_mca_addon_card            = 0x07,
	location_pcmcia_addon_card         = 0x08,
	location_proprietary_addon_card    = 0x09,
	location_nu_bus                    = 0x0a,
	location_pc98c20_addon_card        = 0xa0,
	location_pc98c24_addon_card        = 0xa1,
	location_pc98e_addon_card          = 0xa2,
	location_pc98_local_bus_addon_card = 0xa3,
	location_cxl_addon_card            = 0xa4
}__packed memory_array_location;
typedef enum memory_array_use{
	use_other            = 0x01,
	use_unknown          = 0x02,
	use_system_memory    = 0x03,
	use_video_memory     = 0x04,
	use_flash_memory     = 0x05,
	use_non_volatile_ram = 0x06,
	use_cache_memory     = 0x07
}__packed memory_array_use;
typedef enum memory_error_corrion{
	err_corr_other          = 0x01,
	err_corr_unknown        = 0x02,
	err_corr_none           = 0x03,
	err_corr_parity         = 0x04,
	err_corr_single_bit_ecc = 0x05,
	err_corr_multi_bit_ecc  = 0x06,
	err_corr_crc            = 0x07
}__packed memory_error_corrion;
typedef struct smbios_table_type16{
	smbios_structure header;
	uint8_t          location;
	uint8_t          use;
	uint8_t          memory_error_correction;
	uint32_t         max_capacity;
	uint16_t         memory_error_information_handle;
	uint16_t         memory_devices_cnt;
	uint64_t         ext_max_capacity;
}__packed smbios_table_type16;
typedef enum memory_form_factor{
	form_other            = 0x01,
	form_unknown          = 0x02,
	form_simm             = 0x03,
	form_sip              = 0x04,
	form_chip             = 0x05,
	form_dip              = 0x06,
	form_zip              = 0x07,
	form_proprietary_card = 0x08,
	form_dimm             = 0x09,
	form_tsop             = 0x0a,
	form_row_of_chips     = 0x0b,
	form_rimm             = 0x0c,
	form_sodimm           = 0x0d,
	form_srimm            = 0x0e,
	form_fb_dimm          = 0x0f,
	form_die              = 0x10,
	form_camm             = 0x11
}__packed memory_form_factor;
typedef enum memory_device_type{
	type_other              = 0x01,
	type_unknown            = 0x02,
	type_dram               = 0x03,
	type_edram              = 0x04,
	type_vram               = 0x05,
	type_sram               = 0x06,
	type_ram                = 0x07,
	type_rom                = 0x08,
	type_flash              = 0x09,
	type_eeprom             = 0x0a,
	type_feprom             = 0x0b,
	type_eprom              = 0x0c,
	type_cdram              = 0x0d,
	type3_dram              = 0x0e,
	type_sdram              = 0x0f,
	type_sgram              = 0x10,
	type_rdram              = 0x11,
	type_ddr                = 0x12,
	type_ddr2               = 0x13,
	type_ddr2_fb_dimm       = 0x14,
	type_ddr3               = 0x18,
	type_fbd2               = 0x19,
	type_ddr4               = 0x1a,
	type_lpddr              = 0x1b,
	type_lpddr2             = 0x1c,
	type_lpddr3             = 0x1d,
	type_lpddr4             = 0x1e,
	type_logical_nonvol_dev = 0x1f,
	type_hbm                = 0x20,
	type_hbm2               = 0x21,
	type_ddr5               = 0x22,
	type_lpddr5             = 0x23,
	type_hbm3               = 0x24
}__packed memory_device_type;
typedef struct memory_device_type_detail{
	uint16_t reserved      :1;
	uint16_t other         :1;
	uint16_t unknown       :1;
	uint16_t fast_paged    :1;
	uint16_t static_column :1;
	uint16_t pseudo_static :1;
	uint16_t rambus        :1;
	uint16_t synchronous   :1;
	uint16_t cmos          :1;
	uint16_t edo           :1;
	uint16_t window_dram   :1;
	uint16_t cache_dram    :1;
	uint16_t nonvolatile   :1;
	uint16_t registered    :1;
	uint16_t unbuffered    :1;
	uint16_t lr_dimm       :1;
}__packed memory_device_type_detail;
typedef enum memory_device_tech{
	tech_other    = 0x01,
	tech_unknown  = 0x02,
	tech_dram     = 0x03,
	tech_nvdimm_n = 0x04,
	tech_nvdimm_f = 0x05,
	tech_nvdimm_p = 0x06,
	tech_optane   = 0x07
}__packed memory_device_tech;
typedef union {
	struct {
		uint16_t reserved      :1;
		uint16_t other         :1;
		uint16_t unknown       :1;
		uint16_t vol_memory    :1;
		uint16_t byte_persist  :1;
		uint16_t block_persist :1;
		uint16_t reserved2     :10;
	}__packed bits;
	uint16_t uint16;
}__packed memory_device_operating_mode_capability;
typedef struct smbios_table_type17{
	smbios_structure          header;
	smbios_handle             memory_array_handle;
	smbios_handle             memory_error_information_handle;
	uint16_t                  total_width;
	uint16_t                  data_width;
	uint16_t                  size;
	uint8_t                   form_factor;
	uint8_t                   device_set;
	smbios_table_string       device_locator;
	smbios_table_string       bank_locator;
	uint8_t                   memory_type;
	memory_device_type_detail type_detail;
	uint16_t                  speed;
	smbios_table_string       manufacturer;
	smbios_table_string       serial_number;
	smbios_table_string       asset_tag;
	smbios_table_string       part_number;
	uint8_t                   attributes;
	uint32_t                  ext_size;
	uint16_t                  configured_memory_clock_speed;
	uint16_t                  minimum_voltage;
	uint16_t                  max_voltage;
	uint16_t                  configured_voltage;
	uint8_t                   memory_technology;
	uint16_t                  memory_operating_mode_capability;
	smbios_table_string       firmware_version;
	uint16_t                  module_manufacturer_id;
	uint16_t                  module_product_id;
	uint16_t                  memory_subsystem_controller_manufacturer_id;
	uint16_t                  memory_subsystem_controller_product_id;
	uint64_t                  non_volatile_size;
	uint64_t                  volatile_size;
	uint64_t                  cache_size;
	uint64_t                  logical_size;
	uint32_t                  ext_speed;
	uint32_t                  ext_configured_memory_speed;
	uint16_t                  pmic0_manufacturer_id;
	uint16_t                  pmic0_revision_number;
	uint16_t                  rcd_manufacturer_id;
	uint16_t                  rcd_revision_number;
}__packed smbios_table_type17;
typedef enum memory_error_type{
	error_other              = 0x01,
	error_unknown            = 0x02,
	error_ok                 = 0x03,
	error_bad_read           = 0x04,
	error_parity             = 0x05,
	error_sigle_bit          = 0x06,
	error_double_bit         = 0x07,
	error_multi_bit          = 0x08,
	error_nibble             = 0x09,
	error_checksum           = 0x0a,
	error_crc                = 0x0b,
	error_correct_single_bit = 0x0c,
	error_corrected          = 0x0d,
	error_un_correctable     = 0x0e
}__packed memory_error_type;
typedef enum memory_error_granularity{
	granu_other              = 0x01,
	granu_other_unknown       = 0x02,
	granu_device_level        = 0x03,
	granu_mem_partition_level = 0x04
}__packed memory_error_granularity;
typedef enum memory_error_operation{
	oper_other        = 0x01,
	oper_unknown      = 0x02,
	oper_read         = 0x03,
	oper_write        = 0x04,
	oper_partial_write = 0x05
}__packed memory_error_operation;
typedef struct smbios_table_type18{
	smbios_structure   header;
	uint8_t            error_type;
	uint8_t            error_granularity;
	uint8_t            error_operation;
	uint32_t           vendor_syndrome;
	uint32_t           memory_array_error_address;
	uint32_t           device_error_address;
	uint32_t           error_resolution;
}__packed smbios_table_type18;
typedef struct smbios_table_type19{
	smbios_structure   header;
	uint32_t           starting_address;
	uint32_t           ending_address;
	uint16_t           memory_array_handle;
	uint8_t            partition_width;
	uint64_t           ext_starting_address;
	uint64_t           ext_ending_address;
}__packed smbios_table_type19;
typedef struct smbios_table_type20{
	smbios_structure   header;
	uint32_t           starting_address;
	uint32_t           ending_address;
	uint16_t           memory_device_handle;
	uint16_t           memory_array_mapped_address_handle;
	uint8_t            partition_row_position;
	uint8_t            interleave_position;
	uint8_t            interleaved_data_depth;
	uint64_t           ext_starting_address;
	uint64_t           ext_ending_address;
}__packed smbios_table_type20;
typedef enum misc_boot_information_status_data_type{
	status_no_error                  = 0x00,
	status_no_bootable_media         = 0x01,
	status_normal_os_failed_loading  = 0x02,
	status_firmware_detected_failure = 0x03,
	status_os_detected_failure       = 0x04,
	status_user_requested_boot       = 0x05,
	status_system_security_violation = 0x06,
	status_previous_requested_image  = 0x07,
	status_watchdog_timer_expired    = 0x08,
	status_start_reserved            = 0x09,
	status_start_oem_specific        = 0x80,
	status_start_product_specific    = 0xc0
}__packed misc_boot_information_status_data_type;
typedef struct smbios_table_type32{
	smbios_structure   header;
	uint8_t            reserved[6];
	uint8_t            status;
}__packed smbios_table_type32;
typedef struct smbios_table_type127{
	smbios_structure    header;
}__packed smbios_table_type127;
typedef union smbios_structure_pointer{
	smbios_structure        *header;
	smbios_table_type0      *type0;
	smbios_table_type1      *type1;
	smbios_table_type2      *type2;
	smbios_table_type3      *type3;
	smbios_table_type4      *type4;
	smbios_table_type7      *type7;
	smbios_table_type8      *type8;
	smbios_table_type9      *type9;
	smbios_table_type16     *type16;
	smbios_table_type17     *type17;
	smbios_table_type18     *type18;
	smbios_table_type19     *type19;
	smbios_table_type20     *type20;
	smbios_table_type32     *type32;
	smbios_table_type127    *type127;
	uint8_t                 *raw;
	void                    *pointer;
	uintn_t                 value;
}smbios_structure_pointer;
extern efi_guid gEfiSmbiosTableGuid;
extern efi_guid gEfiSmbios3TableGuid;
#endif
