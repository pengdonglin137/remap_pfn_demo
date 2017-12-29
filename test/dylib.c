#include <stdlib.h>
#include <string.h>

#define PAGE_SIZE (4*1024)

static char *buf2[1024*PAGE_SIZE];

char *func2(void)
{
	//char *buf = malloc(1024*PAGE_SIZE);
	char *buf;
	memset(buf2, 0x5, sizeof(buf2));
	return buf;
}
