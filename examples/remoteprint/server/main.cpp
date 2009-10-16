/**
 * @file printserver.cpp
 * @brief printserver application entry point
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 12 Sep 2009
 */
#include "server.h"

int main(int argc, char** argv) {
   QCoreApplication app(argc,argv);

   Server* srv = new Server(&app);

   return app.exec();
}
