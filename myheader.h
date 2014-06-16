# ifndef __MYHEADER__H
# define  __MYHEADER__H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <netinet/in.h>
# include <sys/un.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>

# include <netdb.h>
# include <unistd.h>


typedef struct ethrnet {
	unsigned char dest[6];
	unsigned char source[6];
	unsigned short int ethrent_type;
}ETHRENT;


typedef struct TCP_header {
	unsigned short int source_port_number;
	unsigned short int dest_port_number;
	unsigned int  sequence_number;
	unsigned  int ack_number;
	unsigned char header_length:4;
	unsigned char reserved:6;
	unsigned char URG:1;
	unsigned char PSH:1;
	unsigned char ACK:1;
	unsigned char RST:1;
	unsigned char SYN:1;
	unsigned char FTN:1;
	unsigned short int window_size;
	unsigned short int tcp_checksum;
	unsigned short int urgent_pointer;
	//unsigned  int options;
	//unsigned  int data;
}TCP_HEADER;
	
typedef struct UDP_header {
	unsigned short int source_port;
	unsigned short int dest_port;
	unsigned short int length;
	//unsigned short int checksum;
	//unsigned int  payload;
}UDP_HEADER;

# endif
