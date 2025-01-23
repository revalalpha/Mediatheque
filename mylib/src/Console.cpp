//#include "Console.h"
//
//#include <Windows.h>
//#include <vector>
//#include <algorithm>
//#include <iostream>
//
//class ConsoleFramebufferPrivateImpl
//{
//public:
//    ConsoleFramebufferPrivateImpl();
//    void show();
//    void setString(std::string text, Color color = White, Color backColor = Black);
//    void updateSize();
//    void processInputEvents();
//    std::string getLastCommand();
//    void waitForEnter();
//    std::string readLine(const std::string& prompt = "");
//    int readInt(const std::string& prompt);
//private:
//    void setCharacter(int row, int col, char car, Color foreground, Color background);
//    void copyStringToEnd(std::string string);
//    void addCommandToHistory(std::string& string);
//    void resize(int numRows, int numCols);
//    void setString(int row, int i);
//    void eraseEmtpyHistory();
//    void printText();
//private:
//    HANDLE m_handleOutput;
//    HANDLE m_handleInput;
//    std::vector<CHAR_INFO> m_buffer;
//    SHORT windowWidth;
//    SHORT windowHeight;
//    int m_numRows;
//    int m_numCols;
//    int m_idx;
//    std::string m_lastCommand;
//    std::vector<std::string> m_orderHistory;
//    std::vector <std::string> m_toWrite;
//    std::vector <Color> m_colorToWrite;
//    std::vector <Color> m_backColorToWrite;
//};
//
//void ConsoleFramebufferPrivateImpl::updateSize()
//{
//    CONSOLE_SCREEN_BUFFER_INFO sbi;
//    BOOL result = GetConsoleScreenBufferInfo(m_handleOutput, &sbi);
//    windowWidth = sbi.srWindow.Right - sbi.srWindow.Left + 1;
//    windowHeight = sbi.srWindow.Bottom - sbi.srWindow.Top + 1;
//    resize(windowHeight, windowWidth);
//    eraseEmtpyHistory();
//}
//
//void ConsoleFramebufferPrivateImpl::processInputEvents()
//{
//    INPUT_RECORD inputRecord;
//    DWORD events;
//    ReadConsoleInput(m_handleInput, &inputRecord, 1, &events);
//    if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown)
//    {
//        wchar_t key = inputRecord.Event.KeyEvent.uChar.UnicodeChar;
//        WORD virtualKey = inputRecord.Event.KeyEvent.wVirtualKeyCode;
//        if (key == '\r') // ENTER
//        {
//            // Save the last command
//            m_lastCommand = m_orderHistory[m_idx];
//            if (m_idx != m_orderHistory.size() - 1)
//                copyStringToEnd(m_orderHistory[m_idx]);
//            std::string newstring;
//            addCommandToHistory(newstring);
//        }
//        else if (virtualKey == VK_UP) // UP
//        {
//            if (m_idx > 0)
//                --m_idx;
//        }
//        else if (virtualKey == VK_DOWN) // DOWN
//        {
//            if (m_idx < static_cast<int>(m_orderHistory.size()) - 1)
//                ++m_idx;
//        }
//        else if (key >= 32)
//        {
//            // Duplicate the last string
//            if (m_idx != m_orderHistory.size() - 1)
//                copyStringToEnd(m_orderHistory[m_idx]);
//            m_orderHistory[m_idx] += key;
//        }
//        else if (key == '\b' && !m_orderHistory[m_idx].empty())
//        {
//            // Duplicate the last string
//            if (m_idx != m_orderHistory.size() - 1)
//                copyStringToEnd(m_orderHistory[m_idx]);
//            m_orderHistory[m_idx].pop_back();
//        }
//    }
//}
//
//std::string ConsoleFramebufferPrivateImpl::getLastCommand()
//{
//    return m_lastCommand;
//}
//
//void ConsoleFramebufferPrivateImpl::copyStringToEnd(std::string string)
//{
//    if (m_orderHistory.empty() || m_orderHistory.back() != string) {
//        std::string newstring = string;
//        addCommandToHistory(newstring);
//    }
//}
//
//void ConsoleFramebufferPrivateImpl::addCommandToHistory(std::string& string)
//{
//    m_orderHistory.push_back(string);
//    m_idx = m_orderHistory.size() - 1;
//}
//
//ConsoleFramebufferPrivateImpl::ConsoleFramebufferPrivateImpl() :m_handleOutput(GetStdHandle(STD_OUTPUT_HANDLE)), m_handleInput(::GetStdHandle(STD_INPUT_HANDLE)), m_idx(0)
//{
//    //First command
//    m_orderHistory.reserve(1);
//    m_orderHistory.resize(1);
//    updateSize();
//}
//
//void ConsoleFramebufferPrivateImpl::resize(int numRows, int numCols)
//{
//    try {
//        m_numRows = numRows;
//        m_numCols = numCols;
//        m_buffer.resize(m_numRows * m_numCols);
//        ::ZeroMemory(&m_buffer[0], m_numRows * m_numCols * sizeof(CHAR_INFO));
//    }
//    catch (const std::bad_alloc& e) {
//        std::cerr << "Memory allocation failed during resize: " << e.what() << std::endl;
//    }
//}
//
//WORD convertForegroundColorToWindows(Color foreground)
//{
//    switch (foreground)
//    {
//    case Red:
//        return FOREGROUND_RED;
//
//    case Green:
//        return FOREGROUND_GREEN;
//
//    case Blue:
//        return FOREGROUND_BLUE;
//
//    case White:
//        return FOREGROUND_RED + FOREGROUND_GREEN + FOREGROUND_BLUE;
//
//    case Cyan:
//        return FOREGROUND_BLUE | FOREGROUND_GREEN;
//
//    case Yellow:
//        return FOREGROUND_RED | FOREGROUND_GREEN;
//
//    case Magenta:
//        return FOREGROUND_RED | FOREGROUND_BLUE;
//
//
//    case Black:
//        return 0;
//
//    default:
//        throw std::invalid_argument("Invalid color value provided.");
//
//    }
//}
//
//WORD convertBackgroundColorToWindows(Color background)
//{
//    return convertForegroundColorToWindows(background) * 16;
//}
//
//WORD convertColorToWindows(Color foreground, Color background)
//{
//    return convertForegroundColorToWindows(foreground) + convertBackgroundColorToWindows(background);
//}
//
//void ConsoleFramebufferPrivateImpl::setCharacter(int row, int col, char car, Color foreground, Color background) {
//    if (row < 0 || row >= m_numRows || col < 0 || col >= m_numCols) {
//        return;
//    }
//    CHAR_INFO& cell = m_buffer[row * m_numCols + col];
//    cell.Char.AsciiChar = car;
//    cell.Attributes = convertColorToWindows(foreground, background);
//}
//
//
//void ConsoleFramebufferPrivateImpl::show()
//{
//    updateSize();
//    printText();
//    COORD dwBufferSize;
//    dwBufferSize.X = m_numCols;
//    dwBufferSize.Y = m_numRows;
//    COORD dwBufferCoord;
//    dwBufferCoord.X = 0;
//    dwBufferCoord.Y = 0;
//
//    SMALL_RECT writeRegion;
//    writeRegion.Top = 0;
//    writeRegion.Left = 0;
//    writeRegion.Right = m_numCols - 1;
//    writeRegion.Bottom = m_numRows - 1;
//
//    BOOL result = WriteConsoleOutput(
//        m_handleOutput,
//        &m_buffer[0],
//        dwBufferSize,
//        dwBufferCoord,
//        &writeRegion
//    );
//
//    if (!result) {
//        std::cerr << "WriteConsoleOutput failed with error code: " << GetLastError() << std::endl;
//    }
//}
//
//int myMin(int a, int b)
//{
//    return (a > b) ? b : a;
//}
//
//void ConsoleFramebufferPrivateImpl::setString(std::string text, Color color, Color backColor)
//{
//    if (text.length() > m_numCols) {
//        text = text.substr(0, m_numCols); // cut if too long
//    }
//    m_toWrite.push_back(text);
//    m_colorToWrite.push_back(color);
//    m_backColorToWrite.push_back(backColor);
//}
//
//void ConsoleFramebufferPrivateImpl::setString(int row, int i)
//{
//    for (int idx = 0; idx < m_toWrite[i].size(); ++idx)
//    {
//        setCharacter(row, idx, m_toWrite[i][idx], m_colorToWrite[i], m_backColorToWrite[i]);
//    }
//}
//
//void ConsoleFramebufferPrivateImpl::eraseEmtpyHistory() {
//    m_orderHistory.erase(
//        std::remove_if(m_orderHistory.begin(), m_orderHistory.end(),
//            [](const std::string& str) { return str.empty(); }),
//        m_orderHistory.end());
//}
//
//void ConsoleFramebufferPrivateImpl::printText()
//{
//    int row = 0;
//    for (auto i = m_toWrite.size() - myMin((m_numRows - 1), m_toWrite.size()); i < m_toWrite.size(); ++i)
//    {
//        setString(row, i);
//        ++row;
//    }
//
//    for (int idx = 0; idx < m_orderHistory[m_idx].size(); ++idx)
//    {
//        setCharacter(row, idx, m_orderHistory[m_idx][idx], White, Black);
//    }
//}
//
//void ConsoleFramebufferPrivateImpl::waitForEnter() {
//    std::cin.get();  // Wait for ENTER
//}
//
//std::string ConsoleFramebufferPrivateImpl::readLine(const std::string& prompt) {
//    setString(prompt, White, Black);
//    std::string input;
//    if (std::cin.peek() == '\n') {  // find if '\n' stay in the buffer
//        std::cin.get();  
//    }
//    std::getline(std::cin, input);
//    return input;
//}
//
//int ConsoleFramebufferPrivateImpl::readInt(const std::string& prompt) {
//    setString(prompt, White, Black);
//    int input;
//    while (true) {
//        if (std::cin >> input) {
//            return input;
//        }
//        else {
//            setString("Invalid. Please enter a number : ", Red, Black);
//            std::cin.clear();
//            while (std::cin.get() != '\n');
//        }
//    }
//}
//
//ConsoleFramebuffer::ConsoleFramebuffer() : m_pimpl(new ConsoleFramebufferPrivateImpl)
//{}
//
//ConsoleFramebuffer::~ConsoleFramebuffer()
//{
//    delete m_pimpl;
//    m_pimpl = nullptr;
//}
//
//void ConsoleFramebuffer::setString(std::string text, Color color, Color backColor)
//{
//    m_pimpl->setString(text, color, backColor);
//}
//
//void ConsoleFramebuffer::show()
//{
//    m_pimpl->show();
//}
//
//void ConsoleFramebuffer::updateConsoleSize()
//{
//    m_pimpl->updateSize();
//}
//
//void ConsoleFramebuffer::processInputEvents()
//{
//    m_pimpl->processInputEvents();
//}
//
//std::string ConsoleFramebuffer::getLastCommand()
//{
//    return m_pimpl->getLastCommand();
//}
//
//int ConsoleFramebuffer::readInt(const std::string& prompt)
//{
//    return m_pimpl->readInt(prompt);
//}
//
//void ConsoleFramebuffer::waitForEnter()
//{
//    m_pimpl->waitForEnter();
//}
//
//std::string ConsoleFramebuffer::readLine(const std::string& prompt)
//{
//    return m_pimpl->readLine(prompt);
//}

#include "Console.h"
#include <Windows.h>
#include <sstream>
class ConsoleFramebufferPrivateImpl
{
public:
    ConsoleFramebufferPrivateImpl();
    void show();
    void display(const std::string& message);
    std::string readLine();
    void setString(std::string text, Color color = White, Color backColor = Black);
    void updateSize();
    void writeConsol();
    void parseCommand(const std::string& command, std::string& action, std::vector<std::string>& args);
    std::string getLastCommand();
private:
    void setCharacter(int row, int col, char car, Color foreground, Color background);
    void copyStringToEnd(std::string string);
    void changeIdxToEnd(std::string& string);
    void resize(int numRows, int numCols);
    void setString(int row, int i);
    void eraseEmtpyHistorique();
    void printText();
private:
    //windows needed member
    HANDLE m_handleoutput;
    HANDLE m_handleinput;
    std::vector<CHAR_INFO> m_buffer;
    SHORT windowWidth;
    SHORT windowHeight;
    int m_numRows;
    int m_numCols;
    int m_idx;
    std::string m_lastCommand;
    std::vector<std::string> m_historique;
    std::vector <std::string> m_toWrite;
    std::vector <Color> m_colorToWrite;
    std::vector <Color> m_backColorToWrite;
};

void ConsoleFramebufferPrivateImpl::display(const std::string& message)
{
    std::cout << message << std::endl;
}

void ConsoleFramebufferPrivateImpl::updateSize()
{
    CONSOLE_SCREEN_BUFFER_INFO sbi;
    BOOL result = GetConsoleScreenBufferInfo(m_handleoutput, &sbi);
    windowWidth = sbi.srWindow.Right - sbi.srWindow.Left + 1;
    windowHeight = sbi.srWindow.Bottom - sbi.srWindow.Top + 1;
    resize(windowHeight, windowWidth);
    //remove empty commands
    eraseEmtpyHistorique();
}



void ConsoleFramebufferPrivateImpl::writeConsol()
{
    INPUT_RECORD inputRecord;
    DWORD events;
    ReadConsoleInput(m_handleinput, &inputRecord, 1, &events);
    if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown)
    {
        wchar_t key = inputRecord.Event.KeyEvent.uChar.UnicodeChar;
        WORD virtualKey = inputRecord.Event.KeyEvent.wVirtualKeyCode;
        if (key == '\r') //if ENTER is pressed
        {
            //Save the last command
            m_lastCommand = m_historique[m_idx];
            // Duplicate the last string
            if (m_idx != m_historique.size() - 1)
                copyStringToEnd(m_historique[m_idx]);
            // Create a new string
            std::string newstring;
            changeIdxToEnd(newstring);
        }
        else if (virtualKey == VK_UP) //if Up is pressed
        {
            if (m_idx == 0)
                return;
            --m_idx;
        }
        else if (virtualKey == VK_DOWN) //if Down is pressed
        {
            if (m_idx == m_historique.size() - 1)
                return;
            ++m_idx;
        }
        else if (key >= 32)
        {
            // Duplicate the last string
            if (m_idx != m_historique.size() - 1)
                copyStringToEnd(m_historique[m_idx]);
            m_historique[m_idx] += key;
        }
        else if (key == '\b' && !m_historique.back().empty())
        {
            // Duplicate the last string
            if (m_idx != m_historique.size() - 1)
                copyStringToEnd(m_historique[m_idx]);
            m_historique[m_idx].pop_back();
        }
    }
}

void ConsoleFramebufferPrivateImpl::parseCommand(const std::string& command, std::string& action, std::vector<std::string>& args) 
{
    std::istringstream iss(command);
    iss >> action;  // Récupère la commande principale
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }
}


std::string ConsoleFramebufferPrivateImpl::getLastCommand()
{
    return m_lastCommand;
}
void ConsoleFramebufferPrivateImpl::copyStringToEnd(std::string string)
{
    std::string newstring = string;
    changeIdxToEnd(newstring);
}

void ConsoleFramebufferPrivateImpl::changeIdxToEnd(std::string& string)
{
    m_historique.push_back(string);
    m_idx = m_historique.size() - 1;
}




ConsoleFramebufferPrivateImpl::ConsoleFramebufferPrivateImpl() :m_handleoutput(GetStdHandle(STD_OUTPUT_HANDLE)), m_handleinput(::GetStdHandle(STD_INPUT_HANDLE)), m_idx(0)
{
    //prepare the first command
    m_historique.reserve(1);
    m_historique.resize(1);
    updateSize();
}


void ConsoleFramebufferPrivateImpl::resize(int numRows, int numCols)
{
    m_numRows = numRows;
    m_numCols = numCols;
    m_buffer.resize(m_numRows * m_numCols);
    ::ZeroMemory(&m_buffer[0], m_numRows * m_numCols * sizeof(CHAR_INFO));
}



WORD convertForegroundColorToWindows(Color foreground)
{
    switch (foreground)
    {
    case Red:
        return FOREGROUND_RED;

    case Green:
        return FOREGROUND_GREEN;

    case Blue:
        return FOREGROUND_BLUE;

    case White:
        return FOREGROUND_RED + FOREGROUND_GREEN + FOREGROUND_BLUE;

    case Black:
        return 0;

    default:
        throw;
    }
}

WORD convertBackgroundColorToWindows(Color background)
{
    return convertForegroundColorToWindows(background) * 16;
}

WORD convertColorToWindows(Color foreground, Color background)
{
    return convertForegroundColorToWindows(foreground) + convertBackgroundColorToWindows(background);
}

void ConsoleFramebufferPrivateImpl::setCharacter(int row, int col, char car, Color foreground, Color background)
{
    CHAR_INFO& cell = m_buffer[row * m_numCols + col];
    cell.Char.AsciiChar = car;
    cell.Attributes = convertColorToWindows(foreground, background);
}

void ConsoleFramebufferPrivateImpl::show()
{
    printText();
    COORD dwBufferSize;
    dwBufferSize.X = m_numCols;
    dwBufferSize.Y = m_numRows;
    COORD dwBufferCoord;
    dwBufferCoord.X = 0;
    dwBufferCoord.Y = 0;

    SMALL_RECT writeRegion;
    writeRegion.Top = 0;
    writeRegion.Left = 0;
    writeRegion.Right = m_numCols - 1;
    writeRegion.Bottom = m_numRows - 1;

    BOOL result = WriteConsoleOutput(
        m_handleoutput,
        &m_buffer[0],
        dwBufferSize,
        dwBufferCoord,
        &writeRegion
    );
}
int myMin(int a, int b)
{
    //returns the minimum between a and b
    return (a > b) ? b : a;
}
void ConsoleFramebufferPrivateImpl::setString(std::string text, Color color, Color backColor)
{
    m_toWrite.push_back(text);
    m_colorToWrite.push_back(color);
    m_backColorToWrite.push_back(backColor);
}
void ConsoleFramebufferPrivateImpl::setString(int row, int i)
{
    for (int idx = 0; idx < m_toWrite[i].size(); ++idx)
    {
        setCharacter(row, idx, m_toWrite[i][idx], m_colorToWrite[i], m_backColorToWrite[i]);
    }
}
void ConsoleFramebufferPrivateImpl::eraseEmtpyHistorique()
{
    for (auto i = 0; i < m_historique.size() - 1; ++i)
    {
        if (m_historique[i] != "")
            continue;
        auto it = std::find(m_historique.begin(), m_historique.end(), m_historique[i]);
        if (it != m_historique.end())
        {
            --m_idx;
            m_historique.erase(it);
            --i;
        }
    }
}
void ConsoleFramebufferPrivateImpl::printText()
{
    int row = 0;
    for (auto i = m_toWrite.size() - myMin((m_numRows - 1), m_toWrite.size()); i < m_toWrite.size(); ++i)
    {
        setString(row, i);
        ++row;
    }
    //write what you write
    for (int idx = 0; idx < m_historique[m_idx].size(); ++idx)
    {
        setCharacter(row, idx, m_historique[m_idx][idx], White, Black);
    }
}

std::string ConsoleFramebufferPrivateImpl::readLine() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

ConsoleFramebuffer::ConsoleFramebuffer() :m_impl(new ConsoleFramebufferPrivateImpl)
{}

ConsoleFramebuffer::~ConsoleFramebuffer()
{
    delete m_impl;
    m_impl = nullptr;
}

void ConsoleFramebuffer::setString(std::string text, Color color, Color backColor)
{
    m_impl->setString(text, color, backColor);
}

void ConsoleFramebuffer::show()
{
    m_impl->show();
}

void ConsoleFramebuffer::updateSize()
{
    m_impl->updateSize();
}

void ConsoleFramebuffer::writeConsol()
{
    m_impl->writeConsol();
}

void ConsoleFramebuffer::parseCommand(const std::string& command, std::string& action, std::vector<std::string>& args)
{
    m_impl->parseCommand(command, action, args);
}

std::string ConsoleFramebuffer::getLastCommand()
{
    return m_impl->getLastCommand();
}

void ConsoleFramebuffer::display(const std::string& message)
{
    m_impl->display(message);
}

std::string ConsoleFramebuffer::readLine()
{
    return m_impl->readLine();
}