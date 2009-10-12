all:
	scons nocheck=1

clean:
	scons -c

examples:
	make -C examples

clean-examples:
	make -C examples clean

.PHONY: all clean examples clean-examples
