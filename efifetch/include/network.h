#ifndef EFI_NETWORK_H
#define EFI_NETWORK_H
#include"efi.h"
typedef struct efi_simple_network_protocol efi_simple_network_protocol;
typedef efi_simple_network_protocol efi_simple_network;
typedef struct efi_network_statistics{
	uint64_t rx_total_frames;
	uint64_t rx_good_frames;
	uint64_t rx_undersize_frames;
	uint64_t rx_oversize_frames;
	uint64_t rx_dropped_frames;
	uint64_t rx_unicast_frames;
	uint64_t rx_broadcast_frames;
	uint64_t rx_multicast_frames;
	uint64_t rx_crcError_frames;
	uint64_t rx_total_bytes;
	uint64_t tx_total_frames;
	uint64_t tx_good_frames;
	uint64_t tx_undersize_frames;
	uint64_t tx_oversize_frames;
	uint64_t tx_dropped_frames;
	uint64_t tx_unicast_frames;
	uint64_t tx_broadcast_frames;
	uint64_t tx_multicast_frames;
	uint64_t tx_crc_error_frames;
	uint64_t tx_total_bytes;
	uint64_t collisions;
	uint64_t unsupported_protocol;
	uint64_t rx_duplicated_frames;
	uint64_t rx_decrypt_error_frames;
	uint64_t tx_error_frames;
	uint64_t tx_retry_frames;
}efi_network_statistics;
typedef enum efi_simple_network_state{
	efi_simple_network_stopped,
	efi_simple_network_started,
	efi_simple_network_initialized,
	efi_simple_network_max_state
}efi_simple_network_state;
#define EFI_SIMPLE_NETWORK_RECEIVE_UNICAST                0x01
#define EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST              0x02
#define EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST              0x04
#define EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS            0x08
#define EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS_MULTICAST  0x10
#define EFI_SIMPLE_NETWORK_RECEIVE_INTERRUPT              0x01
#define EFI_SIMPLE_NETWORK_TRANSMIT_INTERRUPT             0x02
#define EFI_SIMPLE_NETWORK_COMMAND_INTERRUPT              0x04
#define EFI_SIMPLE_NETWORK_SOFTWARE_INTERRUPT             0x08
#define MAX_MCAST_FILTER_CNT                              16
typedef struct efi_simple_network_mode{
	uint32_t        state;
	uint32_t        hw_addr_size;
	uint32_t        media_header_size;
	uint32_t        max_packet_size;
	uint32_t        nv_ram_size;
	uint32_t        nv_ram_access_size;
	uint32_t        receive_filter_mask;
	uint32_t        receive_filter_setting;
	uint32_t        max_mcast_filter_count;
	uint32_t        mcast_filter_count;
	efi_mac_address mcast_filter[MAX_MCAST_FILTER_CNT];
	efi_mac_address cur_addr;
	efi_mac_address broadcast_addr;
	efi_mac_address perm_addr;
	uint8_t         if_type;
	bool            mac_addr_changeable;
	bool            multi_tx_supported;
	bool            media_present_supported;
	bool            media_present;
}efi_simple_network_mode;
typedef efi_status(efiapi*efi_simple_network_start)(
	efi_simple_network_protocol*proto
);
typedef efi_status(efiapi*efi_simple_network_stop)(
	efi_simple_network_protocol*proto
);
typedef efi_status(efiapi*efi_simple_network_initialize)(
	efi_simple_network_protocol*proto,
	uintn_t extra_rx_buf_size,
	uintn_t extra_tx_buf_size
);
typedef efi_status(efiapi*efi_simple_network_reset)(
	efi_simple_network_protocol*proto,
	bool ext_verify
);
typedef efi_status(efiapi*efi_simple_network_shutdown)(
	efi_simple_network_protocol*proto
);
typedef efi_status(efiapi*efi_simple_network_receive_filters)(
	efi_simple_network_protocol *proto,
	uint32_t                    enable,
	uint32_t                    disable,
	bool                        reset_mcast_filter,
	uintn_t                     mcast_filter_cnt,
	efi_mac_address             *mcast_filter
);
typedef efi_status(efiapi*efi_simple_network_station_address)(
	efi_simple_network_protocol *proto,
	bool                        reset,
	efi_mac_address             *new
);
typedef efi_status(efiapi*efi_simple_network_statistics)(
	efi_simple_network_protocol *proto,
	bool                        reset,
	uintn_t                     *size,
	efi_network_statistics      *table
);
typedef efi_status(efiapi*efi_simple_network_mcast_ip_to_mac)(
	efi_simple_network_protocol *proto,
	bool                        ipv6,
	efi_ip_address              *ip,
	efi_mac_address             *mac
);
typedef efi_status(efiapi*efi_simple_network_nvdata)(
	efi_simple_network_protocol *proto,
	bool                        rw,
	uintn_t                     offset,
	uintn_t                     size,
	void                        *buf
);
typedef efi_status(efiapi*efi_simple_network_get_status)(
	efi_simple_network_protocol *proto,
	uint32_t                    *int_status,
	void                        **tx_buf
);
typedef efi_status(efiapi*efi_simple_network_transmit)(
	efi_simple_network_protocol *proto,
	uintn_t                     hdr_size,
	uintn_t                     buf_size,
	void                        *buf,
	efi_mac_address             *src_addr,
	efi_mac_address             *dest_addr,
	uint16_t                    *protocol
);
typedef efi_status(efiapi*efi_simple_network_receive)(
	efi_simple_network_protocol *proto,
	uintn_t                     *hdr_size,
	uintn_t                     *buf_size,
	void                        *buf,
	efi_mac_address             *src_addr,
	efi_mac_address             *dest_addr,
	uint16_t                    *protocol
);
#define EFI_SIMPLE_NETWORK_PROTOCOL_REVISION 0x00010000
#define EFI_SIMPLE_NETWORK_INTERFACE_REVISION EFI_SIMPLE_NETWORK_PROTOCOL_REVISION
struct efi_simple_network_protocol{
	uint64_t                            revision;
	efi_simple_network_start            start;
	efi_simple_network_stop             stop;
	efi_simple_network_initialize       initialize;
	efi_simple_network_reset            reset;
	efi_simple_network_shutdown         shutdown;
	efi_simple_network_receive_filters  receive_filters;
	efi_simple_network_station_address  station_address;
	efi_simple_network_statistics       statistics;
	efi_simple_network_mcast_ip_to_mac  mcast_ip_to_mac;
	efi_simple_network_nvdata           nvdata;
	efi_simple_network_get_status       getstatus;
	efi_simple_network_transmit         transmit;
	efi_simple_network_receive          receive;
	efi_event                           wait_for_packet;
	efi_simple_network_mode             *mode;
};
typedef struct efi_managed_network_protocol efi_managed_network_protocol;
typedef struct efi_managed_network_config_data{
	uint32_t received_queue_timeout;
	uint32_t transmit_queue_timeout;
	uint16_t protocol_type_filter;
	bool enable_unicast_receive;
	bool enable_multicast_receive;
	bool enable_broadcast_receive;
	bool enable_promiscuous_receive;
	bool flush_queue_son_reset;
	bool enable_receive_timestamps;
	bool disable_background_polling;
}efi_managed_network_config_data;
typedef struct efi_managed_network_receive_data{
	efi_time timestamp;
	efi_event recycle_event;
	uint32_t pkt_len;
	uint32_t hdr_len;
	uint32_t addr_len;
	uint32_t data_len;
	bool broadcast_flag;
	bool multicast_flag;
	bool promiscuous_flag;
	uint16_t proto_type;
	void*dest_addr;
	void*src_addr;
	void*media_hdr;
	void*pkt_data;
}efi_managed_network_receive_data;
typedef struct efi_managed_network_fragment_data{
	uint32_t frag_len;
	void*frag_buffer;
}efi_managed_network_fragment_data;
typedef struct efi_managed_network_transmit_data{
	efi_mac_address*dest_addr;
	efi_mac_address*src_addr;
	uint16_t proto_type;
	uint32_t data_len;
	uint16_t hdr_len;
	uint16_t frag_count;
	efi_managed_network_fragment_data frag_table[0];
}efi_managed_network_transmit_data;
typedef struct efi_managed_network_completion_token{
	efi_event  event;
	efi_status status;
	union{
		efi_managed_network_receive_data  *rx;
		efi_managed_network_transmit_data *tx;
	}packet;
}efi_managed_network_completion_token;
typedef efi_status(efiapi*efi_managed_network_get_mode_data)(
	efi_managed_network_protocol    *this,
	efi_managed_network_config_data *mnp,
	efi_simple_network_mode         *snp
);
typedef efi_status(efiapi*efi_managed_network_configure)(
	efi_managed_network_protocol    *this,
	efi_managed_network_config_data *mnp
);
typedef efi_status(efiapi*efi_managed_network_mcast_ip_to_mac)(
	efi_managed_network_protocol *this,
	bool                         ipv6_flag,
	efi_ip_address               *ip,
	efi_mac_address              *mac
);
typedef efi_status(efiapi*efi_managed_network_groups)(
	efi_managed_network_protocol *this,
	bool                         join_flag,
	efi_mac_address              *mac
);

typedef efi_status(efiapi*efi_managed_network_transmit)(
	efi_managed_network_protocol         *this,
	efi_managed_network_completion_token *token
);
typedef efi_status(efiapi*efi_managed_network_receive)(
	efi_managed_network_protocol         *this,
	efi_managed_network_completion_token *token
);
typedef efi_status(efiapi*efi_managed_network_cancel)(
	efi_managed_network_protocol         *this,
	efi_managed_network_completion_token *token
);
typedef efi_status(efiapi*efi_managed_network_poll)(
	efi_managed_network_protocol*this
);
struct efi_managed_network_protocol{
	efi_managed_network_get_mode_data   get_mode_data;
	efi_managed_network_configure       configure;
	efi_managed_network_mcast_ip_to_mac mcast_ip_to_mac;
	efi_managed_network_groups          groups;
	efi_managed_network_transmit        transmit;
	efi_managed_network_receive         receive;
	efi_managed_network_cancel          cancel;
	efi_managed_network_poll            poll;
};
typedef struct efi_ip4_protocol efi_ip4_protocol;
typedef struct efi_ip4_address_pair{
	efi_handle       instance;
	efi_ipv4_address address;
	efi_ipv4_address subnet_mask;
}efi_ip4_address_pair;
typedef struct efi_ip4_variable_data{
	efi_handle           driver;
	uint32_t             addr_count;
	efi_ip4_address_pair addr_pairs[0];
}efi_ip4_variable_data;
typedef struct efi_ip4_config_data{
	uint8_t default_proto;
	bool accept_any_proto;
	bool accept_icmp_errors;
	bool accept_broadcast;
	bool accept_promiscuous;
	bool use_default_addr;
	efi_ipv4_address station_addr;
	efi_ipv4_address subnet_mask;
	uint8_t tos;
	uint8_t ttl;
	bool do_not_fragment;
	bool raw_data;
	uint32_t receive_timeout;
	uint32_t transmit_timeout;
}efi_ip4_config_data;
typedef struct efi_ip4_route_table{
	efi_ipv4_address subnet_addr;
	efi_ipv4_address subnet_mask;
	efi_ipv4_address nexthop;
}efi_ip4_route_table;
typedef struct efi_ip4_icmp_type{
	uint8_t type;
	uint8_t code;
}efi_ip4_icmp_type;
typedef struct efi_ip4_mode_data{
	bool                is_started;
	uint32_t            max_pkt_size;
	efi_ip4_config_data config;
	bool                is_configured;
	uint32_t            group_count;
	efi_ipv4_address    *group_table;
	uint32_t            route_count;
	efi_ip4_route_table *route_table;
	uint32_t            icmp_type_count;
	efi_ip4_icmp_type   *icmp_type_list;
}efi_ip4_mode_data;
typedef struct efi_ip4_header{
	uint8_t          hdr_len:4;
	uint8_t          version:4;
	uint8_t          tos;
	uint16_t         total_len;
	uint16_t         identification;
	uint16_t         fragmentation;
	uint8_t          ttl;
	uint8_t          protocol;
	uint16_t         checksum;
	efi_ipv4_address src;
	efi_ipv4_address dst;
}__packed efi_ip4_header;
typedef struct efi_ip4_fragment_data{
	uint32_t len;
	void*buffer;
}efi_ip4_fragment_data;
typedef struct efi_ip4_receive_data{
	efi_time               timestamp;
	efi_event              recycle_signal;
	uint32_t               hdr_len;
	efi_ip4_header         *hdr;
	uint32_t               opts_len;
	void                   *opts;
	uint32_t               data_len;
	uint32_t               frag_count;
	efi_ip4_fragment_data  frag_table[0];
}efi_ip4_receive_data;
typedef struct efi_ip4_override_data{
	efi_ipv4_address src;
	efi_ipv4_address gateway;
	uint8_t          proto;
	uint8_t          tos;
	uint8_t          ttl;
	bool             do_not_fragment;
}efi_ip4_override_data;
typedef struct efi_ip4_transmit_data{
	efi_ipv4_address       dst;
	efi_ip4_override_data  *override;
	uint32_t               opts_len;
	void                   *opts_buff;
	uint32_t               total_data_len;
	uint32_t               frag_count;
	efi_ip4_fragment_data  frag_table[0];
}efi_ip4_transmit_data;
typedef struct efi_ip4_completion_token{
	efi_event event;
	efi_status status;
	union{
		efi_ip4_receive_data  *rx;
		efi_ip4_transmit_data *tx;
	}packet;
}efi_ip4_completion_token;
typedef efi_status(efiapi*efi_ip4_get_mode_data)(
	const efi_ip4_protocol          *this,
	efi_ip4_mode_data               *mode,
	efi_managed_network_config_data *mnp,
	efi_simple_network_mode         *snp
);
typedef efi_status(efiapi*efi_ip4_configure)(
	efi_ip4_protocol    *this,
	efi_ip4_config_data *config
);
typedef efi_status(efiapi*efi_ip4_groups)(
	efi_ip4_protocol *this,
	bool             join_flag,
	efi_ipv4_address *group_addr
);
typedef efi_status(efiapi*efi_ip4_routes)(
	efi_ip4_protocol *this,
	bool             delete_route,
	efi_ipv4_address *subnet_addr,
	efi_ipv4_address *subnet_mask,
	efi_ipv4_address *gateway
);
typedef efi_status(efiapi*efi_ip4_transmit)(
	efi_ip4_protocol         *this,
	efi_ip4_completion_token *token
);
typedef efi_status(efiapi*efi_ip4_receive)(
	efi_ip4_protocol         *this,
	efi_ip4_completion_token *token
);
typedef efi_status(efiapi*efi_ip4_cancel)(
	efi_ip4_protocol         *this,
	efi_ip4_completion_token *token
);
typedef efi_status(efiapi*efi_ip4_poll)(
	efi_ip4_protocol *this
);
struct efi_ip4_protocol{
	efi_ip4_get_mode_data get_mode_data;
	efi_ip4_configure     configure;
	efi_ip4_groups        groups;
	efi_ip4_routes        routes;
	efi_ip4_transmit      transmit;
	efi_ip4_receive       receive;
	efi_ip4_cancel        cancel;
	efi_ip4_poll          poll;
};
typedef struct efi_ip4_config_protocol efi_ip4_config_protocol;
#define IP4_CONFIG_VARIABLE_ATTRIBUTES (EFI_VARIABLE_NON_VOLATILE|EFI_VARIABLE_BOOTSERVICE_ACCESS)
typedef struct efi_ip4_ipconfig_data{
	efi_ipv4_address    station_addr;
	efi_ipv4_address    subnet_mask;
	uint32_t            route_table_size;
	efi_ip4_route_table *route_table;
}efi_ip4_ipconfig_data;
typedef efi_status(efiapi*efi_ip4_config_start)(
	efi_ip4_config_protocol *this,
	efi_event               done,
	efi_event               re_config
);
typedef efi_status(efiapi*efi_ip4_config_stop)(
	efi_ip4_config_protocol *this
);
typedef efi_status(efiapi*efi_ip4_config_get_data)(
	efi_ip4_config_protocol *this,
	uintn_t                 *size,
	efi_ip4_ipconfig_data   *data
);
struct efi_ip4_config_protocol{
	efi_ip4_config_start    start;
	efi_ip4_config_stop     stop;
	efi_ip4_config_get_data get_data;
};
typedef struct efi_ip4_config2_protocol efi_ip4_config2_protocol;
typedef enum efi_ip4_config2_data_type{
	ip4cfg2_type_int_info,
	ip4cfg2_type_policy,
	ip4cfg2_type_man_addr,
	ip4cfg2_type_gateway,
	ip4cfg2_type_dns,
	ip4cfg2_type_max
}efi_ip4_config2_data_type;
#define EFI_IP4_CONFIG2_INTERFACE_INFO_NAME_SIZE 32
typedef struct{
	char16              name[EFI_IP4_CONFIG2_INTERFACE_INFO_NAME_SIZE];
	uint8_t             if_type;
	uint32_t            hw_addr_size;
	efi_mac_address     hw_addr;
	efi_ipv4_address    station_addr;
	efi_ipv4_address    subnet_mask;
	uint32_t            route_table_size;
	efi_ip4_route_table *route_table;
}efi_ip4_config2_interface_info;
typedef enum efi_ip4_config2_policy{
	ip4cfg2_policy_static,
	ip4cfg2_policy_dhcp,
	ip4cfg2_policy_max
}efi_ip4_config2_policy;
typedef struct efi_ip4_config2_manual_address{
	efi_ipv4_address addr;
	efi_ipv4_address subnet_mask;
}efi_ip4_config2_manual_address;
typedef efi_status(efiapi*efi_ip4_config2_set_data)(
	efi_ip4_config2_protocol   *this,
	efi_ip4_config2_data_type  type,
	uintn_t                    size,
	void                       *data
);
typedef efi_status(efiapi*efi_ip4_config2_get_data)(
	efi_ip4_config2_protocol  *this,
	efi_ip4_config2_data_type type,
	uintn_t                   *size,
	void                      *data
);
typedef efi_status(efiapi*efi_ip4_config2_register_notify)(
	efi_ip4_config2_protocol  *this,
	efi_ip4_config2_data_type type,
	efi_event                 event
);
typedef efi_status(efiapi*efi_ip4_config2_unregister_notify)(
	efi_ip4_config2_protocol  *this,
	efi_ip4_config2_data_type type,
	efi_event                 event
);
struct efi_ip4_config2_protocol{
	efi_ip4_config2_set_data          set_data;
	efi_ip4_config2_get_data          get_data;
	efi_ip4_config2_register_notify   register_data_notify;
	efi_ip4_config2_unregister_notify unregister_data_notify;
};
typedef struct efi_ip6_protocol efi_ip6_protocol;
typedef struct efi_ip6_address_pair{
	efi_handle       instance;
	efi_ipv6_address address;
	uint8_t          prefix;
}efi_ip6_address_pair;
typedef struct efi_ip6_variable_data{
	efi_handle           driver;
	uint32_t             addr_count;
	efi_ip6_address_pair addr_pairs[0];
}efi_ip6_variable_data;
#define ICMP_V6_DEST_UNREACHABLE                 0x1
#define ICMP_V6_PACKET_TOO_BIG                   0x2
#define ICMP_V6_TIME_EXCEEDED                    0x3
#define ICMP_V6_PARAMETER_PROBLEM                0x4
#define ICMP_V6_ECHO_REQUEST                     0x80
#define ICMP_V6_ECHO_REPLY                       0x81
#define ICMP_V6_LISTENER_QUERY                   0x82
#define ICMP_V6_LISTENER_REPORT                  0x83
#define ICMP_V6_LISTENER_DONE                    0x84
#define ICMP_V6_ROUTER_SOLICIT                   0x85
#define ICMP_V6_ROUTER_ADVERTISE                 0x86
#define ICMP_V6_NEIGHBOR_SOLICIT                 0x87
#define ICMP_V6_NEIGHBOR_ADVERTISE               0x88
#define ICMP_V6_REDIRECT                         0x89
#define ICMP_V6_LISTENER_REPORT_2                0x8F
#define ICMP_V6_NO_ROUTE_TO_DEST                 0x0
#define ICMP_V6_COMM_PROHIBITED                  0x1
#define ICMP_V6_BEYOND_SCOPE                     0x2
#define ICMP_V6_ADDR_UNREACHABLE                 0x3
#define ICMP_V6_PORT_UNREACHABLE                 0x4
#define ICMP_V6_SOURCE_ADDR_FAILED               0x5
#define ICMP_V6_ROUTE_REJECTED                   0x6
#define ICMP_V6_TIMEOUT_HOP_LIMIT                0x0
#define ICMP_V6_TIMEOUT_REASSEMBLE               0x1
#define ICMP_V6_ERRONEOUS_HEADER                 0x0
#define ICMP_V6_UNRECOGNIZE_NEXT_HDR             0x1
#define ICMP_V6_UNRECOGNIZE_OPTION               0x2
typedef struct efi_ip6_config_data{
	uint8_t default_proto;
	bool accept_any_proto;
	bool accept_icmp_errors;
	bool accept_promiscuous;
	efi_ipv6_address dest_addr;
	efi_ipv6_address station_addr;
	uint8_t traffic_class;
	uint8_t hop_limit;
	uint32_t flow_label;
	uint32_t receive_timeout;
	uint32_t transmit_timeout;
}efi_ip6_config_data;
typedef struct efi_ip6_address_info{
	efi_ipv6_address addr;
	uint8_t          prefix;
}efi_ip6_address_info;
typedef struct efi_ip6_route_table{
	efi_ipv6_address gateway;
	efi_ipv6_address dest;
	uint8_t          prefix;
}efi_ip6_route_table;
typedef enum efi_ip6_neighbor_state{
	efi_ip6_neigh_incomplete,
	efi_ip6_neigh_reachable,
	efi_ip6_neigh_stale,
	efi_ip6_neigh_delay,
	efi_ip6_neigh_probe
}efi_ip6_neighbor_state;
typedef struct efi_ip6_neighbor_cache{
	efi_ipv6_address        neighbor;
	efi_mac_address         link_addr;
	efi_ip6_neighbor_state  state;
}efi_ip6_neighbor_cache;
typedef struct efi_ip6_icmp_type{
	uint8_t type;
	uint8_t code;
}efi_ip6_icmp_type;
typedef struct efi_ip6_mode_data{
	bool                   is_started;
	uint32_t               max_pkt_size;
	efi_ip6_config_data    config;
	bool                   is_configured;
	uint32_t               addr_count;
	efi_ip6_address_info   *addr_list;
	uint32_t               group_count;
	efi_ipv6_address       *group_table;
	uint32_t               route_count;
	efi_ip6_route_table    *route_table;
	uint32_t               neighbor_count;
	efi_ip6_neighbor_cache *neighbor_cache;
	uint32_t               prefix_count;
	efi_ip6_address_info   *prefix_table;
	uint32_t               icmp_type_count;
	efi_ip6_icmp_type      *icmp_type_list;
}efi_ip6_mode_data;
typedef struct efi_ip6_header{
	uint8_t          traffic_class_h:4;
	uint8_t          version:4;
	uint8_t          flow_label_h:4;
	uint8_t          traffic_class_l:4;
	uint16_t         flow_label_l;
	uint16_t         payload_len;
	uint8_t          next_hdr;
	uint8_t          hop_limit;
	efi_ipv6_address src_addr;
	efi_ipv6_address dst_addr;
}__packed efi_ip6_header;
typedef struct efi_ip6_fragment_data{
	uint32_t len;
	void     *buf;
}efi_ip6_fragment_data;
typedef struct efi_ip6_receive_data{
	efi_time              timestamp;
	efi_event             recycle_signal;
	uint32_t              hdr_len;
	efi_ip6_header        *hdr;
	uint32_t              data_len;
	uint32_t              frag_count;
	efi_ip6_fragment_data frag_table[0];
}efi_ip6_receive_data;
typedef struct efi_ip6_override_data{
	uint8_t  proto;
	uint8_t  hop_limit;
	uint32_t flow_label;
}efi_ip6_override_data;
typedef struct efi_ip6_transmit_data{
	efi_ipv6_address      dest_addr;
	efi_ip6_override_data *override_data;
	uint32_t              ext_hdrs_len;
	void                  *ext_hdrs;
	uint8_t               next_hdr;
	uint32_t              data_len;
	uint32_t              frag_count;
	efi_ip6_fragment_data frag_table[0];
}efi_ip6_transmit_data;
typedef struct efi_ip6_completion_token{
	efi_event  event;
	efi_status status;
	union{
		efi_ip6_receive_data  *rx;
		efi_ip6_transmit_data *tx;
	}packet;
}efi_ip6_completion_token;
typedef efi_status(efiapi*efi_ip6_get_mode_data)(
	efi_ip6_protocol                *this,
	efi_ip6_mode_data               *mode,
	efi_managed_network_config_data *mnp,
	efi_simple_network_mode         *snp
);
typedef efi_status(efiapi*efi_ip6_configure)(
	efi_ip6_protocol    *this,
	efi_ip6_config_data *config
);
typedef efi_status(efiapi*efi_ip6_groups)(
	efi_ip6_protocol *this,
	bool             join_flag,
	efi_ipv6_address *group_addr
);
typedef efi_status(efiapi*efi_ip6_routes)(
	efi_ip6_protocol *this,
	bool             delete_route,
	efi_ipv6_address *dst,
	uint8_t          prefix,
	efi_ipv6_address *gateway
);
typedef efi_status(efiapi*efi_ip6_neighbors)(
	efi_ip6_protocol *this,
	bool             delete_flag,
	efi_ipv6_address *target_ip6_addr,
	efi_mac_address  *target_link_addr,
	uint32_t         timeout,
	bool             override
);
typedef efi_status(efiapi*efi_ip6_transmit)(
	efi_ip6_protocol         *this,
	efi_ip6_completion_token *token
);
typedef efi_status(efiapi*efi_ip6_receive)(
	efi_ip6_protocol         *this,
	efi_ip6_completion_token *token
);
typedef efi_status(efiapi*efi_ip6_cancel)(
	efi_ip6_protocol         *this,
	efi_ip6_completion_token *token
);
typedef efi_status(efiapi*efi_ip6_poll)(
	efi_ip6_protocol *this
);
struct efi_ip6_protocol{
	efi_ip6_get_mode_data   get_mode_data;
	efi_ip6_configure       configure;
	efi_ip6_groups          groups;
	efi_ip6_routes          routes;
	efi_ip6_neighbors       neighbors;
	efi_ip6_transmit        transmit;
	efi_ip6_receive         receive;
	efi_ip6_cancel          cancel;
	efi_ip6_poll            poll;
};
typedef struct efi_ip6_config_protocol efi_ip6_config_protocol;
typedef enum efi_ip6_config_data_type{
	ip6cfg_type_int_info,
	ip6cfg_type_alt_int_id,
	ip6cfg_type_policy,
	ip6cfg_type_dup_addr_detect_transmits,
	ip6cfg_type_manual_addr,
	ip6cfg_type_gateway,
	ip6cfg_type_dns,
	ip6cfg_type_max
}efi_ip6_config_data_type;
typedef struct efi_ip6_config_interface_info{
	char16                name[32];
	uint8_t               if_type;
	uint32_t              hw_addr_size;
	efi_mac_address       hw_addr;
	uint32_t              addr_info_count;
	efi_ip6_address_info  *addr_info;
	uint32_t              route_count;
	efi_ip6_route_table   *route_table;
}efi_ip6_config_interface_info;
typedef struct efi_ip6_config_interface_id{
	uint8_t id[8];
}efi_ip6_config_interface_id;
typedef enum efi_ip6_config_policy{
	ip6cfg_policy_manual,
	ip6cfg_policy_auto
}efi_ip6_config_policy;
typedef struct efi_ip6_config_dup_addr_detect_transmits{
	uint32_t dup_addr_detect_transmits;
}efi_ip6_config_dup_addr_detect_transmits;
typedef struct efi_ip6_config_manual_address{
	efi_ipv6_address addr;
	bool             is_anycast;
	uint8_t          prefix;
}efi_ip6_config_manual_address;
typedef efi_status(efiapi*efi_ip6_config_set_data)(
	efi_ip6_config_protocol  *this,
	efi_ip6_config_data_type data_type,
	uintn_t                  data_size,
	void                     *data
);
typedef efi_status(efiapi*efi_ip6_config_get_data)(
	efi_ip6_config_protocol  *this,
	efi_ip6_config_data_type data_type,
	uintn_t                  *data_size,
	void                     *data
);
typedef efi_status(efiapi*efi_ip6_config_register_notify)(
	efi_ip6_config_protocol  *this,
	efi_ip6_config_data_type data_type,
	efi_event                event
);
typedef efi_status(efiapi*efi_ip6_config_unregister_notify)(
	efi_ip6_config_protocol  *this,
	efi_ip6_config_data_type data_type,
	efi_event                event
);
struct efi_ip6_config_protocol{
	efi_ip6_config_set_data          set_data;
	efi_ip6_config_get_data          get_data;
	efi_ip6_config_register_notify   register_data_notify;
	efi_ip6_config_unregister_notify unregister_data_notify;
};
typedef struct efi_tcp4_protocol efi_tcp4_protocol;
typedef struct efi_tcp4_service_point{
	efi_handle       instance;
	efi_ipv4_address local_addr;
	uint16_t         local_port;
	efi_ipv4_address remote_addr;
	uint16_t         remote_port;
}efi_tcp4_service_point;
typedef struct efi_tcp4_variable_data{
	efi_handle             driver;
	uint32_t               count;
	efi_tcp4_service_point services[0];
}efi_tcp4_variable_data;
typedef struct efi_tcp4_access_point{
	bool             use_default_addr;
	efi_ipv4_address station_addr;
	efi_ipv4_address subnet_mask;
	uint16_t         station_port;
	efi_ipv4_address remote_addr;
	uint16_t         remote_port;
	bool             active_flag;
}efi_tcp4_access_point;
typedef struct efi_tcp4_option{
	uint32_t receive_buf_size;
	uint32_t send_buf_size;
	uint32_t max_syn_backlog;
	uint32_t conn_timeout;
	uint32_t data_retries;
	uint32_t fin_timeout;
	uint32_t time_wait_timeout;
	uint32_t keep_alive_probes;
	uint32_t keep_alive_time;
	uint32_t keep_alive_interval;
	bool enable_nagle;
	bool enable_timestamp;
	bool enable_window_scaling;
	bool enable_selective_ack;
	bool enable_path_mtu_discovery;
}efi_tcp4_option;
typedef struct efi_tcp4_config_data{
	uint8_t tos;
	uint8_t ttl;
	efi_tcp4_access_point access_point;
	efi_tcp4_option *ctrl_opt;
}efi_tcp4_config_data;
typedef enum efi_tcp4_connection_state{
	tcp4_state_closed       = 0,
	tcp4_state_listen       = 1,
	tcp4_state_syn_sent     = 2,
	tcp4_state_syn_received = 3,
	tcp4_state_established  = 4,
	tcp4_state_fin_wait1    = 5,
	tcp4_state_fin_wait2    = 6,
	tcp4_state_closing      = 7,
	tcp4_state_time_wait    = 8,
	tcp4_state_close_wait   = 9,
	tcp4_state_last_ack     = 10
}efi_tcp4_connection_state;
typedef struct efi_tcp4_completion_token{
	efi_event event;
	efi_status status;
}efi_tcp4_completion_token;
typedef struct efi_tcp4_connection_token{
	efi_tcp4_completion_token token;
}efi_tcp4_connection_token;
typedef struct efi_tcp4_listen_token{
	efi_tcp4_completion_token token;
	efi_handle new_child;
}efi_tcp4_listen_token;
typedef struct efi_tcp4_fragment_data{
	uint32_t len;
	void*buf;
}efi_tcp4_fragment_data;
typedef struct efi_tcp4_receive_data{
	bool urgent_flag;
	uint32_t data_len;
	uint32_t frag_count;
	efi_tcp4_fragment_data frag_table[0];
}efi_tcp4_receive_data;
typedef struct efi_tcp4_transmit_data{
	bool push;
	bool urgent;
	uint32_t data_len;
	uint32_t frag_count;
	efi_tcp4_fragment_data frag_table[0];
}efi_tcp4_transmit_data;
typedef struct efi_tcp4_io_token{
	efi_tcp4_completion_token token;
	union{
		efi_tcp4_receive_data  *rx;
		efi_tcp4_transmit_data *tx;
	}pkt;
}efi_tcp4_io_token;
typedef struct efi_tcp4_close_token{
	efi_tcp4_completion_token token;
	bool abort_on_close;
}efi_tcp4_close_token;
typedef efi_status(efiapi*efi_tcp4_get_mode_data)(
	efi_tcp4_protocol               *this,
	efi_tcp4_connection_state       *state,
	efi_tcp4_config_data            *config,
	efi_ip4_mode_data               *ipv4_mode,
	efi_managed_network_config_data *mnp,
	efi_simple_network_mode         *snp
);
typedef efi_status(efiapi*efi_tcp4_configure)(
	efi_tcp4_protocol    *this,
	efi_tcp4_config_data *config
);

typedef efi_status(efiapi*efi_tcp4_routes)(
	efi_tcp4_protocol *this,
	bool              delete_route,
	efi_ipv4_address  *subnet_addr,
	efi_ipv4_address  *subnet_mask,
	efi_ipv4_address  *gateway
);
typedef efi_status(efiapi*efi_tcp4_connect)(
	efi_tcp4_protocol         *this,
	efi_tcp4_connection_token *token
);
typedef efi_status(efiapi*efi_tcp4_accept)(
	efi_tcp4_protocol     *this,
	efi_tcp4_listen_token *token
);
typedef efi_status(efiapi*efi_tcp4_transmit)(
	efi_tcp4_protocol *this,
	efi_tcp4_io_token *token
);
typedef efi_status(efiapi*efi_tcp4_receive)(
	efi_tcp4_protocol *this,
	efi_tcp4_io_token *token
);
typedef efi_status(efiapi*efi_tcp4_close)(
	efi_tcp4_protocol    *this,
	efi_tcp4_close_token *token
);
typedef efi_status(efiapi*efi_tcp4_cancel)(
	efi_tcp4_protocol         *this,
	efi_tcp4_completion_token *token
);
typedef efi_status(efiapi*efi_tcp4_poll)(
	efi_tcp4_protocol*this
);
struct efi_tcp4_protocol{
	efi_tcp4_get_mode_data get_mode_data;
	efi_tcp4_configure     configure;
	efi_tcp4_routes        routes;
	efi_tcp4_connect       connect;
	efi_tcp4_accept        accept;
	efi_tcp4_transmit      transmit;
	efi_tcp4_receive       receive;
	efi_tcp4_close         close;
	efi_tcp4_cancel        cancel;
	efi_tcp4_poll          poll;
};
typedef struct efi_tcp6_protocol efi_tcp6_protocol;
typedef struct efi_tcp6_service_point{
	efi_handle       instance;
	efi_ipv6_address local_addr;
	uint16_t         local_port;
	efi_ipv6_address remote_addr;
	uint16_t         remote_port;
}efi_tcp6_service_point;
typedef struct efi_tcp6_variable_data{
	efi_handle driver;
	uint32_t service_count;
	efi_tcp6_service_point services[0];
}efi_tcp6_variable_data;
typedef struct efi_tcp6_access_point{
	efi_ipv6_address station_addr;
	uint16_t         station_port;
	efi_ipv6_address remote_addr;
	uint16_t         remote_port;
	bool             active_flag;
}efi_tcp6_access_point;
typedef struct efi_tcp6_option{
	uint32_t receive_buf_size;
	uint32_t send_buf_size;
	uint32_t max_syn_back_log;
	uint32_t conn_timeout;
	uint32_t data_retries;
	uint32_t fin_timeout;
	uint32_t time_wait_timeout;
	uint32_t keep_alive_probes;
	uint32_t keep_alive_time;
	uint32_t keep_alive_interval;
	bool enable_nagle;
	bool enable_time_stamp;
	bool enable_window_scaling;
	bool enable_selective_ack;
	bool enable_path_mtu_discovery;
}efi_tcp6_option;
typedef struct efi_tcp6_config_data{
	uint8_t               traffic_class;
	uint8_t               hop_limit;
	efi_tcp6_access_point access_point;
	efi_tcp6_option       *control_option;
}efi_tcp6_config_data;
typedef enum efi_tcp6_connection_state{
	tcp6_state_closed       = 0,
	tcp6_state_listen       = 1,
	tcp6_state_syn_sent     = 2,
	tcp6_state_syn_received = 3,
	tcp6_state_established  = 4,
	tcp6_state_fin_wait1    = 5,
	tcp6_state_fin_wait2    = 6,
	tcp6_state_closing      = 7,
	tcp6_state_time_wait    = 8,
	tcp6_state_close_wait   = 9,
	tcp6_state_last_ack     = 10
}efi_tcp6_connection_state;
typedef struct efi_tcp6_completion_token{
	efi_event   event;
	efi_status  status;
}efi_tcp6_completion_token;
typedef struct efi_tcp6_connection_token{
	efi_tcp6_completion_token token;
}efi_tcp6_connection_token;
typedef struct efi_tcp6_listen_token{
	efi_tcp6_completion_token token;
	efi_handle new_child;
}efi_tcp6_listen_token;
typedef struct efi_tcp6_fragment_data{
	uint32_t len;
	void *buf;
}efi_tcp6_fragment_data;
typedef struct efi_tcp6_receive_data{
	bool urgent_flag;
	uint32_t data_len;
	uint32_t frag_count;
	efi_tcp6_fragment_data frag_table[0];
}efi_tcp6_receive_data;
typedef struct efi_tcp6_transmit_data{
	bool push;
	bool urgent;
	uint32_t data_len;
	uint32_t frag_count;
	efi_tcp6_fragment_data frag_table[0];
}efi_tcp6_transmit_data;
typedef struct efi_tcp6_io_token{
	efi_tcp6_completion_token token;
	union{
		efi_tcp6_receive_data  *rx;
		efi_tcp6_transmit_data *tx;
	}pkt;
}efi_tcp6_io_token;
typedef struct efi_tcp6_close_token{
	efi_tcp6_completion_token token;
	bool abort_on_close;
}efi_tcp6_close_token;
typedef efi_status(efiapi*efi_tcp6_get_mode_data)(
	efi_tcp6_protocol               *this,
	efi_tcp6_connection_state       *state,
	efi_tcp6_config_data            *config,
	efi_ip6_mode_data               *mode,
	efi_managed_network_config_data *mnp,
	efi_simple_network_mode         *snp
);
typedef efi_status(efiapi*efi_tcp6_configure)(
	efi_tcp6_protocol    *this,
	efi_tcp6_config_data *config
);
typedef efi_status(efiapi*efi_tcp6_connect)(
	efi_tcp6_protocol         *this,
	efi_tcp6_connection_token *token
);
typedef efi_status(efiapi*efi_tcp6_accept)(
	efi_tcp6_protocol     *this,
	efi_tcp6_listen_token *token
);
typedef efi_status(efiapi*efi_tcp6_transmit)(
	efi_tcp6_protocol *this,
	efi_tcp6_io_token *token
);
typedef efi_status(efiapi*efi_tcp6_receive)(
	efi_tcp6_protocol *this,
	efi_tcp6_io_token *token
);
typedef efi_status(efiapi*efi_tcp6_close)(
	efi_tcp6_protocol    *this,
	efi_tcp6_close_token *token
);
typedef efi_status(efiapi*efi_tcp6_cancel)(
	efi_tcp6_protocol         *this,
	efi_tcp6_completion_token *token
);
typedef efi_status(efiapi*efi_tcp6_poll)(
	efi_tcp6_protocol *this
);
struct efi_tcp6_protocol{
	efi_tcp6_get_mode_data get_mode_data;
	efi_tcp6_configure     configure;
	efi_tcp6_connect       connect;
	efi_tcp6_accept        accept;
	efi_tcp6_transmit      transmit;
	efi_tcp6_receive       receive;
	efi_tcp6_close         close;
	efi_tcp6_cancel        cancel;
	efi_tcp6_poll          poll;
};
typedef struct efi_udp4_protocol efi_udp4_protocol;
typedef struct efi_udp4_service_point{
	efi_handle       instance;
	efi_ipv4_address local_addr;
	uint16_t         local_port;
	efi_ipv4_address remote_addr;
	uint16_t         remote_port;
}efi_udp4_service_point;
typedef struct efi_udp4_variable_data{
	efi_handle driver;
	uint32_t service_count;
	efi_udp4_service_point services[0];
}efi_udp4_variable_data;
typedef struct efi_udp4_fragment_data{
	uint32_t len;
	void*buf;
}efi_udp4_fragment_data;
typedef struct efi_udp4_session_data{
	efi_ipv4_address src_addr;
	uint16_t         src_port;
	efi_ipv4_address dest_addr;
	uint16_t         dest_port;
}efi_udp4_session_data;
typedef struct efi_udp4_config_data{
	bool             accept_broadcast;
	bool             accept_promiscuous;
	bool             accept_any_port;
	bool             allow_dup_port;
	uint8_t          tos;
	uint8_t          ttl;
	bool             do_not_frag;
	uint32_t         rx_timeout;
	uint32_t         tx_timeout;
	bool             use_default_addr;
	efi_ipv4_address station_addr;
	efi_ipv4_address subnet_mask;
	uint16_t         station_port;
	efi_ipv4_address remote_addr;
	uint16_t         remote_port;
}efi_udp4_config_data;
typedef struct efi_udp4_transmit_data{
	efi_udp4_session_data  *udp_session;
	efi_ipv4_address       *gateway;
	uint32_t               data_len;
	uint32_t               frag_count;
	efi_udp4_fragment_data frag_table[0];
}efi_udp4_transmit_data;
typedef struct efi_udp4_receive_data{
	efi_time               timestamp;
	efi_event              recycle_signal;
	efi_udp4_session_data  udp_session;
	uint32_t               data_len;
	uint32_t               frag_count;
	efi_udp4_fragment_data frag_table[0];
}efi_udp4_receive_data;
typedef struct efi_udp4_completion_token{
	efi_event event;
	efi_status status;
	union{
		efi_udp4_receive_data  *rx;
		efi_udp4_transmit_data *tx;
	}pkt;
}efi_udp4_completion_token;
typedef efi_status(efiapi*efi_udp4_get_mode_data)(
	efi_udp4_protocol               *this,
	efi_udp4_config_data            *config,
	efi_ip4_mode_data               *mode,
	efi_managed_network_config_data *mnp,
	efi_simple_network_mode         *snp
);
typedef efi_status(efiapi*efi_udp4_configure)(
	efi_udp4_protocol    *this,
	efi_udp4_config_data *config
);
typedef efi_status(efiapi*efi_udp4_groups)(
	efi_udp4_protocol *this,
	bool              join_flag,
	efi_ipv4_address  *multicast
);
typedef efi_status(efiapi*efi_udp4_routes)(
	efi_udp4_protocol *this,
	bool              delete_route,
	efi_ipv4_address  *subnet_addr,
	efi_ipv4_address  *subnet_mask,
	efi_ipv4_address  *gateway_addr
);
typedef efi_status(efiapi*efi_udp4_poll)(
	efi_udp4_protocol *this
);
typedef efi_status(efiapi*efi_udp4_receive)(
	efi_udp4_protocol         *this,
	efi_udp4_completion_token *token
);
typedef efi_status(efiapi*efi_udp4_transmit)(
	efi_udp4_protocol         *this,
	efi_udp4_completion_token *token
);
typedef efi_status(efiapi*efi_udp4_cancel)(
	efi_udp4_protocol         *this,
	efi_udp4_completion_token *token
);
struct efi_udp4_protocol{
	efi_udp4_get_mode_data get_mode_data;
	efi_udp4_configure     configure;
	efi_udp4_groups        groups;
	efi_udp4_routes        routes;
	efi_udp4_transmit      transmit;
	efi_udp4_receive       receive;
	efi_udp4_cancel        cancel;
	efi_udp4_poll          poll;
};
typedef struct efi_udp6_protocol efi_udp6_protocol;
typedef struct efi_udp6_service_point{
	efi_handle       instance;
	efi_ipv6_address local_addr;
	uint16_t         local_port;
	efi_ipv6_address remote_addr;
	uint16_t         remote_port;
}efi_udp6_service_point;
typedef struct efi_udp6_variable_data{
	efi_handle driver;
	uint32_t service_count;
	efi_udp6_service_point services[0];
}efi_udp6_variable_data;
typedef struct efi_udp6_fragment_data{
	uint32_t len;
	void     *buf;
}efi_udp6_fragment_data;
typedef struct efi_udp6_session_data{
	efi_ipv6_address src_addr;
	uint16_t         src_port;
	efi_ipv6_address dst_addr;
	uint16_t         dst_port;
}efi_udp6_session_data;
typedef struct efi_udp6_config_data{
	bool accept_promiscuous;
	bool accept_any_port;
	bool allow_dup_port;
	uint8_t traffic_class;
	uint8_t hop_limit;
	uint32_t rx_timeout;
	uint32_t tx_timeout;
	efi_ipv6_address station_addr;
	uint16_t station_port;
	efi_ipv6_address remote_addr;
	uint16_t remote_port;
}efi_udp6_config_data;
typedef struct efi_udp6_transmit_data{
	efi_udp6_session_data  *session;
	uint32_t               data_len;
	uint32_t               frag_count;
	efi_udp6_fragment_data frag_table[0];
}efi_udp6_transmit_data;
typedef struct efi_udp6_receive_data{
	efi_time               timestamp;
	efi_event              recycle_signal;
	efi_udp6_session_data  session;
	uint32_t               data_len;
	uint32_t               frag_count;
	efi_udp6_fragment_data frag_table[0];
}efi_udp6_receive_data;
typedef struct efi_udp6_completion_token{
	efi_event  event;
	efi_status status;
	union{
		efi_udp6_receive_data  *rx;
		efi_udp6_transmit_data *tx;
	}pkt;
}efi_udp6_completion_token;
typedef efi_status(efiapi*efi_udp6_get_mode_data)(
	efi_udp6_protocol               *this,
	efi_udp6_config_data            *config,
	efi_ip6_mode_data               *mode,
	efi_managed_network_config_data *mnp,
	efi_simple_network_mode         *snp
);
typedef efi_status(efiapi*efi_udp6_configure)(
	efi_udp6_protocol    *this,
	efi_udp6_config_data *config
);
typedef efi_status(efiapi*efi_udp6_groups)(
	efi_udp6_protocol *this,
	bool              join_flag,
	efi_ipv6_address  *multicast
);
typedef efi_status(efiapi*efi_udp6_transmit)(
	efi_udp6_protocol         *this,
	efi_udp6_completion_token *token
);
typedef efi_status(efiapi*efi_udp6_receive)(
	efi_udp6_protocol         *this,
	efi_udp6_completion_token *token
);
typedef efi_status(efiapi*efi_udp6_cancel)(
	efi_udp6_protocol         *this,
	efi_udp6_completion_token *token
);
typedef efi_status(efiapi*efi_udp6_poll)(
	efi_udp6_protocol *this
);
struct efi_udp6_protocol{
	efi_udp6_get_mode_data get_mode_data;
	efi_udp6_configure     configure;
	efi_udp6_groups        groups;
	efi_udp6_transmit      transmit;
	efi_udp6_receive       receive;
	efi_udp6_cancel        cancel;
	efi_udp6_poll          poll;
};
typedef struct efi_arp_protocol efi_arp_protocol;
typedef struct efi_arp_find_data{
	uint32_t size;
	bool     deny_flag;
	bool     static_flag;
	uint16_t hw_addr_type;
	uint16_t sw_addr_type;
	uint8_t  hw_addr_length;
	uint8_t  sw_addr_length;
}efi_arp_find_data;
typedef struct efi_arp_config_data{
	uint16_t sw_addr_type;
	uint8_t  sw_addr_length;
	void     *station_addr;
	uint32_t entry_timeout;
	uint32_t retry_count;
	uint32_t retry_timeout;
}efi_arp_config_data;
typedef efi_status(efiapi*efi_arp_configure)(
	efi_arp_protocol    *this,
	efi_arp_config_data *config
);
typedef efi_status(efiapi*efi_arp_add)(
	efi_arp_protocol *this,
	bool             deny_flag,
	void             *target_sw_addr,
	void             *target_hw_addr,
	uint32_t         timeout,
	bool             overwrite
);
typedef efi_status(efiapi*efi_arp_find)(
	efi_arp_protocol  *this,
	bool              by_sw_addr,
	void              *addr_buf,
	uint32_t          *entry_len,
	uint32_t          *entry_cnt,
	efi_arp_find_data **entries,
	bool              refresh
);
typedef efi_status(efiapi*efi_arp_delete)(
	efi_arp_protocol *This,
	bool             by_sw_addr,
	void             *addr_buf
);
typedef efi_status(efiapi*efi_arp_flush)(
	efi_arp_protocol *this
);
typedef efi_status(efiapi*efi_arp_request)(
	efi_arp_protocol *this,
	void             *target_sw_addr,
	efi_event        resolved_event,
	void             *target_hw_addr
);
typedef efi_status(efiapi*efi_arp_cancel)(
	efi_arp_protocol *This,
	void             *target_sw_addr,
	efi_event        resolved_event
);
struct efi_arp_protocol{
	efi_arp_configure configure;
	efi_arp_add       add;
	efi_arp_find      find;
	efi_arp_delete    delete;
	efi_arp_flush     flush;
	efi_arp_request   request;
	efi_arp_cancel    cancel;
};
typedef struct efi_dns4_protocol efi_dns4_protocol;
typedef struct efi_dns4_config_data{
	uintn_t          server_count;
	efi_ipv4_address *server_list;
	bool             use_default_setting;
	bool             enable_cache;
	uint8_t          protocol;
	efi_ipv4_address station_ip;
	efi_ipv4_address subnet_mask;
	uint16_t         local_port;
	uint32_t         retry_count;
	uint32_t         retry_interval;
}efi_dns4_config_data;
typedef struct efi_dns4_cache_entry{
	char16           *hostname;
	efi_ipv4_address *ipaddress;
	uint32_t         timeout;
}efi_dns4_cache_entry;
typedef struct efi_dns4_mode_data{
	efi_dns4_config_data config;
	uint32_t             server_count;
	efi_ipv4_address     *server_list;
	uint32_t             cache_count;
	efi_dns4_cache_entry *cache_list;
}efi_dns4_mode_data;
typedef struct dns_host_to_addr_data{
	uint32_t         ip_count;
	efi_ipv4_address *ip_list;
}dns_host_to_addr_data;
typedef struct dns_addr_to_host_data{
	char16 *hostname;
}dns_addr_to_host_data;
typedef struct dns_resource_record{
	char8    *q_name;
	uint16_t q_type;
	uint16_t q_class;
	uint32_t ttl;
	uint16_t data_len;
	char8    *rdata;
}dns_resource_record;
typedef struct dns_general_lookup_data{
	uintn_t             rr_count;
	dns_resource_record *rr_list;
}dns_general_lookup_data;
typedef struct efi_dns4_completion_token{
	efi_event  event;
	efi_status status;
	uint32_t   retry_count;
	uint32_t   retry_interval;
	union{
		dns_host_to_addr_data   *h2a;
		dns_addr_to_host_data   *a2h;
		dns_general_lookup_data *g_lookup;
	}rsp;
}efi_dns4_completion_token;
typedef efi_status(efiapi*efi_dns4_get_mode_data)(
	efi_dns4_protocol  *this,
	efi_dns4_mode_data *data
);
typedef efi_status(efiapi*efi_dns4_configure)(
	efi_dns4_protocol    *this,
	efi_dns4_config_data *data
);
typedef efi_status(efiapi*efi_dns4_host_name_to_ip)(
	efi_dns4_protocol         *this,
	char16                    *hostname,
	efi_dns4_completion_token *token
);
typedef efi_status(efiapi*efi_dns4_ip_to_host_name)(
	efi_dns4_protocol         *this,
	efi_ipv4_address          address,
	efi_dns4_completion_token *token
);
typedef efi_status(efiapi*efi_dns4_general_lookup)(
	efi_dns4_protocol          *this,
	char8                      *qname,
	uint16_t                   q_type,
	uint16_t                   q_class,
	efi_dns4_completion_token  *token
);
typedef efi_status(efiapi*efi_dns4_update_dns_cache)(
	efi_dns4_protocol    *this,
	bool                 flag,
	bool                 override,
	efi_dns4_cache_entry entry
);
typedef efi_status(efiapi*efi_dns4_poll)(
	efi_dns4_protocol *this
);
typedef efi_status(efiapi*efi_dns4_cancel)(
	efi_dns4_protocol         *this,
	efi_dns4_completion_token *token
);
struct efi_dns4_protocol{
	efi_dns4_get_mode_data        get_mode_data;
	efi_dns4_configure            configure;
	efi_dns4_host_name_to_ip      hostname_to_ip;
	efi_dns4_ip_to_host_name      ip_to_hostname;
	efi_dns4_general_lookup       general_lookup;
	efi_dns4_update_dns_cache     update_dns_cache;
	efi_dns4_poll                 poll;
	efi_dns4_cancel               cancel;
};
typedef struct efi_dns6_protocol efi_dns6_protocol;
typedef struct efi_dns6_config_data{
	bool             enable_cache;
	uint8_t          protocol;
	efi_ipv6_address station_ip;
	uint16_t         local_port;
	uint32_t         server_count;
	efi_ipv6_address *server_list;
	uint32_t         retry_count;
	uint32_t         retry_interval;
}efi_dns6_config_data;
typedef struct efi_dns6_cache_entry{
	char16           *hostname;
	efi_ipv6_address *address;
	uint32_t         timeout;
}efi_dns6_cache_entry;
typedef struct efi_dns6_mode_data{
	efi_dns6_config_data data;
	uint32_t             server_count;
	efi_ipv6_address     *server_list;
	uint32_t             cache_count;
	efi_dns6_cache_entry *cache_list;
}efi_dns6_mode_data;
typedef struct dns6_host_to_addr_data{
	uint32_t         ip_count;
	efi_ipv6_address *ip_list;
}dns6_host_to_addr_data;
typedef struct dns6_addr_to_host_data{
	char16 *hostname;
}dns6_addr_to_host_data;
typedef struct dns6_resource_record{
	char8    *q_name;
	uint16_t q_type;
	uint16_t q_class;
	uint32_t ttl;
	uint16_t data_len;
	char8    *rdata;
}dns6_resource_record;

typedef struct dns6_general_lookup_data{
	uintn_t              rr_count;
	dns6_resource_record *rr_list;
}dns6_general_lookup_data;
typedef struct efi_dns6_completion_token{
	efi_event  event;
	efi_status status;
	uint32_t   retry_count;
	uint32_t   retry_interval;
	union{
		dns6_host_to_addr_data   *h2a;
		dns6_addr_to_host_data   *a2h;
		dns6_general_lookup_data *g_lookup;
	}rsp;
}efi_dns6_completion_token;
typedef efi_status(efiapi*efi_dns6_get_mode_data)(
	efi_dns6_protocol  *this,
	efi_dns6_mode_data *data
);
typedef efi_status(efiapi*efi_dns6_configure)(
	efi_dns6_protocol    *this,
	efi_dns6_config_data *data
);
typedef efi_status(efiapi*efi_dns6_host_name_to_ip)(
	efi_dns6_protocol         *this,
	char16                    *hostname,
	efi_dns6_completion_token *token
);
typedef efi_status(efiapi*efi_dns6_ip_to_host_name)(
	efi_dns6_protocol         *this,
	efi_ipv6_address          address,
	efi_dns6_completion_token *token
);
typedef efi_status(efiapi*efi_dns6_general_lookup)(
	efi_dns6_protocol         *this,
	char8                     *q_name,
	uint16_t                  q_type,
	uint16_t                  q_class,
	efi_dns6_completion_token *token
);
typedef efi_status(efiapi*efi_dns6_update_dns_cache)(
	efi_dns6_protocol    *this,
	bool                 flag,
	bool                 override,
	efi_dns6_cache_entry entry
);
typedef efi_status(efiapi*efi_dns6_poll)(
	efi_dns6_protocol *this
);
typedef efi_status(efiapi*efi_dns6_cancel)(
	efi_dns6_protocol         *this,
	efi_dns6_completion_token *token
);
struct efi_dns6_protocol{
	efi_dns6_get_mode_data    get_mode_data;
	efi_dns6_configure        configure;
	efi_dns6_host_name_to_ip  hostname_to_ip;
	efi_dns6_ip_to_host_name  ip_to_hostname;
	efi_dns6_general_lookup   general_lookup;
	efi_dns6_update_dns_cache update_dns_cache;
	efi_dns6_poll             poll;
	efi_dns6_cancel           cancel;
};
typedef struct efi_tls_protocol efi_tls_protocol;
typedef enum efi_tls_session_data_type{
	efi_tls_type_version,
	efi_tls_type_connection_end,
	efi_tls_type_cipher_list,
	efi_tls_type_compression_method,
	efi_tls_type_ext_data,
	efi_tls_type_verify_method,
	efi_tls_type_session_id,
	efi_tls_type_session_state,
	efi_tls_type_client_random,
	efi_tls_type_server_random,
	efi_tls_type_key_material,
	efi_tls_type_verify_host,
	efi_tls_type_session_data_type_maximum
}efi_tls_session_data_type;
typedef struct efi_tls_version{
	uint8_t major;
	uint8_t minor;
}efi_tls_version;
typedef enum efi_tls_connection_end{
	efi_tls_client,
	efi_tls_server,
}efi_tls_connection_end;
typedef uint32_t efi_tls_verify;
#define EFI_TLS_VERIFY_NONE                  0x0
#define EFI_TLS_VERIFY_PEER                  0x1
#define EFI_TLS_VERIFY_FAIL_IF_NO_PEER_CERT  0x2
#define EFI_TLS_VERIFY_CLIENT_ONCE           0x4
typedef uint32_t efi_tls_verify_host_flag;
#define EFI_TLS_VERIFY_FLAG_NONE                    0x00
#define EFI_TLS_VERIFY_FLAG_ALWAYS_CHECK_SUBJECT    0x01
#define EFI_TLS_VERIFY_FLAG_NO_WILDCARDS            0x02
#define EFI_TLS_VERIFY_FLAG_NO_PARTIAL_WILDCARDS    0x04
#define EFI_TLS_VERIFY_FLAG_MULTI_LABEL_WILDCARDS   0x08
#define EFI_TLS_VERIFY_FLAG_SINGLE_LABEL_SUBDOMAINS 0x10
#define EFI_TLS_VERIFY_FLAG_NEVER_CHECK_SUBJECT     0x20
typedef struct efi_tls_cipher{
	uint8_t data1;
	uint8_t data2;
}__packed efi_tls_cipher;
typedef uint8_t efi_tls_compression;
typedef struct efi_tls_extension{
	uint16_t ext_type;
	uint16_t length;
	uint8_t  data[0];
}__packed efi_tls_extension;
typedef struct efi_tls_verify_host{
	efi_tls_verify_host_flag flags;
	char8 *hostname;
}efi_tls_verify_host;
typedef struct efi_tls_random{
	uint32_t gmt_unix_time;
	uint8_t  random_bytes[28];
}__packed efi_tls_random;
typedef struct efi_tls_master_secret{
	uint8_t data[48];
}__packed efi_tls_master_secret;
#define MAX_TLS_SESSION_ID_LENGTH 32
typedef struct efi_tls_session_id{
	uint16_t len;
	uint8_t data[MAX_TLS_SESSION_ID_LENGTH];
}__packed efi_tls_session_id;
typedef enum efi_tls_session_state{
	efi_tls_session_not_started,
	efi_tls_session_handshaking,
	efi_tls_session_data_transferring,
	efi_tls_session_closing,
	efi_tls_session_error,
	efi_tls_session_state_max
}efi_tls_session_state;
typedef struct efi_tls_fragment_data{
	uint32_t len;
	void*buf;
}efi_tls_fragment_data;
typedef enum efi_tls_crypt_mode{
	efi_tls_encrypt,
	efi_tls_decrypt,
}efi_tls_crypt_mode;
typedef efi_status(efiapi*efi_tls_set_session_data)(
	efi_tls_protocol          *this,
	efi_tls_session_data_type type,
	void                      *data,
	uintn_t                   size
);
typedef efi_status(efiapi*efi_tls_get_session_data)(
	efi_tls_protocol          *this,
	efi_tls_session_data_type type,
	void                      *data,
	uintn_t                   *size
);
typedef efi_status(efiapi*efi_tls_build_response_packet)(
	efi_tls_protocol *this,
	uint8_t          *req_buf,
	uintn_t          req_size,
	uint8_t          *buf,
	uintn_t          *buf_size
);
typedef efi_status(efiapi*efi_tls_process_packet)(
	efi_tls_protocol      *this,
	efi_tls_fragment_data **frag_table,
	uint32_t              *frag_count,
	efi_tls_crypt_mode    crypt_mode
);
struct efi_tls_protocol{
	efi_tls_set_session_data      set_session_data;
	efi_tls_get_session_data      get_session_data;
	efi_tls_build_response_packet build_rsp_pkt;
	efi_tls_process_packet        process_pkt;
};
typedef struct efi_tls_config_protocol efi_tls_config_protocol;
typedef enum efi_tls_config_data_type{
	efi_tls_cfg_type_host_public_cert,
	efi_tls_cfg_type_host_private_key,
	efi_tls_cfg_type_ca_cert,
	efi_tls_cfg_type_cert_Revocation_list,
	efi_tls_cfg_type_max
}efi_tls_config_data_type;
typedef efi_status(efiapi*efi_tls_config_set_data)(
	efi_tls_config_protocol  *this,
	efi_tls_config_data_type type,
	void                     *data,
	uintn_t                  size
);
typedef efi_status(efiapi*efi_tls_config_get_data)(
	efi_tls_config_protocol  *this,
	efi_tls_config_data_type type,
	void                     *data,
	uintn_t                  *size
);
struct efi_tls_config_protocol{
	efi_tls_config_set_data set_data;
	efi_tls_config_get_data get_data;
};
extern efi_guid gEfiTlsConfigurationProtocolGuid;
extern efi_guid gEfiTlsServiceBindingProtocolGuid;
extern efi_guid gEfiTlsProtocolGuid;
extern efi_guid gEfiDns6ServiceBindingProtocolGuid;
extern efi_guid gEfiDns6ProtocolGuid;
extern efi_guid gEfiDns4ServiceBindingProtocolGuid;
extern efi_guid gEfiDns4ProtocolGuid;
extern efi_guid gEfiArpServiceBindingProtocolGuid;
extern efi_guid gEfiArpProtocolGuid;
extern efi_guid gEfiUdp4ServiceBindingProtocolGuid;
extern efi_guid gEfiUdp4ProtocolGuid;
extern efi_guid gEfiUdp6ServiceBindingProtocolGuid;
extern efi_guid gEfiUdp6ProtocolGuid;
extern efi_guid gEfiTcp4ServiceBindingProtocolGuid;
extern efi_guid gEfiTcp4ProtocolGuid;
extern efi_guid gEfiTcp6ServiceBindingProtocolGuid;
extern efi_guid gEfiTcp6ProtocolGuid;
extern efi_guid gEfiIp6ConfigProtocolGuid;
extern efi_guid gEfiIp6ServiceBindingProtocolGuid;
extern efi_guid gEfiIp6ProtocolGuid;
extern efi_guid gEfiIp4Config2ProtocolGuid;
extern efi_guid gEfiIp4ConfigProtocolGuid;
extern efi_guid gEfiManagedNetworkServiceBindingProtocolGuid;
extern efi_guid gEfiManagedNetworkProtocolGuid;
extern efi_guid gEfiSimpleNetworkProtocolGuid;
extern efi_guid gEfiIp4ServiceBindingProtocolGuid;
extern efi_guid gEfiIp4ProtocolGuid;
#endif
