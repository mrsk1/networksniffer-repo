#ifndef header
#define header
	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>	/*errno and perror*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <net/if.h>/*struct ifreq*/
#include <netinet/in.h>
#include <sys/ioctl.h> /*ioctl syscal*/
#include <bits/ioctls.h>



#include "my_struc.h" /* My defined structures*/

#define size 4096

#endif
