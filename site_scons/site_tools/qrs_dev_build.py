import os.path

from SCons.Action import Action
from SCons.Builder import Builder
import SCons.Defaults
import SCons.Tool

def qrsc_emiter(target, source, env):
   header_target = env.File(os.path.splitext(str(target[0]))[0]+'.h')
   target.append(header_target)
   return target,source

def service_action(env,interface):
   cpp = env.File( os.path.splitext(str(interface))[0]+'service.cpp' )
   service = env.QRSBuildService(cpp,interface)
   targets = [ service[0] ]
   if not os.path.exists(str(service[0])) and not os.path.exists(str(service[1])):
      targets.append(env.Moc4(service[1]))
   return targets

def client_action(env,interface):
   cpp = env.File( os.path.splitext(str(interface))[0]+'client.cpp' )
   client = env.QRSBuildClient(cpp,interface)
   targets = [ client[0] ]
   if not os.path.exists(str(client[0])) and not os.path.exists(str(client[1])):
      targets.append(env.Moc4(client[1]))
   return targets

def exists(env):
   return None

def generate(env):
   try: env['QTDIR']
   except KeyError: env.Tool('qt4')

   env['BUILDERS']['QRSBuildService'] = Builder(emitter=qrsc_emiter,
      action="$QRSC --service --header ${TARGETS[1]} --source ${TARGETS[0]} $SOURCE")
   env['BUILDERS']['QRSBuildClient'] = Builder(emitter=qrsc_emiter,
      action="$QRSC --client --header ${TARGETS[1]} --source ${TARGETS[0]} $SOURCE")
   env.AddMethod(service_action,"QRSService")
   env.AddMethod(client_action,"QRSClient")

