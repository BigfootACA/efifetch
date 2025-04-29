#ifndef PCI_H
#define PCI_H
#include"efi.h"
#define PCI_MAX_BUS     255
#define PCI_MAX_DEVICE  31
#define PCI_MAX_FUNC    7
typedef struct pci_device_independent_region{
	uint16_t    vendor_id;
	uint16_t    device_id;
	uint16_t    command;
	uint16_t    status;
	uint8_t     revision_id;
	uint8_t     class_code[3];
	uint8_t     cache_line_size;
	uint8_t     latency_timer;
	uint8_t     header_type;
	uint8_t     bist;
}__packed pci_device_independent_region;
typedef struct pci_device_header_type_region{
	uint32_t    bar[6];
	uint32_t    cis_ptr;
	uint16_t    subsystem_vendor_id;
	uint16_t    subsystem_id;
	uint32_t    expansion_rom_bar;
	uint8_t     capability_ptr;
	uint8_t     reserved1[3];
	uint32_t    reserved2;
	uint8_t     interrupt_line;
	uint8_t     interrupt_pin;
	uint8_t     min_gnt;
	uint8_t     max_lat;
}__packed pci_device_header_type_region;
typedef struct pci_type00{
	pci_device_independent_region hdr;
	pci_device_header_type_region device;
}__packed pci_type00;
typedef struct pci_bridge_control_register{
	uint32_t    bar[2];
	uint8_t     primary_bus;
	uint8_t     secondary_bus;
	uint8_t     subordinate_bus;
	uint8_t     secondary_latency_timer;
	uint8_t     io_base;
	uint8_t     io_limit;
	uint16_t    secondary_status;
	uint16_t    memory_base;
	uint16_t    memory_limit;
	uint16_t    prefetchable_memory_base;
	uint16_t    prefetchable_memory_limit;
	uint32_t    prefetchable_base_upper32;
	uint32_t    prefetchable_limit_upper32;
	uint16_t    io_base_upper16;
	uint16_t    io_limit_upper16;
	uint8_t     capability_ptr;
	uint8_t     reserved[3];
	uint32_t    expansion_rom_bar;
	uint8_t     interrupt_line;
	uint8_t     interrupt_pin;
	uint16_t    bridge_control;
}__packed pci_bridge_control_register;
typedef struct pci_type01{
	pci_device_independent_region hdr;
	pci_bridge_control_register bridge;
}__packed pci_type01;
typedef union pci_type_generic{
	pci_type00 device;
	pci_type01 bridge;
}__packed pci_type_generic;
typedef struct pci_cardbus_control_register{
	uint32_t    card_bus_socket_reg;
	uint8_t     cap_ptr;
	uint8_t     reserved;
	uint16_t    secondary_status;
	uint8_t     pci_bus_number;
	uint8_t     card_bus_bus_number;
	uint8_t     subordinate_bus_number;
	uint8_t     card_bus_latency_timer;
	uint32_t    memory_base0;
	uint32_t    memory_limit0;
	uint32_t    memory_base1;
	uint32_t    memory_limit1;
	uint32_t    io_base0;
	uint32_t    io_limit0;
	uint32_t    io_base1;
	uint32_t    io_limit1;
	uint8_t     interrupt_line;
	uint8_t     interrupt_pin;
	uint16_t    bridge_control;
}__packed pci_cardbus_control_register;
#define PCI_CLASS_OLD          0x00
#define   PCI_CLASS_OLD_OTHER  0x00
#define   PCI_CLASS_OLD_VGA    0x01
#define PCI_CLASS_MASS_STORAGE           0x01
#define   PCI_CLASS_MASS_STORAGE_SCSI    0x00
#define   PCI_CLASS_MASS_STORAGE_IDE     0x01
#define   PCI_CLASS_MASS_STORAGE_FLOPPY  0x02
#define   PCI_CLASS_MASS_STORAGE_IPI     0x03
#define   PCI_CLASS_MASS_STORAGE_RAID    0x04
#define   PCI_CLASS_MASS_STORAGE_OTHER   0x80
#define PCI_CLASS_NETWORK              0x02
#define   PCI_CLASS_NETWORK_ETHERNET   0x00
#define   PCI_CLASS_NETWORK_TOKENRING  0x01
#define   PCI_CLASS_NETWORK_FDDI       0x02
#define   PCI_CLASS_NETWORK_ATM        0x03
#define   PCI_CLASS_NETWORK_ISDN       0x04
#define   PCI_CLASS_NETWORK_OTHER      0x80
#define PCI_CLASS_DISPLAY          0x03
#define   PCI_CLASS_DISPLAY_VGA    0x00
#define     PCI_IF_VGA_VGA         0x00
#define     PCI_IF_VGA_8514        0x01
#define   PCI_CLASS_DISPLAY_XGA    0x01
#define   PCI_CLASS_DISPLAY_3D     0x02
#define   PCI_CLASS_DISPLAY_OTHER  0x80
#define PCI_CLASS_MEDIA              0x04
#define   PCI_CLASS_MEDIA_VIDEO      0x00
#define   PCI_CLASS_MEDIA_AUDIO      0x01
#define   PCI_CLASS_MEDIA_TELEPHONE  0x02
#define   PCI_CLASS_MEDIA_OTHER      0x80
#define PCI_CLASS_MEMORY_CONTROLLER  0x05
#define   PCI_CLASS_MEMORY_RAM       0x00
#define   PCI_CLASS_MEMORY_FLASH     0x01
#define   PCI_CLASS_MEMORY_OTHER     0x80
#define PCI_CLASS_BRIDGE                   0x06
#define   PCI_CLASS_BRIDGE_HOST            0x00
#define   PCI_CLASS_BRIDGE_ISA             0x01
#define   PCI_CLASS_BRIDGE_EISA            0x02
#define   PCI_CLASS_BRIDGE_MCA             0x03
#define   PCI_CLASS_BRIDGE_P2P             0x04
#define     PCI_IF_BRIDGE_P2P              0x00
#define     PCI_IF_BRIDGE_P2P_SUBTRACTIVE  0x01
#define   PCI_CLASS_BRIDGE_PCMCIA          0x05
#define   PCI_CLASS_BRIDGE_NUBUS           0x06
#define   PCI_CLASS_BRIDGE_CARDBUS         0x07
#define   PCI_CLASS_BRIDGE_RACEWAY         0x08
#define   PCI_CLASS_BRIDGE_OTHER           0x80
#define   PCI_CLASS_BRIDGE_ISA_PDECODE     0x80
#define PCI_CLASS_SCC                    0x07
#define   PCI_SUBCLASS_SERIAL            0x00
#define     PCI_IF_GENERIC_XT            0x00
#define     PCI_IF_16450                 0x01
#define     PCI_IF_16550                 0x02
#define     PCI_IF_16650                 0x03
#define     PCI_IF_16750                 0x04
#define     PCI_IF_16850                 0x05
#define     PCI_IF_16950                 0x06
#define   PCI_SUBCLASS_PARALLEL          0x01
#define     PCI_IF_PARALLEL_PORT         0x00
#define     PCI_IF_BI_DIR_PARALLEL_PORT  0x01
#define     PCI_IF_ECP_PARALLEL_PORT     0x02
#define     PCI_IF_1284_CONTROLLER       0x03
#define     PCI_IF_1284_DEVICE           0xFE
#define   PCI_SUBCLASS_MULTIPORT_SERIAL  0x02
#define   PCI_SUBCLASS_MODEM             0x03
#define     PCI_IF_GENERIC_MODEM         0x00
#define     PCI_IF_16450_MODEM           0x01
#define     PCI_IF_16550_MODEM           0x02
#define     PCI_IF_16650_MODEM           0x03
#define     PCI_IF_16750_MODEM           0x04
#define   PCI_SUBCLASS_SCC_OTHER         0x80
#define PCI_CLASS_SYSTEM_PERIPHERAL      0x08
#define   PCI_SUBCLASS_PIC               0x00
#define     PCI_IF_8259_PIC              0x00
#define     PCI_IF_ISA_PIC               0x01
#define     PCI_IF_EISA_PIC              0x02
#define     PCI_IF_APIC_CONTROLLER       0x10
#define     PCI_IF_APIC_CONTROLLER2      0x20
#define   PCI_SUBCLASS_DMA               0x01
#define     PCI_IF_8237_DMA              0x00
#define     PCI_IF_ISA_DMA               0x01
#define     PCI_IF_EISA_DMA              0x02
#define   PCI_SUBCLASS_TIMER             0x02
#define     PCI_IF_8254_TIMER            0x00
#define     PCI_IF_ISA_TIMER             0x01
#define     PCI_IF_EISA_TIMER            0x02
#define   PCI_SUBCLASS_RTC               0x03
#define     PCI_IF_GENERIC_RTC           0x00
#define     PCI_IF_ISA_RTC               0x01
#define   PCI_SUBCLASS_PNP_CONTROLLER    0x04
#define   PCI_SUBCLASS_PERIPHERAL_OTHER  0x80
#define PCI_CLASS_INPUT_DEVICE           0x09
#define   PCI_SUBCLASS_KEYBOARD          0x00
#define   PCI_SUBCLASS_PEN               0x01
#define   PCI_SUBCLASS_MOUSE_CONTROLLER  0x02
#define   PCI_SUBCLASS_SCAN_CONTROLLER   0x03
#define   PCI_SUBCLASS_GAMEPORT          0x04
#define     PCI_IF_GAMEPORT              0x00
#define     PCI_IF_GAMEPORT1             0x10
#define   PCI_SUBCLASS_INPUT_OTHER       0x80
#define PCI_CLASS_DOCKING_STATION       0x0A
#define   PCI_SUBCLASS_DOCKING_GENERIC  0x00
#define   PCI_SUBCLASS_DOCKING_OTHER    0x80
#define PCI_CLASS_PROCESSOR          0x0B
#define   PCI_SUBCLASS_PROC_386      0x00
#define   PCI_SUBCLASS_PROC_486      0x01
#define   PCI_SUBCLASS_PROC_PENTIUM  0x02
#define   PCI_SUBCLASS_PROC_ALPHA    0x10
#define   PCI_SUBCLASS_PROC_POWERPC  0x20
#define   PCI_SUBCLASS_PROC_MIPS     0x30
#define   PCI_SUBCLASS_PROC_CO_PORC  0x40
#define PCI_CLASS_SERIAL                 0x0C
#define   PCI_CLASS_SERIAL_FIREWIRE      0x00
#define     PCI_IF_1394                  0x00
#define     PCI_IF_1394_OPEN_HCI         0x10
#define   PCI_CLASS_SERIAL_ACCESS_BUS    0x01
#define   PCI_CLASS_SERIAL_SSA           0x02
#define   PCI_CLASS_SERIAL_USB           0x03
#define     PCI_IF_UHCI                  0x00
#define     PCI_IF_OHCI                  0x10
#define     PCI_IF_USB_OTHER             0x80
#define     PCI_IF_USB_DEVICE            0xFE
#define   PCI_CLASS_SERIAL_FIBRECHANNEL  0x04
#define   PCI_CLASS_SERIAL_SMB           0x05
#define PCI_CLASS_WIRELESS             0x0D
#define   PCI_SUBCLASS_IRDA            0x00
#define   PCI_SUBCLASS_IR              0x01
#define   PCI_SUBCLASS_RF              0x10
#define   PCI_SUBCLASS_WIRELESS_OTHER  0x80
#define PCI_CLASS_INTELLIGENT_IO  0x0E
#define PCI_CLASS_SATELLITE   0x0F
#define   PCI_SUBCLASS_TV     0x01
#define   PCI_SUBCLASS_AUDIO  0x02
#define   PCI_SUBCLASS_VOICE  0x03
#define   PCI_SUBCLASS_DATA   0x04
#define PCI_SECURITY_CONTROLLER        0x10
#define   PCI_SUBCLASS_NET_COMPUT      0x00
#define   PCI_SUBCLASS_ENTERTAINMENT   0x10
#define   PCI_SUBCLASS_SECURITY_OTHER  0x80
#define PCI_CLASS_DPIO             0x11
#define   PCI_SUBCLASS_DPIO        0x00
#define   PCI_SUBCLASS_DPIO_OTHER  0x80
#define IS_CLASS1(_p, c)  ((_p)->Hdr.ClassCode[2] == (c))
#define IS_CLASS2(_p, c, s)  (IS_CLASS1 (_p, c) && ((_p)->Hdr.ClassCode[1] == (s)))
#define IS_CLASS3(_p, c, s, p)  (IS_CLASS2 (_p, c, s) && ((_p)->Hdr.ClassCode[0] == (p)))
#define IS_PCI_DISPLAY(_p)  IS_CLASS1 (_p, PCI_CLASS_DISPLAY)
#define IS_PCI_VGA(_p)  IS_CLASS3 (_p, PCI_CLASS_DISPLAY, PCI_CLASS_DISPLAY_VGA, PCI_IF_VGA_VGA)
#define IS_PCI_8514(_p)  IS_CLASS3 (_p, PCI_CLASS_DISPLAY, PCI_CLASS_DISPLAY_VGA, PCI_IF_VGA_8514)
#define IS_PCI_OLD(_p)  IS_CLASS1 (_p, PCI_CLASS_OLD)
#define IS_PCI_OLD_VGA(_p)  IS_CLASS2 (_p, PCI_CLASS_OLD, PCI_CLASS_OLD_VGA)
#define IS_PCI_IDE(_p)  IS_CLASS2 (_p, PCI_CLASS_MASS_STORAGE, PCI_CLASS_MASS_STORAGE_IDE)
#define IS_PCI_SCSI(_p)  IS_CLASS2 (_p, PCI_CLASS_MASS_STORAGE, PCI_CLASS_MASS_STORAGE_SCSI)
#define IS_PCI_RAID(_p)  IS_CLASS2 (_p, PCI_CLASS_MASS_STORAGE, PCI_CLASS_MASS_STORAGE_RAID)
#define IS_PCI_LPC(_p)  IS_CLASS2 (_p, PCI_CLASS_BRIDGE, PCI_CLASS_BRIDGE_ISA)
#define IS_PCI_P2P(_p)  IS_CLASS3 (_p, PCI_CLASS_BRIDGE, PCI_CLASS_BRIDGE_P2P, PCI_IF_BRIDGE_P2P)
#define IS_PCI_P2P_SUB(_p)  IS_CLASS3 (_p, PCI_CLASS_BRIDGE, PCI_CLASS_BRIDGE_P2P, PCI_IF_BRIDGE_P2P_SUBTRACTIVE)
#define IS_PCI_16550_SERIAL(_p)  IS_CLASS3 (_p, PCI_CLASS_SCC, PCI_SUBCLASS_SERIAL, PCI_IF_16550)
#define IS_PCI_USB(_p)  IS_CLASS2 (_p, PCI_CLASS_SERIAL, PCI_CLASS_SERIAL_USB)
#define HEADER_TYPE_DEVICE             0x00
#define HEADER_TYPE_PCI_TO_PCI_BRIDGE  0x01
#define HEADER_TYPE_CARDBUS_BRIDGE     0x02
#define HEADER_TYPE_MULTI_FUNCTION     0x80
#define HEADER_LAYOUT_CODE  0x7f
#define IS_PCI_BRIDGE(_p)  (((_p)->Hdr.HeaderType & HEADER_LAYOUT_CODE) == (HEADER_TYPE_PCI_TO_PCI_BRIDGE))
#define IS_CARDBUS_BRIDGE(_p)  (((_p)->Hdr.HeaderType & HEADER_LAYOUT_CODE) == (HEADER_TYPE_CARDBUS_BRIDGE))
#define IS_PCI_MULTI_FUNC(_p)  ((_p)->Hdr.HeaderType & HEADER_TYPE_MULTI_FUNCTION)
#define PCI_BRIDGE_ROMBAR  0x38
#define PCI_MAX_BAR            0x0006
#define PCI_MAX_CONFIG_OFFSET  0x0100
#define PCI_VENDOR_ID_OFFSET            0x00
#define PCI_DEVICE_ID_OFFSET            0x02
#define PCI_COMMAND_OFFSET              0x04
#define PCI_PRIMARY_STATUS_OFFSET       0x06
#define PCI_REVISION_ID_OFFSET          0x08
#define PCI_CLASSCODE_OFFSET            0x09
#define PCI_CACHELINE_SIZE_OFFSET       0x0C
#define PCI_LATENCY_TIMER_OFFSET        0x0D
#define PCI_HEADER_TYPE_OFFSET          0x0E
#define PCI_BIST_OFFSET                 0x0F
#define PCI_BASE_ADDRESSREG_OFFSET      0x10
#define PCI_CARDBUS_CIS_OFFSET          0x28
#define PCI_SVID_OFFSET                 0x2C
#define PCI_SUBSYSTEM_VENDOR_ID_OFFSET  0x2C
#define PCI_SID_OFFSET                  0x2E
#define PCI_SUBSYSTEM_ID_OFFSET         0x2E
#define PCI_EXPANSION_ROM_BASE          0x30
#define PCI_CAPBILITY_POINTER_OFFSET    0x34
#define PCI_INT_LINE_OFFSET             0x3C
#define PCI_INT_PIN_OFFSET              0x3D
#define PCI_MAXGNT_OFFSET               0x3E
#define PCI_MAXLAT_OFFSET               0x3F
#define PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET      0x18
#define PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET    0x19
#define PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET  0x1a
#define PCI_BRIDGE_SECONDARY_LATENCY_TIMER_OFFSET   0x1b
#define PCI_BRIDGE_STATUS_REGISTER_OFFSET           0x1E
#define PCI_BRIDGE_CONTROL_REGISTER_OFFSET          0x3E
#define PCI_INT_LINE_UNKNOWN  0xFF
typedef union pci_config_access_cf8{
	struct{
		uint32_t reg:8;
		uint32_t func:3;
		uint32_t dev:5;
		uint32_t bus:8;
		uint32_t reserved:7;
		uint32_t enable:1;
	}__packed bits;
	uint32_t uint32_t;
}__packed pci_config_access_cf8;
#define EFI_PCI_COMMAND_IO_SPACE                     BIT0
#define EFI_PCI_COMMAND_MEMORY_SPACE                 BIT1
#define EFI_PCI_COMMAND_BUS_MASTER                   BIT2
#define EFI_PCI_COMMAND_SPECIAL_CYCLE                BIT3
#define EFI_PCI_COMMAND_MEMORY_WRITE_AND_INVALIDATE  BIT4
#define EFI_PCI_COMMAND_VGA_PALETTE_SNOOP            BIT5
#define EFI_PCI_COMMAND_PARITY_ERROR_RESPOND         BIT6
#define EFI_PCI_COMMAND_STEPPING_CONTROL             BIT7
#define EFI_PCI_COMMAND_SERR                         BIT8
#define EFI_PCI_COMMAND_FAST_BACK_TO_BACK            BIT9
#define EFI_PCI_BRIDGE_CONTROL_PARITY_ERROR_RESPONSE    BIT0
#define EFI_PCI_BRIDGE_CONTROL_SERR                     BIT1
#define EFI_PCI_BRIDGE_CONTROL_ISA                      BIT2
#define EFI_PCI_BRIDGE_CONTROL_VGA                      BIT3
#define EFI_PCI_BRIDGE_CONTROL_VGA_16                   BIT4
#define EFI_PCI_BRIDGE_CONTROL_MASTER_ABORT             BIT5
#define EFI_PCI_BRIDGE_CONTROL_RESET_SECONDARY_BUS      BIT6
#define EFI_PCI_BRIDGE_CONTROL_FAST_BACK_TO_BACK        BIT7
#define EFI_PCI_BRIDGE_CONTROL_PRIMARY_DISCARD_TIMER    BIT8
#define EFI_PCI_BRIDGE_CONTROL_SECONDARY_DISCARD_TIMER  BIT9
#define EFI_PCI_BRIDGE_CONTROL_TIMER_STATUS             BIT10
#define EFI_PCI_BRIDGE_CONTROL_DISCARD_TIMER_SERR       BIT11
#define EFI_PCI_BRIDGE_CONTROL_IREQINT_ENABLE        BIT7
#define EFI_PCI_BRIDGE_CONTROL_RANGE0_MEMORY_TYPE    BIT8
#define EFI_PCI_BRIDGE_CONTROL_RANGE1_MEMORY_TYPE    BIT9
#define EFI_PCI_BRIDGE_CONTROL_WRITE_POSTING_ENABLE  BIT10
#define EFI_PCI_STATUS_CAPABILITY          BIT4
#define EFI_PCI_STATUS_66MZ_CAPABLE        BIT5
#define EFI_PCI_FAST_BACK_TO_BACK_CAPABLE  BIT7
#define EFI_PCI_MASTER_DATA_PARITY_ERROR   BIT8
#define EFI_PCI_CARDBUS_BRIDGE_CAPABILITY_PTR  0x14
#define EFI_PCI_CAPABILITY_ID_PMI      0x01
#define EFI_PCI_CAPABILITY_ID_AGP      0x02
#define EFI_PCI_CAPABILITY_ID_VPD      0x03
#define EFI_PCI_CAPABILITY_ID_SLOTID   0x04
#define EFI_PCI_CAPABILITY_ID_MSI      0x05
#define EFI_PCI_CAPABILITY_ID_HOTPLUG  0x06
#define EFI_PCI_CAPABILITY_ID_SHPC     0x0C
typedef struct efi_pci_capability_hdr{
	uint8_t capability_id;
	uint8_t next_item_ptr;
}__packed efi_pci_capability_hdr;
typedef union efi_pci_pmc{
	struct{
		uint16_t version:3;
		uint16_t pme_clock:1;
		uint16_t reserved:1;
		uint16_t dev_spec_init:1;
		uint16_t aux_current:3;
		uint16_t d1_support:1;
		uint16_t d2_support:1;
		uint16_t pme_support:5;
	}__packed bits;
	uint16_t data;
}__packed efi_pci_pmc;
#define EFI_PCI_PMC_D3_COLD_MASK  (BIT15)
typedef union efi_pci_pmcsr{
	struct{
		uint16_t power_state:2;
		uint16_t reserved_for_pci_express:1;
		uint16_t no_soft_reset:1;
		uint16_t reserved:4;
		uint16_t pme_enable:1;
		uint16_t data_select:4;
		uint16_t data_scale:2;
		uint16_t pme_status:1;
	}__packed bits;
	uint16_t data;
}__packed efi_pci_pmcsr;
#define PCI_POWER_STATE_D0      0
#define PCI_POWER_STATE_D1      1
#define PCI_POWER_STATE_D2      2
#define PCI_POWER_STATE_D3_HOT  3
typedef union efi_pci_pmcsr_bse{
	struct{
		uint8_t reserved:6;
		uint8_t b2b3:1;
		uint8_t bus_power_clock_control:1;
	}__packed bits;
	uint8_t uint8_t;
}__packed efi_pci_pmcsr_bse;
typedef struct efi_pci_capability_pmi{
	efi_pci_capability_hdr hdr;
	efi_pci_pmc pmc;
	efi_pci_pmcsr pmcsr;
	efi_pci_pmcsr_bse bridge_extention;
	uint8_t data;
}__packed efi_pci_capability_pmi;
typedef struct efi_pci_capability_agp{
	efi_pci_capability_hdr hdr;
	uint8_t rev;
	uint8_t reserved;
	uint32_t status;
	uint32_t command;
}__packed efi_pci_capability_agp;
typedef struct efi_pci_capability_vpd{
	efi_pci_capability_hdr hdr;
	uint16_t addr_reg;
	uint32_t data_reg;
}__packed efi_pci_capability_vpd;
typedef struct efi_pci_capability_slotid{
	efi_pci_capability_hdr hdr;
	uint8_t expns_slot_reg;
	uint8_t chassis_no;
}__packed efi_pci_capability_slotid;
typedef struct efi_pci_capability_msi32{
	efi_pci_capability_hdr hdr;
	uint16_t msg_ctrl_reg;
	uint32_t msg_addr_reg;
	uint16_t msg_data_reg;
}__packed efi_pci_capability_msi32;
typedef struct efi_pci_capability_msi64{
	efi_pci_capability_hdr hdr;
	uint16_t msg_ctrl_reg;
	uint32_t msg_addr_reg_lsdw;
	uint32_t msg_addr_reg_msdw;
	uint16_t msg_data_reg;
}__packed efi_pci_capability_msi64;
typedef struct efi_pci_capability_hotplug{
	efi_pci_capability_hdr hdr;
}__packed efi_pci_capability_hotplug;
#define PCI_BAR_IDX0  0x00
#define PCI_BAR_IDX1  0x01
#define PCI_BAR_IDX2  0x02
#define PCI_BAR_IDX3  0x03
#define PCI_BAR_IDX4  0x04
#define PCI_BAR_IDX5  0x05
#define EFI_ROOT_BRIDGE_LIST                       'eprb'
#define EFI_PCI_EXPANSION_ROM_HEADER_EFISIGNATURE  0x0EF1
#define PCI_EXPANSION_ROM_HEADER_SIGNATURE       0xaa55
#define PCI_DATA_STRUCTURE_SIGNATURE             SIGNATURE_32 ('P', 'C', 'I', 'R')
#define PCI_CODE_TYPE_PCAT_IMAGE                 0x00
#define EFI_PCI_EXPANSION_ROM_HEADER_COMPRESSED  0x0001
typedef struct pci_expansion_rom_header{
	uint16_t    signature;
	uint8_t     reserved[0x16];
	uint16_t    pciroffset;
}__packed pci_expansion_rom_header;
typedef struct efi_legacy_expansion_rom_header{
	uint16_t    signature;
	uint8_t     size512;
	uint8_t     initentrypoint[3];
	uint8_t     reserved[0x12];
	uint16_t    pciroffset;
}__packed efi_legacy_expansion_rom_header;
typedef struct pci_data_structure{
	uint32_t    signature;
	uint16_t    vendorid;
	uint16_t    deviceid;
	uint16_t    reserved0;
	uint16_t    length;
	uint8_t     revision;
	uint8_t     classcode[3];
	uint16_t    imagelength;
	uint16_t    coderevision;
	uint8_t     codetype;
	uint8_t     indicator;
	uint16_t    reserved1;
}__packed pci_data_structure;
typedef struct efi_pci_expansion_rom_header{
	uint16_t    signature;
	uint16_t    initializationsize;
	uint32_t    efisignature;
	uint16_t    efisubsystem;
	uint16_t    efimachinetype;
	uint16_t    compressiontype;
	uint8_t     reserved[8];
	uint16_t    efiimageheaderoffset;
	uint16_t    pciroffset;
}__packed efi_pci_expansion_rom_header;
typedef union efi_pci_rom_header{
	uint8_t                         *raw;
	pci_expansion_rom_header        *generic;
	efi_pci_expansion_rom_header    *efi;
	efi_legacy_expansion_rom_header *pcat;
}__packed efi_pci_rom_header;
typedef struct efi_pci_io_protocol efi_pci_io_protocol;
typedef enum efi_pci_io_protocol_width{
	pciw_u8,
	pciw_u16,
	pciw_u32,
	pciw_u64,
	pciw_fifo_u8,
	pciw_fifo_u16,
	pciw_fifo_u32,
	pciw_fifo_u64,
	pciw_fill_u8,
	pciw_fill_u16,
	pciw_fill_u32,
	pciw_fill_u64,
	pciw_max
}efi_pci_io_protocol_width;
#define EFI_PCI_IO_PASS_THROUGH_BAR               0xff
#define EFI_PCI_IO_ATTRIBUTE_MASK                 0x077f
#define EFI_PCI_IO_ATTRIBUTE_ISA_MOTHERBOARD_IO   0x0001
#define EFI_PCI_IO_ATTRIBUTE_ISA_IO               0x0002
#define EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO       0x0004
#define EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY           0x0008
#define EFI_PCI_IO_ATTRIBUTE_VGA_IO               0x0010
#define EFI_PCI_IO_ATTRIBUTE_IDE_PRIMARY_IO       0x0020
#define EFI_PCI_IO_ATTRIBUTE_IDE_SECONDARY_IO     0x0040
#define EFI_PCI_IO_ATTRIBUTE_MEMORY_WRITE_COMBINE 0x0080
#define EFI_PCI_IO_ATTRIBUTE_IO                   0x0100
#define EFI_PCI_IO_ATTRIBUTE_MEMORY               0x0200
#define EFI_PCI_IO_ATTRIBUTE_BUS_MASTER           0x0400
#define EFI_PCI_IO_ATTRIBUTE_MEMORY_CACHED        0x0800
#define EFI_PCI_IO_ATTRIBUTE_MEMORY_DISABLE       0x1000
#define EFI_PCI_IO_ATTRIBUTE_EMBEDDED_DEVICE      0x2000
#define EFI_PCI_IO_ATTRIBUTE_EMBEDDED_ROM         0x4000
#define EFI_PCI_IO_ATTRIBUTE_DUAL_ADDRESS_CYCLE   0x8000
#define EFI_PCI_IO_ATTRIBUTE_ISA_IO_16            0x10000
#define EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO_16    0x20000
#define EFI_PCI_IO_ATTRIBUTE_VGA_IO_16            0x40000
#define EFI_PCI_DEVICE_ENABLE (EFI_PCI_IO_ATTRIBUTE_IO | EFI_PCI_IO_ATTRIBUTE_MEMORY | EFI_PCI_IO_ATTRIBUTE_BUS_MASTER)
#define EFI_VGA_DEVICE_ENABLE (EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO | EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY | EFI_PCI_IO_ATTRIBUTE_VGA_IO | EFI_PCI_IO_ATTRIBUTE_IO)
typedef enum efi_pci_io_protocol_operation{
	efi_pci_io_oper_bus_master_read,
	efi_pci_io_oper_bus_master_write,
	efi_pci_io_oper_bus_master_buffer,
	efi_pci_io_oper_maximum
}efi_pci_io_protocol_operation;
typedef enum efi_pci_io_protocol_attribute_operation{
	efi_pci_io_attr_oper_get,
	efi_pci_io_attr_oper_set,
	efi_pci_io_attr_oper_enable,
	efi_pci_io_attr_oper_disable,
	efi_pci_io_attr_oper_supported,
	efi_pci_io_attr_oper_maximum
}efi_pci_io_protocol_attribute_operation;
typedef efi_status(efiapi*efi_pci_io_protocol_poll_io_mem)(
	efi_pci_io_protocol       *this,
	efi_pci_io_protocol_width width,
	uint8_t                   bar,
	uint64_t                  offset,
	uint64_t                  mask,
	uint64_t                  value,
	uint64_t                  delay,
	uint64_t                  *result
);
typedef efi_status(efiapi*efi_pci_io_protocol_io_mem)(
	efi_pci_io_protocol       *this,
	efi_pci_io_protocol_width width,
	uint8_t                   bar,
	uint64_t                  offset,
	uintn_t                   count,
	void                      *buffer
);
typedef efi_status(efiapi*efi_pci_io_protocol_config)(
	efi_pci_io_protocol       *this,
	efi_pci_io_protocol_width width,
	uint32_t                  offset,
	uintn_t                   count,
	void                      *buffer
);
typedef efi_status(efiapi*efi_pci_io_protocol_copy_mem)(
	efi_pci_io_protocol       *this,
	efi_pci_io_protocol_width width,
	uint8_t                   dest_bar,
	uint64_t                  dest_offset,
	uint8_t                   src_bar,
	uint64_t                  src_offset,
	uintn_t                   count
);
typedef efi_status(efiapi*efi_pci_io_protocol_map)(
	efi_pci_io_protocol            *this,
	efi_pci_io_protocol_operation  oper,
	void                           *host,
	uintn_t                        *bytes,
	efi_address                    *device,
	void                           **mapping
);
typedef efi_status(efiapi*efi_pci_io_protocol_unmap)(
	efi_pci_io_protocol *this,
	void                *mapping
);
typedef efi_status(efiapi*efi_pci_io_protocol_allocate_buffer)(
	efi_pci_io_protocol *this,
	efi_allocate_type   type,
	efi_memory_type     memory,
	uintn_t             pages,
	void                **host,
	uint64_t            attrs
);
typedef efi_status(efiapi*efi_pci_io_protocol_free_buffer)(
	efi_pci_io_protocol *this,
	uintn_t             pages,
	void                *host
);
typedef efi_status(efiapi*efi_pci_io_protocol_flush)(
	efi_pci_io_protocol*this
);
typedef efi_status(efiapi*efi_pci_io_protocol_get_location)(
	efi_pci_io_protocol *this,
	uintn_t             *segment,
	uintn_t             *bus,
	uintn_t             *device,
	uintn_t             *func
);
typedef efi_status(efiapi*efi_pci_io_protocol_attributes)(
	efi_pci_io_protocol                      This,
	efi_pci_io_protocol_attribute_operation  oper,
	uint64_t                                 attrs,
	uint64_t                                 *result
);
typedef efi_status(efiapi*efi_pci_io_protocol_get_bar_attributes)(
	efi_pci_io_protocol *this,
	uint8_t             bar,
	uint64_t            *supports,
	void                **resources
);
typedef efi_status(efiapi*efi_pci_io_protocol_set_bar_attributes)(
	efi_pci_io_protocol *this,
	uint64_t            attributes,
	uint8_t             bar,
	uint64_t            *offset,
	uint64_t            *length
);
typedef struct efi_pci_io_protocol_access{
	efi_pci_io_protocol_io_mem read;
	efi_pci_io_protocol_io_mem write;
}efi_pci_io_protocol_access;
typedef struct efi_pci_io_protocol_config_access{
	efi_pci_io_protocol_config read;
	efi_pci_io_protocol_config write;
}efi_pci_io_protocol_config_access;
struct efi_pci_io_protocol{
	efi_pci_io_protocol_poll_io_mem         poll_mem;
	efi_pci_io_protocol_poll_io_mem         poll_io;
	efi_pci_io_protocol_access              mem;
	efi_pci_io_protocol_access              io;
	efi_pci_io_protocol_config_access       pci;
	efi_pci_io_protocol_copy_mem            copy_mem;
	efi_pci_io_protocol_map                 map;
	efi_pci_io_protocol_unmap               unmap;
	efi_pci_io_protocol_allocate_buffer     alloc_buffer;
	efi_pci_io_protocol_free_buffer         free_buffer;
	efi_pci_io_protocol_flush               flush;
	efi_pci_io_protocol_get_location        get_location;
	efi_pci_io_protocol_attributes          attributes;
	efi_pci_io_protocol_get_bar_attributes  get_bar_attrs;
	efi_pci_io_protocol_set_bar_attributes  set_bar_attrs;
	uint64_t                                rom_size;
	void                                    *rom_image;
};
typedef struct efi_pci_root_bridge_io_protocol efi_pci_root_bridge_io_protocol;
typedef enum efi_pci_root_bridge_io_protocol_operation{
	pciop_master_read,
	pciop_master_write,
	pciop_master_common_buffer,
	pciop_master_read64,
	pciop_master_write64,
	pciop_master_common_buffer64,
	pciop_max
}efi_pci_root_bridge_io_protocol_operation;
#define EFI_PCI_ATTRIBUTE_ISA_MOTHERBOARD_IO    0x0001
#define EFI_PCI_ATTRIBUTE_ISA_IO                0x0002
#define EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO        0x0004
#define EFI_PCI_ATTRIBUTE_VGA_MEMORY            0x0008
#define EFI_PCI_ATTRIBUTE_VGA_IO                0x0010
#define EFI_PCI_ATTRIBUTE_IDE_PRIMARY_IO        0x0020
#define EFI_PCI_ATTRIBUTE_IDE_SECONDARY_IO      0x0040
#define EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE  0x0080
#define EFI_PCI_ATTRIBUTE_MEMORY_CACHED         0x0800
#define EFI_PCI_ATTRIBUTE_MEMORY_DISABLE        0x1000
#define EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE    0x8000
#define EFI_PCI_ATTRIBUTE_ISA_IO_16             0x10000
#define EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO_16     0x20000
#define EFI_PCI_ATTRIBUTE_VGA_IO_16             0x40000
#define EFI_PCI_ATTRIBUTE_VALID_FOR_ALLOCATE_BUFFER  \
	(EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE|EFI_PCI_ATTRIBUTE_MEMORY_CACHED|EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE)
#define EFI_PCI_ATTRIBUTE_INVALID_FOR_ALLOCATE_BUFFER  (~EFI_PCI_ATTRIBUTE_VALID_FOR_ALLOCATE_BUFFER)
#define EFI_PCI_ADDRESS(bus,dev,func,reg) (uint64_t)(\
	(((uintn_t)bus)<<24)|\
	(((uintn_t)dev)<<16)|\
	(((uintn_t)func)<<8)|\
	(((uintn_t)(reg))<256?((uintn_t)(reg)):(uint64_t)(((uint64_t)(reg))<<32ull))\
)
typedef struct efi_pci_root_bridge_io_protocol_pci_address{
	uint8_t reg;
	uint8_t func;
	uint8_t dev;
	uint8_t bus;
	uint32_t ext_reg;
}efi_pci_root_bridge_io_protocol_pci_address;
typedef efi_status(efiapi*efi_pci_root_bridge_io_protocol_poll_io_mem)(
	efi_pci_root_bridge_io_protocol*this,
	efi_pci_io_protocol_width width,
	uint64_t address,
	uint64_t mask,
	uint64_t value,
	uint64_t delay,
	uint64_t*result
);
typedef efi_status(efiapi*efi_pci_root_bridge_io_protocol_io_mem)(
	efi_pci_root_bridge_io_protocol*this,
	efi_pci_io_protocol_width width,
	uint64_t address,
	uintn_t count,
	void*buffer
);
typedef struct efi_pci_root_bridge_io_protocol_access{
	efi_pci_root_bridge_io_protocol_io_mem read;
	efi_pci_root_bridge_io_protocol_io_mem write;
}efi_pci_root_bridge_io_protocol_access;
typedef efi_status(efiapi*efi_pci_root_bridge_io_protocol_copy_mem)(
	efi_pci_root_bridge_io_protocol*this,
	efi_pci_io_protocol_width width,
	uint64_t dst,uint64_t src,uintn_t count
);
typedef efi_status(efiapi*efi_pci_root_bridge_io_protocol_map)(
	efi_pci_root_bridge_io_protocol*this,
	efi_pci_root_bridge_io_protocol_operation op,
	void*host_add,uintn_t*count,
	efi_address*dev_addr,void**mapping
);
typedef efi_status(efiapi*efi_pci_root_bridge_io_protocol_unmap)(
	efi_pci_root_bridge_io_protocol*this,
	void*mapping
);
typedef efi_status(efiapi*efi_pci_root_bridge_io_protocol_allocate_buffer)(
	efi_pci_root_bridge_io_protocol*this,
	efi_allocate_type type,
	efi_memory_type memory_type,
	uintn_t pages,
	void**host_addr,
	uint64_t attr
);
typedef efi_status(efiapi*efi_pci_root_bridge_io_protocol_free_buffer)(
	efi_pci_root_bridge_io_protocol*this,
	uintn_t pages,void*host_addr
);
typedef efi_status(efiapi*efi_pci_root_bridge_io_protocol_flush)(
	efi_pci_root_bridge_io_protocol*this
);
typedef efi_status(efiapi*efi_pci_root_bridge_io_protocol_get_attributes)(
	efi_pci_root_bridge_io_protocol*this,
	uint64_t*supports,
	uint64_t*attributes
);
typedef efi_status(efiapi*efi_pci_root_bridge_io_protocol_set_attributes)(
	efi_pci_root_bridge_io_protocol*this,
	uint64_t attr,uint64_t*res_base,uint64_t*res_len
);
typedef efi_status(efiapi*efi_pci_root_bridge_io_protocol_configuration)(
	efi_pci_root_bridge_io_protocol*this,void**res
);
struct efi_pci_root_bridge_io_protocol{
	efi_handle                                         parent_handle;
	efi_pci_root_bridge_io_protocol_poll_io_mem        poll_mem;
	efi_pci_root_bridge_io_protocol_poll_io_mem        poll_io;
	efi_pci_root_bridge_io_protocol_access             mem;
	efi_pci_root_bridge_io_protocol_access             io;
	efi_pci_root_bridge_io_protocol_access             pci;
	efi_pci_root_bridge_io_protocol_copy_mem           copy_mem;
	efi_pci_root_bridge_io_protocol_map                map;
	efi_pci_root_bridge_io_protocol_unmap              unmap;
	efi_pci_root_bridge_io_protocol_allocate_buffer    alloc_buffer;
	efi_pci_root_bridge_io_protocol_free_buffer        free_buffer;
	efi_pci_root_bridge_io_protocol_flush              flush;
	efi_pci_root_bridge_io_protocol_get_attributes     get_attrs;
	efi_pci_root_bridge_io_protocol_set_attributes     set_attrs;
	efi_pci_root_bridge_io_protocol_configuration      config;
	uint32_t                                           seg_num;
};
extern efi_guid gEfiPciRootBridgeIoProtocolGuid;
extern efi_guid gEfiPciIoProtocolGuid;
#endif
