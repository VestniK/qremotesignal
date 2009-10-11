# Based on the builder from http://www.scons.org/wiki/GenerateConfig It looks like
# code license is GPL but I'm unsure.

def config_build(target, source, env):
   for a_target, a_source in zip(target, source):
      config = file(str(a_target), "w")
      config_in = file(str(a_source), "r")
      config.write(config_in.read() % env.Dictionary())
      config_in.close()
      config.close()