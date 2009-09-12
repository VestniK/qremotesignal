import os
from checkers import *
from builders import *

BaseEnv=Environment(tools=[],ENV=os.environ)
BaseEnv['BUILDERS']['Config'] = Builder(action=config_build,suffix='',src_suffix='.in')
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

BaseEnv['CONFIG'] = {}
BaseEnv['CONFIG']['PREFIX'] = ARGUMENTS.get('PREFIX','/usr/local')
BaseEnv['CONFIG']['PREFIX_BIN'] = os.path.join(BaseEnv['CONFIG']['PREFIX'],'bin')
BaseEnv['CONFIG']['PREFIX_LIB'] = os.path.join(BaseEnv['CONFIG']['PREFIX'],'lib')
BaseEnv['CONFIG']['PREFIX_PC'] = os.path.join(BaseEnv['CONFIG']['PREFIX'],'lib','pkgconfig')
BaseEnv['CONFIG']['PREFIX_INC'] = os.path.join(BaseEnv['CONFIG']['PREFIX'],'include','qremotesignal')
BaseEnv['CONFIG']['VERSION'] = 'svn'

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

Depends('tests','qrsc')
SConscript('qrsc/SConscript')
SConscript('lib/SConscript')
SConscript('tests/SConscript')
BaseEnv.Alias('install',BaseEnv['CONFIG']['PREFIX'])
