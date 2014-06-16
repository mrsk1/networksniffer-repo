/** @file  myipv4hdr.h
 *  @brief Defintion related to IPV4 
 * 
 *  Header Which contain all the necessary data related to IPV4
 *   
 *  @author Karthik M 
 *  @bug No  bugs.
 */


typedef struct ip_header {
	unsigned char IHL:4;  /*  it is a  octal representation */
	unsigned char ver:4;  /*  IHL Ver Vary According to  Little to Big Endian */

	unsigned char TOS;
	unsigned short int Total_length;
	unsigned short int ident_length;
	unsigned short int frg_offset;
	unsigned char TTL;
	unsigned char protocol;
	unsigned short int header_checksum;
	unsigned  int source_addr;
	unsigned  int dest_addr;
//	unsigned char options[40];
}IP_HEADER;
	


char *protoname[] = {
   "0" ,"ICMP", " IGMP", "GGP", "IP" ," ST", "TCP", "UCL", "EGP", "IGP",
       "BBN-RCC-MON", "NVP-II", "PUP", " ARGUS", "EMCON", "XNET", "CHAOS",
       "UDP", "MUX", "DCN-MEAS", "HMP", " PRM", "XNS-IDP", "TRUNK-1", 
       "TRUNK-2", "LEAF-1", "LEAF-2", "RDP", "IRTP", "ISO-TP4", "NETBLT", 
       "MFE-NSP", "MERIT-INP", "SEP", "3PC", "IDPR", "XTP", "DDP", "IDPR-CMTP",
       "TP++","IL","IPv6","SDRP", "IPv6-Route", "IPv6-Frag", "IDRP", "RSVP", 
       "GRE", "MHRP", "BNA", "IPv6-Crypt", "IPv6-Auth", "I-NLSP", "SWIPE", 
       "NARP", "MOBILE", "TLSP", "Unassigned", "IPv6-ICMP", "IPv6-NoNxt", 
       "IPv6-Opts", "61", "CFTP", "63", "SAT-EXPAK", "KRYPTOLAN", "RVD", 
       "IPPC", "68", "SAT-MON", "VISA", "IPCV", "CPNX", "CPHB", "WSN", "PVP", 
       "BR-SAT-MON", "SUN-ND", "WB-MON", "WB-EXPAK", "ISO-IP", "VMTP", 
       "SECURE-VMTP", "VINES", "TTP", "NSFNET-IGP", "DGP", "TCF", "IGRP",
       "OSPFIGP", "Sprite-RPC","LARP", "MTP", "AX.25", "IPIP", "MICP", 
       "SCC-SP", "ETHERIP", "ENCAP", "99", "GMTP"
};
