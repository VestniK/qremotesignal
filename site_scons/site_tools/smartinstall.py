# -*- coding: utf-8 -*-
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

class ToolSmartinstallWarning(SCons.Warnings.Warning): pass

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
      return os.path.join(env['prefix'],'share',str(env['package']).lower())

def get_default_man_prefix(env):
   if env['PLATFORM'] == 'win32':
      return None
   else:
      return os.path.join(env['prefix'],'share','man')

def get_default_qmake_feature_prefix(env):
   return os.path.join(env['prefix'],'share','qt4','mkspecs','features')

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
      for node in src:
         if os.path.splitext( str(node) )[1] == env['SHLIBSUFFIX']:
            item_name = '%s.%s.%s.%s'%(
               os.path.basename(str(node)),
               env['MAJOR_VERSION'],
               env['MINOR_VERSION'],
               env['PATCH_VERSION']
            )
            item_major_link = '%s.%s'%(
               os.path.basename(str(node)),
               env['MAJOR_VERSION'],
            )
            item_link = os.path.basename(str(node))
            item_path = os.path.join(env['prefix_lib'],item_name)
            item = env.InstallAs(item_path,node)
            for it in item: env.AddPostAction(it , Chmod(str(it),bin_mode) )
            res.extend( item )
            res.append( env.Command(os.path.join(env['prefix_lib'],item_major_link),os.path.join(env['prefix_lib'],item_name),'ln -s ${SOURCE.file} ${TARGET.file}',chdir=env['prefix_lib']) )
            res.append( env.Command(os.path.join(env['prefix_lib'],item_link),os.path.join(env['prefix_lib'],item_name),'ln -s ${SOURCE.file} ${TARGET.file}',chdir=env['prefix_lib']) )
         else:
            item = env.Install(env['prefix_lib'],node)
            for it in item: env.AddPostAction(it , Chmod(str(it),res_mode) )
            res.extend(item)
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

def install_data(env,dest_subdir,src,mode=res_mode):
   if not 'install' in COMMAND_LINE_TARGETS: return None
   res = env.Install(os.path.join(env['prefix_data'],dest_subdir),src)
   env.Alias('install',res)
   for obj in res: env.AddPostAction(obj , Chmod(str(obj),mode) )
   return res

def install_man(env,src,section,mode=res_mode):
   if not 'install' in COMMAND_LINE_TARGETS: return None
   if env['PLATFORM'] == 'win32': return None
   res = env.Install(os.path.join(env['prefix_man'],'man%s'%section),src)
   env.Alias('install',res)
   for obj in res: env.AddPostAction(obj , Chmod(str(obj),mode) )
   return res

def install_qmake_feature(env,src,mode=res_mode):
   if not 'install' in COMMAND_LINE_TARGETS: return None
   if not env['install_dev']: return None
   inst_path = env['prefix_qmake_feature']
   if inst_path == 'GLOBAL':
       try:
          cmd_line = '%s -query QMAKE_MKSPECS'%(env['QT4_QMAKE'])
          inst_path = os.path.join(os.popen( cmd_line ).read().strip(),'features')
       except KeyError:
          inst_path = get_default_qmake_feature_prefix(env)
          SCons.Warnings.warn(
             ToolSmartinstallWarning,
             'Qt4 qmake utility not found. Can\'t install QMake feature "%s" to global features loaction. It will be installed to "%s" directory'
             %(str(src),inst_path)
          )
   res = env.Install(inst_path,src)
   env.Alias('install',res)
   for obj in res: env.AddPostAction(obj , Chmod(str(obj),mode) )
   return res

def install_cmake_config(env,src,mode=res_mode):
   if not 'install' in COMMAND_LINE_TARGETS: return None
   if not env['install_dev']: return None
   inst_path = os.path.join(env['prefix_lib'],'cmake',env['package'])
   res = env.Install(inst_path,src)
   env.Alias('install',res)
   for obj in res: env.AddPostAction(obj , Chmod(str(obj),mode) )
   return res

#####################
# Generate function #
#####################
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
   except: env['prefix_data'] = get_default_data_prefix(env)
   try:
      if env['prefix_man'] == '':
         env['prefix_man'] = get_default_man_prefix(env)
   except: env['prefix_man'] = get_default_man_prefix(env)
   try:
      if env['prefix_qmake_feature'] == '':
         env['prefix_qmake_feature'] = get_default_qmake_feature_prefix(env)
   except: env['prefix_qmake_feature'] = get_default_qmake_feature_prefix(env)
   # install or no development files
   try: env['install_dev']
   except: env['install_dev'] = False
   try: env['MAJOR_VERSION']
   except: env['MAJOR_VERSION'] = '0'
   try: env['MINOR_VERSION']
   except: env['MINOR_VERSION'] = '1'
   try: env['PATCH_VERSION']
   except: env['PATCH_VERSION'] = '0'
   try: env['TWEAK_VERSION']
   except: env['TWEAK_VERSION'] = None
   env.AddMethod(install_bin,'InstallProgram')
   env.AddMethod(install_lib,'InstallLibrary')
   env.AddMethod(install_pc,'InstallPkgConfig')
   env.AddMethod(install_inc,'InstallHeader')
   env.AddMethod(install_man,'InstallMan')
   env.AddMethod(install_qmake_feature,'InstallQMakeFeature')
   env.AddMethod(install_cmake_config,'InstallCMakeConfig')
   env.AddMethod(install_data,'InstallData')
