#
# checkers.py
#
# Author: VestniK (Sergey N.Vidyuk)
# Date: 20 Jun 2009

import os

def CheckQt4Version(context,min_version='4.0.0'):
   context.Message("Checking for Qt %s or higher..."%min_version)
   try: context.env['QTDIR']
   except KeyError: context.env.Tool('qt4')
   oldEnv = context.env.Clone()
   context.env.EnableQt4Modules(['QtCore'])
   version = min_version.replace('.',',')
   ver_checker_src="""
#include <qglobal.h>

int main() {
#if (QT_VERSION >= QT_VERSION_CHECK(%s))
   return 0;
#else
   return 1;
#endif
}
   """%version
   res = context.TryRun(ver_checker_src,".cpp")[0]
   context.env = oldEnv.Clone()
   context.Result(res)
   return res

def CheckQt4Module(context,module):
   context.Message("Checking for %s module..."%module)
   try: context.env['QTDIR']
   except KeyError: context.env.Tool('qt4')
   oldEnv = context.env.Clone()
   context.env.EnableQt4Modules([module])
   test_src="""
#include <%s>

int main() {
   return 0;
}
   """%module
   res = context.TryLink(test_src,".cpp")
   context.env = oldEnv.Clone()
   context.Result(res)
   return res

def CheckQt4Tool(context,tool):
   context.Message("Checking for Qt4 %s tool..."%tool)
   try: context.env['QTDIR']
   except KeyError: context.env.Tool('qt4')
   ToolPath = ''
   try: ToolPath = {
   'moc': context.env['QT4_MOC'],
   'uic': context.env['QT4_UIC'],
   'rcc': context.env['QT4_RCC'],
   'lupdate': context.env['QT4_LUPDATE'],
   'lrelease': context.env['QT4_LRELEASE'],
   }[tool]
   except:
      context.Result('ERROR! Unknown tool "%s"'%tool)
      return False
   res = os.path.isfile(ToolPath) and os.access(ToolPath, os.X_OK)
   context.Result(res)
   return res

qrs_custom_tests = {'CheckQt4Version' : CheckQt4Version,
                       'CheckQt4Tool' : CheckQt4Tool,
                     'CheckQt4Module' : CheckQt4Module,}
