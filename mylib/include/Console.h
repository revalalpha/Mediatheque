//#ifndef CONSOLE_H
//#define CONSOLE_H
//
//#include <string>
//#include <vector>
//#include <stdexcept>
//
//enum Color
//{
//      Red
//    , Green
//    , Blue
//    , White
//    , Black
//    , Yellow
//    , Cyan
//    , Magenta
//};
//
//class ConsoleFramebufferPrivateImpl;
//
//class ConsoleFramebuffer
//{
//public:
//    ConsoleFramebuffer();
//    ~ConsoleFramebuffer();
//    void setString(std::string text, Color color = White, Color backColor = Black);
//    void show();
//    void updateConsoleSize();
//    void processInputEvents();
//    std::string getLastCommand();
//    void waitForEnter();
//    std::string readLine(const std::string& prompt = "");
//    int readInt(const std::string& prompt);
//
//private:
//    ConsoleFramebufferPrivateImpl* m_pimpl;
//};
//
//#endif // CONSOLE_H

#pragma once

#include <vector>
#include <string>

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
    void updateSize();
    void writeConsol();
    void parseCommand(const std::string& command, std::string& action, std::vector<std::string>& args);
    std::string getLastCommand();
private:
    ConsoleFramebufferPrivateImpl* m_impl;
};