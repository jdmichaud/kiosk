#include <iostream>

#include "Interpreter.h"

void Interpreter::register_(std::string prefix, ICommand *command) {
  m_commands[prefix] = command;
}

void Interpreter::interpret(std::string line) {
  // Retrieve the prefix
  auto found = line.find_first_of(":");
  if (found == std::string::npos) {
    throw "Command has no prefix";
  }
  auto prefix = line.substr(0, found);
  auto command = line.substr(found);
  m_commands[prefix]->call(command);
}

void Interpreter::readCommand()
{
  std::string line;
  std::getline(std::cin, line);
  std::cout << "read: " << line << std::endl;
}
