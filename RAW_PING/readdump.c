#include <stdio.h>

int main()
{
	FILE *fp ;
	char c;
	int i;

	fp = fopen("dump","r");
	if (!fp)
		perror("DUMP:");

	while ( (c = fgetc(fp)) !=EOF)
	{
		if (i%8 ==0)
			putchar(' ');
		if (i%16 == 0)
			putchar('\n');

		printf (" %02x ",c);
		i++;
	}


	fclose(fp);
	return 0;
}

