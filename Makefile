all:
	scons nocheck=1

debug:
	scons nocheck=1 CCFLAGS="-ggdb"

clean:
	scons -c
	rm -f *~ lib/*~ qrsc/*~ tests/*~

examples:
	make -C examples

clean-examples:
	make -C examples clean

.PHONY: all clean examples clean-examples
