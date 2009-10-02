all:
	scons

debug:
	scons CCFLAGS="-ggdb -O0 -Wall"

clean:
	scons -c

examples:
	make -C examples

clean-examples:
	make -C examples clean

.PHONY: all clean examples clean-examples
