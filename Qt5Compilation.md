# Introduction #

There is a port of the library for Qt5 available on the qt5 branch in the repo. The port has major varsion 2 and all of the installed files have the version as a name suffix. Later on I'm planning to have packages for the 2.0.0 version but it requires to be able to create package for the Qt5 version of QJson library which can be installed with Qt4 version without file conflicts.

# Build #

First of all you need QJSON compiled from its master sources:
```
$ git clone https://github.com/flavio/qjson.git
$ cd qjson
$ mkdir build && cd build
$ cmake -DCMAKE_INSTALL_PREFIX=${SOME_DESTINATION_DIR} ..
$ make && make install
```

Then tou can build and install QRemoteSignal
```
$ git clone https://sir.vestnik@code.google.com/p/qremotesignal/
$ cd qremotesignal && git checkout -b qt5 origin/qt5
$ mkdir build && cd build
$ cmake -DCMAKE_INSTALL_PREFIX=${SOME_DESTINATION_DIR} -DCMAKE_PREFIX_PATH=${SOME_DESTINATION_DIR} ..
$ make && make install
```
Notice that you need to set CMAKE\_PREFIX\_PATH pointing to the path of the Qt5 version of the QJson installation.

# Usage #

The only thing you have to change to use Qt5 version of the QRemoteSignal is to change `find_package(QRemoteSignal)` to `find_package(QRemoteSignal2)` or `COFIG += qremotesignal` to `COFIG += qremotesignal2` if you using QMake (Scons compilation is not yet adjusted).