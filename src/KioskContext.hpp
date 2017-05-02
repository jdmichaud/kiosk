#ifndef __KIOSK_CONTEXT_HPP__
#define __KIOSK_CONTEXT_HPP__

#include <QtCore/QObject>
#include <QtCore/QString>

class KioskContext : public QObject
{
  Q_OBJECT
public:
  virtual ~KioskContext() {}

  Q_INVOKABLE QString getUrl() const {
    return m_url;
  }

  void setUrl(const QString &url) {
    m_url = url;
    emit urlChanged();
  }

signals:
    void urlChanged();

private:
  QString m_url;
};

#endif // __KIOSK_CONTEXT_HPP__