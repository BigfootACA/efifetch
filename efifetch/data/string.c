#include"efi.h"
#include"str.h"
#include"data.h"

const char*efi_status_to_string(efi_status st){
	switch(st){
		case efi_success:               return "Success";
		case efi_warn_unknown_glyph:    return "Unknown Glyph";
		case efi_warn_delete_failure:   return "Delete Failure";
		case efi_warn_write_failure:    return "Write Failure";
		case efi_warn_buffer_too_small: return "Buffer Too Small";
		case efi_warn_stale_data:       return "Stale Data";
		case efi_load_error:            return "Load Error";
		case efi_invalid_parameter:     return "Invalid Parameter";
		case efi_unsupported:           return "Unsupported";
		case efi_bad_buffer_size:       return "Bad Buffer Size";
		case efi_buffer_too_small:      return "Buffer Too Small";
		case efi_not_ready:             return "Not Ready";
		case efi_device_error:          return "Device Error";
		case efi_write_protected:       return "Write Protected";
		case efi_out_of_resources:      return "Out of Resources";
		case efi_volume_corrupted:      return "Volume Corrupt";
		case efi_volume_full:           return "Volume Full";
		case efi_no_media:              return "No Media";
		case efi_media_changed:         return "Media changed";
		case efi_not_found:             return "Not Found";
		case efi_access_denied:         return "Access Denied";
		case efi_no_response:           return "No Response";
		case efi_no_mapping:            return "No mapping";
		case efi_timeout:               return "Time out";
		case efi_not_started:           return "Not started";
		case efi_already_started:       return "Already started";
		case efi_aborted:               return "Aborted";
		case efi_icmp_error:            return "ICMP Error";
		case efi_tftp_error:            return "TFTP Error";
		case efi_protocol_error:        return "Protocol Error";
		case efi_incompatible_version:  return "Incompatible Version";
		case efi_security_violation:    return "Security Violation";
		case efi_crc_error:             return "CRC Error";
		case efi_end_of_media:          return "End of Media";
		case efi_end_of_file:           return "End of File";
		case efi_invalid_language:      return "Invalid Language";
		case efi_compromised_data:      return "Compromised Data";
		default:                        return "Unknown";
	}
}

const char*efi_status_to_short_string(efi_status st){
	switch(st){
		case efi_success:               return "success";
		case efi_warn_unknown_glyph:    return "warn-unknown-glyph";
		case efi_warn_delete_failure:   return "warn-delete-failure";
		case efi_warn_write_failure:    return "warn-write-failure";
		case efi_warn_buffer_too_small: return "warn-buffer-too-small";
		case efi_warn_stale_data:       return "warn-stale-data";
		case efi_load_error:            return "load-error";
		case efi_invalid_parameter:     return "invalid-parameter";
		case efi_unsupported:           return "unsupported";
		case efi_bad_buffer_size:       return "bad-buffer-size";
		case efi_buffer_too_small:      return "buffer-too-small";
		case efi_not_ready:             return "not-ready";
		case efi_device_error:          return "device-error";
		case efi_write_protected:       return "write-protected";
		case efi_out_of_resources:      return "out-of-resources";
		case efi_volume_corrupted:      return "volume-corrupted";
		case efi_volume_full:           return "volume-full";
		case efi_no_media:              return "no-media";
		case efi_media_changed:         return "media-changed";
		case efi_not_found:             return "not-found";
		case efi_access_denied:         return "access-denied";
		case efi_no_response:           return "no-response";
		case efi_no_mapping:            return "no-mapping";
		case efi_timeout:               return "timeout";
		case efi_not_started:           return "not-started";
		case efi_already_started:       return "already-started";
		case efi_aborted:               return "aborted";
		case efi_icmp_error:            return "icmp-error";
		case efi_tftp_error:            return "tftp-error";
		case efi_protocol_error:        return "protocol-error";
		case efi_incompatible_version:  return "incompatible-version";
		case efi_security_violation:    return "security-violation";
		case efi_crc_error:             return "crc-error";
		case efi_end_of_media:          return "end-of-media";
		case efi_end_of_file:           return "end-of-file";
		case efi_invalid_language:      return "invalid-language";
		case efi_compromised_data:      return "compromised-data";
		default:                        return "unknown";
	}
}

const char*efi_memory_type_to_string(efi_memory_type type){
	switch(type){
		case efi_reserved_memory_type:  return "Reserved";
		case efi_loader_code:           return "Loader Code";
		case efi_loader_data:           return "Loader Data";
		case efi_bs_code:               return "Boot Services Code";
		case efi_bs_data:               return "Boot Services Data";
		case efi_rs_code:               return "Runtime Services Code";
		case efi_rs_data:               return "Runtime Services Data";
		case efi_conventional_memory:   return "Conventional";
		case efi_unusable_memory:       return "Unusable";
		case efi_acpi_reclaim_memory:   return "ACPI Reclaim";
		case efi_acpi_memory_nvs:       return "ACPI Memory NVS";
		case efi_mmio:                  return "MMIO";
		case efi_mmio_port_space:       return "MMIO Port Space";
		case efi_pal_code:              return "Pal Code";
		case efi_persistent_memory:     return "Persistent";
		case efi_max_memory_type:       return "Max";
		default:                        return "Unknown";
	}
}

const char*efi_guid_to_string(const efi_guid*guid,char*buff,size_t len){
	if(!guid||!buff||len<=0)return NULL;
	memset(buff,0,len);
	struct guid*g=(struct guid*)guid;
	snprintf(buff,len-1,
		"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		g->data1,g->data2,g->data3,
		g->data4[0],g->data4[1],g->data4[2],g->data4[3],
		g->data4[4],g->data4[5],g->data4[6],g->data4[7]
	);
	return buff;
}

const char*efi_guid_to_readable_string(const efi_guid*guid,char*buff,size_t len){
	if(!guid||!buff||len<=0)return NULL;
	memset(buff,0,len);
	for(size_t i=0;efi_guid_table[i].guid;i++){
		if(memcmp(guid,efi_guid_table[i].guid,sizeof(efi_guid))!=0)continue;
		if(!efi_guid_table[i].name||!efi_guid_table[i].name[0])continue;
		strncpy(buff,efi_guid_table[i].name,len-1);
		return buff;
	}
	return efi_guid_to_string(guid,buff,len);
}
