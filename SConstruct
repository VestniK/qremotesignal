import os
from checkers import *
from builders import *

BaseEnv=Environment(tools=[],ENV=os.environ)
BaseEnv['package'] = 'qremotesignal'
BaseEnv['VERSION'] = '0.6.0svn'

BaseEnv['BUILDERS']['Config'] = Builder(action=Config,suffix='',src_suffix='.in')

if BaseEnv['PLATFORM'] == 'win32':
   BaseEnv.Tool('mingw')
else:
   BaseEnv.Tool('default')
BaseEnv.Tool('qt4')
BaseEnv.Tool('gch')

BaseEnv['CXXFILESUFFIX']='.cpp'

vars = Variables('%s_build.conf'%BaseEnv['PLATFORM'])
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
vars.Save('%s_build.conf'%BaseEnv['PLATFORM'],BaseEnv)

BaseEnv.Tool('smartinstall')
BaseEnv['install_dev'] = True

Help(vars.GenerateHelpText(BaseEnv))

try:
   if BaseEnv['QJson'] != '':
      BaseEnv.Append(CPPPATH = os.path.join(BaseEnv['QJson'],'include') )
      BaseEnv.Append(LIBPATH = os.path.join(BaseEnv['QJson'],'lib') )
   else:
      BaseEnv.ParseConfig(('pkg-config --cflags --libs-only-L QJson'))
except OSError: pass

BaseEnv.AlwaysBuild( BaseEnv.Config('Doxyfile.in') )

Export('BaseEnv')

Depends('tests','qrsc')
SConscript('qrsc/SConscript')
SConscript('qremotesignal/SConscript')
SConscript('tests/SConscript')
