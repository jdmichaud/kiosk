#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtWebView/QtWebView>
#include <QtDebug>

#include "main.moc"

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);
  QtWebView::initialize();
  QGuiApplication::setApplicationDisplayName(
    QCoreApplication::translate("main", "Kiosk"));


  QQuickView view;
  view.setSource(QUrl("qrc:/main.qml"));
  view.show();

  return app.exec();
}
