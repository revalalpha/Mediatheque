#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <vector>

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
    void setCharacter(int row, int col, char car, Color foreground = White, Color background = Black);
    void show();
    void printString(int row, int col, const std::string& str, Color foreground = White, Color background = Black);
    void clear();
    void displayMenu(const std::vector<std::string>& options, int selectedIndex);

private:
    ConsoleFramebufferPrivateImpl* m_pimpl;
};

#endif // CONSOLE_H