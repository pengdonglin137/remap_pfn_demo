#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PAGE_SIZE (4*1024)
#define BUF_SIZE (32*PAGE_SIZE)
#define OFFSET (0)

int main(int argc, const char *argv[])
{
	int fd;
	char *addr = NULL;
	int *brk;

	fd = open("/dev/remap_pfn", O_RDWR);
	if (fd < 0) {
		perror("open failed\n");
		exit(-1);
	}

	addr = mmap(NULL, BUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_LOCKED, fd, 0);
	if (!addr) {
		perror("mmap failed\n");
		exit(-1);
	}
	memset(addr, 0x0, BUF_SIZE);

	printf("Clear Finished\n");

	while(1)
		sleep(1);

	return 0;
}
