/** @file  myarphdr.h
 *  @brief  my own header for ARP
 * 
 *  @details   Address Resolution Protocol related structre and function

 *  @author Karthik M 
 *  @bug  Need to Document
 */


#ifndef __MYARPHDR_H
#define __MYARPHDR_H

#define  HW_LEN 6


/**  @brief structure of ARP heder 
  *
  *  @details The Header frame structure of Address Resolution Protocol  header.
  *  \struct myarphdr myarp.h
  */
struct myarphdr
{
   uint16_t arp_hdr;       /** @param arp_hdr  format of hardware address */
   uint16_t arp_pro;       /** @param arp_pro  format of protocol address */
   uint8_t arp_hln;        /** @param arp_hln  length of hardware address */
   uint8_t arp_pln;        /** @param arp_pln  length of protocol address */
   uint16_t arp_op;        /** @param arp_op   ARP opcode (command )   */
};

typedef  struct myarphdr ARPHDR;

/**  @brief ARP Data   
  *  
  *  @details  To  Read the ARP soruce and destination address 
  *  \struct arpdata  myarphdr.h
  */
struct  arpdata 
{
  uint8_t ar_sha[HW_LEN] ;   /** @param ar_sha  source hardware address */
  uint8_t ar_spa[4];         /** @param ar_spa  source protocol address */ 
  uint8_t ar_tha[HW_LEN];    /** @param ar_tha  destination hardware address */
  uint8_t ar_tpa[4] ;        /** @param ar_tpa  destination protocol address */
};
typedef struct arpdata ARPDATA ;


#endif 

