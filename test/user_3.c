#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

#define PAGE_SIZE (4*1024)
#define BUF_SIZE (16*PAGE_SIZE)
#define OFFSET (16*PAGE_SIZE)

int main(int argc, const char *argv[])
{
	int fd;
	char *addr = NULL;

	fd = open("/dev/remap_pfn", O_RDWR);
	if (fd < 0) {
		perror("open failed\n");
		exit(-1);
	}

	addr = mmap(NULL, BUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_LOCKED, fd, OFFSET);
	if (!addr) {
		perror("mmap failed\n");
		exit(-1);
	}

	sprintf(addr, "I am %s\n", argv[0]);

	while(1)
		sleep(1);

	return 0;
}
