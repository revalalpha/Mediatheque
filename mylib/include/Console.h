#ifndef CONSOLE_H
#define CONSOLE_H

#include <vector>
#include <iostream>
#include <string>

enum Color
{
      Red
    , Green
    , Blue
    , White
    , Black
    , Yellow
    , Cyan
    , Magenta
};

class ConsoleFramebufferPrivateImpl;

class ConsoleFramebuffer
{
public:
    ConsoleFramebuffer();
    ~ConsoleFramebuffer();
    void setString(std::string text, Color color = White, Color backColor = Black);
    void show();
    void updateSize();
    void writeConsol();
    void parseCommand(const std::string& command, std::string& action, std::vector<std::string>& args);
    std::string getLastCommand();
    void display(const std::string& text, Color color);
    void displayLine(const std::string& text, Color color);
    std::string readLine();
private:
    ConsoleFramebufferPrivateImpl* m_impl;
};

#endif // CONSOLE_H