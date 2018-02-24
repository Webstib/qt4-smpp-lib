#include <QtCore/QCoreApplication>
#include "test_server.h"

int main(int argc, char **argv) {
  QCoreApplication a(argc, argv);

  TestServer test;

  test.start();

  return a.exec();
}

