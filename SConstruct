import os
from checkers import *

BaseEnv=Environment(tools=[],ENV=os.environ)
if BaseEnv['PLATFORM'] == 'win32':
   BaseEnv.Tool('mingw')
else:
   BaseEnv.Tool('default')
BaseEnv.Tool('qt4')

BaseEnv['CXXFILESUFFIX']='.cpp'
BaseEnv['QT4_UICDECLPREFIX'] = 'ui_'

BaseEnv['CCFLAGS']=Split( ARGUMENTS.get('CCFLAGS','') )
BaseEnv['CPPFLAGS']=Split( ARGUMENTS.get('CPPFLAGS','') )
BaseEnv['CXXFLAGS']=Split( ARGUMENTS.get('CXXFLAGS','') )
BaseEnv['LINKFLAGS']=Split( ARGUMENTS.get('LDFLAGS','') )
BaseEnv['PREFIX']=ARGUMENTS.get('prefix','/usr/local')

if not (ARGUMENTS.get('nocheck') or GetOption('clean') or GetOption('help') ) :
   confEnv = BaseEnv.Clone()
   if confEnv['PLATFORM'] != 'win32':
      confEnv.ParseConfig('pkg-config --cflags --libs QJson')
   conf = Configure(confEnv,
                  custom_tests = {'CheckQt4Version' : CheckQt4Version,
                                     'CheckQt4Tool' : CheckQt4Tool,
                                   'CheckQt4Module' : CheckQt4Module})

   if not conf.CheckCXX(): Exit(1)
   if not conf.CheckQt4Version("4.5.0"): Exit(1)
   if not conf.CheckQt4Tool('moc'): Exit(1)
   if not conf.CheckQt4Tool('rcc'): Exit(1)
   if not conf.CheckQt4Module('QtCore'): Exit(1)
   if not conf.CheckQt4Module('QtXml'): Exit(1)
   if not conf.CheckQt4Module('QtXmlPatterns'): Exit(1)
   if not conf.CheckQt4Module('QtTest'): Exit(1)
   if not conf.CheckLibWithHeader('qjson','qjson/parser.h','c++'): Exit(1)

   conf.Finish()
   print "Confiduration done\n"

Export('BaseEnv')
SConscript('xic/SConscript')
libs = SConscript('lib/SConscript')
Default('xic')
Default('lib')
BaseEnv.Alias('install',BaseEnv['PREFIX'])

Export('libs')
SConscript('tests/SConscript')
