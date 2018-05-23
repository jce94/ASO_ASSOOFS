obj-m := assoofs.o

all: ko mkassoofs



ko:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

mkassoofs_SOURCES:
	mkssoofs.c assoofsh

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm mkassoofs
