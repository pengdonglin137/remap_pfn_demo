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

extern void *func2(void);

void func(num)
{
	char buffer[PAGE_SIZE];
	printf("%d\n", num);
	while (1)
		func(--num);
}

int global_bss[PAGE_SIZE];
int global_data[PAGE_SIZE] = {5};

int main(int argc, const char *argv[])
{
	int fd;
	char *addr = NULL;
	int *brk;
	char buffer[1024*1024];
	char *addr2;

	printf("global_bss: 0x%p, global_data: 0x%p\n", &global_bss, &global_data);
	memset(global_bss, 0x55, PAGE_SIZE*4);
	memset(global_data, 0x55, PAGE_SIZE*4);

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

	/*brk = malloc(1024*PAGE_SIZE);*/
	/*memset(brk, 0x0, 1024*PAGE_SIZE);*/

	addr2 = func2();

	//func(0);
	while(1) {
		sleep(1);
	}

	return 0;
}
