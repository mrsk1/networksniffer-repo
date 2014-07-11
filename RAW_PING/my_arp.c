#include "header.h"

int main()
{
	int sock_fd = -1;
	int arp_proto = 0x0806; 

	sock_fd = socket (AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));

	if (sock_fd < 0) {
		perror("Socket");
		exit(EXIT_FAILURE);
	}

	printf ("Socket Created\n");	
	while(1) {	
		int rec_err_chk = -1;
		unsigned char recv_buffer[size];

		rec_err_chk = recvfrom (sock_fd, (void *)recv_buffer, size, 0 , NULL , NULL);

		if (rec_err_chk < 0) {
			perror("Recvfrom");
			exit(EXIT_FAILURE);
		}
		printf ("Size = %d\n", rec_err_chk);	

		int i = 0;/*! Temporary Iterative Variable*/

		ETHER_FRAME *eth;

		eth = (ETHER_FRAME *) recv_buffer;
#if 0	
		/*
		   Displays Ethernet Header 
		 */
		printf("Dest: ");
		for(i = 0; i < 6; i++)
			printf("%02x", eth -> dest[i]);

		printf("\nSrc: ");	
		for(i = 0; i < 6; i++)
			printf("%02x", eth -> src[i]);

		printf("\nType: %04x\n\n", ntohs (eth -> type));
#endif
		ARP_FRAME *req;

		req = (ARP_FRAME *) (recv_buffer + sizeof(ETHER_FRAME));

		//	printf("17.16.7.240 -> %04x\n", inet_addr("172.16.7.240"));	
		//	printf("dest_ip : %04x\n", req -> dest_ip);
		/*
		   for(i = 0 ; i< 60 ; i++)	
		   printf("%02x", recv_buffer[i]);	
		   printf("\n");*/
		char ptr[size];
		inet_ntop(AF_INET, &(req -> dest_ip), ptr, size);
		printf("Dest : %s\n", ptr);
		int ret = 0;

		ret = strcmp("172.16.7.240", ptr);
		printf("RET = %d\n", ret);

		if(!ret) {	

			/*
			   Displays ARP Header
			 */

			/*printf("Buffer: ");
			  for (i = 0; i < 60 ; i++)
			  printf("%02x", recv_buffer[i]);	

			  printf("\n");*/
#if 0
			printf ("HW Type: %04x\n", req -> hw_type);
			printf ("Protocol Type: %04x\n", req -> p_type);
			printf ("Hardware Address Length: %02x\n", req -> ha_len);
			printf ("Protocol Length: %02x\n", req -> pa_len);
			printf ("Operation Code: %04x\n", htons(req -> opcode));
			printf ("Source MAC: ");
			for (i = 0 ; i < 6 ; i++)
				printf ("%02x", req -> src_mac[i]);
			printf ("\nSource IP: ");
			for (i = 0 ; i < 4 ; i++)
				printf ("%02x", req -> src_ip[i]);
			printf("\nDestination MAC: ");
			for (i = 0 ; i < 6 ; i++)
				printf ("%02x", req -> dest_mac[i]);
			printf ("\nDest IP: ");		
			for (i = 0 ; i < 4 ; i++)
				printf ("%02x", req -> dest_ip[i]);

			printf("\n");
#endif	
			char send_buffer[size];	
			/*	sprintf(send_buffer,
				"%02x%02x%02x%02x%02x%02x"
				"a4badbeec8660806"
				"%04x%04x%02x%02x0002"
				"a4badbeec866"
				"%02x%02x%02x%02x"
				"%02x%02x%02x%02x%02x%02x"
				"%02x%02x%02x%02x\0",
				req -> src_mac[0], req -> src_mac[1],
				req -> src_mac[2], req -> src_mac[3],
				req -> src_mac[4], req -> src_mac[5],
				req -> hw_type, req -> pa_len, req -> ha_len, req -> pa_len, 
				req -> dest_ip[0], req -> dest_ip[1], req -> dest_ip[2], req -> dest_ip[3],	
				req -> src_mac[0], req -> src_mac[1],
				req -> src_mac[2], req -> src_mac[3],
				req -> src_mac[4], req -> src_mac[5],
				req -> src_ip[0], req -> src_ip[1], req -> src_ip[2], req -> src_ip[3]);

				for(i = 0 ; i< 60 ; i++)	
				printf("%02x", send_buffer[i]);	
				printf("\n");
			 */
			REPLY_PKT *rep;
			rep = (REPLY_PKT *) send_buffer;/*Check the necessity of this line*/
			memcpy (rep -> dest, "\0", sizeof (rep -> dest));
			printf("size of = %d\n", sizeof(eth -> src[1]));
			for(i = 0; i < 6; i++)
				memcpy (&(rep -> dest[i]), &(eth -> src[i]), sizeof (eth -> src[i]));

			/*
			   Getting Hardware Address
			 */

			struct ifreq if_mac;

			memset (&if_mac, 0, sizeof (if_mac));
			snprintf (if_mac.ifr_name, sizeof (if_mac.ifr_name), "%s", "eth1");
			if (ioctl (sock_fd, SIOCGIFHWADDR, &if_mac) < 0) {
				perror ("IOCTL");
				exit (EXIT_FAILURE);
			}
			memcpy (rep -> src, if_mac.ifr_hwaddr.sa_data, sizeof (rep -> src));
			//		memcpy (rep -> src, "a4badbeec866", sizeof (eth -> dest));
			rep -> type = eth -> type;

			printf("Dest_after: ");
			for(i = 0; i < 6; i++)
				printf("%02x", rep -> dest[i]);

			printf("\nSrc_after: ");	
			for(i = 0; i < 6; i++)
				printf("%02x", rep -> src[i]);

			memcpy (rep -> src_mac, req -> src_mac, sizeof (req -> src_mac));
			memcpy (&(rep -> hw_type), &(req -> hw_type), sizeof (req -> hw_type));
			memcpy (&(rep -> p_type), &(req -> p_type), sizeof (req -> p_type));
			memcpy (&(rep -> ha_len), &(req -> ha_len), sizeof (req -> ha_len));
			memcpy (&(rep -> pa_len), &(req -> pa_len), sizeof (req -> pa_len));
			rep -> opcode  = (unsigned short int) 0x0002;
			memcpy (rep -> src, if_mac.ifr_hwaddr.sa_data, sizeof (rep -> src));
			//		memcpy (&(rep -> src_mac), "a4badbeec866", sizeof ("a4badbeec866"));
			memcpy (rep -> src_ip, req -> dest_ip, sizeof (req -> dest_ip));
			memcpy (rep -> dest_mac, req -> src_mac, sizeof (req -> src_mac));
			memcpy (rep -> dest_ip, req -> src_ip, sizeof (req -> src_ip));

			//	memcpy(send_buffer, rep, sizeof (rep));	

			printf("\nlen = %d\n", strlen (send_buffer));	


			/*	for(i = 0 ; i < 60 ; i++)	
				printf("%02x", send_buffer[i]);	
				printf("\n");
			 */

			struct sockaddr dest1;
			//dest1.sin_family = AF_PACKET;
			//		dest.sin_port = 
			//dest1.sin_addr.s_addr = inet_addr(const char *)&req -> src_ip);	
			
//			dest1. sin_port = htons(INADDR_ANY);
			strcpy (dest1.sa_data, "eth0");
			int send = 0;
			FILE *fp ;
			char myb[100];
			fp = fopen ("dump" , "w");
			if (!fp)
				perror("OPEN:");


			fwrite (send_buffer, 60, 1, fp);
			fclose(fp);

			printf (" the sockfd = %d \n",sock_fd);
	send = sendto (sock_fd,myb ,sizeof(myb) , 0, (struct sockaddr *) &dest1, (socklen_t) sizeof (dest1));	

			if (send == -1) {
				perror("Send 123");
			}
				printf (" wirten into file\n");
				exit(1);
		}
	}
	return EXIT_SUCCESS;
}


