all:
	scons nocheck=1

debug:
	scons nocheck=1 CCFLAGS="-ggdb"

clean:
	scons -c
	rm -f *~ lib/*~ qrsc/*~ tests/*~

.PHONY: all clean
