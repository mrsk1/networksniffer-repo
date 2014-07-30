
/** @file  myipv4hdr.h
 *  @brief Defintion related to IPV4 
 * 
 *  Header Which contain all the necessary data related to IPV4
 *   
 *  @author Karthik M 
 *  @bug  Documentation
 */
#ifndef  __MYIPV4_HEADER_H
#define  __MYIPV4_HEADER_H

/** @brief   ipv4 header
  * 
  * @details Creating my own ipv4 header structure 
  * \struct  ipv4_hdr myipv4header.h 
  */
 

/**TODO: Little Endian big endian
         Fri Jul 25 15:59:32 IST 2014
  */

typedef struct ipv4_hdr {
	uint8_t ihl:4;  /*  it is a  octal representation */
	uint8_t  version:4;  /*  IHL Ver Vary According to  Little to Big Endian */

	uint8_t tos;        /** @param tos  Type Of Service  */
	uint16_t tot_len ;  /** @param tot_len Total bytes of packet in network byte order */
	uint16_t id_len;    /** @param id_len  Identification number */
	uint16_t frg_off;   /** @param frg_off Fragment Offset */
	uint8_t ttl;        /** @param ttl  Time To Live */
	uint8_t  protocol;  /** @param protocol Protocol Number */
	uint16_t check;     /** @param check  Header Checksum */
	uint32_t saddr;     /** @param saddr Source Address */
	uint32_t daddr;     /** @param daddr Destination Address */
}IP_HDR;
	


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


enum proto_list 
{
     ICMP = 1, IGMP, GGP, IP, ST, TCP, UCL, EGP, IGP, BBN_RCC_MON, NVP_II, PUP,
     ARGUS, EMCON, XNET, CHAOS, UDP, MUX, DCN_MEAS, HMP, PRM, XNS_IDP,TRUNK_1,
     TRUNK_2, LEAF_1, LEAF_2, RDP, IRTP, ISO_TP4, NETBLT, MFE_NSP, MERIT_INP, 
     SEP, PC_3, IDPR, XTP, DDP, IDPR_CMTP, TP__, IL, IPv6, SDRP, IPv6_Route , 
     IPv6_Frag, IDRP, RSVP, GRE, MHRP, BNA, IPv6_Crypt, IPv6_Auth, I_NLSP, 
     SWIPE, NARP, MOBILE, TLSP, Unassigned, IPv6_ICMP, IPv6_NoNxt, IPv6_Opts, 
     CFTP = 62, SAT_EXPAK = 64, KRYPTOLAN, RVD, IPPC,  SAT_MON = 69, VISA, IPCV,
     CPNX, CPHB, WSN, PVP, BR_SAT_MON, SUN_ND,  WB_MON, WB_EXPAK, ISO_IP, VMTP,
     SECURE_VMTPi, VINES, TTP, NSFNET_IGP, DGP, TCF, IGRP, OSPFIGP, Sprite_RPC,
     LARP, MTP, AX_25, IPIP, MICP, SCC_SP, ETHERIP, ENCAP, GMTP = 100 
};

typedef enum proto_list PROTOLIST;

#endif
