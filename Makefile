all:
	scons nocheck=1

debug:
	scons nocheck=1 CCFLAGS="-ggdb -O0 -Wall"

clean:
	scons -c

examples:
	make -C examples

clean-examples:
	make -C examples clean

.PHONY: all clean examples clean-examples
