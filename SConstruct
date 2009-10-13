import os
from checkers import *
from builders import *

BaseEnv=Environment(tools=[],ENV=os.environ)
BaseEnv['package'] = 'qremotesignal'
BaseEnv['VERSION'] = 'svn'

BaseEnv['BUILDERS']['Config'] = Builder(action=Config,suffix='',src_suffix='.in')

if BaseEnv['PLATFORM'] == 'win32':
   BaseEnv.Tool('mingw')
else:
   BaseEnv.Tool('default')
BaseEnv.Tool('qt4')
BaseEnv.Tool('gch')

BaseEnv['CXXFILESUFFIX']='.cpp'

vars = Variables('build.conf')
vars.Add('CCFLAGS','Custom C compiler flags','')
vars.Add('CPPFLAGS','Custom C/C++ preprocessor flags','')
vars.Add('CXXFLAGS','Custom C++ compiler flags','')
vars.Add('LINKFLAGS','Custom linker flags','')
vars.Add('prefix','install prefix','')
vars.Add('prefix_bin','binaries install prefix','')
vars.Add('prefix_lib','libraries install prefix','')
vars.Add('prefix_pc','pkg-config files install prefix','')
vars.Add('prefix_inc','headers install prefix','')
vars.Add('prefix_data','package data install prefix','')
vars.Add('QJson','QJson library path. Live blank to detect it using pkg-config','')
vars.Update(BaseEnv)
# Hack: need to convert flags lists from strings to lists
BaseEnv['CCFLAGS'] = Split(BaseEnv['CCFLAGS'])
BaseEnv['CPPFLAGS'] = Split(BaseEnv['CPPFLAGS'])
BaseEnv['CXXFLAGS'] = Split(BaseEnv['CXXFLAGS'])
BaseEnv['LINKFLAGS'] = Split(BaseEnv['LINKFLAGS'])
vars.Save('build.conf',BaseEnv)

BaseEnv.Tool('smartinstall')
BaseEnv['install_dev'] = True

Help(vars.GenerateHelpText(BaseEnv))

if BaseEnv['QJson'] != '':
   BaseEnv.Append(CPPPATH = os.path.join(BaseEnv['QJson'],'include') )
   BaseEnv.Append(LIBPATH = os.path.join(BaseEnv['QJson'],'lib') )
else:
   BaseEnv.Append(CXXFLAGS = Split( os.popen('pkg-config --cflags QJson').read() ) )
   BaseEnv.Append(LINKFLAGS = Split( os.popen('pkg-config --libs-only-L QJson').read() ) )

Export('BaseEnv')

Depends('tests','qrsc')
SConscript('qrsc/SConscript')
SConscript('lib/SConscript')
SConscript('tests/SConscript')