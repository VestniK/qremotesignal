/**
 * @file interfacecompiler.h
 * @brief InterfaceCompiler class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 5 Aug 2009
 */
#ifndef InterfaceCompiler_H
#define InterfaceCompiler_H

#include "interfacedocument.h"

class InterfaceCompiler {
   public:
      InterfaceCompiler (InterfaceDocument* interface) {mInterface = interface;};
      ~InterfaceCompiler() {};

      bool compileServiceHeader();
      bool compileServiceSource();
      bool compileClientHeader();
      bool compileClientSource();

   protected:
      bool xsltTransformation(QFile &source, QFile &xsltFile);
   private:
      InterfaceDocument *mInterface;
};

#endif
