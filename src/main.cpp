// http://doc.qt.io/qt-5/qtwebview-minibrowser-example.html
#include <unistd.h>
#include <fcntl.h>

#include <getopt.h>
#include <unistd.h>
#include <iostream>

#include <QtCore/QString>
#include "QtCore/QSocketNotifier"
#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtWebView/QtWebView>
#include <QtQml/QQmlContext>
#include <QtDebug>

#include "moc_Interpreter.cpp"
#include "moc_KioskContext.cpp"

#define VERSION "0.0.1"

int version() {
  std::cout << "kiosk " << VERSION;
#if DEBUG
  std::cout << " -- debug version";
#endif
  std::cout << std::endl;
  std::cout << "Copyright (C) 2017 Jean-Daniel Michaud." << std::endl;
  std::cout << "License MIT: MIT License <https://opensource.org/licenses/MIT>." << std::endl;
  std::cout << "This is free software: you are free to change and redistribute it." << std::endl;
  std::cout << "There is NO WARRANTY, to the extent permitted by law." << std::endl;
  std::cout << std::endl;
  std::cout << "Written by Jean-Daniel Michaud" << std::endl;
  return 0;
}

int help() {
  std::cout << "Usage: kiosk [OPTION]... [URL]" << std::endl;
  std::cout << "  -v    return the version" << std::endl;
  std::cout << "  -h    display this help" << std::endl;
  std::cout << "  -c    read commands from the standard input" << std::endl;
  return 0;
}

int do_version, do_help, read_stdin;
struct option longopts[] = {
   { "version", no_argument,       & do_version,    1   },
   { "help",    no_argument,       & do_help,       1   },
   { "cli",     no_argument,       & read_stdin,    0   },
   { 0, 0, 0, 0 }
};

void manage_options(int argc, char **argv, QString &url) {
  // If no url is provided, the value is ""
  int c;
  while ((c = getopt_long(argc, argv, "vhc", longopts, NULL)) != -1) {
    switch (c) {
    case 0: /* getopt_long() set a variable, just keep going */
      break;
    case 'h':
      help();
      exit(0);
    case 'v':
      version();
      exit(0);
    case 'c':
      read_stdin = 1;
      std::cout << "read_stdin:" << read_stdin << std::endl;
      break;
    case 1:
      break;
    case ':':   /* missing option argument */
      std::cerr << "option '" << argv[optind - 1]
                << "' requires an argument" << std::endl;
      break;
    case '?':   /* invalid option */
      std::cerr << "option `" << argv[optind - 1]
                << "' is invalid: ignored" << std::endl;
      break;
    default:
      std::cerr << "error parsing options" << std::endl;
      break;
    }
  }
  // Treat non option argument (url)
  url = argv[optind];
  // Just ignore all subsequent arguments
}

int main(int argc, char *argv[])
{
  // Retrieve parameters
  QString url = "";
  manage_options(argc, argv, url);
  if (url == "") {
    url = "about:blank";
  }

  // Create context
  KioskContext context;
  context.setUrl(url);

  // Create interpreter
  Interpreter interpreter;
  URLCommand urlCommand(context);
  interpreter.register_("url", &urlCommand);

  // Create Application
  QGuiApplication app(argc, argv);
  QtWebView::initialize();
  QGuiApplication::setApplicationDisplayName(
    QCoreApplication::translate("main", "Kiosk"));

  // Create View
  QQuickView view;
  view.rootContext()->setContextProperty("context", &context);
  view.setSource(QUrl("qrc:/main.qml"));
  view.show();

  // If stdin is open, connect to stdin event
  QSocketNotifier sn(STDIN_FILENO, QSocketNotifier::Read);
  if (read_stdin) {
    std::cout << "reading standard input" << std::endl;
    sn.setEnabled(true);
    Interpreter::connect(&sn, SIGNAL(activated(int)), &interpreter, SLOT(readCommand()));
  }

  return app.exec();
}

#include "main.moc"
