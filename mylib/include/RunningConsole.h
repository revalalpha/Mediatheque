#ifndef RUNNING_CONSOLE_H
#define RUNNING_CONSOLE_H

#include "LibrarySystem.h"
#include "Console.h"


class Database {
public:
    Database();
    ~Database();
    void Exe();

private:
    void addString(const std::string& str);
    bool isNewCommand(const std::string& str) const;

    ConsoleFramebuffer* m_console;
    std::string m_lastCommand;
    LibrarySystem* m_library;
};

#endif