all:
	scons

clean:
	scons -c

examples:
	make -C examples

clean-examples:
	make -C examples clean

install:
	scons install

uninstall:
	scons install -c

.PHONY: all clean examples clean-examples install uninstall
