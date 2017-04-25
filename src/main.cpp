#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  QQmlEngine engine;
  QQmlContext *objectContext = new QQmlContext(engine.rootContext());

  QQmlComponent component(&engine, "main.qml");
  QObject *object = component.create(objectContext);

  // ... delete object and objectContext when necessary

  return app.exec();
}
