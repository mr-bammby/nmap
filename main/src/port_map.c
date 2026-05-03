#ifndef PORT_MAP_H
#define PORT_MAP_H

/*
 * Auto-generated from /mnt/data/services.
 * TIER 1 contains unique service-name strings only.
 * TIER 2 maps all 65536 ports to indices into TIER 1.
 */

#include <stdint.h>
#include <stddef.h>

typedef struct {
    const uint8_t *payload_data;
    const uint8_t len; // Smallest type for current list (< 256 bytes)
} port_payload_t;

typedef struct {
    uint16_t name_idx;
    uint8_t payload_idx; 
} port_map_entry_t;

static const uint8_t payload_rpc[] = {0x72,0xFE,0x1D,0x13,0,0,0,0,0,0,0,0x02,0,0x01,0x86,0xA0,0,0x01,0x97,0x7C,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static const uint8_t payload_dns_bind[] = {0,0x06,0x01,0,0,0x01,0,0,0,0,0,0,0x07,'v','e','r','s','i','o','n',0x04,'b','i','n','d',0,0,0x10,0,0x03};
static const uint8_t payload_dns_stat[] = {0,0,0x10,0,0,0,0,0,0,0,0,0};
static const uint8_t payload_nbt[] = {0x80,0xf0,0,0x10,0,0x01,0,0,0,0,0,0,0x20,0x43,0x4b,'A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A',0,0,0x21,0,0x01};
static const uint8_t payload_help[] = {'h','e','l','p','\r','\n','\r','\n'};
static const uint8_t payload_ldap[] = {0x30,0x84,0,0,0,0x2d,0x02,0x01,0x07,0x63,0x84,0,0,0,0x24,0x04,0,0x0a,0x01,0,0x0a,0x01,0,0x02,0x01,0,0x02,0x01,0x64,0x01,0x01,0,0x87,0x0b,'o','b','j','e','c','t','C','l','a','s','s',0x30,0x84,0,0,0,0};
static const uint8_t payload_sip[] = "OPTIONS sip:nm SIP/2.0\r\nVia: SIP/2.0/UDP nm;branch=foo;rport\r\nFrom: <sip:nm@nm>;tag=root\r\nTo: <sip:nm2@nm2>\r\nCall-ID: 50000\r\nCSeq: 42 OPTIONS\r\nMax-Forwards: 70\r\nContent-Length: 0\r\nContact: <sip:nm@nm>\r\nAccept: application/sdp\r\n\r\n";
static const uint8_t payload_sqlping[] = {0x02};
static const uint8_t payload_ntp[] = {0xe3,0,0x04,0xfa,0,0x01,0,0,0,0x01,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0xc5,0x4f,0x23,0x4b,0x71,0xb1,0x52,0xf3};
static const uint8_t payload_snmpv1[] = {0x30,0x82,0,0x2f,0x02,0x01,0,0x04,0x06,'p','u','b','l','i','c',0xa0,0x82,0,0x20,0x02,0x04,0x4c,0x33,0xa7,0x56,0x02,0x01,0,0x02,0x01,0,0x30,0x82,0,0x10,0x30,0x82,0,0x0c,0x06,0x08,0x2b,0x06,0x01,0x02,0x01,0x01,0x05,0,0x05,0};
static const uint8_t payload_snmpv3[] = {0x30,0x3a,0x02,0x01,0x03,0x30,0x0f,0x02,0x02,0x4a,0x69,0x02,0x03,0,0xff,0xe3,0x04,0x01,0x04,0x02,0x01,0x03,0x04,0x10,0x30,0x0e,0x04,0,0x02,0x01,0,0x02,0x01,0,0x04,0,0x04,0,0x04,0,0x30,0x12,0x04,0,0x04,0,0xa0,0x0c,0x02,0x02,0x37,0xf0,0x02,0x01,0,0x02,0x01,0,0x30,0};
static const uint8_t payload_xdmcp[] = {0,0x01,0,0x02,0,0x01,0};
static const uint8_t payload_afs[] = {0,0,0x03,0xe7,0,0,0,0,0,0,0,0x65,0,0,0,0,0,0,0,0,0x0d,0x05,0,0,0,0,0,0,0,0,0,0};
static const uint8_t payload_db2[] = "DB2GETADDR\0SQL08010\0";
static const uint8_t payload_mdns[] = {0,0,0,0,0,0x01,0,0,0,0,0,0,0x09,'_','s','e','r','v','i','c','e','s',0x07,'_','d','n','s','-','s','d',0x04,'_','u','d','p',0x05,'l','o','c','a','l',0,0,0x0c,0,0x01};
static const uint8_t payload_citrix[] = {0x1e,0,0x01,0x30,0x02,0xfd,0xa8,0xe3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static const uint8_t payload_kerberos[] = {0x6a,0x81,0x6e,0x30,0x81,0x6b,0xa1,0x03,0x02,0x01,0x05,0xa2,0x03,0x02,0x01,0x0a,0xa4,0x81,0x5e,0x30,0x5c,0xa0,0x07,0x03,0x05,0,0x50,0x80,0,0x10,0xa2,0x04,0x1b,0x02,'N','M',0xa3,0x17,0x30,0x15,0xa0,0x03,0x02,0x01,0,0xa1,0x0e,0x30,0x0c,0x1b,0x06,'k','r','b','t','g','t',0x1b,0x02,'N','M',0xa5,0x11,0x18,0x0f,'1','9','7','0','0','1','0','1','0','0','0','0','0','0','Z',0xa7,0x06,0x02,0x04,0x1f,0x1e,0xb9,0xd9,0xa8,0x17,0x30,0x15,0x02,0x01,0x12,0x02,0x01,0x11,0x02,0x01,0x10,0x02,0x01,0x17,0x02,0x01,0x01,0x02,0x01,0x03,0x02,0x01,0x02};
static const uint8_t payload_lms[] = "eIPAD\0NAME\0JSON\0VERS\0UUID\0JVID\x06\x12\x34\x56\x78\x12\x34";
static const uint8_t payload_quake1[] = {0x80,0,0,0x0c,0x02,'Q','U','A','K','E',0,0x03};
static const uint8_t payload_quake2[] = {0xff,0xff,0xff,0xff,'s','t','a','t','u','s'};
static const uint8_t payload_quake3[] = {0xff,0xff,0xff,0xff,'g','e','t','s','t','a','t','u','s'};
static const uint8_t payload_quake3m[] = {0xff,0xff,0xff,0xff,'g','e','t','s','e','r','v','e','r','s',' ','6','8',' ','e','m','p','t','y',' ','f','u','l','l'};
static const uint8_t payload_snquery[] = "SNQUERY: 127.0.0.1:AAAAAA:xsvr";
static const uint8_t payload_bo[] = {0xCE,0x63,0xD1,0xD2,0x16,0xE7,0x13,0xCF,0x38,0xA5,0xA5,0x86,0xB2,0x75,0x4B,0x99,0xAA,0x32,0x58};
static const uint8_t payload_sybase[] = {0x1b,0,0,0x3d,0,0,0,0,0x12,'C','O','N','N','E','C','T','I','O','N','L','E','S','S','_','T','D','S',0,0,0,0x01,0,0,0x04,0,0x05,0,0x05,0,0,0x01,0x02,0,0,0x03,0x01,0x01,0x04,0x08,0,0,0,0,0,0,0,0,0x07,0x02,0x04,0xb1};
static const uint8_t payload_vuze[] = {0xff,0xf0,0x97,0x0d,0x2e,0x60,0xd1,0x6f,0,0,0x04,0,0,0x55,0xab,0xec,0x32,0,0,0,0,0,0x32,0x04,0x0a,0,0xc8,0x75,0xf8,0x16,0,0x5c,0xb9,0x65,0,0,0,0,0x4e,0xd1,0xf5,0x28};
static const uint8_t payload_pcanywhere[] = "NQ";
static const uint8_t payload_pcduo[] = {0,0x80,0x80,0x08,0xff,0};
static const uint8_t payload_pcduogw[] = {0x20,0x90,0x80,0x08,0xff,0};
static const uint8_t payload_memcached[] = {0,0x01,0,0,0,0x01,0,0,'s','t','a','t','s','\r','\n'};
static const uint8_t payload_slp[] = {0x02,0x01,0,0,0x36,' ',0,0,0,0,0,0x01,0,0x02,'e','n',0,0,0,0x15,'s','e','r','v','i','c','e',':','s','e','r','v','i','c','e','-','a','g','e','n','t',0,0x07,'d','e','f','a','u','l','t',0,0,0,0};
static const uint8_t payload_murmur[] = {0,0,0,0,'a','b','c','d','e','f','g','h'};
static const uint8_t payload_ventrilo[] = {0x01,0xe7,0xe5,0x75,0x31,0xa3,0x17,0x0b,0x21,0xcf,0xbf,0x2b,0x99,0x4e,0xdd,0x19,0xac,0xde,0x08,0x5f,0x8b,0x24,0x0a,0x11,0x19,0xb6,0x73,0x6f,0xad,0x28,0x13,0xd2,0x0a,0xb9,0x12,0x75};
static const uint8_t payload_ts2[] = {0xf4,0xbe,0x03,0,0,0,0,0,0,0,0,0,0x01,0,0,0,0x32,0x78,0xba,0x85,0x09,'T','e','a','m','S','p','e','a','k',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x0a,'W','i','n','d','o','w','s',' ','X','P',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x02,0,0,0,0x20,0,0x3c,0,0,0x01,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x08,'n','i','c','k','n','a','m','e',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static const uint8_t payload_ts3[] = {0x05,0xca,0x7f,0x16,0x9c,0x11,0xf9,0x89,0,0,0,0,0x02,0x9d,0x74,0x8b,0x45,0xaa,0x7b,0xef,0xb9,0x9e,0xfe,0xad,0x08,0x19,0xba,0xcf,0x41,0xe0,0x16,0xa2,0x32,0x6c,0xf3,0xcf,0xf4,0x8e,0x3c,0x44,0x83,0xc8,0x8d,0x51,0x45,0x6f,0x90,0x95,0x23,0x3e,0,0x97,0x2b,0x1c,0x71,0xb2,0x4e,0xc0,0x61,0xf1,0xd7,0x6f,0xc5,0x7e,0xf6,0x48,0x52,0xbf,0x82,0x6a,0xa2,0x3b,0x65,0xaa,0x18,0x7a,0x17,0x38,0xc3,0x81,0x27,0xc3,0x47,0xfc,0xa7,0x35,0xba,0xfc,0x0f,0x9d,0x9d,0x72,0x24,0x9d,0xfc,0x02,0x17,0x6d,0x6b,0xb1,0x2d,0x72,0xc6,0xe3,0x17,0x1c,0x95,0xd9,0x69,0x99,0x57,0xce,0xdd,0xdf,0x05,0xdc,0x03,0x94,0x56,0x04,0x3a,0x14,0xe5,0xad,0x9a,0x2b,0x14,0x30,0x3a,0x23,0xa3,0x25,0xad,0xe8,0xe6,0x39,0x8a,0x85,0x2a,0xc6,0xdf,0xe5,0x5d,0x2d,0xa0,0x2f,0x5d,0x9c,0xd7,0x2b,0x24,0xfb,0xb0,0x9c,0xc2,0xba,0x89,0xb4,0x1b,0x17,0xa2,0xb6};
static const uint8_t payload_freelancer[] = {0,0x02,0xf1,0x26,0x01,0x26,0xf0,0x90,0xa6,0xf0,0x26,0x57,0x4e,0xac,0xa0,0xec,0xf8,0x68,0xe4,0x8d,0x21};
static const uint8_t payload_ase[] = {'s'};
static const uint8_t payload_andromouse[] = "AMSNIFF";
static const uint8_t payload_airhid[] = "from:airhid";
static const uint8_t payload_netmotion[] = {0,0x40,0x50,0,0,0,0,0x85,0x5d,0xb4,0x91,0x28,0,0,0,0,0,0x01,0x7c,0x91,0x40,0,0,0,0xaa,0x39,0xda,0x42,0x37,0x65,0xcf,0x01,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static const uint8_t payload_openvpn[] = {0x8d,0xc1,0x78,0x01,0xb8,0x9b,0xcb,0x8f,0,0,0,0,0};
static const uint8_t payload_ipmi[] = {0x06,0,0xff,0x07,0,0,0,0,0,0,0,0,0,0x09,0x20,0x18,0xc8,0x81,0,0x38,0x8e,0x04,0xb5};
static const uint8_t payload_coap[] = {0x40,0x01,0x01,0xce,0xbb,'.','w','e','l','l','-','k','n','o','w','n',0x04,'c','o','r','e'};
static const uint8_t payload_dtls[] = {0x16,0xfe,0xff,0,0,0,0,0,0,0,0,0,0x36,0x01,0,0,0x2a,0,0,0,0,0,0,0,0x2a,0xfe,0xfd,0,0,0,0,0x7c,0x77,0x40,0x1e,0x8a,0xc8,0x22,0xa0,0xa0,0x18,0xff,0x93,0x08,0xca,0xac,0x0a,0x64,0x2f,0xc9,0x22,0x64,0xbc,0x08,0xa8,0x16,0x89,0x19,0x30,0,0,0,0x02,0,0x2f,0x01,0};
static const uint8_t payload_quic[] = {0x0d,0x89,0xc1,0x9c,0x1c,0x2a,0xff,0xfc,0xf1,'Q','9','9','9',0};
static const uint8_t payload_ard[] = {0,0x14,0,0x01,0x03};
static const uint8_t payload_ubiq1[] = {0x01,0,0,0};
static const uint8_t payload_ubiq2[] = {0x02,0x08,0,0};

static const port_payload_t PAYLOADS[] = {
    { NULL, 0 },                                                    // 0: Fallback
    { payload_rpc, sizeof(payload_rpc) },                           // 1: RPCCheck | Service: RPC
    { payload_dns_bind, sizeof(payload_dns_bind) },                 // 2: DNSVersionBindReq | Service: DNS
    { payload_dns_stat, sizeof(payload_dns_stat) },                 // 3: DNSStatusRequest | Service: DNS
    { payload_nbt, sizeof(payload_nbt) },                           // 4: NBTStat | Service: NetBIOS
    { payload_help, sizeof(payload_help) },                         // 5: Help | Service: Generic Management
    { payload_ldap, sizeof(payload_ldap) },                         // 6: LDAPSearchReqUDP | Service: LDAP
    { payload_sip, sizeof(payload_sip) },                           // 7: SIPOptions | Service: SIP
    { payload_sqlping, sizeof(payload_sqlping) },                   // 8: Sqlping | Service: MSSQL Monitor
    { payload_ntp, sizeof(payload_ntp) },                           // 9: NTPRequest | Service: NTP
    { payload_snmpv1, sizeof(payload_snmpv1) },                     // 10: SNMPv1public | Service: SNMP
    { payload_snmpv3, sizeof(payload_snmpv3) },                     // 11: SNMPv3GetRequest | Service: SNMP
    { payload_xdmcp, sizeof(payload_xdmcp) },                       // 12: xdmcp | Service: XDMCP
    { payload_afs, sizeof(payload_afs) },                           // 13: AFSVersionRequest | Service: AFS
    { payload_db2, sizeof(payload_db2) },                           // 14: ibm-db2-das-udp | Service: DB2
    { payload_mdns, sizeof(payload_mdns) },                         // 15: DNS-SD | Service: mDNS
    { payload_citrix, sizeof(payload_citrix) },                     // 16: Citrix | Service: ICA/Citrix
    { payload_kerberos, sizeof(payload_kerberos) },                 // 17: Kerberos | Service: Kerberos
    { payload_lms, sizeof(payload_lms) },                           // 18: SqueezeCenter | Service: LMS
    { payload_quake1, sizeof(payload_quake1) },                     // 19: Quake1_server_info | Service: Quake
    { payload_quake2, sizeof(payload_quake2) },                     // 20: Quake2_status | Service: Quake2
    { payload_quake3, sizeof(payload_quake3) },                     // 21: Quake3_getstatus | Service: Quake3
    { payload_quake3m, sizeof(payload_quake3m) },                   // 22: Quake3_master_getservers | Service: Quake3 Master
    { payload_snquery, sizeof(payload_snquery) },                   // 23: serialnumberd | Service: Apple SNQuery
    { payload_bo, sizeof(payload_bo) },                             // 24: BackOrifice | Service: BackOrifice
    { payload_sybase, sizeof(payload_sybase) },                     // 25: sybaseanywhere | Service: Sybase
    { payload_vuze, sizeof(payload_vuze) },                         // 26: vuze-dht | Service: BitTorrent/Vuze
    { payload_pcanywhere, sizeof(payload_pcanywhere) },             // 27: pc-anywhere | Service: pcAnywhere
    { payload_pcduo, sizeof(payload_pcduo) },                       // 28: pc-duo | Service: PC-Duo
    { payload_pcduogw, sizeof(payload_pcduogw) },                   // 29: pc-duo-gw | Service: PC-Duo Gateway
    { payload_memcached, sizeof(payload_memcached) },               // 30: memcached | Service: Memcached
    { payload_slp, sizeof(payload_slp) },                           // 31: svrloc | Service: SLP
    { payload_murmur, sizeof(payload_murmur) },                     // 32: Murmur | Service: Mumble
    { payload_ventrilo, sizeof(payload_ventrilo) },                 // 33: Ventrilo | Service: Ventrilo
    { payload_ts2, sizeof(payload_ts2) },                           // 34: TeamSpeak2 | Service: TS2
    { payload_ts3, sizeof(payload_ts3) },                           // 35: TeamSpeak3 | Service: TS3
    { payload_freelancer, sizeof(payload_freelancer) },             // 36: FreelancerStatus | Service: Freelancer
    { payload_ase, sizeof(payload_ase) },                           // 37: ASE | Service: All-Seeing Eye
    { payload_andromouse, sizeof(payload_andromouse) },                // 38: AndroMouse | Service: AndroMouse
    { payload_airhid, sizeof(payload_airhid) },                                   // 39: AirHID | Service: AirHID
    { payload_netmotion, sizeof(payload_netmotion) },               // 40: NetMotionMobility | Service: NetMotion
    { payload_openvpn, sizeof(payload_openvpn) },                   // 41: OpenVPN | Service: OpenVPN
    { payload_ipmi, sizeof(payload_ipmi) },                         // 42: ipmi-rmcp | Service: IPMI
    { payload_coap, sizeof(payload_coap) },                         // 43: coap-request | Service: CoAP
    { payload_dtls, sizeof(payload_dtls) },                         // 44: DTLSSessionReq | Service: DTLS
    { payload_quic, sizeof(payload_quic) },                         // 45: QUIC | Service: QUIC
    { payload_ard, sizeof(payload_ard) },                           // 46: ARD | Service: Apple Remote Desktop
    { payload_ubiq1, sizeof(payload_ubiq1) },                       // 47: UbiquitiDiscoveryv1 | Service: Ubiquiti
    { payload_ubiq2, sizeof(payload_ubiq2) },                       // 48: UbiquitiDiscoveryv2 | Service: Ubiquiti
};

static const char *const SVC_NAMES[] = {
    "unknown",  // Index 0
    "tcpmux",  // Index 1
    "compressnet",  // Index 2
    "rje",  // Index 3
    "echo",  // Index 4
    "discard",  // Index 5
    "systat",  // Index 6
    "daytime",  // Index 7
    "netstat",  // Index 8
    "qotd",  // Index 9
    "msp",  // Index 10
    "chargen",  // Index 11
    "ftp-data",  // Index 12
    "ftp",  // Index 13
    "ssh",  // Index 14
    "telnet",  // Index 15
    "priv-mail",  // Index 16
    "smtp",  // Index 17
    "rsftp",  // Index 18
    "nsw-fe",  // Index 19
    "msg-icp",  // Index 20
    "msg-auth",  // Index 21
    "dsp",  // Index 22
    "priv-print",  // Index 23
    "time",  // Index 24
    "rap",  // Index 25
    "rlp",  // Index 26
    "graphics",  // Index 27
    "nameserver",  // Index 28
    "whois",  // Index 29
    "mpm-flags",  // Index 30
    "mpm",  // Index 31
    "mpm-snd",  // Index 32
    "ni-ftp",  // Index 33
    "auditd",  // Index 34
    "tacacs",  // Index 35
    "re-mail-ck",  // Index 36
    "la-maint",  // Index 37
    "xns-time",  // Index 38
    "domain",  // Index 39
    "xns-ch",  // Index 40
    "isi-gl",  // Index 41
    "xns-auth",  // Index 42
    "priv-term",  // Index 43
    "xns-mail",  // Index 44
    "priv-file",  // Index 45
    "ni-mail",  // Index 46
    "acas",  // Index 47
    "via-ftp",  // Index 48
    "covia",  // Index 49
    "tacacs-ds",  // Index 50
    "sqlnet",  // Index 51
    "dhcps",  // Index 52
    "dhcpc",  // Index 53
    "tftp",  // Index 54
    "gopher",  // Index 55
    "netrjs-1",  // Index 56
    "netrjs-2",  // Index 57
    "netrjs-3",  // Index 58
    "netrjs-4",  // Index 59
    "priv-dial",  // Index 60
    "deos",  // Index 61
    "priv-rje",  // Index 62
    "vettcp",  // Index 63
    "finger",  // Index 64
    "http",  // Index 65
    "hosts2-ns",  // Index 66
    "xfer",  // Index 67
    "mit-ml-dev",  // Index 68
    "ctf",  // Index 69
    "mfcobol",  // Index 70
    "priv-term-l",  // Index 71
    "kerberos-sec",  // Index 72
    "su-mit-tg",  // Index 73
    "dnsix",  // Index 74
    "mit-dov",  // Index 75
    "npp",  // Index 76
    "dcp",  // Index 77
    "objcall",  // Index 78
    "supdup",  // Index 79
    "dixie",  // Index 80
    "swift-rvf",  // Index 81
    "linuxconf",  // Index 82
    "tacnews",  // Index 83
    "metagram",  // Index 84
    "newacct",  // Index 85
    "hostname",  // Index 86
    "iso-tsap",  // Index 87
    "gppitnp",  // Index 88
    "acr-nema",  // Index 89
    "csnet-ns",  // Index 90
    "pop3pw",  // Index 91
    "3com-tsmux",  // Index 92
    "rtelnet",  // Index 93
    "snagas",  // Index 94
    "pop2",  // Index 95
    "pop3",  // Index 96
    "rpcbind",  // Index 97
    "mcidas",  // Index 98
    "ident",  // Index 99
    "auth",  // Index 100
    "audionews",  // Index 101
    "sftp",  // Index 102
    "ansanotify",  // Index 103
    "uucp-path",  // Index 104
    "sqlserv",  // Index 105
    "nntp",  // Index 106
    "cfdptkt",  // Index 107
    "erpc",  // Index 108
    "smakynet",  // Index 109
    "ntp",  // Index 110
    "ansatrader",  // Index 111
    "locus-map",  // Index 112
    "unitary",  // Index 113
    "locus-con",  // Index 114
    "gss-xlicen",  // Index 115
    "pwdgen",  // Index 116
    "cisco-fna",  // Index 117
    "cisco-tna",  // Index 118
    "cisco-sys",  // Index 119
    "statsrv",  // Index 120
    "ingres-net",  // Index 121
    "msrpc",  // Index 122
    "profile",  // Index 123
    "netbios-ns",  // Index 124
    "netbios-dgm",  // Index 125
    "netbios-ssn",  // Index 126
    "emfis-data",  // Index 127
    "emfis-cntl",  // Index 128
    "bl-idm",  // Index 129
    "imap",  // Index 130
    "news",  // Index 131
    "uaac",  // Index 132
    "iso-tp0",  // Index 133
    "iso-ip",  // Index 134
    "cronus",  // Index 135
    "aed-512",  // Index 136
    "sql-net",  // Index 137
    "hems",  // Index 138
    "bftp",  // Index 139
    "sgmp",  // Index 140
    "netsc-prod",  // Index 141
    "netsc-dev",  // Index 142
    "sqlsrv",  // Index 143
    "knet-cmp",  // Index 144
    "pcmail-srv",  // Index 145
    "nss-routing",  // Index 146
    "sgmp-traps",  // Index 147
    "snmp",  // Index 148
    "snmptrap",  // Index 149
    "cmip-man",  // Index 150
    "cmip-agent",  // Index 151
    "smip-agent",  // Index 152
    "xns-courier",  // Index 153
    "s-net",  // Index 154
    "namp",  // Index 155
    "rsvd",  // Index 156
    "send",  // Index 157
    "print-srv",  // Index 158
    "multiplex",  // Index 159
    "cl-1",  // Index 160
    "xyplex-mux",  // Index 161
    "mailq",  // Index 162
    "vmnet",  // Index 163
    "genrad-mux",  // Index 164
    "xdmcp",  // Index 165
    "nextstep",  // Index 166
    "bgp",  // Index 167
    "ris",  // Index 168
    "unify",  // Index 169
    "audit",  // Index 170
    "ocbinder",  // Index 171
    "ocserver",  // Index 172
    "remote-kis",  // Index 173
    "kis",  // Index 174
    "aci",  // Index 175
    "mumps",  // Index 176
    "qft",  // Index 177
    "gacp",  // Index 178
    "cacp",  // Index 179
    "prospero",  // Index 180
    "osu-nms",  // Index 181
    "srmp",  // Index 182
    "irc",  // Index 183
    "dn6-nlm-aud",  // Index 184
    "dn6-smm-red",  // Index 185
    "dls",  // Index 186
    "dls-mon",  // Index 187
    "smux",  // Index 188
    "src",  // Index 189
    "at-rtmp",  // Index 190
    "at-nbp",  // Index 191
    "at-3",  // Index 192
    "at-echo",  // Index 193
    "at-5",  // Index 194
    "at-zis",  // Index 195
    "at-7",  // Index 196
    "at-8",  // Index 197
    "tam",  // Index 198
    "z39.50",  // Index 199
    "914c-g",  // Index 200
    "anet",  // Index 201
    "ipx",  // Index 202
    "vmpwscs",  // Index 203
    "softpc",  // Index 204
    "atls",  // Index 205
    "dbase",  // Index 206
    "mpp",  // Index 207
    "uarps",  // Index 208
    "imap3",  // Index 209
    "fln-spx",  // Index 210
    "rsh-spx",  // Index 211
    "cdc",  // Index 212
    "masqdialer",  // Index 213
    "direct",  // Index 214
    "sur-meas",  // Index 215
    "dayna",  // Index 216
    "link",  // Index 217
    "dsp3270",  // Index 218
    "subntbcst_tftp",  // Index 219
    "bhfhs",  // Index 220
    "fw1-secureremote",  // Index 221
    "fw1-mc-fwmodule",  // Index 222
    "set",  // Index 223
    "fw1-mc-gui",  // Index 224
    "yak-chat",  // Index 225
    "esro-gen",  // Index 226
    "firewall1-rdp",  // Index 227
    "openport",  // Index 228
    "nsiiops",  // Index 229
    "arcisdms",  // Index 230
    "hdap",  // Index 231
    "bgmp",  // Index 232
    "fw1-or-bgmp",  // Index 233
    "maybe-fw1",  // Index 234
    "x-bone-ctl",  // Index 235
    "sst",  // Index 236
    "td-service",  // Index 237
    "td-replica",  // Index 238
    "manet",  // Index 239
    "gist",  // Index 240
    "pt-tls",  // Index 241
    "http-mgmt",  // Index 242
    "personal-link",  // Index 243
    "cableport-ax",  // Index 244
    "rescap",  // Index 245
    "corerjd",  // Index 246
    "fxp",  // Index 247
    "k-block",  // Index 248
    "novastorbakcup",  // Index 249
    "entrusttime",  // Index 250
    "bhmds",  // Index 251
    "asip-webadmin",  // Index 252
    "vslmp",  // Index 253
    "magenta-logic",  // Index 254
    "opalis-robot",  // Index 255
    "dpsi",  // Index 256
    "decauth",  // Index 257
    "zannet",  // Index 258
    "pkix-timestamp",  // Index 259
    "ptp-event",  // Index 260
    "ptp-general",  // Index 261
    "pip",  // Index 262
    "rtsps",  // Index 263
    "rpki-rtr",  // Index 264
    "rpki-rtr-tls",  // Index 265
    "texar",  // Index 266
    "pdap",  // Index 267
    "pawserv",  // Index 268
    "zserv",  // Index 269
    "fatserv",  // Index 270
    "csi-sgwp",  // Index 271
    "mftp",  // Index 272
    "matip-type-a",  // Index 273
    "matip-type-b",  // Index 274
    "dtag-ste-sb",  // Index 275
    "ndsauth",  // Index 276
    "bh611",  // Index 277
    "datex-asn",  // Index 278
    "cloanto-net-1",  // Index 279
    "bhevent",  // Index 280
    "shrinkwrap",  // Index 281
    "tenebris_nts",  // Index 282
    "scoi2odialog",  // Index 283
    "semantix",  // Index 284
    "srssend",  // Index 285
    "rsvp_tunnel",  // Index 286
    "aurora-cmgr",  // Index 287
    "dtk",  // Index 288
    "odmr",  // Index 289
    "mortgageware",  // Index 290
    "qbikgdp",  // Index 291
    "rpc2portmap",  // Index 292
    "codaauth2",  // Index 293
    "clearcase",  // Index 294
    "ulistserv",  // Index 295
    "legent-1",  // Index 296
    "legent-2",  // Index 297
    "hassle",  // Index 298
    "nip",  // Index 299
    "tnETOS",  // Index 300
    "dsETOS",  // Index 301
    "is99c",  // Index 302
    "is99s",  // Index 303
    "hp-collector",  // Index 304
    "hp-managed-node",  // Index 305
    "hp-alarm-mgr",  // Index 306
    "arns",  // Index 307
    "ibm-app",  // Index 308
    "asa",  // Index 309
    "aurp",  // Index 310
    "unidata-ldm",  // Index 311
    "ldap",  // Index 312
    "uis",  // Index 313
    "synotics-relay",  // Index 314
    "synotics-broker",  // Index 315
    "dis",  // Index 316
    "embl-ndt",  // Index 317
    "netcp",  // Index 318
    "netware-ip",  // Index 319
    "mptn",  // Index 320
    "kryptolan",  // Index 321
    "iso-tsap-c2",  // Index 322
    "work-sol",  // Index 323
    "ups",  // Index 324
    "genie",  // Index 325
    "decap",  // Index 326
    "nced",  // Index 327
    "ncld",  // Index 328
    "imsp",  // Index 329
    "timbuktu",  // Index 330
    "prm-sm",  // Index 331
    "prm-nm",  // Index 332
    "decladebug",  // Index 333
    "rmt",  // Index 334
    "synoptics-trap",  // Index 335
    "smsp",  // Index 336
    "infoseek",  // Index 337
    "bnet",  // Index 338
    "silverplatter",  // Index 339
    "onmux",  // Index 340
    "hyper-g",  // Index 341
    "ariel1",  // Index 342
    "smpte",  // Index 343
    "ariel2",  // Index 344
    "ariel3",  // Index 345
    "opc-job-start",  // Index 346
    "opc-job-track",  // Index 347
    "icad-el",  // Index 348
    "smartsdp",  // Index 349
    "svrloc",  // Index 350
    "ocs_cmu",  // Index 351
    "ocs_amu",  // Index 352
    "utmpsd",  // Index 353
    "utmpcd",  // Index 354
    "iasd",  // Index 355
    "nnsp",  // Index 356
    "mobileip-agent",  // Index 357
    "mobilip-mn",  // Index 358
    "dna-cml",  // Index 359
    "comscm",  // Index 360
    "dsfgw",  // Index 361
    "dasp",  // Index 362
    "sgcp",  // Index 363
    "decvms-sysmgt",  // Index 364
    "cvc_hostd",  // Index 365
    "https",  // Index 366
    "snpp",  // Index 367
    "microsoft-ds",  // Index 368
    "ddm-rdb",  // Index 369
    "ddm-dfm",  // Index 370
    "ddm-ssl",  // Index 371
    "as-servermap",  // Index 372
    "tserver",  // Index 373
    "sfs-smp-net",  // Index 374
    "sfs-config",  // Index 375
    "creativeserver",  // Index 376
    "contentserver",  // Index 377
    "creativepartnr",  // Index 378
    "macon",  // Index 379
    "scohelp",  // Index 380
    "appleqtc",  // Index 381
    "ampr-rcmd",  // Index 382
    "skronk",  // Index 383
    "datasurfsrv",  // Index 384
    "datasurfsrvsec",  // Index 385
    "alpes",  // Index 386
    "kpasswd5",  // Index 387
    "smtps",  // Index 388
    "digital-vrc",  // Index 389
    "mylex-mapd",  // Index 390
    "photuris",  // Index 391
    "rcp",  // Index 392
    "scx-proxy",  // Index 393
    "mondex",  // Index 394
    "ljk-login",  // Index 395
    "hybrid-pop",  // Index 396
    "tn-tl-w1",  // Index 397
    "tn-tl-w2",  // Index 398
    "tcpnethaspsrv",  // Index 399
    "tn-tl-fd1",  // Index 400
    "ss7ns",  // Index 401
    "spsc",  // Index 402
    "iafserver",  // Index 403
    "loadsrv",  // Index 404
    "iafdbase",  // Index 405
    "dvs",  // Index 406
    "ph",  // Index 407
    "bgs-nsi",  // Index 408
    "xlog",  // Index 409
    "ulpnet",  // Index 410
    "integra-sme",  // Index 411
    "powerburst",  // Index 412
    "sstats",  // Index 413
    "avian",  // Index 414
    "saft",  // Index 415
    "gss-http",  // Index 416
    "nest-protocol",  // Index 417
    "micom-pfs",  // Index 418
    "go-login",  // Index 419
    "ticf-1",  // Index 420
    "ticf-2",  // Index 421
    "pov-ray",  // Index 422
    "intecourier",  // Index 423
    "pim-rp-disc",  // Index 424
    "retrospect",  // Index 425
    "siam",  // Index 426
    "iso-ill",  // Index 427
    "isakmp",  // Index 428
    "stmf",  // Index 429
    "mbap",  // Index 430
    "intrinsa",  // Index 431
    "citadel",  // Index 432
    "mailbox-lm",  // Index 433
    "ohimsrv",  // Index 434
    "crs",  // Index 435
    "xvttp",  // Index 436
    "snare",  // Index 437
    "fcp",  // Index 438
    "passgo",  // Index 439
    "exec",  // Index 440
    "biff",  // Index 441
    "login",  // Index 442
    "who",  // Index 443
    "shell",  // Index 444
    "syslog",  // Index 445
    "printer",  // Index 446
    "videotex",  // Index 447
    "talk",  // Index 448
    "ntalk",  // Index 449
    "utime",  // Index 450
    "efs",  // Index 451
    "route",  // Index 452
    "ripng",  // Index 453
    "ulp",  // Index 454
    "ibm-db2",  // Index 455
    "ncp",  // Index 456
    "timed",  // Index 457
    "tempo",  // Index 458
    "stx",  // Index 459
    "custix",  // Index 460
    "courier",  // Index 461
    "conference",  // Index 462
    "netnews",  // Index 463
    "netwall",  // Index 464
    "mm-admin",  // Index 465
    "iiop",  // Index 466
    "opalis-rdv",  // Index 467
    "nmsp",  // Index 468
    "gdomap",  // Index 469
    "apertus-ldp",  // Index 470
    "uucp",  // Index 471
    "uucp-rlogin",  // Index 472
    "commerce",  // Index 473
    "klogin",  // Index 474
    "kshell",  // Index 475
    "ekshell",  // Index 476
    "appleqtcsrvr",  // Index 477
    "dhcpv6-client",  // Index 478
    "dhcpv6-server",  // Index 479
    "afp",  // Index 480
    "idfp",  // Index 481
    "new-rwho",  // Index 482
    "cybercash",  // Index 483
    "deviceshare",  // Index 484
    "pirp",  // Index 485
    "rtsp",  // Index 486
    "dsf",  // Index 487
    "remotefs",  // Index 488
    "openvms-sysipc",  // Index 489
    "sdnskmp",  // Index 490
    "teedtap",  // Index 491
    "rmonitor",  // Index 492
    "monitor",  // Index 493
    "chshell",  // Index 494
    "snews",  // Index 495
    "9pfs",  // Index 496
    "whoami",  // Index 497
    "streettalk",  // Index 498
    "banyan-rpc",  // Index 499
    "ms-shuttle",  // Index 500
    "ms-rome",  // Index 501
    "meter",  // Index 502
    "umeter",  // Index 503
    "sonar",  // Index 504
    "banyan-vip",  // Index 505
    "ftp-agent",  // Index 506
    "vemmi",  // Index 507
    "ipcd",  // Index 508
    "vnas",  // Index 509
    "ipdd",  // Index 510
    "decbsrv",  // Index 511
    "sntp-heartbeat",  // Index 512
    "bdp",  // Index 513
    "scc-security",  // Index 514
    "philips-vc",  // Index 515
    "keyserver",  // Index 516
    "imap4-ssl",  // Index 517
    "password-chg",  // Index 518
    "submission",  // Index 519
    "cal",  // Index 520
    "eyelink",  // Index 521
    "tns-cml",  // Index 522
    "http-alt",  // Index 523
    "eudora-set",  // Index 524
    "http-rpc-epmap",  // Index 525
    "tpip",  // Index 526
    "cab-protocol",  // Index 527
    "smsd",  // Index 528
    "ptcnameservice",  // Index 529
    "sco-websrvrmg3",  // Index 530
    "acp",  // Index 531
    "ipcserver",  // Index 532
    "syslog-conn",  // Index 533
    "xmlrpc-beep",  // Index 534
    "mnotes",  // Index 535
    "idxp",  // Index 536
    "tunnel",  // Index 537
    "soap-beep",  // Index 538
    "urm",  // Index 539
    "nqs",  // Index 540
    "sift-uft",  // Index 541
    "npmp-trap",  // Index 542
    "npmp-local",  // Index 543
    "npmp-gui",  // Index 544
    "hmmp-ind",  // Index 545
    "hmmp-op",  // Index 546
    "sshell",  // Index 547
    "sco-inetmgr",  // Index 548
    "sco-sysmgr",  // Index 549
    "sco-dtmgr",  // Index 550
    "dei-icda",  // Index 551
    "compaq-evm",  // Index 552
    "sco-websrvrmgr",  // Index 553
    "escp-ip",  // Index 554
    "collaborator",  // Index 555
    "oob-ws-http",  // Index 556
    "asf-rmcp",  // Index 557
    "cryptoadmin",  // Index 558
    "apple-xsrvr-admin",  // Index 559
    "dec_dlm",  // Index 560
    "apple-imap-admin",  // Index 561
    "serialnumberd",  // Index 562
    "passgo-tivoli",  // Index 563
    "qmqp",  // Index 564
    "3com-amp3",  // Index 565
    "rda",  // Index 566
    "ipp",  // Index 567
    "bmpp",  // Index 568
    "servstat",  // Index 569
    "ginad",  // Index 570
    "rlzdbase",  // Index 571
    "mount",  // Index 572
    "ldapssl",  // Index 573
    "ldaps",  // Index 574
    "lanserver",  // Index 575
    "mcns-sec",  // Index 576
    "msdp",  // Index 577
    "entrust-sps",  // Index 578
    "pcnfs",  // Index 579
    "repcmd",  // Index 580
    "esro-emsdp",  // Index 581
    "sanity",  // Index 582
    "dwr",  // Index 583
    "pssc",  // Index 584
    "ldp",  // Index 585
    "dhcp-failover",  // Index 586
    "rrp",  // Index 587
    "cadview-3d",  // Index 588
    "obex",  // Index 589
    "bwnfs",  // Index 590
    "ieee-mms",  // Index 591
    "hello-port",  // Index 592
    "repscmd",  // Index 593
    "aodv",  // Index 594
    "tinc",  // Index 595
    "spmp",  // Index 596
    "rmc",  // Index 597
    "tenfold",  // Index 598
    "mac-srvr-admin",  // Index 599
    "hap",  // Index 600
    "pftp",  // Index 601
    "purenoise",  // Index 602
    "secure-aux-bus",  // Index 603
    "sun-dr",  // Index 604
    "doom",  // Index 605
    "disclose",  // Index 606
    "mecomm",  // Index 607
    "meregister",  // Index 608
    "vacdsm-sws",  // Index 609
    "vacdsm-app",  // Index 610
    "vpps-qua",  // Index 611
    "cimplex",  // Index 612
    "acap",  // Index 613
    "dctp",  // Index 614
    "vpps-via",  // Index 615
    "vpp",  // Index 616
    "ggf-ncp",  // Index 617
    "mrm",  // Index 618
    "entrust-aaas",  // Index 619
    "entrust-aams",  // Index 620
    "xfr",  // Index 621
    "corba-iiop",  // Index 622
    "corba-iiop-ssl",  // Index 623
    "mdc-portmapper",  // Index 624
    "hcp-wismar",  // Index 625
    "asipregistry",  // Index 626
    "realm-rusd",  // Index 627
    "nmap",  // Index 628
    "vatp",  // Index 629
    "resvc",  // Index 630
    "msexch-routing",  // Index 631
    "hyperwave-isp",  // Index 632
    "connendp",  // Index 633
    "ha-cluster",  // Index 634
    "ieee-mms-ssl",  // Index 635
    "rushd",  // Index 636
    "uuidgen",  // Index 637
    "olsr",  // Index 638
    "accessnetwork",  // Index 639
    "epp",  // Index 640
    "lmp",  // Index 641
    "iris-beep",  // Index 642
    "elcsd",  // Index 643
    "agentx",  // Index 644
    "silc",  // Index 645
    "borland-dsj",  // Index 646
    "entrustmanager",  // Index 647
    "entrust-ash",  // Index 648
    "cisco-tdp",  // Index 649
    "tbrpf",  // Index 650
    "iris-xpc",  // Index 651
    "iris-xpcs",  // Index 652
    "iris-lwz",  // Index 653
    "pana",  // Index 654
    "omfs",  // Index 655
    "netviewdm1",  // Index 656
    "netviewdm2",  // Index 657
    "netviewdm3",  // Index 658
    "sometimes-rpc2",  // Index 659
    "netgw",  // Index 660
    "netrcs",  // Index 661
    "flexlm",  // Index 662
    "fujitsu-dev",  // Index 663
    "ris-cm",  // Index 664
    "kerberos-adm",  // Index 665
    "kerberos",  // Index 666
    "kadmin",  // Index 667
    "qrh",  // Index 668
    "rrh",  // Index 669
    "krb_prop",  // Index 670
    "tell",  // Index 671
    "nlogin",  // Index 672
    "con",  // Index 673
    "krbupdate",  // Index 674
    "ns",  // Index 675
    "kpasswd",  // Index 676
    "rxe",  // Index 677
    "quotad",  // Index 678
    "cycleserv",  // Index 679
    "omserv",  // Index 680
    "webster",  // Index 681
    "phonebook",  // Index 682
    "vid",  // Index 683
    "cadlock",  // Index 684
    "rtip",  // Index 685
    "cycleserv2",  // Index 686
    "submit",  // Index 687
    "notify",  // Index 688
    "rpasswd",  // Index 689
    "acmaint_dbd",  // Index 690
    "entomb",  // Index 691
    "acmaint_transd",  // Index 692
    "wpages",  // Index 693
    "multiling-http",  // Index 694
    "wpgs",  // Index 695
    "spamassassin",  // Index 696
    "concert",  // Index 697
    "qsc",  // Index 698
    "controlit",  // Index 699
    "mdbs_daemon",  // Index 700
    "device",  // Index 701
    "mbap-s",  // Index 702
    "ccproxy-http",  // Index 703
    "fcp-udp",  // Index 704
    "itm-mcell-s",  // Index 705
    "pkix-3-ca-ra",  // Index 706
    "netconf-ssh",  // Index 707
    "netconf-beep",  // Index 708
    "netconfsoaphttp",  // Index 709
    "netconfsoapbeep",  // Index 710
    "dhcp-failover2",  // Index 711
    "gdoi",  // Index 712
    "domain-s",  // Index 713
    "dlep",  // Index 714
    "iscsi",  // Index 715
    "owamp-control",  // Index 716
    "twamp-control",  // Index 717
    "supfilesrv",  // Index 718
    "rsync",  // Index 719
    "iclcnet-locate",  // Index 720
    "iclcnet_svinfo",  // Index 721
    "accessbuilder",  // Index 722
    "sun-manageconsole",  // Index 723
    "omginitialrefs",  // Index 724
    "samba-swat",  // Index 725
    "smpnameres",  // Index 726
    "iss-realsecure",  // Index 727
    "ideafarm-door",  // Index 728
    "iss-console-mgr",  // Index 729
    "ideafarm-panic",  // Index 730
    "kink",  // Index 731
    "xact-backup",  // Index 732
    "apex-mesh",  // Index 733
    "apex-edge",  // Index 734
    "oftep-rpc",  // Index 735
    "rndc",  // Index 736
    "securenetpro-sensor",  // Index 737
    "ftps-data",  // Index 738
    "ftps",  // Index 739
    "nas",  // Index 740
    "telnets",  // Index 741
    "imaps",  // Index 742
    "ircs",  // Index 743
    "pop3s",  // Index 744
    "xtreelic",  // Index 745
    "vsinet",  // Index 746
    "maitrd",  // Index 747
    "busboy",  // Index 748
    "puparp",  // Index 749
    "garcon",  // Index 750
    "applix",  // Index 751
    "ock",  // Index 752
    "webpush",  // Index 753
    "windows-icfw",  // Index 754
    "ufsd",  // Index 755
    "surf",  // Index 756
    "sometimes-rpc1",  // Index 757
    "exp1",  // Index 758
    "exp2",  // Index 759
    "netvenuechat",  // Index 760
    "kdm",  // Index 761
    "NFS-or-IIS",  // Index 762
    "blackjack",  // Index 763
    "LSA-or-nterm",  // Index 764
    "win-rpc",  // Index 765
    "IIS",  // Index 766
    "ms-lsa",  // Index 767
    "solid-mux",  // Index 768
    "iad1",  // Index 769
    "iad2",  // Index 770
    "iad3",  // Index 771
    "netinfo",  // Index 772
    "netinfo-local",  // Index 773
    "zincite-a",  // Index 774
    "activesync-notify",  // Index 775
    "multidropper",  // Index 776
    "mxxrlogin",  // Index 777
    "nsstp",  // Index 778
    "ams",  // Index 779
    "mtqp",  // Index 780
    "sbl",  // Index 781
    "netsaint",  // Index 782
    "netarx",  // Index 783
    "danf-ak2",  // Index 784
    "afrog",  // Index 785
    "boinc",  // Index 786
    "dcutility",  // Index 787
    "fpitp",  // Index 788
    "wfremotertm",  // Index 789
    "neod1",  // Index 790
    "neod2",  // Index 791
    "td-postman",  // Index 792
    "java-or-OTGfileshare",  // Index 793
    "cma",  // Index 794
    "optima-vnet",  // Index 795
    "ddt",  // Index 796
    "remote-as",  // Index 797
    "brvread",  // Index 798
    "ansyslmd",  // Index 799
    "vfo",  // Index 800
    "startron",  // Index 801
    "nim",  // Index 802
    "nimreg",  // Index 803
    "polestar",  // Index 804
    "kiosk",  // Index 805
    "veracity",  // Index 806
    "kyoceranetdev",  // Index 807
    "jstel",  // Index 808
    "syscomlan",  // Index 809
    "fpo-fns",  // Index 810
    "instl_boots",  // Index 811
    "instl_bootc",  // Index 812
    "cognex-insight",  // Index 813
    "gmrupdateserv",  // Index 814
    "bsquare-voip",  // Index 815
    "cardax",  // Index 816
    "bridgecontrol",  // Index 817
    "warmspotMgmt",  // Index 818
    "rdrmshc",  // Index 819
    "sns_credit",  // Index 820
    "dab-sti-c",  // Index 821
    "imgames",  // Index 822
    "avocent-proxy",  // Index 823
    "asprovatalk",  // Index 824
    "socks",  // Index 825
    "pvuniwien",  // Index 826
    "amt-esd-prot",  // Index 827
    "ansoft-lm-1",  // Index 828
    "ansoft-lm-2",  // Index 829
    "webobjects",  // Index 830
    "cplscrambler-lg",  // Index 831
    "cplscrambler-in",  // Index 832
    "cplscrambler-al",  // Index 833
    "ff-annunc",  // Index 834
    "ff-fms",  // Index 835
    "ff-sm",  // Index 836
    "obrpd",  // Index 837
    "proofd",  // Index 838
    "rootd",  // Index 839
    "nicelink",  // Index 840
    "cnrprotocol",  // Index 841
    "sunclustermgr",  // Index 842
    "rmiactivation",  // Index 843
    "rmiregistry",  // Index 844
    "mctp",  // Index 845
    "pt2-discover",  // Index 846
    "adobeserver-1",  // Index 847
    "xaudio",  // Index 848
    "adobeserver-2",  // Index 849
    "xrl",  // Index 850
    "ftranhc",  // Index 851
    "isoipsigport-1",  // Index 852
    "isoipsigport-2",  // Index 853
    "ratio-adp",  // Index 854
    "kpop",  // Index 855
    "nfsd-status",  // Index 856
    "nfsd-keepalive",  // Index 857
    "lmsocialserver",  // Index 858
    "msql",  // Index 859
    "icp",  // Index 860
    "ltp-deepspace",  // Index 861
    "mini-sql",  // Index 862
    "ardus-trns",  // Index 863
    "ardus-cntl",  // Index 864
    "ardus-mtrns",  // Index 865
    "sacred",  // Index 866
    "bnetgame",  // Index 867
    "bnetfile",  // Index 868
    "rmpp",  // Index 869
    "availant-mgr",  // Index 870
    "murray",  // Index 871
    "hpvmmcontrol",  // Index 872
    "hpvmmagent",  // Index 873
    "hpvmmdata",  // Index 874
    "supfiledbg",  // Index 875
    "kwdb-commn",  // Index 876
    "saphostctrl",  // Index 877
    "saphostctrls",  // Index 878
    "casp",  // Index 879
    "caspssl",  // Index 880
    "kvm-via-ip",  // Index 881
    "dfn",  // Index 882
    "aplx",  // Index 883
    "omnivision",  // Index 884
    "hhb-gateway",  // Index 885
    "trim",  // Index 886
    "encrypted_admin",  // Index 887
    "cce3x",  // Index 888
    "evm",  // Index 889
    "autonoc",  // Index 890
    "mxomss",  // Index 891
    "edtools",  // Index 892
    "imyx",  // Index 893
    "fuscript",  // Index 894
    "x9-icue",  // Index 895
    "audit-transfer",  // Index 896
    "capioverlan",  // Index 897
    "elfiq-repl",  // Index 898
    "bvtsonar",  // Index 899
    "blaze",  // Index 900
    "unizensus",  // Index 901
    "winpoplanmess",  // Index 902
    "c1222-acse",  // Index 903
    "resacommunity",  // Index 904
    "nfa",  // Index 905
    "iascontrol-oms",  // Index 906
    "iascontrol",  // Index 907
    "lsnr",  // Index 908
    "dbcontrol-oms",  // Index 909
    "oracle-oms",  // Index 910
    "olsv",  // Index 911
    "health-polling",  // Index 912
    "health-trap",  // Index 913
    "sddp",  // Index 914
    "qsm-proxy",  // Index 915
    "qsm-gui",  // Index 916
    "qsm-remote",  // Index 917
    "cisco-ipsla",  // Index 918
    "vchat",  // Index 919
    "tripwire",  // Index 920
    "atc-lm",  // Index 921
    "atc-appserver",  // Index 922
    "dnap",  // Index 923
    "d-cinema-rrp",  // Index 924
    "fnet-remote-ui",  // Index 925
    "dossier",  // Index 926
    "indigo-server",  // Index 927
    "dkmessenger",  // Index 928
    "skkserv",  // Index 929
    "sgi-storman",  // Index 930
    "b2n",  // Index 931
    "mc-client",  // Index 932
    "3comnetman",  // Index 933
    "accelenet",  // Index 934
    "accelenet-data",  // Index 935
    "llsurfup-http",  // Index 936
    "llsurfup-https",  // Index 937
    "catchpole",  // Index 938
    "mysql-cluster",  // Index 939
    "alias",  // Index 940
    "hp-webadmin",  // Index 941
    "unet",  // Index 942
    "commlinx-avl",  // Index 943
    "gpfs",  // Index 944
    "caids-sensor",  // Index 945
    "fiveacross",  // Index 946
    "openvpn",  // Index 947
    "rsf-1",  // Index 948
    "netmagic",  // Index 949
    "carrius-rshell",  // Index 950
    "cajo-discovery",  // Index 951
    "dmidi",  // Index 952
    "scol",  // Index 953
    "nucleus-sand",  // Index 954
    "caiccipc",  // Index 955
    "ssslic-mgr",  // Index 956
    "ssslog-mgr",  // Index 957
    "accord-mgc",  // Index 958
    "anthony-data",  // Index 959
    "metasage",  // Index 960
    "seagull-ais",  // Index 961
    "ipcd3",  // Index 962
    "eoss",  // Index 963
    "groove-dpp",  // Index 964
    "lupa",  // Index 965
    "mpc-lifenet",  // Index 966
    "fasttrack",  // Index 967
    "scanstat-1",  // Index 968
    "etebac5",  // Index 969
    "hpss-ndapi",  // Index 970
    "aeroflight-ads",  // Index 971
    "aeroflight-ret",  // Index 972
    "quicktime",  // Index 973
    "qt-serveradmin",  // Index 974
    "sweetware-apps",  // Index 975
    "nerv",  // Index 976
    "tgp",  // Index 977
    "vpnz",  // Index 978
    "slinkysearch",  // Index 979
    "stgxfws",  // Index 980
    "dns2go",  // Index 981
    "florence",  // Index 982
    "zented",  // Index 983
    "periscope",  // Index 984
    "menandmice-lpm",  // Index 985
    "first-defense",  // Index 986
    "univ-appserver",  // Index 987
    "hotline",  // Index 988
    "search-agent",  // Index 989
    "mosaicsyssvc1",  // Index 990
    "bvcontrol",  // Index 991
    "tsdos390",  // Index 992
    "hacl-qs",  // Index 993
    "nmsd",  // Index 994
    "instantia",  // Index 995
    "nessus",  // Index 996
    "nmasoverip",  // Index 997
    "serialgateway",  // Index 998
    "isbconference1",  // Index 999
    "isbconference2",  // Index 1000
    "payrouter",  // Index 1001
    "visionpyramid",  // Index 1002
    "hermes",  // Index 1003
    "mesavistaco",  // Index 1004
    "swldy-sias",  // Index 1005
    "servergraph",  // Index 1006
    "bspne-pcc",  // Index 1007
    "q55-pcc",  // Index 1008
    "de-noc",  // Index 1009
    "de-cache-query",  // Index 1010
    "de-server",  // Index 1011
    "shockwave2",  // Index 1012
    "opennl",  // Index 1013
    "opennl-voice",  // Index 1014
    "ibm-ssd",  // Index 1015
    "mpshrsv",  // Index 1016
    "qnts-orb",  // Index 1017
    "dka",  // Index 1018
    "prat",  // Index 1019
    "dssiapi",  // Index 1020
    "dellpwrappks",  // Index 1021
    "epc",  // Index 1022
    "propel-msgsys",  // Index 1023
    "watilapp",  // Index 1024
    "ssserver",  // Index 1025
    "opsmgr",  // Index 1026
    "excw",  // Index 1027
    "cspmlockmgr",  // Index 1028
    "emc-gateway",  // Index 1029
    "t1distproc",  // Index 1030
    "ivcollector",  // Index 1031
    "ivmanager",  // Index 1032
    "miva-mqs",  // Index 1033
    "dellwebadmin-1",  // Index 1034
    "dellwebadmin-2",  // Index 1035
    "pictrography",  // Index 1036
    "healthd",  // Index 1037
    "emperion",  // Index 1038
    "productinfo",  // Index 1039
    "iee-qfx",  // Index 1040
    "neoiface",  // Index 1041
    "netuitive",  // Index 1042
    "routematch",  // Index 1043
    "navbuddy",  // Index 1044
    "jwalkserver",  // Index 1045
    "winjaserver",  // Index 1046
    "seagulllms",  // Index 1047
    "dsdn",  // Index 1048
    "pkt-krb-ipsec",  // Index 1049
    "cmmdriver",  // Index 1050
    "ehtp",  // Index 1051
    "dproxy",  // Index 1052
    "sdproxy",  // Index 1053
    "lpcp",  // Index 1054
    "hp-sci",  // Index 1055
    "h323hostcallsc",  // Index 1056
    "ci3-software-1",  // Index 1057
    "ci3-software-2",  // Index 1058
    "sftsrv",  // Index 1059
    "boomerang",  // Index 1060
    "pe-mike",  // Index 1061
    "re-conn-proto",  // Index 1062
    "pacmand",  // Index 1063
    "odsi",  // Index 1064
    "jtag-server",  // Index 1065
    "husky",  // Index 1066
    "rxmon",  // Index 1067
    "sti-envision",  // Index 1068
    "bmc_patroldb",  // Index 1069
    "pdps",  // Index 1070
    "els",  // Index 1071
    "exbit-escp",  // Index 1072
    "vrts-ipcserver",  // Index 1073
    "krb5gatekeeper",  // Index 1074
    "amx-icsp",  // Index 1075
    "amx-axbnet",  // Index 1076
    "novation",  // Index 1077
    "brcd",  // Index 1078
    "delta-mcp",  // Index 1079
    "dx-instrument",  // Index 1080
    "wimsic",  // Index 1081
    "ultrex",  // Index 1082
    "ewall",  // Index 1083
    "netdb-export",  // Index 1084
    "streetperfect",  // Index 1085
    "intersan",  // Index 1086
    "pcia-rxp-b",  // Index 1087
    "passwrd-policy",  // Index 1088
    "writesrv",  // Index 1089
    "digital-notary",  // Index 1090
    "ischat",  // Index 1091
    "waste",  // Index 1092
    "menandmice-dns",  // Index 1093
    "wmc-log-svc",  // Index 1094
    "kjtsiteserver",  // Index 1095
    "naap",  // Index 1096
    "qubes",  // Index 1097
    "esbroker",  // Index 1098
    "re101",  // Index 1099
    "icap",  // Index 1100
    "vpjp",  // Index 1101
    "alta-ana-lm",  // Index 1102
    "bbn-mmc",  // Index 1103
    "bbn-mmx",  // Index 1104
    "sbook",  // Index 1105
    "editbench",  // Index 1106
    "equationbuilder",  // Index 1107
    "lotusnotes",  // Index 1108
    "relief",  // Index 1109
    "rightbrain",  // Index 1110
    "intuitive-edge",  // Index 1111
    "cuillamartin",  // Index 1112
    "pegboard",  // Index 1113
    "connlcli",  // Index 1114
    "ftsrv",  // Index 1115
    "mimer",  // Index 1116
    "linx",  // Index 1117
    "timeflies",  // Index 1118
    "ndm-requester",  // Index 1119
    "ndm-server",  // Index 1120
    "adapt-sna",  // Index 1121
    "netware-csp",  // Index 1122
    "dcs",  // Index 1123
    "screencast",  // Index 1124
    "gv-us",  // Index 1125
    "us-gv",  // Index 1126
    "fc-cli",  // Index 1127
    "fc-ser",  // Index 1128
    "chromagrafx",  // Index 1129
    "molly",  // Index 1130
    "bytex",  // Index 1131
    "ibm-pps",  // Index 1132
    "cichlid",  // Index 1133
    "elan",  // Index 1134
    "dbreporter",  // Index 1135
    "telesis-licman",  // Index 1136
    "apple-licman",  // Index 1137
    "udt_os",  // Index 1138
    "gwha",  // Index 1139
    "os-licman",  // Index 1140
    "atex_elmd",  // Index 1141
    "checksum",  // Index 1142
    "cadsi-lm",  // Index 1143
    "objective-dbc",  // Index 1144
    "iclpv-dm",  // Index 1145
    "iclpv-sc",  // Index 1146
    "iclpv-sas",  // Index 1147
    "iclpv-pm",  // Index 1148
    "iclpv-nls",  // Index 1149
    "iclpv-nlc",  // Index 1150
    "iclpv-wsm",  // Index 1151
    "dvl-activemail",  // Index 1152
    "audio-activmail",  // Index 1153
    "video-activmail",  // Index 1154
    "cadkey-licman",  // Index 1155
    "cadkey-tablet",  // Index 1156
    "goldleaf-licman",  // Index 1157
    "prm-sm-np",  // Index 1158
    "prm-nm-np",  // Index 1159
    "igi-lm",  // Index 1160
    "ibm-res",  // Index 1161
    "netlabs-lm",  // Index 1162
    "dbsa-lm",  // Index 1163
    "sophia-lm",  // Index 1164
    "here-lm",  // Index 1165
    "hiq",  // Index 1166
    "af",  // Index 1167
    "innosys",  // Index 1168
    "innosys-acl",  // Index 1169
    "ibm-mqseries",  // Index 1170
    "dbstar",  // Index 1171
    "novell-lu6.2",  // Index 1172
    "timbuktu-srv1",  // Index 1173
    "timbuktu-srv2",  // Index 1174
    "timbuktu-srv3",  // Index 1175
    "timbuktu-srv4",  // Index 1176
    "gandalf-lm",  // Index 1177
    "autodesk-lm",  // Index 1178
    "essbase",  // Index 1179
    "hybrid",  // Index 1180
    "zion-lm",  // Index 1181
    "sas-1",  // Index 1182
    "mloadd",  // Index 1183
    "informatik-lm",  // Index 1184
    "nms",  // Index 1185
    "tpdu",  // Index 1186
    "rgtp",  // Index 1187
    "blueberry-lm",  // Index 1188
    "ms-sql-s",  // Index 1189
    "ms-sql-m",  // Index 1190
    "ibm-cics",  // Index 1191
    "sas-2",  // Index 1192
    "tabula",  // Index 1193
    "eicon-server",  // Index 1194
    "eicon-x25",  // Index 1195
    "eicon-slp",  // Index 1196
    "cadis-1",  // Index 1197
    "cadis-2",  // Index 1198
    "ies-lm",  // Index 1199
    "marcam-lm",  // Index 1200
    "proxima-lm",  // Index 1201
    "ora-lm",  // Index 1202
    "apri-lm",  // Index 1203
    "oc-lm",  // Index 1204
    "peport",  // Index 1205
    "dwf",  // Index 1206
    "infoman",  // Index 1207
    "gtegsc-lm",  // Index 1208
    "genie-lm",  // Index 1209
    "interhdl_elmd",  // Index 1210
    "esl-lm",  // Index 1211
    "dca",  // Index 1212
    "valisys-lm",  // Index 1213
    "nrcabq-lm",  // Index 1214
    "proshare1",  // Index 1215
    "proshare2",  // Index 1216
    "ibm_wrless_lan",  // Index 1217
    "world-lm",  // Index 1218
    "nucleus",  // Index 1219
    "msl_lmd",  // Index 1220
    "pipes",  // Index 1221
    "oceansoft-lm",  // Index 1222
    "csdmbase",  // Index 1223
    "csdm",  // Index 1224
    "aal-lm",  // Index 1225
    "uaiact",  // Index 1226
    "openmath",  // Index 1227
    "telefinder",  // Index 1228
    "taligent-lm",  // Index 1229
    "clvm-cfg",  // Index 1230
    "ms-sna-server",  // Index 1231
    "ms-sna-base",  // Index 1232
    "dberegister",  // Index 1233
    "pacerforum",  // Index 1234
    "airs",  // Index 1235
    "miteksys-lm",  // Index 1236
    "afs",  // Index 1237
    "confluent",  // Index 1238
    "lansource",  // Index 1239
    "nms_topo_serv",  // Index 1240
    "localinfosrvr",  // Index 1241
    "docstor",  // Index 1242
    "dmdocbroker",  // Index 1243
    "insitu-conf",  // Index 1244
    "anynetgateway",  // Index 1245
    "stone-design-1",  // Index 1246
    "netmap_lm",  // Index 1247
    "citrix-ica",  // Index 1248
    "cvc",  // Index 1249
    "liberty-lm",  // Index 1250
    "rfx-lm",  // Index 1251
    "watcom-sql",  // Index 1252
    "fhc",  // Index 1253
    "vlsi-lm",  // Index 1254
    "sas-3",  // Index 1255
    "shivadiscovery",  // Index 1256
    "imtc-mcs",  // Index 1257
    "evb-elm",  // Index 1258
    "funkproxy",  // Index 1259
    "utcd",  // Index 1260
    "symplex",  // Index 1261
    "diagmond",  // Index 1262
    "robcad-lm",  // Index 1263
    "mvx-lm",  // Index 1264
    "3l-l1",  // Index 1265
    "wins",  // Index 1266
    "fujitsu-dtc",  // Index 1267
    "fujitsu-dtcns",  // Index 1268
    "ifor-protocol",  // Index 1269
    "vpad",  // Index 1270
    "vpac",  // Index 1271
    "vpvd",  // Index 1272
    "vpvc",  // Index 1273
    "atm-zip-office",  // Index 1274
    "oracle",  // Index 1275
    "ncube-lm",  // Index 1276
    "rna-lm",  // Index 1277
    "cichild-lm",  // Index 1278
    "ingreslock",  // Index 1279
    "orasrv",  // Index 1280
    "pdap-np",  // Index 1281
    "tlisrv",  // Index 1282
    "mciautoreg",  // Index 1283
    "support",  // Index 1284
    "coauthor",  // Index 1285
    "rap-service",  // Index 1286
    "rap-listen",  // Index 1287
    "miroconnect",  // Index 1288
    "virtual-places",  // Index 1289
    "micromuse-lm",  // Index 1290
    "ampr-info",  // Index 1291
    "ampr-inter",  // Index 1292
    "sdsc-lm",  // Index 1293
    "3ds-lm",  // Index 1294
    "intellistor-lm",  // Index 1295
    "rds",  // Index 1296
    "rds2",  // Index 1297
    "gridgen-elmd",  // Index 1298
    "simba-cs",  // Index 1299
    "aspeclmd",  // Index 1300
    "vistium-share",  // Index 1301
    "abbaccuray",  // Index 1302
    "laplink",  // Index 1303
    "axon-lm",  // Index 1304
    "shivahose",  // Index 1305
    "shivasound",  // Index 1306
    "3m-image-lm",  // Index 1307
    "hecmtl-db",  // Index 1308
    "pciarray",  // Index 1309
    "sna-cs",  // Index 1310
    "caci-lm",  // Index 1311
    "livelan",  // Index 1312
    "veritas_pbx",  // Index 1313
    "arbortext-lm",  // Index 1314
    "xingmpeg",  // Index 1315
    "web2host",  // Index 1316
    "asci-val",  // Index 1317
    "facilityview",  // Index 1318
    "pconnectmgr",  // Index 1319
    "cadabra-lm",  // Index 1320
    "pay-per-view",  // Index 1321
    "winddlb",  // Index 1322
    "corelvideo",  // Index 1323
    "jlicelmd",  // Index 1324
    "tsspmap",  // Index 1325
    "ets",  // Index 1326
    "orbixd",  // Index 1327
    "rdb-dbs-disp",  // Index 1328
    "chip-lm",  // Index 1329
    "itscomm-ns",  // Index 1330
    "mvel-lm",  // Index 1331
    "oraclenames",  // Index 1332
    "moldflow-lm",  // Index 1333
    "hypercube-lm",  // Index 1334
    "jacobus-lm",  // Index 1335
    "ioc-sea-lm",  // Index 1336
    "tn-tl-r1",  // Index 1337
    "tn-tl-r2",  // Index 1338
    "mil-2045-47001",  // Index 1339
    "msims",  // Index 1340
    "simbaexpress",  // Index 1341
    "tn-tl-fd2",  // Index 1342
    "intv",  // Index 1343
    "ibm-abtact",  // Index 1344
    "pra_elmd",  // Index 1345
    "triquest-lm",  // Index 1346
    "vqp",  // Index 1347
    "gemini-lm",  // Index 1348
    "ncpm-pm",  // Index 1349
    "commonspace",  // Index 1350
    "mainsoft-lm",  // Index 1351
    "sixtrak",  // Index 1352
    "radio",  // Index 1353
    "radio-sm",  // Index 1354
    "radio-bc",  // Index 1355
    "orbplus-iiop",  // Index 1356
    "picknfs",  // Index 1357
    "simbaservices",  // Index 1358
    "issd",  // Index 1359
    "aas",  // Index 1360
    "inspect",  // Index 1361
    "picodbc",  // Index 1362
    "icabrowser",  // Index 1363
    "slp",  // Index 1364
    "slm-api",  // Index 1365
    "stt",  // Index 1366
    "smart-lm",  // Index 1367
    "isysg-lm",  // Index 1368
    "taurus-wh",  // Index 1369
    "ill",  // Index 1370
    "netbill-trans",  // Index 1371
    "netbill-keyrep",  // Index 1372
    "netbill-cred",  // Index 1373
    "netbill-auth",  // Index 1374
    "netbill-prod",  // Index 1375
    "nimrod-agent",  // Index 1376
    "skytelnet",  // Index 1377
    "xs-openstorage",  // Index 1378
    "faxportwinport",  // Index 1379
    "softdataphone",  // Index 1380
    "ontime",  // Index 1381
    "jaleosnd",  // Index 1382
    "udp-sr-port",  // Index 1383
    "svs-omagent",  // Index 1384
    "shockwave",  // Index 1385
    "t128-gateway",  // Index 1386
    "lontalk-norm",  // Index 1387
    "lontalk-urgnt",  // Index 1388
    "oraclenet8cman",  // Index 1389
    "visitview",  // Index 1390
    "pammratc",  // Index 1391
    "pammrpc",  // Index 1392
    "loaprobe",  // Index 1393
    "edb-server1",  // Index 1394
    "isdc",  // Index 1395
    "islc",  // Index 1396
    "ismc",  // Index 1397
    "cert-initiator",  // Index 1398
    "cert-responder",  // Index 1399
    "invision",  // Index 1400
    "isis-am",  // Index 1401
    "isis-ambc",  // Index 1402
    "saiseh",  // Index 1403
    "sightline",  // Index 1404
    "radius",  // Index 1405
    "sa-msg-port",  // Index 1406
    "radacct",  // Index 1407
    "rsap",  // Index 1408
    "concurrent-lm",  // Index 1409
    "kermit",  // Index 1410
    "nkd",  // Index 1411
    "shiva_confsrvr",  // Index 1412
    "xnmp",  // Index 1413
    "alphatech-lm",  // Index 1414
    "stargatealerts",  // Index 1415
    "dec-mbadmin",  // Index 1416
    "dec-mbadmin-h",  // Index 1417
    "fujitsu-mmpdc",  // Index 1418
    "sixnetudr",  // Index 1419
    "sg-lm",  // Index 1420
    "skip-mc-gikreq",  // Index 1421
    "netview-aix-1",  // Index 1422
    "netview-aix-2",  // Index 1423
    "netview-aix-3",  // Index 1424
    "netview-aix-4",  // Index 1425
    "netview-aix-5",  // Index 1426
    "netview-aix-6",  // Index 1427
    "netview-aix-7",  // Index 1428
    "netview-aix-8",  // Index 1429
    "netview-aix-9",  // Index 1430
    "netview-aix-10",  // Index 1431
    "netview-aix-11",  // Index 1432
    "netview-aix-12",  // Index 1433
    "proshare-mc-1",  // Index 1434
    "proshare-mc-2",  // Index 1435
    "pdp",  // Index 1436
    "netcomm1",  // Index 1437
    "netcomm2",  // Index 1438
    "groupwise",  // Index 1439
    "prolink",  // Index 1440
    "darcorp-lm",  // Index 1441
    "CarbonCopy",  // Index 1442
    "microcom-sbp",  // Index 1443
    "sd-elmd",  // Index 1444
    "lanyon-lantern",  // Index 1445
    "ncpm-hip",  // Index 1446
    "snaresecure",  // Index 1447
    "n2nremote",  // Index 1448
    "cvmon",  // Index 1449
    "nsjtp-ctrl",  // Index 1450
    "nsjtp-data",  // Index 1451
    "firefox",  // Index 1452
    "ng-umds",  // Index 1453
    "empire-empuma",  // Index 1454
    "sstsys-lm",  // Index 1455
    "rrirtr",  // Index 1456
    "rrimwm",  // Index 1457
    "rrilwm",  // Index 1458
    "rrifmm",  // Index 1459
    "rrisat",  // Index 1460
    "rsvp-encap-1",  // Index 1461
    "rsvp-encap-2",  // Index 1462
    "mps-raft",  // Index 1463
    "l2f",  // Index 1464
    "L2TP",  // Index 1465
    "deskshare",  // Index 1466
    "hb-engine",  // Index 1467
    "bcs-broker",  // Index 1468
    "slingshot",  // Index 1469
    "jetform",  // Index 1470
    "vdmplay",  // Index 1471
    "gat-lmd",  // Index 1472
    "centra",  // Index 1473
    "impera",  // Index 1474
    "pptconference",  // Index 1475
    "registrar",  // Index 1476
    "conferencetalk",  // Index 1477
    "sesi-lm",  // Index 1478
    "houdini-lm",  // Index 1479
    "xmsg",  // Index 1480
    "fj-hdnet",  // Index 1481
    "h323gatedisc",  // Index 1482
    "h225gatedisc",  // Index 1483
    "h323gatestat",  // Index 1484
    "h323q931",  // Index 1485
    "h323hostcall",  // Index 1486
    "caicci",  // Index 1487
    "hks-lm",  // Index 1488
    "pptp",  // Index 1489
    "csbphone",  // Index 1490
    "iden-ralp",  // Index 1491
    "iberiagames",  // Index 1492
    "winddx",  // Index 1493
    "telindus",  // Index 1494
    "citynl",  // Index 1495
    "roketz",  // Index 1496
    "msiccp",  // Index 1497
    "proxim",  // Index 1498
    "siipat",  // Index 1499
    "cambertx-lm",  // Index 1500
    "privatechat",  // Index 1501
    "street-stream",  // Index 1502
    "ultimad",  // Index 1503
    "gamegen1",  // Index 1504
    "webaccess",  // Index 1505
    "encore",  // Index 1506
    "cisco-net-mgmt",  // Index 1507
    "3Com-nsd",  // Index 1508
    "cinegrfx-lm",  // Index 1509
    "ncpm-ft",  // Index 1510
    "remote-winsock",  // Index 1511
    "ftrapid-1",  // Index 1512
    "ftrapid-2",  // Index 1513
    "oracle-em1",  // Index 1514
    "aspen-services",  // Index 1515
    "sslp",  // Index 1516
    "swiftnet",  // Index 1517
    "lofr-lm",  // Index 1518
    "predatar-comms",  // Index 1519
    "oracle-em2",  // Index 1520
    "wms",  // Index 1521
    "ms-streaming",  // Index 1522
    "capfast-lmd",  // Index 1523
    "cnhrp",  // Index 1524
    "tftp-mcast",  // Index 1525
    "spss-lm",  // Index 1526
    "www-ldap-gw",  // Index 1527
    "landesk-rc",  // Index 1528
    "cft-0",  // Index 1529
    "cft-1",  // Index 1530
    "cft-2",  // Index 1531
    "cft-3",  // Index 1532
    "cft-4",  // Index 1533
    "cft-5",  // Index 1534
    "cft-6",  // Index 1535
    "cft-7",  // Index 1536
    "bmc-net-adm",  // Index 1537
    "bmc-net-svc",  // Index 1538
    "vaultbase",  // Index 1539
    "essweb-gw",  // Index 1540
    "kmscontrol",  // Index 1541
    "global-dtserv",  // Index 1542
    "vdab",  // Index 1543
    "femis",  // Index 1544
    "powerguardian",  // Index 1545
    "prodigy-intrnet",  // Index 1546
    "pharmasoft",  // Index 1547
    "dpkeyserv",  // Index 1548
    "answersoft-lm",  // Index 1549
    "hp-hcip",  // Index 1550
    "finle-lm",  // Index 1551
    "windlm",  // Index 1552
    "funk-logger",  // Index 1553
    "funk-license",  // Index 1554
    "psmond",  // Index 1555
    "hello",  // Index 1556
    "ea1",  // Index 1557
    "ibm-dt-2",  // Index 1558
    "rsc-robot",  // Index 1559
    "cera-bcm",  // Index 1560
    "dpi-proxy",  // Index 1561
    "vocaltec-admin",  // Index 1562
    "uma",  // Index 1563
    "etp",  // Index 1564
    "netrisk",  // Index 1565
    "ansys-lm",  // Index 1566
    "msmq",  // Index 1567
    "concomp1",  // Index 1568
    "hp-hcip-gwy",  // Index 1569
    "enl",  // Index 1570
    "enl-name",  // Index 1571
    "musiconline",  // Index 1572
    "fhsp",  // Index 1573
    "oracle-vp2",  // Index 1574
    "oracle-vp1",  // Index 1575
    "jerand-lm",  // Index 1576
    "scientia-sdb",  // Index 1577
    "radius-acct",  // Index 1578
    "tdp-suite",  // Index 1579
    "mmpft",  // Index 1580
    "harp",  // Index 1581
    "rkb-oscs",  // Index 1582
    "etftp",  // Index 1583
    "plato-lm",  // Index 1584
    "mcagent",  // Index 1585
    "donnyworld",  // Index 1586
    "es-elmd",  // Index 1587
    "unisys-lm",  // Index 1588
    "metrics-pas",  // Index 1589
    "direcpc-video",  // Index 1590
    "ardt",  // Index 1591
    "pcm",  // Index 1592
    "asi",  // Index 1593
    "itm-mcell-u",  // Index 1594
    "optika-emedia",  // Index 1595
    "net8-cman",  // Index 1596
    "myrtle",  // Index 1597
    "tht-treasure",  // Index 1598
    "udpradio",  // Index 1599
    "ardusuni",  // Index 1600
    "ardusmul",  // Index 1601
    "ste-smsc",  // Index 1602
    "csoft1",  // Index 1603
    "talnet",  // Index 1604
    "netopia-vo1",  // Index 1605
    "netopia-vo2",  // Index 1606
    "netopia-vo3",  // Index 1607
    "netopia-vo4",  // Index 1608
    "netopia-vo5",  // Index 1609
    "direcpc-dll",  // Index 1610
    "altalink",  // Index 1611
    "tunstall-pnc",  // Index 1612
    "slp-notify",  // Index 1613
    "fjdocdist",  // Index 1614
    "alpha-sms",  // Index 1615
    "gsi",  // Index 1616
    "ctcd",  // Index 1617
    "virtual-time",  // Index 1618
    "vids-avtp",  // Index 1619
    "buddy-draw",  // Index 1620
    "fiorano-rtrsvc",  // Index 1621
    "fiorano-msgsvc",  // Index 1622
    "datacaptor",  // Index 1623
    "privateark",  // Index 1624
    "gammafetchsvr",  // Index 1625
    "sunscalar-svc",  // Index 1626
    "lecroy-vicp",  // Index 1627
    "mysql-cm-agent",  // Index 1628
    "msnp",  // Index 1629
    "paradym-31",  // Index 1630
    "entp",  // Index 1631
    "swrmi",  // Index 1632
    "udrive",  // Index 1633
    "viziblebrowser",  // Index 1634
    "transact",  // Index 1635
    "sunscalar-dns",  // Index 1636
    "canocentral0",  // Index 1637
    "canocentral1",  // Index 1638
    "fjmpjps",  // Index 1639
    "fjswapsnp",  // Index 1640
    "westell-stats",  // Index 1641
    "ewcappsrv",  // Index 1642
    "hp-webqosdb",  // Index 1643
    "drmsmc",  // Index 1644
    "nettgain-nms",  // Index 1645
    "vsat-control",  // Index 1646
    "ibm-mqseries2",  // Index 1647
    "ecsqdmn",  // Index 1648
    "mqtt",  // Index 1649
    "ibm-mqisdp",  // Index 1650
    "idmaps",  // Index 1651
    "vrtstrapserver",  // Index 1652
    "leoip",  // Index 1653
    "filex-lport",  // Index 1654
    "ncconfig",  // Index 1655
    "unify-adapter",  // Index 1656
    "wilkenlistener",  // Index 1657
    "childkey-notif",  // Index 1658
    "childkey-ctrl",  // Index 1659
    "elad",  // Index 1660
    "o2server-port",  // Index 1661
    "b-novative-ls",  // Index 1662
    "metaagent",  // Index 1663
    "cymtec-port",  // Index 1664
    "mc2studios",  // Index 1665
    "upnp",  // Index 1666
    "fjicl-tep-a",  // Index 1667
    "fjicl-tep-b",  // Index 1668
    "linkname",  // Index 1669
    "fjicl-tep-c",  // Index 1670
    "sugp",  // Index 1671
    "tpmd",  // Index 1672
    "intrastar",  // Index 1673
    "dawn",  // Index 1674
    "global-wlink",  // Index 1675
    "ultrabac",  // Index 1676
    "mtp",  // Index 1677
    "rhp-iibp",  // Index 1678
    "armadp",  // Index 1679
    "elm-momentum",  // Index 1680
    "facelink",  // Index 1681
    "persona",  // Index 1682
    "noagent",  // Index 1683
    "can-nds",  // Index 1684
    "can-dch",  // Index 1685
    "can-ferret",  // Index 1686
    "noadmin",  // Index 1687
    "tapestry",  // Index 1688
    "spice",  // Index 1689
    "xiip",  // Index 1690
    "discovery-port",  // Index 1691
    "egs",  // Index 1692
    "videte-cipc",  // Index 1693
    "emsd-port",  // Index 1694
    "bandwiz-system",  // Index 1695
    "driveappserver",  // Index 1696
    "amdsched",  // Index 1697
    "ctt-broker",  // Index 1698
    "xmapi",  // Index 1699
    "xaapi",  // Index 1700
    "rtmp",  // Index 1701
    "macromedia-fcs",  // Index 1702
    "jetcmeserver",  // Index 1703
    "jwserver",  // Index 1704
    "jwclient",  // Index 1705
    "jvserver",  // Index 1706
    "jvclient",  // Index 1707
    "dic-aida",  // Index 1708
    "res",  // Index 1709
    "beeyond-media",  // Index 1710
    "close-combat",  // Index 1711
    "dialogic-elmd",  // Index 1712
    "tekpls",  // Index 1713
    "sentinelsrm",  // Index 1714
    "eye2eye",  // Index 1715
    "ismaeasdaqlive",  // Index 1716
    "ismaeasdaqtest",  // Index 1717
    "bcs-lmserver",  // Index 1718
    "mpnjsc",  // Index 1719
    "rapidbase",  // Index 1720
    "abr-api",  // Index 1721
    "abr-secure",  // Index 1722
    "vrtl-vmf-ds",  // Index 1723
    "unix-status",  // Index 1724
    "dxadmind",  // Index 1725
    "simp-all",  // Index 1726
    "nasmanager",  // Index 1727
    "bts-appserver",  // Index 1728
    "biap-mp",  // Index 1729
    "webmachine",  // Index 1730
    "solid-e-engine",  // Index 1731
    "tivoli-npm",  // Index 1732
    "slush",  // Index 1733
    "sns-quote",  // Index 1734
    "lipsinc",  // Index 1735
    "lipsinc1",  // Index 1736
    "netop-rc",  // Index 1737
    "netop-school",  // Index 1738
    "intersys-cache",  // Index 1739
    "dlsrap",  // Index 1740
    "drp",  // Index 1741
    "tcoflashagent",  // Index 1742
    "tcoregagent",  // Index 1743
    "tcoaddressbook",  // Index 1744
    "unisql",  // Index 1745
    "unisql-java",  // Index 1746
    "pearldoc-xact",  // Index 1747
    "p2pq",  // Index 1748
    "estamp",  // Index 1749
    "lhtp",  // Index 1750
    "bigbrother",  // Index 1751
    "bb",  // Index 1752
    "hsrp",  // Index 1753
    "licensedaemon",  // Index 1754
    "tr-rsrb-p1",  // Index 1755
    "tr-rsrb-p2",  // Index 1756
    "tr-rsrb-p3",  // Index 1757
    "stun-p1",  // Index 1758
    "stun-p2",  // Index 1759
    "stun-p3",  // Index 1760
    "snmp-tcp-port",  // Index 1761
    "stun-port",  // Index 1762
    "perf-port",  // Index 1763
    "tr-rsrb-port",  // Index 1764
    "gdp-port",  // Index 1765
    "x25-svc-port",  // Index 1766
    "tcp-id-port",  // Index 1767
    "cisco-sccp",  // Index 1768
    "dc",  // Index 1769
    "wizard",  // Index 1770
    "globe",  // Index 1771
    "brutus",  // Index 1772
    "mailbox",  // Index 1773
    "emce",  // Index 1774
    "deslogin",  // Index 1775
    "invokator",  // Index 1776
    "raid-cc",  // Index 1777
    "dectalk",  // Index 1778
    "raid-am",  // Index 1779
    "conf",  // Index 1780
    "terminaldb",  // Index 1781
    "whosockami",  // Index 1782
    "search",  // Index 1783
    "pipe_server",  // Index 1784
    "servserv",  // Index 1785
    "ttyinfo",  // Index 1786
    "raid-ac",  // Index 1787
    "raid-cd",  // Index 1788
    "troff",  // Index 1789
    "raid-sf",  // Index 1790
    "cypress",  // Index 1791
    "raid-cs",  // Index 1792
    "bootserver",  // Index 1793
    "cypress-stat",  // Index 1794
    "bootclient",  // Index 1795
    "rellpack",  // Index 1796
    "about",  // Index 1797
    "xinupageserver",  // Index 1798
    "servexec",  // Index 1799
    "xinuexpansion1",  // Index 1800
    "down",  // Index 1801
    "xinuexpansion2",  // Index 1802
    "xinuexpansion3",  // Index 1803
    "xinuexpansion4",  // Index 1804
    "ellpack",  // Index 1805
    "xribs",  // Index 1806
    "scrabble",  // Index 1807
    "shadowserver",  // Index 1808
    "submitserver",  // Index 1809
    "hsrpv6",  // Index 1810
    "device2",  // Index 1811
    "mobrien-chat",  // Index 1812
    "blackboard",  // Index 1813
    "glogger",  // Index 1814
    "scoremgr",  // Index 1815
    "imsldoc",  // Index 1816
    "e-dpnet",  // Index 1817
    "applus",  // Index 1818
    "objectmanager",  // Index 1819
    "prizma",  // Index 1820
    "lam",  // Index 1821
    "interbase",  // Index 1822
    "isis",  // Index 1823
    "isis-bcast",  // Index 1824
    "rimsl",  // Index 1825
    "cdfunc",  // Index 1826
    "sdfunc",  // Index 1827
    "dls-monitor",  // Index 1828
    "nfs",  // Index 1829
    "av-emb-config",  // Index 1830
    "epnsdp",  // Index 1831
    "clearvisn",  // Index 1832
    "knetd",  // Index 1833
    "lot105-ds-upd",  // Index 1834
    "weblogin",  // Index 1835
    "iop",  // Index 1836
    "omnisky",  // Index 1837
    "rich-cp",  // Index 1838
    "newwavesearch",  // Index 1839
    "bmc-messaging",  // Index 1840
    "teleniumdaemon",  // Index 1841
    "netmount",  // Index 1842
    "icg-swp",  // Index 1843
    "icg-bridge",  // Index 1844
    "dnet-keyproxy",  // Index 1845
    "icg-iprelay",  // Index 1846
    "dlsrpn",  // Index 1847
    "aura",  // Index 1848
    "dlswpn",  // Index 1849
    "avocentkvm",  // Index 1850
    "avauthsrvprtcl",  // Index 1851
    "event-port",  // Index 1852
    "ah-esp-encap",  // Index 1853
    "acp-port",  // Index 1854
    "msync",  // Index 1855
    "gxs-data-port",  // Index 1856
    "vrtl-vmf-sa",  // Index 1857
    "newlixengine",  // Index 1858
    "newlixconfig",  // Index 1859
    "tsrmagt",  // Index 1860
    "tpcsrvr",  // Index 1861
    "idware-router",  // Index 1862
    "autodesk-nlm",  // Index 1863
    "kme-trap-port",  // Index 1864
    "infowave",  // Index 1865
    "radsec",  // Index 1866
    "sunclustergeo",  // Index 1867
    "ada-cip",  // Index 1868
    "gnunet",  // Index 1869
    "eli",  // Index 1870
    "ip-blf",  // Index 1871
    "sep",  // Index 1872
    "lrp",  // Index 1873
    "prp",  // Index 1874
    "descent3",  // Index 1875
    "nbx-cc",  // Index 1876
    "nbx-au",  // Index 1877
    "nbx-ser",  // Index 1878
    "nbx-dir",  // Index 1879
    "jetformpreview",  // Index 1880
    "dialog-port",  // Index 1881
    "h2250-annex-g",  // Index 1882
    "amiganetfs",  // Index 1883
    "rtcm-sc104",  // Index 1884
    "zephyr-srv",  // Index 1885
    "zephyr-clt",  // Index 1886
    "zephyr-hm",  // Index 1887
    "eklogin",  // Index 1888
    "msmq-mgmt",  // Index 1889
    "bintec-admin",  // Index 1890
    "rkinit",  // Index 1891
    "ergolight",  // Index 1892
    "umsp",  // Index 1893
    "kx",  // Index 1894
    "dsatp",  // Index 1895
    "kip",  // Index 1896
    "idonix-metanet",  // Index 1897
    "hsl-storm",  // Index 1898
    "newheights",  // Index 1899
    "ccowcmr",  // Index 1900
    "mentaclient",  // Index 1901
    "mentaserver",  // Index 1902
    "gsigatekeeper",  // Index 1903
    "kauth",  // Index 1904
    "qencp",  // Index 1905
    "ccproxy-ftp",  // Index 1906
    "scientia-ssdb",  // Index 1907
    "caupc-remote",  // Index 1908
    "gtp-control",  // Index 1909
    "elatelink",  // Index 1910
    "lockstep",  // Index 1911
    "pktcable-cops",  // Index 1912
    "index-pc-wb",  // Index 1913
    "net-steward",  // Index 1914
    "cs-live",  // Index 1915
    "xds",  // Index 1916
    "avantageb2b",  // Index 1917
    "solera-epmap",  // Index 1918
    "zymed-zpp",  // Index 1919
    "avenue",  // Index 1920
    "gris",  // Index 1921
    "appworxsrv",  // Index 1922
    "connect",  // Index 1923
    "unbind-cluster",  // Index 1924
    "ias-auth",  // Index 1925
    "ias-reg",  // Index 1926
    "ias-admind",  // Index 1927
    "tdmoip",  // Index 1928
    "lv-jc",  // Index 1929
    "lv-ffx",  // Index 1930
    "lv-pici",  // Index 1931
    "lv-not",  // Index 1932
    "lv-auth",  // Index 1933
    "veritas-ucl",  // Index 1934
    "acptsys",  // Index 1935
    "dynamic3d",  // Index 1936
    "docent",  // Index 1937
    "gtp-user",  // Index 1938
    "ctlptc",  // Index 1939
    "stdptc",  // Index 1940
    "brdptc",  // Index 1941
    "trp",  // Index 1942
    "xnds",  // Index 1943
    "touchnetplus",  // Index 1944
    "gdbremote",  // Index 1945
    "apc-2160",  // Index 1946
    "apc-agent",  // Index 1947
    "apc-2161",  // Index 1948
    "navisphere",  // Index 1949
    "navisphere-sec",  // Index 1950
    "ddns-v3",  // Index 1951
    "x-bone-api",  // Index 1952
    "iwserver",  // Index 1953
    "raw-serial",  // Index 1954
    "easy-soft-mux",  // Index 1955
    "brain",  // Index 1956
    "eyetv",  // Index 1957
    "msfw-storage",  // Index 1958
    "msfw-s-storage",  // Index 1959
    "msfw-replica",  // Index 1960
    "msfw-array",  // Index 1961
    "airsync",  // Index 1962
    "rapi",  // Index 1963
    "qwave",  // Index 1964
    "bitspeer",  // Index 1965
    "vmrdp",  // Index 1966
    "mc-gt-srv",  // Index 1967
    "eforward",  // Index 1968
    "cgn-stat",  // Index 1969
    "cgn-config",  // Index 1970
    "nvd",  // Index 1971
    "onbase-dds",  // Index 1972
    "gtaua",  // Index 1973
    "ssmc",  // Index 1974
    "ssmd",  // Index 1975
    "radware-rpm",  // Index 1976
    "radware-rpm-s",  // Index 1977
    "tivoconnect",  // Index 1978
    "tvbus",  // Index 1979
    "asdis",  // Index 1980
    "drwcs",  // Index 1981
    "mnp-exchange",  // Index 1982
    "onehome-remote",  // Index 1983
    "onehome-help",  // Index 1984
    "ici",  // Index 1985
    "ats",  // Index 1986
    "imtc-map",  // Index 1987
    "b2-runtime",  // Index 1988
    "b2-license",  // Index 1989
    "jps",  // Index 1990
    "hpocbus",  // Index 1991
    "hpssd",  // Index 1992
    "hpiod",  // Index 1993
    "rimf-ps",  // Index 1994
    "noaaport",  // Index 1995
    "emwin",  // Index 1996
    "leecoposserver",  // Index 1997
    "kali",  // Index 1998
    "rpi",  // Index 1999
    "ipcore",  // Index 2000
    "vtu-comms",  // Index 2001
    "gotodevice",  // Index 2002
    "bounzza",  // Index 2003
    "netiq-ncap",  // Index 2004
    "netiq",  // Index 2005
    "rockwell-csp1",  // Index 2006
    "EtherNetIP-1",  // Index 2007
    "msantipiracy",  // Index 2008
    "rockwell-csp2",  // Index 2009
    "efi-mg",  // Index 2010
    "rcip-itu",  // Index 2011
    "di-drm",  // Index 2012
    "di-msg",  // Index 2013
    "ehome-ms",  // Index 2014
    "datalens",  // Index 2015
    "queueadm",  // Index 2016
    "wimaxasncp",  // Index 2017
    "ivs-video",  // Index 2018
    "infocrypt",  // Index 2019
    "directplay",  // Index 2020
    "sercomm-wlink",  // Index 2021
    "nani",  // Index 2022
    "optech-port1-lm",  // Index 2023
    "aviva-sna",  // Index 2024
    "imagequery",  // Index 2025
    "recipe",  // Index 2026
    "ivsd",  // Index 2027
    "foliocorp",  // Index 2028
    "magicom",  // Index 2029
    "nmsserver",  // Index 2030
    "hao",  // Index 2031
    "pc-mta-addrmap",  // Index 2032
    "antidotemgrsvr",  // Index 2033
    "ums",  // Index 2034
    "rfmp",  // Index 2035
    "remote-collab",  // Index 2036
    "dif-port",  // Index 2037
    "njenet-ssl",  // Index 2038
    "dtv-chan-req",  // Index 2039
    "seispoc",  // Index 2040
    "vrtp",  // Index 2041
    "pcc-mfp",  // Index 2042
    "simple-tx-rx",  // Index 2043
    "rcts",  // Index 2044
    "acd-pm",  // Index 2045
    "apc-2260",  // Index 2046
    "comotionmaster",  // Index 2047
    "comotionback",  // Index 2048
    "ecwcfg",  // Index 2049
    "apx500api-1",  // Index 2050
    "apx500api-2",  // Index 2051
    "mfserver",  // Index 2052
    "ontobroker",  // Index 2053
    "amt",  // Index 2054
    "mikey",  // Index 2055
    "starschool",  // Index 2056
    "mmcals",  // Index 2057
    "mmcal",  // Index 2058
    "mysql-im",  // Index 2059
    "pcttunnell",  // Index 2060
    "ibridge-data",  // Index 2061
    "ibridge-mgmt",  // Index 2062
    "bluectrlproxy",  // Index 2063
    "s3db",  // Index 2064
    "xmquery",  // Index 2065
    "lnvpoller",  // Index 2066
    "lnvconsole",  // Index 2067
    "lnvalarm",  // Index 2068
    "lnvstatus",  // Index 2069
    "lnvmaps",  // Index 2070
    "lnvmailmon",  // Index 2071
    "nas-metering",  // Index 2072
    "dna",  // Index 2073
    "netml",  // Index 2074
    "dict-lookup",  // Index 2075
    "sonus-logging",  // Index 2076
    "eapsp",  // Index 2077
    "mib-streaming",  // Index 2078
    "npdbgmngr",  // Index 2079
    "konshus-lm",  // Index 2080
    "advant-lm",  // Index 2081
    "theta-lm",  // Index 2082
    "d2k-datamover1",  // Index 2083
    "d2k-datamover2",  // Index 2084
    "pc-telecommute",  // Index 2085
    "cvmmon",  // Index 2086
    "compaqdiag",  // Index 2087
    "cpq-wbem",  // Index 2088
    "binderysupport",  // Index 2089
    "proxy-gateway",  // Index 2090
    "attachmate-uts",  // Index 2091
    "mt-scaleserver",  // Index 2092
    "tappi-boxnet",  // Index 2093
    "pehelp",  // Index 2094
    "sdhelp",  // Index 2095
    "sdserver",  // Index 2096
    "sdclient",  // Index 2097
    "messageservice",  // Index 2098
    "wanscaler",  // Index 2099
    "iapp",  // Index 2100
    "cr-websystems",  // Index 2101
    "precise-sft",  // Index 2102
    "sent-lm",  // Index 2103
    "attachmate-g32",  // Index 2104
    "cadencecontrol",  // Index 2105
    "infolibria",  // Index 2106
    "siebel-ns",  // Index 2107
    "rdlap",  // Index 2108
    "ofsd",  // Index 2109
    "3d-nfsd",  // Index 2110
    "cosmocall",  // Index 2111
    "ansysli",  // Index 2112
    "idcp",  // Index 2113
    "xingcsm",  // Index 2114
    "netrix-sftm",  // Index 2115
    "tscchat",  // Index 2116
    "agentview",  // Index 2117
    "rcc-host",  // Index 2118
    "snapp",  // Index 2119
    "ace-client",  // Index 2120
    "ace-proxy",  // Index 2121
    "appleugcontrol",  // Index 2122
    "ideesrv",  // Index 2123
    "norton-lambert",  // Index 2124
    "3com-webview",  // Index 2125
    "wrs_registry",  // Index 2126
    "xiostatus",  // Index 2127
    "manage-exec",  // Index 2128
    "nati-logos",  // Index 2129
    "fcmsys",  // Index 2130
    "dbm",  // Index 2131
    "redstorm_join",  // Index 2132
    "redstorm_find",  // Index 2133
    "redstorm_info",  // Index 2134
    "redstorm_diag",  // Index 2135
    "psbserver",  // Index 2136
    "psrserver",  // Index 2137
    "pslserver",  // Index 2138
    "pspserver",  // Index 2139
    "psprserver",  // Index 2140
    "psdbserver",  // Index 2141
    "gxtelmd",  // Index 2142
    "unihub-server",  // Index 2143
    "futrix",  // Index 2144
    "flukeserver",  // Index 2145
    "nexstorindltd",  // Index 2146
    "tl1",  // Index 2147
    "digiman",  // Index 2148
    "mediacntrlnfsd",  // Index 2149
    "oi-2000",  // Index 2150
    "dbref",  // Index 2151
    "qip-login",  // Index 2152
    "service-ctrl",  // Index 2153
    "opentable",  // Index 2154
    "l3-hbmon",  // Index 2155
    "worldwire",  // Index 2156
    "lanmessenger",  // Index 2157
    "remographlm",  // Index 2158
    "hydra",  // Index 2159
    "docker",  // Index 2160
    "swarm",  // Index 2161
    "dali",  // Index 2162
    "etcd-client",  // Index 2163
    "etcd-server",  // Index 2164
    "compaq-https",  // Index 2165
    "ms-olap3",  // Index 2166
    "ms-olap4",  // Index 2167
    "sd-request",  // Index 2168
    "sd-capacity",  // Index 2169
    "sd-data",  // Index 2170
    "virtualtape",  // Index 2171
    "vsamredirector",  // Index 2172
    "mynahautostart",  // Index 2173
    "ovsessionmgr",  // Index 2174
    "rsmtp",  // Index 2175
    "3com-net-mgmt",  // Index 2176
    "tacticalauth",  // Index 2177
    "ms-olap1",  // Index 2178
    "ms-olap2",  // Index 2179
    "lan900_remote",  // Index 2180
    "wusage",  // Index 2181
    "ncl",  // Index 2182
    "orbiter",  // Index 2183
    "fmpro-fdal",  // Index 2184
    "opequus-server",  // Index 2185
    "cvspserver",  // Index 2186
    "taskmaster2000",  // Index 2187
    "iec-104",  // Index 2188
    "trc-netpoll",  // Index 2189
    "jediserver",  // Index 2190
    "orion",  // Index 2191
    "optimanet",  // Index 2192
    "sns-protocol",  // Index 2193
    "vrts-registry",  // Index 2194
    "netwave-ap-mgmt",  // Index 2195
    "cdn",  // Index 2196
    "orion-rmi-reg",  // Index 2197
    "beeyond",  // Index 2198
    "codima-rtp",  // Index 2199
    "rmtserver",  // Index 2200
    "composit-server",  // Index 2201
    "cas",  // Index 2202
    "attachmate-s2s",  // Index 2203
    "dslremote-mgmt",  // Index 2204
    "g-talk",  // Index 2205
    "crmsbits",  // Index 2206
    "rnrp",  // Index 2207
    "kofax-svr",  // Index 2208
    "fjitsuappmgr",  // Index 2209
    "vcmp",  // Index 2210
    "mgcp-gateway",  // Index 2211
    "ott",  // Index 2212
    "ft-role",  // Index 2213
    "venus",  // Index 2214
    "venus-se",  // Index 2215
    "codasrv",  // Index 2216
    "codasrv-se",  // Index 2217
    "pxc-epmap",  // Index 2218
    "optilogic",  // Index 2219
    "topx",  // Index 2220
    "unicontrol",  // Index 2221
    "sybasedbsynch",  // Index 2222
    "spearway",  // Index 2223
    "pvsw-inet",  // Index 2224
    "netangel",  // Index 2225
    "powerclientcsf",  // Index 2226
    "btpp2sectrans",  // Index 2227
    "dtn1",  // Index 2228
    "bues_service",  // Index 2229
    "ovwdb",  // Index 2230
    "hpppssvr",  // Index 2231
    "ratl",  // Index 2232
    "netadmin",  // Index 2233
    "netchat",  // Index 2234
    "snifferclient",  // Index 2235
    "madge-ltd",  // Index 2236
    "indx-dds",  // Index 2237
    "wago-io-system",  // Index 2238
    "altav-remmgt",  // Index 2239
    "rapido-ip",  // Index 2240
    "griffin",  // Index 2241
    "community",  // Index 2242
    "ms-theater",  // Index 2243
    "qadmifoper",  // Index 2244
    "qadmifevent",  // Index 2245
    "lsi-raid-mgmt",  // Index 2246
    "direcpc-si",  // Index 2247
    "lbm",  // Index 2248
    "lbf",  // Index 2249
    "high-criteria",  // Index 2250
    "qip-msgd",  // Index 2251
    "mti-tcs-comm",  // Index 2252
    "taskman-port",  // Index 2253
    "seaodbc",  // Index 2254
    "c3",  // Index 2255
    "aker-cdp",  // Index 2256
    "vitalanalysis",  // Index 2257
    "ace-server",  // Index 2258
    "ace-svr-prop",  // Index 2259
    "ssm-cvs",  // Index 2260
    "ssm-cssps",  // Index 2261
    "ssm-els",  // Index 2262
    "powerexchange",  // Index 2263
    "giop",  // Index 2264
    "giop-ssl",  // Index 2265
    "ttc",  // Index 2266
    "ttc-ssl",  // Index 2267
    "netobjects1",  // Index 2268
    "netobjects2",  // Index 2269
    "pns",  // Index 2270
    "moy-corp",  // Index 2271
    "tsilb",  // Index 2272
    "qip-qdhcp",  // Index 2273
    "conclave-cpp",  // Index 2274
    "groove",  // Index 2275
    "talarian-mqs",  // Index 2276
    "bmc-ar",  // Index 2277
    "fast-rem-serv",  // Index 2278
    "dirgis",  // Index 2279
    "quaddb",  // Index 2280
    "odn-castraq",  // Index 2281
    "rtsserv",  // Index 2282
    "rtsclient",  // Index 2283
    "kentrox-prot",  // Index 2284
    "nms-dpnss",  // Index 2285
    "wlbs",  // Index 2286
    "ppcontrol",  // Index 2287
    "jbroker",  // Index 2288
    "spock",  // Index 2289
    "jdatastore",  // Index 2290
    "fjmpss",  // Index 2291
    "fjappmgrbulk",  // Index 2292
    "metastorm",  // Index 2293
    "citrixima",  // Index 2294
    "citrixadmin",  // Index 2295
    "facsys-ntp",  // Index 2296
    "facsys-router",  // Index 2297
    "maincontrol",  // Index 2298
    "call-sig-trans",  // Index 2299
    "willy",  // Index 2300
    "globmsgsvc",  // Index 2301
    "pvsw",  // Index 2302
    "adaptecmgr",  // Index 2303
    "windb",  // Index 2304
    "qke-llc-v3",  // Index 2305
    "optiwave-lm",  // Index 2306
    "ms-v-worlds",  // Index 2307
    "ema-sent-lm",  // Index 2308
    "iqserver",  // Index 2309
    "ncr_ccl",  // Index 2310
    "utsftp",  // Index 2311
    "vrcommerce",  // Index 2312
    "ito-e-gui",  // Index 2313
    "ovtopmd",  // Index 2314
    "snifferserver",  // Index 2315
    "combox-web-acc",  // Index 2316
    "madcap",  // Index 2317
    "btpp2audctr1",  // Index 2318
    "upgrade",  // Index 2319
    "vnwk-prapi",  // Index 2320
    "vsiadmin",  // Index 2321
    "lonworks",  // Index 2322
    "lonworks2",  // Index 2323
    "udrawgraph",  // Index 2324
    "reftek",  // Index 2325
    "novell-zen",  // Index 2326
    "sis-emt",  // Index 2327
    "vytalvaultbrtp",  // Index 2328
    "vytalvaultvsmp",  // Index 2329
    "vytalvaultpipe",  // Index 2330
    "ipass",  // Index 2331
    "ads",  // Index 2332
    "isg-uda-server",  // Index 2333
    "call-logging",  // Index 2334
    "efidiningport",  // Index 2335
    "vcnet-link-v10",  // Index 2336
    "compaq-wcp",  // Index 2337
    "nicetec-nmsvc",  // Index 2338
    "nicetec-mgmt",  // Index 2339
    "pclemultimedia",  // Index 2340
    "lstp",  // Index 2341
    "labrat",  // Index 2342
    "mosaixcc",  // Index 2343
    "delibo",  // Index 2344
    "cti-redwood",  // Index 2345
    "hp-3000-telnet",  // Index 2346
    "coord-svr",  // Index 2347
    "pcs-pcw",  // Index 2348
    "clp",  // Index 2349
    "spamtrap",  // Index 2350
    "sonuscallsig",  // Index 2351
    "hs-port",  // Index 2352
    "cecsvc",  // Index 2353
    "ibp",  // Index 2354
    "trustestablish",  // Index 2355
    "blockade-bpsp",  // Index 2356
    "hl7",  // Index 2357
    "tclprodebugger",  // Index 2358
    "scipticslsrvr",  // Index 2359
    "rvs-isdn-dcp",  // Index 2360
    "mpfoncl",  // Index 2361
    "tributary",  // Index 2362
    "argis-te",  // Index 2363
    "argis-ds",  // Index 2364
    "mon",  // Index 2365
    "cyaserv",  // Index 2366
    "netx-server",  // Index 2367
    "netx-agent",  // Index 2368
    "masc",  // Index 2369
    "privilege",  // Index 2370
    "quartus-tcl",  // Index 2371
    "idotdist",  // Index 2372
    "maytagshuffle",  // Index 2373
    "netrek",  // Index 2374
    "mns-mail",  // Index 2375
    "dts",  // Index 2376
    "worldfusion1",  // Index 2377
    "worldfusion2",  // Index 2378
    "homesteadglory",  // Index 2379
    "citriximaclient",  // Index 2380
    "snapd",  // Index 2381
    "zebrasrv",  // Index 2382
    "hpstgmgr",  // Index 2383
    "zebra",  // Index 2384
    "discp-client",  // Index 2385
    "ripd",  // Index 2386
    "discp-server",  // Index 2387
    "ripngd",  // Index 2388
    "servicemeter",  // Index 2389
    "ospfd",  // Index 2390
    "nsc-ccs",  // Index 2391
    "bgpd",  // Index 2392
    "nsc-posa",  // Index 2393
    "netmon",  // Index 2394
    "connection",  // Index 2395
    "wag-service",  // Index 2396
    "system-monitor",  // Index 2397
    "versa-tek",  // Index 2398
    "lionhead",  // Index 2399
    "qpasa-agent",  // Index 2400
    "smntubootstrap",  // Index 2401
    "neveroffline",  // Index 2402
    "firepower",  // Index 2403
    "appswitch-emp",  // Index 2404
    "cmadmin",  // Index 2405
    "priority-e-com",  // Index 2406
    "bruce",  // Index 2407
    "lpsrecommender",  // Index 2408
    "miles-apart",  // Index 2409
    "metricadbc",  // Index 2410
    "lmdp",  // Index 2411
    "aria",  // Index 2412
    "blwnkl-port",  // Index 2413
    "gbjd816",  // Index 2414
    "dict",  // Index 2415
    "sitaraserver",  // Index 2416
    "sitaramgmt",  // Index 2417
    "sitaradir",  // Index 2418
    "irdg-post",  // Index 2419
    "interintelli",  // Index 2420
    "pk-electronics",  // Index 2421
    "backburner",  // Index 2422
    "solve",  // Index 2423
    "imdocsvc",  // Index 2424
    "sybase",  // Index 2425
    "sybaseanywhere",  // Index 2426
    "aminet",  // Index 2427
    "sai_sentlm",  // Index 2428
    "hdl-srv",  // Index 2429
    "tragic",  // Index 2430
    "gte-samp",  // Index 2431
    "travsoft-ipx-t",  // Index 2432
    "novell-ipx-cmd",  // Index 2433
    "and-lm",  // Index 2434
    "syncserver",  // Index 2435
    "upsnotifyprot",  // Index 2436
    "vpsipport",  // Index 2437
    "eristwoguns",  // Index 2438
    "ebinsite",  // Index 2439
    "interpathpanel",  // Index 2440
    "sonus",  // Index 2441
    "corel_vncadmin",  // Index 2442
    "unglue",  // Index 2443
    "kana",  // Index 2444
    "sns-dispatcher",  // Index 2445
    "sns-admin",  // Index 2446
    "sns-query",  // Index 2447
    "gcmonitor",  // Index 2448
    "olhost",  // Index 2449
    "bintec-capi",  // Index 2450
    "bintec-tapi",  // Index 2451
    "patrol-mq-gm",  // Index 2452
    "patrol-mq-nm",  // Index 2453
    "extensis",  // Index 2454
    "alarm-clock-s",  // Index 2455
    "alarm-clock-c",  // Index 2456
    "toad",  // Index 2457
    "tve-announce",  // Index 2458
    "newlixreg",  // Index 2459
    "nhserver",  // Index 2460
    "firstcall42",  // Index 2461
    "ewnn",  // Index 2462
    "ttc-etap",  // Index 2463
    "simslink",  // Index 2464
    "gadgetgate1way",  // Index 2465
    "gadgetgate2way",  // Index 2466
    "syncserverssl",  // Index 2467
    "pxc-sapxom",  // Index 2468
    "mpnjsomb",  // Index 2469
    "ncdloadbalance",  // Index 2470
    "mpnjsosv",  // Index 2471
    "mpnjsocl",  // Index 2472
    "mpnjsomg",  // Index 2473
    "pq-lic-mgmt",  // Index 2474
    "md-cg-http",  // Index 2475
    "fastlynx",  // Index 2476
    "hp-nnm-data",  // Index 2477
    "itinternet",  // Index 2478
    "admins-lms",  // Index 2479
    "pwrsevent",  // Index 2480
    "vspread",  // Index 2481
    "unifyadmin",  // Index 2482
    "oce-snmp-trap",  // Index 2483
    "mck-ivpip",  // Index 2484
    "csoft-plusclnt",  // Index 2485
    "tqdata",  // Index 2486
    "sms-rcinfo",  // Index 2487
    "sms-xfer",  // Index 2488
    "sms-chat",  // Index 2489
    "sms-remctrl",  // Index 2490
    "sds-admin",  // Index 2491
    "ncdmirroring",  // Index 2492
    "emcsymapiport",  // Index 2493
    "banyan-net",  // Index 2494
    "supermon",  // Index 2495
    "sso-service",  // Index 2496
    "sso-control",  // Index 2497
    "aocp",  // Index 2498
    "raventbs",  // Index 2499
    "raventdm",  // Index 2500
    "hpstgmgr2",  // Index 2501
    "inova-ip-disco",  // Index 2502
    "pn-requester",  // Index 2503
    "pn-requester2",  // Index 2504
    "scan-change",  // Index 2505
    "wkars",  // Index 2506
    "smart-diagnose",  // Index 2507
    "proactivesrvr",  // Index 2508
    "watchdog-nt",  // Index 2509
    "qotps",  // Index 2510
    "msolap-ptp2",  // Index 2511
    "tams",  // Index 2512
    "mgcp-callagent",  // Index 2513
    "sqdr",  // Index 2514
    "tcim-control",  // Index 2515
    "nec-raidplus",  // Index 2516
    "fyre-messanger",  // Index 2517
    "g5m",  // Index 2518
    "signet-ctf",  // Index 2519
    "ccs-software",  // Index 2520
    "netiq-mc",  // Index 2521
    "radwiz-nms-srv",  // Index 2522
    "srp-feedback",  // Index 2523
    "ndl-tcp-ois-gw",  // Index 2524
    "tn-timing",  // Index 2525
    "alarm",  // Index 2526
    "tsb",  // Index 2527
    "tsb2",  // Index 2528
    "murx",  // Index 2529
    "honyaku",  // Index 2530
    "urbisnet",  // Index 2531
    "cpudpencap",  // Index 2532
    "fjippol-swrly",  // Index 2533
    "fjippol-polsvr",  // Index 2534
    "fjippol-cnsl",  // Index 2535
    "fjippol-port1",  // Index 2536
    "fjippol-port2",  // Index 2537
    "rsisysaccess",  // Index 2538
    "de-spot",  // Index 2539
    "apollo-cc",  // Index 2540
    "expresspay",  // Index 2541
    "simplement-tie",  // Index 2542
    "cnrp",  // Index 2543
    "apollo-status",  // Index 2544
    "apollo-gms",  // Index 2545
    "sabams",  // Index 2546
    "dicom-iscl",  // Index 2547
    "dicom-tls",  // Index 2548
    "desktop-dna",  // Index 2549
    "data-insurance",  // Index 2550
    "qip-audup",  // Index 2551
    "listen",  // Index 2552
    "compaq-scp",  // Index 2553
    "uadtc",  // Index 2554
    "uacs",  // Index 2555
    "exce",  // Index 2556
    "veronica",  // Index 2557
    "vergencecm",  // Index 2558
    "auris",  // Index 2559
    "rbakcup1",  // Index 2560
    "rbakcup2",  // Index 2561
    "smpp",  // Index 2562
    "ridgeway1",  // Index 2563
    "ridgeway2",  // Index 2564
    "gwen-sonya",  // Index 2565
    "lbc-sync",  // Index 2566
    "lbc-control",  // Index 2567
    "whosells",  // Index 2568
    "everydayrc",  // Index 2569
    "aises",  // Index 2570
    "www-dev",  // Index 2571
    "aic-np",  // Index 2572
    "aic-oncrpc",  // Index 2573
    "piccolo",  // Index 2574
    "fryeserv",  // Index 2575
    "media-agent",  // Index 2576
    "plgproxy",  // Index 2577
    "mtport-regist",  // Index 2578
    "f5-globalsite",  // Index 2579
    "initlsmsad",  // Index 2580
    "livestats",  // Index 2581
    "ac-tech",  // Index 2582
    "esp-encap",  // Index 2583
    "tmesis-upshot",  // Index 2584
    "icon-discover",  // Index 2585
    "acc-raid",  // Index 2586
    "igcp",  // Index 2587
    "veritas-tcp1",  // Index 2588
    "veritas-udp1",  // Index 2589
    "btprjctrl",  // Index 2590
    "dvr-esm",  // Index 2591
    "wta-wsp-s",  // Index 2592
    "cspuni",  // Index 2593
    "cspmulti",  // Index 2594
    "j-lan-p",  // Index 2595
    "corbaloc",  // Index 2596
    "netsteward",  // Index 2597
    "gsiftp",  // Index 2598
    "atmtcp",  // Index 2599
    "llm-pass",  // Index 2600
    "llm-csv",  // Index 2601
    "lbc-measure",  // Index 2602
    "lbc-watchdog",  // Index 2603
    "nmsigport",  // Index 2604
    "rmlnk",  // Index 2605
    "fc-faultnotify",  // Index 2606
    "univision",  // Index 2607
    "vrts-at-port",  // Index 2608
    "ka0wuc",  // Index 2609
    "cqg-netlan",  // Index 2610
    "cqg-netlan-1",  // Index 2611
    "slc-systemlog",  // Index 2612
    "slc-ctrlrloops",  // Index 2613
    "itm-lm",  // Index 2614
    "silkp1",  // Index 2615
    "silkp2",  // Index 2616
    "silkp3",  // Index 2617
    "silkp4",  // Index 2618
    "glishd",  // Index 2619
    "evtp",  // Index 2620
    "evtp-data",  // Index 2621
    "catalyst",  // Index 2622
    "repliweb",  // Index 2623
    "starbot",  // Index 2624
    "l3-exprt",  // Index 2625
    "l3-ranger",  // Index 2626
    "l3-hawk",  // Index 2627
    "pdnet",  // Index 2628
    "bpcp-poll",  // Index 2629
    "bpcp-trap",  // Index 2630
    "aimpp-hello",  // Index 2631
    "aimpp-port-req",  // Index 2632
    "amt-blc-port",  // Index 2633
    "metaconsole",  // Index 2634
    "webemshttp",  // Index 2635
    "bears-01",  // Index 2636
    "ispipes",  // Index 2637
    "infomover",  // Index 2638
    "msrp",  // Index 2639
    "cesdinv",  // Index 2640
    "simctlp",  // Index 2641
    "ecnp",  // Index 2642
    "activememory",  // Index 2643
    "dialpad-voice1",  // Index 2644
    "dialpad-voice2",  // Index 2645
    "ttg-protocol",  // Index 2646
    "sonardata",  // Index 2647
    "astromed-main",  // Index 2648
    "pit-vpn",  // Index 2649
    "iwlistener",  // Index 2650
    "esps-portal",  // Index 2651
    "npep-messaging",  // Index 2652
    "icslap",  // Index 2653
    "daishi",  // Index 2654
    "msi-selectplay",  // Index 2655
    "radix",  // Index 2656
    "psrt",  // Index 2657
    "dxmessagebase1",  // Index 2658
    "dxmessagebase2",  // Index 2659
    "sps-tunnel",  // Index 2660
    "bluelance",  // Index 2661
    "aap",  // Index 2662
    "ucentric-ds",  // Index 2663
    "synapse",  // Index 2664
    "ndsp",  // Index 2665
    "ndtp",  // Index 2666
    "ndnp",  // Index 2667
    "flashmsg",  // Index 2668
    "topflow",  // Index 2669
    "responselogic",  // Index 2670
    "aironetddp",  // Index 2671
    "spcsdlobby",  // Index 2672
    "rsom",  // Index 2673
    "cspclmulti",  // Index 2674
    "cinegrfx-elmd",  // Index 2675
    "snifferdata",  // Index 2676
    "vseconnector",  // Index 2677
    "abacus-remote",  // Index 2678
    "natuslink",  // Index 2679
    "ecovisiong6-1",  // Index 2680
    "citrix-rtmp",  // Index 2681
    "appliance-cfg",  // Index 2682
    "powergemplus",  // Index 2683
    "quicksuite",  // Index 2684
    "allstorcns",  // Index 2685
    "netaspi",  // Index 2686
    "extensisportfolio",  // Index 2687
    "suitcase",  // Index 2688
    "m2ua",  // Index 2689
    "m3ua",  // Index 2690
    "caller9",  // Index 2691
    "webmethods-b2b",  // Index 2692
    "mao",  // Index 2693
    "funk-dialout",  // Index 2694
    "tdaccess",  // Index 2695
    "blockade",  // Index 2696
    "epicon",  // Index 2697
    "boosterware",  // Index 2698
    "gamelobby",  // Index 2699
    "tksocket",  // Index 2700
    "elvin_server",  // Index 2701
    "elvin_client",  // Index 2702
    "kastenchasepad",  // Index 2703
    "roboer",  // Index 2704
    "roboeda",  // Index 2705
    "cesdcdman",  // Index 2706
    "cesdcdtrn",  // Index 2707
    "wta-wsp-wtp-s",  // Index 2708
    "precise-vip",  // Index 2709
    "mobile-file-dl",  // Index 2710
    "unimobilectrl",  // Index 2711
    "redstone-cpss",  // Index 2712
    "amx-webadmin",  // Index 2713
    "amx-weblinx",  // Index 2714
    "circle-x",  // Index 2715
    "incp",  // Index 2716
    "4-tieropmgw",  // Index 2717
    "4-tieropmcli",  // Index 2718
    "qtp",  // Index 2719
    "otpatch",  // Index 2720
    "pnaconsult-lm",  // Index 2721
    "sm-pas-1",  // Index 2722
    "sm-pas-2",  // Index 2723
    "sm-pas-3",  // Index 2724
    "sm-pas-4",  // Index 2725
    "sm-pas-5",  // Index 2726
    "ttnrepository",  // Index 2727
    "megaco-h248",  // Index 2728
    "h248-binary",  // Index 2729
    "fjsvmpor",  // Index 2730
    "gpsd",  // Index 2731
    "wap-push",  // Index 2732
    "wap-pushsecure",  // Index 2733
    "esip",  // Index 2734
    "ottp",  // Index 2735
    "mpfwsas",  // Index 2736
    "ovalarmsrv",  // Index 2737
    "ovalarmsrv-cmd",  // Index 2738
    "csnotify",  // Index 2739
    "ovrimosdbman",  // Index 2740
    "jmact5",  // Index 2741
    "jmact6",  // Index 2742
    "rmopagt",  // Index 2743
    "dfoxserver",  // Index 2744
    "boldsoft-lm",  // Index 2745
    "iph-policy-cli",  // Index 2746
    "iph-policy-adm",  // Index 2747
    "bullant-srap",  // Index 2748
    "bullant-rap",  // Index 2749
    "idp-infotrieve",  // Index 2750
    "symantec-av",  // Index 2751
    "enpp",  // Index 2752
    "essp",  // Index 2753
    "index-net",  // Index 2754
    "netclip",  // Index 2755
    "pmsm-webrctl",  // Index 2756
    "svnetworks",  // Index 2757
    "signal",  // Index 2758
    "fjmpcm",  // Index 2759
    "cns-srv-port",  // Index 2760
    "ttc-etap-ns",  // Index 2761
    "ttc-etap-ds",  // Index 2762
    "h263-video",  // Index 2763
    "wimd",  // Index 2764
    "mylxamport",  // Index 2765
    "iwb-whiteboard",  // Index 2766
    "netplan",  // Index 2767
    "hpidsadmin",  // Index 2768
    "hpidsagent",  // Index 2769
    "stonefalls",  // Index 2770
    "identify",  // Index 2771
    "hippad",  // Index 2772
    "zarkov",  // Index 2773
    "boscap",  // Index 2774
    "wkstn-mon",  // Index 2775
    "avenyo",  // Index 2776
    "veritas-vis1",  // Index 2777
    "veritas-vis2",  // Index 2778
    "idrs",  // Index 2779
    "vsixml",  // Index 2780
    "rebol",  // Index 2781
    "iss-realsec",  // Index 2782
    "realsecure",  // Index 2783
    "remoteware-un",  // Index 2784
    "ppp",  // Index 2785
    "hbci",  // Index 2786
    "exlm-agent",  // Index 2787
    "cgms",  // Index 2788
    "csoftragent",  // Index 2789
    "geniuslm",  // Index 2790
    "deslogind",  // Index 2791
    "ii-admin",  // Index 2792
    "lotusmtap",  // Index 2793
    "midnight-tech",  // Index 2794
    "pxc-ntfy",  // Index 2795
    "gw",  // Index 2796
    "ping-pong",  // Index 2797
    "trusted-web",  // Index 2798
    "twsdss",  // Index 2799
    "gilatskysurfer",  // Index 2800
    "broker_service",  // Index 2801
    "nati-dstp",  // Index 2802
    "notify_srvr",  // Index 2803
    "event_listener",  // Index 2804
    "srvc_registry",  // Index 2805
    "resource_mgr",  // Index 2806
    "cifs",  // Index 2807
    "agriserver",  // Index 2808
    "csregagent",  // Index 2809
    "magicnotes",  // Index 2810
    "nds_sso",  // Index 2811
    "slnp",  // Index 2812
    "arepa-raft",  // Index 2813
    "agri-gateway",  // Index 2814
    "LiebDevMgmt_C",  // Index 2815
    "LiebDevMgmt_DM",  // Index 2816
    "LiebDevMgmt_A",  // Index 2817
    "arepa-cas",  // Index 2818
    "eppc",  // Index 2819
    "redwood-chat",  // Index 2820
    "pdb",  // Index 2821
    "osmosis-aeea",  // Index 2822
    "fjsv-gssagt",  // Index 2823
    "hagel-dump",  // Index 2824
    "hp-san-mgmt",  // Index 2825
    "santak-ups",  // Index 2826
    "cogitate",  // Index 2827
    "tomato-springs",  // Index 2828
    "di-traceware",  // Index 2829
    "journee",  // Index 2830
    "brp",  // Index 2831
    "responsenet",  // Index 2832
    "di-ase",  // Index 2833
    "hlserver",  // Index 2834
    "pctrader",  // Index 2835
    "cfs",  // Index 2836
    "gds_db",  // Index 2837
    "galaxy-server",  // Index 2838
    "powerchute",  // Index 2839
    "apc-3052",  // Index 2840
    "dsom-server",  // Index 2841
    "amt-cnf-prot",  // Index 2842
    "policyserver",  // Index 2843
    "cdl-server",  // Index 2844
    "goahead-fldup",  // Index 2845
    "videobeans",  // Index 2846
    "qsoft",  // Index 2847
    "interserver",  // Index 2848
    "cautcpd",  // Index 2849
    "ncacn-ip-tcp",  // Index 2850
    "ncadg-ip-udp",  // Index 2851
    "dnet-tstproxy",  // Index 2852
    "rprt",  // Index 2853
    "slinterbase",  // Index 2854
    "netattachsdmp",  // Index 2855
    "fjhpjp",  // Index 2856
    "ls3bcast",  // Index 2857
    "ls3",  // Index 2858
    "mgxswitch",  // Index 2859
    "csd-mgmt-port",  // Index 2860
    "csd-monitor",  // Index 2861
    "vcrp",  // Index 2862
    "xbox",  // Index 2863
    "orbix-locator",  // Index 2864
    "orbix-config",  // Index 2865
    "orbix-loc-ssl",  // Index 2866
    "orbix-cfg-ssl",  // Index 2867
    "lv-frontpanel",  // Index 2868
    "stm_pproc",  // Index 2869
    "tl1-lv",  // Index 2870
    "tl1-raw",  // Index 2871
    "tl1-telnet",  // Index 2872
    "itm-mccs",  // Index 2873
    "pcihreq",  // Index 2874
    "sj3",  // Index 2875
    "jdl-dbkitchen",  // Index 2876
    "asoki-sma",  // Index 2877
    "xdtp",  // Index 2878
    "ptk-alink",  // Index 2879
    "stss",  // Index 2880
    "1ci-smcs",  // Index 2881
    "rapidmq-center",  // Index 2882
    "rapidmq-reg",  // Index 2883
    "panasas",  // Index 2884
    "ndl-aps",  // Index 2885
    "itu-bicc-stc",  // Index 2886
    "umm-port",  // Index 2887
    "chmd",  // Index 2888
    "opcon-xps",  // Index 2889
    "hp-pxpib",  // Index 2890
    "sl-mon",  // Index 2891
    "autocuesmi",  // Index 2892
    "autocuelog",  // Index 2893
    "autocuetime",  // Index 2894
    "cardbox",  // Index 2895
    "cardbox-http",  // Index 2896
    "business",  // Index 2897
    "geolocate",  // Index 2898
    "personnel",  // Index 2899
    "sim-control",  // Index 2900
    "wsynch",  // Index 2901
    "ksysguard",  // Index 2902
    "cs-auth-svr",  // Index 2903
    "ccmad",  // Index 2904
    "mctet-master",  // Index 2905
    "mctet-gateway",  // Index 2906
    "mctet-jserv",  // Index 2907
    "pkagent",  // Index 2908
    "d2000kernel",  // Index 2909
    "d2000webserver",  // Index 2910
    "pcmk-remote",  // Index 2911
    "vtr-emulator",  // Index 2912
    "edix",  // Index 2913
    "beacon-port",  // Index 2914
    "a13-an",  // Index 2915
    "ctx-bridge",  // Index 2916
    "squid-http",  // Index 2917
    "ndl-aas",  // Index 2918
    "netport-id",  // Index 2919
    "icpv2",  // Index 2920
    "squid-ipc",  // Index 2921
    "netbookmark",  // Index 2922
    "ms-rule-engine",  // Index 2923
    "prism-deploy",  // Index 2924
    "ecp",  // Index 2925
    "peerbook-port",  // Index 2926
    "grubd",  // Index 2927
    "rtnt-1",  // Index 2928
    "rtnt-2",  // Index 2929
    "incognitorv",  // Index 2930
    "ariliamulti",  // Index 2931
    "vmodem",  // Index 2932
    "apt-cacher",  // Index 2933
    "rdc-wh-eos",  // Index 2934
    "seaview",  // Index 2935
    "tarantella",  // Index 2936
    "csi-lfap",  // Index 2937
    "bears-02",  // Index 2938
    "rfio",  // Index 2939
    "nm-game-admin",  // Index 2940
    "nm-game-server",  // Index 2941
    "nm-asses-admin",  // Index 2942
    "nm-assessor",  // Index 2943
    "feitianrockey",  // Index 2944
    "s8-client-port",  // Index 2945
    "ccmrmi",  // Index 2946
    "jpegmpeg",  // Index 2947
    "indura",  // Index 2948
    "e3consultants",  // Index 2949
    "stvp",  // Index 2950
    "navegaweb-port",  // Index 2951
    "tip-app-server",  // Index 2952
    "doc1lm",  // Index 2953
    "sflm",  // Index 2954
    "res-sap",  // Index 2955
    "imprs",  // Index 2956
    "newgenpay",  // Index 2957
    "sossecollector",  // Index 2958
    "nowcontact",  // Index 2959
    "poweronnud",  // Index 2960
    "serverview-as",  // Index 2961
    "serverview-asn",  // Index 2962
    "serverview-gf",  // Index 2963
    "serverview-rm",  // Index 2964
    "serverview-icc",  // Index 2965
    "armi-server",  // Index 2966
    "t1-e1-over-ip",  // Index 2967
    "ars-master",  // Index 2968
    "phonex-port",  // Index 2969
    "radclientport",  // Index 2970
    "h2gf-w-2m",  // Index 2971
    "mc-brk-srv",  // Index 2972
    "bmcpatrolagent",  // Index 2973
    "bmcpatrolrnvu",  // Index 2974
    "cops-tls",  // Index 2975
    "apogeex-port",  // Index 2976
    "smpppd",  // Index 2977
    "iiw-port",  // Index 2978
    "odi-port",  // Index 2979
    "brcm-comm-port",  // Index 2980
    "pcle-infex",  // Index 2981
    "csvr-proxy",  // Index 2982
    "csvr-sslproxy",  // Index 2983
    "firemonrcc",  // Index 2984
    "spandataport",  // Index 2985
    "magbind",  // Index 2986
    "ncu-1",  // Index 2987
    "ncu-2",  // Index 2988
    "embrace-dp-s",  // Index 2989
    "embrace-dp-c",  // Index 2990
    "dmod-workspace",  // Index 2991
    "tick-port",  // Index 2992
    "cpq-tasksmart",  // Index 2993
    "intraintra",  // Index 2994
    "netwatcher-mon",  // Index 2995
    "netwatcher-db",  // Index 2996
    "isns",  // Index 2997
    "ironmail",  // Index 2998
    "vx-auth-port",  // Index 2999
    "pfu-prcallback",  // Index 3000
    "netwkpathengine",  // Index 3001
    "flamenco-proxy",  // Index 3002
    "avsecuremgmt",  // Index 3003
    "surveyinst",  // Index 3004
    "neon24x7",  // Index 3005
    "jmq-daemon-1",  // Index 3006
    "jmq-daemon-2",  // Index 3007
    "ferrari-foam",  // Index 3008
    "unite",  // Index 3009
    "smartpackets",  // Index 3010
    "wms-messenger",  // Index 3011
    "xnm-ssl",  // Index 3012
    "xnm-clear-text",  // Index 3013
    "glbp",  // Index 3014
    "digivote",  // Index 3015
    "aes-discovery",  // Index 3016
    "fcip-port",  // Index 3017
    "isi-irp",  // Index 3018
    "dwnmshttp",  // Index 3019
    "dwmsgserver",  // Index 3020
    "global-cd-port",  // Index 3021
    "sftdst-port",  // Index 3022
    "vidigo",  // Index 3023
    "mdtp",  // Index 3024
    "whisker",  // Index 3025
    "alchemy",  // Index 3026
    "mdap-port",  // Index 3027
    "apparenet-ts",  // Index 3028
    "apparenet-tps",  // Index 3029
    "apparenet-as",  // Index 3030
    "apparenet-ui",  // Index 3031
    "triomotion",  // Index 3032
    "sysorb",  // Index 3033
    "sdp-id-port",  // Index 3034
    "timelot",  // Index 3035
    "onesaf",  // Index 3036
    "vieo-fe",  // Index 3037
    "dvt-system",  // Index 3038
    "kademlia",  // Index 3039
    "dvt-data",  // Index 3040
    "procos-lm",  // Index 3041
    "ssp",  // Index 3042
    "hicp",  // Index 3043
    "sysscanner",  // Index 3044
    "dhe",  // Index 3045
    "pda-data",  // Index 3046
    "pda-sys",  // Index 3047
    "semaphore",  // Index 3048
    "cpqrpm-agent",  // Index 3049
    "cpqrpm-server",  // Index 3050
    "ivecon-port",  // Index 3051
    "epncdp2",  // Index 3052
    "winshadow",  // Index 3053
    "necp",  // Index 3054
    "ecolor-imager",  // Index 3055
    "ccmail",  // Index 3056
    "altav-tunnel",  // Index 3057
    "ns-cfg-server",  // Index 3058
    "ibm-dial-out",  // Index 3059
    "globalcatLDAP",  // Index 3060
    "msft-gc",  // Index 3061
    "globalcatLDAPssl",  // Index 3062
    "msft-gc-ssl",  // Index 3063
    "verismart",  // Index 3064
    "csoft-prev",  // Index 3065
    "user-manager",  // Index 3066
    "sxmp",  // Index 3067
    "ordinox-server",  // Index 3068
    "samd",  // Index 3069
    "maxim-asics",  // Index 3070
    "awg-proxy",  // Index 3071
    "lkcmserver",  // Index 3072
    "admind",  // Index 3073
    "vs-server",  // Index 3074
    "sysopt",  // Index 3075
    "datusorb",  // Index 3076
    "netassistant",  // Index 3077
    "4talk",  // Index 3078
    "plato",  // Index 3079
    "e-net",  // Index 3080
    "directvdata",  // Index 3081
    "cops",  // Index 3082
    "enpc",  // Index 3083
    "caps-lm",  // Index 3084
    "sah-lm",  // Index 3085
    "meetingmaker",  // Index 3086
    "cart-o-rama",  // Index 3087
    "fg-fps",  // Index 3088
    "fg-gip",  // Index 3089
    "dyniplookup",  // Index 3090
    "rib-slm",  // Index 3091
    "cytel-lm",  // Index 3092
    "deskview",  // Index 3093
    "saprouter",  // Index 3094
    "pdrncs",  // Index 3095
    "ceph",  // Index 3096
    "tarantool",  // Index 3097
    "mcs-fastmail",  // Index 3098
    "opsession-clnt",  // Index 3099
    "opsession-srvr",  // Index 3100
    "odette-ftp",  // Index 3101
    "mysql",  // Index 3102
    "opsession-prxy",  // Index 3103
    "tns-server",  // Index 3104
    "tns-adv",  // Index 3105
    "dyna-access",  // Index 3106
    "mcns-tel-ret",  // Index 3107
    "appman-server",  // Index 3108
    "uorb",  // Index 3109
    "uohost",  // Index 3110
    "cdid",  // Index 3111
    "aicc-cmi",  // Index 3112
    "vsaiport",  // Index 3113
    "ssrip",  // Index 3114
    "sdt-lmd",  // Index 3115
    "officelink2000",  // Index 3116
    "vnsstr",  // Index 3117
    "active-net",  // Index 3118
    "sftu",  // Index 3119
    "bbars",  // Index 3120
    "egptlm",  // Index 3121
    "hp-device-disc",  // Index 3122
    "mcs-calypsoicf",  // Index 3123
    "mcs-messaging",  // Index 3124
    "mcs-mailsvr",  // Index 3125
    "dec-notes",  // Index 3126
    "directv-web",  // Index 3127
    "directv-soft",  // Index 3128
    "directv-tick",  // Index 3129
    "directv-catlg",  // Index 3130
    "anet-b",  // Index 3131
    "anet-l",  // Index 3132
    "anet-m",  // Index 3133
    "anet-h",  // Index 3134
    "webtie",  // Index 3135
    "ms-cluster-net",  // Index 3136
    "bnt-manager",  // Index 3137
    "influence",  // Index 3138
    "trnsprntproxy",  // Index 3139
    "phoenix-rpc",  // Index 3140
    "pangolin-laser",  // Index 3141
    "chevinservices",  // Index 3142
    "findviatv",  // Index 3143
    "btrieve",  // Index 3144
    "ssql",  // Index 3145
    "fatpipe",  // Index 3146
    "suitjd",  // Index 3147
    "ordinox-dbase",  // Index 3148
    "upnotifyps",  // Index 3149
    "adtech-test",  // Index 3150
    "mpsysrmsvr",  // Index 3151
    "wg-netforce",  // Index 3152
    "kv-server",  // Index 3153
    "kv-agent",  // Index 3154
    "dj-ilm",  // Index 3155
    "nati-vi-server",  // Index 3156
    "satvid-datalnk",  // Index 3157
    "msdtc",  // Index 3158
    "tip2",  // Index 3159
    "lavenir-lm",  // Index 3160
    "cluster-disc",  // Index 3161
    "vsnm-agent",  // Index 3162
    "cdbroker",  // Index 3163
    "cogsys-lm",  // Index 3164
    "wsicopy",  // Index 3165
    "socorfs",  // Index 3166
    "sns-channels",  // Index 3167
    "geneous",  // Index 3168
    "fujitsu-neat",  // Index 3169
    "esp-lm",  // Index 3170
    "hp-clic",  // Index 3171
    "qnxnetman",  // Index 3172
    "gprs-data",  // Index 3173
    "gprs-sig",  // Index 3174
    "backroomnet",  // Index 3175
    "cbserver",  // Index 3176
    "ms-wbt-server",  // Index 3177
    "dsc",  // Index 3178
    "savant",  // Index 3179
    "efi-lm",  // Index 3180
    "d2k-tapestry1",  // Index 3181
    "d2k-tapestry2",  // Index 3182
    "dyna-lm",  // Index 3183
    "printer_agent",  // Index 3184
    "saposs",  // Index 3185
    "cloanto-lm",  // Index 3186
    "sapcomm",  // Index 3187
    "mercantile",  // Index 3188
    "sapeps",  // Index 3189
    "csms",  // Index 3190
    "csms2",  // Index 3191
    "filecast",  // Index 3192
    "squid-snmp",  // Index 3193
    "fxaengine-net",  // Index 3194
    "nokia-ann-ch1",  // Index 3195
    "nokia-ann-ch2",  // Index 3196
    "ldap-admin",  // Index 3197
    "BESApi",  // Index 3198
    "networklens",  // Index 3199
    "networklenss",  // Index 3200
    "biolink-auth",  // Index 3201
    "xmlblaster",  // Index 3202
    "svnet",  // Index 3203
    "wip-port",  // Index 3204
    "bcinameservice",  // Index 3205
    "commandport",  // Index 3206
    "csvr",  // Index 3207
    "rnmap",  // Index 3208
    "softaudit",  // Index 3209
    "ifcp-port",  // Index 3210
    "bmap",  // Index 3211
    "rusb-sys-port",  // Index 3212
    "xtrm",  // Index 3213
    "xtrms",  // Index 3214
    "agps-port",  // Index 3215
    "arkivio",  // Index 3216
    "websphere-snmp",  // Index 3217
    "twcss",  // Index 3218
    "gcsp",  // Index 3219
    "ssdispatch",  // Index 3220
    "ndl-als",  // Index 3221
    "osdcp",  // Index 3222
    "alta-smp",  // Index 3223
    "opencm",  // Index 3224
    "pacom",  // Index 3225
    "gc-config",  // Index 3226
    "autocueds",  // Index 3227
    "spiral-admin",  // Index 3228
    "hri-port",  // Index 3229
    "ans-console",  // Index 3230
    "connect-client",  // Index 3231
    "connect-server",  // Index 3232
    "ov-nnm-websrv",  // Index 3233
    "denali-server",  // Index 3234
    "monp",  // Index 3235
    "3comfaxrpc",  // Index 3236
    "directnet",  // Index 3237
    "dnc-port",  // Index 3238
    "hotu-chat",  // Index 3239
    "castorproxy",  // Index 3240
    "asam",  // Index 3241
    "sabp-signal",  // Index 3242
    "pscupd",  // Index 3243
    "mira",  // Index 3244
    "prsvp",  // Index 3245
    "vat",  // Index 3246
    "IISrpc-or-vat",  // Index 3247
    "vat-control",  // Index 3248
    "d3winosfi",  // Index 3249
    "integral",  // Index 3250
    "edm-manager",  // Index 3251
    "edm-stager",  // Index 3252
    "track",  // Index 3253
    "edm-std-notify",  // Index 3254
    "edm-adm-notify",  // Index 3255
    "edm-mgr-sync",  // Index 3256
    "edm-mgr-cntrl",  // Index 3257
    "workflow",  // Index 3258
    "rcst",  // Index 3259
    "ttcmremotectrl",  // Index 3260
    "pluribus",  // Index 3261
    "jt400",  // Index 3262
    "jt400-ssl",  // Index 3263
    "jaugsremotec-1",  // Index 3264
    "jaugsremotec-2",  // Index 3265
    "ttntspauto",  // Index 3266
    "genisar-port",  // Index 3267
    "nppmp",  // Index 3268
    "ecomm",  // Index 3269
    "stun",  // Index 3270
    "twrpc",  // Index 3271
    "plethora",  // Index 3272
    "cleanerliverc",  // Index 3273
    "vulture",  // Index 3274
    "slim-devices",  // Index 3275
    "gbs-stp",  // Index 3276
    "celatalk",  // Index 3277
    "ifsf-hb-port",  // Index 3278
    "ltctcp",  // Index 3279
    "ltcudp",  // Index 3280
    "fs-rh-srv",  // Index 3281
    "dtp-dia",  // Index 3282
    "colubris",  // Index 3283
    "swr-port",  // Index 3284
    "tvdumtray-port",  // Index 3285
    "nut",  // Index 3286
    "ibm3494",  // Index 3287
    "seclayer-tcp",  // Index 3288
    "seclayer-tls",  // Index 3289
    "ipether232port",  // Index 3290
    "dashpas-port",  // Index 3291
    "sccip-media",  // Index 3292
    "rtmp-port",  // Index 3293
    "isoft-p2p",  // Index 3294
    "avinstalldisc",  // Index 3295
    "lsp-ping",  // Index 3296
    "ironstorm",  // Index 3297
    "ccmcomm",  // Index 3298
    "apc-3506",  // Index 3299
    "nesh-broker",  // Index 3300
    "interactionweb",  // Index 3301
    "vt-ssl",  // Index 3302
    "xss-port",  // Index 3303
    "webmail-2",  // Index 3304
    "aztec",  // Index 3305
    "arcpd",  // Index 3306
    "must-p2p",  // Index 3307
    "must-backplane",  // Index 3308
    "smartcard-port",  // Index 3309
    "802-11-iapp",  // Index 3310
    "artifact-msg",  // Index 3311
    "nvmsgd",  // Index 3312
    "galileo",  // Index 3313
    "galileolog",  // Index 3314
    "mc3ss",  // Index 3315
    "nssocketport",  // Index 3316
    "odeumservlink",  // Index 3317
    "ecmport",  // Index 3318
    "eisport",  // Index 3319
    "starquiz-port",  // Index 3320
    "beserver-msg-q",  // Index 3321
    "jboss-iiop",  // Index 3322
    "jboss-iiop-ssl",  // Index 3323
    "gf",  // Index 3324
    "peerenabler",  // Index 3325
    "raven-rmp",  // Index 3326
    "raven-rdp",  // Index 3327
    "urld-port",  // Index 3328
    "ms-la",  // Index 3329
    "snac",  // Index 3330
    "ni-visa-remote",  // Index 3331
    "ibm-diradm",  // Index 3332
    "ibm-diradm-ssl",  // Index 3333
    "pnrp-port",  // Index 3334
    "voispeed-port",  // Index 3335
    "hacl-monitor",  // Index 3336
    "qftest-lookup",  // Index 3337
    "teredo",  // Index 3338
    "camac",  // Index 3339
    "symantec-sim",  // Index 3340
    "interworld",  // Index 3341
    "tellumat-nms",  // Index 3342
    "ssmpp",  // Index 3343
    "apcupsd",  // Index 3344
    "taserver",  // Index 3345
    "rbr-discovery",  // Index 3346
    "questnotify",  // Index 3347
    "razor",  // Index 3348
    "sky-transport",  // Index 3349
    "personalos-001",  // Index 3350
    "mcp-port",  // Index 3351
    "cctv-port",  // Index 3352
    "iniserve-port",  // Index 3353
    "bmc-onekey",  // Index 3354
    "sdbproxy",  // Index 3355
    "watcomdebug",  // Index 3356
    "esimport",  // Index 3357
    "m2pa",  // Index 3358
    "quest-data-hub",  // Index 3359
    "oap",  // Index 3360
    "oap-s",  // Index 3361
    "mbg-ctrl",  // Index 3362
    "mccwebsvr-port",  // Index 3363
    "megardsvr-port",  // Index 3364
    "megaregsvrport",  // Index 3365
    "tag-ups-1",  // Index 3366
    "dmaf-server",  // Index 3367
    "dmaf-caster",  // Index 3368
    "ccm-port",  // Index 3369
    "cmc-port",  // Index 3370
    "config-port",  // Index 3371
    "data-port",  // Index 3372
    "ttat3lb",  // Index 3373
    "nati-svrloc",  // Index 3374
    "kfxaclicensing",  // Index 3375
    "press",  // Index 3376
    "canex-watch",  // Index 3377
    "u-dbap",  // Index 3378
    "emprise-lls",  // Index 3379
    "emprise-lsc",  // Index 3380
    "p2pgroup",  // Index 3381
    "sentinel",  // Index 3382
    "isomair",  // Index 3383
    "wv-csp-sms",  // Index 3384
    "gtrack-server",  // Index 3385
    "gtrack-ne",  // Index 3386
    "bpmd",  // Index 3387
    "mediaspace",  // Index 3388
    "shareapp",  // Index 3389
    "iw-mmogame",  // Index 3390
    "a14",  // Index 3391
    "a15",  // Index 3392
    "quasar-server",  // Index 3393
    "trap-daemon",  // Index 3394
    "visinet-gui",  // Index 3395
    "infiniswitchcl",  // Index 3396
    "int-rcv-cntrl",  // Index 3397
    "bmc-jmx-port",  // Index 3398
    "comcam-io",  // Index 3399
    "splitlock",  // Index 3400
    "precise-i3",  // Index 3401
    "trendchip-dcp",  // Index 3402
    "cpdi-pidas-cm",  // Index 3403
    "echonet",  // Index 3404
    "six-degrees",  // Index 3405
    "hp-dataprotect",  // Index 3406
    "alaris-disc",  // Index 3407
    "sigma-port",  // Index 3408
    "start-network",  // Index 3409
    "cd3o-protocol",  // Index 3410
    "sharp-server",  // Index 3411
    "aairnet-1",  // Index 3412
    "aairnet-2",  // Index 3413
    "ep-pcp",  // Index 3414
    "ep-nsp",  // Index 3415
    "ff-lr-port",  // Index 3416
    "haipe-discover",  // Index 3417
    "dist-upgrade",  // Index 3418
    "volley",  // Index 3419
    "bvcdaemon-port",  // Index 3420
    "jamserverport",  // Index 3421
    "ept-machine",  // Index 3422
    "escvpnet",  // Index 3423
    "cs-remote-db",  // Index 3424
    "cs-services",  // Index 3425
    "distccd",  // Index 3426
    "distcc",  // Index 3427
    "wacp",  // Index 3428
    "hlibmgr",  // Index 3429
    "sdo",  // Index 3430
    "servistaitsm",  // Index 3431
    "scservp",  // Index 3432
    "ehp-backup",  // Index 3433
    "xap-ha",  // Index 3434
    "netplay-port1",  // Index 3435
    "netplay-port2",  // Index 3436
    "juxml-port",  // Index 3437
    "audiojuggler",  // Index 3438
    "ssowatch",  // Index 3439
    "cyc",  // Index 3440
    "xss-srv-port",  // Index 3441
    "splitlock-gw",  // Index 3442
    "fjcp",  // Index 3443
    "nmmp",  // Index 3444
    "prismiq-plugin",  // Index 3445
    "xrpc-registry",  // Index 3446
    "vxcrnbuport",  // Index 3447
    "tsp",  // Index 3448
    "vaprtm",  // Index 3449
    "abatemgr",  // Index 3450
    "abatjss",  // Index 3451
    "immedianet-bcn",  // Index 3452
    "ps-ams",  // Index 3453
    "apple-sasl",  // Index 3454
    "can-nds-ssl",  // Index 3455
    "can-ferret-ssl",  // Index 3456
    "pserver",  // Index 3457
    "dtp",  // Index 3458
    "ups-engine",  // Index 3459
    "ent-engine",  // Index 3460
    "eserver-pap",  // Index 3461
    "infoexch",  // Index 3462
    "dell-rm-port",  // Index 3463
    "casanswmgmt",  // Index 3464
    "smile",  // Index 3465
    "efcp",  // Index 3466
    "lispworks-orb",  // Index 3467
    "mediavault-gui",  // Index 3468
    "wininstall-ipc",  // Index 3469
    "calltrax",  // Index 3470
    "va-pacbase",  // Index 3471
    "roverlog",  // Index 3472
    "ipr-dglt",  // Index 3473
    "newton-dock",  // Index 3474
    "npds-tracker",  // Index 3475
    "bts-x73",  // Index 3476
    "cas-mapi",  // Index 3477
    "bmc-ea",  // Index 3478
    "faxstfx-port",  // Index 3479
    "dsx-agent",  // Index 3480
    "tnmpv2",  // Index 3481
    "simple-push",  // Index 3482
    "simple-push-s",  // Index 3483
    "rendezvous",  // Index 3484
    "daap",  // Index 3485
    "svn",  // Index 3486
    "magaya-network",  // Index 3487
    "intelsync",  // Index 3488
    "easl",  // Index 3489
    "bmc-data-coll",  // Index 3490
    "telnetcpcd",  // Index 3491
    "nw-license",  // Index 3492
    "sagectlpanel",  // Index 3493
    "kpn-icw",  // Index 3494
    "lrs-paging",  // Index 3495
    "netcelera",  // Index 3496
    "ws-discovery",  // Index 3497
    "adobeserver-3",  // Index 3498
    "adobeserver-4",  // Index 3499
    "adobeserver-5",  // Index 3500
    "rt-event",  // Index 3501
    "rt-event-s",  // Index 3502
    "sun-as-iiops",  // Index 3503
    "ca-idms",  // Index 3504
    "portgate-auth",  // Index 3505
    "edb-server2",  // Index 3506
    "sentinel-ent",  // Index 3507
    "tftps",  // Index 3508
    "delos-dms",  // Index 3509
    "anoto-rendezv",  // Index 3510
    "wv-csp-sms-cir",  // Index 3511
    "wv-csp-udp-cir",  // Index 3512
    "opus-services",  // Index 3513
    "itelserverport",  // Index 3514
    "ufastro-instr",  // Index 3515
    "xsync",  // Index 3516
    "xserveraid",  // Index 3517
    "sychrond",  // Index 3518
    "blizwow",  // Index 3519
    "na-er-tip",  // Index 3520
    "array-manager",  // Index 3521
    "e-mdu",  // Index 3522
    "e-woa",  // Index 3523
    "fksp-audit",  // Index 3524
    "client-ctrl",  // Index 3525
    "smap",  // Index 3526
    "m-wnn",  // Index 3527
    "multip-msg",  // Index 3528
    "synel-data",  // Index 3529
    "pwdis",  // Index 3530
    "rs-rmi",  // Index 3531
    "xpanel",  // Index 3532
    "versatalk",  // Index 3533
    "launchbird-lm",  // Index 3534
    "heartbeat",  // Index 3535
    "wysdma",  // Index 3536
    "cst-port",  // Index 3537
    "ipcs-command",  // Index 3538
    "sasg",  // Index 3539
    "gw-call-port",  // Index 3540
    "linktest",  // Index 3541
    "linktest-s",  // Index 3542
    "webdata",  // Index 3543
    "cimtrak",  // Index 3544
    "cbos-ip-port",  // Index 3545
    "gprs-cube",  // Index 3546
    "vipremoteagent",  // Index 3547
    "nattyserver",  // Index 3548
    "timestenbroker",  // Index 3549
    "sas-remote-hlp",  // Index 3550
    "canon-capt",  // Index 3551
    "grf-port",  // Index 3552
    "apw-registry",  // Index 3553
    "exapt-lmgr",  // Index 3554
    "adtempusclient",  // Index 3555
    "gsakmp",  // Index 3556
    "gbs-smp",  // Index 3557
    "xo-wave",  // Index 3558
    "mni-prot-rout",  // Index 3559
    "rtraceroute",  // Index 3560
    "sitewatch-s",  // Index 3561
    "listmgr-port",  // Index 3562
    "rblcheckd",  // Index 3563
    "haipe-otnk",  // Index 3564
    "cindycollab",  // Index 3565
    "paging-port",  // Index 3566
    "ctp",  // Index 3567
    "ctdhercules",  // Index 3568
    "zicom",  // Index 3569
    "ispmmgr",  // Index 3570
    "dvcprov-port",  // Index 3571
    "jibe-eb",  // Index 3572
    "c-h-it-port",  // Index 3573
    "cognima",  // Index 3574
    "nnp",  // Index 3575
    "abcvoice-port",  // Index 3576
    "iso-tp0s",  // Index 3577
    "bim-pem",  // Index 3578
    "bfd-control",  // Index 3579
    "bfd-echo",  // Index 3580
    "upstriggervsw",  // Index 3581
    "fintrx",  // Index 3582
    "isrp-port",  // Index 3583
    "remotedeploy",  // Index 3584
    "quickbooksrds",  // Index 3585
    "tvnetworkvideo",  // Index 3586
    "sitewatch",  // Index 3587
    "dcsoftware",  // Index 3588
    "jaus",  // Index 3589
    "myblast",  // Index 3590
    "spw-dialer",  // Index 3591
    "idps",  // Index 3592
    "minilock",  // Index 3593
    "radius-dynauth",  // Index 3594
    "pwgpsi",  // Index 3595
    "ibm-mgr",  // Index 3596
    "vhd",  // Index 3597
    "soniqsync",  // Index 3598
    "iqnet-port",  // Index 3599
    "tcpdataserver",  // Index 3600
    "wsmlb",  // Index 3601
    "spugna",  // Index 3602
    "sun-as-iiops-ca",  // Index 3603
    "apocd",  // Index 3604
    "wlanauth",  // Index 3605
    "amp",  // Index 3606
    "neto-wol-server",  // Index 3607
    "rap-ip",  // Index 3608
    "neto-dcs",  // Index 3609
    "lansurveyorxml",  // Index 3610
    "sunlps-http",  // Index 3611
    "tapeware",  // Index 3612
    "crinis-hb",  // Index 3613
    "epl-slp",  // Index 3614
    "scp",  // Index 3615
    "pmcp",  // Index 3616
    "acp-discovery",  // Index 3617
    "acp-conduit",  // Index 3618
    "acp-policy",  // Index 3619
    "ffserver",  // Index 3620
    "wormux",  // Index 3621
    "netmpi",  // Index 3622
    "neteh",  // Index 3623
    "neteh-ext",  // Index 3624
    "cernsysmgmtagt",  // Index 3625
    "dvapps",  // Index 3626
    "xxnetserver",  // Index 3627
    "aipn-auth",  // Index 3628
    "spectardata",  // Index 3629
    "spectardb",  // Index 3630
    "markem-dcp",  // Index 3631
    "mkm-discovery",  // Index 3632
    "sos",  // Index 3633
    "amx-rms",  // Index 3634
    "flirtmitmir",  // Index 3635
    "zfirm-shiprush3",  // Index 3636
    "nhci",  // Index 3637
    "quest-agent",  // Index 3638
    "rnm",  // Index 3639
    "v-one-spp",  // Index 3640
    "an-pcp",  // Index 3641
    "msfw-control",  // Index 3642
    "item",  // Index 3643
    "spw-dnspreload",  // Index 3644
    "qtms-bootstrap",  // Index 3645
    "spectraport",  // Index 3646
    "sse-app-config",  // Index 3647
    "sscan",  // Index 3648
    "stryker-com",  // Index 3649
    "opentrac",  // Index 3650
    "informer",  // Index 3651
    "trap-port",  // Index 3652
    "trap-port-mom",  // Index 3653
    "nav-port",  // Index 3654
    "sasp",  // Index 3655
    "winshadow-hd",  // Index 3656
    "giga-pocket",  // Index 3657
    "asap-sctp",  // Index 3658
    "asap-tcp",  // Index 3659
    "asap-sctp-tls",  // Index 3660
    "asap-tcp-tls",  // Index 3661
    "xpl",  // Index 3662
    "dzdaemon",  // Index 3663
    "dzoglserver",  // Index 3664
    "diameter",  // Index 3665
    "ovsam-mgmt",  // Index 3666
    "ovsam-d-agent",  // Index 3667
    "avocent-adsap",  // Index 3668
    "oem-agent",  // Index 3669
    "fagordnc",  // Index 3670
    "sixxsconfig",  // Index 3671
    "pnbscada",  // Index 3672
    "dl_agent",  // Index 3673
    "xmpcr-interface",  // Index 3674
    "fotogcad",  // Index 3675
    "appss-lm",  // Index 3676
    "igrs",  // Index 3677
    "idac",  // Index 3678
    "msdts1",  // Index 3679
    "vrpn",  // Index 3680
    "softrack-meter",  // Index 3681
    "topflow-ssl",  // Index 3682
    "nei-management",  // Index 3683
    "ciphire-data",  // Index 3684
    "ciphire-serv",  // Index 3685
    "dandv-tester",  // Index 3686
    "ndsconnect",  // Index 3687
    "rtc-pm-port",  // Index 3688
    "pcc-image-port",  // Index 3689
    "cgi-starapi",  // Index 3690
    "syam-agent",  // Index 3691
    "syam-smc",  // Index 3692
    "sdo-tls",  // Index 3693
    "sdo-ssh",  // Index 3694
    "senip",  // Index 3695
    "itv-control",  // Index 3696
    "nimsh",  // Index 3697
    "nimaux",  // Index 3698
    "charsetmgr",  // Index 3699
    "omnilink-port",  // Index 3700
    "mupdate",  // Index 3701
    "topovista-data",  // Index 3702
    "imoguia-port",  // Index 3703
    "hppronetman",  // Index 3704
    "surfcontrolcpa",  // Index 3705
    "prnrequest",  // Index 3706
    "prnstatus",  // Index 3707
    "gbmt-stars",  // Index 3708
    "listcrt-port",  // Index 3709
    "listcrt-port-2",  // Index 3710
    "agcat",  // Index 3711
    "wysdmc",  // Index 3712
    "aftmux",  // Index 3713
    "pktcablemmcops",  // Index 3714
    "hyperip",  // Index 3715
    "exasoftport1",  // Index 3716
    "herodotus-net",  // Index 3717
    "sor-update",  // Index 3718
    "symb-sb-port",  // Index 3719
    "mpl-gprs-port",  // Index 3720
    "zmp",  // Index 3721
    "winport",  // Index 3722
    "natdataservice",  // Index 3723
    "netboot-pxe",  // Index 3724
    "smauth-port",  // Index 3725
    "syam-webserver",  // Index 3726
    "msr-plugin-port",  // Index 3727
    "dyn-site",  // Index 3728
    "plbserve-port",  // Index 3729
    "sunfm-port",  // Index 3730
    "sdp-portmapper",  // Index 3731
    "mailprox",  // Index 3732
    "dvbservdsc",  // Index 3733
    "dbcontrol_agent",  // Index 3734
    "aamp",  // Index 3735
    "xecp-node",  // Index 3736
    "homeportal-web",  // Index 3737
    "srdp",  // Index 3738
    "tig",  // Index 3739
    "sops",  // Index 3740
    "emcads",  // Index 3741
    "backupedge",  // Index 3742
    "ccp",  // Index 3743
    "apdap",  // Index 3744
    "drip",  // Index 3745
    "namemunge",  // Index 3746
    "pwgippfax",  // Index 3747
    "i3-sessionmgr",  // Index 3748
    "xmlink-connect",  // Index 3749
    "adrep",  // Index 3750
    "p2pcommunity",  // Index 3751
    "gvcp",  // Index 3752
    "mqe-broker",  // Index 3753
    "mqe-agent",  // Index 3754
    "treehopper",  // Index 3755
    "bess",  // Index 3756
    "proaxess",  // Index 3757
    "sbi-agent",  // Index 3758
    "thrp",  // Index 3759
    "sasggprs",  // Index 3760
    "ati-ip-to-ncpe",  // Index 3761
    "bflckmgr",  // Index 3762
    "ppsms",  // Index 3763
    "ianywhere-dbns",  // Index 3764
    "landmarks",  // Index 3765
    "lanrevagent",  // Index 3766
    "lanrevserver",  // Index 3767
    "iconp",  // Index 3768
    "progistics",  // Index 3769
    "citysearch",  // Index 3770
    "airshot",  // Index 3771
    "opswagent",  // Index 3772
    "opswmanager",  // Index 3773
    "secure-cfg-svr",  // Index 3774
    "smwan",  // Index 3775
    "acms",  // Index 3776
    "starfish",  // Index 3777
    "eis",  // Index 3778
    "eisp",  // Index 3779
    "mapper-nodemgr",  // Index 3780
    "mapper-mapethd",  // Index 3781
    "mapper-ws_ethd",  // Index 3782
    "centerline",  // Index 3783
    "dcs-config",  // Index 3784
    "bv-queryengine",  // Index 3785
    "bv-is",  // Index 3786
    "bv-smcsrv",  // Index 3787
    "bv-ds",  // Index 3788
    "bv-agent",  // Index 3789
    "iss-mgmt-ssl",  // Index 3790
    "abcsoftware",  // Index 3791
    "remoteanything",  // Index 3792
    "agentsease-db",  // Index 3793
    "dnx",  // Index 3794
    "nvcnet",  // Index 3795
    "icq",  // Index 3796
    "newoak",  // Index 3797
    "mlchat-proxy",  // Index 3798
    "pxc-spvr-ft",  // Index 3799
    "pxc-splr-ft",  // Index 3800
    "pxc-roid",  // Index 3801
    "pxc-pin",  // Index 3802
    "pxc-spvr",  // Index 3803
    "pxc-splr",  // Index 3804
    "netcheque",  // Index 3805
    "chimera-hwm",  // Index 3806
    "samsung-unidex",  // Index 3807
    "altserviceboot",  // Index 3808
    "pda-gate",  // Index 3809
    "acl-manager",  // Index 3810
    "taiclock",  // Index 3811
    "talarian-mcast1",  // Index 3812
    "talarian-mcast2",  // Index 3813
    "talarian-mcast3",  // Index 3814
    "talarian-mcast4",  // Index 3815
    "talarian-mcast5",  // Index 3816
    "trap",  // Index 3817
    "nexus-portal",  // Index 3818
    "dnox",  // Index 3819
    "esnm-zoning",  // Index 3820
    "tnp1-port",  // Index 3821
    "partimage",  // Index 3822
    "as-debug",  // Index 3823
    "bxp",  // Index 3824
    "dtserver-port",  // Index 3825
    "ip-qsig",  // Index 3826
    "jdmn-port",  // Index 3827
    "suucp",  // Index 3828
    "vrts-auth-port",  // Index 3829
    "sanavigator",  // Index 3830
    "ubxd",  // Index 3831
    "wap-push-http",  // Index 3832
    "wap-push-https",  // Index 3833
    "ravehd",  // Index 3834
    "fazzt-ptp",  // Index 3835
    "fazzt-admin",  // Index 3836
    "yo-main",  // Index 3837
    "houston",  // Index 3838
    "ldxp",  // Index 3839
    "nirp",  // Index 3840
    "ltp",  // Index 3841
    "lockd",  // Index 3842
    "acp-proto",  // Index 3843
    "ctp-state",  // Index 3844
    "wafs",  // Index 3845
    "cisco-wafs",  // Index 3846
    "cppdp",  // Index 3847
    "interact",  // Index 3848
    "ccu-comm-1",  // Index 3849
    "ccu-comm-2",  // Index 3850
    "ccu-comm-3",  // Index 3851
    "lms",  // Index 3852
    "wfm",  // Index 3853
    "kingfisher",  // Index 3854
    "dlms-cosem",  // Index 3855
    "dsmeter_iatc",  // Index 3856
    "ice-location",  // Index 3857
    "ice-slocation",  // Index 3858
    "ice-router",  // Index 3859
    "ice-srouter",  // Index 3860
    "avanti_cdp",  // Index 3861
    "pmas",  // Index 3862
    "idp",  // Index 3863
    "ipfltbcst",  // Index 3864
    "minger",  // Index 3865
    "tripe",  // Index 3866
    "aibkup",  // Index 3867
    "zieto-sock",  // Index 3868
    "iRAPP",  // Index 3869
    "cequint-cityid",  // Index 3870
    "perimlan",  // Index 3871
    "seraph",  // Index 3872
    "ascomalarm",  // Index 3873
    "cssp",  // Index 3874
    "santools",  // Index 3875
    "lorica-in",  // Index 3876
    "lorica-in-sec",  // Index 3877
    "lorica-out",  // Index 3878
    "lorica-out-sec",  // Index 3879
    "fortisphere-vm",  // Index 3880
    "ezmessagesrv",  // Index 3881
    "ftsync",  // Index 3882
    "applusservice",  // Index 3883
    "npsp",  // Index 3884
    "opencore",  // Index 3885
    "omasgport",  // Index 3886
    "ewinstaller",  // Index 3887
    "ewdgs",  // Index 3888
    "pvxpluscs",  // Index 3889
    "sysrqd",  // Index 3890
    "xtgui",  // Index 3891
    "bre",  // Index 3892
    "patrolview",  // Index 3893
    "drmsfsd",  // Index 3894
    "dpcp",  // Index 3895
    "igo-incognito",  // Index 3896
    "brlp-0",  // Index 3897
    "brlp-1",  // Index 3898
    "brlp-2",  // Index 3899
    "brlp-3",  // Index 3900
    "shofarplayer",  // Index 3901
    "synchronite",  // Index 3902
    "j-ac",  // Index 3903
    "accel",  // Index 3904
    "izm",  // Index 3905
    "g2tag",  // Index 3906
    "xgrid",  // Index 3907
    "apple-vpns-rp",  // Index 3908
    "aipn-reg",  // Index 3909
    "jomamqmonitor",  // Index 3910
    "cds",  // Index 3911
    "smartcard-tls",  // Index 3912
    "hillrserv",  // Index 3913
    "netscript",  // Index 3914
    "assuria-slm",  // Index 3915
    "minirem",  // Index 3916
    "e-builder",  // Index 3917
    "fprams",  // Index 3918
    "z-wave",  // Index 3919
    "tigv2",  // Index 3920
    "rww",  // Index 3921
    "opsview-envoy",  // Index 3922
    "ddrepl",  // Index 3923
    "unikeypro",  // Index 3924
    "nufw",  // Index 3925
    "nuauth",  // Index 3926
    "fronet",  // Index 3927
    "stars",  // Index 3928
    "nuts_dem",  // Index 3929
    "nuts_bootp",  // Index 3930
    "nifty-hmi",  // Index 3931
    "cl-db-attach",  // Index 3932
    "cl-db-request",  // Index 3933
    "cl-db-remote",  // Index 3934
    "nettest",  // Index 3935
    "thrtx",  // Index 3936
    "cedros_fds",  // Index 3937
    "oirtgsvc",  // Index 3938
    "oidocsvc",  // Index 3939
    "oidsr",  // Index 3940
    "wincim",  // Index 3941
    "vvr-control",  // Index 3942
    "tgcconnect",  // Index 3943
    "vrxpservman",  // Index 3944
    "hhb-handheld",  // Index 3945
    "agslb",  // Index 3946
    "PowerAlert-nsa",  // Index 3947
    "menandmice_noh",  // Index 3948
    "idig_mux",  // Index 3949
    "mbl-battd",  // Index 3950
    "atlinks",  // Index 3951
    "bzr",  // Index 3952
    "stat-results",  // Index 3953
    "stat-scanner",  // Index 3954
    "stat-cc",  // Index 3955
    "nss",  // Index 3956
    "jini-discovery",  // Index 3957
    "omscontact",  // Index 3958
    "omstopology",  // Index 3959
    "silverpeakpeer",  // Index 3960
    "silverpeakcomm",  // Index 3961
    "altcp",  // Index 3962
    "joost",  // Index 3963
    "ddgn",  // Index 3964
    "pslicser",  // Index 3965
    "iadt",  // Index 3966
    "iadt-disc",  // Index 3967
    "d-cinema-csp",  // Index 3968
    "ml-svnet",  // Index 3969
    "pcoip",  // Index 3970
    "mma-discovery",  // Index 3971
    "smcluster",  // Index 3972
    "bccp",  // Index 3973
    "tl-ipcproxy",  // Index 3974
    "wello",  // Index 3975
    "storman",  // Index 3976
    "MaxumSP",  // Index 3977
    "httpx",  // Index 3978
    "macbak",  // Index 3979
    "pcptcpservice",  // Index 3980
    "gmmp",  // Index 3981
    "universe_suite",  // Index 3982
    "wcpp",  // Index 3983
    "boxbackupstore",  // Index 3984
    "csc_proxy",  // Index 3985
    "vatata",  // Index 3986
    "pcep",  // Index 3987
    "sieve",  // Index 3988
    "dsmipv6",  // Index 3989
    "azeti",  // Index 3990
    "azeti-bd",  // Index 3991
    "pvxplusio",  // Index 3992
    "spdm",  // Index 3993
    "aws-wsp",  // Index 3994
    "hctl",  // Index 3995
    "eims-admin",  // Index 3996
    "vrml-multi-use",  // Index 3997
    "xtell",  // Index 3998
    "corelccam",  // Index 3999
    "d-data",  // Index 4000
    "d-data-control",  // Index 4001
    "srcp",  // Index 4002
    "owserver",  // Index 4003
    "batman",  // Index 4004
    "pinghgl",  // Index 4005
    "visicron-vs",  // Index 4006
    "compx-lockview",  // Index 4007
    "dserver",  // Index 4008
    "mirrtex",  // Index 4009
    "p6ssmc",  // Index 4010
    "pscl-mgt",  // Index 4011
    "perrla",  // Index 4012
    "choiceview-agt",  // Index 4013
    "choiceview-clt",  // Index 4014
    "opentelemetry",  // Index 4015
    "fox-skytale",  // Index 4016
    "fdt-rcatp",  // Index 4017
    "rwhois",  // Index 4018
    "trim-event",  // Index 4019
    "trim-ice",  // Index 4020
    "balour",  // Index 4021
    "geognosisman",  // Index 4022
    "geognosis",  // Index 4023
    "jaxer-web",  // Index 4024
    "jaxer-manager",  // Index 4025
    "publiqare-sync",  // Index 4026
    "dey-sapi",  // Index 4027
    "ktickets-rest",  // Index 4028
    "getty-focus",  // Index 4029
    "netconf-ch-ssh",  // Index 4030
    "netconf-ch-tls",  // Index 4031
    "restconf-ch-tls",  // Index 4032
    "gaia",  // Index 4033
    "lisp-data",  // Index 4034
    "lisp-cons",  // Index 4035
    "lisp-control",  // Index 4036
    "unicall",  // Index 4037
    "vinainstall",  // Index 4038
    "m4-network-as",  // Index 4039
    "elanlm",  // Index 4040
    "lansurveyor",  // Index 4041
    "itose",  // Index 4042
    "fsportmap",  // Index 4043
    "net-device",  // Index 4044
    "plcy-net-svcs",  // Index 4045
    "pjlink",  // Index 4046
    "f5-iquery",  // Index 4047
    "qsnet-trans",  // Index 4048
    "qsnet-workst",  // Index 4049
    "qsnet-assist",  // Index 4050
    "qsnet-cond",  // Index 4051
    "qsnet-nucl",  // Index 4052
    "omabcastltkm",  // Index 4053
    "matrix_vnet",  // Index 4054
    "nacnl",  // Index 4055
    "afore-vdp-disc",  // Index 4056
    "shadowstream",  // Index 4057
    "wxbrief",  // Index 4058
    "epmd",  // Index 4059
    "elpro_tunnel",  // Index 4060
    "l2c-control",  // Index 4061
    "l2c-disc",  // Index 4062
    "l2c-data",  // Index 4063
    "remctl",  // Index 4064
    "psi-ptt",  // Index 4065
    "tolteces",  // Index 4066
    "bip",  // Index 4067
    "cp-spxsvr",  // Index 4068
    "cp-spxdpy",  // Index 4069
    "ctdb",  // Index 4070
    "xandros-cms",  // Index 4071
    "wiegand",  // Index 4072
    "apwi-imserver",  // Index 4073
    "apwi-rxserver",  // Index 4074
    "apwi-rxspooler",  // Index 4075
    "apwi-disc",  // Index 4076
    "omnivisionesx",  // Index 4077
    "fly",  // Index 4078
    "ds-srv",  // Index 4079
    "ds-srvr",  // Index 4080
    "ds-clnt",  // Index 4081
    "ds-user",  // Index 4082
    "ds-admin",  // Index 4083
    "ds-mail",  // Index 4084
    "ds-slp",  // Index 4085
    "nacagent",  // Index 4086
    "slscc",  // Index 4087
    "netcabinet-com",  // Index 4088
    "itwo-server",  // Index 4089
    "found",  // Index 4090
    "smallchat",  // Index 4091
    "avi-nms",  // Index 4092
    "updog",  // Index 4093
    "brcd-vr-req",  // Index 4094
    "pjj-player",  // Index 4095
    "workflowdir",  // Index 4096
    "axysbridge",  // Index 4097
    "cbp",  // Index 4098
    "nvm-express",  // Index 4099
    "scaleft",  // Index 4100
    "tsepisp",  // Index 4101
    "thingkit",  // Index 4102
    "netrockey6",  // Index 4103
    "beacon-port-2",  // Index 4104
    "drizzle",  // Index 4105
    "omviserver",  // Index 4106
    "omviagent",  // Index 4107
    "rsqlserver",  // Index 4108
    "wspipe",  // Index 4109
    "l-acoustics",  // Index 4110
    "vop",  // Index 4111
    "netblox",  // Index 4112
    "saris",  // Index 4113
    "pharos",  // Index 4114
    "krb524",  // Index 4115
    "upnotifyp",  // Index 4116
    "n1-fwp",  // Index 4117
    "n1-rmgmt",  // Index 4118
    "asc-slmd",  // Index 4119
    "privatewire",  // Index 4120
    "camp",  // Index 4121
    "ctisystemmsg",  // Index 4122
    "ctiprogramload",  // Index 4123
    "nssalertmgr",  // Index 4124
    "nssagentmgr",  // Index 4125
    "prchat-user",  // Index 4126
    "prchat-server",  // Index 4127
    "prRegister",  // Index 4128
    "mcp",  // Index 4129
    "ntske",  // Index 4130
    "proxy-plus",  // Index 4131
    "hpssmgmt",  // Index 4132
    "assyst-dr",  // Index 4133
    "icms",  // Index 4134
    "prex-tcp",  // Index 4135
    "awacs-ice",  // Index 4136
    "sae-urn",  // Index 4137
    "nat-t-ike",  // Index 4138
    "a25-fap-fgw",  // Index 4139
    "armagetronad",  // Index 4140
    "ehs",  // Index 4141
    "ehs-ssl",  // Index 4142
    "wssauthsvc",  // Index 4143
    "swx-gate",  // Index 4144
    "worldscores",  // Index 4145
    "sf-lm",  // Index 4146
    "lanner-lm",  // Index 4147
    "synchromesh",  // Index 4148
    "aegate",  // Index 4149
    "gds-adppiw-db",  // Index 4150
    "ieee-mih",  // Index 4151
    "menandmice-mon",  // Index 4152
    "icshostsvc",  // Index 4153
    "msfrs",  // Index 4154
    "rsip",  // Index 4155
    "dtn-bundle-tcp",  // Index 4156
    "dtn-bundle-udp",  // Index 4157
    "fax",  // Index 4158
    "mtcevrunqss",  // Index 4159
    "mtcevrunqman",  // Index 4160
    "hylafax",  // Index 4161
    "amahi-anywhere",  // Index 4162
    "kwtc",  // Index 4163
    "tram",  // Index 4164
    "bmc-reporting",  // Index 4165
    "iax",  // Index 4166
    "deploymentmap",  // Index 4167
    "cardifftec-back",  // Index 4168
    "rid",  // Index 4169
    "l3t-at-an",  // Index 4170
    "hrpd-ith-at-an",  // Index 4171
    "ipt-anri-anri",  // Index 4172
    "ias-session",  // Index 4173
    "ias-paging",  // Index 4174
    "ias-neighbor",  // Index 4175
    "a21-an-1xbs",  // Index 4176
    "a16-an-an",  // Index 4177
    "a17-an-an",  // Index 4178
    "piranha1",  // Index 4179
    "piranha2",  // Index 4180
    "mtsserver",  // Index 4181
    "menandmice-upg",  // Index 4182
    "irp",  // Index 4183
    "sixchat",  // Index 4184
    "sixid",  // Index 4185
    "ventoso",  // Index 4186
    "dots-signal",  // Index 4187
    "playsta2-app",  // Index 4188
    "playsta2-lob",  // Index 4189
    "mosmig",  // Index 4190
    "smaclmgr",  // Index 4191
    "kar2ouche",  // Index 4192
    "edonkey",  // Index 4193
    "oms",  // Index 4194
    "noteit",  // Index 4195
    "ems",  // Index 4196
    "contclientms",  // Index 4197
    "eportcomm",  // Index 4198
    "mmacomm",  // Index 4199
    "mmaeds",  // Index 4200
    "eportcommdata",  // Index 4201
    "light",  // Index 4202
    "acter",  // Index 4203
    "rfa",  // Index 4204
    "cxws",  // Index 4205
    "appiq-mgmt",  // Index 4206
    "dhct-status",  // Index 4207
    "dhct-alerts",  // Index 4208
    "bcs",  // Index 4209
    "traversal",  // Index 4210
    "mgesupervision",  // Index 4211
    "mgemanagement",  // Index 4212
    "parliant",  // Index 4213
    "finisar",  // Index 4214
    "spike",  // Index 4215
    "rfid-rp1",  // Index 4216
    "autopac",  // Index 4217
    "msp-os",  // Index 4218
    "nst",  // Index 4219
    "mobile-p2p",  // Index 4220
    "altovacentral",  // Index 4221
    "prelude",  // Index 4222
    "mtn",  // Index 4223
    "conspiracy",  // Index 4224
    "netxms-agent",  // Index 4225
    "netxms-mgmt",  // Index 4226
    "netxms-sync",  // Index 4227
    "npqes-test",  // Index 4228
    "assuria-ins",  // Index 4229
    "trinity-dist",  // Index 4230
    "pulseaudio",  // Index 4231
    "truckstar",  // Index 4232
    "a26-fap-fgw",  // Index 4233
    "fcis",  // Index 4234
    "fcis-disc",  // Index 4235
    "capmux",  // Index 4236
    "gsmtap",  // Index 4237
    "gearman",  // Index 4238
    "remcap",  // Index 4239
    "ohmtrigger",  // Index 4240
    "resorcs",  // Index 4241
    "ipdr-sp",  // Index 4242
    "solera-lpn",  // Index 4243
    "ipfix",  // Index 4244
    "ipfixs",  // Index 4245
    "lumimgrd",  // Index 4246
    "sicct",  // Index 4247
    "sicct-sdp",  // Index 4248
    "openhpid",  // Index 4249
    "ifsp",  // Index 4250
    "fmp",  // Index 4251
    "intelliadm-disc",  // Index 4252
    "buschtrommel",  // Index 4253
    "profilemac",  // Index 4254
    "ssad",  // Index 4255
    "spocp",  // Index 4256
    "snap",  // Index 4257
    "simon",  // Index 4258
    "gre-in-udp",  // Index 4259
    "gre-udp-dtls",  // Index 4260
    "RDCenter",  // Index 4261
    "converge",  // Index 4262
    "bfd-multi-ctl",  // Index 4263
    "cncp",  // Index 4264
    "smart-install",  // Index 4265
    "sia-ctrl-plane",  // Index 4266
    "xmcp",  // Index 4267
    "vxlan",  // Index 4268
    "vxlan-gpe",  // Index 4269
    "roce",  // Index 4270
    "unified-bus",  // Index 4271
    "iims",  // Index 4272
    "iwec",  // Index 4273
    "ilss",  // Index 4274
    "notateit",  // Index 4275
    "notateit-disc",  // Index 4276
    "aja-ntv4-disc",  // Index 4277
    "htcp",  // Index 4278
    "squid-htcp",  // Index 4279
    "varadero-0",  // Index 4280
    "varadero-1",  // Index 4281
    "varadero-2",  // Index 4282
    "opcua-tcp",  // Index 4283
    "opcua-udp",  // Index 4284
    "quosa",  // Index 4285
    "gw-asv",  // Index 4286
    "opcua-tls",  // Index 4287
    "gw-log",  // Index 4288
    "wcr-remlib",  // Index 4289
    "contamac_icm",  // Index 4290
    "wfc",  // Index 4291
    "appserv-http",  // Index 4292
    "appserv-https",  // Index 4293
    "sun-as-nodeagt",  // Index 4294
    "derby-repli",  // Index 4295
    "unify-debug",  // Index 4296
    "phrelay",  // Index 4297
    "phrelaydbg",  // Index 4298
    "cc-tracking",  // Index 4299
    "wired",  // Index 4300
    "tritium-can",  // Index 4301
    "lmcs",  // Index 4302
    "inst-discovery",  // Index 4303
    "wsdl-event",  // Index 4304
    "hislip",  // Index 4305
    "socp-t",  // Index 4306
    "socp-c",  // Index 4307
    "wmlserver",  // Index 4308
    "hivestor",  // Index 4309
    "abbs",  // Index 4310
    "xcap-portal",  // Index 4311
    "xcap-control",  // Index 4312
    "lyskom",  // Index 4313
    "radmin",  // Index 4314
    "radmin-port",  // Index 4315
    "hfcs",  // Index 4316
    "flr_agent",  // Index 4317
    "magiccontrol",  // Index 4318
    "lutap",  // Index 4319
    "lutcp",  // Index 4320
    "bones",  // Index 4321
    "frcs",  // Index 4322
    "an-signaling",  // Index 4323
    "atsc-mh-ssc",  // Index 4324
    "eq-office-4940",  // Index 4325
    "eq-office-4941",  // Index 4326
    "eq-office-4942",  // Index 4327
    "munin",  // Index 4328
    "sybasesrvmon",  // Index 4329
    "pwgwims",  // Index 4330
    "sagxtsds",  // Index 4331
    "dbsyncarbiter",  // Index 4332
    "ccss-qmm",  // Index 4333
    "ccss-qsm",  // Index 4334
    "burp",  // Index 4335
    "ctxs-vpp",  // Index 4336
    "webyast",  // Index 4337
    "gerhcs",  // Index 4338
    "mrip",  // Index 4339
    "maybe-veritas",  // Index 4340
    "smar-se-port1",  // Index 4341
    "smar-se-port2",  // Index 4342
    "parallel",  // Index 4343
    "busycal",  // Index 4344
    "vrt",  // Index 4345
    "hfcs-manager",  // Index 4346
    "commplex-link",  // Index 4347
    "rfe",  // Index 4348
    "filemaker",  // Index 4349
    "avt-profile-1",  // Index 4350
    "avt-profile-2",  // Index 4351
    "wsm-server",  // Index 4352
    "wsm-server-ssl",  // Index 4353
    "synapsis-edge",  // Index 4354
    "airport-admin",  // Index 4355
    "winfs",  // Index 4356
    "telelpathstart",  // Index 4357
    "telelpathattack",  // Index 4358
    "nsp",  // Index 4359
    "fmpro-v6",  // Index 4360
    "onpsocket",  // Index 4361
    "fmwp",  // Index 4362
    "zenginkyo-1",  // Index 4363
    "zenginkyo-2",  // Index 4364
    "mice",  // Index 4365
    "htuilsrv",  // Index 4366
    "scpi-telnet",  // Index 4367
    "scpi-raw",  // Index 4368
    "strexec-d",  // Index 4369
    "strexec-s",  // Index 4370
    "qvr",  // Index 4371
    "infobright",  // Index 4372
    "surfpass",  // Index 4373
    "dmp",  // Index 4374
    "signacert-agent",  // Index 4375
    "jtnetd-server",  // Index 4376
    "jtnetd-status",  // Index 4377
    "asnaacceler8db",  // Index 4378
    "swxadmin",  // Index 4379
    "lxi-evntsvc",  // Index 4380
    "osp",  // Index 4381
    "vpm-udp",  // Index 4382
    "iscape",  // Index 4383
    "texai",  // Index 4384
    "ivocalize",  // Index 4385
    "mmcc",  // Index 4386
    "ida-agent",  // Index 4387
    "ita-agent",  // Index 4388
    "ita-manager",  // Index 4389
    "rlm",  // Index 4390
    "rlm-admin",  // Index 4391
    "unot",  // Index 4392
    "intecom-ps1",  // Index 4393
    "intecom-ps2",  // Index 4394
    "locus-disc",  // Index 4395
    "sds",  // Index 4396
    "sip",  // Index 4397
    "sip-tls",  // Index 4398
    "na-localise",  // Index 4399
    "csrpc",  // Index 4400
    "ca-1",  // Index 4401
    "ca-2",  // Index 4402
    "stanag-5066",  // Index 4403
    "authentx",  // Index 4404
    "bitforestsrv",  // Index 4405
    "i-net-2000-npr",  // Index 4406
    "vtsas",  // Index 4407
    "powerschool",  // Index 4408
    "ayiya",  // Index 4409
    "tag-pm",  // Index 4410
    "alesquery",  // Index 4411
    "pvaccess",  // Index 4412
    "pixelpusher",  // Index 4413
    "cp-spxrpts",  // Index 4414
    "onscreen",  // Index 4415
    "sdl-ets",  // Index 4416
    "qcp",  // Index 4417
    "qfp",  // Index 4418
    "llrp",  // Index 4419
    "encrypted-llrp",  // Index 4420
    "aprigo-cs",  // Index 4421
    "biotic",  // Index 4422
    "car",  // Index 4423
    "cxtp",  // Index 4424
    "magpie",  // Index 4425
    "sentinel-lm",  // Index 4426
    "hart-ip",  // Index 4427
    "sentlm-srv2srv",  // Index 4428
    "admd",  // Index 4429
    "socalia",  // Index 4430
    "admdog",  // Index 4431
    "talarian-udp",  // Index 4432
    "admeng",  // Index 4433
    "oms-nonsecure",  // Index 4434
    "actifio-c2c",  // Index 4435
    "tinymessage",  // Index 4436
    "hughes-ap",  // Index 4437
    "actifioudsagent",  // Index 4438
    "actifioreplic",  // Index 4439
    "taep-as-svc",  // Index 4440
    "pm-cmdsvr",  // Index 4441
    "ev-services",  // Index 4442
    "autobuild",  // Index 4443
    "emb-proj-cmd",  // Index 4444
    "gradecam",  // Index 4445
    "barracuda-bbs",  // Index 4446
    "nbt-pc",  // Index 4447
    "ppactivation",  // Index 4448
    "erp-scale",  // Index 4449
    "minotaur-sa",  // Index 4450
    "ctsd",  // Index 4451
    "rmonitor_secure",  // Index 4452
    "social-alarm",  // Index 4453
    "atmp",  // Index 4454
    "esri_sde",  // Index 4455
    "sde-discovery",  // Index 4456
    "toruxserver",  // Index 4457
    "bzflag",  // Index 4458
    "asctrl-agent",  // Index 4459
    "rugameonline",  // Index 4460
    "mediat",  // Index 4461
    "snmpssh",  // Index 4462
    "snmpssh-trap",  // Index 4463
    "sbackup",  // Index 4464
    "vpa",  // Index 4465
    "vpa-disc",  // Index 4466
    "ife_icorp",  // Index 4467
    "winpcs",  // Index 4468
    "scte104",  // Index 4469
    "scte30",  // Index 4470
    "pcoip-mgmt",  // Index 4471
    "aol",  // Index 4472
    "aol-1",  // Index 4473
    "aol-2",  // Index 4474
    "aol-3",  // Index 4475
    "cpscomm",  // Index 4476
    "ampl-lic",  // Index 4477
    "ampl-tableproxy",  // Index 4478
    "tunstall-lwp",  // Index 4479
    "targus-getdata",  // Index 4480
    "targus-getdata1",  // Index 4481
    "targus-getdata2",  // Index 4482
    "targus-getdata3",  // Index 4483
    "nomad",  // Index 4484
    "noteza",  // Index 4485
    "3exmp",  // Index 4486
    "xmpp-client",  // Index 4487
    "hpvirtgrp",  // Index 4488
    "hpvirtctrl",  // Index 4489
    "hp-server",  // Index 4490
    "hp-status",  // Index 4491
    "perfd",  // Index 4492
    "hpvroom",  // Index 4493
    "jaxflow",  // Index 4494
    "jaxflow-data",  // Index 4495
    "crusecontrol",  // Index 4496
    "sgi-dgl",  // Index 4497
    "enfs",  // Index 4498
    "eenet",  // Index 4499
    "galaxy-network",  // Index 4500
    "padl2sim",  // Index 4501
    "mnet-discovery",  // Index 4502
    "attune",  // Index 4503
    "xycstatus",  // Index 4504
    "downtools",  // Index 4505
    "downtools-disc",  // Index 4506
    "capwap-control",  // Index 4507
    "capwap-data",  // Index 4508
    "caacws",  // Index 4509
    "caaclang2",  // Index 4510
    "soagateway",  // Index 4511
    "caevms",  // Index 4512
    "movaz-ssc",  // Index 4513
    "kpdp",  // Index 4514
    "logcabin",  // Index 4515
    "3com-njack-1",  // Index 4516
    "3com-njack-2",  // Index 4517
    "xmpp-server",  // Index 4518
    "xmp",  // Index 4519
    "cuelink",  // Index 4520
    "cuelink-disc",  // Index 4521
    "pk",  // Index 4522
    "xmpp-bosh",  // Index 4523
    "undo-lm",  // Index 4524
    "transmit-port",  // Index 4525
    "presence",  // Index 4526
    "nlg-data",  // Index 4527
    "hacl-hb",  // Index 4528
    "hacl-gs",  // Index 4529
    "hacl-cfg",  // Index 4530
    "hacl-probe",  // Index 4531
    "hacl-local",  // Index 4532
    "hacl-test",  // Index 4533
    "sun-mc-grp",  // Index 4534
    "sco-aip",  // Index 4535
    "cfengine",  // Index 4536
    "jprinter",  // Index 4537
    "outlaws",  // Index 4538
    "permabit-cs",  // Index 4539
    "rrdp",  // Index 4540
    "opalis-rbt-ipc",  // Index 4541
    "hacl-poll",  // Index 4542
    "hpdevms",  // Index 4543
    "pkix-cmc",  // Index 4544
    "bsfserver-zn",  // Index 4545
    "bsfsvr-zn-ssl",  // Index 4546
    "kfserver",  // Index 4547
    "xkotodrcp",  // Index 4548
    "stuns",  // Index 4549
    "nat-pmp-status",  // Index 4550
    "nat-pmp",  // Index 4551
    "dns-llq",  // Index 4552
    "mdns",  // Index 4553
    "zeroconf",  // Index 4554
    "mdnsresponder",  // Index 4555
    "llmnr",  // Index 4556
    "ms-smlbiz",  // Index 4557
    "wsdapi",  // Index 4558
    "wsdapi-s",  // Index 4559
    "ms-alerter",  // Index 4560
    "ms-sideshow",  // Index 4561
    "ms-s-sideshow",  // Index 4562
    "serverwsd2",  // Index 4563
    "net-projection",  // Index 4564
    "kdnet",  // Index 4565
    "stresstester",  // Index 4566
    "elektron-admin",  // Index 4567
    "securitychase",  // Index 4568
    "pcduo-old",  // Index 4569
    "excerpt",  // Index 4570
    "excerpts",  // Index 4571
    "hpoms-ci-lstn",  // Index 4572
    "hpoms-dps-lstn",  // Index 4573
    "pcduo",  // Index 4574
    "netsupport",  // Index 4575
    "systemics-sox",  // Index 4576
    "foresyte-clear",  // Index 4577
    "foresyte-sec",  // Index 4578
    "salient-dtasrv",  // Index 4579
    "salient-usrmgr",  // Index 4580
    "actnet",  // Index 4581
    "continuus",  // Index 4582
    "wwiotalk",  // Index 4583
    "statusd",  // Index 4584
    "ns-server",  // Index 4585
    "sns-gateway",  // Index 4586
    "sns-agent",  // Index 4587
    "mcntp",  // Index 4588
    "dj-ice",  // Index 4589
    "cylink-c",  // Index 4590
    "netsupport2",  // Index 4591
    "salient-mux",  // Index 4592
    "virtualuser",  // Index 4593
    "beyond-remote",  // Index 4594
    "br-channel",  // Index 4595
    "devbasic",  // Index 4596
    "sco-peer-tta",  // Index 4597
    "telaconsole",  // Index 4598
    "omid",  // Index 4599
    "base",  // Index 4600
    "radec-corp",  // Index 4601
    "park-agent",  // Index 4602
    "postgresql",  // Index 4603
    "pyrrho",  // Index 4604
    "sgi-arrayd",  // Index 4605
    "sceanics",  // Index 4606
    "pmip6-cntl",  // Index 4607
    "pmip6-data",  // Index 4608
    "spss",  // Index 4609
    "smbdirect",  // Index 4610
    "tiepie",  // Index 4611
    "surebox",  // Index 4612
    "apc-5454",  // Index 4613
    "apc-5455",  // Index 4614
    "apc-5456",  // Index 4615
    "silkmeter",  // Index 4616
    "ttl-publisher",  // Index 4617
    "ttlpriceproxy",  // Index 4618
    "quailnet",  // Index 4619
    "netops-broker",  // Index 4620
    "apsolab-col",  // Index 4621
    "apsolab-cols",  // Index 4622
    "apsolab-tag",  // Index 4623
    "apsolab-tags",  // Index 4624
    "apsolab-rpc",  // Index 4625
    "apsolab-data",  // Index 4626
    "connect-proxy",  // Index 4627
    "securid",  // Index 4628
    "fcp-addr-srvr2",  // Index 4629
    "fcp-srvr-inst1",  // Index 4630
    "fcp-srvr-inst2",  // Index 4631
    "fcp-cics-gw1",  // Index 4632
    "checkoutdb",  // Index 4633
    "amc",  // Index 4634
    "psl-management",  // Index 4635
    "secureidprop",  // Index 4636
    "sdlog",  // Index 4637
    "sdserv",  // Index 4638
    "sdreport",  // Index 4639
    "sdxauthd",  // Index 4640
    "sdadmind",  // Index 4641
    "sgi-eventmond",  // Index 4642
    "sgi-esphttp",  // Index 4643
    "freeciv",  // Index 4644
    "rplay",  // Index 4645
    "farenet",  // Index 4646
    "isqlplus",  // Index 4647
    "hpe-dp-bura",  // Index 4648
    "westec-connect",  // Index 4649
    "m-oap",  // Index 4650
    "sdt",  // Index 4651
    "rdmnet-ctrl",  // Index 4652
    "sdmmp",  // Index 4653
    "lsi-bobcat",  // Index 4654
    "ora-oap",  // Index 4655
    "fdtracks",  // Index 4656
    "tmosms0",  // Index 4657
    "tmosms1",  // Index 4658
    "fac-restore",  // Index 4659
    "tmo-icon-sync",  // Index 4660
    "bis-web",  // Index 4661
    "bis-sync",  // Index 4662
    "att-mt-sms",  // Index 4663
    "ininmessaging",  // Index 4664
    "mctfeed",  // Index 4665
    "esinstall",  // Index 4666
    "esmmanager",  // Index 4667
    "esmagent",  // Index 4668
    "a1-msc",  // Index 4669
    "a1-bs",  // Index 4670
    "a3-sdunode",  // Index 4671
    "a4-sdunode",  // Index 4672
    "efr",  // Index 4673
    "ninaf",  // Index 4674
    "htrust",  // Index 4675
    "symantec-sfdb",  // Index 4676
    "precise-comm",  // Index 4677
    "pcanywheredata",  // Index 4678
    "pcanywherestat",  // Index 4679
    "beorl",  // Index 4680
    "xprtld",  // Index 4681
    "sfmsso",  // Index 4682
    "sfm-db-server",  // Index 4683
    "cssc",  // Index 4684
    "flcrs",  // Index 4685
    "ics",  // Index 4686
    "vfmobile",  // Index 4687
    "nrpe",  // Index 4688
    "filemq",  // Index 4689
    "amqps",  // Index 4690
    "amqp",  // Index 4691
    "jms",  // Index 4692
    "hyperscsi-port",  // Index 4693
    "v5ua",  // Index 4694
    "raadmin",  // Index 4695
    "questdb2-lnchr",  // Index 4696
    "rrac",  // Index 4697
    "activesync",  // Index 4698
    "dccm",  // Index 4699
    "canna",  // Index 4700
    "auriga-router",  // Index 4701
    "ncxcp",  // Index 4702
    "brightcore",  // Index 4703
    "coap",  // Index 4704
    "coaps",  // Index 4705
    "gog-multiplayer",  // Index 4706
    "ggz",  // Index 4707
    "qmvideo",  // Index 4708
    "rbsystem",  // Index 4709
    "kmip",  // Index 4710
    "supportassist",  // Index 4711
    "storageos",  // Index 4712
    "proshareaudio",  // Index 4713
    "prosharevideo",  // Index 4714
    "prosharedata",  // Index 4715
    "prosharerequest",  // Index 4716
    "prosharenotify",  // Index 4717
    "dpm",  // Index 4718
    "dpm-agent",  // Index 4719
    "ms-licensing",  // Index 4720
    "dtpt",  // Index 4721
    "msdfsr",  // Index 4722
    "omhs",  // Index 4723
    "omsdk",  // Index 4724
    "ms-ilm",  // Index 4725
    "ms-ilm-sts",  // Index 4726
    "asgenf",  // Index 4727
    "io-dist-data",  // Index 4728
    "io-dist-group",  // Index 4729
    "openmail",  // Index 4730
    "unieng",  // Index 4731
    "ida-discover1",  // Index 4732
    "ida-discover2",  // Index 4733
    "watchdoc-pod",  // Index 4734
    "watchdoc",  // Index 4735
    "fcopy-server",  // Index 4736
    "fcopys-server",  // Index 4737
    "tunatic",  // Index 4738
    "tunalyzer",  // Index 4739
    "rscd",  // Index 4740
    "openmailg",  // Index 4741
    "x500ms",  // Index 4742
    "openmailns",  // Index 4743
    "s-openmail",  // Index 4744
    "openmailpxy",  // Index 4745
    "spramsca",  // Index 4746
    "spramsd",  // Index 4747
    "netagent",  // Index 4748
    "dali-port",  // Index 4749
    "vts-rpc",  // Index 4750
    "3par-evts",  // Index 4751
    "3par-mgmt",  // Index 4752
    "3par-mgmt-ssl",  // Index 4753
    "ibar",  // Index 4754
    "3par-rcopy",  // Index 4755
    "cisco-redu",  // Index 4756
    "waascluster",  // Index 4757
    "xtreamx",  // Index 4758
    "spdp",  // Index 4759
    "enlabel-dpl",  // Index 4760
    "vnc-http",  // Index 4761
    "vnc-http-1",  // Index 4762
    "vnc-http-2",  // Index 4763
    "vnc-http-3",  // Index 4764
    "icmpd",  // Index 4765
    "spt-automation",  // Index 4766
    "autopassdaemon",  // Index 4767
    "shiprush-d-ch",  // Index 4768
    "reversion",  // Index 4769
    "wherehoo",  // Index 4770
    "ppsuitemsg",  // Index 4771
    "diameters",  // Index 4772
    "jute",  // Index 4773
    "vnc",  // Index 4774
    "rfb",  // Index 4775
    "vnc-1",  // Index 4776
    "vnc-2",  // Index 4777
    "vnc-3",  // Index 4778
    "ag-swim",  // Index 4779
    "asmgcs",  // Index 4780
    "rpas-c2",  // Index 4781
    "dsd",  // Index 4782
    "ipsma",  // Index 4783
    "agma",  // Index 4784
    "cm",  // Index 4785
    "cpdlc",  // Index 4786
    "fis",  // Index 4787
    "ads-c",  // Index 4788
    "teamviewer",  // Index 4789
    "indy",  // Index 4790
    "mppolicy-v5",  // Index 4791
    "mppolicy-mgr",  // Index 4792
    "ncd-pref-tcp",  // Index 4793
    "ncd-diag-tcp",  // Index 4794
    "ncd-conf-tcp",  // Index 4795
    "couchdb",  // Index 4796
    "wsman",  // Index 4797
    "wsmans",  // Index 4798
    "wbem-rmi",  // Index 4799
    "wbem-http",  // Index 4800
    "wbem-https",  // Index 4801
    "wbem-exp-https",  // Index 4802
    "nuxsl",  // Index 4803
    "consul-insight",  // Index 4804
    "cim-rs",  // Index 4805
    "rms-agent",  // Index 4806
    "ncd-pref",  // Index 4807
    "ncd-diag",  // Index 4808
    "ncd-conf",  // Index 4809
    "cvsup",  // Index 4810
    "X11",  // Index 4811
    "X11:1",  // Index 4812
    "X11:2",  // Index 4813
    "X11:3",  // Index 4814
    "X11:4",  // Index 4815
    "X11:5",  // Index 4816
    "X11:6",  // Index 4817
    "X11:7",  // Index 4818
    "X11:8",  // Index 4819
    "X11:9",  // Index 4820
    "x11",  // Index 4821
    "xmail-ctrl",  // Index 4822
    "arcserve",  // Index 4823
    "X11:59",  // Index 4824
    "ndl-ahp-svc",  // Index 4825
    "winpharaoh",  // Index 4826
    "ewctsp",  // Index 4827
    "gsmp",  // Index 4828
    "trip",  // Index 4829
    "messageasap",  // Index 4830
    "ssdtp",  // Index 4831
    "diagnose-proc",  // Index 4832
    "directplay8",  // Index 4833
    "max",  // Index 4834
    "dpm-acm",  // Index 4835
    "msft-dpm-cert",  // Index 4836
    "iconstructsrv",  // Index 4837
    "gue",  // Index 4838
    "geneve",  // Index 4839
    "p25cai",  // Index 4840
    "miami-bcast",  // Index 4841
    "p2p-sip",  // Index 4842
    "konspire2b",  // Index 4843
    "pdtp",  // Index 4844
    "ldss",  // Index 4845
    "doglms",  // Index 4846
    "raxa-mgmt",  // Index 4847
    "synchronet-db",  // Index 4848
    "backupexec",  // Index 4849
    "synchronet-rtc",  // Index 4850
    "synchronet-upd",  // Index 4851
    "RETS-or-BackupExec",  // Index 4852
    "rets",  // Index 4853
    "dbdb",  // Index 4854
    "isdninfo",  // Index 4855
    "primaserver",  // Index 4856
    "mpsserver",  // Index 4857
    "etc-control",  // Index 4858
    "sercomm-scadmin",  // Index 4859
    "globecast-id",  // Index 4860
    "softcm",  // Index 4861
    "spc",  // Index 4862
    "dtspc",  // Index 4863
    "dtspcd",  // Index 4864
    "dayliteserver",  // Index 4865
    "wrspice",  // Index 4866
    "xic",  // Index 4867
    "xtlserv",  // Index 4868
    "daylitetouch",  // Index 4869
    "tipc",  // Index 4870
    "spdy",  // Index 4871
    "bex-webadmin",  // Index 4872
    "backup-express",  // Index 4873
    "pnbs",  // Index 4874
    "damewaremobgtwy",  // Index 4875
    "nbt-wol",  // Index 4876
    "pulsonixnls",  // Index 4877
    "meta-corp",  // Index 4878
    "aspentec-lm",  // Index 4879
    "watershed-lm",  // Index 4880
    "statsci1-lm",  // Index 4881
    "statsci2-lm",  // Index 4882
    "lonewolf-lm",  // Index 4883
    "montage-lm",  // Index 4884
    "ricardo-lm",  // Index 4885
    "tal-pod",  // Index 4886
    "efb-aci",  // Index 4887
    "ecmp",  // Index 4888
    "patrol-ism",  // Index 4889
    "patrol-coll",  // Index 4890
    "pscribe",  // Index 4891
    "lm-x",  // Index 4892
    "thermo-calc",  // Index 4893
    "qmtps",  // Index 4894
    "radmind",  // Index 4895
    "jeol-nsdtp-1",  // Index 4896
    "jeol-nsddp-1",  // Index 4897
    "jeol-nsdtp-2",  // Index 4898
    "jeol-nsddp-2",  // Index 4899
    "jeol-nsdtp-3",  // Index 4900
    "jeol-nsddp-3",  // Index 4901
    "jeol-nsdtp-4",  // Index 4902
    "jeol-nsddp-4",  // Index 4903
    "tl1-raw-ssl",  // Index 4904
    "tl1-ssh",  // Index 4905
    "crip",  // Index 4906
    "gld",  // Index 4907
    "grid",  // Index 4908
    "grid-alt",  // Index 4909
    "bmc-grx",  // Index 4910
    "bmc_ctd_ldap",  // Index 4911
    "ufmp",  // Index 4912
    "scup",  // Index 4913
    "scup-disc",  // Index 4914
    "abb-escp",  // Index 4915
    "nav-data-cmd",  // Index 4916
    "repsvc",  // Index 4917
    "emp-server1",  // Index 4918
    "emp-server2",  // Index 4919
    "hrd-ncs",  // Index 4920
    "dt-mgmtsvc",  // Index 4921
    "dt-vra",  // Index 4922
    "sflow",  // Index 4923
    "streletz",  // Index 4924
    "gnutella",  // Index 4925
    "gnutella2",  // Index 4926
    "adap",  // Index 4927
    "pmcs",  // Index 4928
    "metaedit-mu",  // Index 4929
    "ndn",  // Index 4930
    "metaedit-se",  // Index 4931
    "redis",  // Index 4932
    "metatude-mds",  // Index 4933
    "clariion-evr01",  // Index 4934
    "metaedit-ws",  // Index 4935
    "crystalreports",  // Index 4936
    "boe-cms",  // Index 4937
    "crystalenterprise",  // Index 4938
    "boe-was",  // Index 4939
    "boe-eventsrv",  // Index 4940
    "boe-cachesvr",  // Index 4941
    "boe-filesvr",  // Index 4942
    "boe-pagesvr",  // Index 4943
    "boe-processsvr",  // Index 4944
    "boe-resssvr1",  // Index 4945
    "boe-resssvr2",  // Index 4946
    "boe-resssvr3",  // Index 4947
    "boe-resssvr4",  // Index 4948
    "faxcomservice",  // Index 4949
    "syserverremote",  // Index 4950
    "svdrp",  // Index 4951
    "nim-vdrshell",  // Index 4952
    "nim-wan",  // Index 4953
    "pgbouncer",  // Index 4954
    "heliosd",  // Index 4955
    "tarp",  // Index 4956
    "sun-sr-https",  // Index 4957
    "sge_qmaster",  // Index 4958
    "sge_execd",  // Index 4959
    "mysql-proxy",  // Index 4960
    "skip-cert-recv",  // Index 4961
    "skip-cert-send",  // Index 4962
    "ieee11073-20701",  // Index 4963
    "lvision-lm",  // Index 4964
    "sun-sr-http",  // Index 4965
    "servicetags",  // Index 4966
    "ldoms-mgmt",  // Index 4967
    "SunVTS-RMI",  // Index 4968
    "sun-sr-jms",  // Index 4969
    "sun-sr-iiop",  // Index 4970
    "sun-sr-iiops",  // Index 4971
    "sun-sr-iiop-aut",  // Index 4972
    "sun-sr-jmx",  // Index 4973
    "sun-sr-admin",  // Index 4974
    "boks",  // Index 4975
    "boks_servc",  // Index 4976
    "boks_clntd",  // Index 4977
    "badm_priv",  // Index 4978
    "badm_pub",  // Index 4979
    "bdir_priv",  // Index 4980
    "bdir_pub",  // Index 4981
    "mgcs-mfp-port",  // Index 4982
    "mcer-port",  // Index 4983
    "dccp-udp",  // Index 4984
    "netconf-tls",  // Index 4985
    "syslog-tls",  // Index 4986
    "elipse-rec",  // Index 4987
    "mythtv",  // Index 4988
    "lds-distrib",  // Index 4989
    "lds-dump",  // Index 4990
    "powerchuteplus",  // Index 4991
    "apc-6547",  // Index 4992
    "apc-6548",  // Index 4993
    "apc-6549",  // Index 4994
    "fg-sysupdate",  // Index 4995
    "sum",  // Index 4996
    "checkmk-agent",  // Index 4997
    "xdsxdm",  // Index 4998
    "sane-port",  // Index 4999
    "esp",  // Index 5000
    "canit_store",  // Index 5001
    "rp-reputation",  // Index 5002
    "affiliate",  // Index 5003
    "parsec-master",  // Index 5004
    "parsec-peer",  // Index 5005
    "parsec-game",  // Index 5006
    "joaJewelSuite",  // Index 5007
    "analogx",  // Index 5008
    "mshvlm",  // Index 5009
    "mstmg-sstp",  // Index 5010
    "wsscomfrmwk",  // Index 5011
    "odette-ftps",  // Index 5012
    "kftp-data",  // Index 5013
    "kftp",  // Index 5014
    "mcftp",  // Index 5015
    "ktelnet",  // Index 5016
    "datascaler-db",  // Index 5017
    "datascaler-ctl",  // Index 5018
    "wago-service",  // Index 5019
    "nexgen",  // Index 5020
    "afesc-mc",  // Index 5021
    "nexgen-aux",  // Index 5022
    "mxodbc-connect",  // Index 5023
    "cisco-vpath-tun",  // Index 5024
    "mpls-pm",  // Index 5025
    "mpls-udp",  // Index 5026
    "mpls-udp-dtls",  // Index 5027
    "ovsdb",  // Index 5028
    "openflow",  // Index 5029
    "pcs-sf-ui-man",  // Index 5030
    "emgmsg",  // Index 5031
    "palcom-disc",  // Index 5032
    "ircu",  // Index 5033
    "vocaltec-gold",  // Index 5034
    "p4p-portal",  // Index 5035
    "vision_server",  // Index 5036
    "vision_elmd",  // Index 5037
    "vfbp",  // Index 5038
    "osaut",  // Index 5039
    "clever-ctrace",  // Index 5040
    "clever-tcpip",  // Index 5041
    "tsa",  // Index 5042
    "cleverdetect",  // Index 5043
    "babel",  // Index 5044
    "ircs-u",  // Index 5045
    "napster",  // Index 5046
    "carracho",  // Index 5047
    "kti-icad-srvr",  // Index 5048
    "e-design-net",  // Index 5049
    "e-design-web",  // Index 5050
    "frc-hp",  // Index 5051
    "frc-mp",  // Index 5052
    "frc-lp",  // Index 5053
    "ibprotocol",  // Index 5054
    "fibotrader-com",  // Index 5055
    "princity-agent",  // Index 5056
    "bmc-perf-agent",  // Index 5057
    "bmc-perf-mgrd",  // Index 5058
    "adi-gxp-srvprt",  // Index 5059
    "plysrv-http",  // Index 5060
    "plysrv-https",  // Index 5061
    "ntz-tracker",  // Index 5062
    "ntz-p2p-storage",  // Index 5063
    "bfd-lag",  // Index 5064
    "dgpf-exchg",  // Index 5065
    "smc-jmx",  // Index 5066
    "smc-admin",  // Index 5067
    "smc-http",  // Index 5068
    "ibm-db2-admin",  // Index 5069
    "smc-https",  // Index 5070
    "hnmp",  // Index 5071
    "hnm",  // Index 5072
    "acnet",  // Index 5073
    "pentbox-sim",  // Index 5074
    "ambit-lm",  // Index 5075
    "netmo-default",  // Index 5076
    "netmo-http",  // Index 5077
    "iccrushmore",  // Index 5078
    "acctopus-cc",  // Index 5079
    "acctopus-st",  // Index 5080
    "bittorrent-tracker",  // Index 5081
    "muse",  // Index 5082
    "rtimeviewer",  // Index 5083
    "jetstream",  // Index 5084
    "split-ping",  // Index 5085
    "ethoscan",  // Index 5086
    "xsmsvc",  // Index 5087
    "bioserver",  // Index 5088
    "otlp",  // Index 5089
    "jmact3",  // Index 5090
    "jmevt2",  // Index 5091
    "swismgr1",  // Index 5092
    "swismgr2",  // Index 5093
    "swistrap",  // Index 5094
    "swispol",  // Index 5095
    "acmsoda",  // Index 5096
    "conductor",  // Index 5097
    "qolyester",  // Index 5098
    "MobilitySrv",  // Index 5099
    "iatp-highpri",  // Index 5100
    "iatp-normalpri",  // Index 5101
    "afs3-fileserver",  // Index 5102
    "afs3-callback",  // Index 5103
    "afs3-prserver",  // Index 5104
    "afs3-vlserver",  // Index 5105
    "afs3-kaserver",  // Index 5106
    "afs3-volser",  // Index 5107
    "afs3-errors",  // Index 5108
    "afs3-bos",  // Index 5109
    "afs3-update",  // Index 5110
    "afs3-rmtsys",  // Index 5111
    "ups-onlinet",  // Index 5112
    "talon-disc",  // Index 5113
    "talon-engine",  // Index 5114
    "microtalon-dis",  // Index 5115
    "microtalon-com",  // Index 5116
    "talon-webserver",  // Index 5117
    "spg",  // Index 5118
    "grasp",  // Index 5119
    "fisa-svc",  // Index 5120
    "doceri-ctl",  // Index 5121
    "dpserve",  // Index 5122
    "dpserveadmin",  // Index 5123
    "ctdp",  // Index 5124
    "ct2nmcs",  // Index 5125
    "vmsvc",  // Index 5126
    "vmsvc-2",  // Index 5127
    "loreji-panel",  // Index 5128
    "op-probe",  // Index 5129
    "iposplanet",  // Index 5130
    "quest-disc",  // Index 5131
    "realserver",  // Index 5132
    "arcp",  // Index 5133
    "iwg1",  // Index 5134
    "iba-cfg",  // Index 5135
    "martalk",  // Index 5136
    "empowerid",  // Index 5137
    "zixi-transport",  // Index 5138
    "jdp-disc",  // Index 5139
    "lazy-ptop",  // Index 5140
    "font-service",  // Index 5141
    "elcn",  // Index 5142
    "aes-x170",  // Index 5143
    "rothaga",  // Index 5144
    "virprot-lm",  // Index 5145
    "snif",  // Index 5146
    "scenidm",  // Index 5147
    "scenccs",  // Index 5148
    "cabsm-comm",  // Index 5149
    "caistoragemgr",  // Index 5150
    "cacsambroker",  // Index 5151
    "fsr",  // Index 5152
    "doc-server",  // Index 5153
    "aruba-server",  // Index 5154
    "casrmagent",  // Index 5155
    "cnckadserver",  // Index 5156
    "ccag-pib",  // Index 5157
    "nsrp",  // Index 5158
    "drm-production",  // Index 5159
    "metalbend",  // Index 5160
    "zsecure",  // Index 5161
    "clutild",  // Index 5162
    "janus-disc",  // Index 5163
    "fodms",  // Index 5164
    "dlip",  // Index 5165
    "pon-ictp",  // Index 5166
    "PS-Server",  // Index 5167
    "PS-Capture-Pro",  // Index 5168
    "ramp",  // Index 5169
    "citrixupp",  // Index 5170
    "citrixuppg",  // Index 5171
    "asa-gateways",  // Index 5172
    "aspcoordination",  // Index 5173
    "display",  // Index 5174
    "pads",  // Index 5175
    "frc-hicp",  // Index 5176
    "cnap",  // Index 5177
    "watchme-7272",  // Index 5178
    "openmanage",  // Index 5179
    "oma-rlp",  // Index 5180
    "oma-rlp-s",  // Index 5181
    "oma-ulp",  // Index 5182
    "oma-ilp",  // Index 5183
    "oma-ilp-s",  // Index 5184
    "oma-dcdocbs",  // Index 5185
    "ctxlic",  // Index 5186
    "itactionserver1",  // Index 5187
    "itactionserver2",  // Index 5188
    "mzca-action",  // Index 5189
    "mzca-alert",  // Index 5190
    "genstat",  // Index 5191
    "swx",  // Index 5192
    "icb",  // Index 5193
    "lcm-server",  // Index 5194
    "mindfilesys",  // Index 5195
    "mrssrendezvous",  // Index 5196
    "nfoldman",  // Index 5197
    "fse",  // Index 5198
    "winqedit",  // Index 5199
    "hexarc",  // Index 5200
    "rtps-discovery",  // Index 5201
    "rtps-dd-ut",  // Index 5202
    "rtps-dd-mt",  // Index 5203
    "ionixnetmon",  // Index 5204
    "daqstream",  // Index 5205
    "ipluminary",  // Index 5206
    "mtportmon",  // Index 5207
    "pmdmgr",  // Index 5208
    "oveadmgr",  // Index 5209
    "ovladmgr",  // Index 5210
    "opi-sock",  // Index 5211
    "xmpv7",  // Index 5212
    "pmd",  // Index 5213
    "faximum",  // Index 5214
    "oracleas-https",  // Index 5215
    "pythonds",  // Index 5216
    "sttunnel",  // Index 5217
    "rise",  // Index 5218
    "neo4j",  // Index 5219
    "openit",  // Index 5220
    "telops-lmd",  // Index 5221
    "silhouette",  // Index 5222
    "ovbus",  // Index 5223
    "adcp",  // Index 5224
    "acplt",  // Index 5225
    "ovhpas",  // Index 5226
    "pafec-lm",  // Index 5227
    "saratoga",  // Index 5228
    "atul",  // Index 5229
    "nta-ds",  // Index 5230
    "nta-us",  // Index 5231
    "cwmp",  // Index 5232
    "tidp",  // Index 5233
    "nls-tl",  // Index 5234
    "cloudsignaling",  // Index 5235
    "controlone-con",  // Index 5236
    "sncp",  // Index 5237
    "cfw",  // Index 5238
    "vsi-omega",  // Index 5239
    "dell-eql-asm",  // Index 5240
    "aries-kfinder",  // Index 5241
    "coherence",  // Index 5242
    "sun-lm",  // Index 5243
    "qaz",  // Index 5244
    "mipi-debug",  // Index 5245
    "indi",  // Index 5246
    "simco",  // Index 5247
    "soap-http",  // Index 5248
    "zen-pawn",  // Index 5249
    "xdas",  // Index 5250
    "hawk",  // Index 5251
    "tesla-sys-msg",  // Index 5252
    "pmdfmgt",  // Index 5253
    "hddtemp",  // Index 5254
    "cuseeme",  // Index 5255
    "cucme-1",  // Index 5256
    "cucme-2",  // Index 5257
    "cucme-3",  // Index 5258
    "cucme-4",  // Index 5259
    "rome",  // Index 5260
    "imqstomp",  // Index 5261
    "imqstomps",  // Index 5262
    "imqtunnels",  // Index 5263
    "imqtunnel",  // Index 5264
    "imqbrokerd",  // Index 5265
    "sun-user-https",  // Index 5266
    "pando-pub",  // Index 5267
    "dmt",  // Index 5268
    "bolt",  // Index 5269
    "collaber",  // Index 5270
    "sovd",  // Index 5271
    "klio",  // Index 5272
    "em7-secom",  // Index 5273
    "nfapi",  // Index 5274
    "sync-em7",  // Index 5275
    "scinet",  // Index 5276
    "medimageportal",  // Index 5277
    "nsdeepfreezectl",  // Index 5278
    "nitrogen",  // Index 5279
    "freezexservice",  // Index 5280
    "trident-data",  // Index 5281
    "osvr",  // Index 5282
    "smip",  // Index 5283
    "aiagent",  // Index 5284
    "scriptview",  // Index 5285
    "msss",  // Index 5286
    "sstp-1",  // Index 5287
    "raqmon-pdu",  // Index 5288
    "prgp",  // Index 5289
    "inetfs",  // Index 5290
    "cbt",  // Index 5291
    "interwise",  // Index 5292
    "vstat",  // Index 5293
    "accu-lmgr",  // Index 5294
    "s-bfd",  // Index 5295
    "minivend",  // Index 5296
    "popup-reminders",  // Index 5297
    "office-tools",  // Index 5298
    "q3ade",  // Index 5299
    "pnet-conn",  // Index 5300
    "pnet-enc",  // Index 5301
    "altbsdp",  // Index 5302
    "asr",  // Index 5303
    "ssp-client",  // Index 5304
    "vns-tp",  // Index 5305
    "rbt-wanopt",  // Index 5306
    "apc-7845",  // Index 5307
    "apc-7846",  // Index 5308
    "csoauth",  // Index 5309
    "mobileanalyzer",  // Index 5310
    "rbt-smc",  // Index 5311
    "mdm",  // Index 5312
    "mipv6tls",  // Index 5313
    "owms",  // Index 5314
    "pss",  // Index 5315
    "ubroker",  // Index 5316
    "mevent",  // Index 5317
    "tnos-sp",  // Index 5318
    "tnos-dp",  // Index 5319
    "tnos-dps",  // Index 5320
    "qo-secure",  // Index 5321
    "t2-drm",  // Index 5322
    "t2-brm",  // Index 5323
    "nsrexecd",  // Index 5324
    "lgtomapper",  // Index 5325
    "generalsync",  // Index 5326
    "supercell",  // Index 5327
    "micromuse-ncps",  // Index 5328
    "quest-vista",  // Index 5329
    "sossd-collect",  // Index 5330
    "sossd-agent",  // Index 5331
    "sossd-disc",  // Index 5332
    "pushns",  // Index 5333
    "usicontentpush",  // Index 5334
    "irdmi2",  // Index 5335
    "irdmi",  // Index 5336
    "vcom-tunnel",  // Index 5337
    "teradataordbms",  // Index 5338
    "mcreport",  // Index 5339
    "p2pevolvenet",  // Index 5340
    "mxi",  // Index 5341
    "wpl-analytics",  // Index 5342
    "ajp12",  // Index 5343
    "ajp13",  // Index 5344
    "xmpp",  // Index 5345
    "cfg-cloud",  // Index 5346
    "ads-s",  // Index 5347
    "cisco-cloudsec",  // Index 5348
    "qbdb",  // Index 5349
    "intu-ec-svcdisc",  // Index 5350
    "ftp-proxy",  // Index 5351
    "intu-ec-client",  // Index 5352
    "oa-system",  // Index 5353
    "arca-api",  // Index 5354
    "ca-audit-da",  // Index 5355
    "ca-audit-ds",  // Index 5356
    "papachi-p2p-srv",  // Index 5357
    "pro-ed",  // Index 5358
    "mindprint",  // Index 5359
    "vantronix-mgmt",  // Index 5360
    "ampify",  // Index 5361
    "enguity-xccetp",  // Index 5362
    "fs-agent",  // Index 5363
    "fs-server",  // Index 5364
    "fs-mgmt",  // Index 5365
    "rocrail",  // Index 5366
    "senomix01",  // Index 5367
    "senomix02",  // Index 5368
    "senomix03",  // Index 5369
    "senomix04",  // Index 5370
    "senomix05",  // Index 5371
    "senomix06",  // Index 5372
    "senomix07",  // Index 5373
    "senomix08",  // Index 5374
    "aero",  // Index 5375
    "toad-bi-appsrvr",  // Index 5376
    "infi-async",  // Index 5377
    "ucs-isc",  // Index 5378
    "gadugadu",  // Index 5379
    "mles",  // Index 5380
    "http-proxy",  // Index 5381
    "blackice-icecap",  // Index 5382
    "sunproxyadmin",  // Index 5383
    "blackice-alerts",  // Index 5384
    "us-cli",  // Index 5385
    "us-srv",  // Index 5386
    "websnp",  // Index 5387
    "d-s-n",  // Index 5388
    "simplifymedia",  // Index 5389
    "radan-http",  // Index 5390
    "opsmessaging",  // Index 5391
    "jamlink",  // Index 5392
    "sac",  // Index 5393
    "xprint-server",  // Index 5394
    "ldoms-migr",  // Index 5395
    "kz-migr",  // Index 5396
    "skynetflow",  // Index 5397
    "mtl8000-matrix",  // Index 5398
    "cp-cluster",  // Index 5399
    "purityrpc",  // Index 5400
    "privoxy",  // Index 5401
    "apollo-data",  // Index 5402
    "apollo-admin",  // Index 5403
    "polipo",  // Index 5404
    "paycash-online",  // Index 5405
    "paycash-wbp",  // Index 5406
    "indigo-vrmi",  // Index 5407
    "indigo-vbcp",  // Index 5408
    "dbabble",  // Index 5409
    "puppet",  // Index 5410
    "isdd",  // Index 5411
    "eor-game",  // Index 5412
    "quantastor",  // Index 5413
    "patrol",  // Index 5414
    "patrol-snmp",  // Index 5415
    "lpar2rrd",  // Index 5416
    "intermapper",  // Index 5417
    "vmware-fdm",  // Index 5418
    "proremote",  // Index 5419
    "itach",  // Index 5420
    "gcp-rphy",  // Index 5421
    "limnerpressure",  // Index 5422
    "sophos",  // Index 5423
    "blp2",  // Index 5424
    "vvr-data",  // Index 5425
    "trivnet1",  // Index 5426
    "trivnet2",  // Index 5427
    "aesop",  // Index 5428
    "lm-perfworks",  // Index 5429
    "lm-instmgr",  // Index 5430
    "lm-dta",  // Index 5431
    "lm-sserver",  // Index 5432
    "lm-webwatcher",  // Index 5433
    "aruba-papi",  // Index 5434
    "rexecj",  // Index 5435
    "hncp-udp-port",  // Index 5436
    "hncp-dtls-port",  // Index 5437
    "synapse-nhttps",  // Index 5438
    "espeasy-p2p",  // Index 5439
    "robot-remote",  // Index 5440
    "pando-sec",  // Index 5441
    "synapse-nhttp",  // Index 5442
    "libelle",  // Index 5443
    "blp3",  // Index 5444
    "hiperscan-id",  // Index 5445
    "blp4",  // Index 5446
    "tmi",  // Index 5447
    "amberon",  // Index 5448
    "hub-open-net",  // Index 5449
    "tnp-discover",  // Index 5450
    "tnp",  // Index 5451
    "garmin-marine",  // Index 5452
    "bitcoin",  // Index 5453
    "server-find",  // Index 5454
    "cruise-enum",  // Index 5455
    "cruise-swroute",  // Index 5456
    "cruise-config",  // Index 5457
    "cruise-diags",  // Index 5458
    "cruise-update",  // Index 5459
    "m2mservices",  // Index 5460
    "marathontp",  // Index 5461
    "cvd",  // Index 5462
    "sabarsd",  // Index 5463
    "abarsd",  // Index 5464
    "svcloud",  // Index 5465
    "svbackup",  // Index 5466
    "dlpx-sp",  // Index 5467
    "espeech",  // Index 5468
    "espeech-rtp",  // Index 5469
    "aritts",  // Index 5470
    "pgbackrest",  // Index 5471
    "cybro-a-bus",  // Index 5472
    "https-alt",  // Index 5473
    "pcsync-https",  // Index 5474
    "pcsync-http",  // Index 5475
    "copy",  // Index 5476
    "npmp",  // Index 5477
    "nexentamv",  // Index 5478
    "cisco-avp",  // Index 5479
    "pim-port",  // Index 5480
    "otv",  // Index 5481
    "vp2p",  // Index 5482
    "noteshare",  // Index 5483
    "fmtp",  // Index 5484
    "cmtp-mgt",  // Index 5485
    "ftnmtp",  // Index 5486
    "lsp-self-ping",  // Index 5487
    "rtsp-alt",  // Index 5488
    "d-fence",  // Index 5489
    "oap-admin",  // Index 5490
    "asterix",  // Index 5491
    "canon-cpp-disc",  // Index 5492
    "canon-mfnp",  // Index 5493
    "canon-bjnp1",  // Index 5494
    "canon-bjnp2",  // Index 5495
    "canon-bjnp3",  // Index 5496
    "canon-bjnp4",  // Index 5497
    "imink",  // Index 5498
    "monetra",  // Index 5499
    "monetra-admin",  // Index 5500
    "msi-cps-rm",  // Index 5501
    "sun-as-jmxrmi",  // Index 5502
    "openremote-ctrl",  // Index 5503
    "vnyx",  // Index 5504
    "semi-grpc",  // Index 5505
    "nvc",  // Index 5506
    "dtp-net",  // Index 5507
    "ibus",  // Index 5508
    "dey-keyneg",  // Index 5509
    "mc-appserver",  // Index 5510
    "openqueue",  // Index 5511
    "ultraseek-http",  // Index 5512
    "amcs",  // Index 5513
    "core-of-source",  // Index 5514
    "sandpolis",  // Index 5515
    "oktaauthenticat",  // Index 5516
    "apple-iphoto",  // Index 5517
    "dpap",  // Index 5518
    "uec",  // Index 5519
    "msgclnt",  // Index 5520
    "msgsrvr",  // Index 5521
    "sunwebadmin",  // Index 5522
    "truecm",  // Index 5523
    "pfcp",  // Index 5524
    "hes-clip",  // Index 5525
    "ssports-bcast",  // Index 5526
    "3gpp-monp",  // Index 5527
    "nessus-xmlrpc",  // Index 5528
    "dxspider",  // Index 5529
    "cddbp-alt",  // Index 5530
    "galaxy4d",  // Index 5531
    "secure-mqtt",  // Index 5532
    "sun-answerbook",  // Index 5533
    "ddi-udp-1",  // Index 5534
    "ddi-tcp-2",  // Index 5535
    "ddi-udp-2",  // Index 5536
    "ddi-tcp-3",  // Index 5537
    "ddi-udp-3",  // Index 5538
    "ddi-tcp-4",  // Index 5539
    "ddi-udp-4",  // Index 5540
    "seosload",  // Index 5541
    "ddi-udp-5",  // Index 5542
    "ddi-tcp-6",  // Index 5543
    "ddi-udp-6",  // Index 5544
    "ddi-tcp-7",  // Index 5545
    "ddi-udp-7",  // Index 5546
    "ospf-lite",  // Index 5547
    "jmb-cds1",  // Index 5548
    "jmb-cds2",  // Index 5549
    "dpp",  // Index 5550
    "manyone-http",  // Index 5551
    "manyone-xml",  // Index 5552
    "wcbackup",  // Index 5553
    "dragonfly",  // Index 5554
    "twds",  // Index 5555
    "ub-dns-control",  // Index 5556
    "cumulus-admin",  // Index 5557
    "nod-provider",  // Index 5558
    "nod-client",  // Index 5559
    "sunwebadmins",  // Index 5560
    "http-wmap",  // Index 5561
    "https-wmap",  // Index 5562
    "oracle-ms-ens",  // Index 5563
    "canto-roboflow",  // Index 5564
    "bctp",  // Index 5565
    "cslistener",  // Index 5566
    "tor-orport",  // Index 5567
    "etlservicemgr",  // Index 5568
    "dynamid",  // Index 5569
    "golem",  // Index 5570
    "ogs-client",  // Index 5571
    "ogs-server",  // Index 5572
    "pichat",  // Index 5573
    "sdr",  // Index 5574
    "d-star",  // Index 5575
    "tambora",  // Index 5576
    "panagolin-ident",  // Index 5577
    "paragent",  // Index 5578
    "swa-1",  // Index 5579
    "swa-2",  // Index 5580
    "swa-3",  // Index 5581
    "swa-4",  // Index 5582
    "tor-trans",  // Index 5583
    "tor-socks",  // Index 5584
    "tor-control",  // Index 5585
    "CardWeb-IO",  // Index 5586
    "glrpc",  // Index 5587
    "cisco-aqos",  // Index 5588
    "lcs-ap",  // Index 5589
    "emc-pp-mgmtsvc",  // Index 5590
    "aurora",  // Index 5591
    "ibm-rsyscon",  // Index 5592
    "net2display",  // Index 5593
    "classic",  // Index 5594
    "sqlexec",  // Index 5595
    "sqlexec-ssl",  // Index 5596
    "zeus-admin",  // Index 5597
    "websm",  // Index 5598
    "xmltec-xmlmail",  // Index 5599
    "XmlIpcRegSvc",  // Index 5600
    "copycat",  // Index 5601
    "jetdirect",  // Index 5602
    "hp-pdl-datastr",  // Index 5603
    "bacula-dir",  // Index 5604
    "bacula-fd",  // Index 5605
    "bacula-sd",  // Index 5606
    "peerwire",  // Index 5607
    "xadmin",  // Index 5608
    "astergate-disc",  // Index 5609
    "DragonIDSConsole",  // Index 5610
    "mxit",  // Index 5611
    "grcmp",  // Index 5612
    "grcp",  // Index 5613
    "dddp",  // Index 5614
    "ms-sql2000",  // Index 5615
    "apani1",  // Index 5616
    "apani2",  // Index 5617
    "apani3",  // Index 5618
    "apani4",  // Index 5619
    "apani5",  // Index 5620
    "sun-as-jpda",  // Index 5621
    "wap-wsp",  // Index 5622
    "wap-wsp-wtp",  // Index 5623
    "wap-wsp-s",  // Index 5624
    "wap-wsp-wtp-s",  // Index 5625
    "wap-vcard",  // Index 5626
    "wap-vcal",  // Index 5627
    "wap-vcard-s",  // Index 5628
    "wap-vcal-s",  // Index 5629
    "rjcdb-vcards",  // Index 5630
    "almobile-system",  // Index 5631
    "oma-mlp",  // Index 5632
    "oma-mlp-s",  // Index 5633
    "serverviewdbms",  // Index 5634
    "serverstart",  // Index 5635
    "ipdcesgbs",  // Index 5636
    "insis",  // Index 5637
    "acme",  // Index 5638
    "fsc-port",  // Index 5639
    "teamcoherence",  // Index 5640
    "traingpsdata",  // Index 5641
    "pegasus",  // Index 5642
    "pegasus-ctl",  // Index 5643
    "pgps",  // Index 5644
    "swtp-port1",  // Index 5645
    "swtp-port2",  // Index 5646
    "callwaveiam",  // Index 5647
    "visd",  // Index 5648
    "n2h2server",  // Index 5649
    "n2receive",  // Index 5650
    "cumulus",  // Index 5651
    "armtechdaemon",  // Index 5652
    "storview",  // Index 5653
    "armcenterhttp",  // Index 5654
    "armcenterhttps",  // Index 5655
    "vrace",  // Index 5656
    "sphinxql",  // Index 5657
    "sapms",  // Index 5658
    "sphinxapi",  // Index 5659
    "secure-ts",  // Index 5660
    "guibase",  // Index 5661
    "litecoin",  // Index 5662
    "gnmi-gnoi",  // Index 5663
    "gribi",  // Index 5664
    "mpidcmgr",  // Index 5665
    "mphlpdmc",  // Index 5666
    "rancher",  // Index 5667
    "ctechlicensing",  // Index 5668
    "fjdmimgr",  // Index 5669
    "boxp",  // Index 5670
    "d2dconfig",  // Index 5671
    "d2ddatatrans",  // Index 5672
    "adws",  // Index 5673
    "otp",  // Index 5674
    "fjinvmgr",  // Index 5675
    "mpidcagt",  // Index 5676
    "sec-t4net-srv",  // Index 5677
    "sec-t4net-clt",  // Index 5678
    "sec-pc2fax-srv",  // Index 5679
    "git",  // Index 5680
    "tungsten-https",  // Index 5681
    "wso2esb-console",  // Index 5682
    "mindarray-ca",  // Index 5683
    "sntlkeyssrvr",  // Index 5684
    "ismserver",  // Index 5685
    "sma-spw",  // Index 5686
    "man",  // Index 5687
    "laes-bf",  // Index 5688
    "trispen-sra",  // Index 5689
    "p4runtime",  // Index 5690
    "ldgateway",  // Index 5691
    "cba8",  // Index 5692
    "msgsys",  // Index 5693
    "pds",  // Index 5694
    "mercury-disc",  // Index 5695
    "pd-admin",  // Index 5696
    "vscp",  // Index 5697
    "robix",  // Index 5698
    "micromuse-ncpw",  // Index 5699
    "streamcomm-ds",  // Index 5700
    "iadt-tls",  // Index 5701
    "erunbook_agent",  // Index 5702
    "erunbook_server",  // Index 5703
    "condor",  // Index 5704
    "odbcpathway",  // Index 5705
    "uniport",  // Index 5706
    "peoctlr",  // Index 5707
    "peocoll",  // Index 5708
    "mc-comm",  // Index 5709
    "pqsflows",  // Index 5710
    "zoomcp",  // Index 5711
    "xmms2",  // Index 5712
    "tec5-sdctp",  // Index 5713
    "client-wakeup",  // Index 5714
    "ccnx",  // Index 5715
    "board-roar",  // Index 5716
    "l5nas-parchan",  // Index 5717
    "board-voip",  // Index 5718
    "rasadv",  // Index 5719
    "tungsten-http",  // Index 5720
    "davsrc",  // Index 5721
    "sstp-2",  // Index 5722
    "davsrcs",  // Index 5723
    "sapv1",  // Index 5724
    "sd",  // Index 5725
    "x510",  // Index 5726
    "kca-service",  // Index 5727
    "cyborg-systems",  // Index 5728
    "gt-proxy",  // Index 5729
    "monkeycom",  // Index 5730
    "sctp-tunneling",  // Index 5731
    "iua",  // Index 5732
    "enrp-sctp",  // Index 5733
    "enrp",  // Index 5734
    "enrp-sctp-tls",  // Index 5735
    "multicast-ping",  // Index 5736
    "domaintime",  // Index 5737
    "sype-transport",  // Index 5738
    "xybrid-cloud",  // Index 5739
    "nping-echo",  // Index 5740
    "apc-9950",  // Index 5741
    "apc-9951",  // Index 5742
    "apc-9952",  // Index 5743
    "acis",  // Index 5744
    "hinp",  // Index 5745
    "alljoyn-stm",  // Index 5746
    "alljoyn",  // Index 5747
    "odnsp",  // Index 5748
    "xybrid-rt",  // Index 5749
    "visweather",  // Index 5750
    "pumpkindb",  // Index 5751
    "dsm-scm-target",  // Index 5752
    "nsesrvr",  // Index 5753
    "osm-appsrvr",  // Index 5754
    "issa",  // Index 5755
    "osm-oev",  // Index 5756
    "issc",  // Index 5757
    "palace-1",  // Index 5758
    "palace-2",  // Index 5759
    "palace-3",  // Index 5760
    "palace-4",  // Index 5761
    "palace-5",  // Index 5762
    "palace-6",  // Index 5763
    "distinct32",  // Index 5764
    "abyss",  // Index 5765
    "distinct",  // Index 5766
    "snet-sensor-mgmt",  // Index 5767
    "ndmp",  // Index 5768
    "scp-config",  // Index 5769
    "documentum",  // Index 5770
    "documentum_s",  // Index 5771
    "emcrmirccd",  // Index 5772
    "stel",  // Index 5773
    "netapp-sync",  // Index 5774
    "mvs-capacity",  // Index 5775
    "octopus",  // Index 5776
    "swdtp-sv",  // Index 5777
    "rxapi",  // Index 5778
    "abb-hw",  // Index 5779
    "cefd-vmp",  // Index 5780
    "zabbix-agent",  // Index 5781
    "zabbix-trapper",  // Index 5782
    "qptlmd",  // Index 5783
    "amanda",  // Index 5784
    "famdc",  // Index 5785
    "amandaidx",  // Index 5786
    "amidxtape",  // Index 5787
    "itap-ddtp",  // Index 5788
    "ezmeeting-2",  // Index 5789
    "ezproxy-2",  // Index 5790
    "ezrelay",  // Index 5791
    "swdtp",  // Index 5792
    "bctp-server",  // Index 5793
    "nmea-0183",  // Index 5794
    "nmea-onenet",  // Index 5795
    "netiq-endpoint",  // Index 5796
    "netiq-qcheck",  // Index 5797
    "netiq-endpt",  // Index 5798
    "netiq-voipa",  // Index 5799
    "iqrm",  // Index 5800
    "cimple",  // Index 5801
    "bmc-perf-sd",  // Index 5802
    "bmc-gms",  // Index 5803
    "qb-db-server",  // Index 5804
    "snmptls",  // Index 5805
    "snmpdtls",  // Index 5806
    "snmptls-trap",  // Index 5807
    "snmpdtls-trap",  // Index 5808
    "trisoap",  // Index 5809
    "rsms",  // Index 5810
    "rscs",  // Index 5811
    "apollo-relay",  // Index 5812
    "eapol-relay",  // Index 5813
    "axis-wimp-port",  // Index 5814
    "tile-ml",  // Index 5815
    "blocks",  // Index 5816
    "cosir",  // Index 5817
    "bngsync",  // Index 5818
    "cirrossp",  // Index 5819
    "hip-nat-t",  // Index 5820
    "MOS-lower",  // Index 5821
    "MOS-upper",  // Index 5822
    "MOS-aux",  // Index 5823
    "MOS-soap",  // Index 5824
    "MOS-soap-opt",  // Index 5825
    "serverdocs",  // Index 5826
    "printopia",  // Index 5827
    "gap",  // Index 5828
    "lpdg",  // Index 5829
    "nbd",  // Index 5830
    "nmc-disc",  // Index 5831
    "helix",  // Index 5832
    "bveapi",  // Index 5833
    "octopustentacle",  // Index 5834
    "rmiaux",  // Index 5835
    "irisa",  // Index 5836
    "metasys",  // Index 5837
    "weave",  // Index 5838
    "origo-sync",  // Index 5839
    "netapp-icmgmt",  // Index 5840
    "netapp-icdata",  // Index 5841
    "sgi-lk",  // Index 5842
    "myq-termlink",  // Index 5843
    "sgi-dmfmgr",  // Index 5844
    "sgi-soap",  // Index 5845
    "vce",  // Index 5846
    "dicom",  // Index 5847
    "suncacao-snmp",  // Index 5848
    "suncacao-jmxmp",  // Index 5849
    "suncacao-rmi",  // Index 5850
    "suncacao-csa",  // Index 5851
    "suncacao-websvc",  // Index 5852
    "snss",  // Index 5853
    "oemcacao-jmxmp",  // Index 5854
    "t5-straton",  // Index 5855
    "oemcacao-rmi",  // Index 5856
    "oemcacao-websvc",  // Index 5857
    "smsqp",  // Index 5858
    "dcsl-backup",  // Index 5859
    "wifree",  // Index 5860
    "memcache",  // Index 5861
    "xcompute",  // Index 5862
    "imip",  // Index 5863
    "imip-channels",  // Index 5864
    "arena-server",  // Index 5865
    "atm-uhas",  // Index 5866
    "pksd",  // Index 5867
    "hkp",  // Index 5868
    "lsdp",  // Index 5869
    "asgcypresstcps",  // Index 5870
    "tempest-port",  // Index 5871
    "emc-xsw-dconfig",  // Index 5872
    "h323callsigalt",  // Index 5873
    "emc-xsw-dcache",  // Index 5874
    "intrepid-ssl",  // Index 5875
    "lanschool",  // Index 5876
    "xoraya",  // Index 5877
    "x2e-disc",  // Index 5878
    "sysinfo-sp",  // Index 5879
    "tibsd",  // Index 5880
    "wmereceiving",  // Index 5881
    "wmedistribution",  // Index 5882
    "wmereporting",  // Index 5883
    "cce4x",  // Index 5884
    "entextxid",  // Index 5885
    "entextnetwk",  // Index 5886
    "entexthigh",  // Index 5887
    "entextmed",  // Index 5888
    "entextlow",  // Index 5889
    "dbisamserver1",  // Index 5890
    "dbisamserver2",  // Index 5891
    "accuracer",  // Index 5892
    "accuracer-dbms",  // Index 5893
    "ghvpn",  // Index 5894
    "edbsrvr",  // Index 5895
    "vipera",  // Index 5896
    "vipera-ssl",  // Index 5897
    "rets-ssl",  // Index 5898
    "nupaper-ss",  // Index 5899
    "cawas",  // Index 5900
    "hivep",  // Index 5901
    "linogridengine",  // Index 5902
    "rads",  // Index 5903
    "warehouse-sss",  // Index 5904
    "warehouse",  // Index 5905
    "netbus",  // Index 5906
    "italk",  // Index 5907
    "tsaf",  // Index 5908
    "netperf",  // Index 5909
    "i-zipqd",  // Index 5910
    "bcslogc",  // Index 5911
    "rs-pias",  // Index 5912
    "emc-vcas-tcp",  // Index 5913
    "emc-vcas-udp",  // Index 5914
    "powwow-client",  // Index 5915
    "powwow-server",  // Index 5916
    "doip-data",  // Index 5917
    "netbackup",  // Index 5918
    "bprd",  // Index 5919
    "bpdbm",  // Index 5920
    "bpjava-msvc",  // Index 5921
    "vnetd",  // Index 5922
    "bpcd",  // Index 5923
    "vopied",  // Index 5924
    "nbdb",  // Index 5925
    "nomdb",  // Index 5926
    "dsmcc-config",  // Index 5927
    "dsmcc-session",  // Index 5928
    "dsmcc-passthru",  // Index 5929
    "dsmcc-download",  // Index 5930
    "dsmcc-ccp",  // Index 5931
    "bmdss",  // Index 5932
    "ucontrol",  // Index 5933
    "dta-systems",  // Index 5934
    "medevolve",  // Index 5935
    "scotty-ft",  // Index 5936
    "sua",  // Index 5937
    "scotty-disc",  // Index 5938
    "sage-best-com1",  // Index 5939
    "sage-best-com2",  // Index 5940
    "bo2k",  // Index 5941
    "vcs-app",  // Index 5942
    "icpp",  // Index 5943
    "icpps",  // Index 5944
    "gcm-app",  // Index 5945
    "vrts-tdd",  // Index 5946
    "vcscmd",  // Index 5947
    "vad",  // Index 5948
    "cps",  // Index 5949
    "ca-web-update",  // Index 5950
    "xpra",  // Index 5951
    "hde-lcesrvr-1",  // Index 5952
    "hde-lcesrvr-2",  // Index 5953
    "hydap",  // Index 5954
    "onep-tls",  // Index 5955
    "v2g-secc",  // Index 5956
    "swgps",  // Index 5957
    "xpilot",  // Index 5958
    "3link",  // Index 5959
    "cisco-snat",  // Index 5960
    "bex-xr",  // Index 5961
    "ptp",  // Index 5962
    "2ping",  // Index 5963
    "programmar",  // Index 5964
    "fmsas",  // Index 5965
    "fmsascon",  // Index 5966
    "gsms",  // Index 5967
    "alfin",  // Index 5968
    "jwpc",  // Index 5969
    "jwpc-bin",  // Index 5970
    "osxwebadmin",  // Index 5971
    "sun-sea-port",  // Index 5972
    "solaris-audit",  // Index 5973
    "etb4j",  // Index 5974
    "pduncs",  // Index 5975
    "pdefmns",  // Index 5976
    "netserialext1",  // Index 5977
    "netserialext2",  // Index 5978
    "netserialext3",  // Index 5979
    "netserialext4",  // Index 5980
    "connected",  // Index 5981
    "rdgs",  // Index 5982
    "overnet",  // Index 5983
    "xoms",  // Index 5984
    "axon-tunnel",  // Index 5985
    "vtp",  // Index 5986
    "cadsisvr",  // Index 5987
    "newbay-snc-mc",  // Index 5988
    "sgcip",  // Index 5989
    "subseven",  // Index 5990
    "intel-rci-mp",  // Index 5991
    "amt-soap-http",  // Index 5992
    "amt-soap-https",  // Index 5993
    "amt-redir-tcp",  // Index 5994
    "amt-redir-tls",  // Index 5995
    "isode-dua",  // Index 5996
    "ncpu",  // Index 5997
    "vestasdlp",  // Index 5998
    "soundsvirtual",  // Index 5999
    "wdbrpc",  // Index 6000
    "chipper",  // Index 6001
    "avtp",  // Index 6002
    "avdecc",  // Index 6003
    "cpsp",  // Index 6004
    "isa100-gci",  // Index 6005
    "trdp-pd",  // Index 6006
    "trdp-md",  // Index 6007
    "integrius-stp",  // Index 6008
    "ssh-mgmt",  // Index 6009
    "kuang2",  // Index 6010
    "db-lsp",  // Index 6011
    "db-lsp-disc",  // Index 6012
    "ailith",  // Index 6013
    "ea",  // Index 6014
    "zep",  // Index 6015
    "zigbee-ip",  // Index 6016
    "zigbee-ips",  // Index 6017
    "sw-orion",  // Index 6018
    "biimenu",  // Index 6019
    "radpdf",  // Index 6020
    "racf",  // Index 6021
    "opsec-cvp",  // Index 6022
    "opsec-ufp",  // Index 6023
    "opsec-sam",  // Index 6024
    "opsec-lea",  // Index 6025
    "opsec-omi",  // Index 6026
    "ohsc",  // Index 6027
    "opsec-ela",  // Index 6028
    "checkpoint-rtm",  // Index 6029
    "iclid",  // Index 6030
    "clusterxl",  // Index 6031
    "gv-pf",  // Index 6032
    "ac-cluster",  // Index 6033
    "heythings",  // Index 6034
    "rds-ib",  // Index 6035
    "rds-ip",  // Index 6036
    "vdmmesh",  // Index 6037
    "ique",  // Index 6038
    "infotos",  // Index 6039
    "apc-necmp",  // Index 6040
    "igrid",  // Index 6041
    "scintilla",  // Index 6042
    "j-link",  // Index 6043
    "gkrellm",  // Index 6044
    "opsec-uaa",  // Index 6045
    "ua-secureagent",  // Index 6046
    "cora",  // Index 6047
    "keysrvr",  // Index 6048
    "keyshadow",  // Index 6049
    "mtrgtrans",  // Index 6050
    "hp-sco",  // Index 6051
    "hp-sca",  // Index 6052
    "hp-sessmon",  // Index 6053
    "fxuptp",  // Index 6054
    "sxuptp",  // Index 6055
    "jcp",  // Index 6056
    "mle",  // Index 6057
    "faircom-db",  // Index 6058
    "iec-104-sec",  // Index 6059
    "dnp-sec",  // Index 6060
    "dnp",  // Index 6061
    "microsan",  // Index 6062
    "commtact-http",  // Index 6063
    "commtact-https",  // Index 6064
    "btx",  // Index 6065
    "openwebnet",  // Index 6066
    "ss-idi-disc",  // Index 6067
    "ss-idi",  // Index 6068
    "opendeploy",  // Index 6069
    "bakbonenetvault",  // Index 6070
    "nburn_id",  // Index 6071
    "tmophl7mts",  // Index 6072
    "mountd",  // Index 6073
    "nfsrdma",  // Index 6074
    "avesterra",  // Index 6075
    "tolfab",  // Index 6076
    "ipdtp-port",  // Index 6077
    "ipulse-ics",  // Index 6078
    "emwavemsg",  // Index 6079
    "crtech-nlm",  // Index 6080
    "athand-mmp",  // Index 6081
    "irtrans",  // Index 6082
    "notezilla-lan",  // Index 6083
    "memcachedb",  // Index 6084
    "trinket-agent",  // Index 6085
    "cohesity-agent",  // Index 6086
    "aigairserver",  // Index 6087
    "rdm-tfs",  // Index 6088
    "dfserver",  // Index 6089
    "vofr-gateway",  // Index 6090
    "tvpm",  // Index 6091
    "sal",  // Index 6092
    "webphone",  // Index 6093
    "netspeak-is",  // Index 6094
    "netspeak-cs",  // Index 6095
    "netspeak-acd",  // Index 6096
    "netspeak-cps",  // Index 6097
    "snapenetio",  // Index 6098
    "optocontrol",  // Index 6099
    "optohost002",  // Index 6100
    "optohost003",  // Index 6101
    "optohost004",  // Index 6102
    "dcap",  // Index 6103
    "gsidcap",  // Index 6104
    "easyengine",  // Index 6105
    "wnn6",  // Index 6106
    "wnn6_Cn",  // Index 6107
    "wnn6_Kr",  // Index 6108
    "cis",  // Index 6109
    "wnn6_Tw",  // Index 6110
    "showcockpit-net",  // Index 6111
    "shrewd-control",  // Index 6112
    "cis-secure",  // Index 6113
    "WibuKey",  // Index 6114
    "CodeMeter",  // Index 6115
    "codemeter-cmwan",  // Index 6116
    "hpnpd",  // Index 6117
    "caldsoft-backup",  // Index 6118
    "vocaltec-wconf",  // Index 6119
    "vocaltec-phone",  // Index 6120
    "talikaserver",  // Index 6121
    "aws-brf",  // Index 6122
    "brf-gw",  // Index 6123
    "inovaport1",  // Index 6124
    "inovaport2",  // Index 6125
    "inovaport3",  // Index 6126
    "inovaport4",  // Index 6127
    "inovaport5",  // Index 6128
    "inovaport6",  // Index 6129
    "gntp",  // Index 6130
    "s102",  // Index 6131
    "5afe-dir",  // Index 6132
    "elxmgmt",  // Index 6133
    "novar-dbase",  // Index 6134
    "novar-alarm",  // Index 6135
    "novar-global",  // Index 6136
    "aequus",  // Index 6137
    "aequus-alt",  // Index 6138
    "areaguard-neo",  // Index 6139
    "med-ltp",  // Index 6140
    "med-fsp-rx",  // Index 6141
    "med-fsp-tx",  // Index 6142
    "med-supp",  // Index 6143
    "med-ovw",  // Index 6144
    "med-ci",  // Index 6145
    "med-net-svc",  // Index 6146
    "filesphere",  // Index 6147
    "vista-4gl",  // Index 6148
    "ild",  // Index 6149
    "hid",  // Index 6150
    "vrmg-ip",  // Index 6151
    "intel_rci",  // Index 6152
    "tonidods",  // Index 6153
    "binkp",  // Index 6154
    "bilobit",  // Index 6155
    "sdtvwcam",  // Index 6156
    "canditv",  // Index 6157
    "flashfiler",  // Index 6158
    "proactivate",  // Index 6159
    "tcc-http",  // Index 6160
    "cslg",  // Index 6161
    "assoc-disc",  // Index 6162
    "find",  // Index 6163
    "icl-twobase1",  // Index 6164
    "icl-twobase2",  // Index 6165
    "icl-twobase3",  // Index 6166
    "icl-twobase4",  // Index 6167
    "icl-twobase5",  // Index 6168
    "icl-twobase6",  // Index 6169
    "icl-twobase7",  // Index 6170
    "icl-twobase8",  // Index 6171
    "icl-twobase9",  // Index 6172
    "icl-twobase10",  // Index 6173
    "rna",  // Index 6174
    "minecraft",  // Index 6175
    "sauterdongle",  // Index 6176
    "idtp",  // Index 6177
    "vocaltec-hos",  // Index 6178
    "tasp-net",  // Index 6179
    "niobserver",  // Index 6180
    "nilinkanalyst",  // Index 6181
    "niprobe",  // Index 6182
    "bf-game",  // Index 6183
    "bf-master",  // Index 6184
    "quake",  // Index 6185
    "scscp",  // Index 6186
    "wnn6_DS",  // Index 6187
    "wnn6-ds",  // Index 6188
    "cockroach",  // Index 6189
    "ezproxy",  // Index 6190
    "ezmeeting",  // Index 6191
    "k3software-svr",  // Index 6192
    "k3software-cli",  // Index 6193
    "exoline-tcp",  // Index 6194
    "exoline-udp",  // Index 6195
    "exoconfig",  // Index 6196
    "exonet",  // Index 6197
    "hexen2",  // Index 6198
    "flexlm0",  // Index 6199
    "flex-lm",  // Index 6200
    "flexlm1",  // Index 6201
    "flexlm2",  // Index 6202
    "flexlm3",  // Index 6203
    "flexlm4",  // Index 6204
    "flexlm5",  // Index 6205
    "flexlm6",  // Index 6206
    "flexlm7",  // Index 6207
    "flexlm8",  // Index 6208
    "flexlm9",  // Index 6209
    "flexlm10",  // Index 6210
    "halflife",  // Index 6211
    "mongod",  // Index 6212
    "imagepump",  // Index 6213
    "mdcs-scheduler",  // Index 6214
    "jesmsjc",  // Index 6215
    "Trinoo_Bcast",  // Index 6216
    "quakeworld",  // Index 6217
    "kopek-httphead",  // Index 6218
    "Trinoo_Master",  // Index 6219
    "ars-vista",  // Index 6220
    "astrolink",  // Index 6221
    "quake2",  // Index 6222
    "quake3",  // Index 6223
    "tw-auth-key",  // Index 6224
    "nxlmd",  // Index 6225
    "pqsp",  // Index 6226
    "gruber-cashreg",  // Index 6227
    "rethinkdb",  // Index 6228
    "thor-engine",  // Index 6229
    "a27-ran-ran",  // Index 6230
    "voxelstorm",  // Index 6231
    "siemensgsm",  // Index 6232
    "bosswave",  // Index 6233
    "heretic2",  // Index 6234
    "saltd-licensing",  // Index 6235
    "sgsap",  // Index 6236
    "otmp",  // Index 6237
    "sbcap",  // Index 6238
    "iuhsctpassoc",  // Index 6239
    "bingbang",  // Index 6240
    "ndmps",  // Index 6241
    "pago-services1",  // Index 6242
    "pago-services2",  // Index 6243
    "amicon-fpsu-ra",  // Index 6244
    "amicon-fpsu-s",  // Index 6245
    "rwp",  // Index 6246
    "kingdomsonline",  // Index 6247
    "gs-realtime",  // Index 6248
    "samsung-disc",  // Index 6249
    "ovobs",  // Index 6250
    "ka-sddp",  // Index 6251
    "autotrac-acp",  // Index 6252
    "yawn",  // Index 6253
    "Trinoo_Register",  // Index 6254
    "Elite",  // Index 6255
    "BackOrifice",  // Index 6256
    "pace-licensed",  // Index 6257
    "xqosd",  // Index 6258
    "tetrinet",  // Index 6259
    "lm-mon",  // Index 6260
    "dsx_monitor",  // Index 6261
    "diagd",  // Index 6262
    "gamesmith-port",  // Index 6263
    "iceedcp_tx",  // Index 6264
    "iceedcp_rx",  // Index 6265
    "iracinghelper",  // Index 6266
    "t1distproc60",  // Index 6267
    "plex",  // Index 6268
    "apm-link",  // Index 6269
    "sec-ntb-clnt",  // Index 6270
    "DMExpress",  // Index 6271
    "filenet-powsrm",  // Index 6272
    "filenet-tms",  // Index 6273
    "omad",  // Index 6274
    "filenet-rpc",  // Index 6275
    "sometimes-rpc3",  // Index 6276
    "sometimes-rpc4",  // Index 6277
    "sometimes-rpc5",  // Index 6278
    "sometimes-rpc6",  // Index 6279
    "sometimes-rpc7",  // Index 6280
    "sometimes-rpc8",  // Index 6281
    "sometimes-rpc9",  // Index 6282
    "sometimes-rpc10",  // Index 6283
    "sometimes-rpc11",  // Index 6284
    "sometimes-rpc12",  // Index 6285
    "sometimes-rpc13",  // Index 6286
    "sometimes-rpc14",  // Index 6287
    "sometimes-rpc15",  // Index 6288
    "sometimes-rpc16",  // Index 6289
    "sometimes-rpc17",  // Index 6290
    "sometimes-rpc18",  // Index 6291
    "sometimes-rpc19",  // Index 6292
    "sometimes-rpc20",  // Index 6293
    "sometimes-rpc21",  // Index 6294
    "sometimes-rpc22",  // Index 6295
    "sometimes-rpc23",  // Index 6296
    "sometimes-rpc24",  // Index 6297
    "sometimes-rpc25",  // Index 6298
    "sometimes-rpc26",  // Index 6299
    "sometimes-rpc27",  // Index 6300
    "sometimes-rpc28",  // Index 6301
    "mlsn",  // Index 6302
    "retp",  // Index 6303
    "idmgratm",  // Index 6304
    "wg-endpt-comms",  // Index 6305
    "mysqlx",  // Index 6306
    "aurora-balaena",  // Index 6307
    "diamondport",  // Index 6308
    "dgi-serv",  // Index 6309
    "speedtrace",  // Index 6310
    "traceroute",  // Index 6311
    "mtrace",  // Index 6312
    "snip",  // Index 6313
    "digilent-adept",  // Index 6314
    "turbonote-2",  // Index 6315
    "p-net-local",  // Index 6316
    "p-net-remote",  // Index 6317
    "dhanalakshmi",  // Index 6318
    "profinet-rt",  // Index 6319
    "profinet-rtm",  // Index 6320
    "profinet-cm",  // Index 6321
    "ethercat",  // Index 6322
    "heathview",  // Index 6323
    "rt-viewer",  // Index 6324
    "rt-sound",  // Index 6325
    "rt-devicemapper",  // Index 6326
    "rt-classmanager",  // Index 6327
    "rt-labtracker",  // Index 6328
    "rt-helper",  // Index 6329
    "axio-disc",  // Index 6330
    "kitim",  // Index 6331
    "altova-lm",  // Index 6332
    "guttersnex",  // Index 6333
    "openstack-id",  // Index 6334
    "allpeers",  // Index 6335
    "wlcp",  // Index 6336
    "s1-control",  // Index 6337
    "x2-control",  // Index 6338
    "slmap",  // Index 6339
    "nq-ap",  // Index 6340
    "m2ap",  // Index 6341
    "m3ap",  // Index 6342
    "xw-control",  // Index 6343
    "febooti-aw",  // Index 6344
    "observium-agent",  // Index 6345
    "mapx",  // Index 6346
    "kastenxpipe",  // Index 6347
    "3gpp-w1ap",  // Index 6348
    "neckar",  // Index 6349
    "gdrive-sync",  // Index 6350
    "eftp",  // Index 6351
    "unisys-eportal",  // Index 6352
    "ivs-database",  // Index 6353
    "ivs-insertion",  // Index 6354
    "cresco-control",  // Index 6355
    "landesk-cba",  // Index 6356
    "galaxy7-data",  // Index 6357
    "fairview",  // Index 6358
    "agpolicy",  // Index 6359
    "ng-control",  // Index 6360
    "xn-control",  // Index 6361
    "e1-interface",  // Index 6362
    "f1-control",  // Index 6363
    "psqlmws",  // Index 6364
    "sruth",  // Index 6365
    "secrmmsafecopya",  // Index 6366
    "vroa",  // Index 6367
    "sygatefw",  // Index 6368
    "turbonote-1",  // Index 6369
    "safetynetp",  // Index 6370
    "k-patentssensor",  // Index 6371
    "sptx",  // Index 6372
    "cscp",  // Index 6373
    "csccredir",  // Index 6374
    "csccfirewall",  // Index 6375
    "ortec-disc",  // Index 6376
    "fs-qos",  // Index 6377
    "tentacle",  // Index 6378
    "z-wave-s",  // Index 6379
    "crestron-cip",  // Index 6380
    "crestron-ctp",  // Index 6381
    "crestron-cips",  // Index 6382
    "crestron-ctps",  // Index 6383
    "candp",  // Index 6384
    "candrp",  // Index 6385
    "caerpc",  // Index 6386
    "recvr-rc",  // Index 6387
    "reachout",  // Index 6388
    "ndm-agent-port",  // Index 6389
    "ip-provision",  // Index 6390
    "noit-transport",  // Index 6391
    "shaperai",  // Index 6392
    "hmip-routing",  // Index 6393
    "eq3-update",  // Index 6394
    "ew-mgmt",  // Index 6395
    "ew-disc-cmd",  // Index 6396
    "ciscocsdb",  // Index 6397
    "z-wave-tunnel",  // Index 6398
    "pmcd",  // Index 6399
    "pmcdproxy",  // Index 6400
    "pmwebapi",  // Index 6401
    "tinyfw",  // Index 6402
    "coldfusion-auth",  // Index 6403
    "cognex-dataman",  // Index 6404
    "acronis-backup",  // Index 6405
    "domiq",  // Index 6406
    "rbr-debug",  // Index 6407
    "asihpi",  // Index 6408
    "EtherNetIP-2",  // Index 6409
    "m3da",  // Index 6410
    "asmp",  // Index 6411
    "ciscopop",  // Index 6412
    "asmps",  // Index 6413
    "rs-status",  // Index 6414
    "synctest",  // Index 6415
    "invision-ag",  // Index 6416
    "cloudcheck",  // Index 6417
    "eba",  // Index 6418
    "dai-shell",  // Index 6419
    "qdb2service",  // Index 6420
    "ssr-servermgr",  // Index 6421
    "inedo",  // Index 6422
    "spremotetablet",  // Index 6423
    "mediabox",  // Index 6424
    "mbus",  // Index 6425
    "winrm",  // Index 6426
    "jvl-mactalk",  // Index 6427
    "dbbrowse",  // Index 6428
    "directplaysrvr",  // Index 6429
    "ap",  // Index 6430
    "bacnet",  // Index 6431
    "presonus-ucnet",  // Index 6432
    "nimcontroller",  // Index 6433
    "nimspooler",  // Index 6434
    "nimhub",  // Index 6435
    "nimgtw",  // Index 6436
    "nimbusdb",  // Index 6437
    "nimbusdbctrl",  // Index 6438
    "juka",  // Index 6439
    "3gpp-cbsp",  // Index 6440
    "weandsf",  // Index 6441
    "isnetserv",  // Index 6442
    "blp5",  // Index 6443
    "com-bardac-dw",  // Index 6444
    "iqobject",  // Index 6445
    "robotraconteur",  // Index 6446
    "tc_ads_discovery",  // Index 6447
    "matahari",  // Index 6448
    "nusrp",  // Index 6449
    "inspider",  // Index 6450
    "iiimsf",  // Index 6451
    "netprowler-manager",  // Index 6452
    "netprowler-manager2",  // Index 6453
    "netprowler-sensor",  // Index 6454
    "iphone-sync",  // Index 6455
    "murmur",  // Index 6456
    "pcanywhere",  // Index 6457
};

const port_map_entry_t PORT_MAP[65536] = {
    [0 ... 65535] = { 0, 0 },

    [1] = { 1, 0 }, // tcpmux
    [2] = { 2, 0 }, // compressnet
    [3] = { 2, 0 }, // compressnet
    [5] = { 3, 0 }, // rje
    [7] = { 4, 0 }, // echo
    [9] = { 5, 0 }, // discard
    [11] = { 6, 0 }, // systat
    [13] = { 7, 0 }, // daytime
    [15] = { 8, 0 }, // netstat
    [17] = { 9, 0 }, // qotd
    [18] = { 10, 0 }, // msp
    [19] = { 11, 0 }, // chargen
    [20] = { 12, 0 }, // ftp-data
    [21] = { 13, 0 }, // ftp
    [22] = { 14, 0 }, // ssh
    [23] = { 15, 0 }, // telnet
    [24] = { 16, 0 }, // priv-mail
    [25] = { 17, 0 }, // smtp
    [26] = { 18, 0 }, // rsftp
    [27] = { 19, 0 }, // nsw-fe
    [29] = { 20, 0 }, // msg-icp
    [31] = { 21, 0 }, // msg-auth
    [33] = { 22, 0 }, // dsp
    [35] = { 23, 0 }, // priv-print
    [37] = { 24, 0 }, // time
    [38] = { 25, 0 }, // rap
    [39] = { 26, 0 }, // rlp
    [41] = { 27, 0 }, // graphics
    [42] = { 28, 0 }, // nameserver
    [43] = { 29, 0 }, // whois
    [44] = { 30, 0 }, // mpm-flags
    [45] = { 31, 0 }, // mpm
    [46] = { 32, 0 }, // mpm-snd
    [47] = { 33, 0 }, // ni-ftp
    [48] = { 34, 0 }, // auditd
    [49] = { 35, 0 }, // tacacs
    [50] = { 36, 0 }, // re-mail-ck
    [51] = { 37, 0 }, // la-maint
    [52] = { 38, 0 }, // xns-time
    [53] = { 39, 0 }, // domain
    [54] = { 40, 0 }, // xns-ch
    [55] = { 41, 0 }, // isi-gl
    [56] = { 42, 0 }, // xns-auth
    [57] = { 43, 0 }, // priv-term
    [58] = { 44, 0 }, // xns-mail
    [59] = { 45, 0 }, // priv-file
    [61] = { 46, 0 }, // ni-mail
    [62] = { 47, 0 }, // acas
    [63] = { 48, 0 }, // via-ftp
    [64] = { 49, 0 }, // covia
    [65] = { 50, 0 }, // tacacs-ds
    [66] = { 51, 0 }, // sqlnet
    [67] = { 52, 0 }, // dhcps
    [68] = { 53, 0 }, // dhcpc
    [69] = { 54, 0 }, // tftp
    [70] = { 55, 0 }, // gopher
    [71] = { 56, 0 }, // netrjs-1
    [72] = { 57, 0 }, // netrjs-2
    [73] = { 58, 0 }, // netrjs-3
    [74] = { 59, 0 }, // netrjs-4
    [75] = { 60, 0 }, // priv-dial
    [76] = { 61, 0 }, // deos
    [77] = { 62, 0 }, // priv-rje
    [78] = { 63, 0 }, // vettcp
    [79] = { 64, 0 }, // finger
    [80] = { 65, 0 }, // http
    [81] = { 66, 0 }, // hosts2-ns
    [82] = { 67, 0 }, // xfer
    [83] = { 68, 0 }, // mit-ml-dev
    [84] = { 69, 0 }, // ctf
    [85] = { 68, 0 }, // mit-ml-dev
    [86] = { 70, 0 }, // mfcobol
    [87] = { 71, 0 }, // priv-term-l
    [88] = { 72, 0 }, // kerberos-sec
    [89] = { 73, 0 }, // su-mit-tg
    [90] = { 74, 0 }, // dnsix
    [91] = { 75, 0 }, // mit-dov
    [92] = { 76, 0 }, // npp
    [93] = { 77, 0 }, // dcp
    [94] = { 78, 0 }, // objcall
    [95] = { 79, 0 }, // supdup
    [96] = { 80, 0 }, // dixie
    [97] = { 81, 0 }, // swift-rvf
    [98] = { 82, 0 }, // linuxconf
    [99] = { 84, 0 }, // metagram
    [100] = { 85, 0 }, // newacct
    [101] = { 86, 0 }, // hostname
    [102] = { 87, 0 }, // iso-tsap
    [103] = { 88, 0 }, // gppitnp
    [104] = { 89, 0 }, // acr-nema
    [105] = { 90, 0 }, // csnet-ns
    [106] = { 91, 0 }, // pop3pw
    [107] = { 93, 0 }, // rtelnet
    [108] = { 94, 0 }, // snagas
    [109] = { 95, 0 }, // pop2
    [110] = { 96, 0 }, // pop3
    [111] = { 97, 0 }, // rpcbind
    [112] = { 98, 0 }, // mcidas
    [113] = { 99, 0 }, // ident
    [114] = { 101, 0 }, // audionews
    [115] = { 102, 0 }, // sftp
    [116] = { 103, 0 }, // ansanotify
    [117] = { 104, 0 }, // uucp-path
    [118] = { 105, 0 }, // sqlserv
    [119] = { 106, 0 }, // nntp
    [120] = { 107, 0 }, // cfdptkt
    [121] = { 108, 0 }, // erpc
    [122] = { 109, 0 }, // smakynet
    [123] = { 110, 0 }, // ntp
    [124] = { 111, 0 }, // ansatrader
    [125] = { 112, 0 }, // locus-map
    [126] = { 113, 0 }, // unitary
    [127] = { 114, 0 }, // locus-con
    [128] = { 115, 0 }, // gss-xlicen
    [129] = { 116, 0 }, // pwdgen
    [130] = { 117, 0 }, // cisco-fna
    [131] = { 118, 0 }, // cisco-tna
    [132] = { 119, 0 }, // cisco-sys
    [133] = { 120, 0 }, // statsrv
    [134] = { 121, 0 }, // ingres-net
    [135] = { 122, 0 }, // msrpc
    [136] = { 123, 0 }, // profile
    [137] = { 124, 0 }, // netbios-ns
    [138] = { 125, 0 }, // netbios-dgm
    [139] = { 126, 0 }, // netbios-ssn
    [140] = { 127, 0 }, // emfis-data
    [141] = { 128, 0 }, // emfis-cntl
    [142] = { 129, 0 }, // bl-idm
    [143] = { 130, 0 }, // imap
    [144] = { 131, 0 }, // news
    [145] = { 132, 0 }, // uaac
    [146] = { 133, 0 }, // iso-tp0
    [147] = { 134, 0 }, // iso-ip
    [148] = { 135, 0 }, // cronus
    [149] = { 136, 0 }, // aed-512
    [150] = { 137, 0 }, // sql-net
    [151] = { 138, 0 }, // hems
    [152] = { 139, 0 }, // bftp
    [153] = { 140, 0 }, // sgmp
    [154] = { 141, 0 }, // netsc-prod
    [155] = { 142, 0 }, // netsc-dev
    [156] = { 143, 0 }, // sqlsrv
    [157] = { 144, 0 }, // knet-cmp
    [158] = { 145, 0 }, // pcmail-srv
    [159] = { 146, 0 }, // nss-routing
    [160] = { 147, 0 }, // sgmp-traps
    [161] = { 148, 0 }, // snmp
    [162] = { 149, 0 }, // snmptrap
    [163] = { 150, 0 }, // cmip-man
    [164] = { 151, 0 }, // cmip-agent
    [165] = { 153, 0 }, // xns-courier
    [166] = { 154, 0 }, // s-net
    [167] = { 155, 0 }, // namp
    [168] = { 156, 0 }, // rsvd
    [169] = { 157, 0 }, // send
    [170] = { 158, 0 }, // print-srv
    [171] = { 159, 0 }, // multiplex
    [172] = { 160, 0 }, // cl-1
    [173] = { 161, 0 }, // xyplex-mux
    [174] = { 162, 0 }, // mailq
    [175] = { 163, 0 }, // vmnet
    [176] = { 164, 0 }, // genrad-mux
    [177] = { 165, 0 }, // xdmcp
    [178] = { 166, 0 }, // nextstep
    [179] = { 167, 0 }, // bgp
    [180] = { 168, 0 }, // ris
    [181] = { 169, 0 }, // unify
    [182] = { 170, 0 }, // audit
    [183] = { 171, 0 }, // ocbinder
    [184] = { 172, 0 }, // ocserver
    [185] = { 173, 0 }, // remote-kis
    [186] = { 174, 0 }, // kis
    [187] = { 175, 0 }, // aci
    [188] = { 176, 0 }, // mumps
    [189] = { 177, 0 }, // qft
    [190] = { 178, 0 }, // gacp
    [191] = { 180, 0 }, // prospero
    [192] = { 181, 0 }, // osu-nms
    [193] = { 182, 0 }, // srmp
    [194] = { 183, 0 }, // irc
    [195] = { 184, 0 }, // dn6-nlm-aud
    [196] = { 185, 0 }, // dn6-smm-red
    [197] = { 186, 0 }, // dls
    [198] = { 187, 0 }, // dls-mon
    [199] = { 188, 0 }, // smux
    [200] = { 189, 0 }, // src
    [201] = { 190, 0 }, // at-rtmp
    [202] = { 191, 0 }, // at-nbp
    [203] = { 192, 0 }, // at-3
    [204] = { 193, 0 }, // at-echo
    [205] = { 194, 0 }, // at-5
    [206] = { 195, 0 }, // at-zis
    [207] = { 196, 0 }, // at-7
    [208] = { 197, 0 }, // at-8
    [209] = { 198, 0 }, // tam
    [210] = { 199, 0 }, // z39.50
    [211] = { 200, 0 }, // 914c-g
    [212] = { 201, 0 }, // anet
    [213] = { 202, 0 }, // ipx
    [214] = { 203, 0 }, // vmpwscs
    [215] = { 204, 0 }, // softpc
    [216] = { 205, 0 }, // atls
    [217] = { 206, 0 }, // dbase
    [218] = { 207, 0 }, // mpp
    [219] = { 208, 0 }, // uarps
    [220] = { 209, 0 }, // imap3
    [221] = { 210, 0 }, // fln-spx
    [222] = { 211, 0 }, // rsh-spx
    [223] = { 212, 0 }, // cdc
    [224] = { 213, 0 }, // masqdialer
    [242] = { 214, 0 }, // direct
    [243] = { 215, 0 }, // sur-meas
    [244] = { 216, 0 }, // dayna
    [245] = { 217, 0 }, // link
    [246] = { 218, 0 }, // dsp3270
    [247] = { 219, 0 }, // subntbcst_tftp
    [248] = { 220, 0 }, // bhfhs
    [256] = { 221, 0 }, // fw1-secureremote
    [257] = { 222, 0 }, // fw1-mc-fwmodule
    [258] = { 224, 0 }, // fw1-mc-gui
    [259] = { 226, 0 }, // esro-gen
    [260] = { 228, 0 }, // openport
    [261] = { 229, 0 }, // nsiiops
    [262] = { 230, 0 }, // arcisdms
    [263] = { 231, 0 }, // hdap
    [264] = { 232, 0 }, // bgmp
    [265] = { 234, 0 }, // maybe-fw1
    [266] = { 236, 0 }, // sst
    [267] = { 237, 0 }, // td-service
    [268] = { 238, 0 }, // td-replica
    [269] = { 239, 0 }, // manet
    [270] = { 240, 0 }, // gist
    [271] = { 241, 0 }, // pt-tls
    [280] = { 242, 0 }, // http-mgmt
    [281] = { 243, 0 }, // personal-link
    [282] = { 244, 0 }, // cableport-ax
    [283] = { 245, 0 }, // rescap
    [284] = { 246, 0 }, // corerjd
    [286] = { 247, 0 }, // fxp
    [287] = { 248, 0 }, // k-block
    [308] = { 249, 0 }, // novastorbakcup
    [309] = { 250, 0 }, // entrusttime
    [310] = { 251, 0 }, // bhmds
    [311] = { 252, 0 }, // asip-webadmin
    [312] = { 253, 0 }, // vslmp
    [313] = { 254, 0 }, // magenta-logic
    [314] = { 255, 0 }, // opalis-robot
    [315] = { 256, 0 }, // dpsi
    [316] = { 257, 0 }, // decauth
    [317] = { 258, 0 }, // zannet
    [318] = { 259, 0 }, // pkix-timestamp
    [319] = { 260, 0 }, // ptp-event
    [320] = { 261, 0 }, // ptp-general
    [321] = { 262, 0 }, // pip
    [322] = { 263, 0 }, // rtsps
    [323] = { 264, 0 }, // rpki-rtr
    [324] = { 265, 0 }, // rpki-rtr-tls
    [333] = { 266, 0 }, // texar
    [344] = { 267, 0 }, // pdap
    [345] = { 268, 0 }, // pawserv
    [346] = { 269, 0 }, // zserv
    [347] = { 270, 0 }, // fatserv
    [348] = { 271, 0 }, // csi-sgwp
    [349] = { 272, 0 }, // mftp
    [350] = { 273, 0 }, // matip-type-a
    [351] = { 274, 0 }, // matip-type-b
    [352] = { 275, 0 }, // dtag-ste-sb
    [353] = { 276, 0 }, // ndsauth
    [354] = { 277, 0 }, // bh611
    [355] = { 278, 0 }, // datex-asn
    [356] = { 279, 0 }, // cloanto-net-1
    [357] = { 280, 0 }, // bhevent
    [358] = { 281, 0 }, // shrinkwrap
    [359] = { 282, 0 }, // tenebris_nts
    [360] = { 283, 0 }, // scoi2odialog
    [361] = { 284, 0 }, // semantix
    [362] = { 285, 0 }, // srssend
    [363] = { 286, 0 }, // rsvp_tunnel
    [364] = { 287, 0 }, // aurora-cmgr
    [365] = { 288, 0 }, // dtk
    [366] = { 289, 0 }, // odmr
    [367] = { 290, 0 }, // mortgageware
    [368] = { 291, 0 }, // qbikgdp
    [369] = { 292, 0 }, // rpc2portmap
    [370] = { 293, 0 }, // codaauth2
    [371] = { 294, 0 }, // clearcase
    [372] = { 295, 0 }, // ulistserv
    [373] = { 296, 0 }, // legent-1
    [374] = { 297, 0 }, // legent-2
    [375] = { 298, 0 }, // hassle
    [376] = { 299, 0 }, // nip
    [377] = { 300, 0 }, // tnETOS
    [378] = { 301, 0 }, // dsETOS
    [379] = { 302, 0 }, // is99c
    [380] = { 303, 0 }, // is99s
    [381] = { 304, 0 }, // hp-collector
    [382] = { 305, 0 }, // hp-managed-node
    [383] = { 306, 0 }, // hp-alarm-mgr
    [384] = { 307, 0 }, // arns
    [385] = { 308, 0 }, // ibm-app
    [386] = { 309, 0 }, // asa
    [387] = { 310, 0 }, // aurp
    [388] = { 311, 0 }, // unidata-ldm
    [389] = { 312, 0 }, // ldap
    [390] = { 313, 0 }, // uis
    [391] = { 314, 0 }, // synotics-relay
    [392] = { 315, 0 }, // synotics-broker
    [393] = { 316, 0 }, // dis
    [394] = { 317, 0 }, // embl-ndt
    [395] = { 318, 0 }, // netcp
    [396] = { 319, 0 }, // netware-ip
    [397] = { 320, 0 }, // mptn
    [398] = { 321, 0 }, // kryptolan
    [399] = { 322, 0 }, // iso-tsap-c2
    [400] = { 323, 0 }, // work-sol
    [401] = { 324, 0 }, // ups
    [402] = { 325, 0 }, // genie
    [403] = { 326, 0 }, // decap
    [404] = { 327, 0 }, // nced
    [405] = { 328, 0 }, // ncld
    [406] = { 329, 0 }, // imsp
    [407] = { 330, 0 }, // timbuktu
    [408] = { 331, 0 }, // prm-sm
    [409] = { 332, 0 }, // prm-nm
    [410] = { 333, 0 }, // decladebug
    [411] = { 334, 0 }, // rmt
    [412] = { 335, 0 }, // synoptics-trap
    [413] = { 336, 0 }, // smsp
    [414] = { 337, 0 }, // infoseek
    [415] = { 338, 0 }, // bnet
    [416] = { 339, 0 }, // silverplatter
    [417] = { 340, 0 }, // onmux
    [418] = { 341, 0 }, // hyper-g
    [419] = { 342, 0 }, // ariel1
    [420] = { 343, 0 }, // smpte
    [421] = { 344, 0 }, // ariel2
    [422] = { 345, 0 }, // ariel3
    [423] = { 346, 0 }, // opc-job-start
    [424] = { 347, 0 }, // opc-job-track
    [425] = { 348, 0 }, // icad-el
    [426] = { 349, 0 }, // smartsdp
    [427] = { 350, 0 }, // svrloc
    [428] = { 351, 0 }, // ocs_cmu
    [429] = { 352, 0 }, // ocs_amu
    [430] = { 353, 0 }, // utmpsd
    [431] = { 354, 0 }, // utmpcd
    [432] = { 355, 0 }, // iasd
    [433] = { 356, 0 }, // nnsp
    [434] = { 357, 0 }, // mobileip-agent
    [435] = { 358, 0 }, // mobilip-mn
    [436] = { 359, 0 }, // dna-cml
    [437] = { 360, 0 }, // comscm
    [438] = { 361, 0 }, // dsfgw
    [439] = { 362, 0 }, // dasp
    [440] = { 363, 0 }, // sgcp
    [441] = { 364, 0 }, // decvms-sysmgt
    [442] = { 365, 0 }, // cvc_hostd
    [443] = { 366, 0 }, // https
    [444] = { 367, 0 }, // snpp
    [445] = { 368, 0 }, // microsoft-ds
    [446] = { 369, 0 }, // ddm-rdb
    [447] = { 370, 0 }, // ddm-dfm
    [448] = { 371, 0 }, // ddm-ssl
    [449] = { 372, 0 }, // as-servermap
    [450] = { 373, 0 }, // tserver
    [451] = { 374, 0 }, // sfs-smp-net
    [452] = { 375, 0 }, // sfs-config
    [453] = { 376, 0 }, // creativeserver
    [454] = { 377, 0 }, // contentserver
    [455] = { 378, 0 }, // creativepartnr
    [456] = { 379, 0 }, // macon
    [457] = { 380, 0 }, // scohelp
    [458] = { 381, 0 }, // appleqtc
    [459] = { 382, 0 }, // ampr-rcmd
    [460] = { 383, 0 }, // skronk
    [461] = { 384, 0 }, // datasurfsrv
    [462] = { 385, 0 }, // datasurfsrvsec
    [463] = { 386, 0 }, // alpes
    [464] = { 387, 0 }, // kpasswd5
    [465] = { 388, 0 }, // smtps
    [466] = { 389, 0 }, // digital-vrc
    [467] = { 390, 0 }, // mylex-mapd
    [468] = { 391, 0 }, // photuris
    [469] = { 392, 0 }, // rcp
    [470] = { 393, 0 }, // scx-proxy
    [471] = { 394, 0 }, // mondex
    [472] = { 395, 0 }, // ljk-login
    [473] = { 396, 0 }, // hybrid-pop
    [474] = { 397, 0 }, // tn-tl-w1
    [475] = { 399, 0 }, // tcpnethaspsrv
    [476] = { 400, 0 }, // tn-tl-fd1
    [477] = { 401, 0 }, // ss7ns
    [478] = { 402, 0 }, // spsc
    [479] = { 403, 0 }, // iafserver
    [480] = { 404, 0 }, // loadsrv
    [481] = { 406, 0 }, // dvs
    [482] = { 408, 0 }, // bgs-nsi
    [483] = { 410, 0 }, // ulpnet
    [484] = { 411, 0 }, // integra-sme
    [485] = { 412, 0 }, // powerburst
    [486] = { 413, 0 }, // sstats
    [487] = { 415, 0 }, // saft
    [488] = { 416, 0 }, // gss-http
    [489] = { 417, 0 }, // nest-protocol
    [490] = { 418, 0 }, // micom-pfs
    [491] = { 419, 0 }, // go-login
    [492] = { 420, 0 }, // ticf-1
    [493] = { 421, 0 }, // ticf-2
    [494] = { 422, 0 }, // pov-ray
    [495] = { 423, 0 }, // intecourier
    [496] = { 424, 0 }, // pim-rp-disc
    [497] = { 425, 0 }, // retrospect
    [498] = { 426, 0 }, // siam
    [499] = { 427, 0 }, // iso-ill
    [500] = { 428, 0 }, // isakmp
    [501] = { 429, 0 }, // stmf
    [502] = { 430, 0 }, // mbap
    [503] = { 431, 0 }, // intrinsa
    [504] = { 432, 0 }, // citadel
    [505] = { 433, 0 }, // mailbox-lm
    [506] = { 434, 0 }, // ohimsrv
    [507] = { 435, 0 }, // crs
    [508] = { 436, 0 }, // xvttp
    [509] = { 437, 0 }, // snare
    [510] = { 438, 0 }, // fcp
    [511] = { 439, 0 }, // passgo
    [512] = { 440, 0 }, // exec
    [513] = { 442, 0 }, // login
    [514] = { 444, 0 }, // shell
    [515] = { 446, 0 }, // printer
    [516] = { 447, 0 }, // videotex
    [517] = { 448, 0 }, // talk
    [518] = { 449, 0 }, // ntalk
    [519] = { 450, 0 }, // utime
    [520] = { 451, 0 }, // efs
    [521] = { 453, 0 }, // ripng
    [522] = { 454, 0 }, // ulp
    [523] = { 455, 0 }, // ibm-db2
    [524] = { 456, 0 }, // ncp
    [525] = { 457, 0 }, // timed
    [526] = { 458, 0 }, // tempo
    [527] = { 459, 0 }, // stx
    [528] = { 460, 0 }, // custix
    [529] = { 183, 0 }, // irc
    [530] = { 461, 0 }, // courier
    [531] = { 462, 0 }, // conference
    [532] = { 463, 0 }, // netnews
    [533] = { 464, 0 }, // netwall
    [534] = { 465, 0 }, // mm-admin
    [535] = { 466, 0 }, // iiop
    [536] = { 467, 0 }, // opalis-rdv
    [537] = { 468, 0 }, // nmsp
    [538] = { 469, 0 }, // gdomap
    [539] = { 470, 0 }, // apertus-ldp
    [540] = { 471, 0 }, // uucp
    [541] = { 472, 0 }, // uucp-rlogin
    [542] = { 473, 0 }, // commerce
    [543] = { 474, 0 }, // klogin
    [544] = { 475, 0 }, // kshell
    [545] = { 476, 0 }, // ekshell
    [546] = { 478, 0 }, // dhcpv6-client
    [547] = { 479, 0 }, // dhcpv6-server
    [548] = { 480, 0 }, // afp
    [549] = { 481, 0 }, // idfp
    [550] = { 482, 0 }, // new-rwho
    [551] = { 483, 0 }, // cybercash
    [552] = { 484, 0 }, // deviceshare
    [553] = { 485, 0 }, // pirp
    [554] = { 486, 0 }, // rtsp
    [555] = { 487, 0 }, // dsf
    [556] = { 488, 0 }, // remotefs
    [557] = { 489, 0 }, // openvms-sysipc
    [558] = { 490, 0 }, // sdnskmp
    [559] = { 491, 0 }, // teedtap
    [560] = { 492, 0 }, // rmonitor
    [561] = { 493, 0 }, // monitor
    [562] = { 494, 0 }, // chshell
    [563] = { 495, 0 }, // snews
    [564] = { 496, 0 }, // 9pfs
    [565] = { 497, 0 }, // whoami
    [566] = { 498, 0 }, // streettalk
    [567] = { 499, 0 }, // banyan-rpc
    [568] = { 500, 0 }, // ms-shuttle
    [569] = { 501, 0 }, // ms-rome
    [570] = { 502, 0 }, // meter
    [571] = { 503, 0 }, // umeter
    [572] = { 504, 0 }, // sonar
    [573] = { 505, 0 }, // banyan-vip
    [574] = { 506, 0 }, // ftp-agent
    [575] = { 507, 0 }, // vemmi
    [576] = { 508, 0 }, // ipcd
    [577] = { 509, 0 }, // vnas
    [578] = { 510, 0 }, // ipdd
    [579] = { 511, 0 }, // decbsrv
    [580] = { 512, 0 }, // sntp-heartbeat
    [581] = { 513, 0 }, // bdp
    [582] = { 514, 0 }, // scc-security
    [583] = { 515, 0 }, // philips-vc
    [584] = { 516, 0 }, // keyserver
    [585] = { 517, 0 }, // imap4-ssl
    [586] = { 518, 0 }, // password-chg
    [587] = { 519, 0 }, // submission
    [588] = { 520, 0 }, // cal
    [589] = { 521, 0 }, // eyelink
    [590] = { 522, 0 }, // tns-cml
    [591] = { 523, 0 }, // http-alt
    [592] = { 524, 0 }, // eudora-set
    [593] = { 525, 0 }, // http-rpc-epmap
    [594] = { 526, 0 }, // tpip
    [595] = { 527, 0 }, // cab-protocol
    [596] = { 528, 0 }, // smsd
    [597] = { 529, 0 }, // ptcnameservice
    [598] = { 530, 0 }, // sco-websrvrmg3
    [599] = { 531, 0 }, // acp
    [600] = { 532, 0 }, // ipcserver
    [601] = { 533, 0 }, // syslog-conn
    [602] = { 534, 0 }, // xmlrpc-beep
    [603] = { 535, 0 }, // mnotes
    [604] = { 537, 0 }, // tunnel
    [605] = { 538, 0 }, // soap-beep
    [606] = { 539, 0 }, // urm
    [607] = { 540, 0 }, // nqs
    [608] = { 541, 0 }, // sift-uft
    [609] = { 542, 0 }, // npmp-trap
    [610] = { 543, 0 }, // npmp-local
    [611] = { 544, 0 }, // npmp-gui
    [612] = { 545, 0 }, // hmmp-ind
    [613] = { 546, 0 }, // hmmp-op
    [614] = { 547, 0 }, // sshell
    [615] = { 548, 0 }, // sco-inetmgr
    [616] = { 549, 0 }, // sco-sysmgr
    [617] = { 550, 0 }, // sco-dtmgr
    [618] = { 551, 0 }, // dei-icda
    [619] = { 552, 0 }, // compaq-evm
    [620] = { 553, 0 }, // sco-websrvrmgr
    [621] = { 554, 0 }, // escp-ip
    [622] = { 555, 0 }, // collaborator
    [623] = { 556, 0 }, // oob-ws-http
    [624] = { 558, 0 }, // cryptoadmin
    [625] = { 559, 0 }, // apple-xsrvr-admin
    [626] = { 561, 0 }, // apple-imap-admin
    [627] = { 563, 0 }, // passgo-tivoli
    [628] = { 564, 0 }, // qmqp
    [629] = { 565, 0 }, // 3com-amp3
    [630] = { 566, 0 }, // rda
    [631] = { 567, 0 }, // ipp
    [632] = { 568, 0 }, // bmpp
    [633] = { 569, 0 }, // servstat
    [634] = { 570, 0 }, // ginad
    [635] = { 571, 0 }, // rlzdbase
    [636] = { 573, 0 }, // ldapssl
    [637] = { 575, 0 }, // lanserver
    [638] = { 576, 0 }, // mcns-sec
    [639] = { 577, 0 }, // msdp
    [640] = { 578, 0 }, // entrust-sps
    [641] = { 580, 0 }, // repcmd
    [642] = { 581, 0 }, // esro-emsdp
    [643] = { 582, 0 }, // sanity
    [644] = { 583, 0 }, // dwr
    [645] = { 584, 0 }, // pssc
    [646] = { 585, 0 }, // ldp
    [647] = { 586, 0 }, // dhcp-failover
    [648] = { 587, 0 }, // rrp
    [649] = { 588, 0 }, // cadview-3d
    [650] = { 589, 0 }, // obex
    [651] = { 591, 0 }, // ieee-mms
    [652] = { 592, 0 }, // hello-port
    [653] = { 593, 0 }, // repscmd
    [654] = { 594, 0 }, // aodv
    [655] = { 595, 0 }, // tinc
    [656] = { 596, 0 }, // spmp
    [657] = { 597, 0 }, // rmc
    [658] = { 598, 0 }, // tenfold
    [660] = { 599, 0 }, // mac-srvr-admin
    [661] = { 600, 0 }, // hap
    [662] = { 601, 0 }, // pftp
    [663] = { 602, 0 }, // purenoise
    [664] = { 603, 0 }, // secure-aux-bus
    [665] = { 604, 0 }, // sun-dr
    [666] = { 605, 0 }, // doom
    [667] = { 606, 0 }, // disclose
    [668] = { 607, 0 }, // mecomm
    [669] = { 608, 0 }, // meregister
    [670] = { 609, 0 }, // vacdsm-sws
    [671] = { 610, 0 }, // vacdsm-app
    [672] = { 611, 0 }, // vpps-qua
    [673] = { 612, 0 }, // cimplex
    [674] = { 613, 0 }, // acap
    [675] = { 614, 0 }, // dctp
    [676] = { 615, 0 }, // vpps-via
    [677] = { 616, 0 }, // vpp
    [678] = { 617, 0 }, // ggf-ncp
    [679] = { 618, 0 }, // mrm
    [680] = { 619, 0 }, // entrust-aaas
    [681] = { 620, 0 }, // entrust-aams
    [682] = { 621, 0 }, // xfr
    [683] = { 622, 0 }, // corba-iiop
    [684] = { 623, 0 }, // corba-iiop-ssl
    [685] = { 624, 0 }, // mdc-portmapper
    [686] = { 625, 0 }, // hcp-wismar
    [687] = { 626, 0 }, // asipregistry
    [688] = { 627, 0 }, // realm-rusd
    [689] = { 628, 0 }, // nmap
    [690] = { 629, 0 }, // vatp
    [691] = { 630, 0 }, // resvc
    [692] = { 632, 0 }, // hyperwave-isp
    [693] = { 633, 0 }, // connendp
    [694] = { 634, 0 }, // ha-cluster
    [695] = { 635, 0 }, // ieee-mms-ssl
    [696] = { 636, 0 }, // rushd
    [697] = { 637, 0 }, // uuidgen
    [698] = { 638, 0 }, // olsr
    [699] = { 639, 0 }, // accessnetwork
    [700] = { 640, 0 }, // epp
    [701] = { 641, 0 }, // lmp
    [702] = { 642, 0 }, // iris-beep
    [704] = { 643, 0 }, // elcsd
    [705] = { 644, 0 }, // agentx
    [706] = { 645, 0 }, // silc
    [707] = { 646, 0 }, // borland-dsj
    [709] = { 647, 0 }, // entrustmanager
    [710] = { 648, 0 }, // entrust-ash
    [711] = { 649, 0 }, // cisco-tdp
    [712] = { 650, 0 }, // tbrpf
    [713] = { 651, 0 }, // iris-xpc
    [714] = { 652, 0 }, // iris-xpcs
    [715] = { 653, 0 }, // iris-lwz
    [716] = { 654, 0 }, // pana
    [723] = { 655, 0 }, // omfs
    [729] = { 656, 0 }, // netviewdm1
    [730] = { 657, 0 }, // netviewdm2
    [731] = { 658, 0 }, // netviewdm3
    [740] = { 318, 0 }, // netcp
    [741] = { 660, 0 }, // netgw
    [742] = { 661, 0 }, // netrcs
    [744] = { 662, 0 }, // flexlm
    [747] = { 663, 0 }, // fujitsu-dev
    [748] = { 664, 0 }, // ris-cm
    [749] = { 665, 0 }, // kerberos-adm
    [750] = { 666, 0 }, // kerberos
    [751] = { 667, 0 }, // kadmin
    [752] = { 668, 0 }, // qrh
    [753] = { 669, 0 }, // rrh
    [754] = { 670, 0 }, // krb_prop
    [758] = { 672, 0 }, // nlogin
    [759] = { 673, 0 }, // con
    [760] = { 674, 0 }, // krbupdate
    [761] = { 676, 0 }, // kpasswd
    [762] = { 678, 0 }, // quotad
    [763] = { 679, 0 }, // cycleserv
    [764] = { 680, 0 }, // omserv
    [765] = { 681, 0 }, // webster
    [767] = { 682, 0 }, // phonebook
    [769] = { 683, 0 }, // vid
    [770] = { 684, 0 }, // cadlock
    [771] = { 685, 0 }, // rtip
    [772] = { 686, 0 }, // cycleserv2
    [773] = { 687, 0 }, // submit
    [774] = { 689, 0 }, // rpasswd
    [775] = { 691, 0 }, // entomb
    [776] = { 693, 0 }, // wpages
    [777] = { 694, 0 }, // multiling-http
    [780] = { 695, 0 }, // wpgs
    [781] = { 304, 0 }, // hp-collector
    [782] = { 305, 0 }, // hp-managed-node
    [783] = { 696, 0 }, // spamassassin
    [786] = { 697, 0 }, // concert
    [787] = { 698, 0 }, // qsc
    [799] = { 699, 0 }, // controlit
    [800] = { 700, 0 }, // mdbs_daemon
    [801] = { 701, 0 }, // device
    [802] = { 702, 0 }, // mbap-s
    [808] = { 703, 0 }, // ccproxy-http
    [810] = { 704, 0 }, // fcp-udp
    [828] = { 705, 0 }, // itm-mcell-s
    [829] = { 706, 0 }, // pkix-3-ca-ra
    [830] = { 707, 0 }, // netconf-ssh
    [831] = { 708, 0 }, // netconf-beep
    [832] = { 709, 0 }, // netconfsoaphttp
    [833] = { 710, 0 }, // netconfsoapbeep
    [847] = { 711, 0 }, // dhcp-failover2
    [848] = { 712, 0 }, // gdoi
    [853] = { 713, 0 }, // domain-s
    [854] = { 714, 0 }, // dlep
    [860] = { 715, 0 }, // iscsi
    [861] = { 716, 0 }, // owamp-control
    [862] = { 717, 0 }, // twamp-control
    [871] = { 718, 0 }, // supfilesrv
    [873] = { 719, 0 }, // rsync
    [886] = { 720, 0 }, // iclcnet-locate
    [887] = { 721, 0 }, // iclcnet_svinfo
    [888] = { 722, 0 }, // accessbuilder
    [898] = { 723, 0 }, // sun-manageconsole
    [900] = { 724, 0 }, // omginitialrefs
    [901] = { 725, 0 }, // samba-swat
    [902] = { 727, 0 }, // iss-realsecure
    [903] = { 729, 0 }, // iss-console-mgr
    [910] = { 731, 0 }, // kink
    [911] = { 732, 0 }, // xact-backup
    [912] = { 733, 0 }, // apex-mesh
    [913] = { 734, 0 }, // apex-edge
    [950] = { 735, 0 }, // oftep-rpc
    [953] = { 736, 0 }, // rndc
    [975] = { 737, 0 }, // securenetpro-sensor
    [989] = { 738, 0 }, // ftps-data
    [990] = { 739, 0 }, // ftps
    [991] = { 740, 0 }, // nas
    [992] = { 741, 0 }, // telnets
    [993] = { 742, 0 }, // imaps
    [994] = { 743, 0 }, // ircs
    [995] = { 744, 0 }, // pop3s
    [996] = { 745, 0 }, // xtreelic
    [997] = { 747, 0 }, // maitrd
    [998] = { 748, 0 }, // busboy
    [999] = { 750, 0 }, // garcon
    [1000] = { 684, 0 }, // cadlock
    [1001] = { 753, 0 }, // webpush
    [1002] = { 754, 0 }, // windows-icfw
    [1008] = { 755, 0 }, // ufsd
    [1010] = { 756, 0 }, // surf
    [1021] = { 758, 0 }, // exp1
    [1022] = { 759, 0 }, // exp2
    [1023] = { 760, 0 }, // netvenuechat
    [1024] = { 761, 0 }, // kdm
    [1025] = { 762, 0 }, // NFS-or-IIS
    [1026] = { 764, 0 }, // LSA-or-nterm
    [1027] = { 766, 0 }, // IIS
    [1029] = { 767, 0 }, // ms-lsa
    [1030] = { 769, 0 }, // iad1
    [1031] = { 770, 0 }, // iad2
    [1032] = { 771, 0 }, // iad3
    [1033] = { 772, 0 }, // netinfo
    [1034] = { 774, 0 }, // zincite-a
    [1035] = { 776, 0 }, // multidropper
    [1036] = { 778, 0 }, // nsstp
    [1037] = { 779, 0 }, // ams
    [1038] = { 780, 0 }, // mtqp
    [1039] = { 781, 0 }, // sbl
    [1040] = { 782, 0 }, // netsaint
    [1041] = { 784, 0 }, // danf-ak2
    [1042] = { 785, 0 }, // afrog
    [1043] = { 786, 0 }, // boinc
    [1044] = { 787, 0 }, // dcutility
    [1045] = { 788, 0 }, // fpitp
    [1046] = { 789, 0 }, // wfremotertm
    [1047] = { 790, 0 }, // neod1
    [1048] = { 791, 0 }, // neod2
    [1049] = { 792, 0 }, // td-postman
    [1050] = { 793, 0 }, // java-or-OTGfileshare
    [1051] = { 795, 0 }, // optima-vnet
    [1052] = { 796, 0 }, // ddt
    [1053] = { 797, 0 }, // remote-as
    [1054] = { 798, 0 }, // brvread
    [1055] = { 799, 0 }, // ansyslmd
    [1056] = { 800, 0 }, // vfo
    [1057] = { 801, 0 }, // startron
    [1058] = { 802, 0 }, // nim
    [1059] = { 803, 0 }, // nimreg
    [1060] = { 804, 0 }, // polestar
    [1061] = { 805, 0 }, // kiosk
    [1062] = { 806, 0 }, // veracity
    [1063] = { 807, 0 }, // kyoceranetdev
    [1064] = { 808, 0 }, // jstel
    [1065] = { 809, 0 }, // syscomlan
    [1066] = { 810, 0 }, // fpo-fns
    [1067] = { 811, 0 }, // instl_boots
    [1068] = { 812, 0 }, // instl_bootc
    [1069] = { 813, 0 }, // cognex-insight
    [1070] = { 814, 0 }, // gmrupdateserv
    [1071] = { 815, 0 }, // bsquare-voip
    [1072] = { 816, 0 }, // cardax
    [1073] = { 817, 0 }, // bridgecontrol
    [1074] = { 818, 0 }, // warmspotMgmt
    [1075] = { 819, 0 }, // rdrmshc
    [1076] = { 820, 0 }, // sns_credit
    [1077] = { 822, 0 }, // imgames
    [1078] = { 823, 0 }, // avocent-proxy
    [1079] = { 824, 0 }, // asprovatalk
    [1080] = { 825, 0 }, // socks
    [1081] = { 826, 0 }, // pvuniwien
    [1082] = { 827, 0 }, // amt-esd-prot
    [1083] = { 828, 0 }, // ansoft-lm-1
    [1084] = { 829, 0 }, // ansoft-lm-2
    [1085] = { 830, 0 }, // webobjects
    [1086] = { 831, 0 }, // cplscrambler-lg
    [1087] = { 832, 0 }, // cplscrambler-in
    [1088] = { 833, 0 }, // cplscrambler-al
    [1089] = { 834, 0 }, // ff-annunc
    [1090] = { 835, 0 }, // ff-fms
    [1091] = { 836, 0 }, // ff-sm
    [1092] = { 837, 0 }, // obrpd
    [1093] = { 838, 0 }, // proofd
    [1094] = { 839, 0 }, // rootd
    [1095] = { 840, 0 }, // nicelink
    [1096] = { 841, 0 }, // cnrprotocol
    [1097] = { 842, 0 }, // sunclustermgr
    [1098] = { 843, 0 }, // rmiactivation
    [1099] = { 844, 0 }, // rmiregistry
    [1100] = { 845, 0 }, // mctp
    [1101] = { 846, 0 }, // pt2-discover
    [1102] = { 847, 0 }, // adobeserver-1
    [1103] = { 848, 0 }, // xaudio
    [1104] = { 850, 0 }, // xrl
    [1105] = { 851, 0 }, // ftranhc
    [1106] = { 852, 0 }, // isoipsigport-1
    [1107] = { 853, 0 }, // isoipsigport-2
    [1108] = { 854, 0 }, // ratio-adp
    [1109] = { 855, 0 }, // kpop
    [1110] = { 856, 0 }, // nfsd-status
    [1111] = { 858, 0 }, // lmsocialserver
    [1112] = { 859, 0 }, // msql
    [1113] = { 861, 0 }, // ltp-deepspace
    [1114] = { 862, 0 }, // mini-sql
    [1115] = { 863, 0 }, // ardus-trns
    [1116] = { 864, 0 }, // ardus-cntl
    [1117] = { 865, 0 }, // ardus-mtrns
    [1118] = { 866, 0 }, // sacred
    [1119] = { 867, 0 }, // bnetgame
    [1120] = { 868, 0 }, // bnetfile
    [1121] = { 869, 0 }, // rmpp
    [1122] = { 870, 0 }, // availant-mgr
    [1123] = { 871, 0 }, // murray
    [1124] = { 872, 0 }, // hpvmmcontrol
    [1125] = { 873, 0 }, // hpvmmagent
    [1126] = { 874, 0 }, // hpvmmdata
    [1127] = { 875, 0 }, // supfiledbg
    [1128] = { 877, 0 }, // saphostctrl
    [1129] = { 878, 0 }, // saphostctrls
    [1130] = { 879, 0 }, // casp
    [1131] = { 880, 0 }, // caspssl
    [1132] = { 881, 0 }, // kvm-via-ip
    [1133] = { 882, 0 }, // dfn
    [1134] = { 883, 0 }, // aplx
    [1135] = { 884, 0 }, // omnivision
    [1136] = { 885, 0 }, // hhb-gateway
    [1137] = { 886, 0 }, // trim
    [1138] = { 887, 0 }, // encrypted_admin
    [1139] = { 888, 0 }, // cce3x
    [1140] = { 890, 0 }, // autonoc
    [1141] = { 891, 0 }, // mxomss
    [1142] = { 892, 0 }, // edtools
    [1143] = { 893, 0 }, // imyx
    [1144] = { 894, 0 }, // fuscript
    [1145] = { 895, 0 }, // x9-icue
    [1146] = { 896, 0 }, // audit-transfer
    [1147] = { 897, 0 }, // capioverlan
    [1148] = { 898, 0 }, // elfiq-repl
    [1149] = { 899, 0 }, // bvtsonar
    [1150] = { 900, 0 }, // blaze
    [1151] = { 901, 0 }, // unizensus
    [1152] = { 902, 0 }, // winpoplanmess
    [1153] = { 903, 0 }, // c1222-acse
    [1154] = { 904, 0 }, // resacommunity
    [1155] = { 905, 0 }, // nfa
    [1156] = { 906, 0 }, // iascontrol-oms
    [1157] = { 907, 0 }, // iascontrol
    [1158] = { 908, 0 }, // lsnr
    [1159] = { 910, 0 }, // oracle-oms
    [1160] = { 911, 0 }, // olsv
    [1161] = { 912, 0 }, // health-polling
    [1162] = { 913, 0 }, // health-trap
    [1163] = { 914, 0 }, // sddp
    [1164] = { 915, 0 }, // qsm-proxy
    [1165] = { 916, 0 }, // qsm-gui
    [1166] = { 917, 0 }, // qsm-remote
    [1167] = { 918, 0 }, // cisco-ipsla
    [1168] = { 919, 0 }, // vchat
    [1169] = { 920, 0 }, // tripwire
    [1170] = { 921, 0 }, // atc-lm
    [1171] = { 922, 0 }, // atc-appserver
    [1172] = { 923, 0 }, // dnap
    [1173] = { 924, 0 }, // d-cinema-rrp
    [1174] = { 925, 0 }, // fnet-remote-ui
    [1175] = { 926, 0 }, // dossier
    [1176] = { 927, 0 }, // indigo-server
    [1177] = { 928, 0 }, // dkmessenger
    [1178] = { 929, 0 }, // skkserv
    [1179] = { 931, 0 }, // b2n
    [1180] = { 932, 0 }, // mc-client
    [1181] = { 933, 0 }, // 3comnetman
    [1182] = { 934, 0 }, // accelenet
    [1183] = { 936, 0 }, // llsurfup-http
    [1184] = { 937, 0 }, // llsurfup-https
    [1185] = { 938, 0 }, // catchpole
    [1186] = { 939, 0 }, // mysql-cluster
    [1187] = { 940, 0 }, // alias
    [1188] = { 941, 0 }, // hp-webadmin
    [1189] = { 942, 0 }, // unet
    [1190] = { 943, 0 }, // commlinx-avl
    [1191] = { 944, 0 }, // gpfs
    [1192] = { 945, 0 }, // caids-sensor
    [1193] = { 946, 0 }, // fiveacross
    [1194] = { 947, 0 }, // openvpn
    [1195] = { 948, 0 }, // rsf-1
    [1196] = { 949, 0 }, // netmagic
    [1197] = { 950, 0 }, // carrius-rshell
    [1198] = { 951, 0 }, // cajo-discovery
    [1199] = { 952, 0 }, // dmidi
    [1200] = { 953, 0 }, // scol
    [1201] = { 954, 0 }, // nucleus-sand
    [1202] = { 955, 0 }, // caiccipc
    [1203] = { 956, 0 }, // ssslic-mgr
    [1204] = { 957, 0 }, // ssslog-mgr
    [1205] = { 958, 0 }, // accord-mgc
    [1206] = { 959, 0 }, // anthony-data
    [1207] = { 960, 0 }, // metasage
    [1208] = { 961, 0 }, // seagull-ais
    [1209] = { 962, 0 }, // ipcd3
    [1210] = { 963, 0 }, // eoss
    [1211] = { 964, 0 }, // groove-dpp
    [1212] = { 965, 0 }, // lupa
    [1213] = { 966, 0 }, // mpc-lifenet
    [1214] = { 967, 0 }, // fasttrack
    [1215] = { 968, 0 }, // scanstat-1
    [1216] = { 969, 0 }, // etebac5
    [1217] = { 970, 0 }, // hpss-ndapi
    [1218] = { 971, 0 }, // aeroflight-ads
    [1219] = { 972, 0 }, // aeroflight-ret
    [1220] = { 973, 0 }, // quicktime
    [1221] = { 975, 0 }, // sweetware-apps
    [1222] = { 976, 0 }, // nerv
    [1223] = { 977, 0 }, // tgp
    [1224] = { 978, 0 }, // vpnz
    [1225] = { 979, 0 }, // slinkysearch
    [1226] = { 980, 0 }, // stgxfws
    [1227] = { 981, 0 }, // dns2go
    [1228] = { 982, 0 }, // florence
    [1229] = { 983, 0 }, // zented
    [1230] = { 984, 0 }, // periscope
    [1231] = { 985, 0 }, // menandmice-lpm
    [1232] = { 986, 0 }, // first-defense
    [1233] = { 987, 0 }, // univ-appserver
    [1234] = { 988, 0 }, // hotline
    [1235] = { 990, 0 }, // mosaicsyssvc1
    [1236] = { 991, 0 }, // bvcontrol
    [1237] = { 992, 0 }, // tsdos390
    [1238] = { 993, 0 }, // hacl-qs
    [1239] = { 994, 0 }, // nmsd
    [1240] = { 995, 0 }, // instantia
    [1241] = { 996, 0 }, // nessus
    [1242] = { 997, 0 }, // nmasoverip
    [1243] = { 998, 0 }, // serialgateway
    [1244] = { 999, 0 }, // isbconference1
    [1245] = { 1000, 0 }, // isbconference2
    [1246] = { 1001, 0 }, // payrouter
    [1247] = { 1002, 0 }, // visionpyramid
    [1248] = { 1003, 0 }, // hermes
    [1249] = { 1004, 0 }, // mesavistaco
    [1250] = { 1005, 0 }, // swldy-sias
    [1251] = { 1006, 0 }, // servergraph
    [1252] = { 1007, 0 }, // bspne-pcc
    [1253] = { 1008, 0 }, // q55-pcc
    [1254] = { 1009, 0 }, // de-noc
    [1255] = { 1010, 0 }, // de-cache-query
    [1256] = { 1011, 0 }, // de-server
    [1257] = { 1012, 0 }, // shockwave2
    [1258] = { 1013, 0 }, // opennl
    [1259] = { 1014, 0 }, // opennl-voice
    [1260] = { 1015, 0 }, // ibm-ssd
    [1261] = { 1016, 0 }, // mpshrsv
    [1262] = { 1017, 0 }, // qnts-orb
    [1263] = { 1018, 0 }, // dka
    [1264] = { 1019, 0 }, // prat
    [1265] = { 1020, 0 }, // dssiapi
    [1266] = { 1021, 0 }, // dellpwrappks
    [1267] = { 1022, 0 }, // epc
    [1268] = { 1023, 0 }, // propel-msgsys
    [1269] = { 1024, 0 }, // watilapp
    [1270] = { 1025, 0 }, // ssserver
    [1271] = { 1027, 0 }, // excw
    [1272] = { 1028, 0 }, // cspmlockmgr
    [1273] = { 1029, 0 }, // emc-gateway
    [1274] = { 1030, 0 }, // t1distproc
    [1275] = { 1031, 0 }, // ivcollector
    [1276] = { 1032, 0 }, // ivmanager
    [1277] = { 1033, 0 }, // miva-mqs
    [1278] = { 1034, 0 }, // dellwebadmin-1
    [1279] = { 1035, 0 }, // dellwebadmin-2
    [1280] = { 1036, 0 }, // pictrography
    [1281] = { 1037, 0 }, // healthd
    [1282] = { 1038, 0 }, // emperion
    [1283] = { 1039, 0 }, // productinfo
    [1284] = { 1040, 0 }, // iee-qfx
    [1285] = { 1041, 0 }, // neoiface
    [1286] = { 1042, 0 }, // netuitive
    [1287] = { 1043, 0 }, // routematch
    [1288] = { 1044, 0 }, // navbuddy
    [1289] = { 1045, 0 }, // jwalkserver
    [1290] = { 1046, 0 }, // winjaserver
    [1291] = { 1047, 0 }, // seagulllms
    [1292] = { 1048, 0 }, // dsdn
    [1293] = { 1049, 0 }, // pkt-krb-ipsec
    [1294] = { 1050, 0 }, // cmmdriver
    [1295] = { 1051, 0 }, // ehtp
    [1296] = { 1052, 0 }, // dproxy
    [1297] = { 1053, 0 }, // sdproxy
    [1298] = { 1054, 0 }, // lpcp
    [1300] = { 1056, 0 }, // h323hostcallsc
    [1299] = { 1055, 0 }, // hp-sci
    [1301] = { 1057, 0 }, // ci3-software-1
    [1302] = { 1058, 0 }, // ci3-software-2
    [1303] = { 1059, 0 }, // sftsrv
    [1304] = { 1060, 0 }, // boomerang
    [1305] = { 1061, 0 }, // pe-mike
    [1306] = { 1062, 0 }, // re-conn-proto
    [1307] = { 1063, 0 }, // pacmand
    [1308] = { 1064, 0 }, // odsi
    [1309] = { 1065, 0 }, // jtag-server
    [1310] = { 1066, 0 }, // husky
    [1311] = { 1067, 0 }, // rxmon
    [1312] = { 1068, 0 }, // sti-envision
    [1313] = { 1069, 0 }, // bmc_patroldb
    [1314] = { 1070, 0 }, // pdps
    [1315] = { 1071, 0 },  // els
    [1316] = { 1072, 0 },  // exbit-escp
    [1317] = { 1073, 0 },  // vrts-ipcserver
    [1318] = { 1074, 0 },  // krb5gatekeeper
    [1319] = { 1075, 0 },  // amx-icsp
    [1320] = { 1076, 0 },  // amx-axbnet
    [1321] = { 262,  0 }, // pip
    [1322] = { 1077, 0 },  // novation
    [1323] = { 1078, 0 },  // brcd
    [1324] = { 1079, 0 },  // delta-mcp
    [1325] = { 1080, 0 },  // dx-instrument
    [1326] = { 1081, 0 },  // wimsic
    [1327] = { 1082, 0 },  // ultrex
    [1328] = { 1083, 0 },  // ewall
    [1329] = { 1084, 0 },  // netdb-export
    [1330] = { 1085, 0 },  // streetperfect
    [1331] = { 1086, 0 },  // intersan
    [1332] = { 1087, 0 },  // pcia-rxp-b
    [1333] = { 1088, 0 },  // passwrd-policy
    [1334] = { 1089, 0 },  // writesrv
    [1335] = { 1090, 0 },  // digital-notary
    [1336] = { 1091, 0 },  // ischat
    [1337] = { 1092, 0 },  // waste
    [1338] = { 1094, 0 },  // wmc-log-svc
    [1339] = { 1095, 0 },  // kjtsiteserver
    [1340] = { 1096, 0 },  // naap
    [1341] = { 1097, 0 },  // qubes
    [1342] = { 1098, 0 },  // esbroker
    [1343] = { 1099, 0 },  // re101
    [1344] = { 1100, 0 },  // icap
    [1345] = { 1101, 0 },  // vpjp
    [1346] = { 1102, 0 },  // alta-ana-lm
    [1347] = { 1103, 0 },  // bbn-mmc
    [1348] = { 1104, 0 },  // bbn-mmx
    [1349] = { 1105, 0 },  // sbook
    [1350] = { 1106, 0 },  // editbench
    [1351] = { 1107, 0 },  // equationbuilder
    [1352] = { 1108, 0 },  // lotusnotes
    [1353] = { 1109, 0 },  // relief
    [1354] = { 1110, 0 },  // rightbrain
    [1355] = { 1111, 0 },  // intuitive-edge
    [1356] = { 1112, 0 },  // cuillamartin
    [1357] = { 1113, 0 },  // pegboard
    [1358] = { 1114, 0 },  // connlcli
    [1359] = { 1115, 0 },  // ftsrv
    [1360] = { 1116, 0 },  // mimer
    [1361] = { 1117, 0 },  // linx
    [1362] = { 1118, 0 },  // timeflies
    [1363] = { 1119, 0 },  // ndm-requester
    [1364] = { 1120, 0 },  // ndm-server
    [1365] = { 1121, 0 },  // adapt-sna
    [1366] = { 1122, 0 },  // netware-csp
    [1367] = { 1123, 0 },  // dcs
    [1368] = { 1124, 0 },  // screencast
    [1369] = { 1125, 0 },  // gv-us
    [1370] = { 1126, 0 },  // us-gv
    [1371] = { 1127, 0 },  // fc-cli
    [1372] = { 1128, 0 },  // fc-ser
    [1373] = { 1129, 0 },  // chromagrafx
    [1374] = { 1130, 0 },  // molly
    [1375] = { 1131, 0 },  // bytex
    [1376] = { 1132, 0 },  // ibm-pps
    [1377] = { 1133, 0 },  // cichlid
    [1378] = { 1134, 0 },  // elan
    [1379] = { 1135, 0 },  // dbreporter
    [1380] = { 1136, 0 },  // telesis-licman
    [1381] = { 1137, 0 },  // apple-licman
    [1382] = { 1138, 0 },  // udt_os
    [1383] = { 1139, 0 },  // gwha
    [1384] = { 1140, 0 },  // os-licman
    [1385] = { 1141, 0 },  // atex_elmd
    [1386] = { 1142, 0 },  // checksum
    [1387] = { 1143, 0 },  // cadsi-lm
    [1388] = { 1144, 0 },  // objective-dbc
    [1389] = { 1145, 0 },  // iclpv-dm
    [1390] = { 1146, 0 },  // iclpv-sc
    [1391] = { 1147, 0 },  // iclpv-sas
    [1392] = { 1148, 0 },  // iclpv-pm
    [1393] = { 1149, 0 },  // iclpv-nls
    [1394] = { 1150, 0 },  // iclpv-nlc
    [1395] = { 1151, 0 },  // iclpv-wsm
    [1396] = { 1152, 0 },  // dvl-activemail
    [1397] = { 1153, 0 },  // audio-activmail
    [1398] = { 1154, 0 },  // video-activmail
    [1399] = { 1155, 0 },  // cadkey-licman
    [1400] = { 1156, 0 },  // cadkey-tablet
    [1401] = { 1157, 0 },  // goldleaf-licman
    [1402] = { 1158, 0 },  // prm-sm-np
    [1403] = { 1159, 0 },  // prm-nm-np
    [1404] = { 1160, 0 },  // igi-lm
    [1405] = { 1161, 0 },  // ibm-res
    [1406] = { 1162, 0 },  // netlabs-lm
    [1407] = { 1163, 0 },  // dbsa-lm
    [1408] = { 1164, 0 },  // sophia-lm
    [1409] = { 1165, 0 },  // here-lm
    [1410] = { 1166, 0 },  // hiq
    [1411] = { 1167, 0 },  // af
    [1412] = { 1168, 0 },  // innosys
    [1413] = { 1169, 0 },  // innosys-acl
    [1414] = { 1170, 0 },  // ibm-mqseries
    [1415] = { 1171, 0 },  // dbstar
    [1416] = { 1172, 0 },  // novell-lu6.2
    [1417] = { 1173, 0 },  // timbuktu-srv1
    [1418] = { 1174, 0 },  // timbuktu-srv2
    [1419] = { 1175, 0 },  // timbuktu-srv3
    [1420] = { 1176, 0 },  // timbuktu-srv4
    [1421] = { 1177, 0 },  // gandalf-lm
    [1422] = { 1178, 0 },  // autodesk-lm
    [1423] = { 1179, 0 },  // essbase
    [1424] = { 1180, 0 },  // hybrid
    [1425] = { 1181, 0 },  // zion-lm
    [1426] = { 1182, 0 },  // sas-1
    [1427] = { 1183, 0 },  // mloadd
    [1428] = { 1184, 0 },  // informatik-lm
    [1429] = { 1185, 0 },  // nms
    [1430] = { 1186, 0 },  // tpdu
    [1431] = { 1187, 0 },  // rgtp
    [1432] = { 1188, 0 },  // blueberry-lm
    [1433] = { 1189, 0 },  // ms-sql-s
    [1434] = { 1190, 0 },  // ms-sql-m
    [1435] = { 1191, 0 },  // ibm-cics
    [1436] = { 1192, 0 },  // sas-2
    [1437] = { 1193, 0 },  // tabula
    [1438] = { 1194, 0 },  // eicon-server
    [1439] = { 1195, 0 },  // eicon-x25
    [1440] = { 1196, 0 },  // eicon-slp
    [1441] = { 1197, 0 },  // cadis-1
    [1442] = { 1198, 0 },  // cadis-2
    [1443] = { 1199, 0 },  // ies-lm
    [1444] = { 1200, 0 },  // marcam-lm
    [1445] = { 1201, 0 },  // proxima-lm
    [1446] = { 1202, 0 },  // ora-lm
    [1447] = { 1203, 0 },  // apri-lm
    [1448] = { 1204, 0 },  // oc-lm
    [1449] = { 1205, 0 },  // peport
    [1450] = { 1206, 0 },  // dwf
    [1451] = { 1207, 0 },  // infoman
    [1452] = { 1208, 0 },  // gtegsc-lm
    [1453] = { 1209, 0 },  // genie-lm
    [1454] = { 1210, 0 },  // interhdl_elmd
    [1455] = { 1211, 0 },  // esl-lm
    [1456] = { 1212, 0 },  // dca
    [1457] = { 1213, 0 },  // valisys-lm
    [1458] = { 1214, 0 },  // nrcabq-lm
    [1459] = { 1215, 0 },  // proshare1
    [1460] = { 1216, 0 },  // proshare2
    [1461] = { 1217, 0 },  // ibm_wrless_lan
    [1462] = { 1218, 0 },  // world-lm
    [1463] = { 1219, 0 },  // nucleus
    [1464] = { 1220, 0 },  // msl_lmd
    [1465] = { 1221, 0 },  // pipes
    [1466] = { 1222, 0 },  // oceansoft-lm
    [1467] = { 1223, 0 },  // csdmbase
    [1468] = { 1224, 0 },  // csdm
    [1469] = { 1225, 0 },  // aal-lm
    [1470] = { 1226, 0 },  // uaiact
    [1471] = { 1223, 0 },  // csdmbase
    [1472] = { 1224, 0 },  // csdm
    [1473] = { 1227, 0 },  // openmath
    [1474] = { 1228, 0 },  // telefinder
    [1475] = { 1229, 0 },  // taligent-lm
    [1476] = { 1230, 0 },  // clvm-cfg
    [1477] = { 1231, 0 },  // ms-sna-server
    [1478] = { 1232, 0 },  // ms-sna-base
    [1479] = { 1233, 0 },  // dberegister
    [1480] = { 1234, 0 },  // pacerforum
    [1481] = { 1235, 0 },  // airs
    [1482] = { 1236, 0 },  // miteksys-lm
    [1483] = { 1237, 0 },  // afs
    [1484] = { 1238, 0 },  // confluent
    [1485] = { 1239, 0 },  // lansource
    [1486] = { 1240, 0 },  // nms_topo_serv
    [1487] = { 1241, 0 },  // localinfosrvr
    [1488] = { 1242, 0 },  // docstor
    [1489] = { 1243, 0 },  // dmdocbroker
    [1490] = { 1244, 0 },  // insitu-conf
    [1491] = { 1245, 0 },  // anynetgateway
    [1492] = { 1246, 0 },  // stone-design-1
    [1493] = { 1247, 0 },  // netmap_lm
    [1494] = { 1248, 0 },  // citrix-ica
    [1495] = { 1249, 0 },  // cvc
    [1496] = { 1250, 0 },  // liberty-lm
    [1497] = { 1251, 0 },  // rfx-lm
    [1498] = { 1252, 0 },  // watcom-sql
    [1499] = { 1253, 0 },  // fhc
    [1500] = { 1254, 0 },  // vlsi-lm
    [1501] = { 1255, 0 },  // sas-3
    [1502] = { 1256, 0 },  // shivadiscovery
    [1503] = { 1257, 0 },  // imtc-mcs
    [1504] = { 1258, 0 },  // evb-elm
    [1505] = { 1259, 0 },  // funkproxy
    [1506] = { 1260, 0 },  // utcd
    [1507] = { 1261, 0 },  // symplex
    [1508] = { 1262, 0 },  // diagmond
    [1509] = { 1263, 0 },  // robcad-lm
    [1510] = { 1264, 0 },  // mvx-lm
    [1511] = { 1265, 0 },  // 3l-l1
    [1512] = { 1266, 0 },  // wins
    [1513] = { 1267, 0 },  // fujitsu-dtc
    [1514] = { 1268, 0 },  // fujitsu-dtcns
    [1515] = { 1269, 0 },  // ifor-protocol
    [1516] = { 1270, 0 },  // vpad
    [1517] = { 1271, 0 },  // vpac
    [1518] = { 1272, 0 },  // vpvd
    [1519] = { 1273, 0 },  // vpvc
    [1520] = { 1274, 0 },  // atm-zip-office
    [1521] = { 1275, 0 },  // oracle
    [1522] = { 1277, 0 },  // rna-lm
    [1523] = { 1278, 0 },  // cichild-lm
    [1524] = { 1279, 0 },  // ingreslock
    [1525] = { 1280, 0 },  // orasrv
    [1526] = { 1281, 0 },  // pdap-np
    [1527] = { 1282, 0 },  // tlisrv
    [1528] = { 1283, 0 },  // mciautoreg
    [1529] = { 1284, 0 },  // support
    [1530] = { 1286, 0 },  // rap-service
    [1531] = { 1287, 0 },  // rap-listen
    [1532] = { 1288, 0 },  // miroconnect
    [1533] = { 1289, 0 },  // virtual-places
    [1534] = { 1290, 0 },  // micromuse-lm
    [1535] = { 1291, 0 },  // ampr-info
    [1536] = { 1292, 0 },  // ampr-inter
    [1537] = { 1293, 0 },  // sdsc-lm
    [1538] = { 1294, 0 },  // 3ds-lm
    [1539] = { 1295, 0 },  // intellistor-lm
    [1540] = { 1296, 0 },  // rds
    [1541] = { 1297, 0 },  // rds2
    [1542] = { 1298, 0 },  // gridgen-elmd
    [1543] = { 1299, 0 },  // simba-cs
    [1544] = { 1300, 0 },  // aspeclmd
    [1545] = { 1301, 0 },  // vistium-share
    [1546] = { 1302, 0 },  // abbaccuray
    [1547] = { 1303, 0 },  // laplink
    [1548] = { 1304, 0 },  // axon-lm
    [1549] = { 1305, 0 },  // shivahose
    [1550] = { 1307, 0 },  // 3m-image-lm
    [1551] = { 1308, 0 },  // hecmtl-db
    [1552] = { 1309, 0 },  // pciarray
    [1553] = { 1310, 0 },  // sna-cs
    [1554] = { 1311, 0 },  // caci-lm
    [1555] = { 1312, 0 },  // livelan
    [1556] = { 1313, 0 },  // veritas_pbx
    [1557] = { 1314, 0 },  // arbortext-lm
    [1558] = { 1315, 0 },  // xingmpeg
    [1559] = { 1316, 0 },  // web2host
    [1560] = { 1317, 0 },  // asci-val
    [1561] = { 1318, 0 },  // facilityview
    [1562] = { 1319, 0 },  // pconnectmgr
    [1563] = { 1320, 0 },  // cadabra-lm
    [1564] = { 1321, 0 },  // pay-per-view
    [1565] = { 1322, 0 },  // winddlb
    [1566] = { 1323, 0 },  // corelvideo
    [1567] = { 1324, 0 },  // jlicelmd
    [1568] = { 1325, 0 },  // tsspmap
    [1569] = { 1326, 0 },  // ets
    [1570] = { 1327, 0 },  // orbixd
    [1571] = { 1328, 0 },  // rdb-dbs-disp
    [1572] = { 1329, 0 },  // chip-lm
    [1573] = { 1330, 0 },  // itscomm-ns
    [1574] = { 1331, 0 },  // mvel-lm
    [1575] = { 1332, 0 },  // oraclenames
    [1576] = { 1333, 0 },  // moldflow-lm
    [1577] = { 1334, 0 },  // hypercube-lm
    [1578] = { 1335, 0 },  // jacobus-lm
    [1579] = { 1336, 0 },  // ioc-sea-lm
    [1580] = { 1337, 0 },  // tn-tl-r1
    [1581] = { 1339, 0 },  // mil-2045-47001
    [1582] = { 1340, 0 },  // msims
    [1583] = { 1341, 0 },  // simbaexpress
    [1584] = { 1342, 0 },  // tn-tl-fd2
    [1585] = { 1343, 0 },  // intv
    [1586] = { 1344, 0 },  // ibm-abtact
    [1587] = { 1345, 0 },  // pra_elmd
    [1588] = { 1346, 0 },  // triquest-lm
    [1589] = { 1347, 0 },  // vqp
    [1590] = { 1348, 0 },  // gemini-lm
    [1591] = { 1349, 0 },  // ncpm-pm
    [1592] = { 1350, 0 },  // commonspace
    [1593] = { 1351, 0 },  // mainsoft-lm
    [1594] = { 1352, 0 },  // sixtrak
    [1595] = { 1353, 0 },  // radio
    [1596] = { 1354, 0 },  // radio-sm
    [1597] = { 1356, 0 },  // orbplus-iiop
    [1598] = { 1357, 0 },  // picknfs
    [1599] = { 1358, 0 },  // simbaservices
    [1600] = { 1359, 0 },  // issd
    [1601] = { 1360, 0 },  // aas
    [1602] = { 1361, 0 },  // inspect
    [1603] = { 1362, 0 },  // picodbc
    [1604] = { 1363, 0 },  // icabrowser
    [1605] = { 1364, 0 },  // slp
    [1606] = { 1365, 0 },  // slm-api
    [1607] = { 1366, 0 },  // stt
    [1608] = { 1367, 0 },  // smart-lm
    [1609] = { 1368, 0 },  // isysg-lm
    [1610] = { 1369, 0 },  // taurus-wh
    [1611] = { 1370, 0 },  // ill
    [1612] = { 1371, 0 },  // netbill-trans
    [1613] = { 1372, 0 },  // netbill-keyrep
    [1614] = { 1373, 0 },  // netbill-cred
    [1615] = { 1374, 0 },  // netbill-auth
    [1616] = { 1375, 0 },  // netbill-prod
    [1617] = { 1376, 0 },  // nimrod-agent
    [1618] = { 1377, 0 },  // skytelnet
    [1619] = { 1378, 0 },  // xs-openstorage
    [1620] = { 1379, 0 },  // faxportwinport
    [1621] = { 1380, 0 },  // softdataphone
    [1622] = { 1381, 0 },  // ontime
    [1623] = { 1382, 0 },  // jaleosnd
    [1624] = { 1383, 0 },  // udp-sr-port
    [1625] = { 1384, 0 },  // svs-omagent
    [1626] = { 1385, 0 },  // shockwave
    [1627] = { 1386, 0 },  // t128-gateway
    [1628] = { 1387, 0 },  // lontalk-norm
    [1629] = { 1388, 0 },  // lontalk-urgnt
    [1630] = { 1389, 0 },  // oraclenet8cman
    [1631] = { 1390, 0 },  // visitview
    [1632] = { 1391, 0 },  // pammratc
    [1633] = { 1392, 0 },  // pammrpc
    [1634] = { 1393, 0 },  // loaprobe
    [1635] = { 1394, 0 },  // edb-server1
    [1636] = { 1395, 0 },  // isdc
    [1637] = { 1396, 0 },  // islc
    [1638] = { 1397, 0 },  // ismc
    [1639] = { 1398, 0 },  // cert-initiator
    [1640] = { 1399, 0 },  // cert-responder
    [1641] = { 1400, 0 },  // invision
    [1642] = { 1401, 0 },  // isis-am
    [1643] = { 1402, 0 },  // isis-ambc
    [1644] = { 1403, 0 },  // saiseh
    [1645] = { 1404, 0 },  // sightline
    [1646] = { 1406, 0 },  // sa-msg-port
    [1647] = { 1408, 0 },  // rsap
    [1648] = { 1409, 0 },  // concurrent-lm
    [1649] = { 1410, 0 },  // kermit
    [1650] = { 1411, 0 },  // nkd
    [1651] = { 1412, 0 },  // shiva_confsrvr
    [1652] = { 1413, 0 },  // xnmp
    [1653] = { 1414, 0 },  // alphatech-lm
    [1654] = { 1415, 0 },  // stargatealerts
    [1655] = { 1416, 0 },  // dec-mbadmin
    [1656] = { 1417, 0 },  // dec-mbadmin-h
    [1657] = { 1418, 0 },  // fujitsu-mmpdc
    [1658] = { 1419, 0 },  // sixnetudr
    [1659] = { 1420, 0 },  // sg-lm
    [1660] = { 1421, 0 },  // skip-mc-gikreq
    [1661] = { 1422, 0 },  // netview-aix-1
    [1662] = { 1423, 0 },  // netview-aix-2
    [1663] = { 1424, 0 },  // netview-aix-3
    [1664] = { 1425, 0 },  // netview-aix-4
    [1665] = { 1426, 0 },  // netview-aix-5
    [1666] = { 1427, 0 },  // netview-aix-6
    [1667] = { 1428, 0 },  // netview-aix-7
    [1668] = { 1429, 0 },  // netview-aix-8
    [1669] = { 1430, 0 },  // netview-aix-9
    [1670] = { 1431, 0 },  // netview-aix-10
    [1671] = { 1432, 0 },  // netview-aix-11
    [1672] = { 1433, 0 },  // netview-aix-12
    [1673] = { 1434, 0 },  // proshare-mc-1
    [1674] = { 1435, 0 },  // proshare-mc-2
    [1675] = { 1436, 0 },  // pdp
    [1676] = { 1437, 0 },  // netcomm1
    [1677] = { 1439, 0 },  // groupwise
    [1678] = { 1440, 0 },  // prolink
    [1679] = { 1441, 0 },  // darcorp-lm
    [1680] = { 1442, 0 },  // CarbonCopy
    [1681] = { 1444, 0 },  // sd-elmd
    [1682] = { 1445, 0 },  // lanyon-lantern
    [1683] = { 1446, 0 },  // ncpm-hip
    [1684] = { 1447, 0 },  // snaresecure
    [1685] = { 1448, 0 },  // n2nremote
    [1686] = { 1449, 0 },  // cvmon
    [1687] = { 1450, 0 },  // nsjtp-ctrl
    [1688] = { 1451, 0 },  // nsjtp-data
    [1689] = { 1452, 0 },  // firefox
    [1690] = { 1453, 0 },  // ng-umds
    [1691] = { 1454, 0 },  // empire-empuma
    [1692] = { 1455, 0 },  // sstsys-lm
    [1693] = { 1456, 0 },  // rrirtr
    [1694] = { 1457, 0 },  // rrimwm
    [1695] = { 1458, 0 },  // rrilwm
    [1696] = { 1459, 0 },  // rrifmm
    [1697] = { 1460, 0 },  // rrisat
    [1698] = { 1461, 0 },  // rsvp-encap-1
    [1699] = { 1462, 0 },  // rsvp-encap-2
    [1700] = { 1463, 0 },  // mps-raft
    [1701] = { 1464, 0 },  // l2f
    [1702] = { 1466, 0 },  // deskshare
    [1703] = { 1467, 0 },  // hb-engine
    [1704] = { 1468, 0 },  // bcs-broker
    [1705] = { 1469, 0 },  // slingshot
    [1706] = { 1470, 0 },  // jetform
    [1707] = { 1471, 0 },  // vdmplay
    [1708] = { 1472, 0 },  // gat-lmd
    [1709] = { 1473, 0 },  // centra
    [1710] = { 1474, 0 },  // impera
    [1711] = { 1475, 0 },  // pptconference
    [1712] = { 1476, 0 },  // registrar
    [1713] = { 1477, 0 },  // conferencetalk
    [1714] = { 1478, 0 },  // sesi-lm
    [1715] = { 1479, 0 },  // houdini-lm
    [1716] = { 1480, 0 },  // xmsg
    [1717] = { 1481, 0 },  // fj-hdnet
    [1718] = { 1482, 0 },  // h323gatedisc
    [1719] = { 1484, 0 },  // h323gatestat
    [1720] = { 1485, 0 },  // h323q931
    [1721] = { 1487, 0 },  // caicci
    [1722] = { 1488, 0 },  // hks-lm
    [1723] = { 1489, 0 },  // pptp
    [1724] = { 1490, 0 },  // csbphone
    [1725] = { 1491, 0 },  // iden-ralp
    [1726] = { 1492, 0 },  // iberiagames
    [1727] = { 1493, 0 },  // winddx
    [1728] = { 1494, 0 },  // telindus
    [1729] = { 1495, 0 },  // citynl
    [1730] = { 1496, 0 },  // roketz
    [1731] = { 1497, 0 },  // msiccp
    [1732] = { 1498, 0 },  // proxim
    [1733] = { 1499, 0 },  // siipat
    [1734] = { 1500, 0 },  // cambertx-lm
    [1735] = { 1501, 0 },  // privatechat
    [1736] = { 1502, 0 },  // street-stream
    [1737] = { 1503, 0 },  // ultimad
    [1738] = { 1504, 0 },  // gamegen1
    [1739] = { 1505, 0 },  // webaccess
    [1740] = { 1506, 0 },  // encore
    [1741] = { 1507, 0 },  // cisco-net-mgmt
    [1742] = { 1508, 0 },  // 3Com-nsd
    [1743] = { 1509, 0 },  // cinegrfx-lm
    [1744] = { 1510, 0 },  // ncpm-ft
    [1745] = { 1511, 0 },  // remote-winsock
    [1746] = { 1512, 0 },  // ftrapid-1
    [1747] = { 1513, 0 },  // ftrapid-2
    [1748] = { 1514, 0 },  // oracle-em1
    [1749] = { 1515, 0 },  // aspen-services
    [1750] = { 1516, 0 },  // sslp
    [1751] = { 1517, 0 },  // swiftnet
    [1752] = { 1518, 0 },  // lofr-lm
    [1753] = { 1519, 0 },  // predatar-comms
    [1754] = { 1520, 0 },  // oracle-em2
    [1755] = { 1521, 0 },  // wms
    [1756] = { 1523, 0 },  // capfast-lmd
    [1757] = { 1524, 0 },  // cnhrp
    [1758] = { 1525, 0 },  // tftp-mcast
    [1759] = { 1526, 0 },  // spss-lm
    [1760] = { 1527, 0 },  // www-ldap-gw
    [1761] = { 1528, 0 },  // landesk-rc
    [1762] = { 1528, 0 },  // landesk-rc
    [1763] = { 1528, 0 },  // landesk-rc
    [1764] = { 1528, 0 },  // landesk-rc
    [1765] = { 1533, 0 },  // cft-4
    [1766] = { 1534, 0 },  // cft-5
    [1767] = { 1535, 0 },  // cft-6
    [1768] = { 1536, 0 },  // cft-7
    [1769] = { 1537, 0 },  // bmc-net-adm
    [1770] = { 1538, 0 },  // bmc-net-svc
    [1771] = { 1539, 0 },  // vaultbase
    [1772] = { 1540, 0 },  // essweb-gw
    [1773] = { 1541, 0 },  // kmscontrol
    [1774] = { 1542, 0 },  // global-dtserv
    [1775] = { 1543, 0 },  // vdab
    [1776] = { 1544, 0 },  // femis
    [1777] = { 1545, 0 },  // powerguardian
    [1778] = { 1546, 0 },  // prodigy-intrnet
    [1779] = { 1547, 0 },  // pharmasoft
    [1780] = { 1548, 0 },  // dpkeyserv
    [1781] = { 1549, 0 },  // answersoft-lm
    [1782] = { 1550, 0 },  // hp-hcip
    [1784] = { 1551, 0 },  // finle-lm
    [1785] = { 1552, 0 },  // windlm
    [1786] = { 1553, 0 },  // funk-logger
    [1787] = { 1554, 0 },  // funk-license
    [1788] = { 1555, 0 },  // psmond
    [1789] = { 1556, 0 },  // hello
    [1790] = { 468,  0 }, // nmsp
    [1791] = { 1557, 0 },  // ea1
    [1792] = { 1558, 0 },  // ibm-dt-2
    [1793] = { 1559, 0 },  // rsc-robot
    [1794] = { 1560, 0 },  // cera-bcm
    [1795] = { 1561, 0 },  // dpi-proxy
    [1796] = { 1562, 0 },  // vocaltec-admin
    [1797] = { 1563, 0 },  // uma
    [1798] = { 1564, 0 },  // etp
    [1799] = { 1565, 0 },  // netrisk
    [1800] = { 1566, 0 },  // ansys-lm
    [1801] = { 1567, 0 },  // msmq
    [1802] = { 1568, 0 },  // concomp1
    [1803] = { 1569, 0 },  // hp-hcip-gwy
    [1804] = { 1570, 0 },  // enl
    [1805] = { 1571, 0 },  // enl-name
    [1806] = { 1572, 0 },  // musiconline
    [1807] = { 1573, 0 },  // fhsp
    [1808] = { 1574, 0 },  // oracle-vp2
    [1809] = { 1575, 0 },  // oracle-vp1
    [1810] = { 1576, 0 },  // jerand-lm
    [1811] = { 1577, 0 },  // scientia-sdb
    [1812] = { 1405, 0 },  // radius
    [1813] = { 1407, 0 },  // radacct
    [1814] = { 1579, 0 },  // tdp-suite
    [1815] = { 1580, 0 },  // mmpft
    [1816] = { 1581, 0 },  // harp
    [1817] = { 1582, 0 },  // rkb-oscs
    [1818] = { 1583, 0 },  // etftp
    [1819] = { 1584, 0 },  // plato-lm
    [1820] = { 1585, 0 },  // mcagent
    [1821] = { 1586, 0 },  // donnyworld
    [1822] = { 1587, 0 },  // es-elmd
    [1823] = { 1588, 0 },  // unisys-lm
    [1824] = { 1589, 0 },  // metrics-pas
    [1825] = { 1590, 0 },  // direcpc-video
    [1826] = { 1591, 0 },  // ardt
    [1827] = { 1592, 0 },  // pcm
    [1828] = { 1594, 0 },  // itm-mcell-u
    [1829] = { 1595, 0 },  // optika-emedia
    [1830] = { 1596, 0 },  // net8-cman
    [1831] = { 1597, 0 },  // myrtle
    [1832] = { 1598, 0 },  // tht-treasure
    [1833] = { 1599, 0 },  // udpradio
    [1834] = { 1600, 0 },  // ardusuni
    [1835] = { 1601, 0 },  // ardusmul
    [1836] = { 1602, 0 },  // ste-smsc
    [1837] = { 1603, 0 },  // csoft1
    [1838] = { 1604, 0 },  // talnet
    [1839] = { 1605, 0 },  // netopia-vo1
    [1840] = { 1606, 0 },  // netopia-vo2
    [1841] = { 1607, 0 },  // netopia-vo3
    [1842] = { 1608, 0 },  // netopia-vo4
    [1843] = { 1609, 0 },  // netopia-vo5
    [1844] = { 1610, 0 },  // direcpc-dll
    [1845] = { 1611, 0 },  // altalink
    [1846] = { 1612, 0 },  // tunstall-pnc
    [1847] = { 1613, 0 },  // slp-notify
    [1848] = { 1614, 0 },  // fjdocdist
    [1849] = { 1615, 0 },  // alpha-sms
    [1850] = { 1616, 0 },  // gsi
    [1851] = { 1617, 0 },  // ctcd
    [1852] = { 1618, 0 },  // virtual-time
    [1853] = { 1619, 0 },  // vids-avtp
    [1854] = { 1620, 0 },  // buddy-draw
    [1855] = { 1621, 0 },  // fiorano-rtrsvc
    [1856] = { 1622, 0 },  // fiorano-msgsvc
    [1857] = { 1623, 0 },  // datacaptor
    [1858] = { 1624, 0 },  // privateark
    [1859] = { 1625, 0 },  // gammafetchsvr
    [1860] = { 1626, 0 },  // sunscalar-svc
    [1861] = { 1627, 0 },  // lecroy-vicp
    [1862] = { 1628, 0 },  // mysql-cm-agent
    [1863] = { 1629, 0 },  // msnp
    [1864] = { 1630, 0 },  // paradym-31
    [1865] = { 1631, 0 },  // entp
    [1866] = { 1632, 0 },  // swrmi
    [1867] = { 1633, 0 },  // udrive
    [1868] = { 1634, 0 },  // viziblebrowser
    [1869] = { 1635, 0 },  // transact
    [1870] = { 1636, 0 },  // sunscalar-dns
    [1871] = { 1637, 0 },  // canocentral0
    [1872] = { 1638, 0 },  // canocentral1
    [1873] = { 1639, 0 },  // fjmpjps
    [1874] = { 1640, 0 },  // fjswapsnp
    [1875] = { 1641, 0 },  // westell-stats
    [1876] = { 1642, 0 },  // ewcappsrv
    [1877] = { 1643, 0 },  // hp-webqosdb
    [1878] = { 1644, 0 },  // drmsmc
    [1879] = { 1645, 0 },  // nettgain-nms
    [1880] = { 1646, 0 },  // vsat-control
    [1881] = { 1647, 0 },  // ibm-mqseries2
    [1882] = { 1648, 0 },  // ecsqdmn
    [1883] = { 1649, 0 },  // mqtt
    [1884] = { 1651, 0 },  // idmaps
    [1885] = { 1652, 0 },  // vrtstrapserver
    [1886] = { 1653, 0 },  // leoip
    [1887] = { 1654, 0 },  // filex-lport
    [1888] = { 1655, 0 },  // ncconfig
    [1889] = { 1656, 0 },  // unify-adapter
    [1890] = { 1657, 0 },  // wilkenlistener
    [1891] = { 1658, 0 },  // childkey-notif
    [1892] = { 1659, 0 },  // childkey-ctrl
    [1893] = { 1660, 0 },  // elad
    [1894] = { 1661, 0 },  // o2server-port
    [1896] = { 1662, 0 },  // b-novative-ls
    [1897] = { 1663, 0 },  // metaagent
    [1898] = { 1664, 0 },  // cymtec-port
    [1899] = { 1665, 0 },  // mc2studios
    [1900] = { 1666, 0 },  // upnp
    [1901] = { 1667, 0 },  // fjicl-tep-a
    [1902] = { 1668, 0 },  // fjicl-tep-b
    [1903] = { 1669, 0 },  // linkname
    [1904] = { 1670, 0 },  // fjicl-tep-c
    [1905] = { 1671, 0 },  // sugp
    [1906] = { 1672, 0 },  // tpmd
    [1907] = { 1673, 0 },  // intrastar
    [1908] = { 1674, 0 },  // dawn
    [1909] = { 1675, 0 },  // global-wlink
    [1910] = { 1676, 0 },  // ultrabac
    [1911] = { 1677, 0 },  // mtp
    [1912] = { 1678, 0 },  // rhp-iibp
    [1913] = { 1679, 0 },  // armadp
    [1914] = { 1680, 0 },  // elm-momentum
    [1915] = { 1681, 0 },  // facelink
    [1916] = { 1682, 0 },  // persona
    [1917] = { 1683, 0 },  // noagent
    [1918] = { 1684, 0 },  // can-nds
    [1919] = { 1685, 0 },  // can-dch
    [1920] = { 1686, 0 },  // can-ferret
    [1921] = { 1687, 0 },  // noadmin
    [1922] = { 1688, 0 },  // tapestry
    [1923] = { 1689, 0 },  // spice
    [1924] = { 1690, 0 },  // xiip
    [1925] = { 1691, 0 },  // discovery-port
    [1926] = { 1692, 0 },  // egs
    [1927] = { 1693, 0 },  // videte-cipc
    [1928] = { 1694, 0 },  // emsd-port
    [1929] = { 1695, 0 },  // bandwiz-system
    [1930] = { 1696, 0 },  // driveappserver
    [1931] = { 1697, 0 },  // amdsched
    [1932] = { 1698, 0 },  // ctt-broker
    [1933] = { 1699, 0 },  // xmapi
    [1934] = { 1700, 0 },  // xaapi
    [1935] = { 1701, 0 },  // rtmp
    [1936] = { 1703, 0 },  // jetcmeserver
    [1937] = { 1704, 0 },  // jwserver
    [1938] = { 1705, 0 },  // jwclient
    [1939] = { 1706, 0 },  // jvserver
    [1940] = { 1707, 0 },  // jvclient
    [1941] = { 1708, 0 },  // dic-aida
    [1942] = { 1709, 0 },  // res
    [1943] = { 1710, 0 },  // beeyond-media
    [1944] = { 1711, 0 },  // close-combat
    [1945] = { 1712, 0 },  // dialogic-elmd
    [1946] = { 1713, 0 },  // tekpls
    [1947] = { 1714, 0 },  // sentinelsrm
    [1948] = { 1715, 0 },  // eye2eye
    [1949] = { 1716, 0 },  // ismaeasdaqlive
    [1950] = { 1717, 0 },  // ismaeasdaqtest
    [1951] = { 1718, 0 },  // bcs-lmserver
    [1952] = { 1719, 0 },  // mpnjsc
    [1953] = { 1720, 0 },  // rapidbase
    [1954] = { 1721, 0 },  // abr-api
    [1955] = { 1722, 0 },  // abr-secure
    [1956] = { 1723, 0 },  // vrtl-vmf-ds
    [1957] = { 1724, 0 },  // unix-status
    [1958] = { 1725, 0 },  // dxadmind
    [1959] = { 1726, 0 },  // simp-all
    [1960] = { 1727, 0 },  // nasmanager
    [1961] = { 1728, 0 },  // bts-appserver
    [1962] = { 1729, 0 },  // biap-mp
    [1963] = { 1730, 0 },  // webmachine
    [1964] = { 1731, 0 },  // solid-e-engine
    [1965] = { 1732, 0 },  // tivoli-npm
    [1966] = { 1733, 0 },  // slush
    [1967] = { 1734, 0 },  // sns-quote
    [1968] = { 1735, 0 },  // lipsinc
    [1969] = { 1736, 0 }, // lipsinc1
    [1970] = { 1737, 0 }, // netop-rc
    [1971] = { 1738, 0 }, // netop-school
    [1972] = { 1739, 0 }, // intersys-cache
    [1973] = { 1740, 0 }, // dlsrap
    [1974] = { 1741, 0 }, // drp
    [1975] = { 1742, 0 }, // tcoflashagent
    [1976] = { 1743, 0 }, // tcoregagent
    [1977] = { 1744, 0 }, // tcoaddressbook
    [1978] = { 1745, 0 }, // unisql
    [1979] = { 1746, 0 }, // unisql-java
    [1980] = { 1747, 0 }, // pearldoc-xact
    [1981] = { 1748, 0 }, // p2pq
    [1982] = { 1749, 0 }, // estamp
    [1983] = { 1750, 0 }, // lhtp
    [1984] = { 1751, 0 }, // bigbrother
    [1985] = { 1753, 0 }, // hsrp
    [1986] = { 1754, 0 }, // licensedaemon
    [1987] = { 1755, 0 }, // tr-rsrb-p1
    [1988] = { 1756, 0 }, // tr-rsrb-p2
    [1989] = { 1757, 0 }, // tr-rsrb-p3
    [1990] = { 1758, 0 }, // stun-p1
    [1991] = { 1759, 0 }, // stun-p2
    [1992] = { 1760, 0 }, // stun-p3
    [1993] = { 1761, 0 }, // snmp-tcp-port
    [1994] = { 1762, 0 }, // stun-port
    [1995] = { 1763, 0 }, // perf-port
    [1996] = { 1764, 0 }, // tr-rsrb-port
    [1997] = { 1765, 0 }, // gdp-port
    [1998] = { 1766, 0 }, // x25-svc-port
    [1999] = { 1767, 0 }, // tcp-id-port
    [2000] = { 1768, 0 }, // cisco-sccp
    [2001] = { 1769, 0 }, // dc
    [2002] = { 1771, 0 }, // globe
    [2003] = { 64, 0 }, // finger
    [2004] = { 1773, 0 }, // mailbox
    [2005] = { 1775, 0 }, // deslogin
    [2006] = { 1776, 0 }, // invokator
    [2007] = { 1778, 0 }, // dectalk
    [2008] = { 1780, 0 }, // conf
    [2009] = { 131, 0 }, // news
    [2010] = { 1783, 0 }, // search
    [2011] = { 1777, 0 }, // raid-cc
    [2012] = { 1786, 0 }, // ttyinfo
    [2013] = { 1779, 0 }, // raid-am
    [2014] = { 1789, 0 }, // troff
    [2015] = { 1791, 0 }, // cypress
    [2016] = { 1793, 0 }, // bootserver
    [2017] = { 1794, 0 }, // cypress-stat
    [2018] = { 1781, 0 }, // terminaldb
    [2019] = { 1782, 0 }, // whosockami
    [2020] = { 1798, 0 }, // xinupageserver
    [2021] = { 1799, 0 }, // servexec
    [2022] = { 1801, 0 }, // down
    [2023] = { 1803, 0 }, // xinuexpansion3
    [2024] = { 1804, 0 }, // xinuexpansion4
    [2025] = { 1805, 0 }, // ellpack
    [2026] = { 1807, 0 }, // scrabble
    [2027] = { 1808, 0 }, // shadowserver
    [2028] = { 1809, 0 }, // submitserver
    [2029] = { 1810, 0 }, // hsrpv6
    [2030] = { 1811, 0 }, // device2
    [2031] = { 1812, 0 }, // mobrien-chat
    [2032] = { 1813, 0 }, // blackboard
    [2033] = { 1814, 0 }, // glogger
    [2034] = { 1815, 0 }, // scoremgr
    [2035] = { 1816, 0 }, // imsldoc
    [2036] = { 1817, 0 }, // e-dpnet
    [2037] = { 1818, 0 }, // applus
    [2038] = { 1819, 0 }, // objectmanager
    [2039] = { 1820, 0 }, // prizma
    [2040] = { 1821, 0 }, // lam
    [2041] = { 1822, 0 }, // interbase
    [2042] = { 1823, 0 }, // isis
    [2043] = { 1824, 0 }, // isis-bcast
    [2044] = { 1825, 0 }, // rimsl
    [2045] = { 1826, 0 }, // cdfunc
    [2046] = { 1827, 0 }, // sdfunc
    [2047] = { 186, 0 }, // dls
    [2048] = { 1828, 0 }, // dls-monitor
    [2049] = { 1829, 0 }, // nfs
    [2050] = { 1830, 0 }, // av-emb-config
    [2051] = { 1831, 0 }, // epnsdp
    [2052] = { 1832, 0 }, // clearvisn
    [2053] = { 1833, 0 }, // knetd
    [2054] = { 1835, 0 }, // weblogin
    [2055] = { 1836, 0 }, // iop
    [2056] = { 1837, 0 }, // omnisky
    [2057] = { 1838, 0 }, // rich-cp
    [2058] = { 1839, 0 }, // newwavesearch
    [2059] = { 1840, 0 }, // bmc-messaging
    [2060] = { 1841, 0 }, // teleniumdaemon
    [2061] = { 1842, 0 }, // netmount
    [2062] = { 1843, 0 }, // icg-swp
    [2063] = { 1844, 0 }, // icg-bridge
    [2064] = { 1845, 0 }, // dnet-keyproxy
    [2065] = { 1847, 0 }, // dlsrpn
    [2066] = { 1848, 0 }, // aura
    [2067] = { 1849, 0 }, // dlswpn
    [2068] = { 1850, 0 }, // avocentkvm
    [2069] = { 1852, 0 }, // event-port
    [2070] = { 1853, 0 }, // ah-esp-encap
    [2071] = { 1854, 0 }, // acp-port
    [2072] = { 1855, 0 }, // msync
    [2073] = { 1856, 0 }, // gxs-data-port
    [2074] = { 1857, 0 }, // vrtl-vmf-sa
    [2075] = { 1858, 0 }, // newlixengine
    [2076] = { 1859, 0 }, // newlixconfig
    [2077] = { 1860, 0 }, // tsrmagt
    [2078] = { 1861, 0 }, // tpcsrvr
    [2079] = { 1862, 0 }, // idware-router
    [2080] = { 1863, 0 }, // autodesk-nlm
    [2081] = { 1864, 0 }, // kme-trap-port
    [2082] = { 1865, 0 }, // infowave
    [2083] = { 1866, 0 }, // radsec
    [2084] = { 1867, 0 }, // sunclustergeo
    [2085] = { 1868, 0 }, // ada-cip
    [2086] = { 1869, 0 }, // gnunet
    [2087] = { 1870, 0 }, // eli
    [2088] = { 1871, 0 }, // ip-blf
    [2089] = { 1872, 0 }, // sep
    [2090] = { 1873, 0 }, // lrp
    [2091] = { 1874, 0 }, // prp
    [2092] = { 1875, 0 }, // descent3
    [2093] = { 1876, 0 }, // nbx-cc
    [2094] = { 1877, 0 }, // nbx-au
    [2095] = { 1878, 0 }, // nbx-ser
    [2096] = { 1879, 0 }, // nbx-dir
    [2097] = { 1880, 0 }, // jetformpreview
    [2098] = { 1881, 0 }, // dialog-port
    [2099] = { 1882, 0 }, // h2250-annex-g
    [2100] = { 1883, 0 }, // amiganetfs
    [2101] = { 1884, 0 }, // rtcm-sc104
    [2102] = { 1885, 0 }, // zephyr-srv
    [2103] = { 1886, 0 }, // zephyr-clt
    [2104] = { 1887, 0 }, // zephyr-hm
    [2105] = { 1888, 0 }, // eklogin
    [2106] = { 476, 0 }, // ekshell
    [2107] = { 1889, 0 }, // msmq-mgmt
    [2108] = { 1891, 0 }, // rkinit
    [2109] = { 1892, 0 }, // ergolight
    [2110] = { 1893, 0 }, // umsp
    [2111] = { 1894, 0 }, // kx
    [2112] = { 1896, 0 }, // kip
    [2113] = { 1898, 0 }, // hsl-storm
    [2114] = { 1899, 0 }, // newheights
    [2115] = { 761, 0 }, // kdm
    [2116] = { 1900, 0 }, // ccowcmr
    [2117] = { 1901, 0 }, // mentaclient
    [2118] = { 1902, 0 }, // mentaserver
    [2119] = { 1903, 0 }, // gsigatekeeper
    [2120] = { 1904, 0 }, // kauth
    [2121] = { 1906, 0 }, // ccproxy-ftp
    [2122] = { 1908, 0 }, // caupc-remote
    [2123] = { 1909, 0 }, // gtp-control
    [2124] = { 1910, 0 }, // elatelink
    [2125] = { 1911, 0 }, // lockstep
    [2126] = { 1912, 0 }, // pktcable-cops
    [2127] = { 1913, 0 }, // index-pc-wb
    [2128] = { 1914, 0 }, // net-steward
    [2129] = { 1915, 0 }, // cs-live
    [2130] = { 1916, 0 }, // xds
    [2131] = { 1917, 0 }, // avantageb2b
    [2132] = { 1918, 0 }, // solera-epmap
    [2133] = { 1919, 0 }, // zymed-zpp
    [2134] = { 1920, 0 }, // avenue
    [2135] = { 1921, 0 }, // gris
    [2136] = { 1922, 0 }, // appworxsrv
    [2137] = { 1923, 0 }, // connect
    [2138] = { 1924, 0 }, // unbind-cluster
    [2139] = { 1925, 0 }, // ias-auth
    [2140] = { 1926, 0 }, // ias-reg
    [2141] = { 1927, 0 }, // ias-admind
    [2142] = { 1928, 0 }, // tdmoip
    [2143] = { 1929, 0 }, // lv-jc
    [2144] = { 1930, 0 }, // lv-ffx
    [2145] = { 1931, 0 }, // lv-pici
    [2146] = { 1932, 0 }, // lv-not
    [2147] = { 1933, 0 }, // lv-auth
    [2148] = { 1934, 0 }, // veritas-ucl
    [2149] = { 1935, 0 }, // acptsys
    [2150] = { 1936, 0 }, // dynamic3d
    [2151] = { 1937, 0 }, // docent
    [2152] = { 1938, 0 }, // gtp-user
    [2153] = { 1939, 0 }, // ctlptc
    [2154] = { 1940, 0 }, // stdptc
    [2155] = { 1941, 0 }, // brdptc
    [2156] = { 1942, 0 }, // trp
    [2157] = { 1943, 0 }, // xnds
    [2158] = { 1944, 0 }, // touchnetplus
    [2159] = { 1945, 0 }, // gdbremote
    [2160] = { 1946, 0 }, // apc-2160
    [2161] = { 1947, 0 }, // apc-agent
    [2162] = { 1949, 0 }, // navisphere
    [2163] = { 1950, 0 }, // navisphere-sec
    [2164] = { 1951, 0 }, // ddns-v3
    [2165] = { 1952, 0 }, // x-bone-api
    [2166] = { 1953, 0 }, // iwserver
    [2167] = { 1954, 0 }, // raw-serial
    [2168] = { 1955, 0 }, // easy-soft-mux
    [2169] = { 1956, 0 }, // brain
    [2170] = { 1957, 0 }, // eyetv
    [2171] = { 1958, 0 }, // msfw-storage
    [2172] = { 1959, 0 }, // msfw-s-storage
    [2173] = { 1960, 0 }, // msfw-replica
    [2174] = { 1961, 0 }, // msfw-array
    [2175] = { 1962, 0 }, // airsync
    [2176] = { 1963, 0 }, // rapi
    [2177] = { 1964, 0 }, // qwave
    [2178] = { 1965, 0 }, // bitspeer
    [2179] = { 1966, 0 }, // vmrdp
    [2180] = { 1967, 0 }, // mc-gt-srv
    [2181] = { 1968, 0 }, // eforward
    [2182] = { 1969, 0 }, // cgn-stat
    [2183] = { 1970, 0 }, // cgn-config
    [2184] = { 1971, 0 }, // nvd
    [2185] = { 1972, 0 }, // onbase-dds
    [2186] = { 1973, 0 }, // gtaua
    [2187] = { 1974, 0 }, // ssmc
    [2188] = { 1976, 0 }, // radware-rpm
    [2189] = { 1977, 0 }, // radware-rpm-s
    [2190] = { 1978, 0 }, // tivoconnect
    [2191] = { 1979, 0 }, // tvbus
    [2192] = { 1980, 0 }, // asdis
    [2193] = { 1981, 0 }, // drwcs
    [2197] = { 1982, 0 }, // mnp-exchange
    [2198] = { 1983, 0 }, // onehome-remote
    [2199] = { 1984, 0 }, // onehome-help
    [2200] = { 1985, 0 }, // ici
    [2201] = { 1986, 0 }, // ats
    [2202] = { 1987, 0 }, // imtc-map
    [2203] = { 1988, 0 }, // b2-runtime
    [2204] = { 1989, 0 }, // b2-license
    [2205] = { 1990, 0 }, // jps
    [2206] = { 1991, 0 }, // hpocbus
    [2207] = { 1992, 0 }, // hpssd
    [2208] = { 1993, 0 }, // hpiod
    [2209] = { 1994, 0 }, // rimf-ps
    [2210] = { 1995, 0 }, // noaaport
    [2211] = { 1996, 0 }, // emwin
    [2212] = { 1997, 0 }, // leecoposserver
    [2213] = { 1998, 0 }, // kali
    [2214] = { 1999, 0 }, // rpi
    [2215] = { 2000, 0 }, // ipcore
    [2216] = { 2001, 0 }, // vtu-comms
    [2217] = { 2002, 0 }, // gotodevice
    [2218] = { 2003, 0 }, // bounzza
    [2219] = { 2004, 0 }, // netiq-ncap
    [2220] = { 2005, 0 }, // netiq
    [2221] = { 2006, 0 }, // rockwell-csp1
    [2222] = { 2007, 0 }, // EtherNetIP-1
    [2223] = { 2009, 0 }, // rockwell-csp2
    [2224] = { 2010, 0 }, // efi-mg
    [2225] = { 2011, 0 }, // rcip-itu
    [2226] = { 2012, 0 }, // di-drm
    [2227] = { 2013, 0 }, // di-msg
    [2228] = { 2014, 0 }, // ehome-ms
    [2229] = { 2015, 0 }, // datalens
    [2230] = { 2016, 0 }, // queueadm
    [2231] = { 2017, 0 }, // wimaxasncp
    [2232] = { 2018, 0 }, // ivs-video
    [2233] = { 2019, 0 }, // infocrypt
    [2234] = { 2020, 0 }, // directplay
    [2235] = { 2021, 0 }, // sercomm-wlink
    [2236] = { 2022, 0 }, // nani
    [2237] = { 2023, 0 }, // optech-port1-lm
    [2238] = { 2024, 0 }, // aviva-sna
    [2239] = { 2025, 0 }, // imagequery
    [2240] = { 2026, 0 }, // recipe
    [2241] = { 2027, 0 }, // ivsd
    [2242] = { 2028, 0 }, // foliocorp
    [2243] = { 2029, 0 }, // magicom
    [2244] = { 2030, 0 }, // nmsserver
    [2245] = { 2031, 0 }, // hao
    [2246] = { 2032, 0 }, // pc-mta-addrmap
    [2247] = { 2033, 0 }, // antidotemgrsvr
    [2248] = { 2034, 0 }, // ums
    [2249] = { 2035, 0 }, // rfmp
    [2250] = { 2036, 0 }, // remote-collab
    [2251] = { 2037, 0 }, // dif-port
    [2252] = { 2038, 0 }, // njenet-ssl
    [2253] = { 2039, 0 }, // dtv-chan-req
    [2254] = { 2040, 0 }, // seispoc
    [2255] = { 2041, 0 }, // vrtp
    [2256] = { 2042, 0 }, // pcc-mfp
    [2257] = { 2043, 0 }, // simple-tx-rx
    [2258] = { 2044, 0 }, // rcts
    [2259] = { 2045, 0 }, // acd-pm
    [2260] = { 2046, 0 }, // apc-2260
    [2261] = { 2047, 0 }, // comotionmaster
    [2262] = { 2048, 0 }, // comotionback
    [2263] = { 2049, 0 }, // ecwcfg
    [2264] = { 2050, 0 }, // apx500api-1
    [2265] = { 2051, 0 }, // apx500api-2
    [2266] = { 2052, 0 }, // mfserver
    [2267] = { 2053, 0 }, // ontobroker
    [2268] = { 2054, 0 }, // amt
    [2269] = { 2055, 0 }, // mikey
    [2270] = { 2056, 0 }, // starschool
    [2271] = { 2057, 0 }, // mmcals
    [2272] = { 2058, 0 }, // mmcal
    [2273] = { 2059, 0 }, // mysql-im
    [2274] = { 2060, 0 }, // pcttunnell
    [2275] = { 2061, 0 }, // ibridge-data
    [2276] = { 2062, 0 }, // ibridge-mgmt
    [2277] = { 2063, 0 }, // bluectrlproxy
    [2278] = { 2064, 0 }, // s3db
    [2279] = { 2065, 0 }, // xmquery
    [2280] = { 2066, 0 }, // lnvpoller
    [2281] = { 2067, 0 }, // lnvconsole
    [2282] = { 2068, 0 }, // lnvalarm
    [2283] = { 2069, 0 }, // lnvstatus
    [2284] = { 2070, 0 }, // lnvmaps
    [2285] = { 2071, 0 }, // lnvmailmon
    [2286] = { 2072, 0 }, // nas-metering
    [2287] = { 2073, 0 }, // dna
    [2288] = { 2074, 0 }, // netml
    [2289] = { 2075, 0 }, // dict-lookup
    [2290] = { 2076, 0 }, // sonus-logging
    [2291] = { 2077, 0 }, // eapsp
    [2292] = { 2078, 0 }, // mib-streaming
    [2293] = { 2079, 0 }, // npdbgmngr
    [2294] = { 2080, 0 }, // konshus-lm
    [2295] = { 2081, 0 }, // advant-lm
    [2296] = { 2082, 0 }, // theta-lm
    [2297] = { 2083, 0 }, // d2k-datamover1
    [2298] = { 2084, 0 }, // d2k-datamover2
    [2299] = { 2085, 0 }, // pc-telecommute
    [2300] = { 2086, 0 }, // cvmmon
    [2301] = { 2087, 0 }, // compaqdiag
    [2302] = { 2089, 0 }, // binderysupport
    [2303] = { 2090, 0 }, // proxy-gateway
    [2304] = { 2091, 0 }, // attachmate-uts
    [2305] = { 2092, 0 }, // mt-scaleserver
    [2306] = { 2093, 0 }, // tappi-boxnet
    [2307] = { 2094, 0 }, // pehelp
    [2308] = { 2095, 0 }, // sdhelp
    [2309] = { 2096, 0 }, // sdserver
    [2310] = { 2097, 0 }, // sdclient
    [2311] = { 2098, 0 }, // messageservice
    [2312] = { 2099, 0 }, // wanscaler
    [2313] = { 2100, 0 }, // iapp
    [2314] = { 2101, 0 }, // cr-websystems
    [2315] = { 2102, 0 }, // precise-sft
    [2316] = { 2103, 0 }, // sent-lm
    [2317] = { 2104, 0 }, // attachmate-g32
    [2318] = { 2105, 0 }, // cadencecontrol
    [2319] = { 2106, 0 }, // infolibria
    [2320] = { 2107, 0 }, // siebel-ns
    [2321] = { 2108, 0 }, // rdlap
    [2322] = { 2109, 0 }, // ofsd
    [2323] = { 2110, 0 }, // 3d-nfsd
    [2324] = { 2111, 0 }, // cosmocall
    [2325] = { 2112, 0 }, // ansysli
    [2326] = { 2113, 0 }, // idcp
    [2327] = { 2114, 0 }, // xingcsm
    [2328] = { 2115, 0 }, // netrix-sftm
    [2329] = { 1971, 0 }, // nvd
    [2330] = { 2116, 0 }, // tscchat
    [2331] = { 2117, 0 }, // agentview
    [2332] = { 2118, 0 }, // rcc-host
    [2333] = { 2119, 0 }, // snapp
    [2334] = { 2120, 0 }, // ace-client
    [2335] = { 2121, 0 }, // ace-proxy
    [2336] = { 2122, 0 }, // appleugcontrol
    [2337] = { 2123, 0 }, // ideesrv
    [2338] = { 2124, 0 }, // norton-lambert
    [2339] = { 2125, 0 }, // 3com-webview
    [2340] = { 2126, 0 }, // wrs_registry
    [2341] = { 2127, 0 }, // xiostatus
    [2342] = { 2128, 0 }, // manage-exec
    [2343] = { 2129, 0 }, // nati-logos
    [2344] = { 2130, 0 }, // fcmsys
    [2345] = { 2131, 0 }, // dbm
    [2346] = { 2132, 0 }, // redstorm_join
    [2347] = { 2133, 0 }, // redstorm_find
    [2348] = { 2134, 0 }, // redstorm_info
    [2349] = { 2135, 0 }, // redstorm_diag
    [2350] = { 2136, 0 }, // psbserver
    [2351] = { 2137, 0 }, // psrserver
    [2352] = { 2138, 0 }, // pslserver
    [2353] = { 2139, 0 }, // pspserver
    [2354] = { 2140, 0 }, // psprserver
    [2355] = { 2141, 0 }, // psdbserver
    [2356] = { 2142, 0 }, // gxtelmd
    [2357] = { 2143, 0 }, // unihub-server
    [2358] = { 2144, 0 }, // futrix
    [2359] = { 2145, 0 }, // flukeserver
    [2360] = { 2146, 0 }, // nexstorindltd
    [2361] = { 2147, 0 }, // tl1
    [2362] = { 2148, 0 }, // digiman
    [2363] = { 2149, 0 }, // mediacntrlnfsd
    [2364] = { 2150, 0 }, // oi-2000
    [2365] = { 2151, 0 }, // dbref
    [2366] = { 2152, 0 }, // qip-login
    [2367] = { 2153, 0 }, // service-ctrl
    [2368] = { 2154, 0 }, // opentable
    [2370] = { 2155, 0 }, // l3-hbmon
    [2371] = { 2156, 0 }, // worldwire
    [2372] = { 2157, 0 }, // lanmessenger
    [2373] = { 2158, 0 }, // remographlm
    [2374] = { 2159, 0 }, // hydra
    [2375] = { 2160, 0 }, // docker
    [2376] = { 2160, 0 }, // docker
    [2377] = { 2161, 0 }, // swarm
    [2378] = { 2162, 0 }, // dali
    [2379] = { 2163, 0 }, // etcd-client
    [2380] = { 2164, 0 }, // etcd-server
    [2381] = { 2165, 0 }, // compaq-https
    [2382] = { 2166, 0 }, // ms-olap3
    [2383] = { 2167, 0 }, // ms-olap4
    [2384] = { 2168, 0 }, // sd-request
    [2385] = { 2170, 0 }, // sd-data
    [2386] = { 2171, 0 }, // virtualtape
    [2387] = { 2172, 0 }, // vsamredirector
    [2388] = { 2173, 0 }, // mynahautostart
    [2389] = { 2174, 0 }, // ovsessionmgr
    [2390] = { 2175, 0 }, // rsmtp
    [2391] = { 2176, 0 }, // 3com-net-mgmt
    [2392] = { 2177, 0 }, // tacticalauth
    [2393] = { 2178, 0 }, // ms-olap1
    [2394] = { 2179, 0 }, // ms-olap2
    [2395] = { 2180, 0 }, // lan900_remote
    [2396] = { 2181, 0 }, // wusage
    [2397] = { 2182, 0 }, // ncl
    [2398] = { 2183, 0 }, // orbiter
    [2399] = { 2184, 0 }, // fmpro-fdal
    [2400] = { 2185, 0 }, // opequus-server
    [2401] = { 2186, 0 }, // cvspserver
    [2402] = { 2187, 0 }, // taskmaster2000
    [2403] = { 2187, 0 }, // taskmaster2000
    [2404] = { 2188, 0 }, // iec-104
    [2405] = { 2189, 0 }, // trc-netpoll
    [2406] = { 2190, 0 }, // jediserver
    [2407] = { 2191, 0 }, // orion
    [2408] = { 2192, 0 }, // optimanet
    [2409] = { 2193, 0 }, // sns-protocol
    [2410] = { 2194, 0 }, // vrts-registry
    [2411] = { 2195, 0 }, // netwave-ap-mgmt
    [2412] = { 2196, 0 }, // cdn
    [2413] = { 2197, 0 }, // orion-rmi-reg
    [2414] = { 2198, 0 }, // beeyond
    [2415] = { 2199, 0 }, // codima-rtp
    [2416] = { 2200, 0 }, // rmtserver
    [2417] = { 2201, 0 }, // composit-server
    [2418] = { 2202, 0 }, // cas
    [2419] = { 2203, 0 }, // attachmate-s2s
    [2420] = { 2204, 0 }, // dslremote-mgmt
    [2421] = { 2205, 0 }, // g-talk
    [2422] = { 2206, 0 }, // crmsbits
    [2423] = { 2207, 0 }, // rnrp
    [2424] = { 2208, 0 }, // kofax-svr
    [2425] = { 2209, 0 }, // fjitsuappmgr
    [2426] = { 2210, 0 }, // vcmp
    [2427] = { 2211, 0 }, // mgcp-gateway
    [2428] = { 2212, 0 }, // ott
    [2429] = { 2213, 0 }, // ft-role
    [2430] = { 2214, 0 }, // venus
    [2431] = { 2215, 0 }, // venus-se
    [2432] = { 2216, 0 }, // codasrv
    [2433] = { 2217, 0 }, // codasrv-se
    [2434] = { 2218, 0 }, // pxc-epmap
    [2435] = { 2219, 0 }, // optilogic
    [2436] = { 2220, 0 }, // topx
    [2437] = { 2221, 0 }, // unicontrol
    [2438] = { 10, 0 }, // msp
    [2439] = { 2222, 0 }, // sybasedbsynch
    [2440] = { 2223, 0 }, // spearway
    [2441] = { 2224, 0 }, // pvsw-inet
    [2442] = { 2225, 0 }, // netangel
    [2443] = { 2226, 0 }, // powerclientcsf
    [2444] = { 2227, 0 }, // btpp2sectrans
    [2445] = { 2228, 0 }, // dtn1
    [2446] = { 2229, 0 }, // bues_service
    [2447] = { 2230, 0 }, // ovwdb
    [2448] = { 2231, 0 }, // hpppssvr
    [2449] = { 2232, 0 }, // ratl
    [2450] = { 2233, 0 }, // netadmin
    [2451] = { 2234, 0 }, // netchat
    [2452] = { 2235, 0 }, // snifferclient
    [2453] = { 2236, 0 }, // madge-ltd
    [2454] = { 2237, 0 }, // indx-dds
    [2455] = { 2238, 0 }, // wago-io-system
    [2456] = { 2239, 0 }, // altav-remmgt
    [2457] = { 2240, 0 }, // rapido-ip
    [2458] = { 2241, 0 }, // griffin
    [2459] = { 2242, 0 }, // community
    [2460] = { 2243, 0 }, // ms-theater
    [2461] = { 2244, 0 }, // qadmifoper
    [2462] = { 2245, 0 }, // qadmifevent
    [2463] = { 2246, 0 }, // lsi-raid-mgmt
    [2464] = { 2247, 0 }, // direcpc-si
    [2465] = { 2248, 0 }, // lbm
    [2466] = { 2249, 0 }, // lbf
    [2467] = { 2250, 0 }, // high-criteria
    [2468] = { 2251, 0 }, // qip-msgd
    [2469] = { 2252, 0 }, // mti-tcs-comm
    [2470] = { 2253, 0 }, // taskman-port
    [2471] = { 2254, 0 }, // seaodbc
    [2472] = { 2255, 0 }, // c3
    [2473] = { 2256, 0 }, // aker-cdp
    [2474] = { 2257, 0 }, // vitalanalysis
    [2475] = { 2258, 0 }, // ace-server
    [2476] = { 2259, 0 }, // ace-svr-prop
    [2477] = { 2260, 0 }, // ssm-cvs
    [2478] = { 2261, 0 }, // ssm-cssps
    [2479] = { 2262, 0 }, // ssm-els
    [2480] = { 2263, 0 }, // powerexchange
    [2481] = { 2264, 0 }, // giop
    [2482] = { 2265, 0 }, // giop-ssl
    [2483] = { 2266, 0 }, // ttc
    [2484] = { 2267, 0 }, // ttc-ssl
    [2485] = { 2268, 0 }, // netobjects1
    [2486] = { 2269, 0 }, // netobjects2
    [2487] = { 2270, 0 }, // pns
    [2488] = { 2271, 0 }, // moy-corp
    [2489] = { 2272, 0 }, // tsilb
    [2490] = { 2273, 0 }, // qip-qdhcp
    [2491] = { 2274, 0 }, // conclave-cpp
    [2492] = { 2275, 0 }, // groove
    [2493] = { 2276, 0 }, // talarian-mqs
    [2494] = { 2277, 0 }, // bmc-ar
    [2495] = { 2278, 0 }, // fast-rem-serv
    [2496] = { 2279, 0 }, // dirgis
    [2497] = { 2280, 0 }, // quaddb
    [2498] = { 2281, 0 }, // odn-castraq
    [2499] = { 2221, 0 }, // unicontrol
    [2500] = { 2282, 0 }, // rtsserv
    [2501] = { 2283, 0 }, // rtsclient
    [2502] = { 2284, 0 }, // kentrox-prot
    [2503] = { 2285, 0 }, // nms-dpnss
    [2504] = { 2286, 0 }, // wlbs
    [2505] = { 2287, 0 }, // ppcontrol
    [2506] = { 2288, 0 }, // jbroker
    [2507] = { 2289, 0 }, // spock
    [2508] = { 2290, 0 }, // jdatastore
    [2509] = { 2291, 0 }, // fjmpss
    [2510] = { 2292, 0 }, // fjappmgrbulk
    [2511] = { 2293, 0 }, // metastorm
    [2512] = { 2294, 0 }, // citrixima
    [2513] = { 2295, 0 }, // citrixadmin
    [2514] = { 2296, 0 }, // facsys-ntp
    [2515] = { 2297, 0 }, // facsys-router
    [2516] = { 2298, 0 }, // maincontrol
    [2517] = { 2299, 0 }, // call-sig-trans
    [2518] = { 2300, 0 }, // willy
    [2519] = { 2301, 0 }, // globmsgsvc
    [2520] = { 2302, 0 }, // pvsw
    [2521] = { 2303, 0 }, // adaptecmgr
    [2522] = { 2304, 0 }, // windb
    [2523] = { 2305, 0 }, // qke-llc-v3
    [2524] = { 2306, 0 }, // optiwave-lm
    [2525] = { 2307, 0 }, // ms-v-worlds
    [2526] = { 2308, 0 }, // ema-sent-lm
    [2527] = { 2309, 0 }, // iqserver
    [2528] = { 2310, 0 }, // ncr_ccl
    [2529] = { 2311, 0 }, // utsftp
    [2530] = { 2312, 0 }, // vrcommerce
    [2531] = { 2313, 0 }, // ito-e-gui
    [2532] = { 2314, 0 }, // ovtopmd
    [2533] = { 2315, 0 }, // snifferserver
    [2534] = { 2316, 0 }, // combox-web-acc
    [2535] = { 2317, 0 }, // madcap
    [2536] = { 2318, 0 }, // btpp2audctr1
    [2537] = { 2319, 0 }, // upgrade
    [2538] = { 2320, 0 }, // vnwk-prapi
    [2539] = { 2321, 0 }, // vsiadmin
    [2540] = { 2322, 0 }, // lonworks
    [2541] = { 2323, 0 }, // lonworks2
    [2542] = { 2324, 0 }, // udrawgraph
    [2543] = { 2325, 0 }, // reftek
    [2544] = { 2326, 0 }, // novell-zen
    [2545] = { 2327, 0 }, // sis-emt
    [2546] = { 2328, 0 }, // vytalvaultbrtp
    [2547] = { 2329, 0 }, // vytalvaultvsmp
    [2548] = { 2330, 0 }, // vytalvaultpipe
    [2549] = { 2331, 0 }, // ipass
    [2550] = { 2332, 0 }, // ads
    [2551] = { 2333, 0 }, // isg-uda-server
    [2552] = { 2334, 0 }, // call-logging
    [2553] = { 2335, 0 }, // efidiningport
    [2554] = { 2336, 0 }, // vcnet-link-v10
    [2555] = { 2337, 0 }, // compaq-wcp
    [2556] = { 2338, 0 }, // nicetec-nmsvc
    [2557] = { 2339, 0 }, // nicetec-mgmt
    [2558] = { 2340, 0 }, // pclemultimedia
    [2559] = { 2341, 0 }, // lstp
    [2560] = { 2342, 0 }, // labrat
    [2561] = { 2343, 0 }, // mosaixcc
    [2562] = { 2344, 0 }, // delibo
    [2563] = { 2345, 0 }, // cti-redwood
    [2564] = { 2346, 0 }, // hp-3000-telnet
    [2565] = { 2347, 0 }, // coord-svr
    [2566] = { 2348, 0 }, // pcs-pcw
    [2567] = { 2349, 0 }, // clp
    [2568] = { 2350, 0 }, // spamtrap
    [2569] = { 2351, 0 }, // sonuscallsig
    [2570] = { 2352, 0 }, // hs-port
    [2571] = { 2353, 0 }, // cecsvc
    [2572] = { 2354, 0 }, // ibp
    [2573] = { 2355, 0 }, // trustestablish
    [2574] = { 2356, 0 }, // blockade-bpsp
    [2575] = { 2357, 0 }, // hl7
    [2576] = { 2358, 0 }, // tclprodebugger
    [2577] = { 2359, 0 }, // scipticslsrvr
    [2578] = { 2360, 0 }, // rvs-isdn-dcp
    [2579] = { 2361, 0 }, // mpfoncl
    [2580] = { 2362, 0 }, // tributary
    [2581] = { 2363, 0 }, // argis-te
    [2582] = { 2364, 0 }, // argis-ds
    [2583] = { 2365, 0 }, // mon
    [2584] = { 2366, 0 }, // cyaserv
    [2585] = { 2367, 0 }, // netx-server
    [2586] = { 2368, 0 }, // netx-agent
    [2587] = { 2369, 0 }, // masc
    [2588] = { 2370, 0 }, // privilege
    [2589] = { 2371, 0 }, // quartus-tcl
    [2590] = { 2372, 0 }, // idotdist
    [2591] = { 2373, 0 }, // maytagshuffle
    [2592] = { 2374, 0 }, // netrek
    [2593] = { 2375, 0 }, // mns-mail
    [2594] = { 2376, 0 }, // dts
    [2595] = { 2377, 0 }, // worldfusion1
    [2596] = { 2378, 0 }, // worldfusion2
    [2597] = { 2379, 0 }, // homesteadglory
    [2598] = { 2380, 0 }, // citriximaclient
    [2599] = { 2381, 0 }, // snapd
    [2600] = { 2382, 0 }, // zebrasrv
    [2601] = { 2384, 0 }, // zebra
    [2602] = { 2386, 0 }, // ripd
    [2603] = { 2388, 0 }, // ripngd
    [2604] = { 2390, 0 }, // ospfd
    [2605] = { 2392, 0 }, // bgpd
    [2606] = { 2394, 0 }, // netmon
    [2607] = { 2395, 0 }, // connection
    [2608] = { 2396, 0 }, // wag-service
    [2609] = { 2397, 0 }, // system-monitor
    [2610] = { 2398, 0 }, // versa-tek
    [2611] = { 2399, 0 }, // lionhead
    [2612] = { 2400, 0 }, // qpasa-agent
    [2613] = { 2401, 0 }, // smntubootstrap
    [2614] = { 2402, 0 }, // neveroffline
    [2615] = { 2403, 0 }, // firepower
    [2616] = { 2404, 0 }, // appswitch-emp
    [2617] = { 2405, 0 }, // cmadmin
    [2618] = { 2406, 0 }, // priority-e-com
    [2619] = { 2407, 0 }, // bruce
    [2620] = { 2408, 0 }, // lpsrecommender
    [2621] = { 2409, 0 }, // miles-apart
    [2622] = { 2410, 0 }, // metricadbc
    [2623] = { 2411, 0 }, // lmdp
    [2624] = { 2412, 0 }, // aria
    [2625] = { 2413, 0 }, // blwnkl-port
    [2626] = { 2414, 0 }, // gbjd816
    [2627] = { 681, 0 }, // webster
    [2628] = { 2415, 0 }, // dict
    [2629] = { 2416, 0 }, // sitaraserver
    [2630] = { 2417, 0 }, // sitaramgmt
    [2631] = { 2418, 0 }, // sitaradir
    [2632] = { 2419, 0 }, // irdg-post
    [2633] = { 2420, 0 }, // interintelli
    [2634] = { 2421, 0 }, // pk-electronics
    [2635] = { 2422, 0 }, // backburner
    [2636] = { 2423, 0 }, // solve
    [2637] = { 2424, 0 }, // imdocsvc
    [2638] = { 2425, 0 }, // sybase
    [2639] = { 2427, 0 }, // aminet
    [2640] = { 2428, 0 }, // sai_sentlm
    [2641] = { 2429, 0 }, // hdl-srv
    [2642] = { 2430, 0 }, // tragic
    [2643] = { 2431, 0 }, // gte-samp
    [2644] = { 2432, 0 }, // travsoft-ipx-t
    [2645] = { 2433, 0 }, // novell-ipx-cmd
    [2646] = { 2434, 0 }, // and-lm
    [2647] = { 2435, 0 }, // syncserver
    [2648] = { 2436, 0 }, // upsnotifyprot
    [2649] = { 2437, 0 }, // vpsipport
    [2650] = { 2438, 0 }, // eristwoguns
    [2651] = { 2439, 0 }, // ebinsite
    [2652] = { 2440, 0 }, // interpathpanel
    [2653] = { 2441, 0 }, // sonus
    [2654] = { 2442, 0 }, // corel_vncadmin
    [2655] = { 2443, 0 }, // unglue
    [2656] = { 2444, 0 }, // kana
    [2657] = { 2445, 0 }, // sns-dispatcher
    [2658] = { 2446, 0 }, // sns-admin
    [2659] = { 2447, 0 }, // sns-query
    [2660] = { 2448, 0 }, // gcmonitor
    [2661] = { 2449, 0 }, // olhost
    [2662] = { 2450, 0 }, // bintec-capi
    [2663] = { 2451, 0 }, // bintec-tapi
    [2664] = { 2452, 0 }, // patrol-mq-gm
    [2665] = { 2453, 0 }, // patrol-mq-nm
    [2666] = { 2454, 0 }, // extensis
    [2667] = { 2455, 0 }, // alarm-clock-s
    [2668] = { 2456, 0 }, // alarm-clock-c
    [2669] = { 2457, 0 }, // toad
    [2670] = { 2458, 0 }, // tve-announce
    [2671] = { 2459, 0 }, // newlixreg
    [2672] = { 2460, 0 }, // nhserver
    [2673] = { 2461, 0 }, // firstcall42
    [2674] = { 2462, 0 }, // ewnn
    [2675] = { 2463, 0 }, // ttc-etap
    [2676] = { 2464, 0 }, // simslink
    [2677] = { 2465, 0 }, // gadgetgate1way
    [2678] = { 2466, 0 }, // gadgetgate2way
    [2679] = { 2467, 0 }, // syncserverssl
    [2680] = { 2468, 0 }, // pxc-sapxom
    [2681] = { 2469, 0 }, // mpnjsomb
    [2683] = { 2470, 0 }, // ncdloadbalance
    [2684] = { 2471, 0 }, // mpnjsosv
    [2685] = { 2472, 0 }, // mpnjsocl
    [2686] = { 2473, 0 }, // mpnjsomg
    [2687] = { 2474, 0 }, // pq-lic-mgmt
    [2688] = { 2475, 0 }, // md-cg-http
    [2689] = { 2476, 0 }, // fastlynx
    [2690] = { 2477, 0 }, // hp-nnm-data
    [2691] = { 2478, 0 }, // itinternet
    [2692] = { 2479, 0 }, // admins-lms
    [2694] = { 2480, 0 }, // pwrsevent
    [2695] = { 2481, 0 }, // vspread
    [2696] = { 2482, 0 }, // unifyadmin
    [2697] = { 2483, 0 }, // oce-snmp-trap
    [2698] = { 2484, 0 }, // mck-ivpip
    [2699] = { 2485, 0 }, // csoft-plusclnt
    [2700] = { 2486, 0 }, // tqdata
    [2701] = { 2487, 0 }, // sms-rcinfo
    [2702] = { 2488, 0 }, // sms-xfer
    [2703] = { 2489, 0 }, // sms-chat
    [2704] = { 2490, 0 }, // sms-remctrl
    [2705] = { 2491, 0 }, // sds-admin
    [2706] = { 2492, 0 }, // ncdmirroring
    [2707] = { 2493, 0 }, // emcsymapiport
    [2708] = { 2494, 0 }, // banyan-net
    [2709] = { 2495, 0 }, // supermon
    [2710] = { 2496, 0 }, // sso-service
    [2711] = { 2497, 0 }, // sso-control
    [2712] = { 2498, 0 }, // aocp
    [2713] = { 2499, 0 }, // raventbs
    [2714] = { 2500, 0 }, // raventdm
    [2715] = { 2501, 0 }, // hpstgmgr2
    [2716] = { 2502, 0 }, // inova-ip-disco
    [2717] = { 2503, 0 }, // pn-requester
    [2718] = { 2504, 0 }, // pn-requester2
    [2719] = { 2505, 0 }, // scan-change
    [2720] = { 2506, 0 }, // wkars
    [2721] = { 2507, 0 }, // smart-diagnose
    [2722] = { 2508, 0 }, // proactivesrvr
    [2723] = { 2509, 0 }, // watchdog-nt
    [2724] = { 2510, 0 }, // qotps
    [2725] = { 2511, 0 }, // msolap-ptp2
    [2726] = { 2512, 0 }, // tams
    [2727] = { 2513, 0 }, // mgcp-callagent
    [2728] = { 2514, 0 }, // sqdr
    [2729] = { 2515, 0 }, // tcim-control
    [2730] = { 2516, 0 }, // nec-raidplus
    [2731] = { 2517, 0 }, // fyre-messanger
    [2732] = { 2518, 0 }, // g5m
    [2733] = { 2519, 0 }, // signet-ctf
    [2734] = { 2520, 0 }, // ccs-software
    [2735] = { 2521, 0 }, // netiq-mc
    [2736] = { 2522, 0 }, // radwiz-nms-srv
    [2737] = { 2523, 0 }, // srp-feedback
    [2738] = { 2524, 0 }, // ndl-tcp-ois-gw
    [2739] = { 2525, 0 }, // tn-timing
    [2740] = { 2526, 0 }, // alarm
    [2741] = { 2527, 0 }, // tsb
    [2742] = { 2528, 0 }, // tsb2
    [2743] = { 2529, 0 }, // murx
    [2744] = { 2530, 0 }, // honyaku
    [2745] = { 2531, 0 }, // urbisnet
    [2746] = { 2532, 0 }, // cpudpencap
    [2747] = { 2533, 0 }, // fjippol-swrly
    [2748] = { 2534, 0 }, // fjippol-polsvr
    [2749] = { 2535, 0 }, // fjippol-cnsl
    [2750] = { 2536, 0 }, // fjippol-port1
    [2751] = { 2537, 0 }, // fjippol-port2
    [2752] = { 2538, 0 }, // rsisysaccess
    [2753] = { 2539, 0 }, // de-spot
    [2754] = { 2540, 0 }, // apollo-cc
    [2755] = { 2541, 0 }, // expresspay
    [2756] = { 2542, 0 }, // simplement-tie
    [2757] = { 2543, 0 }, // cnrp
    [2758] = { 2544, 0 }, // apollo-status
    [2759] = { 2545, 0 }, // apollo-gms
    [2760] = { 2546, 0 }, // sabams
    [2761] = { 2547, 0 }, // dicom-iscl
    [2762] = { 2548, 0 }, // dicom-tls
    [2763] = { 2549, 0 }, // desktop-dna
    [2764] = { 2550, 0 }, // data-insurance
    [2765] = { 2551, 0 }, // qip-audup
    [2766] = { 2552, 0 }, // listen
    [2767] = { 2554, 0 }, // uadtc
    [2768] = { 2555, 0 }, // uacs
    [2769] = { 2556, 0 }, // exce
    [2770] = { 2557, 0 }, // veronica
    [2771] = { 2558, 0 }, // vergencecm
    [2772] = { 2559, 0 }, // auris
    [2773] = { 2560, 0 }, // rbakcup1
    [2774] = { 2561, 0 }, // rbakcup2
    [2775] = { 2562, 0 }, // smpp
    [2776] = { 2563, 0 }, // ridgeway1
    [2777] = { 2564, 0 }, // ridgeway2
    [2778] = { 2565, 0 }, // gwen-sonya
    [2779] = { 2566, 0 }, // lbc-sync
    [2780] = { 2567, 0 }, // lbc-control
    [2781] = { 2568, 0 }, // whosells
    [2782] = { 2569, 0 }, // everydayrc
    [2783] = { 2570, 0 }, // aises
    [2784] = { 2571, 0 }, // www-dev
    [2785] = { 2572, 0 }, // aic-np
    [2786] = { 2573, 0 }, // aic-oncrpc
    [2787] = { 2574, 0 }, // piccolo
    [2788] = { 2575, 0 }, // fryeserv
    [2789] = { 2576, 0 }, // media-agent
    [2790] = { 2577, 0 }, // plgproxy
    [2791] = { 2578, 0 }, // mtport-regist
    [2792] = { 2579, 0 }, // f5-globalsite
    [2793] = { 2580, 0 }, // initlsmsad
    [2795] = { 2581, 0 }, // livestats
    [2796] = { 2582, 0 }, // ac-tech
    [2797] = { 2583, 0 }, // esp-encap
    [2798] = { 2584, 0 }, // tmesis-upshot
    [2799] = { 2585, 0 }, // icon-discover
    [2800] = { 2586, 0 }, // acc-raid
    [2801] = { 2587, 0 }, // igcp
    [2802] = { 2588, 0 }, // veritas-tcp1
    [2803] = { 2590, 0 }, // btprjctrl
    [2804] = { 2591, 0 }, // dvr-esm
    [2805] = { 2592, 0 }, // wta-wsp-s
    [2806] = { 2593, 0 }, // cspuni
    [2807] = { 2594, 0 }, // cspmulti
    [2808] = { 2595, 0 }, // j-lan-p
    [2809] = { 2596, 0 }, // corbaloc
    [2810] = { 2597, 0 }, // netsteward
    [2811] = { 2598, 0 }, // gsiftp
    [2812] = { 2599, 0 }, // atmtcp
    [2813] = { 2600, 0 }, // llm-pass
    [2814] = { 2601, 0 }, // llm-csv
    [2815] = { 2602, 0 }, // lbc-measure
    [2816] = { 2603, 0 }, // lbc-watchdog
    [2817] = { 2604, 0 }, // nmsigport
    [2818] = { 2605, 0 }, // rmlnk
    [2819] = { 2606, 0 }, // fc-faultnotify
    [2820] = { 2607, 0 }, // univision
    [2821] = { 2608, 0 }, // vrts-at-port
    [2822] = { 2609, 0 }, // ka0wuc
    [2823] = { 2610, 0 }, // cqg-netlan
    [2824] = { 2611, 0 }, // cqg-netlan-1
    [2826] = { 2612, 0 }, // slc-systemlog
    [2827] = { 2613, 0 }, // slc-ctrlrloops
    [2828] = { 2614, 0 }, // itm-lm
    [2829] = { 2615, 0 }, // silkp1
    [2830] = { 2616, 0 }, // silkp2
    [2831] = { 2617, 0 }, // silkp3
    [2832] = { 2618, 0 }, // silkp4
    [2833] = { 2619, 0 }, // glishd
    [2834] = { 2620, 0 }, // evtp
    [2835] = { 2621, 0 }, // evtp-data
    [2836] = { 2622, 0 }, // catalyst
    [2837] = { 2623, 0 }, // repliweb
    [2838] = { 2624, 0 }, // starbot
    [2839] = { 2604, 0 }, // nmsigport
    [2840] = { 2625, 0 }, // l3-exprt
    [2841] = { 2626, 0 }, // l3-ranger
    [2842] = { 2627, 0 }, // l3-hawk
    [2843] = { 2628, 0 }, // pdnet
    [2844] = { 2629, 0 }, // bpcp-poll
    [2845] = { 2630, 0 }, // bpcp-trap
    [2846] = { 2631, 0 }, // aimpp-hello
    [2847] = { 2632, 0 }, // aimpp-port-req
    [2848] = { 2633, 0 }, // amt-blc-port
    [2849] = { 247, 0 }, // fxp
    [2850] = { 2634, 0 }, // metaconsole
    [2851] = { 2635, 0 }, // webemshttp
    [2852] = { 2636, 0 }, // bears-01
    [2853] = { 2637, 0 }, // ispipes
    [2854] = { 2638, 0 }, // infomover
    [2855] = { 2639, 0 }, // msrp
    [2856] = { 2640, 0 }, // cesdinv
    [2857] = { 2641, 0 }, // simctlp
    [2858] = { 2642, 0 }, // ecnp
    [2859] = { 2643, 0 }, // activememory
    [2860] = { 2644, 0 }, // dialpad-voice1
    [2861] = { 2645, 0 }, // dialpad-voice2
    [2862] = { 2646, 0 }, // ttg-protocol
    [2863] = { 2647, 0 }, // sonardata
    [2864] = { 2648, 0 }, // astromed-main
    [2865] = { 2649, 0 }, // pit-vpn
    [2866] = { 2650, 0 }, // iwlistener
    [2867] = { 2651, 0 }, // esps-portal
    [2868] = { 2652, 0 }, // npep-messaging
    [2869] = { 2653, 0 }, // icslap
    [2870] = { 2654, 0 }, // daishi
    [2871] = { 2655, 0 }, // msi-selectplay
    [2872] = { 2656, 0 }, // radix
    [2873] = { 2657, 0 }, // psrt
    [2874] = { 2658, 0 }, // dxmessagebase1
    [2875] = { 2659, 0 }, // dxmessagebase2
    [2876] = { 2660, 0 }, // sps-tunnel
    [2877] = { 2661, 0 }, // bluelance
    [2878] = { 2662, 0 }, // aap
    [2879] = { 2663, 0 }, // ucentric-ds
    [2880] = { 2664, 0 }, // synapse
    [2881] = { 2665, 0 }, // ndsp
    [2882] = { 2666, 0 }, // ndtp
    [2883] = { 2667, 0 }, // ndnp
    [2884] = { 2668, 0 }, // flashmsg
    [2885] = { 2669, 0 }, // topflow
    [2886] = { 2670, 0 }, // responselogic
    [2887] = { 2671, 0 }, // aironetddp
    [2888] = { 2672, 0 }, // spcsdlobby
    [2889] = { 2673, 0 }, // rsom
    [2890] = { 2674, 0 }, // cspclmulti
    [2891] = { 2675, 0 }, // cinegrfx-elmd
    [2892] = { 2676, 0 }, // snifferdata
    [2893] = { 2677, 0 }, // vseconnector
    [2894] = { 2678, 0 }, // abacus-remote
    [2895] = { 2679, 0 }, // natuslink
    [2896] = { 2680, 0 }, // ecovisiong6-1
    [2897] = { 2681, 0 }, // citrix-rtmp
    [2898] = { 2682, 0 }, // appliance-cfg
    [2899] = { 2683, 0 }, // powergemplus
    [2900] = { 2684, 0 }, // quicksuite
    [2901] = { 2685, 0 }, // allstorcns
    [2902] = { 2686, 0 }, // netaspi
    [2903] = { 2687, 0 }, // extensisportfolio
    [2904] = { 2689, 0 }, // m2ua
    [2905] = { 2690, 0 }, // m3ua
    [2906] = { 2691, 0 }, // caller9
    [2907] = { 2692, 0 }, // webmethods-b2b
    [2908] = { 2693, 0 }, // mao
    [2909] = { 2694, 0 }, // funk-dialout
    [2910] = { 2695, 0 }, // tdaccess
    [2911] = { 2696, 0 }, // blockade
    [2912] = { 2697, 0 }, // epicon
    [2913] = { 2698, 0 }, // boosterware
    [2914] = { 2699, 0 }, // gamelobby
    [2915] = { 2700, 0 }, // tksocket
    [2916] = { 2701, 0 }, // elvin_server
    [2917] = { 2702, 0 }, // elvin_client
    [2918] = { 2703, 0 }, // kastenchasepad
    [2919] = { 2704, 0 }, // roboer
    [2920] = { 2705, 0 }, // roboeda
    [2921] = { 2706, 0 }, // cesdcdman
    [2922] = { 2707, 0 }, // cesdcdtrn
    [2923] = { 2708, 0 }, // wta-wsp-wtp-s
    [2924] = { 2709, 0 }, // precise-vip
    [2926] = { 2710, 0 }, // mobile-file-dl
    [2927] = { 2711, 0 }, // unimobilectrl
    [2928] = { 2712, 0 }, // redstone-cpss
    [2929] = { 2713, 0 }, // amx-webadmin
    [2930] = { 2714, 0 }, // amx-weblinx
    [2931] = { 2715, 0 }, // circle-x
    [2932] = { 2716, 0 }, // incp
    [2933] = { 2717, 0 }, // 4-tieropmgw
    [2934] = { 2718, 0 }, // 4-tieropmcli
    [2935] = { 2719, 0 }, // qtp
    [2936] = { 2720, 0 }, // otpatch
    [2937] = { 2721, 0 }, // pnaconsult-lm
    [2938] = { 2722, 0 }, // sm-pas-1
    [2939] = { 2723, 0 }, // sm-pas-2
    [2940] = { 2724, 0 }, // sm-pas-3
    [2941] = { 2725, 0 }, // sm-pas-4
    [2942] = { 2726, 0 }, // sm-pas-5
    [2943] = { 2727, 0 }, // ttnrepository
    [2944] = { 2728, 0 }, // megaco-h248
    [2945] = { 2729, 0 }, // h248-binary
    [2946] = { 2730, 0 }, // fjsvmpor
    [2947] = { 2731, 0 }, // gpsd
    [2948] = { 2732, 0 }, // wap-push
    [2949] = { 2733, 0 }, // wap-pushsecure
    [2950] = { 2734, 0 }, // esip
    [2951] = { 2735, 0 }, // ottp
    [2952] = { 2736, 0 }, // mpfwsas
    [2953] = { 2737, 0 }, // ovalarmsrv
    [2954] = { 2738, 0 }, // ovalarmsrv-cmd
    [2955] = { 2739, 0 }, // csnotify
    [2956] = { 2740, 0 }, // ovrimosdbman
    [2957] = { 2741, 0 }, // jmact5
    [2958] = { 2742, 0 }, // jmact6
    [2959] = { 2743, 0 }, // rmopagt
    [2960] = { 2744, 0 }, // dfoxserver
    [2961] = { 2745, 0 }, // boldsoft-lm
    [2962] = { 2746, 0 }, // iph-policy-cli
    [2963] = { 2747, 0 }, // iph-policy-adm
    [2964] = { 2748, 0 }, // bullant-srap
    [2965] = { 2749, 0 }, // bullant-rap
    [2966] = { 2750, 0 }, // idp-infotrieve
    [2967] = { 2751, 0 }, // symantec-av
    [2968] = { 2752, 0 }, // enpp
    [2969] = { 2753, 0 }, // essp
    [2970] = { 2754, 0 }, // index-net
    [2971] = { 2755, 0 }, // netclip
    [2972] = { 2756, 0 }, // pmsm-webrctl
    [2973] = { 2757, 0 }, // svnetworks
    [2974] = { 2758, 0 }, // signal
    [2975] = { 2759, 0 }, // fjmpcm
    [2976] = { 2760, 0 }, // cns-srv-port
    [2977] = { 2761, 0 }, // ttc-etap-ns
    [2978] = { 2762, 0 }, // ttc-etap-ds
    [2979] = { 2763, 0 }, // h263-video
    [2980] = { 2764, 0 }, // wimd
    [2981] = { 2765, 0 }, // mylxamport
    [2982] = { 2766, 0 }, // iwb-whiteboard
    [2983] = { 2767, 0 }, // netplan
    [2984] = { 2768, 0 }, // hpidsadmin
    [2985] = { 2769, 0 }, // hpidsagent
    [2986] = { 2770, 0 }, // stonefalls
    [2987] = { 2771, 0 }, // identify
    [2988] = { 2772, 0 }, // hippad
    [2989] = { 2773, 0 }, // zarkov
    [2990] = { 2774, 0 }, // boscap
    [2991] = { 2775, 0 }, // wkstn-mon
    [2992] = { 2776, 0 }, // avenyo
    [2993] = { 2777, 0 }, // veritas-vis1
    [2994] = { 2778, 0 }, // veritas-vis2
    [2995] = { 2779, 0 }, // idrs
    [2996] = { 2780, 0 }, // vsixml
    [2997] = { 2781, 0 }, // rebol
    [2998] = { 2782, 0 }, // iss-realsec
    [2999] = { 2784, 0 }, // remoteware-un
    [3000] = { 2785, 0 }, // ppp
    [3001] = { 996, 0 }, // nessus
    [3002] = { 2787, 0 }, // exlm-agent
    [3003] = { 2788, 0 }, // cgms
    [3004] = { 2789, 0 }, // csoftragent
    [3005] = { 1775, 0 }, // deslogin
    [3006] = { 2791, 0 }, // deslogind
    [3007] = { 2793, 0 }, // lotusmtap
    [3008] = { 2794, 0 }, // midnight-tech
    [3009] = { 2795, 0 }, // pxc-ntfy
    [3010] = { 2796, 0 }, // gw
    [3011] = { 2798, 0 }, // trusted-web
    [3012] = { 2799, 0 }, // twsdss
    [3013] = { 2800, 0 }, // gilatskysurfer
    [3014] = { 2801, 0 }, // broker_service
    [3015] = { 2802, 0 }, // nati-dstp
    [3016] = { 2803, 0 }, // notify_srvr
    [3017] = { 2804, 0 }, // event_listener
    [3018] = { 2805, 0 }, // srvc_registry
    [3019] = { 2806, 0 }, // resource_mgr
    [3020] = { 2807, 0 }, // cifs
    [3021] = { 2808, 0 }, // agriserver
    [3022] = { 2809, 0 }, // csregagent
    [3023] = { 2810, 0 }, // magicnotes
    [3024] = { 2811, 0 }, // nds_sso
    [3025] = { 2812, 0 }, // slnp
    [3026] = { 2814, 0 }, // agri-gateway
    [3027] = { 2815, 0 }, // LiebDevMgmt_C
    [3028] = { 2816, 0 }, // LiebDevMgmt_DM
    [3029] = { 2817, 0 }, // LiebDevMgmt_A
    [3030] = { 2818, 0 }, // arepa-cas
    [3031] = { 2819, 0 }, // eppc
    [3032] = { 2820, 0 }, // redwood-chat
    [3033] = { 2821, 0 }, // pdb
    [3034] = { 2822, 0 }, // osmosis-aeea
    [3035] = { 2823, 0 }, // fjsv-gssagt
    [3036] = { 2824, 0 }, // hagel-dump
    [3037] = { 2825, 0 }, // hp-san-mgmt
    [3038] = { 2826, 0 }, // santak-ups
    [3039] = { 2827, 0 }, // cogitate
    [3040] = { 2828, 0 }, // tomato-springs
    [3041] = { 2829, 0 }, // di-traceware
    [3042] = { 2830, 0 }, // journee
    [3043] = { 2831, 0 }, // brp
    [3044] = { 640, 0 }, // epp
    [3045] = { 2812, 0 }, // slnp
    [3046] = { 2833, 0 }, // di-ase
    [3047] = { 2834, 0 }, // hlserver
    [3048] = { 2835, 0 }, // pctrader
    [3049] = { 2836, 0 }, // cfs
    [3050] = { 2837, 0 }, // gds_db
    [3051] = { 2838, 0 }, // galaxy-server
    [3052] = { 2839, 0 }, // powerchute
    [3053] = { 2841, 0 }, // dsom-server
    [3054] = { 2842, 0 }, // amt-cnf-prot
    [3055] = { 2843, 0 }, // policyserver
    [3056] = { 2844, 0 }, // cdl-server
    [3057] = { 2845, 0 }, // goahead-fldup
    [3058] = { 2846, 0 }, // videobeans
    [3059] = { 2847, 0 }, // qsoft
    [3060] = { 2848, 0 }, // interserver
    [3061] = { 2849, 0 }, // cautcpd
    [3062] = { 2850, 0 }, // ncacn-ip-tcp
    [3063] = { 2851, 0 }, // ncadg-ip-udp
    [3064] = { 2852, 0 }, // dnet-tstproxy
    [3065] = { 2854, 0 }, // slinterbase
    [3066] = { 2855, 0 }, // netattachsdmp
    [3067] = { 2856, 0 }, // fjhpjp
    [3068] = { 2857, 0 }, // ls3bcast
    [3069] = { 2858, 0 }, // ls3
    [3070] = { 2859, 0 }, // mgxswitch
    [3071] = { 2860, 0 }, // csd-mgmt-port
    [3072] = { 2861, 0 }, // csd-monitor
    [3073] = { 2862, 0 }, // vcrp
    [3074] = { 2863, 0 }, // xbox
    [3075] = { 2864, 0 }, // orbix-locator
    [3076] = { 2865, 0 }, // orbix-config
    [3077] = { 2866, 0 }, // orbix-loc-ssl
    [3078] = { 2867, 0 }, // orbix-cfg-ssl
    [3079] = { 2868, 0 }, // lv-frontpanel
    [3080] = { 2869, 0 }, // stm_pproc
    [3081] = { 2870, 0 }, // tl1-lv
    [3082] = { 2871, 0 }, // tl1-raw
    [3083] = { 2872, 0 }, // tl1-telnet
    [3084] = { 2873, 0 }, // itm-mccs
    [3085] = { 2874, 0 }, // pcihreq
    [3086] = { 2875, 0 }, // sj3
    [3087] = { 2877, 0 }, // asoki-sma
    [3088] = { 2878, 0 }, // xdtp
    [3089] = { 2879, 0 }, // ptk-alink
    [3090] = { 2880, 0 }, // stss
    [3091] = { 2881, 0 }, // 1ci-smcs
    [3093] = { 2882, 0 }, // rapidmq-center
    [3094] = { 2883, 0 }, // rapidmq-reg
    [3095] = { 2884, 0 }, // panasas
    [3096] = { 2885, 0 }, // ndl-aps
    [3097] = { 2886, 0 }, // itu-bicc-stc
    [3098] = { 2887, 0 }, // umm-port
    [3099] = { 2888, 0 }, // chmd
    [3100] = { 2889, 0 }, // opcon-xps
    [3101] = { 2890, 0 }, // hp-pxpib
    [3102] = { 2891, 0 }, // sl-mon
    [3103] = { 2892, 0 }, // autocuesmi
    [3104] = { 2893, 0 }, // autocuelog
    [3105] = { 2895, 0 }, // cardbox
    [3106] = { 2896, 0 }, // cardbox-http
    [3107] = { 2897, 0 }, // business
    [3108] = { 2898, 0 }, // geolocate
    [3109] = { 2899, 0 }, // personnel
    [3110] = { 2900, 0 }, // sim-control
    [3111] = { 2901, 0 }, // wsynch
    [3112] = { 2902, 0 }, // ksysguard
    [3113] = { 2903, 0 }, // cs-auth-svr
    [3114] = { 2904, 0 }, // ccmad
    [3115] = { 2905, 0 }, // mctet-master
    [3116] = { 2906, 0 }, // mctet-gateway
    [3117] = { 2907, 0 }, // mctet-jserv
    [3118] = { 2908, 0 }, // pkagent
    [3119] = { 2909, 0 }, // d2000kernel
    [3120] = { 2910, 0 }, // d2000webserver
    [3121] = { 2911, 0 }, // pcmk-remote
    [3122] = { 2912, 0 }, // vtr-emulator
    [3123] = { 2913, 0 }, // edix
    [3124] = { 2914, 0 }, // beacon-port
    [3125] = { 2915, 0 }, // a13-an
    [3127] = { 2916, 0 }, // ctx-bridge
    [3128] = { 2917, 0 }, // squid-http
    [3129] = { 2919, 0 }, // netport-id
    [3130] = { 2920, 0 }, // icpv2
    [3131] = { 2922, 0 }, // netbookmark
    [3132] = { 2923, 0 }, // ms-rule-engine
    [3133] = { 2924, 0 }, // prism-deploy
    [3134] = { 2925, 0 }, // ecp
    [3135] = { 2926, 0 }, // peerbook-port
    [3136] = { 2927, 0 }, // grubd
    [3137] = { 2928, 0 }, // rtnt-1
    [3138] = { 2929, 0 }, // rtnt-2
    [3139] = { 2930, 0 }, // incognitorv
    [3140] = { 2931, 0 }, // ariliamulti
    [3141] = { 2932, 0 }, // vmodem
    [3142] = { 2933, 0 }, // apt-cacher
    [3143] = { 2935, 0 }, // seaview
    [3144] = { 2936, 0 }, // tarantella
    [3145] = { 2937, 0 }, // csi-lfap
    [3146] = { 2938, 0 }, // bears-02
    [3147] = { 2939, 0 }, // rfio
    [3148] = { 2940, 0 }, // nm-game-admin
    [3149] = { 2941, 0 }, // nm-game-server
    [3150] = { 2942, 0 }, // nm-asses-admin
    [3151] = { 2943, 0 }, // nm-assessor
    [3152] = { 2944, 0 }, // feitianrockey
    [3153] = { 2945, 0 }, // s8-client-port
    [3154] = { 2946, 0 }, // ccmrmi
    [3155] = { 2947, 0 }, // jpegmpeg
    [3156] = { 2948, 0 }, // indura
    [3157] = { 2949, 0 }, // e3consultants
    [3158] = { 2950, 0 }, // stvp
    [3159] = { 2951, 0 }, // navegaweb-port
    [3160] = { 2952, 0 }, // tip-app-server
    [3161] = { 2953, 0 }, // doc1lm
    [3162] = { 2954, 0 }, // sflm
    [3163] = { 2955, 0 }, // res-sap
    [3164] = { 2956, 0 }, // imprs
    [3165] = { 2957, 0 }, // newgenpay
    [3166] = { 2958, 0 }, // sossecollector
    [3167] = { 2959, 0 }, // nowcontact
    [3168] = { 2960, 0 }, // poweronnud
    [3169] = { 2961, 0 }, // serverview-as
    [3170] = { 2962, 0 }, // serverview-asn
    [3171] = { 2963, 0 }, // serverview-gf
    [3172] = { 2964, 0 }, // serverview-rm
    [3173] = { 2965, 0 }, // serverview-icc
    [3174] = { 2966, 0 }, // armi-server
    [3175] = { 2967, 0 }, // t1-e1-over-ip
    [3176] = { 2968, 0 }, // ars-master
    [3177] = { 2969, 0 }, // phonex-port
    [3178] = { 2970, 0 }, // radclientport
    [3179] = { 2971, 0 }, // h2gf-w-2m
    [3180] = { 2972, 0 }, // mc-brk-srv
    [3181] = { 2973, 0 }, // bmcpatrolagent
    [3182] = { 2974, 0 }, // bmcpatrolrnvu
    [3183] = { 2975, 0 }, // cops-tls
    [3184] = { 2976, 0 }, // apogeex-port
    [3185] = { 2977, 0 }, // smpppd
    [3186] = { 2978, 0 }, // iiw-port
    [3187] = { 2979, 0 }, // odi-port
    [3188] = { 2980, 0 }, // brcm-comm-port
    [3189] = { 2981, 0 }, // pcle-infex
    [3190] = { 2982, 0 }, // csvr-proxy
    [3191] = { 2983, 0 }, // csvr-sslproxy
    [3192] = { 2984, 0 }, // firemonrcc
    [3193] = { 2985, 0 }, // spandataport
    [3194] = { 2986, 0 }, // magbind
    [3195] = { 2987, 0 }, // ncu-1
    [3196] = { 2988, 0 }, // ncu-2
    [3197] = { 2989, 0 }, // embrace-dp-s
    [3198] = { 2990, 0 }, // embrace-dp-c
    [3199] = { 2991, 0 }, // dmod-workspace
    [3200] = { 2992, 0 }, // tick-port
    [3201] = { 2993, 0 }, // cpq-tasksmart
    [3202] = { 2994, 0 }, // intraintra
    [3203] = { 2995, 0 }, // netwatcher-mon
    [3204] = { 2996, 0 }, // netwatcher-db
    [3205] = { 2997, 0 }, // isns
    [3206] = { 2998, 0 }, // ironmail
    [3207] = { 2999, 0 }, // vx-auth-port
    [3208] = { 3000, 0 }, // pfu-prcallback
    [3209] = { 3001, 0 }, // netwkpathengine
    [3210] = { 3002, 0 }, // flamenco-proxy
    [3211] = { 3003, 0 }, // avsecuremgmt
    [3212] = { 3004, 0 }, // surveyinst
    [3213] = { 3005, 0 }, // neon24x7
    [3214] = { 3006, 0 }, // jmq-daemon-1
    [3215] = { 3007, 0 }, // jmq-daemon-2
    [3216] = { 3008, 0 }, // ferrari-foam
    [3217] = { 3009, 0 }, // unite
    [3218] = { 3010, 0 }, // smartpackets
    [3219] = { 3011, 0 }, // wms-messenger
    [3220] = { 3012, 0 }, // xnm-ssl
    [3221] = { 3013, 0 }, // xnm-clear-text
    [3222] = { 3014, 0 }, // glbp
    [3223] = { 3015, 0 }, // digivote
    [3224] = { 3016, 0 }, // aes-discovery
    [3225] = { 3017, 0 }, // fcip-port
    [3226] = { 3018, 0 }, // isi-irp
    [3227] = { 3019, 0 }, // dwnmshttp
    [3228] = { 3020, 0 }, // dwmsgserver
    [3229] = { 3021, 0 }, // global-cd-port
    [3230] = { 3022, 0 }, // sftdst-port
    [3231] = { 3023, 0 }, // vidigo
    [3232] = { 3024, 0 }, // mdtp
    [3233] = { 3025, 0 }, // whisker
    [3234] = { 3026, 0 }, // alchemy
    [3235] = { 3027, 0 }, // mdap-port
    [3236] = { 3028, 0 }, // apparenet-ts
    [3237] = { 3029, 0 }, // apparenet-tps
    [3238] = { 3030, 0 }, // apparenet-as
    [3239] = { 3031, 0 }, // apparenet-ui
    [3240] = { 3032, 0 }, // triomotion
    [3241] = { 3033, 0 }, // sysorb
    [3242] = { 3034, 0 }, // sdp-id-port
    [3243] = { 3035, 0 }, // timelot
    [3244] = { 3036, 0 }, // onesaf
    [3245] = { 3037, 0 }, // vieo-fe
    [3246] = { 3038, 0 }, // dvt-system
    [3247] = { 3040, 0 }, // dvt-data
    [3248] = { 3041, 0 }, // procos-lm
    [3249] = { 3042, 0 }, // ssp
    [3250] = { 3043, 0 }, // hicp
    [3251] = { 3044, 0 }, // sysscanner
    [3252] = { 3045, 0 }, // dhe
    [3253] = { 3046, 0 }, // pda-data
    [3254] = { 3047, 0 }, // pda-sys
    [3255] = { 3048, 0 }, // semaphore
    [3256] = { 3049, 0 }, // cpqrpm-agent
    [3257] = { 3050, 0 }, // cpqrpm-server
    [3258] = { 3051, 0 }, // ivecon-port
    [3259] = { 3052, 0 }, // epncdp2
    [3260] = { 715, 0 }, // iscsi
    [3261] = { 3053, 0 }, // winshadow
    [3262] = { 3054, 0 }, // necp
    [3263] = { 3055, 0 }, // ecolor-imager
    [3264] = { 3056, 0 }, // ccmail
    [3265] = { 3057, 0 }, // altav-tunnel
    [3266] = { 3058, 0 }, // ns-cfg-server
    [3267] = { 3059, 0 }, // ibm-dial-out
    [3268] = { 3060, 0 }, // globalcatLDAP
    [3269] = { 3062, 0 }, // globalcatLDAPssl
    [3270] = { 3064, 0 }, // verismart
    [3271] = { 3065, 0 }, // csoft-prev
    [3272] = { 3066, 0 }, // user-manager
    [3273] = { 3067, 0 }, // sxmp
    [3274] = { 3068, 0 }, // ordinox-server
    [3275] = { 3069, 0 }, // samd
    [3276] = { 3070, 0 }, // maxim-asics
    [3277] = { 3071, 0 }, // awg-proxy
    [3278] = { 3072, 0 }, // lkcmserver
    [3279] = { 3073, 0 }, // admind
    [3280] = { 3074, 0 }, // vs-server
    [3281] = { 3075, 0 }, // sysopt
    [3282] = { 3076, 0 }, // datusorb
    [3283] = { 3077, 0 }, // netassistant
    [3284] = { 3078, 0 }, // 4talk
    [3285] = { 3079, 0 }, // plato
    [3286] = { 3080, 0 }, // e-net
    [3287] = { 3081, 0 }, // directvdata
    [3288] = { 3082, 0 }, // cops
    [3289] = { 3083, 0 }, // enpc
    [3290] = { 3084, 0 }, // caps-lm
    [3291] = { 3085, 0 }, // sah-lm
    [3292] = { 3086, 0 }, // meetingmaker
    [3293] = { 3088, 0 }, // fg-fps
    [3294] = { 3089, 0 }, // fg-gip
    [3295] = { 3090, 0 }, // dyniplookup
    [3296] = { 3091, 0 }, // rib-slm
    [3297] = { 3092, 0 }, // cytel-lm
    [3298] = { 3093, 0 }, // deskview
    [3299] = { 3094, 0 }, // saprouter
    [3300] = { 3096, 0 }, // ceph
    [3301] = { 3097, 0 }, // tarantool
    [3302] = { 3098, 0 }, // mcs-fastmail
    [3303] = { 3099, 0 }, // opsession-clnt
    [3304] = { 3100, 0 }, // opsession-srvr
    [3305] = { 3101, 0 }, // odette-ftp
    [3306] = { 3102, 0 }, // mysql
    [3307] = { 3103, 0 }, // opsession-prxy
    [3308] = { 3104, 0 }, // tns-server
    [3309] = { 3105, 0 }, // tns-adv
    [3310] = { 3106, 0 }, // dyna-access
    [3311] = { 3107, 0 }, // mcns-tel-ret
    [3312] = { 3108, 0 }, // appman-server
    [3313] = { 3109, 0 }, // uorb
    [3314] = { 3110, 0 }, // uohost
    [3315] = { 3111, 0 }, // cdid
    [3316] = { 3112, 0 }, // aicc-cmi
    [3317] = { 3113, 0 }, // vsaiport
    [3318] = { 3114, 0 }, // ssrip
    [3319] = { 3115, 0 }, // sdt-lmd
    [3320] = { 3116, 0 }, // officelink2000
    [3321] = { 3117, 0 }, // vnsstr
    [3322] = { 3118, 0 }, // active-net
    [3323] = { 3118, 0 }, // active-net
    [3324] = { 3118, 0 }, // active-net
    [3325] = { 3118, 0 }, // active-net
    [3326] = { 3119, 0 }, // sftu
    [3327] = { 3120, 0 }, // bbars
    [3328] = { 3121, 0 }, // egptlm
    [3329] = { 3122, 0 }, // hp-device-disc
    [3330] = { 3123, 0 }, // mcs-calypsoicf
    [3331] = { 3124, 0 }, // mcs-messaging
    [3332] = { 3125, 0 }, // mcs-mailsvr
    [3333] = { 3126, 0 }, // dec-notes
    [3334] = { 3127, 0 }, // directv-web
    [3335] = { 3128, 0 }, // directv-soft
    [3336] = { 3129, 0 }, // directv-tick
    [3337] = { 3130, 0 }, // directv-catlg
    [3338] = { 3131, 0 }, // anet-b
    [3339] = { 3132, 0 }, // anet-l
    [3340] = { 3133, 0 }, // anet-m
    [3341] = { 3134, 0 }, // anet-h
    [3342] = { 3135, 0 }, // webtie
    [3343] = { 3136, 0 }, // ms-cluster-net
    [3344] = { 3137, 0 }, // bnt-manager
    [3345] = { 3138, 0 }, // influence
    [3346] = { 3139, 0 }, // trnsprntproxy
    [3347] = { 3140, 0 }, // phoenix-rpc
    [3348] = { 3141, 0 }, // pangolin-laser
    [3349] = { 3142, 0 }, // chevinservices
    [3350] = { 3143, 0 }, // findviatv
    [3351] = { 3144, 0 }, // btrieve
    [3352] = { 3145, 0 }, // ssql
    [3353] = { 3146, 0 }, // fatpipe
    [3354] = { 3147, 0 }, // suitjd
    [3355] = { 3148, 0 }, // ordinox-dbase
    [3356] = { 3149, 0 }, // upnotifyps
    [3357] = { 3150, 0 }, // adtech-test
    [3358] = { 3151, 0 }, // mpsysrmsvr
    [3359] = { 3152, 0 }, // wg-netforce
    [3360] = { 3153, 0 }, // kv-server
    [3361] = { 3154, 0 }, // kv-agent
    [3362] = { 3155, 0 }, // dj-ilm
    [3363] = { 3156, 0 }, // nati-vi-server
    [3364] = { 376, 0 }, // creativeserver
    [3365] = { 377, 0 }, // contentserver
    [3366] = { 378, 0 }, // creativepartnr
    [3367] = { 3157, 0 }, // satvid-datalnk
    [3368] = { 3157, 0 }, // satvid-datalnk
    [3369] = { 3157, 0 }, // satvid-datalnk
    [3370] = { 3157, 0 }, // satvid-datalnk
    [3371] = { 3157, 0 }, // satvid-datalnk
    [3372] = { 3158, 0 }, // msdtc
    [3373] = { 3160, 0 }, // lavenir-lm
    [3374] = { 3161, 0 }, // cluster-disc
    [3375] = { 3162, 0 }, // vsnm-agent
    [3376] = { 3163, 0 }, // cdbroker
    [3377] = { 3164, 0 }, // cogsys-lm
    [3378] = { 3165, 0 }, // wsicopy
    [3379] = { 3166, 0 }, // socorfs
    [3380] = { 3167, 0 }, // sns-channels
    [3381] = { 3168, 0 }, // geneous
    [3382] = { 3169, 0 }, // fujitsu-neat
    [3383] = { 3170, 0 }, // esp-lm
    [3384] = { 3171, 0 }, // hp-clic
    [3385] = { 3172, 0 }, // qnxnetman
    [3386] = { 3173, 0 }, // gprs-data
    [3387] = { 3175, 0 }, // backroomnet
    [3388] = { 3176, 0 }, // cbserver
    [3389] = { 3177, 0 }, // ms-wbt-server
    [3390] = { 3178, 0 }, // dsc
    [3391] = { 3179, 0 }, // savant
    [3392] = { 3180, 0 }, // efi-lm
    [3393] = { 3181, 0 }, // d2k-tapestry1
    [3394] = { 3182, 0 }, // d2k-tapestry2
    [3395] = { 3183, 0 }, // dyna-lm
    [3396] = { 3184, 0 }, // printer_agent
    [3397] = { 3185, 0 }, // saposs
    [3398] = { 3187, 0 }, // sapcomm
    [3399] = { 3189, 0 }, // sapeps
    [3400] = { 3191, 0 }, // csms2
    [3401] = { 3192, 0 }, // filecast
    [3402] = { 3194, 0 }, // fxaengine-net
    [3405] = { 3195, 0 }, // nokia-ann-ch1
    [3406] = { 3196, 0 }, // nokia-ann-ch2
    [3407] = { 3197, 0 }, // ldap-admin
    [3408] = { 3198, 0 }, // BESApi
    [3409] = { 3199, 0 }, // networklens
    [3410] = { 3200, 0 }, // networklenss
    [3411] = { 3201, 0 }, // biolink-auth
    [3412] = { 3202, 0 }, // xmlblaster
    [3413] = { 3203, 0 }, // svnet
    [3414] = { 3204, 0 }, // wip-port
    [3415] = { 3205, 0 }, // bcinameservice
    [3416] = { 3206, 0 }, // commandport
    [3417] = { 3207, 0 }, // csvr
    [3418] = { 3208, 0 }, // rnmap
    [3419] = { 3209, 0 }, // softaudit
    [3420] = { 3210, 0 }, // ifcp-port
    [3421] = { 3211, 0 }, // bmap
    [3422] = { 3212, 0 }, // rusb-sys-port
    [3423] = { 3213, 0 }, // xtrm
    [3424] = { 3214, 0 }, // xtrms
    [3425] = { 3215, 0 }, // agps-port
    [3426] = { 3216, 0 }, // arkivio
    [3427] = { 3217, 0 }, // websphere-snmp
    [3428] = { 3218, 0 }, // twcss
    [3429] = { 3219, 0 }, // gcsp
    [3430] = { 3220, 0 }, // ssdispatch
    [3431] = { 3221, 0 }, // ndl-als
    [3432] = { 3222, 0 }, // osdcp
    [3433] = { 3223, 0 }, // alta-smp
    [3434] = { 3224, 0 }, // opencm
    [3435] = { 3225, 0 }, // pacom
    [3436] = { 3226, 0 }, // gc-config
    [3437] = { 3227, 0 }, // autocueds
    [3438] = { 3228, 0 }, // spiral-admin
    [3439] = { 3229, 0 }, // hri-port
    [3440] = { 3230, 0 }, // ans-console
    [3441] = { 3231, 0 }, // connect-client
    [3442] = { 3232, 0 }, // connect-server
    [3443] = { 3233, 0 }, // ov-nnm-websrv
    [3444] = { 3234, 0 }, // denali-server
    [3445] = { 3235, 0 }, // monp
    [3446] = { 3236, 0 }, // 3comfaxrpc
    [3447] = { 3237, 0 }, // directnet
    [3448] = { 3238, 0 }, // dnc-port
    [3449] = { 3239, 0 }, // hotu-chat
    [3450] = { 3240, 0 }, // castorproxy
    [3451] = { 3241, 0 }, // asam
    [3452] = { 3242, 0 }, // sabp-signal
    [3453] = { 3243, 0 }, // pscupd
    [3454] = { 3244, 0 }, // mira
    [3455] = { 3245, 0 }, // prsvp
    [3456] = { 3246, 0 }, // vat
    [3457] = { 3248, 0 }, // vat-control
    [3458] = { 3249, 0 }, // d3winosfi
    [3459] = { 3250, 0 }, // integral
    [3460] = { 3251, 0 }, // edm-manager
    [3461] = { 3252, 0 }, // edm-stager
    [3462] = { 3253, 0 }, // track
    [3463] = { 3255, 0 }, // edm-adm-notify
    [3464] = { 3256, 0 }, // edm-mgr-sync
    [3465] = { 3257, 0 }, // edm-mgr-cntrl
    [3466] = { 3258, 0 }, // workflow
    [3467] = { 3259, 0 }, // rcst
    [3468] = { 3260, 0 }, // ttcmremotectrl
    [3469] = { 3261, 0 }, // pluribus
    [3470] = { 3262, 0 }, // jt400
    [3471] = { 3263, 0 }, // jt400-ssl
    [3472] = { 3264, 0 }, // jaugsremotec-1
    [3473] = { 3265, 0 }, // jaugsremotec-2
    [3474] = { 3266, 0 }, // ttntspauto
    [3475] = { 3267, 0 }, // genisar-port
    [3476] = { 3268, 0 }, // nppmp
    [3477] = { 3269, 0 }, // ecomm
    [3478] = { 3270, 0 }, // stun
    [3479] = { 3271, 0 }, // twrpc
    [3480] = { 3272, 0 }, // plethora
    [3481] = { 3273, 0 }, // cleanerliverc
    [3482] = { 3274, 0 }, // vulture
    [3483] = { 3275, 0 }, // slim-devices
    [3484] = { 3276, 0 }, // gbs-stp
    [3485] = { 3277, 0 }, // celatalk
    [3486] = { 3278, 0 }, // ifsf-hb-port
    [3487] = { 3279, 0 }, // ltctcp
    [3488] = { 3281, 0 }, // fs-rh-srv
    [3489] = { 3282, 0 }, // dtp-dia
    [3490] = { 3283, 0 }, // colubris
    [3491] = { 3284, 0 }, // swr-port
    [3492] = { 3285, 0 }, // tvdumtray-port
    [3493] = { 3286, 0 }, // nut
    [3494] = { 3287, 0 }, // ibm3494
    [3495] = { 3288, 0 }, // seclayer-tcp
    [3496] = { 3289, 0 }, // seclayer-tls
    [3497] = { 3290, 0 }, // ipether232port
    [3498] = { 3291, 0 }, // dashpas-port
    [3499] = { 3292, 0 }, // sccip-media
    [3500] = { 3293, 0 }, // rtmp-port
    [3501] = { 3294, 0 }, // isoft-p2p
    [3502] = { 3295, 0 }, // avinstalldisc
    [3503] = { 3296, 0 }, // lsp-ping
    [3504] = { 3297, 0 }, // ironstorm
    [3505] = { 3298, 0 }, // ccmcomm
    [3506] = { 3299, 0 }, // apc-3506
    [3507] = { 3300, 0 }, // nesh-broker
    [3508] = { 3301, 0 }, // interactionweb
    [3509] = { 3302, 0 }, // vt-ssl
    [3510] = { 3303, 0 }, // xss-port
    [3511] = { 3304, 0 }, // webmail-2
    [3512] = { 3305, 0 }, // aztec
    [3513] = { 3306, 0 }, // arcpd
    [3514] = { 3307, 0 }, // must-p2p
    [3515] = { 3308, 0 }, // must-backplane
    [3516] = { 3309, 0 }, // smartcard-port
    [3517] = { 3310, 0 }, // 802-11-iapp
    [3518] = { 3311, 0 }, // artifact-msg
    [3519] = { 3312, 0 }, // nvmsgd
    [3520] = { 3314, 0 }, // galileolog
    [3521] = { 3315, 0 }, // mc3ss
    [3522] = { 3316, 0 }, // nssocketport
    [3523] = { 3317, 0 }, // odeumservlink
    [3524] = { 3318, 0 }, // ecmport
    [3525] = { 3319, 0 }, // eisport
    [3526] = { 3320, 0 }, // starquiz-port
    [3527] = { 3321, 0 }, // beserver-msg-q
    [3528] = { 3322, 0 }, // jboss-iiop
    [3529] = { 3323, 0 }, // jboss-iiop-ssl
    [3530] = { 3324, 0 }, // gf
    [3531] = { 3325, 0 }, // peerenabler
    [3532] = { 3326, 0 }, // raven-rmp
    [3533] = { 3327, 0 }, // raven-rdp
    [3534] = { 3328, 0 }, // urld-port
    [3535] = { 3329, 0 }, // ms-la
    [3536] = { 3330, 0 }, // snac
    [3537] = { 3331, 0 }, // ni-visa-remote
    [3538] = { 3332, 0 }, // ibm-diradm
    [3539] = { 3333, 0 }, // ibm-diradm-ssl
    [3540] = { 3334, 0 }, // pnrp-port
    [3541] = { 3335, 0 }, // voispeed-port
    [3542] = { 3336, 0 }, // hacl-monitor
    [3543] = { 3337, 0 }, // qftest-lookup
    [3544] = { 3338, 0 }, // teredo
    [3545] = { 3339, 0 }, // camac
    [3547] = { 3340, 0 }, // symantec-sim
    [3548] = { 3341, 0 }, // interworld
    [3549] = { 3342, 0 }, // tellumat-nms
    [3550] = { 3343, 0 }, // ssmpp
    [3551] = { 3344, 0 }, // apcupsd
    [3552] = { 3345, 0 }, // taserver
    [3553] = { 3346, 0 }, // rbr-discovery
    [3554] = { 3347, 0 }, // questnotify
    [3555] = { 3348, 0 }, // razor
    [3556] = { 3349, 0 }, // sky-transport
    [3557] = { 3350, 0 }, // personalos-001
    [3558] = { 3351, 0 }, // mcp-port
    [3559] = { 3352, 0 }, // cctv-port
    [3560] = { 3353, 0 }, // iniserve-port
    [3561] = { 3354, 0 }, // bmc-onekey
    [3562] = { 3355, 0 }, // sdbproxy
    [3563] = { 3356, 0 }, // watcomdebug
    [3564] = { 3357, 0 }, // esimport
    [3565] = { 3358, 0 }, // m2pa
    [3566] = { 3359, 0 }, // quest-data-hub
    [3567] = { 3360, 0 }, // oap
    [3568] = { 3361, 0 }, // oap-s
    [3569] = { 3362, 0 }, // mbg-ctrl
    [3570] = { 3363, 0 }, // mccwebsvr-port
    [3571] = { 3364, 0 }, // megardsvr-port
    [3572] = { 3365, 0 }, // megaregsvrport
    [3573] = { 3366, 0 }, // tag-ups-1
    [3574] = { 3367, 0 }, // dmaf-server
    [3575] = { 3369, 0 }, // ccm-port
    [3576] = { 3370, 0 }, // cmc-port
    [3577] = { 3371, 0 }, // config-port
    [3578] = { 3372, 0 }, // data-port
    [3579] = { 3373, 0 }, // ttat3lb
    [3580] = { 3374, 0 }, // nati-svrloc
    [3581] = { 3375, 0 }, // kfxaclicensing
    [3582] = { 3376, 0 }, // press
    [3583] = { 3377, 0 }, // canex-watch
    [3584] = { 3378, 0 }, // u-dbap
    [3585] = { 3379, 0 }, // emprise-lls
    [3586] = { 3380, 0 }, // emprise-lsc
    [3587] = { 3381, 0 }, // p2pgroup
    [3588] = { 3382, 0 }, // sentinel
    [3589] = { 3383, 0 }, // isomair
    [3590] = { 3384, 0 }, // wv-csp-sms
    [3591] = { 3385, 0 }, // gtrack-server
    [3592] = { 3386, 0 }, // gtrack-ne
    [3593] = { 3387, 0 }, // bpmd
    [3594] = { 3388, 0 }, // mediaspace
    [3595] = { 3389, 0 }, // shareapp
    [3596] = { 3390, 0 }, // iw-mmogame
    [3597] = { 3391, 0 }, // a14
    [3598] = { 3392, 0 }, // a15
    [3599] = { 3393, 0 }, // quasar-server
    [3600] = { 3394, 0 }, // trap-daemon
    [3601] = { 3395, 0 }, // visinet-gui
    [3602] = { 3396, 0 }, // infiniswitchcl
    [3603] = { 3397, 0 }, // int-rcv-cntrl
    [3604] = { 3398, 0 }, // bmc-jmx-port
    [3605] = { 3399, 0 }, // comcam-io
    [3606] = { 3400, 0 }, // splitlock
    [3607] = { 3401, 0 }, // precise-i3
    [3608] = { 3402, 0 }, // trendchip-dcp
    [3609] = { 3403, 0 }, // cpdi-pidas-cm
    [3610] = { 3404, 0 }, // echonet
    [3611] = { 3405, 0 }, // six-degrees
    [3612] = { 3406, 0 }, // hp-dataprotect
    [3613] = { 3407, 0 }, // alaris-disc
    [3614] = { 3408, 0 }, // sigma-port
    [3615] = { 3409, 0 }, // start-network
    [3616] = { 3410, 0 }, // cd3o-protocol
    [3617] = { 3411, 0 }, // sharp-server
    [3618] = { 3412, 0 }, // aairnet-1
    [3619] = { 3413, 0 }, // aairnet-2
    [3620] = { 3414, 0 }, // ep-pcp
    [3621] = { 3415, 0 }, // ep-nsp
    [3622] = { 3416, 0 }, // ff-lr-port
    [3623] = { 3417, 0 }, // haipe-discover
    [3624] = { 3418, 0 }, // dist-upgrade
    [3625] = { 3419, 0 }, // volley
    [3626] = { 3420, 0 }, // bvcdaemon-port
    [3627] = { 3421, 0 }, // jamserverport
    [3628] = { 3422, 0 }, // ept-machine
    [3629] = { 3423, 0 }, // escvpnet
    [3630] = { 3424, 0 }, // cs-remote-db
    [3631] = { 3425, 0 }, // cs-services
    [3632] = { 3426, 0 }, // distccd
    [3633] = { 3428, 0 }, // wacp
    [3634] = { 3429, 0 }, // hlibmgr
    [3635] = { 3430, 0 }, // sdo
    [3636] = { 3431, 0 }, // servistaitsm
    [3637] = { 3432, 0 }, // scservp
    [3638] = { 3433, 0 }, // ehp-backup
    [3639] = { 3434, 0 }, // xap-ha
    [3640] = { 3435, 0 }, // netplay-port1
    [3641] = { 3436, 0 }, // netplay-port2
    [3642] = { 3437, 0 }, // juxml-port
    [3643] = { 3438, 0 }, // audiojuggler
    [3644] = { 3439, 0 }, // ssowatch
    [3645] = { 3440, 0 }, // cyc
    [3646] = { 3441, 0 }, // xss-srv-port
    [3647] = { 3442, 0 }, // splitlock-gw
    [3648] = { 3443, 0 }, // fjcp
    [3649] = { 3444, 0 }, // nmmp
    [3650] = { 3445, 0 }, // prismiq-plugin
    [3651] = { 3446, 0 }, // xrpc-registry
    [3652] = { 3447, 0 }, // vxcrnbuport
    [3653] = { 3448, 0 }, // tsp
    [3654] = { 3449, 0 }, // vaprtm
    [3655] = { 3450, 0 }, // abatemgr
    [3656] = { 3451, 0 }, // abatjss
    [3657] = { 3452, 0 }, // immedianet-bcn
    [3658] = { 3453, 0 }, // ps-ams
    [3659] = { 3454, 0 }, // apple-sasl
    [3660] = { 3455, 0 }, // can-nds-ssl
    [3661] = { 3456, 0 }, // can-ferret-ssl
    [3662] = { 3457, 0 }, // pserver
    [3663] = { 3458, 0 }, // dtp
    [3664] = { 3459, 0 }, // ups-engine
    [3665] = { 3460, 0 }, // ent-engine
    [3666] = { 3461, 0 }, // eserver-pap
    [3667] = { 3462, 0 }, // infoexch
    [3668] = { 3463, 0 }, // dell-rm-port
    [3669] = { 3464, 0 }, // casanswmgmt
    [3670] = { 3465, 0 }, // smile
    [3671] = { 3466, 0 }, // efcp
    [3672] = { 3467, 0 }, // lispworks-orb
    [3673] = { 3468, 0 }, // mediavault-gui
    [3674] = { 3469, 0 }, // wininstall-ipc
    [3675] = { 3470, 0 }, // calltrax
    [3676] = { 3471, 0 }, // va-pacbase
    [3677] = { 3472, 0 }, // roverlog
    [3678] = { 3473, 0 }, // ipr-dglt
    [3679] = { 3474, 0 }, // newton-dock
    [3680] = { 3475, 0 }, // npds-tracker
    [3681] = { 3476, 0 }, // bts-x73
    [3682] = { 3477, 0 }, // cas-mapi
    [3683] = { 3478, 0 }, // bmc-ea
    [3684] = { 3479, 0 }, // faxstfx-port
    [3685] = { 3480, 0 }, // dsx-agent
    [3686] = { 3481, 0 }, // tnmpv2
    [3687] = { 3482, 0 }, // simple-push
    [3688] = { 3483, 0 }, // simple-push-s
    [3689] = { 3484, 0 }, // rendezvous
    [3690] = { 3486, 0 }, // svn
    [3691] = { 3487, 0 }, // magaya-network
    [3692] = { 3488, 0 }, // intelsync
    [3693] = { 3489, 0 }, // easl
    [3695] = { 3490, 0 }, // bmc-data-coll
    [3696] = { 3491, 0 }, // telnetcpcd
    [3697] = { 3492, 0 }, // nw-license
    [3698] = { 3493, 0 }, // sagectlpanel
    [3699] = { 3494, 0 }, // kpn-icw
    [3700] = { 3495, 0 }, // lrs-paging
    [3701] = { 3496, 0 }, // netcelera
    [3702] = { 3497, 0 }, // ws-discovery
    [3703] = { 3498, 0 }, // adobeserver-3
    [3704] = { 3499, 0 }, // adobeserver-4
    [3705] = { 3500, 0 }, // adobeserver-5
    [3706] = { 3501, 0 }, // rt-event
    [3707] = { 3502, 0 }, // rt-event-s
    [3708] = { 3503, 0 }, // sun-as-iiops
    [3709] = { 3504, 0 }, // ca-idms
    [3710] = { 3505, 0 }, // portgate-auth
    [3711] = { 3506, 0 }, // edb-server2
    [3712] = { 3507, 0 }, // sentinel-ent
    [3713] = { 3508, 0 }, // tftps
    [3714] = { 3509, 0 }, // delos-dms
    [3715] = { 3510, 0 }, // anoto-rendezv
    [3716] = { 3511, 0 }, // wv-csp-sms-cir
    [3717] = { 3512, 0 }, // wv-csp-udp-cir
    [3718] = { 3513, 0 }, // opus-services
    [3719] = { 3514, 0 }, // itelserverport
    [3720] = { 3515, 0 }, // ufastro-instr
    [3721] = { 3516, 0 }, // xsync
    [3722] = { 3517, 0 }, // xserveraid
    [3723] = { 3518, 0 }, // sychrond
    [3724] = { 3519, 0 }, // blizwow
    [3725] = { 3520, 0 }, // na-er-tip
    [3726] = { 3521, 0 }, // array-manager
    [3727] = { 3522, 0 }, // e-mdu
    [3728] = { 3523, 0 }, // e-woa
    [3729] = { 3524, 0 }, // fksp-audit
    [3730] = { 3525, 0 }, // client-ctrl
    [3731] = { 3526, 0 }, // smap
    [3732] = { 3527, 0 }, // m-wnn
    [3733] = { 3528, 0 }, // multip-msg
    [3734] = { 3529, 0 }, // synel-data
    [3735] = { 3530, 0 }, // pwdis
    [3736] = { 3531, 0 }, // rs-rmi
    [3737] = { 3532, 0 }, // xpanel
    [3738] = { 3533, 0 }, // versatalk
    [3739] = { 3534, 0 }, // launchbird-lm
    [3740] = { 3535, 0 }, // heartbeat
    [3741] = { 3536, 0 }, // wysdma
    [3742] = { 3537, 0 }, // cst-port
    [3743] = { 3538, 0 }, // ipcs-command
    [3744] = { 3539, 0 }, // sasg
    [3745] = { 3540, 0 }, // gw-call-port
    [3746] = { 3541, 0 }, // linktest
    [3747] = { 3542, 0 }, // linktest-s
    [3748] = { 3543, 0 }, // webdata
    [3749] = { 3544, 0 }, // cimtrak
    [3750] = { 3545, 0 }, // cbos-ip-port
    [3751] = { 3546, 0 }, // gprs-cube
    [3752] = { 3547, 0 }, // vipremoteagent
    [3753] = { 3548, 0 }, // nattyserver
    [3754] = { 3549, 0 }, // timestenbroker
    [3755] = { 3550, 0 }, // sas-remote-hlp
    [3756] = { 3551, 0 }, // canon-capt
    [3757] = { 3552, 0 }, // grf-port
    [3758] = { 3553, 0 }, // apw-registry
    [3759] = { 3554, 0 }, // exapt-lmgr
    [3760] = { 3555, 0 }, // adtempusclient
    [3761] = { 3556, 0 }, // gsakmp
    [3762] = { 3557, 0 }, // gbs-smp
    [3763] = { 3558, 0 }, // xo-wave
    [3764] = { 3559, 0 }, // mni-prot-rout
    [3765] = { 3560, 0 }, // rtraceroute
    [3766] = { 3561, 0 }, // sitewatch-s
    [3767] = { 3562, 0 }, // listmgr-port
    [3768] = { 3563, 0 }, // rblcheckd
    [3769] = { 3564, 0 }, // haipe-otnk
    [3770] = { 3565, 0 }, // cindycollab
    [3771] = { 3566, 0 }, // paging-port
    [3772] = { 3567, 0 }, // ctp
    [3773] = { 3568, 0 }, // ctdhercules
    [3774] = { 3569, 0 }, // zicom
    [3775] = { 3570, 0 }, // ispmmgr
    [3776] = { 3571, 0 }, // dvcprov-port
    [3777] = { 3572, 0 }, // jibe-eb
    [3778] = { 3573, 0 }, // c-h-it-port
    [3779] = { 3574, 0 }, // cognima
    [3780] = { 3575, 0 }, // nnp
    [3781] = { 3576, 0 }, // abcvoice-port
    [3782] = { 3577, 0 }, // iso-tp0s
    [3783] = { 3578, 0 }, // bim-pem
    [3784] = { 3579, 0 }, // bfd-control
    [3785] = { 3580, 0 }, // bfd-echo
    [3786] = { 3581, 0 }, // upstriggervsw
    [3787] = { 3582, 0 }, // fintrx
    [3788] = { 3583, 0 }, // isrp-port
    [3789] = { 3584, 0 }, // remotedeploy
    [3790] = { 3585, 0 }, // quickbooksrds
    [3791] = { 3586, 0 }, // tvnetworkvideo
    [3792] = { 3587, 0 }, // sitewatch
    [3793] = { 3588, 0 }, // dcsoftware
    [3794] = { 3589, 0 }, // jaus
    [3795] = { 3590, 0 }, // myblast
    [3796] = { 3591, 0 }, // spw-dialer
    [3797] = { 3592, 0 }, // idps
    [3798] = { 3593, 0 }, // minilock
    [3799] = { 3594, 0 }, // radius-dynauth
    [3800] = { 3595, 0 }, // pwgpsi
    [3801] = { 3596, 0 }, // ibm-mgr
    [3802] = { 3597, 0 }, // vhd
    [3803] = { 3598, 0 }, // soniqsync
    [3804] = { 3599, 0 }, // iqnet-port
    [3805] = { 3600, 0 }, // tcpdataserver
    [3806] = { 3601, 0 }, // wsmlb
    [3807] = { 3602, 0 }, // spugna
    [3808] = { 3603, 0 }, // sun-as-iiops-ca
    [3809] = { 3604, 0 }, // apocd
    [3810] = { 3605, 0 }, // wlanauth
    [3811] = { 3606, 0 }, // amp
    [3812] = { 3607, 0 }, // neto-wol-server
    [3813] = { 3608, 0 }, // rap-ip
    [3814] = { 3609, 0 }, // neto-dcs
    [3815] = { 3610, 0 }, // lansurveyorxml
    [3816] = { 3611, 0 }, // sunlps-http
    [3817] = { 3612, 0 }, // tapeware
    [3818] = { 3613, 0 }, // crinis-hb
    [3819] = { 3614, 0 }, // epl-slp
    [3820] = { 3615, 0 }, // scp
    [3821] = { 3616, 0 }, // pmcp
    [3822] = { 3617, 0 }, // acp-discovery
    [3823] = { 3618, 0 }, // acp-conduit
    [3824] = { 3619, 0 }, // acp-policy
    [3825] = { 3620, 0 }, // ffserver
    [3826] = { 3621, 0 }, // wormux
    [3827] = { 3622, 0 }, // netmpi
    [3828] = { 3623, 0 }, // neteh
    [3829] = { 3624, 0 }, // neteh-ext
    [3830] = { 3625, 0 }, // cernsysmgmtagt
    [3831] = { 3626, 0 }, // dvapps
    [3832] = { 3627, 0 }, // xxnetserver
    [3833] = { 3628, 0 }, // aipn-auth
    [3834] = { 3629, 0 }, // spectardata
    [3835] = { 3630, 0 }, // spectardb
    [3836] = { 3631, 0 }, // markem-dcp
    [3837] = { 3632, 0 }, // mkm-discovery
    [3838] = { 3633, 0 }, // sos
    [3839] = { 3634, 0 }, // amx-rms
    [3840] = { 3635, 0 }, // flirtmitmir
    [3841] = { 3636, 0 }, // zfirm-shiprush3
    [3842] = { 3637, 0 }, // nhci
    [3843] = { 3638, 0 }, // quest-agent
    [3844] = { 3639, 0 }, // rnm
    [3845] = { 3640, 0 }, // v-one-spp
    [3846] = { 3641, 0 }, // an-pcp
    [3847] = { 3642, 0 }, // msfw-control
    [3848] = { 3643, 0 }, // item
    [3849] = { 3644, 0 }, // spw-dnspreload
    [3850] = { 3645, 0 }, // qtms-bootstrap
    [3851] = { 3646, 0 }, // spectraport
    [3852] = { 3647, 0 }, // sse-app-config
    [3853] = { 3648, 0 }, // sscan
    [3854] = { 3649, 0 }, // stryker-com
    [3855] = { 3650, 0 }, // opentrac
    [3856] = { 3651, 0 }, // informer
    [3857] = { 3652, 0 }, // trap-port
    [3858] = { 3653, 0 }, // trap-port-mom
    [3859] = { 3654, 0 }, // nav-port
    [3860] = { 3655, 0 }, // sasp
    [3861] = { 3656, 0 }, // winshadow-hd
    [3862] = { 3657, 0 }, // giga-pocket
    [3863] = { 3658, 0 }, // asap-sctp
    [3864] = { 3660, 0 }, // asap-sctp-tls
    [3865] = { 3662, 0 }, // xpl
    [3866] = { 3663, 0 }, // dzdaemon
    [3867] = { 3664, 0 }, // dzoglserver
    [3868] = { 3665, 0 }, // diameter
    [3869] = { 3666, 0 }, // ovsam-mgmt
    [3870] = { 3667, 0 }, // ovsam-d-agent
    [3871] = { 3668, 0 }, // avocent-adsap
    [3872] = { 3669, 0 }, // oem-agent
    [3873] = { 3670, 0 }, // fagordnc
    [3874] = { 3671, 0 }, // sixxsconfig
    [3875] = { 3672, 0 }, // pnbscada
    [3876] = { 3673, 0 }, // dl_agent
    [3877] = { 3674, 0 }, // xmpcr-interface
    [3878] = { 3675, 0 }, // fotogcad
    [3879] = { 3676, 0 }, // appss-lm
    [3880] = { 3677, 0 }, // igrs
    [3881] = { 3678, 0 }, // idac
    [3882] = { 3679, 0 }, // msdts1
    [3883] = { 3680, 0 }, // vrpn
    [3884] = { 3681, 0 }, // softrack-meter
    [3885] = { 3682, 0 }, // topflow-ssl
    [3886] = { 3683, 0 }, // nei-management
    [3887] = { 3684, 0 }, // ciphire-data
    [3888] = { 3685, 0 }, // ciphire-serv
    [3889] = { 3686, 0 }, // dandv-tester
    [3890] = { 3687, 0 }, // ndsconnect
    [3891] = { 3688, 0 }, // rtc-pm-port
    [3892] = { 3689, 0 }, // pcc-image-port
    [3893] = { 3690, 0 }, // cgi-starapi
    [3894] = { 3691, 0 }, // syam-agent
    [3895] = { 3692, 0 }, // syam-smc
    [3896] = { 3693, 0 }, // sdo-tls
    [3897] = { 3694, 0 }, // sdo-ssh
    [3898] = { 3695, 0 }, // senip
    [3899] = { 3696, 0 }, // itv-control
    [3900] = { 1138, 0 }, // udt_os
    [3901] = { 3697, 0 }, // nimsh
    [3902] = { 3698, 0 }, // nimaux
    [3903] = { 3699, 0 }, // charsetmgr
    [3904] = { 3700, 0 }, // omnilink-port
    [3905] = { 3701, 0 }, // mupdate
    [3906] = { 3702, 0 }, // topovista-data
    [3907] = { 3703, 0 }, // imoguia-port
    [3908] = { 3704, 0 }, // hppronetman
    [3909] = { 3705, 0 }, // surfcontrolcpa
    [3910] = { 3706, 0 }, // prnrequest
    [3911] = { 3707, 0 }, // prnstatus
    [3912] = { 3708, 0 }, // gbmt-stars
    [3913] = { 3709, 0 }, // listcrt-port
    [3914] = { 3710, 0 }, // listcrt-port-2
    [3915] = { 3711, 0 }, // agcat
    [3916] = { 3712, 0 }, // wysdmc
    [3917] = { 3713, 0 }, // aftmux
    [3918] = { 3714, 0 }, // pktcablemmcops
    [3919] = { 3715, 0 }, // hyperip
    [3920] = { 3716, 0 }, // exasoftport1
    [3921] = { 3717, 0 }, // herodotus-net
    [3922] = { 3718, 0 }, // sor-update
    [3923] = { 3719, 0 }, // symb-sb-port
    [3924] = { 3720, 0 }, // mpl-gprs-port
    [3925] = { 3721, 0 }, // zmp
    [3926] = { 3722, 0 }, // winport
    [3927] = { 3723, 0 }, // natdataservice
    [3928] = { 3724, 0 }, // netboot-pxe
    [3929] = { 3725, 0 }, // smauth-port
    [3930] = { 3726, 0 }, // syam-webserver
    [3931] = { 3727, 0 }, // msr-plugin-port
    [3932] = { 3728, 0 }, // dyn-site
    [3933] = { 3729, 0 }, // plbserve-port
    [3934] = { 3730, 0 }, // sunfm-port
    [3935] = { 3731, 0 }, // sdp-portmapper
    [3936] = { 3732, 0 }, // mailprox
    [3937] = { 3733, 0 }, // dvbservdsc
    [3938] = { 3734, 0 }, // dbcontrol_agent
    [3939] = { 3735, 0 }, // aamp
    [3940] = { 3736, 0 }, // xecp-node
    [3941] = { 3737, 0 }, // homeportal-web
    [3942] = { 3738, 0 }, // srdp
    [3943] = { 3739, 0 }, // tig
    [3944] = { 3740, 0 }, // sops
    [3945] = { 3741, 0 }, // emcads
    [3946] = { 3742, 0 }, // backupedge
    [3947] = { 3743, 0 }, // ccp
    [3948] = { 3744, 0 }, // apdap
    [3949] = { 3745, 0 }, // drip
    [3950] = { 3746, 0 }, // namemunge
    [3951] = { 3747, 0 }, // pwgippfax
    [3952] = { 3748, 0 }, // i3-sessionmgr
    [3953] = { 3749, 0 }, // xmlink-connect
    [3954] = { 3750, 0 }, // adrep
    [3955] = { 3751, 0 }, // p2pcommunity
    [3956] = { 3752, 0 }, // gvcp
    [3957] = { 3753, 0 }, // mqe-broker
    [3958] = { 3754, 0 }, // mqe-agent
    [3959] = { 3755, 0 }, // treehopper
    [3960] = { 3756, 0 }, // bess
    [3961] = { 3757, 0 }, // proaxess
    [3962] = { 3758, 0 }, // sbi-agent
    [3963] = { 3759, 0 }, // thrp
    [3964] = { 3760, 0 }, // sasggprs
    [3965] = { 3761, 0 }, // ati-ip-to-ncpe
    [3966] = { 3762, 0 }, // bflckmgr
    [3967] = { 3763, 0 }, // ppsms
    [3968] = { 3764, 0 }, // ianywhere-dbns
    [3969] = { 3765, 0 }, // landmarks
    [3970] = { 3766, 0 }, // lanrevagent
    [3971] = { 3767, 0 }, // lanrevserver
    [3972] = { 3768, 0 }, // iconp
    [3973] = { 3769, 0 }, // progistics
    [3974] = { 3770, 0 }, // citysearch
    [3975] = { 3771, 0 }, // airshot
    [3976] = { 3772, 0 }, // opswagent
    [3977] = { 3773, 0 }, // opswmanager
    [3978] = { 3774, 0 }, // secure-cfg-svr
    [3979] = { 3775, 0 }, // smwan
    [3980] = { 3776, 0 }, // acms
    [3981] = { 3777, 0 }, // starfish
    [3982] = { 3778, 0 }, // eis
    [3983] = { 3779, 0 }, // eisp
    [3984] = { 3780, 0 }, // mapper-nodemgr
    [3985] = { 3781, 0 }, // mapper-mapethd
    [3986] = { 3782, 0 }, // mapper-ws_ethd
    [3987] = { 3783, 0 }, // centerline
    [3988] = { 3784, 0 }, // dcs-config
    [3989] = { 3785, 0 }, // bv-queryengine
    [3990] = { 3786, 0 }, // bv-is
    [3991] = { 3787, 0 }, // bv-smcsrv
    [3992] = { 3788, 0 }, // bv-ds
    [3993] = { 3789, 0 }, // bv-agent
    [3995] = { 3790, 0 }, // iss-mgmt-ssl
    [3996] = { 3791, 0 }, // abcsoftware
    [3997] = { 3793, 0 }, // agentsease-db
    [3998] = { 3794, 0 }, // dnx
    [3999] = { 3792, 0 }, // remoteanything
    [4000] = { 3792, 0 }, // remoteanything
    [4001] = { 3797, 0 }, // newoak
    [4002] = { 3798, 0 }, // mlchat-proxy
    [4003] = { 3800, 0 }, // pxc-splr-ft
    [4004] = { 3801, 0 }, // pxc-roid
    [4005] = { 3802, 0 }, // pxc-pin
    [4006] = { 3803, 0 }, // pxc-spvr
    [4007] = { 3804, 0 }, // pxc-splr
    [4008] = { 3805, 0 }, // netcheque
    [4009] = { 3806, 0 }, // chimera-hwm
    [4010] = { 3807, 0 }, // samsung-unidex
    [4011] = { 3808, 0 }, // altserviceboot
    [4012] = { 3809, 0 }, // pda-gate
    [4013] = { 3810, 0 }, // acl-manager
    [4014] = { 3811, 0 }, // taiclock
    [4015] = { 3812, 0 }, // talarian-mcast1
    [4016] = { 3813, 0 }, // talarian-mcast2
    [4017] = { 3814, 0 }, // talarian-mcast3
    [4018] = { 3815, 0 }, // talarian-mcast4
    [4019] = { 3816, 0 }, // talarian-mcast5
    [4020] = { 3817, 0 }, // trap
    [4021] = { 3818, 0 }, // nexus-portal
    [4022] = { 3819, 0 }, // dnox
    [4023] = { 3820, 0 }, // esnm-zoning
    [4024] = { 3821, 0 }, // tnp1-port
    [4025] = { 3822, 0 }, // partimage
    [4026] = { 3823, 0 }, // as-debug
    [4027] = { 3824, 0 }, // bxp
    [4028] = { 3825, 0 }, // dtserver-port
    [4029] = { 3826, 0 }, // ip-qsig
    [4030] = { 3827, 0 }, // jdmn-port
    [4031] = { 3828, 0 }, // suucp
    [4032] = { 3829, 0 }, // vrts-auth-port
    [4033] = { 3830, 0 }, // sanavigator
    [4034] = { 3831, 0 }, // ubxd
    [4035] = { 3832, 0 }, // wap-push-http
    [4036] = { 3833, 0 }, // wap-push-https
    [4037] = { 3834, 0 }, // ravehd
    [4038] = { 3835, 0 }, // fazzt-ptp
    [4039] = { 3836, 0 }, // fazzt-admin
    [4040] = { 3837, 0 }, // yo-main
    [4041] = { 3838, 0 }, // houston
    [4042] = { 3839, 0 }, // ldxp
    [4043] = { 3840, 0 }, // nirp
    [4044] = { 3841, 0 }, // ltp
    [4045] = { 3842, 0 }, // lockd
    [4046] = { 3843, 0 }, // acp-proto
    [4047] = { 3844, 0 }, // ctp-state
    [4049] = { 3845, 0 }, // wafs
    [4050] = { 3846, 0 }, // cisco-wafs
    [4051] = { 3847, 0 }, // cppdp
    [4052] = { 3848, 0 }, // interact
    [4053] = { 3849, 0 }, // ccu-comm-1
    [4054] = { 3850, 0 }, // ccu-comm-2
    [4055] = { 3851, 0 }, // ccu-comm-3
    [4056] = { 3852, 0 }, // lms
    [4057] = { 3853, 0 }, // wfm
    [4058] = { 3854, 0 }, // kingfisher
    [4059] = { 3855, 0 }, // dlms-cosem
    [4060] = { 3856, 0 }, // dsmeter_iatc
    [4061] = { 3857, 0 }, // ice-location
    [4062] = { 3858, 0 }, // ice-slocation
    [4063] = { 3859, 0 }, // ice-router
    [4064] = { 3860, 0 }, // ice-srouter
    [4065] = { 3861, 0 }, // avanti_cdp
    [4066] = { 3862, 0 }, // pmas
    [4067] = { 3863, 0 }, // idp
    [4068] = { 3864, 0 }, // ipfltbcst
    [4069] = { 3865, 0 }, // minger
    [4070] = { 3866, 0 }, // tripe
    [4071] = { 3867, 0 }, // aibkup
    [4072] = { 3868, 0 }, // zieto-sock
    [4073] = { 3869, 0 }, // iRAPP
    [4074] = { 3870, 0 }, // cequint-cityid
    [4075] = { 3871, 0 }, // perimlan
    [4076] = { 3872, 0 }, // seraph
    [4077] = { 3873, 0 }, // ascomalarm
    [4078] = { 3874, 0 }, // cssp
    [4079] = { 3875, 0 }, // santools
    [4080] = { 3876, 0 }, // lorica-in
    [4081] = { 3877, 0 }, // lorica-in-sec
    [4082] = { 3878, 0 }, // lorica-out
    [4083] = { 3879, 0 }, // lorica-out-sec
    [4084] = { 3880, 0 }, // fortisphere-vm
    [4085] = { 3881, 0 }, // ezmessagesrv
    [4086] = { 3882, 0 }, // ftsync
    [4087] = { 3883, 0 }, // applusservice
    [4088] = { 3884, 0 }, // npsp
    [4089] = { 3885, 0 }, // opencore
    [4090] = { 3886, 0 }, // omasgport
    [4091] = { 3887, 0 }, // ewinstaller
    [4092] = { 3888, 0 }, // ewdgs
    [4093] = { 3889, 0 }, // pvxpluscs
    [4094] = { 3890, 0 }, // sysrqd
    [4095] = { 3891, 0 }, // xtgui
    [4096] = { 3892, 0 }, // bre
    [4097] = { 3893, 0 }, // patrolview
    [4098] = { 3894, 0 }, // drmsfsd
    [4099] = { 3895, 0 }, // dpcp
    [4100] = { 3896, 0 }, // igo-incognito
    [4101] = { 3897, 0 }, // brlp-0
    [4102] = { 3898, 0 }, // brlp-1
    [4103] = { 3899, 0 }, // brlp-2
    [4104] = { 3900, 0 }, // brlp-3
    [4105] = { 3901, 0 }, // shofarplayer
    [4106] = { 3902, 0 }, // synchronite
    [4107] = { 3903, 0 }, // j-ac
    [4108] = { 3904, 0 }, // accel
    [4109] = { 3905, 0 }, // izm
    [4110] = { 3906, 0 }, // g2tag
    [4111] = { 3907, 0 }, // xgrid
    [4112] = { 3908, 0 }, // apple-vpns-rp
    [4113] = { 3909, 0 }, // aipn-reg
    [4114] = { 3910, 0 }, // jomamqmonitor
    [4115] = { 3911, 0 }, // cds
    [4116] = { 3912, 0 }, // smartcard-tls
    [4117] = { 3913, 0 }, // hillrserv
    [4118] = { 3914, 0 }, // netscript
    [4119] = { 3915, 0 }, // assuria-slm
    [4120] = { 3916, 0 }, // minirem
    [4121] = { 3917, 0 }, // e-builder
    [4122] = { 3918, 0 }, // fprams
    [4123] = { 3919, 0 }, // z-wave
    [4124] = { 3920, 0 }, // tigv2
    [4125] = { 3921, 0 }, // rww
    [4126] = { 3923, 0 }, // ddrepl
    [4127] = { 3924, 0 }, // unikeypro
    [4128] = { 3925, 0 }, // nufw
    [4129] = { 3926, 0 }, // nuauth
    [4130] = { 3927, 0 }, // fronet
    [4131] = { 3928, 0 }, // stars
    [4132] = { 3929, 0 }, // nuts_dem
    [4133] = { 3930, 0 }, // nuts_bootp
    [4134] = { 3931, 0 }, // nifty-hmi
    [4135] = { 3932, 0 }, // cl-db-attach
    [4136] = { 3933, 0 }, // cl-db-request
    [4137] = { 3934, 0 }, // cl-db-remote
    [4138] = { 3935, 0 }, // nettest
    [4139] = { 3936, 0 }, // thrtx
    [4140] = { 3937, 0 }, // cedros_fds
    [4141] = { 3938, 0 }, // oirtgsvc
    [4142] = { 3939, 0 }, // oidocsvc
    [4143] = { 3940, 0 }, // oidsr
    [4144] = { 3941, 0 }, // wincim
    [4145] = { 3942, 0 }, // vvr-control
    [4146] = { 3943, 0 }, // tgcconnect
    [4147] = { 3944, 0 }, // vrxpservman
    [4148] = { 3945, 0 }, // hhb-handheld
    [4149] = { 3946, 0 }, // agslb
    [4150] = { 3947, 0 }, // PowerAlert-nsa
    [4151] = { 3948, 0 }, // menandmice_noh
    [4152] = { 3949, 0 }, // idig_mux
    [4153] = { 3950, 0 }, // mbl-battd
    [4154] = { 3951, 0 }, // atlinks
    [4155] = { 3952, 0 }, // bzr
    [4156] = { 3953, 0 }, // stat-results
    [4157] = { 3954, 0 }, // stat-scanner
    [4158] = { 3955, 0 }, // stat-cc
    [4159] = { 3956, 0 }, // nss
    [4160] = { 3957, 0 }, // jini-discovery
    [4161] = { 3958, 0 }, // omscontact
    [4162] = { 3959, 0 }, // omstopology
    [4163] = { 3960, 0 }, // silverpeakpeer
    [4164] = { 3961, 0 }, // silverpeakcomm
    [4165] = { 3962, 0 }, // altcp
    [4166] = { 3963, 0 }, // joost
    [4167] = { 3964, 0 }, // ddgn
    [4168] = { 3965, 0 }, // pslicser
    [4169] = { 3966, 0 }, // iadt
    [4170] = { 3968, 0 }, // d-cinema-csp
    [4171] = { 3969, 0 }, // ml-svnet
    [4172] = { 3970, 0 }, // pcoip
    [4173] = { 3971, 0 }, // mma-discovery
    [4174] = { 3972, 0 }, // smcluster
    [4175] = { 3973, 0 }, // bccp
    [4176] = { 3974, 0 }, // tl-ipcproxy
    [4177] = { 3975, 0 }, // wello
    [4178] = { 3976, 0 }, // storman
    [4179] = { 3977, 0 }, // MaxumSP
    [4180] = { 3978, 0 }, // httpx
    [4181] = { 3979, 0 }, // macbak
    [4182] = { 3980, 0 }, // pcptcpservice
    [4183] = { 3981, 0 }, // gmmp
    [4184] = { 3982, 0 }, // universe_suite
    [4185] = { 3983, 0 }, // wcpp
    [4186] = { 3984, 0 }, // boxbackupstore
    [4187] = { 3985, 0 }, // csc_proxy
    [4188] = { 3986, 0 }, // vatata
    [4189] = { 3987, 0 }, // pcep
    [4190] = { 3988, 0 }, // sieve
    [4191] = { 3989, 0 }, // dsmipv6
    [4192] = { 3990, 0 }, // azeti
    [4193] = { 3992, 0 }, // pvxplusio
    [4194] = { 3993, 0 }, // spdm
    [4195] = { 3994, 0 }, // aws-wsp
    [4197] = { 3995, 0 }, // hctl
    [4199] = { 3996, 0 }, // eims-admin
    [4200] = { 3997, 0 }, // vrml-multi-use
    [4201] = { 3997, 0 }, // vrml-multi-use
    [4202] = { 3997, 0 }, // vrml-multi-use
    [4203] = { 3997, 0 }, // vrml-multi-use
    [4204] = { 3997, 0 }, // vrml-multi-use
    [4205] = { 3997, 0 }, // vrml-multi-use
    [4206] = { 3997, 0 }, // vrml-multi-use
    [4207] = { 3997, 0 }, // vrml-multi-use
    [4208] = { 3997, 0 }, // vrml-multi-use
    [4209] = { 3997, 0 }, // vrml-multi-use
    [4210] = { 3997, 0 }, // vrml-multi-use
    [4211] = { 3997, 0 }, // vrml-multi-use
    [4212] = { 3997, 0 }, // vrml-multi-use
    [4213] = { 3997, 0 }, // vrml-multi-use
    [4214] = { 3997, 0 }, // vrml-multi-use
    [4215] = { 3997, 0 }, // vrml-multi-use
    [4216] = { 3997, 0 }, // vrml-multi-use
    [4217] = { 3997, 0 }, // vrml-multi-use
    [4218] = { 3997, 0 }, // vrml-multi-use
    [4219] = { 3997, 0 }, // vrml-multi-use
    [4220] = { 3997, 0 }, // vrml-multi-use
    [4221] = { 3997, 0 }, // vrml-multi-use
    [4222] = { 3997, 0 }, // vrml-multi-use
    [4223] = { 3997, 0 }, // vrml-multi-use
    [4224] = { 3998, 0 }, // xtell
    [4225] = { 3997, 0 }, // vrml-multi-use
    [4226] = { 3997, 0 }, // vrml-multi-use
    [4227] = { 3997, 0 }, // vrml-multi-use
    [4228] = { 3997, 0 }, // vrml-multi-use
    [4229] = { 3997, 0 }, // vrml-multi-use
    [4230] = { 3997, 0 }, // vrml-multi-use
    [4231] = { 3997, 0 }, // vrml-multi-use
    [4232] = { 3997, 0 }, // vrml-multi-use
    [4233] = { 3997, 0 }, // vrml-multi-use
    [4234] = { 3997, 0 }, // vrml-multi-use
    [4235] = { 3997, 0 }, // vrml-multi-use
    [4236] = { 3997, 0 }, // vrml-multi-use
    [4237] = { 3997, 0 }, // vrml-multi-use
    [4238] = { 3997, 0 }, // vrml-multi-use
    [4239] = { 3997, 0 }, // vrml-multi-use
    [4240] = { 3997, 0 }, // vrml-multi-use
    [4241] = { 3997, 0 }, // vrml-multi-use
    [4242] = { 3997, 0 }, // vrml-multi-use
    [4243] = { 3997, 0 }, // vrml-multi-use
    [4244] = { 3997, 0 }, // vrml-multi-use
    [4245] = { 3997, 0 }, // vrml-multi-use
    [4246] = { 3997, 0 }, // vrml-multi-use
    [4247] = { 3997, 0 }, // vrml-multi-use
    [4248] = { 3997, 0 }, // vrml-multi-use
    [4249] = { 3997, 0 }, // vrml-multi-use
    [4250] = { 3997, 0 }, // vrml-multi-use
    [4251] = { 3997, 0 }, // vrml-multi-use
    [4252] = { 3997, 0 }, // vrml-multi-use
    [4253] = { 3997, 0 }, // vrml-multi-use
    [4254] = { 3997, 0 }, // vrml-multi-use
    [4255] = { 3997, 0 }, // vrml-multi-use
    [4256] = { 3997, 0 }, // vrml-multi-use
    [4257] = { 3997, 0 }, // vrml-multi-use
    [4258] = { 3997, 0 }, // vrml-multi-use
    [4259] = { 3997, 0 }, // vrml-multi-use
    [4260] = { 3997, 0 }, // vrml-multi-use
    [4261] = { 3997, 0 }, // vrml-multi-use
    [4262] = { 3997, 0 }, // vrml-multi-use
    [4263] = { 3997, 0 }, // vrml-multi-use
    [4264] = { 3997, 0 }, // vrml-multi-use
    [4265] = { 3997, 0 }, // vrml-multi-use
    [4266] = { 3997, 0 }, // vrml-multi-use
    [4267] = { 3997, 0 }, // vrml-multi-use
    [4268] = { 3997, 0 }, // vrml-multi-use
    [4269] = { 3997, 0 }, // vrml-multi-use
    [4270] = { 3997, 0 }, // vrml-multi-use
    [4271] = { 3997, 0 }, // vrml-multi-use
    [4272] = { 3997, 0 }, // vrml-multi-use
    [4273] = { 3997, 0 }, // vrml-multi-use
    [4274] = { 3997, 0 }, // vrml-multi-use
    [4275] = { 3997, 0 }, // vrml-multi-use
    [4276] = { 3997, 0 }, // vrml-multi-use
    [4277] = { 3997, 0 }, // vrml-multi-use
    [4278] = { 3997, 0 }, // vrml-multi-use
    [4279] = { 3997, 0 }, // vrml-multi-use
    [4280] = { 3997, 0 }, // vrml-multi-use
    [4281] = { 3997, 0 }, // vrml-multi-use
    [4282] = { 3997, 0 }, // vrml-multi-use
    [4283] = { 3997, 0 }, // vrml-multi-use
    [4284] = { 3997, 0 }, // vrml-multi-use
    [4285] = { 3997, 0 }, // vrml-multi-use
    [4286] = { 3997, 0 }, // vrml-multi-use
    [4287] = { 3997, 0 }, // vrml-multi-use
    [4288] = { 3997, 0 }, // vrml-multi-use
    [4289] = { 3997, 0 }, // vrml-multi-use
    [4290] = { 3997, 0 }, // vrml-multi-use
    [4291] = { 3997, 0 }, // vrml-multi-use
    [4292] = { 3997, 0 }, // vrml-multi-use
    [4293] = { 3997, 0 }, // vrml-multi-use
    [4294] = { 3997, 0 }, // vrml-multi-use
    [4295] = { 3997, 0 }, // vrml-multi-use
    [4296] = { 3997, 0 }, // vrml-multi-use
    [4297] = { 3997, 0 }, // vrml-multi-use
    [4298] = { 3997, 0 }, // vrml-multi-use
    [4299] = { 3997, 0 }, // vrml-multi-use
    [4300] = { 3999, 0 }, // corelccam
    [4301] = { 4000, 0 }, // d-data
    [4302] = { 4001, 0 }, // d-data-control
    [4303] = { 4002, 0 }, // srcp
    [4304] = { 4003, 0 }, // owserver
    [4305] = { 4004, 0 }, // batman
    [4306] = { 4005, 0 }, // pinghgl
    [4307] = { 4006, 0 }, // visicron-vs
    [4308] = { 4007, 0 }, // compx-lockview
    [4309] = { 4008, 0 }, // dserver
    [4310] = { 4009, 0 }, // mirrtex
    [4311] = { 4010, 0 }, // p6ssmc
    [4312] = { 4011, 0 }, // pscl-mgt
    [4313] = { 4012, 0 }, // perrla
    [4314] = { 4013, 0 }, // choiceview-agt
    [4316] = { 4014, 0 }, // choiceview-clt
    [4317] = { 4015, 0 }, // opentelemetry
    [4319] = { 4016, 0 }, // fox-skytale
    [4320] = { 4017, 0 }, // fdt-rcatp
    [4321] = { 4018, 0 }, // rwhois
    [4322] = { 4019, 0 }, // trim-event
    [4323] = { 4020, 0 }, // trim-ice
    [4324] = { 4021, 0 }, // balour
    [4325] = { 4022, 0 }, // geognosisman
    [4326] = { 4023, 0 }, // geognosis
    [4327] = { 4024, 0 }, // jaxer-web
    [4328] = { 4025, 0 }, // jaxer-manager
    [4329] = { 4026, 0 }, // publiqare-sync
    [4330] = { 4027, 0 }, // dey-sapi
    [4331] = { 4028, 0 }, // ktickets-rest
    [4332] = { 4029, 0 }, // getty-focus
    [4333] = { 859, 0 }, // msql
    [4334] = { 4030, 0 }, // netconf-ch-ssh
    [4335] = { 4031, 0 }, // netconf-ch-tls
    [4336] = { 4032, 0 }, // restconf-ch-tls
    [4340] = { 4033, 0 }, // gaia
    [4341] = { 4034, 0 }, // lisp-data
    [4342] = { 4035, 0 }, // lisp-cons
    [4343] = { 4037, 0 }, // unicall
    [4344] = { 4038, 0 }, // vinainstall
    [4345] = { 4039, 0 }, // m4-network-as
    [4346] = { 4040, 0 }, // elanlm
    [4347] = { 4041, 0 }, // lansurveyor
    [4348] = { 4042, 0 }, // itose
    [4349] = { 4043, 0 }, // fsportmap
    [4350] = { 4044, 0 }, // net-device
    [4351] = { 4045, 0 }, // plcy-net-svcs
    [4352] = { 4046, 0 }, // pjlink
    [4353] = { 4047, 0 }, // f5-iquery
    [4354] = { 4048, 0 }, // qsnet-trans
    [4355] = { 4049, 0 }, // qsnet-workst
    [4356] = { 4050, 0 }, // qsnet-assist
    [4357] = { 4051, 0 }, // qsnet-cond
    [4358] = { 4052, 0 }, // qsnet-nucl
    [4359] = { 4053, 0 }, // omabcastltkm
    [4360] = { 4054, 0 }, // matrix_vnet
    [4361] = { 4055, 0 }, // nacnl
    [4362] = { 4056, 0 }, // afore-vdp-disc
    [4366] = { 4057, 0 }, // shadowstream
    [4368] = { 4058, 0 }, // wxbrief
    [4369] = { 4059, 0 }, // epmd
    [4370] = { 4060, 0 }, // elpro_tunnel
    [4371] = { 4061, 0 }, // l2c-control
    [4372] = { 4063, 0 }, // l2c-data
    [4373] = { 4064, 0 }, // remctl
    [4374] = { 4065, 0 }, // psi-ptt
    [4375] = { 4066, 0 }, // tolteces
    [4376] = { 4067, 0 }, // bip
    [4377] = { 4068, 0 }, // cp-spxsvr
    [4378] = { 4069, 0 }, // cp-spxdpy
    [4379] = { 4070, 0 }, // ctdb
    [4389] = { 4071, 0 }, // xandros-cms
    [4390] = { 4072, 0 }, // wiegand
    [4391] = { 4073, 0 }, // apwi-imserver
    [4392] = { 4074, 0 }, // apwi-rxserver
    [4393] = { 4075, 0 }, // apwi-rxspooler
    [4394] = { 4076, 0 }, // apwi-disc
    [4395] = { 4077, 0 }, // omnivisionesx
    [4396] = { 4078, 0 }, // fly
    [4400] = { 4079, 0 }, // ds-srv
    [4401] = { 4080, 0 }, // ds-srvr
    [4402] = { 4081, 0 }, // ds-clnt
    [4403] = { 4082, 0 }, // ds-user
    [4404] = { 4083, 0 }, // ds-admin
    [4405] = { 4084, 0 }, // ds-mail
    [4406] = { 4085, 0 }, // ds-slp
    [4407] = { 4086, 0 }, // nacagent
    [4408] = { 4087, 0 }, // slscc
    [4409] = { 4088, 0 }, // netcabinet-com
    [4410] = { 4089, 0 }, // itwo-server
    [4411] = { 4090, 0 }, // found
    [4412] = { 4091, 0 }, // smallchat
    [4413] = { 4092, 0 }, // avi-nms
    [4414] = { 4093, 0 }, // updog
    [4415] = { 4094, 0 }, // brcd-vr-req
    [4416] = { 4095, 0 }, // pjj-player
    [4417] = { 4096, 0 }, // workflowdir
    [4418] = { 4097, 0 }, // axysbridge
    [4419] = { 4098, 0 }, // cbp
    [4420] = { 4099, 0 }, // nvm-express
    [4421] = { 4100, 0 }, // scaleft
    [4422] = { 4101, 0 }, // tsepisp
    [4423] = { 4102, 0 }, // thingkit
    [4425] = { 4103, 0 }, // netrockey6
    [4426] = { 4104, 0 }, // beacon-port-2
    [4427] = { 4105, 0 }, // drizzle
    [4428] = { 4106, 0 }, // omviserver
    [4429] = { 4107, 0 }, // omviagent
    [4430] = { 4108, 0 }, // rsqlserver
    [4431] = { 4109, 0 }, // wspipe
    [4432] = { 4110, 0 }, // l-acoustics
    [4433] = { 4111, 0 }, // vop
    [4441] = { 4112, 0 }, // netblox
    [4442] = { 4113, 0 }, // saris
    [4443] = { 4114, 0 }, // pharos
    [4444] = { 4115, 0 }, // krb524
    [4445] = { 4116, 0 }, // upnotifyp
    [4446] = { 4117, 0 }, // n1-fwp
    [4447] = { 4118, 0 }, // n1-rmgmt
    [4448] = { 4119, 0 }, // asc-slmd
    [4449] = { 4120, 0 }, // privatewire
    [4450] = { 4121, 0 }, // camp
    [4451] = { 4122, 0 }, // ctisystemmsg
    [4452] = { 4123, 0 }, // ctiprogramload
    [4453] = { 4124, 0 }, // nssalertmgr
    [4454] = { 4125, 0 }, // nssagentmgr
    [4455] = { 4126, 0 }, // prchat-user
    [4456] = { 4127, 0 }, // prchat-server
    [4457] = { 4128, 0 }, // prRegister
    [4458] = { 4129, 0 }, // mcp
    [4460] = { 4130, 0 }, // ntske
    [4480] = { 4131, 0 }, // proxy-plus
    [4484] = { 4132, 0 }, // hpssmgmt
    [4485] = { 4133, 0 }, // assyst-dr
    [4486] = { 4134, 0 }, // icms
    [4487] = { 4135, 0 }, // prex-tcp
    [4488] = { 4136, 0 }, // awacs-ice
    [4500] = { 4137, 0 }, // sae-urn
    [4502] = { 4139, 0 }, // a25-fap-fgw
    [4534] = { 4140, 0 }, // armagetronad
    [4535] = { 4141, 0 }, // ehs
    [4536] = { 4142, 0 }, // ehs-ssl
    [4537] = { 4143, 0 }, // wssauthsvc
    [4538] = { 4144, 0 }, // swx-gate
    [4545] = { 4145, 0 }, // worldscores
    [4546] = { 4146, 0 }, // sf-lm
    [4547] = { 4147, 0 }, // lanner-lm
    [4548] = { 4148, 0 }, // synchromesh
    [4549] = { 4149, 0 }, // aegate
    [4550] = { 4150, 0 }, // gds-adppiw-db
    [4551] = { 4151, 0 }, // ieee-mih
    [4552] = { 4152, 0 }, // menandmice-mon
    [4553] = { 4153, 0 }, // icshostsvc
    [4554] = { 4154, 0 }, // msfrs
    [4555] = { 4155, 0 }, // rsip
    [4556] = { 4156, 0 }, // dtn-bundle-tcp
    [4557] = { 4158, 0 }, // fax
    [4558] = { 4160, 0 }, // mtcevrunqman
    [4559] = { 4161, 0 }, // hylafax
    [4563] = { 4162, 0 }, // amahi-anywhere
    [4566] = { 4163, 0 }, // kwtc
    [4567] = { 4164, 0 }, // tram
    [4568] = { 4165, 0 }, // bmc-reporting
    [4569] = { 4166, 0 }, // iax
    [4570] = { 4167, 0 }, // deploymentmap
    [4573] = { 4168, 0 }, // cardifftec-back
    [4590] = { 4169, 0 }, // rid
    [4591] = { 4170, 0 }, // l3t-at-an
    [4592] = { 4171, 0 }, // hrpd-ith-at-an
    [4593] = { 4172, 0 }, // ipt-anri-anri
    [4594] = { 4173, 0 }, // ias-session
    [4595] = { 4174, 0 }, // ias-paging
    [4596] = { 4175, 0 }, // ias-neighbor
    [4597] = { 4176, 0 }, // a21-an-1xbs
    [4598] = { 4177, 0 }, // a16-an-an
    [4599] = { 4178, 0 }, // a17-an-an
    [4600] = { 4179, 0 }, // piranha1
    [4601] = { 4180, 0 }, // piranha2
    [4602] = { 4181, 0 }, // mtsserver
    [4603] = { 4182, 0 }, // menandmice-upg
    [4604] = { 4183, 0 }, // irp
    [4605] = { 4184, 0 }, // sixchat
    [4606] = { 4185, 0 }, // sixid
    [4621] = { 4186, 0 }, // ventoso
    [4646] = { 4187, 0 }, // dots-signal
    [4658] = { 4188, 0 }, // playsta2-app
    [4659] = { 4189, 0 }, // playsta2-lob
    [4660] = { 4190, 0 }, // mosmig
    [4661] = { 4192, 0 }, // kar2ouche
    [4662] = { 4193, 0 }, // edonkey
    [4663] = { 4195, 0 }, // noteit
    [4664] = { 4196, 0 }, // ems
    [4665] = { 4197, 0 }, // contclientms
    [4666] = { 4198, 0 }, // eportcomm
    [4667] = { 4199, 0 }, // mmacomm
    [4668] = { 4200, 0 }, // mmaeds
    [4669] = { 4201, 0 }, // eportcommdata
    [4670] = { 4202, 0 }, // light
    [4671] = { 4203, 0 }, // acter
    [4672] = { 4204, 0 }, // rfa
    [4673] = { 4205, 0 }, // cxws
    [4674] = { 4206, 0 }, // appiq-mgmt
    [4675] = { 4207, 0 }, // dhct-status
    [4676] = { 4208, 0 }, // dhct-alerts
    [4677] = { 4209, 0 }, // bcs
    [4678] = { 4210, 0 }, // traversal
    [4679] = { 4211, 0 }, // mgesupervision
    [4680] = { 4212, 0 }, // mgemanagement
    [4681] = { 4213, 0 }, // parliant
    [4682] = { 4214, 0 }, // finisar
    [4683] = { 4215, 0 }, // spike
    [4684] = { 4216, 0 }, // rfid-rp1
    [4685] = { 4217, 0 }, // autopac
    [4686] = { 4218, 0 }, // msp-os
    [4687] = { 4219, 0 }, // nst
    [4688] = { 4220, 0 }, // mobile-p2p
    [4689] = { 4221, 0 }, // altovacentral
    [4690] = { 4222, 0 }, // prelude
    [4691] = { 4223, 0 }, // mtn
    [4692] = { 4224, 0 }, // conspiracy
    [4700] = { 4225, 0 }, // netxms-agent
    [4701] = { 4226, 0 }, // netxms-mgmt
    [4702] = { 4227, 0 }, // netxms-sync
    [4703] = { 4228, 0 }, // npqes-test
    [4704] = { 4229, 0 }, // assuria-ins
    [4711] = { 4230, 0 }, // trinity-dist
    [4713] = { 4231, 0 }, // pulseaudio
    [4725] = { 4232, 0 }, // truckstar
    [4726] = { 4233, 0 }, // a26-fap-fgw
    [4727] = { 4234, 0 }, // fcis
    [4728] = { 4236, 0 }, // capmux
    [4729] = { 4237, 0 }, // gsmtap
    [4730] = { 4238, 0 }, // gearman
    [4731] = { 4239, 0 }, // remcap
    [4732] = { 4240, 0 }, // ohmtrigger
    [4733] = { 4241, 0 }, // resorcs
    [4737] = { 4242, 0 }, // ipdr-sp
    [4738] = { 4243, 0 }, // solera-lpn
    [4739] = { 4244, 0 }, // ipfix
    [4740] = { 4245, 0 }, // ipfixs
    [4741] = { 4246, 0 }, // lumimgrd
    [4742] = { 4247, 0 }, // sicct
    [4743] = { 4249, 0 }, // openhpid
    [4744] = { 4250, 0 }, // ifsp
    [4745] = { 4251, 0 }, // fmp
    [4746] = { 4252, 0 }, // intelliadm-disc
    [4747] = { 4253, 0 }, // buschtrommel
    [4749] = { 4254, 0 }, // profilemac
    [4750] = { 4255, 0 }, // ssad
    [4751] = { 4256, 0 }, // spocp
    [4752] = { 4257, 0 }, // snap
    [4753] = { 4258, 0 }, // simon
    [4754] = { 4259, 0 }, // gre-in-udp
    [4755] = { 4260, 0 }, // gre-udp-dtls
    [4756] = { 4261, 0 }, // RDCenter
    [4774] = { 4262, 0 }, // converge
    [4784] = { 4263, 0 }, // bfd-multi-ctl
    [4785] = { 4264, 0 }, // cncp
    [4786] = { 4265, 0 }, // smart-install
    [4787] = { 4266, 0 }, // sia-ctrl-plane
    [4788] = { 4267, 0 }, // xmcp
    [4789] = { 4268, 0 }, // vxlan
    [4790] = { 4269, 0 }, // vxlan-gpe
    [4791] = { 4270, 0 }, // roce
    [4792] = { 4271, 0 }, // unified-bus
    [4800] = { 4272, 0 }, // iims
    [4801] = { 4273, 0 }, // iwec
    [4802] = { 4274, 0 }, // ilss
    [4803] = { 4275, 0 }, // notateit
    [4804] = { 4277, 0 }, // aja-ntv4-disc
    [4827] = { 4278, 0 }, // htcp
    [4837] = { 4280, 0 }, // varadero-0
    [4838] = { 4281, 0 }, // varadero-1
    [4839] = { 4282, 0 }, // varadero-2
    [4840] = { 4283, 0 }, // opcua-tcp
    [4841] = { 4285, 0 }, // quosa
    [4842] = { 4286, 0 }, // gw-asv
    [4843] = { 4287, 0 }, // opcua-tls
    [4844] = { 4288, 0 }, // gw-log
    [4845] = { 4289, 0 }, // wcr-remlib
    [4846] = { 4290, 0 }, // contamac_icm
    [4847] = { 4291, 0 }, // wfc
    [4848] = { 4292, 0 }, // appserv-http
    [4849] = { 4293, 0 }, // appserv-https
    [4850] = { 4294, 0 }, // sun-as-nodeagt
    [4851] = { 4295, 0 }, // derby-repli
    [4867] = { 4296, 0 }, // unify-debug
    [4868] = { 4297, 0 }, // phrelay
    [4869] = { 4298, 0 }, // phrelaydbg
    [4870] = { 4299, 0 }, // cc-tracking
    [4871] = { 4300, 0 }, // wired
    [4876] = { 4301, 0 }, // tritium-can
    [4877] = { 4302, 0 }, // lmcs
    [4878] = { 4303, 0 }, // inst-discovery
    [4879] = { 4304, 0 }, // wsdl-event
    [4880] = { 4305, 0 }, // hislip
    [4881] = { 4306, 0 }, // socp-t
    [4882] = { 4307, 0 }, // socp-c
    [4883] = { 4308, 0 }, // wmlserver
    [4884] = { 4309, 0 }, // hivestor
    [4885] = { 4310, 0 }, // abbs
    [4888] = { 4311, 0 }, // xcap-portal
    [4889] = { 4312, 0 }, // xcap-control
    [4894] = { 4313, 0 }, // lyskom
    [4899] = { 4314, 0 }, // radmin
    [4900] = { 4316, 0 }, // hfcs
    [4901] = { 4317, 0 }, // flr_agent
    [4902] = { 4318, 0 }, // magiccontrol
    [4912] = { 4319, 0 }, // lutap
    [4913] = { 4320, 0 }, // lutcp
    [4914] = { 4321, 0 }, // bones
    [4915] = { 4322, 0 }, // frcs
    [4936] = { 4323, 0 }, // an-signaling
    [4937] = { 4324, 0 }, // atsc-mh-ssc
    [4940] = { 4325, 0 }, // eq-office-4940
    [4941] = { 4326, 0 }, // eq-office-4941
    [4942] = { 4327, 0 }, // eq-office-4942
    [4949] = { 4328, 0 }, // munin
    [4950] = { 4329, 0 }, // sybasesrvmon
    [4951] = { 4330, 0 }, // pwgwims
    [4952] = { 4331, 0 }, // sagxtsds
    [4953] = { 4332, 0 }, // dbsyncarbiter
    [4969] = { 4333, 0 }, // ccss-qmm
    [4970] = { 4334, 0 }, // ccss-qsm
    [4971] = { 4335, 0 }, // burp
    [4980] = { 4336, 0 }, // ctxs-vpp
    [4984] = { 4337, 0 }, // webyast
    [4985] = { 4338, 0 }, // gerhcs
    [4986] = { 4339, 0 }, // mrip
    [4987] = { 4340, 0 }, // maybe-veritas
    [4988] = { 4342, 0 }, // smar-se-port2
    [4989] = { 4343, 0 }, // parallel
    [4990] = { 4344, 0 }, // busycal
    [4991] = { 4345, 0 }, // vrt
    [4998] = { 4340, 0 }, // maybe-veritas
    [4999] = { 4346, 0 }, // hfcs-manager
    [5000] = { 1666, 0 }, // upnp
    [5001] = { 4347, 0 }, // commplex-link
    [5002] = { 4348, 0 }, // rfe
    [5003] = { 4349, 0 }, // filemaker
    [5004] = { 4350, 0 }, // avt-profile-1
    [5005] = { 4351, 0 }, // avt-profile-2
    [5006] = { 4352, 0 }, // wsm-server
    [5007] = { 4353, 0 }, // wsm-server-ssl
    [5008] = { 4354, 0 }, // synapsis-edge
    [5009] = { 4355, 0 }, // airport-admin
    [5010] = { 4357, 0 }, // telelpathstart
    [5011] = { 4358, 0 }, // telelpathattack
    [5012] = { 4359, 0 }, // nsp
    [5013] = { 4360, 0 }, // fmpro-v6
    [5014] = { 4361, 0 }, // onpsocket
    [5015] = { 4362, 0 }, // fmwp
    [5020] = { 4363, 0 }, // zenginkyo-1
    [5021] = { 4364, 0 }, // zenginkyo-2
    [5022] = { 4365, 0 }, // mice
    [5023] = { 4366, 0 }, // htuilsrv
    [5024] = { 4367, 0 }, // scpi-telnet
    [5025] = { 4368, 0 }, // scpi-raw
    [5026] = { 4369, 0 }, // strexec-d
    [5027] = { 4370, 0 }, // strexec-s
    [5028] = { 4371, 0 }, // qvr
    [5029] = { 4372, 0 }, // infobright
    [5030] = { 4373, 0 }, // surfpass
    [5031] = { 4374, 0 }, // dmp
    [5032] = { 4375, 0 }, // signacert-agent
    [5033] = { 4376, 0 }, // jtnetd-server
    [5034] = { 4377, 0 }, // jtnetd-status
    [5042] = { 4378, 0 }, // asnaacceler8db
    [5043] = { 4379, 0 }, // swxadmin
    [5044] = { 4380, 0 }, // lxi-evntsvc
    [5045] = { 4381, 0 }, // osp
    [5046] = { 4382, 0 }, // vpm-udp
    [5047] = { 4383, 0 }, // iscape
    [5048] = { 4384, 0 }, // texai
    [5049] = { 4385, 0 }, // ivocalize
    [5050] = { 4386, 0 }, // mmcc
    [5051] = { 4387, 0 }, // ida-agent
    [5052] = { 4389, 0 }, // ita-manager
    [5053] = { 4390, 0 }, // rlm
    [5054] = { 4391, 0 }, // rlm-admin
    [5055] = { 4392, 0 }, // unot
    [5056] = { 4393, 0 }, // intecom-ps1
    [5057] = { 4394, 0 }, // intecom-ps2
    [5058] = { 4395, 0 }, // locus-disc
    [5059] = { 4396, 0 }, // sds
    [5060] = { 4397, 0 }, // sip
    [5061] = { 4398, 0 }, // sip-tls
    [5062] = { 4399, 0 }, // na-localise
    [5063] = { 4400, 0 }, // csrpc
    [5064] = { 4401, 0 }, // ca-1
    [5065] = { 4402, 0 }, // ca-2
    [5066] = { 4403, 0 }, // stanag-5066
    [5067] = { 4404, 0 }, // authentx
    [5068] = { 4405, 0 }, // bitforestsrv
    [5069] = { 4406, 0 }, // i-net-2000-npr
    [5070] = { 4407, 0 }, // vtsas
    [5071] = { 4408, 0 }, // powerschool
    [5072] = { 4409, 0 }, // ayiya
    [5073] = { 4410, 0 }, // tag-pm
    [5074] = { 4411, 0 }, // alesquery
    [5075] = { 4412, 0 }, // pvaccess
    [5078] = { 4413, 0 }, // pixelpusher
    [5079] = { 4414, 0 }, // cp-spxrpts
    [5080] = { 4415, 0 }, // onscreen
    [5081] = { 4416, 0 }, // sdl-ets
    [5082] = { 4417, 0 }, // qcp
    [5083] = { 4418, 0 }, // qfp
    [5084] = { 4419, 0 }, // llrp
    [5085] = { 4420, 0 }, // encrypted-llrp
    [5086] = { 4421, 0 }, // aprigo-cs
    [5087] = { 4422, 0 }, // biotic
    [5090] = { 4423, 0 }, // car
    [5091] = { 4424, 0 }, // cxtp
    [5092] = { 4425, 0 }, // magpie
    [5093] = { 4426, 0 }, // sentinel-lm
    [5094] = { 4427, 0 }, // hart-ip
    [5099] = { 4428, 0 }, // sentlm-srv2srv
    [5100] = { 4429, 0 }, // admd
    [5101] = { 4431, 0 }, // admdog
    [5102] = { 4433, 0 }, // admeng
    [5103] = { 4435, 0 }, // actifio-c2c
    [5104] = { 4436, 0 }, // tinymessage
    [5105] = { 4437, 0 }, // hughes-ap
    [5106] = { 4438, 0 }, // actifioudsagent
    [5107] = { 4439, 0 }, // actifioreplic
    [5111] = { 4440, 0 }, // taep-as-svc
    [5112] = { 4441, 0 }, // pm-cmdsvr
    [5114] = { 4442, 0 }, // ev-services
    [5115] = { 4443, 0 }, // autobuild
    [5116] = { 4444, 0 }, // emb-proj-cmd
    [5117] = { 4445, 0 }, // gradecam
    [5120] = { 4446, 0 }, // barracuda-bbs
    [5133] = { 4447, 0 }, // nbt-pc
    [5134] = { 4448, 0 }, // ppactivation
    [5135] = { 4449, 0 }, // erp-scale
    [5136] = { 4450, 0 }, // minotaur-sa
    [5137] = { 4451, 0 }, // ctsd
    [5145] = { 4452, 0 }, // rmonitor_secure
    [5146] = { 4453, 0 }, // social-alarm
    [5150] = { 4454, 0 }, // atmp
    [5151] = { 4455, 0 }, // esri_sde
    [5152] = { 4456, 0 }, // sde-discovery
    [5153] = { 4457, 0 }, // toruxserver
    [5154] = { 4458, 0 }, // bzflag
    [5155] = { 4459, 0 }, // asctrl-agent
    [5156] = { 4460, 0 }, // rugameonline
    [5157] = { 4461, 0 }, // mediat
    [5161] = { 4462, 0 }, // snmpssh
    [5162] = { 4463, 0 }, // snmpssh-trap
    [5163] = { 4464, 0 }, // sbackup
    [5164] = { 4465, 0 }, // vpa
    [5165] = { 4467, 0 }, // ife_icorp
    [5166] = { 4468, 0 }, // winpcs
    [5167] = { 4469, 0 }, // scte104
    [5168] = { 4470, 0 }, // scte30
    [5172] = { 4471, 0 }, // pcoip-mgmt
    [5190] = { 4472, 0 }, // aol
    [5191] = { 4473, 0 }, // aol-1
    [5192] = { 4474, 0 }, // aol-2
    [5193] = { 4475, 0 }, // aol-3
    [5194] = { 4476, 0 }, // cpscomm
    [5195] = { 4477, 0 }, // ampl-lic
    [5196] = { 4478, 0 }, // ampl-tableproxy
    [5197] = { 4479, 0 }, // tunstall-lwp
    [5200] = { 4480, 0 }, // targus-getdata
    [5201] = { 4481, 0 }, // targus-getdata1
    [5202] = { 4482, 0 }, // targus-getdata2
    [5203] = { 4483, 0 }, // targus-getdata3
    [5209] = { 4484, 0 }, // nomad
    [5215] = { 4485, 0 }, // noteza
    [5221] = { 4486, 0 }, // 3exmp
    [5222] = { 4487, 0 }, // xmpp-client
    [5223] = { 4488, 0 }, // hpvirtgrp
    [5224] = { 4489, 0 }, // hpvirtctrl
    [5225] = { 4490, 0 }, // hp-server
    [5226] = { 4491, 0 }, // hp-status
    [5227] = { 4492, 0 }, // perfd
    [5228] = { 4493, 0 }, // hpvroom
    [5229] = { 4494, 0 }, // jaxflow
    [5230] = { 4495, 0 }, // jaxflow-data
    [5231] = { 4496, 0 }, // crusecontrol
    [5232] = { 4497, 0 }, // sgi-dgl
    [5233] = { 4498, 0 }, // enfs
    [5234] = { 4499, 0 }, // eenet
    [5235] = { 4500, 0 }, // galaxy-network
    [5236] = { 4501, 0 }, // padl2sim
    [5237] = { 4502, 0 }, // mnet-discovery
    [5242] = { 4503, 0 }, // attune
    [5243] = { 4504, 0 }, // xycstatus
    [5245] = { 4505, 0 }, // downtools
    [5246] = { 4507, 0 }, // capwap-control
    [5247] = { 4508, 0 }, // capwap-data
    [5248] = { 4509, 0 }, // caacws
    [5249] = { 4510, 0 }, // caaclang2
    [5250] = { 4511, 0 }, // soagateway
    [5251] = { 4512, 0 }, // caevms
    [5252] = { 4513, 0 }, // movaz-ssc
    [5253] = { 4514, 0 }, // kpdp
    [5254] = { 4515, 0 }, // logcabin
    [5264] = { 4516, 0 }, // 3com-njack-1
    [5265] = { 4517, 0 }, // 3com-njack-2
    [5269] = { 4518, 0 }, // xmpp-server
    [5270] = { 4519, 0 }, // xmp
    [5271] = { 4520, 0 }, // cuelink
    [5272] = { 4522, 0 }, // pk
    [5280] = { 4523, 0 }, // xmpp-bosh
    [5281] = { 4524, 0 }, // undo-lm
    [5282] = { 4525, 0 }, // transmit-port
    [5298] = { 4526, 0 }, // presence
    [5299] = { 4527, 0 }, // nlg-data
    [5300] = { 4528, 0 }, // hacl-hb
    [5301] = { 4529, 0 }, // hacl-gs
    [5302] = { 4530, 0 }, // hacl-cfg
    [5303] = { 4531, 0 }, // hacl-probe
    [5304] = { 4532, 0 }, // hacl-local
    [5305] = { 4533, 0 }, // hacl-test
    [5306] = { 4534, 0 }, // sun-mc-grp
    [5307] = { 4535, 0 }, // sco-aip
    [5308] = { 4536, 0 }, // cfengine
    [5309] = { 4537, 0 }, // jprinter
    [5310] = { 4538, 0 }, // outlaws
    [5312] = { 4539, 0 }, // permabit-cs
    [5313] = { 4540, 0 }, // rrdp
    [5314] = { 4541, 0 }, // opalis-rbt-ipc
    [5315] = { 4542, 0 }, // hacl-poll
    [5316] = { 4543, 0 }, // hpdevms
    [5317] = { 4543, 0 }, // hpdevms
    [5318] = { 4544, 0 }, // pkix-cmc
    [5320] = { 4545, 0 }, // bsfserver-zn
    [5321] = { 4546, 0 }, // bsfsvr-zn-ssl
    [5343] = { 4547, 0 }, // kfserver
    [5344] = { 4548, 0 }, // xkotodrcp
    [5349] = { 4549, 0 }, // stuns
    [5350] = { 4550, 0 }, // nat-pmp-status
    [5351] = { 4551, 0 }, // nat-pmp
    [5352] = { 4552, 0 }, // dns-llq
    [5353] = { 4553, 0 }, // mdns
    [5354] = { 4555, 0 }, // mdnsresponder
    [5355] = { 4556, 0 }, // llmnr
    [5356] = { 4557, 0 }, // ms-smlbiz
    [5357] = { 4558, 0 }, // wsdapi
    [5358] = { 4559, 0 }, // wsdapi-s
    [5359] = { 4560, 0 }, // ms-alerter
    [5360] = { 4561, 0 }, // ms-sideshow
    [5361] = { 4562, 0 }, // ms-s-sideshow
    [5362] = { 4563, 0 }, // serverwsd2
    [5363] = { 4564, 0 }, // net-projection
    [5364] = { 4565, 0 }, // kdnet
    [5397] = { 4566, 0 }, // stresstester
    [5398] = { 4567, 0 }, // elektron-admin
    [5399] = { 4568, 0 }, // securitychase
    [5400] = { 4569, 0 }, // pcduo-old
    [5401] = { 4571, 0 }, // excerpts
    [5402] = { 272, 0 }, // mftp
    [5403] = { 4572, 0 }, // hpoms-ci-lstn
    [5404] = { 4573, 0 }, // hpoms-dps-lstn
    [5405] = { 4574, 0 }, // pcduo
    [5406] = { 4576, 0 }, // systemics-sox
    [5407] = { 4577, 0 }, // foresyte-clear
    [5408] = { 4578, 0 }, // foresyte-sec
    [5409] = { 4579, 0 }, // salient-dtasrv
    [5410] = { 4580, 0 }, // salient-usrmgr
    [5411] = { 4581, 0 }, // actnet
    [5412] = { 4582, 0 }, // continuus
    [5413] = { 4583, 0 }, // wwiotalk
    [5414] = { 4584, 0 }, // statusd
    [5415] = { 4585, 0 }, // ns-server
    [5416] = { 4586, 0 }, // sns-gateway
    [5417] = { 4587, 0 }, // sns-agent
    [5418] = { 4588, 0 }, // mcntp
    [5419] = { 4589, 0 }, // dj-ice
    [5420] = { 4590, 0 }, // cylink-c
    [5421] = { 4591, 0 }, // netsupport2
    [5422] = { 4592, 0 }, // salient-mux
    [5423] = { 4593, 0 }, // virtualuser
    [5424] = { 4594, 0 }, // beyond-remote
    [5425] = { 4595, 0 }, // br-channel
    [5426] = { 4596, 0 }, // devbasic
    [5427] = { 4597, 0 }, // sco-peer-tta
    [5428] = { 4598, 0 }, // telaconsole
    [5429] = { 4600, 0 }, // base
    [5430] = { 4601, 0 }, // radec-corp
    [5431] = { 4602, 0 }, // park-agent
    [5432] = { 4603, 0 }, // postgresql
    [5433] = { 4604, 0 }, // pyrrho
    [5434] = { 4605, 0 }, // sgi-arrayd
    [5435] = { 4606, 0 }, // sceanics
    [5436] = { 4607, 0 }, // pmip6-cntl
    [5437] = { 4608, 0 }, // pmip6-data
    [5443] = { 4609, 0 }, // spss
    [5445] = { 4610, 0 }, // smbdirect
    [5450] = { 4611, 0 }, // tiepie
    [5453] = { 4612, 0 }, // surebox
    [5454] = { 4613, 0 }, // apc-5454
    [5455] = { 4614, 0 }, // apc-5455
    [5456] = { 4615, 0 }, // apc-5456
    [5461] = { 4616, 0 }, // silkmeter
    [5462] = { 4617, 0 }, // ttl-publisher
    [5463] = { 4618, 0 }, // ttlpriceproxy
    [5464] = { 4619, 0 }, // quailnet
    [5465] = { 4620, 0 }, // netops-broker
    [5470] = { 4621, 0 }, // apsolab-col
    [5471] = { 4622, 0 }, // apsolab-cols
    [5472] = { 4623, 0 }, // apsolab-tag
    [5473] = { 4624, 0 }, // apsolab-tags
    [5474] = { 4625, 0 }, // apsolab-rpc
    [5475] = { 4626, 0 }, // apsolab-data
    [5490] = { 4627, 0 }, // connect-proxy
    [5500] = { 988, 0 }, // hotline
    [5501] = { 4629, 0 }, // fcp-addr-srvr2
    [5502] = { 4630, 0 }, // fcp-srvr-inst1
    [5503] = { 4631, 0 }, // fcp-srvr-inst2
    [5504] = { 4632, 0 }, // fcp-cics-gw1
    [5505] = { 4633, 0 }, // checkoutdb
    [5506] = { 4634, 0 }, // amc
    [5507] = { 4635, 0 }, // psl-management
    [5510] = { 4636, 0 }, // secureidprop
    [5520] = { 4637, 0 }, // sdlog
    [5530] = { 4638, 0 }, // sdserv
    [5540] = { 4639, 0 }, // sdreport
    [5550] = { 4641, 0 }, // sdadmind
    [5553] = { 4642, 0 }, // sgi-eventmond
    [5554] = { 4643, 0 }, // sgi-esphttp
    [5555] = { 4644, 0 }, // freeciv
    [5556] = { 4644, 0 }, // freeciv
    [5557] = { 4646, 0 }, // farenet
    [5560] = { 4647, 0 }, // isqlplus
    [5565] = { 4648, 0 }, // hpe-dp-bura
    [5566] = { 4649, 0 }, // westec-connect
    [5567] = { 4650, 0 }, // m-oap
    [5568] = { 4651, 0 }, // sdt
    [5569] = { 4652, 0 }, // rdmnet-ctrl
    [5573] = { 4653, 0 }, // sdmmp
    [5574] = { 4654, 0 }, // lsi-bobcat
    [5575] = { 4655, 0 }, // ora-oap
    [5579] = { 4656, 0 }, // fdtracks
    [5580] = { 4657, 0 }, // tmosms0
    [5581] = { 4658, 0 }, // tmosms1
    [5582] = { 4659, 0 }, // fac-restore
    [5583] = { 4660, 0 }, // tmo-icon-sync
    [5584] = { 4661, 0 }, // bis-web
    [5585] = { 4662, 0 }, // bis-sync
    [5586] = { 4663, 0 }, // att-mt-sms
    [5597] = { 4664, 0 }, // ininmessaging
    [5598] = { 4665, 0 }, // mctfeed
    [5599] = { 4666, 0 }, // esinstall
    [5600] = { 4667, 0 }, // esmmanager
    [5601] = { 4668, 0 }, // esmagent
    [5602] = { 4669, 0 }, // a1-msc
    [5603] = { 4670, 0 }, // a1-bs
    [5604] = { 4671, 0 }, // a3-sdunode
    [5605] = { 4672, 0 }, // a4-sdunode
    [5618] = { 4673, 0 }, // efr
    [5627] = { 4674, 0 }, // ninaf
    [5628] = { 4675, 0 }, // htrust
    [5629] = { 4676, 0 }, // symantec-sfdb
    [5630] = { 4677, 0 }, // precise-comm
    [5631] = { 4678, 0 }, // pcanywheredata
    [5632] = { 4679, 0 }, // pcanywherestat
    [5633] = { 4680, 0 }, // beorl
    [5634] = { 4681, 0 }, // xprtld
    [5635] = { 4682, 0 }, // sfmsso
    [5636] = { 4683, 0 }, // sfm-db-server
    [5637] = { 4684, 0 }, // cssc
    [5638] = { 4685, 0 }, // flcrs
    [5639] = { 4686, 0 }, // ics
    [5646] = { 4687, 0 }, // vfmobile
    [5666] = { 4688, 0 }, // nrpe
    [5670] = { 4689, 0 }, // filemq
    [5671] = { 4690, 0 }, // amqps
    [5672] = { 4691, 0 }, // amqp
    [5673] = { 4692, 0 }, // jms
    [5674] = { 4693, 0 }, // hyperscsi-port
    [5675] = { 4694, 0 }, // v5ua
    [5676] = { 4695, 0 }, // raadmin
    [5677] = { 4696, 0 }, // questdb2-lnchr
    [5678] = { 4697, 0 }, // rrac
    [5679] = { 4698, 0 }, // activesync
    [5680] = { 4700, 0 }, // canna
    [5681] = { 4702, 0 }, // ncxcp
    [5682] = { 4703, 0 }, // brightcore
    [5683] = { 4704, 0 }, // coap
    [5684] = { 4705, 0 }, // coaps
    [5687] = { 4706, 0 }, // gog-multiplayer
    [5688] = { 4707, 0 }, // ggz
    [5689] = { 4708, 0 }, // qmvideo
    [5693] = { 4709, 0 }, // rbsystem
    [5696] = { 4710, 0 }, // kmip
    [5700] = { 4711, 0 }, // supportassist
    [5705] = { 4712, 0 }, // storageos
    [5713] = { 4713, 0 }, // proshareaudio
    [5714] = { 4714, 0 }, // prosharevideo
    [5715] = { 4715, 0 }, // prosharedata
    [5716] = { 4716, 0 }, // prosharerequest
    [5717] = { 4717, 0 }, // prosharenotify
    [5718] = { 4718, 0 }, // dpm
    [5719] = { 4719, 0 }, // dpm-agent
    [5720] = { 4720, 0 }, // ms-licensing
    [5721] = { 4721, 0 }, // dtpt
    [5722] = { 4722, 0 }, // msdfsr
    [5723] = { 4723, 0 }, // omhs
    [5724] = { 4724, 0 }, // omsdk
    [5725] = { 4725, 0 }, // ms-ilm
    [5726] = { 4726, 0 }, // ms-ilm-sts
    [5727] = { 4727, 0 }, // asgenf
    [5728] = { 4728, 0 }, // io-dist-data
    [5729] = { 4730, 0 }, // openmail
    [5730] = { 4731, 0 }, // unieng
    [5741] = { 4732, 0 }, // ida-discover1
    [5742] = { 4733, 0 }, // ida-discover2
    [5743] = { 4734, 0 }, // watchdoc-pod
    [5744] = { 4735, 0 }, // watchdoc
    [5745] = { 4736, 0 }, // fcopy-server
    [5746] = { 4737, 0 }, // fcopys-server
    [5747] = { 4738, 0 }, // tunatic
    [5748] = { 4739, 0 }, // tunalyzer
    [5750] = { 4740, 0 }, // rscd
    [5755] = { 4741, 0 }, // openmailg
    [5757] = { 4742, 0 }, // x500ms
    [5766] = { 4743, 0 }, // openmailns
    [5767] = { 4744, 0 }, // s-openmail
    [5768] = { 4745, 0 }, // openmailpxy
    [5769] = { 4746, 0 }, // spramsca
    [5770] = { 4747, 0 }, // spramsd
    [5771] = { 4748, 0 }, // netagent
    [5777] = { 4749, 0 }, // dali-port
    [5780] = { 4750, 0 }, // vts-rpc
    [5781] = { 4751, 0 }, // 3par-evts
    [5782] = { 4752, 0 }, // 3par-mgmt
    [5783] = { 4753, 0 }, // 3par-mgmt-ssl
    [5784] = { 4754, 0 }, // ibar
    [5785] = { 4755, 0 }, // 3par-rcopy
    [5786] = { 4756, 0 }, // cisco-redu
    [5787] = { 4757, 0 }, // waascluster
    [5793] = { 4758, 0 }, // xtreamx
    [5794] = { 4759, 0 }, // spdp
    [5798] = { 4760, 0 }, // enlabel-dpl
    [5800] = { 4761, 0 }, // vnc-http
    [5801] = { 4762, 0 }, // vnc-http-1
    [5802] = { 4763, 0 }, // vnc-http-2
    [5803] = { 4764, 0 }, // vnc-http-3
    [5813] = { 4765, 0 }, // icmpd
    [5814] = { 4766, 0 }, // spt-automation
    [5820] = { 4767, 0 }, // autopassdaemon
    [5841] = { 4768, 0 }, // shiprush-d-ch
    [5842] = { 4769, 0 }, // reversion
    [5859] = { 4770, 0 }, // wherehoo
    [5863] = { 4771, 0 }, // ppsuitemsg
    [5868] = { 4772, 0 }, // diameters
    [5883] = { 4773, 0 }, // jute
    [5900] = { 4774, 0 }, // vnc
    [5901] = { 4776, 0 }, // vnc-1
    [5902] = { 4777, 0 }, // vnc-2
    [5903] = { 4778, 0 }, // vnc-3
    [5904] = { 4779, 0 }, // ag-swim
    [5905] = { 4780, 0 }, // asmgcs
    [5906] = { 4781, 0 }, // rpas-c2
    [5907] = { 4782, 0 }, // dsd
    [5908] = { 4783, 0 }, // ipsma
    [5909] = { 4784, 0 }, // agma
    [5910] = { 4785, 0 }, // cm
    [5911] = { 4786, 0 }, // cpdlc
    [5912] = { 4787, 0 }, // fis
    [5913] = { 4788, 0 }, // ads-c
    [5938] = { 4789, 0 }, // teamviewer
    [5963] = { 4790, 0 }, // indy
    [5968] = { 4791, 0 }, // mppolicy-v5
    [5969] = { 4792, 0 }, // mppolicy-mgr
    [5977] = { 4793, 0 }, // ncd-pref-tcp
    [5978] = { 4794, 0 }, // ncd-diag-tcp
    [5979] = { 4795, 0 }, // ncd-conf-tcp
    [5984] = { 4796, 0 }, // couchdb
    [5985] = { 4797, 0 }, // wsman
    [5986] = { 4798, 0 }, // wsmans
    [5987] = { 4799, 0 }, // wbem-rmi
    [5988] = { 4800, 0 }, // wbem-http
    [5989] = { 4801, 0 }, // wbem-https
    [5990] = { 4802, 0 }, // wbem-exp-https
    [5991] = { 4803, 0 }, // nuxsl
    [5992] = { 4804, 0 }, // consul-insight
    [5993] = { 4805, 0 }, // cim-rs
    [5994] = { 4806, 0 }, // rms-agent
    [5997] = { 4807, 0 }, // ncd-pref
    [5998] = { 4808, 0 }, // ncd-diag
    [5999] = { 4809, 0 }, // ncd-conf
    [6000] = { 4811, 0 }, // X11
    [6001] = { 4812, 0 }, // X11:1
    [6002] = { 4813, 0 }, // X11:2
    [6003] = { 4814, 0 }, // X11:3
    [6004] = { 4815, 0 }, // X11:4
    [6005] = { 4816, 0 }, // X11:5
    [6006] = { 4817, 0 }, // X11:6
    [6007] = { 4818, 0 }, // X11:7
    [6008] = { 4819, 0 }, // X11:8
    [6009] = { 4820, 0 }, // X11:9
    [6010] = { 4821, 0 }, // x11
    [6011] = { 4821, 0 }, // x11
    [6012] = { 4821, 0 }, // x11
    [6013] = { 4821, 0 }, // x11
    [6014] = { 4821, 0 }, // x11
    [6015] = { 4821, 0 }, // x11
    [6016] = { 4821, 0 }, // x11
    [6017] = { 4822, 0 }, // xmail-ctrl
    [6018] = { 4821, 0 }, // x11
    [6019] = { 4821, 0 }, // x11
    [6020] = { 4821, 0 }, // x11
    [6021] = { 4821, 0 }, // x11
    [6022] = { 4821, 0 }, // x11
    [6023] = { 4821, 0 }, // x11
    [6024] = { 4821, 0 }, // x11
    [6025] = { 4821, 0 }, // x11
    [6026] = { 4821, 0 }, // x11
    [6027] = { 4821, 0 }, // x11
    [6028] = { 4821, 0 }, // x11
    [6029] = { 4821, 0 }, // x11
    [6030] = { 4821, 0 }, // x11
    [6031] = { 4821, 0 }, // x11
    [6032] = { 4821, 0 }, // x11
    [6033] = { 4821, 0 }, // x11
    [6034] = { 4821, 0 }, // x11
    [6035] = { 4821, 0 }, // x11
    [6036] = { 4821, 0 }, // x11
    [6037] = { 4821, 0 }, // x11
    [6038] = { 4821, 0 }, // x11
    [6039] = { 4821, 0 }, // x11
    [6040] = { 4821, 0 }, // x11
    [6041] = { 4821, 0 }, // x11
    [6042] = { 4821, 0 }, // x11
    [6043] = { 4821, 0 }, // x11
    [6044] = { 4821, 0 }, // x11
    [6045] = { 4821, 0 }, // x11
    [6046] = { 4821, 0 }, // x11
    [6047] = { 4821, 0 }, // x11
    [6048] = { 4821, 0 }, // x11
    [6049] = { 4821, 0 }, // x11
    [6050] = { 4823, 0 }, // arcserve
    [6051] = { 4821, 0 }, // x11
    [6052] = { 4821, 0 }, // x11
    [6053] = { 4821, 0 }, // x11
    [6054] = { 4821, 0 }, // x11
    [6055] = { 4821, 0 }, // x11
    [6056] = { 4821, 0 }, // x11
    [6057] = { 4821, 0 }, // x11
    [6058] = { 4821, 0 }, // x11
    [6059] = { 4824, 0 }, // X11:59
    [6060] = { 4821, 0 }, // x11
    [6061] = { 4821, 0 }, // x11
    [6062] = { 4821, 0 }, // x11
    [6063] = { 4821, 0 }, // x11
    [6064] = { 4825, 0 }, // ndl-ahp-svc
    [6065] = { 4826, 0 }, // winpharaoh
    [6066] = { 4827, 0 }, // ewctsp
    [6068] = { 4828, 0 }, // gsmp
    [6069] = { 4829, 0 }, // trip
    [6070] = { 4830, 0 }, // messageasap
    [6071] = { 4831, 0 }, // ssdtp
    [6072] = { 4832, 0 }, // diagnose-proc
    [6073] = { 4833, 0 }, // directplay8
    [6074] = { 4834, 0 }, // max
    [6075] = { 4835, 0 }, // dpm-acm
    [6076] = { 4836, 0 }, // msft-dpm-cert
    [6077] = { 4837, 0 }, // iconstructsrv
    [6080] = { 4838, 0 }, // gue
    [6081] = { 4839, 0 }, // geneve
    [6082] = { 4840, 0 }, // p25cai
    [6083] = { 4841, 0 }, // miami-bcast
    [6084] = { 4842, 0 }, // p2p-sip
    [6085] = { 4843, 0 }, // konspire2b
    [6086] = { 4844, 0 }, // pdtp
    [6087] = { 4845, 0 }, // ldss
    [6088] = { 4846, 0 }, // doglms
    [6099] = { 4847, 0 }, // raxa-mgmt
    [6100] = { 4848, 0 }, // synchronet-db
    [6101] = { 4849, 0 }, // backupexec
    [6102] = { 4851, 0 }, // synchronet-upd
    [6103] = { 4852, 0 }, // RETS-or-BackupExec
    [6104] = { 4854, 0 }, // dbdb
    [6105] = { 4855, 0 }, // isdninfo
    [6106] = { 4855, 0 }, // isdninfo
    [6107] = { 4858, 0 }, // etc-control
    [6108] = { 4859, 0 }, // sercomm-scadmin
    [6109] = { 4860, 0 }, // globecast-id
    [6110] = { 4861, 0 }, // softcm
    [6111] = { 4862, 0 }, // spc
    [6112] = { 4863, 0 }, // dtspc
    [6113] = { 4865, 0 }, // dayliteserver
    [6114] = { 4866, 0 }, // wrspice
    [6115] = { 4867, 0 }, // xic
    [6116] = { 4868, 0 }, // xtlserv
    [6117] = { 4869, 0 }, // daylitetouch
    [6118] = { 4870, 0 }, // tipc
    [6121] = { 4871, 0 }, // spdy
    [6122] = { 4872, 0 }, // bex-webadmin
    [6123] = { 4873, 0 }, // backup-express
    [6124] = { 4874, 0 }, // pnbs
    [6130] = { 4875, 0 }, // damewaremobgtwy
    [6133] = { 4876, 0 }, // nbt-wol
    [6140] = { 4877, 0 }, // pulsonixnls
    [6141] = { 4878, 0 }, // meta-corp
    [6142] = { 4879, 0 }, // aspentec-lm
    [6143] = { 4880, 0 }, // watershed-lm
    [6144] = { 4881, 0 }, // statsci1-lm
    [6145] = { 4882, 0 }, // statsci2-lm
    [6146] = { 4883, 0 }, // lonewolf-lm
    [6147] = { 4884, 0 }, // montage-lm
    [6148] = { 4885, 0 }, // ricardo-lm
    [6149] = { 4886, 0 }, // tal-pod
    [6159] = { 4887, 0 }, // efb-aci
    [6160] = { 4888, 0 }, // ecmp
    [6161] = { 4889, 0 }, // patrol-ism
    [6162] = { 4890, 0 }, // patrol-coll
    [6163] = { 4891, 0 }, // pscribe
    [6200] = { 4892, 0 }, // lm-x
    [6201] = { 4893, 0 }, // thermo-calc
    [6209] = { 4894, 0 }, // qmtps
    [6222] = { 4895, 0 }, // radmind
    [6241] = { 4896, 0 }, // jeol-nsdtp-1
    [6242] = { 4898, 0 }, // jeol-nsdtp-2
    [6243] = { 4900, 0 }, // jeol-nsdtp-3
    [6244] = { 4902, 0 }, // jeol-nsdtp-4
    [6251] = { 4904, 0 }, // tl1-raw-ssl
    [6252] = { 4905, 0 }, // tl1-ssh
    [6253] = { 4906, 0 }, // crip
    [6267] = { 4907, 0 }, // gld
    [6268] = { 4908, 0 }, // grid
    [6269] = { 4909, 0 }, // grid-alt
    [6300] = { 4910, 0 }, // bmc-grx
    [6301] = { 4911, 0 }, // bmc_ctd_ldap
    [6306] = { 4912, 0 }, // ufmp
    [6315] = { 4913, 0 }, // scup
    [6316] = { 4915, 0 }, // abb-escp
    [6317] = { 4916, 0 }, // nav-data-cmd
    [6320] = { 4917, 0 }, // repsvc
    [6321] = { 4918, 0 }, // emp-server1
    [6322] = { 4919, 0 }, // emp-server2
    [6324] = { 4920, 0 }, // hrd-ncs
    [6325] = { 4921, 0 }, // dt-mgmtsvc
    [6326] = { 4922, 0 }, // dt-vra
    [6343] = { 4923, 0 }, // sflow
    [6344] = { 4924, 0 }, // streletz
    [6346] = { 4925, 0 }, // gnutella
    [6347] = { 4926, 0 }, // gnutella2
    [6350] = { 4927, 0 }, // adap
    [6355] = { 4928, 0 }, // pmcs
    [6360] = { 4929, 0 }, // metaedit-mu
    [6363] = { 4930, 0 }, // ndn
    [6370] = { 4931, 0 }, // metaedit-se
    [6379] = { 4932, 0 }, // redis
    [6382] = { 4933, 0 }, // metatude-mds
    [6389] = { 4934, 0 }, // clariion-evr01
    [6390] = { 4935, 0 }, // metaedit-ws
    [6400] = { 4936, 0 }, // crystalreports
    [6401] = { 4938, 0 }, // crystalenterprise
    [6402] = { 4940, 0 }, // boe-eventsrv
    [6403] = { 4941, 0 }, // boe-cachesvr
    [6404] = { 4942, 0 }, // boe-filesvr
    [6405] = { 4943, 0 }, // boe-pagesvr
    [6406] = { 4944, 0 }, // boe-processsvr
    [6407] = { 4945, 0 }, // boe-resssvr1
    [6408] = { 4946, 0 }, // boe-resssvr2
    [6409] = { 4947, 0 }, // boe-resssvr3
    [6410] = { 4948, 0 }, // boe-resssvr4
    [6417] = { 4949, 0 }, // faxcomservice
    [6418] = { 4950, 0 }, // syserverremote
    [6419] = { 4951, 0 }, // svdrp
    [6420] = { 4952, 0 }, // nim-vdrshell
    [6421] = { 4953, 0 }, // nim-wan
    [6432] = { 4954, 0 }, // pgbouncer
    [6440] = { 4955, 0 }, // heliosd
    [6442] = { 4956, 0 }, // tarp
    [6443] = { 4957, 0 }, // sun-sr-https
    [6444] = { 4958, 0 }, // sge_qmaster
    [6445] = { 4959, 0 }, // sge_execd
    [6446] = { 4960, 0 }, // mysql-proxy
    [6455] = { 4961, 0 }, // skip-cert-recv
    [6456] = { 4962, 0 }, // skip-cert-send
    [6464] = { 4963, 0 }, // ieee11073-20701
    [6471] = { 4964, 0 }, // lvision-lm
    [6480] = { 4965, 0 }, // sun-sr-http
    [6481] = { 4966, 0 }, // servicetags
    [6482] = { 4967, 0 }, // ldoms-mgmt
    [6483] = { 4968, 0 }, // SunVTS-RMI
    [6484] = { 4969, 0 }, // sun-sr-jms
    [6485] = { 4970, 0 }, // sun-sr-iiop
    [6486] = { 4971, 0 }, // sun-sr-iiops
    [6487] = { 4972, 0 }, // sun-sr-iiop-aut
    [6488] = { 4973, 0 }, // sun-sr-jmx
    [6489] = { 4974, 0 }, // sun-sr-admin
    [6500] = { 4975, 0 }, // boks
    [6501] = { 4976, 0 }, // boks_servc
    [6502] = { 1737, 0 }, // netop-rc
    [6503] = { 4977, 0 }, // boks_clntd
    [6505] = { 4978, 0 }, // badm_priv
    [6506] = { 4979, 0 }, // badm_pub
    [6507] = { 4980, 0 }, // bdir_priv
    [6508] = { 4981, 0 }, // bdir_pub
    [6509] = { 4982, 0 }, // mgcs-mfp-port
    [6510] = { 4983, 0 }, // mcer-port
    [6511] = { 4984, 0 }, // dccp-udp
    [6513] = { 4985, 0 }, // netconf-tls
    [6514] = { 4986, 0 }, // syslog-tls
    [6515] = { 4987, 0 }, // elipse-rec
    [6543] = { 4988, 0 }, // mythtv
    [6544] = { 4988, 0 }, // mythtv
    [6547] = { 4991, 0 }, // powerchuteplus
    [6548] = { 4991, 0 }, // powerchuteplus
    [6549] = { 4994, 0 }, // apc-6549
    [6550] = { 4995, 0 }, // fg-sysupdate
    [6551] = { 4996, 0 }, // sum
    [6556] = { 4997, 0 }, // checkmk-agent
    [6558] = { 4998, 0 }, // xdsxdm
    [6566] = { 4999, 0 }, // sane-port
    [6567] = { 5000, 0 }, // esp
    [6568] = { 5001, 0 }, // canit_store
    [6579] = { 5003, 0 }, // affiliate
    [6580] = { 5004, 0 }, // parsec-master
    [6581] = { 5005, 0 }, // parsec-peer
    [6582] = { 5006, 0 }, // parsec-game
    [6583] = { 5007, 0 }, // joaJewelSuite
    [6588] = { 5008, 0 }, // analogx
    [6600] = { 5009, 0 }, // mshvlm
    [6601] = { 5010, 0 }, // mstmg-sstp
    [6602] = { 5011, 0 }, // wsscomfrmwk
    [6619] = { 5012, 0 }, // odette-ftps
    [6620] = { 5013, 0 }, // kftp-data
    [6621] = { 5014, 0 }, // kftp
    [6622] = { 5015, 0 }, // mcftp
    [6623] = { 5016, 0 }, // ktelnet
    [6624] = { 5017, 0 }, // datascaler-db
    [6625] = { 5018, 0 }, // datascaler-ctl
    [6626] = { 5019, 0 }, // wago-service
    [6627] = { 5020, 0 }, // nexgen
    [6628] = { 5021, 0 }, // afesc-mc
    [6629] = { 5022, 0 }, // nexgen-aux
    [6632] = { 5023, 0 }, // mxodbc-connect
    [6633] = { 5024, 0 }, // cisco-vpath-tun
    [6634] = { 5025, 0 }, // mpls-pm
    [6635] = { 5026, 0 }, // mpls-udp
    [6636] = { 5027, 0 }, // mpls-udp-dtls
    [6640] = { 5028, 0 }, // ovsdb
    [6653] = { 5029, 0 }, // openflow
    [6655] = { 5030, 0 }, // pcs-sf-ui-man
    [6656] = { 5031, 0 }, // emgmsg
    [6657] = { 5032, 0 }, // palcom-disc
    [6662] = { 4895, 0 }, // radmind
    [6665] = { 183, 0 }, // irc
    [6666] = { 183, 0 }, // irc
    [6667] = { 183, 0 }, // irc
    [6668] = { 183, 0 }, // irc
    [6669] = { 183, 0 }, // irc
    [6670] = { 183, 0 }, // irc
    [6671] = { 5035, 0 }, // p4p-portal
    [6672] = { 5036, 0 }, // vision_server
    [6673] = { 5037, 0 }, // vision_elmd
    [6678] = { 5038, 0 }, // vfbp
    [6679] = { 5039, 0 }, // osaut
    [6687] = { 5040, 0 }, // clever-ctrace
    [6688] = { 5041, 0 }, // clever-tcpip
    [6689] = { 5042, 0 }, // tsa
    [6690] = { 5043, 0 }, // cleverdetect
    [6696] = { 5044, 0 }, // babel
    [6697] = { 5045, 0 }, // ircs-u
    [6699] = { 5046, 0 }, // napster
    [6700] = { 5047, 0 }, // carracho
    [6701] = { 5047, 0 }, // carracho
    [6702] = { 5049, 0 }, // e-design-net
    [6703] = { 5050, 0 }, // e-design-web
    [6704] = { 5051, 0 }, // frc-hp
    [6705] = { 5052, 0 }, // frc-mp
    [6706] = { 5053, 0 }, // frc-lp
    [6714] = { 5054, 0 }, // ibprotocol
    [6715] = { 5055, 0 }, // fibotrader-com
    [6716] = { 5056, 0 }, // princity-agent
    [6767] = { 5057, 0 }, // bmc-perf-agent
    [6768] = { 5058, 0 }, // bmc-perf-mgrd
    [6769] = { 5059, 0 }, // adi-gxp-srvprt
    [6770] = { 5060, 0 }, // plysrv-http
    [6771] = { 5061, 0 }, // plysrv-https
    [6777] = { 5062, 0 }, // ntz-tracker
    [6778] = { 5063, 0 }, // ntz-p2p-storage
    [6784] = { 5064, 0 }, // bfd-lag
    [6785] = { 5065, 0 }, // dgpf-exchg
    [6786] = { 5066, 0 }, // smc-jmx
    [6787] = { 5067, 0 }, // smc-admin
    [6788] = { 5068, 0 }, // smc-http
    [6789] = { 5069, 0 }, // ibm-db2-admin
    [6790] = { 5071, 0 }, // hnmp
    [6791] = { 5072, 0 }, // hnm
    [6801] = { 5073, 0 }, // acnet
    [6817] = { 5074, 0 }, // pentbox-sim
    [6831] = { 5075, 0 }, // ambit-lm
    [6841] = { 5076, 0 }, // netmo-default
    [6842] = { 5077, 0 }, // netmo-http
    [6850] = { 5078, 0 }, // iccrushmore
    [6868] = { 5079, 0 }, // acctopus-cc
    [6881] = { 5081, 0 }, // bittorrent-tracker
    [6888] = { 5082, 0 }, // muse
    [6900] = { 5083, 0 }, // rtimeviewer
    [6901] = { 5084, 0 }, // jetstream
    [6924] = { 5085, 0 }, // split-ping
    [6935] = { 5086, 0 }, // ethoscan
    [6936] = { 5087, 0 }, // xsmsvc
    [6946] = { 5088, 0 }, // bioserver
    [6951] = { 5089, 0 }, // otlp
    [6961] = { 5090, 0 }, // jmact3
    [6962] = { 5091, 0 }, // jmevt2
    [6963] = { 5092, 0 }, // swismgr1
    [6964] = { 5093, 0 }, // swismgr2
    [6965] = { 5094, 0 }, // swistrap
    [6966] = { 5095, 0 }, // swispol
    [6969] = { 5096, 0 }, // acmsoda
    [6970] = { 5097, 0 }, // conductor
    [6980] = { 5098, 0 }, // qolyester
    [6997] = { 5099, 0 }, // MobilitySrv
    [6998] = { 5100, 0 }, // iatp-highpri
    [6999] = { 5101, 0 }, // iatp-normalpri
    [7000] = { 5102, 0 }, // afs3-fileserver
    [7001] = { 5103, 0 }, // afs3-callback
    [7002] = { 5104, 0 }, // afs3-prserver
    [7003] = { 5105, 0 }, // afs3-vlserver
    [7004] = { 5106, 0 }, // afs3-kaserver
    [7005] = { 5107, 0 }, // afs3-volser
    [7006] = { 5108, 0 }, // afs3-errors
    [7007] = { 5109, 0 }, // afs3-bos
    [7008] = { 5110, 0 }, // afs3-update
    [7009] = { 5111, 0 }, // afs3-rmtsys
    [7010] = { 5112, 0 }, // ups-onlinet
    [7011] = { 5113, 0 }, // talon-disc
    [7012] = { 5114, 0 }, // talon-engine
    [7013] = { 5115, 0 }, // microtalon-dis
    [7014] = { 5116, 0 }, // microtalon-com
    [7015] = { 5117, 0 }, // talon-webserver
    [7016] = { 5118, 0 }, // spg
    [7017] = { 5119, 0 }, // grasp
    [7018] = { 5120, 0 }, // fisa-svc
    [7019] = { 5121, 0 }, // doceri-ctl
    [7020] = { 5122, 0 }, // dpserve
    [7021] = { 5123, 0 }, // dpserveadmin
    [7022] = { 5124, 0 }, // ctdp
    [7023] = { 5125, 0 }, // ct2nmcs
    [7024] = { 5126, 0 }, // vmsvc
    [7025] = { 5127, 0 }, // vmsvc-2
    [7026] = { 5128, 0 }, // loreji-panel
    [7030] = { 5129, 0 }, // op-probe
    [7031] = { 5130, 0 }, // iposplanet
    [7040] = { 5131, 0 }, // quest-disc
    [7070] = { 5132, 0 }, // realserver
    [7071] = { 5134, 0 }, // iwg1
    [7072] = { 5135, 0 }, // iba-cfg
    [7073] = { 5136, 0 }, // martalk
    [7080] = { 5137, 0 }, // empowerid
    [7088] = { 5138, 0 }, // zixi-transport
    [7095] = { 5139, 0 }, // jdp-disc
    [7099] = { 5140, 0 }, // lazy-ptop
    [7100] = { 5141, 0 }, // font-service
    [7101] = { 5142, 0 }, // elcn
    [7107] = { 5143, 0 }, // aes-x170
    [7117] = { 5144, 0 }, // rothaga
    [7121] = { 5145, 0 }, // virprot-lm
    [7123] = { 5146, 0 }, // snif
    [7128] = { 5147, 0 }, // scenidm
    [7129] = { 5148, 0 }, // scenccs
    [7161] = { 5149, 0 }, // cabsm-comm
    [7162] = { 5150, 0 }, // caistoragemgr
    [7163] = { 5151, 0 }, // cacsambroker
    [7164] = { 5152, 0 }, // fsr
    [7165] = { 5153, 0 }, // doc-server
    [7166] = { 5154, 0 }, // aruba-server
    [7167] = { 5155, 0 }, // casrmagent
    [7168] = { 5156, 0 }, // cnckadserver
    [7169] = { 5157, 0 }, // ccag-pib
    [7170] = { 5158, 0 }, // nsrp
    [7171] = { 5159, 0 }, // drm-production
    [7172] = { 5160, 0 }, // metalbend
    [7173] = { 5161, 0 }, // zsecure
    [7174] = { 5162, 0 }, // clutild
    [7181] = { 5163, 0 }, // janus-disc
    [7200] = { 5164, 0 }, // fodms
    [7201] = { 5165, 0 }, // dlip
    [7202] = { 5166, 0 }, // pon-ictp
    [7215] = { 5167, 0 }, // PS-Server
    [7216] = { 5168, 0 }, // PS-Capture-Pro
    [7227] = { 5169, 0 }, // ramp
    [7228] = { 5170, 0 }, // citrixupp
    [7229] = { 5171, 0 }, // citrixuppg
    [7234] = { 5172, 0 }, // asa-gateways
    [7235] = { 5173, 0 }, // aspcoordination
    [7236] = { 5174, 0 }, // display
    [7237] = { 5175, 0 }, // pads
    [7244] = { 5176, 0 }, // frc-hicp
    [7262] = { 5177, 0 }, // cnap
    [7272] = { 5178, 0 }, // watchme-7272
    [7273] = { 5179, 0 }, // openmanage
    [7274] = { 5181, 0 }, // oma-rlp-s
    [7275] = { 5182, 0 }, // oma-ulp
    [7276] = { 5183, 0 }, // oma-ilp
    [7277] = { 5184, 0 }, // oma-ilp-s
    [7278] = { 5185, 0 }, // oma-dcdocbs
    [7279] = { 5186, 0 }, // ctxlic
    [7280] = { 5187, 0 }, // itactionserver1
    [7281] = { 5188, 0 }, // itactionserver2
    [7282] = { 5189, 0 }, // mzca-action
    [7283] = { 5191, 0 }, // genstat
    [7300] = { 5192, 0 }, // swx
    [7301] = { 5192, 0 }, // swx
    [7302] = { 5192, 0 }, // swx
    [7303] = { 5192, 0 }, // swx
    [7304] = { 5192, 0 }, // swx
    [7305] = { 5192, 0 }, // swx
    [7306] = { 5192, 0 }, // swx
    [7307] = { 5192, 0 }, // swx
    [7308] = { 5192, 0 }, // swx
    [7309] = { 5192, 0 }, // swx
    [7310] = { 5192, 0 }, // swx
    [7311] = { 5192, 0 }, // swx
    [7312] = { 5192, 0 }, // swx
    [7313] = { 5192, 0 }, // swx
    [7314] = { 5192, 0 }, // swx
    [7315] = { 5192, 0 }, // swx
    [7316] = { 5192, 0 }, // swx
    [7317] = { 5192, 0 }, // swx
    [7318] = { 5192, 0 }, // swx
    [7319] = { 5192, 0 }, // swx
    [7320] = { 5192, 0 }, // swx
    [7321] = { 5192, 0 }, // swx
    [7322] = { 5192, 0 }, // swx
    [7323] = { 5192, 0 }, // swx
    [7324] = { 5192, 0 }, // swx
    [7325] = { 5192, 0 }, // swx
    [7326] = { 5193, 0 }, // icb
    [7327] = { 5192, 0 }, // swx
    [7328] = { 5192, 0 }, // swx
    [7329] = { 5192, 0 }, // swx
    [7330] = { 5192, 0 }, // swx
    [7331] = { 5192, 0 }, // swx
    [7332] = { 5192, 0 }, // swx
    [7333] = { 5192, 0 }, // swx
    [7334] = { 5192, 0 }, // swx
    [7335] = { 5192, 0 }, // swx
    [7336] = { 5192, 0 }, // swx
    [7337] = { 5192, 0 }, // swx
    [7338] = { 5192, 0 }, // swx
    [7339] = { 5192, 0 }, // swx
    [7340] = { 5192, 0 }, // swx
    [7341] = { 5192, 0 }, // swx
    [7342] = { 5192, 0 }, // swx
    [7343] = { 5192, 0 }, // swx
    [7344] = { 5192, 0 }, // swx
    [7345] = { 5192, 0 }, // swx
    [7346] = { 5192, 0 }, // swx
    [7347] = { 5192, 0 }, // swx
    [7348] = { 5192, 0 }, // swx
    [7349] = { 5192, 0 }, // swx
    [7350] = { 5192, 0 }, // swx
    [7351] = { 5192, 0 }, // swx
    [7352] = { 5192, 0 }, // swx
    [7353] = { 5192, 0 }, // swx
    [7354] = { 5192, 0 }, // swx
    [7355] = { 5192, 0 }, // swx
    [7356] = { 5192, 0 }, // swx
    [7357] = { 5192, 0 }, // swx
    [7358] = { 5192, 0 }, // swx
    [7359] = { 5192, 0 }, // swx
    [7365] = { 5194, 0 }, // lcm-server
    [7391] = { 5195, 0 }, // mindfilesys
    [7392] = { 5196, 0 }, // mrssrendezvous
    [7393] = { 5197, 0 }, // nfoldman
    [7394] = { 5198, 0 }, // fse
    [7395] = { 5199, 0 }, // winqedit
    [7397] = { 5200, 0 }, // hexarc
    [7400] = { 5201, 0 }, // rtps-discovery
    [7401] = { 5202, 0 }, // rtps-dd-ut
    [7402] = { 5203, 0 }, // rtps-dd-mt
    [7410] = { 5204, 0 }, // ionixnetmon
    [7411] = { 5205, 0 }, // daqstream
    [7420] = { 5206, 0 }, // ipluminary
    [7421] = { 5207, 0 }, // mtportmon
    [7426] = { 5208, 0 }, // pmdmgr
    [7427] = { 5209, 0 }, // oveadmgr
    [7428] = { 5210, 0 }, // ovladmgr
    [7429] = { 5211, 0 }, // opi-sock
    [7430] = { 5212, 0 }, // xmpv7
    [7431] = { 5213, 0 }, // pmd
    [7437] = { 5214, 0 }, // faximum
    [7443] = { 5215, 0 }, // oracleas-https
    [7464] = { 5216, 0 }, // pythonds
    [7471] = { 5217, 0 }, // sttunnel
    [7473] = { 5218, 0 }, // rise
    [7474] = { 5219, 0 }, // neo4j
    [7478] = { 5220, 0 }, // openit
    [7491] = { 5221, 0 }, // telops-lmd
    [7500] = { 5222, 0 }, // silhouette
    [7501] = { 5223, 0 }, // ovbus
    [7508] = { 5224, 0 }, // adcp
    [7509] = { 5225, 0 }, // acplt
    [7510] = { 5226, 0 }, // ovhpas
    [7511] = { 5227, 0 }, // pafec-lm
    [7542] = { 5228, 0 }, // saratoga
    [7543] = { 5229, 0 }, // atul
    [7544] = { 5230, 0 }, // nta-ds
    [7545] = { 5231, 0 }, // nta-us
    [7546] = { 2836, 0 }, // cfs
    [7547] = { 5232, 0 }, // cwmp
    [7548] = { 5233, 0 }, // tidp
    [7549] = { 5234, 0 }, // nls-tl
    [7550] = { 5235, 0 }, // cloudsignaling
    [7551] = { 5236, 0 }, // controlone-con
    [7560] = { 5237, 0 }, // sncp
    [7563] = { 5238, 0 }, // cfw
    [7566] = { 5239, 0 }, // vsi-omega
    [7569] = { 5240, 0 }, // dell-eql-asm
    [7570] = { 5241, 0 }, // aries-kfinder
    [7574] = { 5242, 0 }, // coherence
    [7588] = { 5243, 0 }, // sun-lm
    [7597] = { 5244, 0 }, // qaz
    [7606] = { 5245, 0 }, // mipi-debug
    [7624] = { 5246, 0 }, // indi
    [7626] = { 5247, 0 }, // simco
    [7627] = { 5248, 0 }, // soap-http
    [7628] = { 5249, 0 }, // zen-pawn
    [7629] = { 5250, 0 }, // xdas
    [7630] = { 5251, 0 }, // hawk
    [7631] = { 5252, 0 }, // tesla-sys-msg
    [7633] = { 5253, 0 }, // pmdfmgt
    [7634] = { 5254, 0 }, // hddtemp
    [7648] = { 5255, 0 }, // cuseeme
    [7649] = { 5257, 0 }, // cucme-2
    [7650] = { 5258, 0 }, // cucme-3
    [7651] = { 5259, 0 }, // cucme-4
    [7663] = { 5260, 0 }, // rome
    [7672] = { 5261, 0 }, // imqstomp
    [7673] = { 5262, 0 }, // imqstomps
    [7674] = { 5263, 0 }, // imqtunnels
    [7675] = { 5264, 0 }, // imqtunnel
    [7676] = { 5265, 0 }, // imqbrokerd
    [7677] = { 5266, 0 }, // sun-user-https
    [7680] = { 5267, 0 }, // pando-pub
    [7683] = { 5268, 0 }, // dmt
    [7687] = { 5269, 0 }, // bolt
    [7689] = { 5270, 0 }, // collaber
    [7690] = { 5271, 0 }, // sovd
    [7697] = { 5272, 0 }, // klio
    [7700] = { 5273, 0 }, // em7-secom
    [7701] = { 5274, 0 }, // nfapi
    [7707] = { 5275, 0 }, // sync-em7
    [7708] = { 5276, 0 }, // scinet
    [7720] = { 5277, 0 }, // medimageportal
    [7724] = { 5278, 0 }, // nsdeepfreezectl
    [7725] = { 5279, 0 }, // nitrogen
    [7726] = { 5280, 0 }, // freezexservice
    [7727] = { 5281, 0 }, // trident-data
    [7728] = { 5282, 0 }, // osvr
    [7734] = { 5283, 0 }, // smip
    [7738] = { 5284, 0 }, // aiagent
    [7741] = { 5285, 0 }, // scriptview
    [7742] = { 5286, 0 }, // msss
    [7743] = { 5287, 0 }, // sstp-1
    [7744] = { 5288, 0 }, // raqmon-pdu
    [7747] = { 5289, 0 }, // prgp
    [7775] = { 5290, 0 }, // inetfs
    [7777] = { 5291, 0 }, // cbt
    [7778] = { 5292, 0 }, // interwise
    [7779] = { 5293, 0 }, // vstat
    [7781] = { 5294, 0 }, // accu-lmgr
    [7784] = { 5295, 0 }, // s-bfd
    [7786] = { 5296, 0 }, // minivend
    [7787] = { 5297, 0 }, // popup-reminders
    [7789] = { 5298, 0 }, // office-tools
    [7794] = { 5299, 0 }, // q3ade
    [7797] = { 5300, 0 }, // pnet-conn
    [7798] = { 5301, 0 }, // pnet-enc
    [7799] = { 5302, 0 }, // altbsdp
    [7800] = { 5303, 0 }, // asr
    [7801] = { 5304, 0 }, // ssp-client
    [7802] = { 5305, 0 }, // vns-tp
    [7810] = { 5306, 0 }, // rbt-wanopt
    [7845] = { 5307, 0 }, // apc-7845
    [7846] = { 5308, 0 }, // apc-7846
    [7847] = { 5309, 0 }, // csoauth
    [7869] = { 5310, 0 }, // mobileanalyzer
    [7870] = { 5311, 0 }, // rbt-smc
    [7871] = { 5312, 0 }, // mdm
    [7872] = { 5313, 0 }, // mipv6tls
    [7878] = { 5314, 0 }, // owms
    [7880] = { 5315, 0 }, // pss
    [7887] = { 5316, 0 }, // ubroker
    [7900] = { 5317, 0 }, // mevent
    [7901] = { 5318, 0 }, // tnos-sp
    [7902] = { 5319, 0 }, // tnos-dp
    [7903] = { 5320, 0 }, // tnos-dps
    [7913] = { 5321, 0 }, // qo-secure
    [7932] = { 5322, 0 }, // t2-drm
    [7933] = { 5323, 0 }, // t2-brm
    [7937] = { 5324, 0 }, // nsrexecd
    [7938] = { 5325, 0 }, // lgtomapper
    [7962] = { 5326, 0 }, // generalsync
    [7967] = { 5327, 0 }, // supercell
    [7979] = { 5328, 0 }, // micromuse-ncps
    [7980] = { 5329, 0 }, // quest-vista
    [7981] = { 5330, 0 }, // sossd-collect
    [7982] = { 5331, 0 }, // sossd-agent
    [7997] = { 5333, 0 }, // pushns
    [7998] = { 5334, 0 }, // usicontentpush
    [7999] = { 5335, 0 }, // irdmi2
    [8000] = { 523, 0 }, // http-alt
    [8001] = { 5337, 0 }, // vcom-tunnel
    [8002] = { 5338, 0 }, // teradataordbms
    [8003] = { 5339, 0 }, // mcreport
    [8004] = { 5340, 0 }, // p2pevolvenet
    [8005] = { 5341, 0 }, // mxi
    [8006] = { 5342, 0 }, // wpl-analytics
    [8007] = { 5343, 0 }, // ajp12
    [8008] = { 65, 0 }, // http
    [8009] = { 5344, 0 }, // ajp13
    [8010] = { 5345, 0 }, // xmpp
    [8015] = { 5346, 0 }, // cfg-cloud
    [8016] = { 5347, 0 }, // ads-s
    [8017] = { 5348, 0 }, // cisco-cloudsec
    [8019] = { 5349, 0 }, // qbdb
    [8020] = { 5350, 0 }, // intu-ec-svcdisc
    [8021] = { 5351, 0 }, // ftp-proxy
    [8022] = { 5353, 0 }, // oa-system
    [8023] = { 5354, 0 }, // arca-api
    [8025] = { 5355, 0 }, // ca-audit-da
    [8026] = { 5356, 0 }, // ca-audit-ds
    [8027] = { 5357, 0 }, // papachi-p2p-srv
    [8032] = { 5358, 0 }, // pro-ed
    [8033] = { 5359, 0 }, // mindprint
    [8034] = { 5360, 0 }, // vantronix-mgmt
    [8040] = { 5361, 0 }, // ampify
    [8041] = { 5362, 0 }, // enguity-xccetp
    [8042] = { 5363, 0 }, // fs-agent
    [8043] = { 5364, 0 }, // fs-server
    [8044] = { 5365, 0 }, // fs-mgmt
    [8051] = { 5366, 0 }, // rocrail
    [8052] = { 5367, 0 }, // senomix01
    [8053] = { 5368, 0 }, // senomix02
    [8054] = { 5369, 0 }, // senomix03
    [8055] = { 5370, 0 }, // senomix04
    [8056] = { 5371, 0 }, // senomix05
    [8057] = { 5372, 0 }, // senomix06
    [8058] = { 5373, 0 }, // senomix07
    [8059] = { 5374, 0 }, // senomix08
    [8060] = { 5375, 0 }, // aero
    [8066] = { 5376, 0 }, // toad-bi-appsrvr
    [8067] = { 5377, 0 }, // infi-async
    [8070] = { 5378, 0 }, // ucs-isc
    [8074] = { 5379, 0 }, // gadugadu
    [8076] = { 2812, 0 }, // slnp
    [8077] = { 5380, 0 }, // mles
    [8080] = { 5381, 0 }, // http-proxy
    [8081] = { 5382, 0 }, // blackice-icecap
    [8082] = { 5384, 0 }, // blackice-alerts
    [8083] = { 5386, 0 }, // us-srv
    [8084] = { 5387, 0 }, // websnp
    [8086] = { 5388, 0 }, // d-s-n
    [8087] = { 5389, 0 }, // simplifymedia
    [8088] = { 5390, 0 }, // radan-http
    [8090] = { 5391, 0 }, // opsmessaging
    [8091] = { 5392, 0 }, // jamlink
    [8097] = { 5393, 0 }, // sac
    [8100] = { 5394, 0 }, // xprint-server
    [8101] = { 5395, 0 }, // ldoms-migr
    [8102] = { 5396, 0 }, // kz-migr
    [8111] = { 5397, 0 }, // skynetflow
    [8115] = { 5398, 0 }, // mtl8000-matrix
    [8116] = { 5399, 0 }, // cp-cluster
    [8117] = { 5400, 0 }, // purityrpc
    [8118] = { 5401, 0 }, // privoxy
    [8121] = { 5402, 0 }, // apollo-data
    [8122] = { 5403, 0 }, // apollo-admin
    [8123] = { 5404, 0 }, // polipo
    [8128] = { 5405, 0 }, // paycash-online
    [8129] = { 5406, 0 }, // paycash-wbp
    [8130] = { 5407, 0 }, // indigo-vrmi
    [8131] = { 5408, 0 }, // indigo-vbcp
    [8132] = { 5409, 0 }, // dbabble
    [8140] = { 5410, 0 }, // puppet
    [8148] = { 5411, 0 }, // isdd
    [8149] = { 5412, 0 }, // eor-game
    [8153] = { 5413, 0 }, // quantastor
    [8160] = { 5414, 0 }, // patrol
    [8161] = { 5415, 0 }, // patrol-snmp
    [8162] = { 5416, 0 }, // lpar2rrd
    [8181] = { 5417, 0 }, // intermapper
    [8182] = { 5418, 0 }, // vmware-fdm
    [8183] = { 5419, 0 }, // proremote
    [8184] = { 5420, 0 }, // itach
    [8190] = { 5421, 0 }, // gcp-rphy
    [8191] = { 5422, 0 }, // limnerpressure
    [8192] = { 5423, 0 }, // sophos
    [8193] = { 5423, 0 }, // sophos
    [8194] = { 5423, 0 }, // sophos
    [8195] = { 5424, 0 }, // blp2
    [8199] = { 5425, 0 }, // vvr-data
    [8200] = { 5426, 0 }, // trivnet1
    [8201] = { 5427, 0 }, // trivnet2
    [8202] = { 5428, 0 }, // aesop
    [8204] = { 5429, 0 }, // lm-perfworks
    [8205] = { 5430, 0 }, // lm-instmgr
    [8206] = { 5431, 0 }, // lm-dta
    [8207] = { 5432, 0 }, // lm-sserver
    [8208] = { 5433, 0 }, // lm-webwatcher
    [8211] = { 5434, 0 }, // aruba-papi
    [8230] = { 5435, 0 }, // rexecj
    [8231] = { 5436, 0 }, // hncp-udp-port
    [8232] = { 5437, 0 }, // hncp-dtls-port
    [8243] = { 5438, 0 }, // synapse-nhttps
    [8266] = { 5439, 0 }, // espeasy-p2p
    [8270] = { 5440, 0 }, // robot-remote
    [8276] = { 5441, 0 }, // pando-sec
    [8280] = { 5442, 0 }, // synapse-nhttp
    [8282] = { 5443, 0 }, // libelle
    [8292] = { 5444, 0 }, // blp3
    [8293] = { 5445, 0 }, // hiperscan-id
    [8294] = { 5446, 0 }, // blp4
    [8300] = { 5447, 0 }, // tmi
    [8301] = { 5448, 0 }, // amberon
    [8313] = { 5449, 0 }, // hub-open-net
    [8320] = { 5450, 0 }, // tnp-discover
    [8321] = { 5451, 0 }, // tnp
    [8322] = { 5452, 0 }, // garmin-marine
    [8333] = { 5453, 0 }, // bitcoin
    [8351] = { 5454, 0 }, // server-find
    [8376] = { 5455, 0 }, // cruise-enum
    [8377] = { 5456, 0 }, // cruise-swroute
    [8378] = { 5457, 0 }, // cruise-config
    [8379] = { 5458, 0 }, // cruise-diags
    [8380] = { 5459, 0 }, // cruise-update
    [8383] = { 5460, 0 }, // m2mservices
    [8384] = { 5461, 0 }, // marathontp
    [8400] = { 5462, 0 }, // cvd
    [8401] = { 5463, 0 }, // sabarsd
    [8402] = { 5464, 0 }, // abarsd
    [8403] = { 3073, 0 }, // admind
    [8404] = { 5465, 0 }, // svcloud
    [8405] = { 5466, 0 }, // svbackup
    [8415] = { 5467, 0 }, // dlpx-sp
    [8416] = { 5468, 0 }, // espeech
    [8417] = { 5469, 0 }, // espeech-rtp
    [8423] = { 5470, 0 }, // aritts
    [8432] = { 5471, 0 }, // pgbackrest
    [8442] = { 5472, 0 }, // cybro-a-bus
    [8443] = { 5473, 0 }, // https-alt
    [8444] = { 5475, 0 }, // pcsync-http
    [8445] = { 5476, 0 }, // copy
    [8450] = { 5477, 0 }, // npmp
    [8457] = { 5478, 0 }, // nexentamv
    [8470] = { 5479, 0 }, // cisco-avp
    [8471] = { 5480, 0 }, // pim-port
    [8472] = { 5481, 0 }, // otv
    [8473] = { 5482, 0 }, // vp2p
    [8474] = { 5483, 0 }, // noteshare
    [8500] = { 5484, 0 }, // fmtp
    [8501] = { 5485, 0 }, // cmtp-mgt
    [8502] = { 5486, 0 }, // ftnmtp
    [8503] = { 5487, 0 }, // lsp-self-ping
    [8554] = { 5488, 0 }, // rtsp-alt
    [8555] = { 5489, 0 }, // d-fence
    [8567] = { 5490, 0 }, // oap-admin
    [8600] = { 5491, 0 }, // asterix
    [8609] = { 5492, 0 }, // canon-cpp-disc
    [8610] = { 5493, 0 }, // canon-mfnp
    [8611] = { 5494, 0 }, // canon-bjnp1
    [8612] = { 5495, 0 }, // canon-bjnp2
    [8613] = { 5496, 0 }, // canon-bjnp3
    [8614] = { 5497, 0 }, // canon-bjnp4
    [8615] = { 5498, 0 }, // imink
    [8665] = { 5499, 0 }, // monetra
    [8666] = { 5500, 0 }, // monetra-admin
    [8675] = { 5501, 0 }, // msi-cps-rm
    [8686] = { 5502, 0 }, // sun-as-jmxrmi
    [8688] = { 5503, 0 }, // openremote-ctrl
    [8699] = { 5504, 0 }, // vnyx
    [8710] = { 5505, 0 }, // semi-grpc
    [8711] = { 5506, 0 }, // nvc
    [8732] = { 5507, 0 }, // dtp-net
    [8733] = { 5508, 0 }, // ibus
    [8750] = { 5509, 0 }, // dey-keyneg
    [8763] = { 5510, 0 }, // mc-appserver
    [8764] = { 5511, 0 }, // openqueue
    [8765] = { 5512, 0 }, // ultraseek-http
    [8766] = { 5513, 0 }, // amcs
    [8767] = { 5514, 0 }, // core-of-source
    [8768] = { 5515, 0 }, // sandpolis
    [8769] = { 5516, 0 }, // oktaauthenticat
    [8770] = { 5517, 0 }, // apple-iphoto
    [8778] = { 5519, 0 }, // uec
    [8786] = { 5520, 0 }, // msgclnt
    [8787] = { 5521, 0 }, // msgsrvr
    [8793] = { 2045, 0 }, // acd-pm
    [8800] = { 5522, 0 }, // sunwebadmin
    [8804] = { 5523, 0 }, // truecm
    [8805] = { 5524, 0 }, // pfcp
    [8807] = { 5525, 0 }, // hes-clip
    [8808] = { 5526, 0 }, // ssports-bcast
    [8809] = { 5527, 0 }, // 3gpp-monp
    [8834] = { 5528, 0 }, // nessus-xmlrpc
    [8873] = { 5529, 0 }, // dxspider
    [8880] = { 5530, 0 }, // cddbp-alt
    [8881] = { 5531, 0 }, // galaxy4d
    [8883] = { 5532, 0 }, // secure-mqtt
    [8888] = { 5533, 0 }, // sun-answerbook
    [8889] = { 5535, 0 }, // ddi-tcp-2
    [8890] = { 5537, 0 }, // ddi-tcp-3
    [8891] = { 5539, 0 }, // ddi-tcp-4
    [8892] = { 5541, 0 }, // seosload
    [8893] = { 5543, 0 }, // ddi-tcp-6
    [8894] = { 5545, 0 }, // ddi-tcp-7
    [8899] = { 5547, 0 }, // ospf-lite
    [8900] = { 5548, 0 }, // jmb-cds1
    [8901] = { 5549, 0 }, // jmb-cds2
    [8908] = { 5550, 0 }, // dpp
    [8910] = { 5551, 0 }, // manyone-http
    [8911] = { 5552, 0 }, // manyone-xml
    [8912] = { 5553, 0 }, // wcbackup
    [8913] = { 5554, 0 }, // dragonfly
    [8937] = { 5555, 0 }, // twds
    [8953] = { 5556, 0 }, // ub-dns-control
    [8954] = { 5557, 0 }, // cumulus-admin
    [8980] = { 5558, 0 }, // nod-provider
    [8981] = { 5559, 0 }, // nod-client
    [8989] = { 5560, 0 }, // sunwebadmins
    [8990] = { 5561, 0 }, // http-wmap
    [8991] = { 5562, 0 }, // https-wmap
    [8997] = { 5563, 0 }, // oracle-ms-ens
    [8998] = { 5564, 0 }, // canto-roboflow
    [8999] = { 5565, 0 }, // bctp
    [9000] = { 5566, 0 }, // cslistener
    [9001] = { 5567, 0 }, // tor-orport
    [9002] = { 5569, 0 }, // dynamid
    [9005] = { 5570, 0 }, // golem
    [9007] = { 5571, 0 }, // ogs-client
    [9008] = { 5572, 0 }, // ogs-server
    [9009] = { 5573, 0 }, // pichat
    [9010] = { 5574, 0 }, // sdr
    [9011] = { 5575, 0 }, // d-star
    [9020] = { 5576, 0 }, // tambora
    [9021] = { 5577, 0 }, // panagolin-ident
    [9022] = { 5578, 0 }, // paragent
    [9023] = { 5579, 0 }, // swa-1
    [9024] = { 5580, 0 }, // swa-2
    [9025] = { 5581, 0 }, // swa-3
    [9026] = { 5582, 0 }, // swa-4
    [9040] = { 5583, 0 }, // tor-trans
    [9050] = { 5584, 0 }, // tor-socks
    [9051] = { 5585, 0 }, // tor-control
    [9060] = { 5586, 0 }, // CardWeb-IO
    [9080] = { 5587, 0 }, // glrpc
    [9081] = { 5588, 0 }, // cisco-aqos
    [9082] = { 5589, 0 }, // lcs-ap
    [9083] = { 5590, 0 }, // emc-pp-mgmtsvc
    [9084] = { 5591, 0 }, // aurora
    [9085] = { 5592, 0 }, // ibm-rsyscon
    [9086] = { 5593, 0 }, // net2display
    [9087] = { 5594, 0 }, // classic
    [9088] = { 5595, 0 }, // sqlexec
    [9089] = { 5596, 0 }, // sqlexec-ssl
    [9090] = { 5597, 0 }, // zeus-admin
    [9091] = { 5599, 0 }, // xmltec-xmlmail
    [9092] = { 5600, 0 }, // XmlIpcRegSvc
    [9093] = { 5601, 0 }, // copycat
    [9100] = { 5602, 0 }, // jetdirect
    [9101] = { 5602, 0 }, // jetdirect
    [9102] = { 5602, 0 }, // jetdirect
    [9103] = { 5602, 0 }, // jetdirect
    [9104] = { 5602, 0 }, // jetdirect
    [9105] = { 5602, 0 }, // jetdirect
    [9106] = { 5602, 0 }, // jetdirect
    [9107] = { 5602, 0 }, // jetdirect
    [9111] = { 5610, 0 }, // DragonIDSConsole
    [9119] = { 5611, 0 }, // mxit
    [9122] = { 5612, 0 }, // grcmp
    [9123] = { 5613, 0 }, // grcp
    [9131] = { 5614, 0 }, // dddp
    [9152] = { 5615, 0 }, // ms-sql2000
    [9160] = { 5616, 0 }, // apani1
    [9161] = { 5617, 0 }, // apani2
    [9162] = { 5618, 0 }, // apani3
    [9163] = { 5619, 0 }, // apani4
    [9164] = { 5620, 0 }, // apani5
    [9191] = { 5621, 0 }, // sun-as-jpda
    [9200] = { 5622, 0 }, // wap-wsp
    [9201] = { 5623, 0 }, // wap-wsp-wtp
    [9202] = { 5624, 0 }, // wap-wsp-s
    [9203] = { 5625, 0 }, // wap-wsp-wtp-s
    [9204] = { 5626, 0 }, // wap-vcard
    [9205] = { 5627, 0 }, // wap-vcal
    [9206] = { 5628, 0 }, // wap-vcard-s
    [9207] = { 5629, 0 }, // wap-vcal-s
    [9208] = { 5630, 0 }, // rjcdb-vcards
    [9209] = { 5631, 0 }, // almobile-system
    [9210] = { 5632, 0 }, // oma-mlp
    [9211] = { 5633, 0 }, // oma-mlp-s
    [9212] = { 5634, 0 }, // serverviewdbms
    [9213] = { 5635, 0 }, // serverstart
    [9214] = { 5636, 0 }, // ipdcesgbs
    [9215] = { 5637, 0 }, // insis
    [9216] = { 5638, 0 }, // acme
    [9217] = { 5639, 0 }, // fsc-port
    [9222] = { 5640, 0 }, // teamcoherence
    [9255] = { 2365, 0 }, // mon
    [9277] = { 5641, 0 }, // traingpsdata
    [9278] = { 5642, 0 }, // pegasus
    [9279] = { 5643, 0 }, // pegasus-ctl
    [9280] = { 5644, 0 }, // pgps
    [9281] = { 5645, 0 }, // swtp-port1
    [9282] = { 5646, 0 }, // swtp-port2
    [9283] = { 5647, 0 }, // callwaveiam
    [9284] = { 5648, 0 }, // visd
    [9285] = { 5649, 0 }, // n2h2server
    [9286] = { 5650, 0 }, // n2receive
    [9287] = { 5651, 0 }, // cumulus
    [9292] = { 5652, 0 }, // armtechdaemon
    [9293] = { 5653, 0 }, // storview
    [9294] = { 5654, 0 }, // armcenterhttp
    [9295] = { 5655, 0 }, // armcenterhttps
    [9300] = { 5656, 0 }, // vrace
    [9306] = { 5657, 0 }, // sphinxql
    [9310] = { 5658, 0 }, // sapms
    [9312] = { 5659, 0 }, // sphinxapi
    [9318] = { 5660, 0 }, // secure-ts
    [9321] = { 5661, 0 }, // guibase
    [9333] = { 5662, 0 }, // litecoin
    [9339] = { 5663, 0 }, // gnmi-gnoi
    [9340] = { 5664, 0 }, // gribi
    [9343] = { 5665, 0 }, // mpidcmgr
    [9344] = { 5666, 0 }, // mphlpdmc
    [9345] = { 5667, 0 }, // rancher
    [9346] = { 5668, 0 }, // ctechlicensing
    [9374] = { 5669, 0 }, // fjdmimgr
    [9380] = { 5670, 0 }, // boxp
    [9387] = { 5671, 0 }, // d2dconfig
    [9388] = { 5672, 0 }, // d2ddatatrans
    [9389] = { 5673, 0 }, // adws
    [9390] = { 5674, 0 }, // otp
    [9396] = { 5675, 0 }, // fjinvmgr
    [9397] = { 5676, 0 }, // mpidcagt
    [9400] = { 5677, 0 }, // sec-t4net-srv
    [9401] = { 5678, 0 }, // sec-t4net-clt
    [9402] = { 5679, 0 }, // sec-pc2fax-srv
    [9418] = { 5680, 0 }, // git
    [9443] = { 5681, 0 }, // tungsten-https
    [9444] = { 5682, 0 }, // wso2esb-console
    [9445] = { 5683, 0 }, // mindarray-ca
    [9450] = { 5684, 0 }, // sntlkeyssrvr
    [9500] = { 5685, 0 }, // ismserver
    [9522] = { 5686, 0 }, // sma-spw
    [9535] = { 5687, 0 }, // man
    [9536] = { 5688, 0 }, // laes-bf
    [9555] = { 5689, 0 }, // trispen-sra
    [9559] = { 5690, 0 }, // p4runtime
    [9592] = { 5691, 0 }, // ldgateway
    [9593] = { 5692, 0 }, // cba8
    [9594] = { 5693, 0 }, // msgsys
    [9595] = { 5694, 0 }, // pds
    [9596] = { 5695, 0 }, // mercury-disc
    [9597] = { 5696, 0 }, // pd-admin
    [9598] = { 5697, 0 }, // vscp
    [9599] = { 5698, 0 }, // robix
    [9600] = { 5699, 0 }, // micromuse-ncpw
    [9612] = { 5700, 0 }, // streamcomm-ds
    [9614] = { 5701, 0 }, // iadt-tls
    [9616] = { 5702, 0 }, // erunbook_agent
    [9617] = { 5703, 0 }, // erunbook_server
    [9618] = { 5704, 0 }, // condor
    [9628] = { 5705, 0 }, // odbcpathway
    [9629] = { 5706, 0 }, // uniport
    [9630] = { 5707, 0 }, // peoctlr
    [9631] = { 5708, 0 }, // peocoll
    [9632] = { 5709, 0 }, // mc-comm
    [9640] = { 5710, 0 }, // pqsflows
    [9666] = { 5711, 0 }, // zoomcp
    [9667] = { 5712, 0 }, // xmms2
    [9668] = { 5713, 0 }, // tec5-sdctp
    [9694] = { 5714, 0 }, // client-wakeup
    [9695] = { 5715, 0 }, // ccnx
    [9700] = { 5716, 0 }, // board-roar
    [9747] = { 5717, 0 }, // l5nas-parchan
    [9750] = { 5718, 0 }, // board-voip
    [9753] = { 5719, 0 }, // rasadv
    [9762] = { 5720, 0 }, // tungsten-http
    [9800] = { 5721, 0 }, // davsrc
    [9801] = { 5722, 0 }, // sstp-2
    [9802] = { 5723, 0 }, // davsrcs
    [9875] = { 5724, 0 }, // sapv1
    [9876] = { 5725, 0 }, // sd
    [9877] = { 5726, 0 }, // x510
    [9878] = { 5727, 0 }, // kca-service
    [9888] = { 5728, 0 }, // cyborg-systems
    [9889] = { 5729, 0 }, // gt-proxy
    [9898] = { 5730, 0 }, // monkeycom
    [9899] = { 5731, 0 }, // sctp-tunneling
    [9900] = { 5732, 0 }, // iua
    [9901] = { 5733, 0 }, // enrp-sctp
    [9902] = { 5735, 0 }, // enrp-sctp-tls
    [9903] = { 5736, 0 }, // multicast-ping
    [9909] = { 5737, 0 }, // domaintime
    [9911] = { 5738, 0 }, // sype-transport
    [9925] = { 5739, 0 }, // xybrid-cloud
    [9929] = { 5740, 0 }, // nping-echo
    [9950] = { 5741, 0 }, // apc-9950
    [9951] = { 5742, 0 }, // apc-9951
    [9952] = { 5743, 0 }, // apc-9952
    [9953] = { 5744, 0 }, // acis
    [9954] = { 5745, 0 }, // hinp
    [9955] = { 5746, 0 }, // alljoyn-stm
    [9956] = { 5747, 0 }, // alljoyn
    [9966] = { 5748, 0 }, // odnsp
    [9978] = { 5749, 0 }, // xybrid-rt
    [9979] = { 5750, 0 }, // visweather
    [9981] = { 5751, 0 }, // pumpkindb
    [9987] = { 5752, 0 }, // dsm-scm-target
    [9988] = { 5753, 0 }, // nsesrvr
    [9990] = { 5754, 0 }, // osm-appsrvr
    [9991] = { 5755, 0 }, // issa
    [9992] = { 5757, 0 }, // issc
    [9993] = { 5759, 0 }, // palace-2
    [9994] = { 5760, 0 }, // palace-3
    [9995] = { 5761, 0 }, // palace-4
    [9996] = { 5762, 0 }, // palace-5
    [9997] = { 5763, 0 }, // palace-6
    [9998] = { 5764, 0 }, // distinct32
    [9999] = { 5765, 0 }, // abyss
    [10000] = { 5767, 0 }, // snet-sensor-mgmt
    [10001] = { 5769, 0 }, // scp-config
    [10002] = { 5770, 0 }, // documentum
    [10003] = { 5771, 0 }, // documentum_s
    [10004] = { 5772, 0 }, // emcrmirccd
    [10005] = { 5773, 0 }, // stel
    [10006] = { 5774, 0 }, // netapp-sync
    [10007] = { 5775, 0 }, // mvs-capacity
    [10008] = { 5776, 0 }, // octopus
    [10009] = { 5777, 0 }, // swdtp-sv
    [10010] = { 5778, 0 }, // rxapi
    [10020] = { 5779, 0 }, // abb-hw
    [10023] = { 5780, 0 }, // cefd-vmp
    [10050] = { 5781, 0 }, // zabbix-agent
    [10051] = { 5782, 0 }, // zabbix-trapper
    [10055] = { 5783, 0 }, // qptlmd
    [10080] = { 5784, 0 }, // amanda
    [10081] = { 5785, 0 }, // famdc
    [10082] = { 5786, 0 }, // amandaidx
    [10083] = { 5787, 0 }, // amidxtape
    [10100] = { 5788, 0 }, // itap-ddtp
    [10101] = { 5789, 0 }, // ezmeeting-2
    [10102] = { 5790, 0 }, // ezproxy-2
    [10103] = { 5791, 0 }, // ezrelay
    [10104] = { 5792, 0 }, // swdtp
    [10107] = { 5793, 0 }, // bctp-server
    [10110] = { 5794, 0 }, // nmea-0183
    [10111] = { 5795, 0 }, // nmea-onenet
    [10113] = { 5796, 0 }, // netiq-endpoint
    [10114] = { 5797, 0 }, // netiq-qcheck
    [10115] = { 5798, 0 }, // netiq-endpt
    [10116] = { 5799, 0 }, // netiq-voipa
    [10117] = { 5800, 0 }, // iqrm
    [10125] = { 5801, 0 }, // cimple
    [10128] = { 5802, 0 }, // bmc-perf-sd
    [10129] = { 5803, 0 }, // bmc-gms
    [10160] = { 5804, 0 }, // qb-db-server
    [10161] = { 5805, 0 }, // snmptls
    [10162] = { 5807, 0 }, // snmptls-trap
    [10200] = { 5809, 0 }, // trisoap
    [10201] = { 5810, 0 }, // rsms
    [10252] = { 5812, 0 }, // apollo-relay
    [10253] = { 5813, 0 }, // eapol-relay
    [10260] = { 5814, 0 }, // axis-wimp-port
    [10261] = { 5815, 0 }, // tile-ml
    [10288] = { 5816, 0 }, // blocks
    [10321] = { 5817, 0 }, // cosir
    [10439] = { 5818, 0 }, // bngsync
    [10443] = { 5819, 0 }, // cirrossp
    [10500] = { 5820, 0 }, // hip-nat-t
    [10540] = { 5821, 0 }, // MOS-lower
    [10541] = { 5822, 0 }, // MOS-upper
    [10542] = { 5823, 0 }, // MOS-aux
    [10543] = { 5824, 0 }, // MOS-soap
    [10544] = { 5825, 0 }, // MOS-soap-opt
    [10548] = { 5826, 0 }, // serverdocs
    [10631] = { 5827, 0 }, // printopia
    [10800] = { 5828, 0 }, // gap
    [10805] = { 5829, 0 }, // lpdg
    [10809] = { 5830, 0 }, // nbd
    [10810] = { 5831, 0 }, // nmc-disc
    [10860] = { 5832, 0 }, // helix
    [10880] = { 5833, 0 }, // bveapi
    [10933] = { 5834, 0 }, // octopustentacle
    [10990] = { 5835, 0 }, // rmiaux
    [11000] = { 5836, 0 }, // irisa
    [11001] = { 5837, 0 }, // metasys
    [11095] = { 5838, 0 }, // weave
    [11103] = { 5839, 0 }, // origo-sync
    [11104] = { 5840, 0 }, // netapp-icmgmt
    [11105] = { 5841, 0 }, // netapp-icdata
    [11106] = { 5842, 0 }, // sgi-lk
    [11108] = { 5843, 0 }, // myq-termlink
    [11109] = { 5844, 0 }, // sgi-dmfmgr
    [11110] = { 5845, 0 }, // sgi-soap
    [11111] = { 5846, 0 }, // vce
    [11112] = { 5847, 0 }, // dicom
    [11161] = { 5848, 0 }, // suncacao-snmp
    [11162] = { 5849, 0 }, // suncacao-jmxmp
    [11163] = { 5850, 0 }, // suncacao-rmi
    [11164] = { 5851, 0 }, // suncacao-csa
    [11165] = { 5852, 0 }, // suncacao-websvc
    [11171] = { 5853, 0 }, // snss
    [11172] = { 5854, 0 }, // oemcacao-jmxmp
    [11173] = { 5855, 0 }, // t5-straton
    [11174] = { 5856, 0 }, // oemcacao-rmi
    [11175] = { 5857, 0 }, // oemcacao-websvc
    [11201] = { 5858, 0 }, // smsqp
    [11202] = { 5859, 0 }, // dcsl-backup
    [11208] = { 5860, 0 }, // wifree
    [11211] = { 5861, 0 }, // memcache
    [11235] = { 5862, 0 }, // xcompute
    [11319] = { 5863, 0 }, // imip
    [11320] = { 5864, 0 }, // imip-channels
    [11321] = { 5865, 0 }, // arena-server
    [11367] = { 5866, 0 }, // atm-uhas
    [11371] = { 5867, 0 }, // pksd
    [11430] = { 5869, 0 }, // lsdp
    [11489] = { 5870, 0 }, // asgcypresstcps
    [11600] = { 5871, 0 }, // tempest-port
    [11623] = { 5872, 0 }, // emc-xsw-dconfig
    [11720] = { 5873, 0 }, // h323callsigalt
    [11723] = { 5874, 0 }, // emc-xsw-dcache
    [11751] = { 5875, 0 }, // intrepid-ssl
    [11796] = { 5876, 0 }, // lanschool
    [11876] = { 5877, 0 }, // xoraya
    [11877] = { 5878, 0 }, // x2e-disc
    [11967] = { 5879, 0 }, // sysinfo-sp
    [11971] = { 5880, 0 }, // tibsd
    [11997] = { 5881, 0 }, // wmereceiving
    [11998] = { 5882, 0 }, // wmedistribution
    [11999] = { 5883, 0 }, // wmereporting
    [12000] = { 5884, 0 }, // cce4x
    [12001] = { 5886, 0 }, // entextnetwk
    [12002] = { 5887, 0 }, // entexthigh
    [12003] = { 5888, 0 }, // entextmed
    [12004] = { 5889, 0 }, // entextlow
    [12005] = { 5890, 0 }, // dbisamserver1
    [12006] = { 5891, 0 }, // dbisamserver2
    [12007] = { 5892, 0 }, // accuracer
    [12008] = { 5893, 0 }, // accuracer-dbms
    [12009] = { 5894, 0 }, // ghvpn
    [12010] = { 5895, 0 }, // edbsrvr
    [12012] = { 5896, 0 }, // vipera
    [12013] = { 5897, 0 }, // vipera-ssl
    [12109] = { 5898, 0 }, // rets-ssl
    [12121] = { 5899, 0 }, // nupaper-ss
    [12168] = { 5900, 0 }, // cawas
    [12172] = { 5901, 0 }, // hivep
    [12300] = { 5902, 0 }, // linogridengine
    [12302] = { 5903, 0 }, // rads
    [12321] = { 5904, 0 }, // warehouse-sss
    [12322] = { 5905, 0 }, // warehouse
    [12345] = { 5906, 0 }, // netbus
    [12346] = { 5906, 0 }, // netbus
    [12753] = { 5908, 0 }, // tsaf
    [12865] = { 5909, 0 }, // netperf
    [13160] = { 5910, 0 }, // i-zipqd
    [13216] = { 5911, 0 }, // bcslogc
    [13217] = { 5912, 0 }, // rs-pias
    [13218] = { 5913, 0 }, // emc-vcas-tcp
    [13223] = { 5915, 0 }, // powwow-client
    [13224] = { 5916, 0 }, // powwow-server
    [13400] = { 5917, 0 }, // doip-data
    [13701] = { 5918, 0 }, // netbackup
    [13702] = { 5918, 0 }, // netbackup
    [13705] = { 5918, 0 }, // netbackup
    [13706] = { 5918, 0 }, // netbackup
    [13708] = { 5918, 0 }, // netbackup
    [13709] = { 5918, 0 }, // netbackup
    [13710] = { 5918, 0 }, // netbackup
    [13711] = { 5918, 0 }, // netbackup
    [13712] = { 5918, 0 }, // netbackup
    [13713] = { 5918, 0 }, // netbackup
    [13714] = { 5918, 0 }, // netbackup
    [13715] = { 5918, 0 }, // netbackup
    [13716] = { 5918, 0 }, // netbackup
    [13717] = { 5918, 0 }, // netbackup
    [13718] = { 5918, 0 }, // netbackup
    [13720] = { 5918, 0 }, // netbackup
    [13721] = { 5918, 0 }, // netbackup
    [13722] = { 5918, 0 }, // netbackup
    [13724] = { 5922, 0 }, // vnetd
    [13782] = { 5918, 0 }, // netbackup
    [13783] = { 5918, 0 }, // netbackup
    [13785] = { 5925, 0 }, // nbdb
    [13786] = { 5926, 0 }, // nomdb
    [13818] = { 5927, 0 }, // dsmcc-config
    [13819] = { 5928, 0 }, // dsmcc-session
    [13820] = { 5929, 0 }, // dsmcc-passthru
    [13821] = { 5930, 0 }, // dsmcc-download
    [13822] = { 5931, 0 }, // dsmcc-ccp
    [13823] = { 5932, 0 }, // bmdss
    [13894] = { 5933, 0 }, // ucontrol
    [13929] = { 5934, 0 }, // dta-systems
    [13930] = { 5935, 0 }, // medevolve
    [14000] = { 5936, 0 }, // scotty-ft
    [14001] = { 5937, 0 }, // sua
    [14002] = { 5938, 0 }, // scotty-disc
    [14033] = { 5939, 0 }, // sage-best-com1
    [14034] = { 5940, 0 }, // sage-best-com2
    [14141] = { 5941, 0 }, // bo2k
    [14142] = { 5943, 0 }, // icpp
    [14143] = { 5944, 0 }, // icpps
    [14145] = { 5945, 0 }, // gcm-app
    [14149] = { 5946, 0 }, // vrts-tdd
    [14150] = { 5947, 0 }, // vcscmd
    [14154] = { 5948, 0 }, // vad
    [14250] = { 5949, 0 }, // cps
    [14414] = { 5950, 0 }, // ca-web-update
    [14500] = { 5951, 0 }, // xpra
    [14936] = { 5952, 0 }, // hde-lcesrvr-1
    [14937] = { 5953, 0 }, // hde-lcesrvr-2
    [15000] = { 5954, 0 }, // hydap
    [15002] = { 5955, 0 }, // onep-tls
    [15118] = { 5956, 0 }, // v2g-secc
    [15126] = { 5957, 0 }, // swgps
    [15151] = { 5941, 0 }, // bo2k
    [15345] = { 5958, 0 }, // xpilot
    [15363] = { 5959, 0 }, // 3link
    [15555] = { 5960, 0 }, // cisco-snat
    [15660] = { 5961, 0 }, // bex-xr
    [15740] = { 5962, 0 }, // ptp
    [15998] = { 5963, 0 }, // 2ping
    [15999] = { 5964, 0 }, // programmar
    [16000] = { 5965, 0 }, // fmsas
    [16001] = { 5966, 0 }, // fmsascon
    [16002] = { 5967, 0 }, // gsms
    [16003] = { 5968, 0 }, // alfin
    [16020] = { 5969, 0 }, // jwpc
    [16021] = { 5970, 0 }, // jwpc-bin
    [16080] = { 5971, 0 }, // osxwebadmin
    [16161] = { 5972, 0 }, // sun-sea-port
    [16162] = { 5973, 0 }, // solaris-audit
    [16309] = { 5974, 0 }, // etb4j
    [16310] = { 5975, 0 }, // pduncs
    [16311] = { 5976, 0 }, // pdefmns
    [16360] = { 5977, 0 }, // netserialext1
    [16361] = { 5978, 0 }, // netserialext2
    [16367] = { 5979, 0 }, // netserialext3
    [16368] = { 5980, 0 }, // netserialext4
    [16384] = { 5981, 0 }, // connected
    [16385] = { 5982, 0 }, // rdgs
    [16444] = { 5983, 0 }, // overnet
    [16619] = { 5984, 0 }, // xoms
    [16665] = { 5985, 0 }, // axon-tunnel
    [16666] = { 5986, 0 }, // vtp
    [16789] = { 5987, 0 }, // cadsisvr
    [16900] = { 5988, 0 }, // newbay-snc-mc
    [16950] = { 5989, 0 }, // sgcip
    [16959] = { 5990, 0 }, // subseven
    [16991] = { 5991, 0 }, // intel-rci-mp
    [16992] = { 5992, 0 }, // amt-soap-http
    [16993] = { 5993, 0 }, // amt-soap-https
    [16994] = { 5994, 0 }, // amt-redir-tcp
    [16995] = { 5995, 0 }, // amt-redir-tls
    [17007] = { 5996, 0 }, // isode-dua
    [17010] = { 5997, 0 }, // ncpu
    [17184] = { 5998, 0 }, // vestasdlp
    [17185] = { 5999, 0 }, // soundsvirtual
    [17219] = { 6001, 0 }, // chipper
    [17220] = { 6002, 0 }, // avtp
    [17221] = { 6003, 0 }, // avdecc
    [17222] = { 6004, 0 }, // cpsp
    [17223] = { 6005, 0 }, // isa100-gci
    [17224] = { 6006, 0 }, // trdp-pd
    [17225] = { 6007, 0 }, // trdp-md
    [17234] = { 6008, 0 }, // integrius-stp
    [17235] = { 6009, 0 }, // ssh-mgmt
    [17300] = { 6010, 0 }, // kuang2
    [17500] = { 6011, 0 }, // db-lsp
    [17555] = { 6013, 0 }, // ailith
    [17729] = { 6014, 0 }, // ea
    [17754] = { 6015, 0 }, // zep
    [17755] = { 6016, 0 }, // zigbee-ip
    [17756] = { 6017, 0 }, // zigbee-ips
    [17777] = { 6018, 0 }, // sw-orion
    [18000] = { 6019, 0 }, // biimenu
    [18104] = { 6020, 0 }, // radpdf
    [18136] = { 6021, 0 }, // racf
    [18181] = { 6022, 0 }, // opsec-cvp
    [18182] = { 6023, 0 }, // opsec-ufp
    [18183] = { 6024, 0 }, // opsec-sam
    [18184] = { 6025, 0 }, // opsec-lea
    [18185] = { 6026, 0 }, // opsec-omi
    [18186] = { 6027, 0 }, // ohsc
    [18187] = { 6028, 0 }, // opsec-ela
    [18241] = { 6029, 0 }, // checkpoint-rtm
    [18242] = { 6030, 0 }, // iclid
    [18243] = { 6031, 0 }, // clusterxl
    [18262] = { 6032, 0 }, // gv-pf
    [18333] = { 5453, 0 }, // bitcoin
    [18463] = { 6033, 0 }, // ac-cluster
    [18516] = { 6034, 0 }, // heythings
    [18634] = { 6035, 0 }, // rds-ib
    [18635] = { 6036, 0 }, // rds-ip
    [18668] = { 6037, 0 }, // vdmmesh
    [18769] = { 6038, 0 }, // ique
    [18881] = { 6039, 0 }, // infotos
    [18888] = { 6040, 0 }, // apc-necmp
    [19000] = { 6041, 0 }, // igrid
    [19007] = { 6042, 0 }, // scintilla
    [19020] = { 6043, 0 }, // j-link
    [19150] = { 6044, 0 }, // gkrellm
    [19191] = { 6045, 0 }, // opsec-uaa
    [19194] = { 6046, 0 }, // ua-secureagent
    [19220] = { 6047, 0 }, // cora
    [19283] = { 6048, 0 }, // keysrvr
    [19315] = { 6049, 0 }, // keyshadow
    [19333] = { 5662, 0 }, // litecoin
    [19398] = { 6050, 0 }, // mtrgtrans
    [19410] = { 6051, 0 }, // hp-sco
    [19411] = { 6052, 0 }, // hp-sca
    [19412] = { 6053, 0 }, // hp-sessmon
    [19539] = { 6054, 0 }, // fxuptp
    [19540] = { 6055, 0 }, // sxuptp
    [19541] = { 6056, 0 }, // jcp
    [19788] = { 6057, 0 }, // mle
    [19790] = { 6058, 0 }, // faircom-db
    [19998] = { 6059, 0 }, // iec-104-sec
    [19999] = { 6060, 0 }, // dnp-sec
    [20000] = { 6061, 0 }, // dnp
    [20001] = { 6062, 0 }, // microsan
    [20002] = { 6063, 0 }, // commtact-http
    [20003] = { 6064, 0 }, // commtact-https
    [20005] = { 6065, 0 }, // btx
    [20012] = { 6067, 0 }, // ss-idi-disc
    [20013] = { 6068, 0 }, // ss-idi
    [20014] = { 6069, 0 }, // opendeploy
    [20034] = { 6071, 0 }, // nburn_id
    [20046] = { 6072, 0 }, // tmophl7mts
    [20048] = { 6073, 0 }, // mountd
    [20049] = { 6074, 0 }, // nfsrdma
    [20057] = { 6075, 0 }, // avesterra
    [20167] = { 6076, 0 }, // tolfab
    [20202] = { 6077, 0 }, // ipdtp-port
    [20222] = { 6078, 0 }, // ipulse-ics
    [20480] = { 6079, 0 }, // emwavemsg
    [20670] = { 3253, 0 }, // track
    [20810] = { 6080, 0 }, // crtech-nlm
    [20999] = { 6081, 0 }, // athand-mmp
    [21000] = { 6082, 0 }, // irtrans
    [21010] = { 6083, 0 }, // notezilla-lan
    [21201] = { 6084, 0 }, // memcachedb
    [21212] = { 6085, 0 }, // trinket-agent
    [21213] = { 6086, 0 }, // cohesity-agent
    [21221] = { 6087, 0 }, // aigairserver
    [21553] = { 6088, 0 }, // rdm-tfs
    [21554] = { 6089, 0 }, // dfserver
    [21590] = { 6090, 0 }, // vofr-gateway
    [21800] = { 6091, 0 }, // tvpm
    [21801] = { 6092, 0 }, // sal
    [21845] = { 6093, 0 }, // webphone
    [21846] = { 6094, 0 }, // netspeak-is
    [21847] = { 6095, 0 }, // netspeak-cs
    [21848] = { 6096, 0 }, // netspeak-acd
    [21849] = { 6097, 0 }, // netspeak-cps
    [22000] = { 6098, 0 }, // snapenetio
    [22001] = { 6099, 0 }, // optocontrol
    [22002] = { 6100, 0 }, // optohost002
    [22003] = { 6101, 0 }, // optohost003
    [22004] = { 6102, 0 }, // optohost004
    [22005] = { 6102, 0 }, // optohost004
    [22125] = { 6103, 0 }, // dcap
    [22128] = { 6104, 0 }, // gsidcap
    [22222] = { 6105, 0 }, // easyengine
    [22273] = { 6106, 0 }, // wnn6
    [22289] = { 6107, 0 }, // wnn6_Cn
    [22305] = { 6108, 0 }, // wnn6_Kr
    [22321] = { 6110, 0 }, // wnn6_Tw
    [22333] = { 6111, 0 }, // showcockpit-net
    [22335] = { 6112, 0 }, // shrewd-control
    [22343] = { 6113, 0 }, // cis-secure
    [22347] = { 6114, 0 }, // WibuKey
    [22350] = { 6115, 0 }, // CodeMeter
    [22351] = { 6116, 0 }, // codemeter-cmwan
    [22370] = { 6117, 0 }, // hpnpd
    [22537] = { 6118, 0 }, // caldsoft-backup
    [22555] = { 6119, 0 }, // vocaltec-wconf
    [22763] = { 6121, 0 }, // talikaserver
    [22800] = { 6122, 0 }, // aws-brf
    [22951] = { 6123, 0 }, // brf-gw
    [23000] = { 6124, 0 }, // inovaport1
    [23001] = { 6125, 0 }, // inovaport2
    [23002] = { 6126, 0 }, // inovaport3
    [23003] = { 6127, 0 }, // inovaport4
    [23004] = { 6128, 0 }, // inovaport5
    [23005] = { 6129, 0 }, // inovaport6
    [23053] = { 6130, 0 }, // gntp
    [23272] = { 6131, 0 }, // s102
    [23294] = { 6132, 0 }, // 5afe-dir
    [23333] = { 6133, 0 }, // elxmgmt
    [23400] = { 6134, 0 }, // novar-dbase
    [23401] = { 6135, 0 }, // novar-alarm
    [23402] = { 6136, 0 }, // novar-global
    [23456] = { 6137, 0 }, // aequus
    [23457] = { 6138, 0 }, // aequus-alt
    [23546] = { 6139, 0 }, // areaguard-neo
    [24000] = { 6140, 0 }, // med-ltp
    [24001] = { 6141, 0 }, // med-fsp-rx
    [24002] = { 6142, 0 }, // med-fsp-tx
    [24003] = { 6143, 0 }, // med-supp
    [24004] = { 6144, 0 }, // med-ovw
    [24005] = { 6145, 0 }, // med-ci
    [24006] = { 6146, 0 }, // med-net-svc
    [24242] = { 6147, 0 }, // filesphere
    [24249] = { 6148, 0 }, // vista-4gl
    [24321] = { 6149, 0 }, // ild
    [24322] = { 6150, 0 }, // hid
    [24323] = { 6151, 0 }, // vrmg-ip
    [24386] = { 6152, 0 }, // intel_rci
    [24465] = { 6153, 0 }, // tonidods
    [24554] = { 6154, 0 }, // binkp
    [24577] = { 6155, 0 }, // bilobit
    [24666] = { 6156, 0 }, // sdtvwcam
    [24676] = { 6157, 0 }, // canditv
    [24677] = { 6158, 0 }, // flashfiler
    [24678] = { 6159, 0 }, // proactivate
    [24680] = { 6160, 0 }, // tcc-http
    [24754] = { 6161, 0 }, // cslg
    [24850] = { 6162, 0 }, // assoc-disc
    [24922] = { 6163, 0 }, // find
    [25000] = { 6164, 0 }, // icl-twobase1
    [25001] = { 6165, 0 }, // icl-twobase2
    [25002] = { 6166, 0 }, // icl-twobase3
    [25003] = { 6167, 0 }, // icl-twobase4
    [25004] = { 6168, 0 }, // icl-twobase5
    [25005] = { 6169, 0 }, // icl-twobase6
    [25006] = { 6170, 0 }, // icl-twobase7
    [25007] = { 6171, 0 }, // icl-twobase8
    [25008] = { 6172, 0 }, // icl-twobase9
    [25009] = { 6173, 0 }, // icl-twobase10
    [25471] = { 6174, 0 }, // rna
    [25565] = { 6175, 0 }, // minecraft
    [25576] = { 6176, 0 }, // sauterdongle
    [25604] = { 6177, 0 }, // idtp
    [25793] = { 6178, 0 }, // vocaltec-hos
    [25900] = { 6179, 0 }, // tasp-net
    [25901] = { 6180, 0 }, // niobserver
    [25902] = { 6181, 0 }, // nilinkanalyst
    [25903] = { 6182, 0 }, // niprobe
    [25954] = { 6183, 0 }, // bf-game
    [25955] = { 6184, 0 }, // bf-master
    [26000] = { 6185, 0 }, // quake
    [26133] = { 6186, 0 }, // scscp
    [26208] = { 6187, 0 }, // wnn6_DS
    [26257] = { 6189, 0 }, // cockroach
    [26260] = { 6190, 0 }, // ezproxy
    [26261] = { 6191, 0 }, // ezmeeting
    [26262] = { 6192, 0 }, // k3software-svr
    [26263] = { 6193, 0 }, // k3software-cli
    [26486] = { 6194, 0 }, // exoline-tcp
    [26487] = { 6196, 0 }, // exoconfig
    [26489] = { 6197, 0 }, // exonet
    [26900] = { 6198, 0 }, // hexen2
    [27000] = { 6199, 0 }, // flexlm0
    [27001] = { 6201, 0 }, // flexlm1
    [27002] = { 6202, 0 }, // flexlm2
    [27003] = { 6203, 0 }, // flexlm3
    [27004] = { 6204, 0 }, // flexlm4
    [27005] = { 6205, 0 }, // flexlm5
    [27006] = { 6206, 0 }, // flexlm6
    [27007] = { 6207, 0 }, // flexlm7
    [27008] = { 6208, 0 }, // flexlm8
    [27009] = { 6209, 0 }, // flexlm9
    [27010] = { 6210, 0 }, // flexlm10
    [27017] = { 6212, 0 }, // mongod
    [27018] = { 6212, 0 }, // mongod
    [27019] = { 6212, 0 }, // mongod
    [27345] = { 6213, 0 }, // imagepump
    [27350] = { 6214, 0 }, // mdcs-scheduler
    [27374] = { 5990, 0 }, // subseven
    [27442] = { 6215, 0 }, // jesmsjc
    [27444] = { 6216, 0 }, // Trinoo_Bcast
    [27500] = { 6217, 0 }, // quakeworld
    [27504] = { 6218, 0 }, // kopek-httphead
    [27665] = { 6219, 0 }, // Trinoo_Master
    [27782] = { 6220, 0 }, // ars-vista
    [27876] = { 6221, 0 }, // astrolink
    [27910] = { 6222, 0 }, // quake2
    [27960] = { 6223, 0 }, // quake3
    [27999] = { 6224, 0 }, // tw-auth-key
    [28000] = { 6225, 0 }, // nxlmd
    [28001] = { 6226, 0 }, // pqsp
    [28010] = { 6227, 0 }, // gruber-cashreg
    [28015] = { 6228, 0 }, // rethinkdb
    [28017] = { 6212, 0 }, // mongod
    [28080] = { 6229, 0 }, // thor-engine
    [28119] = { 6230, 0 }, // a27-ran-ran
    [28200] = { 6231, 0 }, // voxelstorm
    [28240] = { 6232, 0 }, // siemensgsm
    [28589] = { 6233, 0 }, // bosswave
    [28910] = { 6234, 0 }, // heretic2
    [29000] = { 6235, 0 }, // saltd-licensing
    [29015] = { 6228, 0 }, // rethinkdb
    [29118] = { 6236, 0 }, // sgsap
    [29167] = { 6237, 0 }, // otmp
    [29168] = { 6238, 0 }, // sbcap
    [29169] = { 6239, 0 }, // iuhsctpassoc
    [29999] = { 6240, 0 }, // bingbang
    [30000] = { 6241, 0 }, // ndmps
    [30001] = { 6242, 0 }, // pago-services1
    [30002] = { 6243, 0 }, // pago-services2
    [30003] = { 6244, 0 }, // amicon-fpsu-ra
    [30004] = { 6245, 0 }, // amicon-fpsu-s
    [30100] = { 6246, 0 }, // rwp
    [30260] = { 6247, 0 }, // kingdomsonline
    [30400] = { 6248, 0 }, // gs-realtime
    [30832] = { 6249, 0 }, // samsung-disc
    [30999] = { 6250, 0 }, // ovobs
    [31016] = { 6251, 0 }, // ka-sddp
    [31020] = { 6252, 0 }, // autotrac-acp
    [31029] = { 6253, 0 }, // yawn
    [31335] = { 6254, 0 }, // Trinoo_Register
    [31337] = { 6255, 0 }, // Elite
    [31400] = { 6257, 0 }, // pace-licensed
    [31416] = { 786, 0 }, // boinc
    [31457] = { 6259, 0 }, // tetrinet
    [31620] = { 6260, 0 }, // lm-mon
    [31685] = { 6261, 0 }, // dsx_monitor
    [31727] = { 6262, 0 }, // diagd
    [31765] = { 6263, 0 }, // gamesmith-port
    [31948] = { 6264, 0 }, // iceedcp_tx
    [31949] = { 6265, 0 }, // iceedcp_rx
    [32034] = { 6266, 0 }, // iracinghelper
    [32249] = { 6267, 0 }, // t1distproc60
    [32400] = { 6268, 0 }, // plex
    [32483] = { 6269, 0 }, // apm-link
    [32635] = { 6270, 0 }, // sec-ntb-clnt
    [32636] = { 6271, 0 }, // DMExpress
    [32767] = { 6272, 0 }, // filenet-powsrm
    [32768] = { 6273, 0 }, // filenet-tms
    [32769] = { 6275, 0 }, // filenet-rpc
    [32770] = { 6276, 0 }, // sometimes-rpc3
    [32771] = { 6278, 0 }, // sometimes-rpc5
    [32772] = { 6280, 0 }, // sometimes-rpc7
    [32773] = { 6282, 0 }, // sometimes-rpc9
    [32774] = { 6284, 0 }, // sometimes-rpc11
    [32775] = { 6286, 0 }, // sometimes-rpc13
    [32776] = { 6288, 0 }, // sometimes-rpc15
    [32777] = { 6290, 0 }, // sometimes-rpc17
    [32778] = { 6292, 0 }, // sometimes-rpc19
    [32779] = { 6294, 0 }, // sometimes-rpc21
    [32780] = { 6296, 0 }, // sometimes-rpc23
    [32786] = { 6298, 0 }, // sometimes-rpc25
    [32787] = { 6300, 0 }, // sometimes-rpc27
    [32801] = { 6302, 0 }, // mlsn
    [32811] = { 6303, 0 }, // retp
    [32896] = { 6304, 0 }, // idmgratm
    [33000] = { 6305, 0 }, // wg-endpt-comms
    [33060] = { 6306, 0 }, // mysqlx
    [33123] = { 6307, 0 }, // aurora-balaena
    [33331] = { 6308, 0 }, // diamondport
    [33333] = { 6309, 0 }, // dgi-serv
    [33334] = { 6310, 0 }, // speedtrace
    [33434] = { 6311, 0 }, // traceroute
    [33435] = { 6312, 0 }, // mtrace
    [33656] = { 6313, 0 }, // snip
    [33890] = { 6314, 0 }, // digilent-adept
    [34249] = { 6315, 0 }, // turbonote-2
    [34378] = { 6316, 0 }, // p-net-local
    [34379] = { 6317, 0 }, // p-net-remote
    [34567] = { 6318, 0 }, // dhanalakshmi
    [34962] = { 6319, 0 }, // profinet-rt
    [34963] = { 6320, 0 }, // profinet-rtm
    [34964] = { 6321, 0 }, // profinet-cm
    [34980] = { 6322, 0 }, // ethercat
    [35000] = { 6323, 0 }, // heathview
    [35001] = { 6324, 0 }, // rt-viewer
    [35002] = { 6325, 0 }, // rt-sound
    [35003] = { 6326, 0 }, // rt-devicemapper
    [35004] = { 6327, 0 }, // rt-classmanager
    [35005] = { 6328, 0 }, // rt-labtracker
    [35006] = { 6329, 0 }, // rt-helper
    [35100] = { 6330, 0 }, // axio-disc
    [35354] = { 6331, 0 }, // kitim
    [35355] = { 6332, 0 }, // altova-lm
    [35356] = { 6333, 0 }, // guttersnex
    [35357] = { 6334, 0 }, // openstack-id
    [36001] = { 6335, 0 }, // allpeers
    [36411] = { 6336, 0 }, // wlcp
    [36412] = { 6337, 0 }, // s1-control
    [36422] = { 6338, 0 }, // x2-control
    [36423] = { 6339, 0 }, // slmap
    [36424] = { 6340, 0 }, // nq-ap
    [36443] = { 6341, 0 }, // m2ap
    [36444] = { 6342, 0 }, // m3ap
    [36462] = { 6343, 0 }, // xw-control
    [36524] = { 6344, 0 }, // febooti-aw
    [36602] = { 6345, 0 }, // observium-agent
    [36700] = { 6346, 0 }, // mapx
    [36865] = { 6347, 0 }, // kastenxpipe
    [37472] = { 6348, 0 }, // 3gpp-w1ap
    [37475] = { 6349, 0 }, // neckar
    [37483] = { 6350, 0 }, // gdrive-sync
    [37601] = { 6351, 0 }, // eftp
    [37654] = { 6352, 0 }, // unisys-eportal
    [38000] = { 6353, 0 }, // ivs-database
    [38001] = { 6354, 0 }, // ivs-insertion
    [38002] = { 6355, 0 }, // cresco-control
    [38037] = { 6356, 0 }, // landesk-cba
    [38201] = { 6357, 0 }, // galaxy7-data
    [38202] = { 6358, 0 }, // fairview
    [38203] = { 6359, 0 }, // agpolicy
    [38292] = { 6356, 0 }, // landesk-cba
    [38293] = { 6356, 0 }, // landesk-cba
    [38412] = { 6360, 0 }, // ng-control
    [38422] = { 6361, 0 }, // xn-control
    [38462] = { 6362, 0 }, // e1-interface
    [38472] = { 6363, 0 }, // f1-control
    [38638] = { 6364, 0 }, // psqlmws
    [38800] = { 6365, 0 }, // sruth
    [38865] = { 6366, 0 }, // secrmmsafecopya
    [39063] = { 6367, 0 }, // vroa
    [39213] = { 6368, 0 }, // sygatefw
    [39681] = { 6369, 0 }, // turbonote-1
    [40000] = { 6370, 0 }, // safetynetp
    [40023] = { 6371, 0 }, // k-patentssensor
    [40404] = { 6372, 0 }, // sptx
    [40841] = { 6373, 0 }, // cscp
    [40842] = { 6374, 0 }, // csccredir
    [40843] = { 6375, 0 }, // csccfirewall
    [40853] = { 6376, 0 }, // ortec-disc
    [41111] = { 6377, 0 }, // fs-qos
    [41121] = { 6378, 0 }, // tentacle
    [41230] = { 6379, 0 }, // z-wave-s
    [41794] = { 6380, 0 }, // crestron-cip
    [41795] = { 6381, 0 }, // crestron-ctp
    [41796] = { 6382, 0 }, // crestron-cips
    [41797] = { 6383, 0 }, // crestron-ctps
    [42508] = { 6384, 0 }, // candp
    [42509] = { 6385, 0 }, // candrp
    [42510] = { 6386, 0 }, // caerpc
    [43000] = { 6387, 0 }, // recvr-rc
    [43188] = { 6388, 0 }, // reachout
    [43189] = { 6389, 0 }, // ndm-agent-port
    [43190] = { 6390, 0 }, // ip-provision
    [43191] = { 6391, 0 }, // noit-transport
    [43210] = { 6392, 0 }, // shaperai
    [43438] = { 6393, 0 }, // hmip-routing
    [43439] = { 6394, 0 }, // eq3-update
    [43440] = { 6395, 0 }, // ew-mgmt
    [43441] = { 6397, 0 }, // ciscocsdb
    [44123] = { 6398, 0 }, // z-wave-tunnel
    [44321] = { 6399, 0 }, // pmcd
    [44322] = { 6400, 0 }, // pmcdproxy
    [44323] = { 6401, 0 }, // pmwebapi
    [44334] = { 6402, 0 }, // tinyfw
    [44442] = { 6403, 0 }, // coldfusion-auth
    [44443] = { 6403, 0 }, // coldfusion-auth
    [44444] = { 6404, 0 }, // cognex-dataman
    [44445] = { 6405, 0 }, // acronis-backup
    [44544] = { 6406, 0 }, // domiq
    [44553] = { 6407, 0 }, // rbr-debug
    [44600] = { 6408, 0 }, // asihpi
    [44818] = { 6409, 0 }, // EtherNetIP-2
    [44900] = { 6410, 0 }, // m3da
    [45000] = { 6411, 0 }, // asmp
    [45001] = { 6413, 0 }, // asmps
    [45002] = { 6414, 0 }, // rs-status
    [45045] = { 6415, 0 }, // synctest
    [45054] = { 6416, 0 }, // invision-ag
    [45514] = { 6417, 0 }, // cloudcheck
    [45678] = { 6418, 0 }, // eba
    [45824] = { 6419, 0 }, // dai-shell
    [45825] = { 6420, 0 }, // qdb2service
    [45966] = { 6421, 0 }, // ssr-servermgr
    [46336] = { 6422, 0 }, // inedo
    [46998] = { 6423, 0 }, // spremotetablet
    [46999] = { 6424, 0 }, // mediabox
    [47000] = { 6425, 0 }, // mbus
    [47001] = { 6426, 0 }, // winrm
    [47100] = { 6427, 0 }, // jvl-mactalk
    [47557] = { 6428, 0 }, // dbbrowse
    [47624] = { 6429, 0 }, // directplaysrvr
    [47806] = { 6430, 0 }, // ap
    [47808] = { 6431, 0 }, // bacnet
    [47809] = { 6432, 0 }, // presonus-ucnet
    [48000] = { 6433, 0 }, // nimcontroller
    [48001] = { 6434, 0 }, // nimspooler
    [48002] = { 6435, 0 }, // nimhub
    [48003] = { 6436, 0 }, // nimgtw
    [48004] = { 6437, 0 }, // nimbusdb
    [48005] = { 6438, 0 }, // nimbusdbctrl
    [48048] = { 6439, 0 }, // juka
    [48049] = { 6440, 0 }, // 3gpp-cbsp
    [48050] = { 6441, 0 }, // weandsf
    [48128] = { 6442, 0 }, // isnetserv
    [48129] = { 6443, 0 }, // blp5
    [48556] = { 6444, 0 }, // com-bardac-dw
    [48619] = { 6445, 0 }, // iqobject
    [48653] = { 6446, 0 }, // robotraconteur
    [48899] = { 6447, 0 }, // tc_ads_discovery
    [49000] = { 6448, 0 }, // matahari
    [49001] = { 6449, 0 }, // nusrp
    [49150] = { 6450, 0 }, // inspider
    [49400] = { 2087, 0 }, // compaqdiag
    [50000] = { 455, 0 }, // ibm-db2
    [50002] = { 6451, 0 }, // iiimsf
    [54320] = { 5941, 0 }, // bo2k
    [61439] = { 6452, 0 }, // netprowler-manager
    [61440] = { 6453, 0 }, // netprowler-manager2
    [61441] = { 6454, 0 }, // netprowler-sensor
    [62078] = { 6455, 0 }, // iphone-sync
    [64738] = { 6456, 0 }, // murmur
    [65301] = { 6457, 0 }, // pcanywhere
};


#endif // PORT_MAP_H