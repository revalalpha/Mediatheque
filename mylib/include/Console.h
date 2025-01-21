#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <vector>
#include <stdexcept>

enum Color
{
      Red
    , Green
    , Blue
    , White
    , Black
};

class ConsoleFramebufferPrivateImpl;

class ConsoleFramebuffer
{
public:
    ConsoleFramebuffer();
    ~ConsoleFramebuffer();
    void setString(std::string text, Color color = White, Color backColor = Black);
    void show();
    void updateConsoleSize();
    void processInputEvents();
    std::string getLastCommand();

private:
    ConsoleFramebufferPrivateImpl* m_pimpl;
};

#endif // CONSOLE_H