
/** @file read.c 
 *  @brief  To Know some Basic abou the WireShark functionality.
 * 
 *   Like Wireshark we are going to display  The Ip Packet Contents Using
 *    Our Own structures.
 *   
 *  @author Karthik M 
 *  @bug No  bugs.
 */


# include <stdio.h>
# include <netdb.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <errno.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <netinet/in.h>
#include <linux/ip.h>
# include <linux/if_ether.h>

# include "myheader.h"
# include "myipv4hdr.h"

# define size 4096

void display_ipheader(char * buffer)
{

   IP_HEADER *ip;
   struct iphdr * ihdr ;
   const char * srcip =  NULL ;
   const char * dstip =  NULL ;
   char * buf = NULL;
   unsigned short  flags  =0;
   unsigned int  f_offset = 0;
   unsigned int temp_offset = 0;

if ((buf = (char *)malloc(size)) == NULL) {
      perror ("memory is not allocated \n");
      exit (1);
   }
   ip  = (IP_HEADER*)(buffer+ (sizeof(struct ethrnet)));
   ihdr  = (struct iphdr*)(buffer+ (sizeof(struct ethhdr)));

      //    addr = ((struct in_addr)(ip->dest_addr)); 
   srcip = inet_ntop(AF_INET, (&ip->source_addr), buf, size);
   dstip = inet_ntop(AF_INET, (&ip->dest_addr), buf, size);

   printf (" Interner Protocol Version 4 : src = %s (%s) ,"
         "Dst = %s (%s)\n", srcip,srcip,dstip,dstip );
   printf ("version = %d\n", ip->ver); 
   printf ("Header Length     = %2d  bytes\n", (ip->IHL) * 4 ); 
   printf ("Differentiated Services Field: 0x%02x \n", ip->TOS);
   printf ("Total_Length = %d\n", ntohs(ip->Total_length));
   //		printf (" predefinde Total_Length = %d\n", ihdr->tot_len);
   printf ("Identification = 0x%04x (%d)\n", ntohs(ip->ident_length),
         ntohs(ip->ident_length)  );
   
   temp_offset = ntohs(ip->frg_offset);
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
   printf ("Time To Live     = %d\n", ip->TTL);
   printf ("protocol= %u (%s)\n", ip->protocol, protoname[ip->protocol]);
   printf (" Header chesum  = 0x%04x\n", ntohs(ip->header_checksum));

   printf ("dst = %x \n", ntohs (ip->dest_addr));


   printf (" wireshark: \n");
      printf ("------------\n");
      printf( "\t ip.src==%s\n",(inet_ntop(AF_INET, (&ip->source_addr), 
                  buf, size)));
      printf( "\t p.dst==%s\n",(inet_ntop(AF_INET, (&ip->dest_addr), 
                  buf, size)));


}



int main() 
{

   int s = -1, rx = -1, i = -1 ,j = -1;
   char *ptr = NULL ,  *buffer = NULL ;
   struct sockaddr_in cli;
   struct in_addr  addr;
   FILE *fp;
   int x =-1;
   unsigned char * dump = NULL;
   char c = -1;
   ETHRENT *eth ;

#if 0
   printf ("sizeof ethernet = %d \n", sizeof (ETHRENT)); 
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

      /*  Buffer contents are dump it into file */
      fp = fopen ("/home/karthik/practice/buffer.txt","w");
      if (fp == NULL)
         perror (" open:");

      fwrite ( buffer ,rx,1,fp);

      fclose(fp);


      eth = (ETHRENT *)buffer;
      printf ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
      printf ("EThernet II: \n");
      printf ("dest   =(" );
      for (i =0 ; i < 6; i++)
         printf ("%02x:", (eth->dest[i])); 
      printf(")\n");
      printf ("src =(" );
      for (i =0 ; i < 6; i++)
         printf ("%02x:", (eth->source[i])); 
      printf(")\n"); 

      printf ("type  : IP (0x%04x )\n",  ntohs(eth->ethrent_type) ); 
      printf ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");


      display_ipheader (buffer);


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

//I m here

   return 0;
}
