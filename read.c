/** @file read.c 
 *  @brief  To Know some Basic abou the WireShark functionality.
 * 
 *  @details Like Wireshark we are going to display  The Ip Packet Contents Using
 *    Our Own structures.
 *   
 *  @author Karthik M 
 *  @bug No  bugs.
 */

#if 0

# include <errno.h>
#include <linux/ip.h>
#endif

# include "header.h"
# include "myipv4hdr.h"
# include "myarphdr.h"

# define size 4096


void display_ipheader(unsigned char * buffer)
{

   const char * srcip =  NULL ;
   const char * dstip =  NULL ;
   char * buf = NULL;
   unsigned short  flags  =0;
   unsigned int  f_offset = 0;
   unsigned int temp_offset = 0;
   IP_HDR *ip;                 /** my Own IP header **/
   struct iphdr * ihdr ;          /**   predefinde header i.e /usr/include/linux/ip.h **/

   /** ALLOC:  allocate memory for the buffer **/
   if ((buf = (char *)malloc(size)) == NULL){
      perror ("memory is not allocated \n");
      exit (1);
   }
   ip  = (IP_HDR *)(buffer+ (sizeof(struct ethernet)));
   ihdr  = (struct iphdr*)(buffer+ (sizeof(struct ethhdr)));

   /** get the souurce and destinatin ip as a string to display **/
   srcip = inet_ntop(AF_INET, (&ip->saddr), buf, size);
   dstip = inet_ntop(AF_INET, (&ip->daddr), buf, size);

   /** Display the IP packet info **/

   printf (" Interner Protocol Version 4 : src = %s (%s) ,"
         "Dst = %s (%s)\n", srcip,srcip,dstip,dstip );
   printf ("version = %d\n", ip->version); 
   printf ("Header Length     = %2d  bytes\n", (ip->ihl) * 4 ); 
   printf ("Differentiated Services Field: 0x%02x \n", ip->tos);
   printf ("Total_Length = %d\n", ntohs(ip->tot_len));
   //		printf (" predefinde Total_Length = %d\n", ihdr->tot_len);
   printf ("Identification = 0x%04x (%d)\n", ntohs(ip->id_len),
         ntohs(ip->id_len)  );

   temp_offset = ntohs(ip->frg_off);
   printf ("\n\n 0x%04x \n", temp_offset);

   flags = ((temp_offset ) & ( ~(~0 << 3) <<12 ))>>13 ;
   f_offset = ((temp_offset ) & ~ ( ~(~0 << 3) <<12 )) ; 

   printf ("4 2 1 \n");
   printf ("%c . . ",(flags>>2 &1)? 49:46) ;
   printf("Reserved bit \n" );
   printf (". %c . ",(flags>>1 &1)? 49:46) ;
   printf ( "Don't Fragement bit \n" );
   printf (". . %c ",(flags &1)? 49:46) ;
   printf ( "More Fragement bit \n" );
   printf ("flags = 0x%04d \n", flags);
   printf ("frag_offset = 0x%04x \n", f_offset);
   //   printf ("for_off = 0x%04x\n", ip->frg_offset);
   printf ("Time To Live     = %d\n", ip->ttl);
   printf ("protocol= %u (%s)\n", ip->protocol, protoname[ip->protocol]);
   printf (" Header chesum  = 0x%04x\n", ntohs(ip->check));
   printf ("dst = %x \n", ntohs (ip->daddr));

   /** To compare with the  wireshark result **/
   printf (" wireshark: \n");
   printf ("------------\n");
   printf( "\t ip.src==%s\n",(inet_ntop(AF_INET, (&ip->saddr), 
               buf, size)));
   printf( "\t p.dst==%s\n",(inet_ntop(AF_INET, (&ip->daddr), 
               buf, size)));
}


void display_arp (char * buffer)
{
     ARPHDR  * arphr ;
     ARPDATA *data;
     int k = -1 ;

     arphr = (ARPHDR *) (buffer +sizeof (ETHHDR));

     printf (" Hardware type = %d \n",ntohs(arphr->arp_hdr));
     printf (" protocol type = 0x%04x \n",ntohs(arphr->arp_pro));
     printf (" hardware length = %d \n",arphr->arp_hln);
     printf (" protocol length = %d \n",arphr->arp_pln);
     printf (" opcode = %d \n",ntohs (arphr->arp_op) );
     
     data = (ARPDATA *) (buffer + sizeof(ETHHDR) + sizeof (ARPHDR));
     printf (" source HW address :\n");
     for (k = 0; k < HW_LEN; k++)
        printf ( "%02x:",data->ar_sha[k]);
      printf ("\n");
     printf ("src  protocol address :\n");
     for (k = 0; k < 4; k++)
         printf ( "%02x:",data->ar_spa[k]);
      printf ("\n");
     printf ("dst  HW address :\n");
     for (k = 0; k < HW_LEN; k++)
     printf ( "%02x:",data->ar_tha[k]);
     printf ("\n");
     printf (" dst protocol address :\n");
     for (k = 0; k < 4; k++)
         printf ( "%02x:",data->ar_tpa[k]);
      printf ("\n");

}



int main() 
{

   int s = -1, rx = -1, i = -1 ,j = -1;
   char *ptr = NULL ;
   char     *buffer = NULL ;
   struct sockaddr_in cli;
   struct in_addr  addr;
   FILE *fp;
   int x =-1;
   unsigned char * dump = NULL;
   char c = -1;
   ETHHDR *eth ;
   int eth_type = -1;
   int type_ip = 0x800 ;
   int type_arp = 0x806 ;

#if 0
   printf ("sizeof ethernet = %d \n", sizeof (ETHHDR)); 
   printf ("sizeof ip_header = %d \n",  sizeof (IP_HEADER)); 
   printf ("sizeof tcp_header = %d \n", sizeof (TCP_HEADER )); 
   printf ("sizeof udp_header = %d \n", sizeof (UDP_HEADER )); 
#endif

   if ((buffer = (char *) malloc (size)) == NULL) {
      perror ("memory is not allocated \n");
      exit (1);
   }

   if ((dump = (char *)malloc(size)) == NULL) {
      perror ("memory is not allocated \n");
      exit (1);
   }

   /** Create the RAW socket **/
   s = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
   if (s == -1) {
      perror ("socket is not created \n");
      exit (1);
   }

   printf ("socket is created \n");
   for (j=0; j< 10; j++) {
      rx = recvfrom (s, buffer, size, 0, NULL, NULL);
      printf (" the size of buffer is = %d \n", rx);
      if (rx == -1 ) {
         perror ("received is failed\n ");
         exit (1);
      }

      
      if ( type_arp == eth_type ){                                             
      
      /**  Buffer contents are dump it into file */
      fp = fopen ("/home/karthik/practice/buffer.txt","w");
      if (fp == NULL)
         perror (" open:");
      fwrite ( buffer ,rx,1,fp);
      fclose(fp);
      }


      eth = (ETHHDR *)buffer;
      printf ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
      printf ("EThernet II: \n");
      printf ("dest   =(" );
      for (i =0 ; i < 6; i++)
         printf ("%02x:", (eth->dst[i])); 
      printf(")\n");
      printf ("src =(" );
      for (i =0 ; i < 6; i++)
         printf ("%02x:", (eth->src[i])); 
      printf(")\n"); 

      eth_type = ntohs (eth->eth_type) ;
      printf ("type  : IP (0x%04x )\n",  eth_type ); 
      printf ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   
#if 0
      if ( type_ip == eth_type ){
      display_ipheader (buffer);
      }
                                 /* TODO:  Display the arp_header  */
#endif 
       if ( type_arp == eth_type ){
          printf (" in ARP \n");
      display_arp (buffer);
      }

   }

   /* TODO: Make buffer content display same as hexdump */ 
   /*
      dump = buffer ;
      printf (" dump: \n");
      printf ("---------------------------: \n");
      i = rx;
      for  (i = 0 ; i <=rx ; i++){
      if ( i%8 == 0)
      putchar(' ');
      if ( i%16 == 0)
      putchar('\n');
      c = dump[i];
   //  printf (" %02d",buffer[i]);
   printf (" %02x",dump[i]);
   }
   printf("\n");

    */



   return 0;
}
