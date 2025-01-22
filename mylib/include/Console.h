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
    void updateConsoleSize();
    void processInputEvents();
    std::string getLastCommand();
    void waitForEnter();
    std::string readLine(const std::string& prompt = "");
    int readInt(const std::string& prompt);

private:
    ConsoleFramebufferPrivateImpl* m_pimpl;
};

#endif // CONSOLE_H