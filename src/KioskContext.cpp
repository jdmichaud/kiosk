#include "KioskContext.h"

Q_INVOKABLE QString KioskContext::getUrl() const {
  return m_url;
}

void KioskContext::setUrl(const QString &url) {
  m_url = url;
  emit urlChanged();
}
