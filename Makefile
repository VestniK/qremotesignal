all:
	scons nocheck=1

debug:
	scons nocheck=1 CCFLAGS="-ggdb"

tests: debug
	scons nocheck=1 CCFLAGS="-ggdb" tests

clean:
	scons -c tests
	scons -c
	rm -f *~ lib/*~ lib/QtSoap/*~ xic/*~ tests/*~

.PHONY: all clean
