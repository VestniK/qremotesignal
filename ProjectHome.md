&lt;wiki:gadget url="http://www.ohloh.net/p/389658/widgets/project\_partner\_badge.xml" height="53" border="0"/&gt;

# Description #

QRemoteSignal library allows you to connect Qt4 signals and slots between different applications. It is designed to simplify development of client-server network applications with Qt.

All signals and slots shared by you server are specified in a small simple XML files. Code generation utility which comes with QRemoteSignal produces two classes: one to be used in the server and one to be used in the client application. Calling a slot in one produced class causes emitting the signal with the same name and parameters in another one class. See library [documentation](https://qremotesignal.googlecode.com/git-history/doc/doc/html/index.html) to learn how to use this library in your application.

Version 1.2.0 brings one API backward compatibility issue. Unfortunately I haven't found any way to add possibility to send lists and maps of custom types without breaking API. In most cases there will be no problems but if you are using template converter functions `QVariant createArg(QList<T> val)`, `QVariant createArg(QMap<QString,T> val)` or corresponding versions of `getArgValue` function you need to include **templateconverters.h** header explicitly. See [this section](http://qremotesignal.googlecode.com/svn/tags/1.2.0/doc/html/converters.html#customCnverters) in the documentation for more details.

# Getting latest sources #

This project sources also available on [gitorious](http://gitorious.org/mahjong-night/qremotesignal). In order to get latest sources run
```
$ git clone https://code.google.com/p/qremotesignal/ 
```
or
```
$ git clone git://gitorious.org/mahjong-night/qremotesignal.git
```


# Installation #

## Build from source ##

This library requires Qt SDK version 4.5.0 or later, [QJson](http://qjson.sf.net) library and [CMake](http://cmake.org/) build tool to be build.

Download and unpack latest library sources. Open a terminal and go to the unpacked directory. Run
```
$ mkdir build && cd build
$ cmake ..
$ make
# make install
```

## Arch Linux ##
Arch users can install latest version from AUR https://aur.archlinux.org/packages/qremotesignal/ for example with yourt:
```
$ yaourt -S qremotesignal
```


## Ubuntu packages ##

If you are using Ubuntu you can install this library from the [Launchpad PPA repository](https://launchpad.net/~vestnik/+archive/mahjong-night). Deb packages development is done in the [Bazzar branch](https://code.launchpad.net/~vestnik/+junk/QRemoteSignal-deb) hosted on Launchpad

# Help needed #

There is an issue with building examples with qmake on windows in debug mode: [issue 36](https://code.google.com/p/qremotesignal/issues/detail?id=36). Since I'm not using windows and qmake it's rather hard for me to investigate and fix this issue.

&lt;wiki:gadget url="http://www.ohloh.net/p/389658/widgets/project\_languages.xml" width="360" height="210" border="1"/&gt;