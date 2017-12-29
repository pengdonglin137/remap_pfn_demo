CC=arm-none-linux-gnueabi-gcc
CFLAGS=-g

all: user_1 user_2 user_3 user_4 user_5
	cp $^ /nfsroot


user_1:user_1.c
user_2:user_2.c
user_3:user_3.c
user_4:user_4.c
user_5:user_5.c

clean:
	$(RM) user_2 user_1 user_3 user_4 user_5
.PHONY:
	clean all
