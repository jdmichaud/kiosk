#ifndef __INTERPRETER_HPP__
#define __INTERPRETER_HPP__

#include <string>
#include <list>
#include <utility>
#include <algorithm>

#include <QtCore/QObject>

#include "Commands.hpp"

class Interpreter : public QObject {
  Q_OBJECT
public:
  void register_(std::string prefix, ICommand *command);
  void interpret(std::string line);
public slots:
  void readCommand();

private:
  std::map<std::string, ICommand *> m_commands;
};

#endif // __INTERPRETER_HPP__