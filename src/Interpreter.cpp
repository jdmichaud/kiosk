#include <iostream>

#include "Interpreter.h"

void Interpreter::register_(std::string prefix, ICommand *command) {
  m_commands[prefix] = command;
}

void Interpreter::interpret(std::string line) {
  // Retrieve the prefix
  auto found = line.find_first_of(":");
  if (found == std::string::npos) {
    std::cerr << "Invalid command" << std::endl;
    return;
  }
  auto prefix = line.substr(0, found);
  auto command = line.substr(found + 1);
  auto it = m_commands.find(prefix);
  if (it == m_commands.end()) {
    std::cerr << "Unknown command: " << prefix << std::endl;
    return;
  }
  it->second->call(command);
}

void Interpreter::readCommand()
{
  std::string line;
  std::getline(std::cin, line);
  interpret(line);
}
