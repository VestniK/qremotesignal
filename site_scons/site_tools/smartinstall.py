import os

from SCons.Action import Action
from SCons.Builder import Builder
from SCons.Node.FS import File
from SCons.Script import COMMAND_LINE_TARGETS
import SCons.Defaults
import SCons.Tool

from SCons.Script import Chmod

bin_mode = 0755
res_mode = 0644

def exists(env):
   if env.has_key('package') and env['package']:
      return True
   else:
      print "Smart install tool require env[\'package\'] to be set to the name of your package"
      return False

# small functions detecting default installation directories for the target OS
def get_default_prefix(env):
   if env['PLATFORM'] == 'win32':
      return os.path.join('C:\\Program Files',env['package'])
   else:
      return '/usr/local'

def get_default_bin_prefix(env):
   return os.path.join(env['prefix'],'bin')

def get_default_lib_prefix(env):
   return os.path.join(env['prefix'],'lib')

def get_default_inc_prefix(env):
   return os.path.join(env['prefix'],'include',env['package'])

def get_default_pc_prefix(env):
   return os.path.join(env['prefix'],'lib','pkgconfig')

def get_default_data_prefix(env):
   if env['PLATFORM'] == 'win32':
      return os.path.join(env['prefix'],'data')
   else:
      return os.path.join(env['prefix'],'share',env['package'])

#####################
# Install functions #
#####################
def install_bin(env,src):
   if not 'install' in COMMAND_LINE_TARGETS: return None
   res = env.Install(env['prefix_bin'],src)
   env.Alias('install',res)
   for obj in res: env.AddPostAction(obj , Chmod(str(obj),bin_mode) )
   return res

def install_lib(env,src):
   if not 'install' in COMMAND_LINE_TARGETS: return None
   res = []
   if env['PLATFORM'] == 'win32':
      for node in src:
         if os.path.splitext( str(node) )[1] == env['SHLIBSUFFIX']:
            res.extend( env.Install(env['prefix_bin'],node) )
         else:
            if env['install_dev'] :
               res.extend( env.Install(env['prefix_lib'],node) )
   else:
      # todo create autotools like symlinks for .so files
      # (libMy.so -> libMy.so.1 -> libMy.so.1.4 -> libMy.so.1.4.2)
      res = env.Install(env['prefix_lib'],src)
      for obj in res:
         if os.path.splitext( str(obj) )[1] == env['SHLIBSUFFIX']:
            env.AddPostAction(obj , Chmod(str(obj),bin_mode) )
         else:
            env.AddPostAction(obj , Chmod(str(obj),res_mode) )
   env.Alias('install',res)
   return res

def install_pc(env,src):
   if not 'install' in COMMAND_LINE_TARGETS: return None
   if env['install_dev'] :
      res = env.Install(env['prefix_pc'],src)
      env.Alias('install',res)
      for obj in res: env.AddPostAction(obj , Chmod(str(obj),res_mode) )
      return res

def install_inc(env,src):
   if not 'install' in COMMAND_LINE_TARGETS: return None
   if env['install_dev'] :
      res = env.Install(env['prefix_inc'],src)
      env.Alias('install',res)
      for obj in res: env.AddPostAction(obj , Chmod(str(obj),res_mode) )
      return res

def install_data(env,src,mode=res_mode):
   if not 'install' in COMMAND_LINE_TARGETS: return None
   res = env.Install(env['prefix_data'],src)
   env.Alias('install',res)
   for obj in res: env.AddPostAction(obj , Chmod(str(obj),mode) )
   return res

def generate(env):
   try:
      if env['prefix'] == '':
         env['prefix'] = get_default_prefix(env)
   except: env['prefix'] = get_default_prefix(env)
   try:
      if env['prefix_bin'] == '':
         env['prefix_bin'] = get_default_bin_prefix(env)
   except: env['prefix_bin'] = get_default_bin_prefix(env)
   try:
      if env['prefix_lib'] == '':
         env['prefix_lib'] = get_default_lib_prefix(env)
   except: env['prefix_lib'] = get_default_lib_prefix(env)
   try:
      if env['prefix_inc'] == '':
         env['prefix_inc'] = get_default_inc_prefix(env)
   except: env['prefix_inc'] = get_default_inc_prefix(env)
   try:
      if env['prefix_pc'] == '':
         env['prefix_pc'] = get_default_pc_prefix(env)
   except: env['prefix_pc'] = get_default_pc_prefix(env)
   try:
      if env['prefix_data'] == '':
         env['prefix_data'] = get_default_data_prefix(env)
   except: env['prefix_pc'] = get_default_data_prefix(env)
   # install or no development files
   try: env['install_dev']
   except: env['install_dev'] = False
   env.AddMethod(install_bin,'InstallProgram')
   env.AddMethod(install_lib,'InstallLibrary')
   env.AddMethod(install_pc,'InstallPkgConfig')
   env.AddMethod(install_inc,'InstallHeader')
   env.AddMethod(install_data,'InstallData')