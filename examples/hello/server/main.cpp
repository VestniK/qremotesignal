/**
 * @file main.cpp
 * @brief Hello example server main function
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 29 Nov 2009
 */
#include <QtCore/QCoreApplication>

#include "server.h"

int main(int argc, char** argv) {
   QCoreApplication app(argc,argv);
   Server server(8081);
   return app.exec();
}
