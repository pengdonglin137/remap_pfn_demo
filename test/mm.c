#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

#define PAGE_SIZE (4*1024)
#define BUF_SIZE (16*PAGE_SIZE)
#define OFFSET (0)

//devmem2 相当重新固定同样mmap物理地址返回个新用户虚拟地址 

int main(int argc, const char *argv[])
{
	int fd;
	char *addr = NULL;
	char *addr1 = 0xb7b48000;
	int val=0;

	fd = open("/dev/remap_pfn", O_RDWR);
	if (fd < 0) {
		perror("open failed\n");
		exit(-1);
	}
	printf("==addr111 :%x \n",addr1);
	addr = mmap(NULL, BUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_LOCKED, fd, OFFSET);//和此类似：devmem2 相当重新固定同样mmap物理地址返回个新用户虚拟地址 
	// addr = mmap(addr1, BUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_LOCKED, fd, OFFSET);
	if (!addr) {
		perror("mmap failed\n");
		exit(-1);
	}
	val=atoi(argv[1]);
	printf("==addr :%x \n",addr);
	printf("==argv[1] :%x \n",val);
	// sprintf(addr, "I am %x\n", val);
	sprintf(addr, "AAA%x\n", val);

	while(1)
		sleep(1);

	return 0;
}
//测试结果
// root@s32g399ardb3:~/11# ./mm AA&
// [1] 548
// ==addr111 :b7b48000 
// ==addr[ 3312.164353] client: mm (548)
//  [ 3312.164369] code  section: [0x558e450000   0x558e450cdc]
// :[ 3312.164373] data  section: [0x558e460d48   0x558e461010]
// a[ 3312.164375] brk   section: s: 0x55ce1a9000, c: 0x55ce1a9000
// f[ 3312.164378] mmap  section: s: 0x7faf659000
// 4[ 3312.164380] stack section: s: 0x7fc09d0430
// a[ 3312.164382] arg   section: [0x7fc09d0ef2   0x7fc09d0efa]
// 5[ 3312.164386] env   section: [0x7fc09d0efa   0x7fc09d0ff3]
// 0[ 3312.164566] phy: 0x884480000, offset: 0x0, size: 0x10000
// 0[ 3312.164573] remap_pfn_mmap: map 0xffffff8804480000 to 0x7faf4a5000, size: 0x10000
// 0 
// ==argv[1] :0 
// root@s32g399ardb3:~/11# 
// root@s32g399ardb3:~/11# 
// root@s32g399ardb3:~/11# devmem2 0x884480000 
// /dev/mem opened.
// Memory mapped at address 0x7f8dad2000.
// Read at address  0x884480000 (0x7f8dad2000): 0x30414141
// root@s32g399ardb3:~/11# 
