all:
	scons

clean:
	scons -c

examples:
	cd examples && scons

clean-examples:
	cd examples && scons -c

install:
	scons install

uninstall:
	scons install -c

.PHONY: all clean examples clean-examples install uninstall
