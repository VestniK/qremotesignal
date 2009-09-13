# Based on the builder from http://www.scons.org/wiki/GenerateConfig It looks like
# code license is GPL but I'm unsure.

def print_config(msg, two_dee_iterable):
   # this function is handy and can be used for other configuration-printing tasks
   print msg
   for key, val in two_dee_iterable:
      print "    %-20s %s" % (key, val)
   print

def config_build(target, source, env):
   print_config("Generating config with the following settings:",env['CONFIG'].items())

   for a_target, a_source in zip(target, source):
      config = file(str(a_target), "w")
      config_in = file(str(a_source), "r")
      config.write(config_in.read() % env['CONFIG'])
      config_in.close()
      config.close()