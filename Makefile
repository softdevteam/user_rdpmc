obj-m += user_rdpmc.o

all: user_rdpmc.ko test_rdpmc

user_rdpmc.ko: user_rdpmc.c
	 make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules

test_rdpmc: test_rdpmc.c
	${CC} ${CFLAGS} -std=gnu99 -o test_rdpmc test_rdpmc.c

.PHONY: clean
clean:
	 make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	 -rm test_rdpmc
