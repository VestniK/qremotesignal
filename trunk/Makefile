all:
	scons nocheck=1

clean:
	scons -c

examples:
	make -C examples

clean-examples:
	make -C examples clean

install:
	scons nocheck=1 install

uninstall:
	scons install -c

.PHONY: all clean examples clean-examples install uninstall
