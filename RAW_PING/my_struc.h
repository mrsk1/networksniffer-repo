#ifndef struc
#define struc

typedef struct ether_frame {
	unsigned char dest[6];
	unsigned char src[6];
	unsigned short int type;
} ETHER_FRAME;


typedef struct arp_frame {
	unsigned short int hw_type;
	unsigned short int p_type;
	unsigned char ha_len;
	unsigned char pa_len;
	unsigned short opcode;
	unsigned char src_mac[6];
	unsigned char src_ip[4];
	unsigned char dest_mac[6];
	unsigned char dest_ip[4];
}ARP_FRAME;

typedef struct reply_pkt {
	unsigned char dest[6];
	unsigned char src[6];
	unsigned short int type;
	unsigned short int hw_type;
	unsigned short int p_type;
	unsigned char ha_len;
	unsigned char pa_len;
	unsigned short opcode;
	unsigned char src_mac[6];
	unsigned char src_ip[4];
	unsigned char dest_mac[6];
	unsigned char dest_ip[4];
}REPLY_PKT;
#endif	
