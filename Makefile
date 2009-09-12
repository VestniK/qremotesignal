all:
	scons nocheck=1

debug:
	scons nocheck=1 CCFLAGS="-ggdb"

clean:
	scons -c
	rm -f *~ lib/*~ lib/QtSoap/*~ xic/*~ tests/*~

.PHONY: all clean
