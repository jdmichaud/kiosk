#ifndef __COMMANDS_HPP__
#define __COMMANDS_HPP__

#include "KioskContext.h"

class ICommand {
public:
  virtual void call(std::string) = 0;
};

class URLCommand: public ICommand {
public:
  explicit URLCommand(KioskContext &context) : m_context(context) {}
  virtual ~URLCommand() {}
  void call(std::string url) {
    m_context.setUrl(QString::fromUtf8(url.c_str()));
  }
private:
  KioskContext &m_context;
};

#endif // __COMMANDS_HPP__
