#include "Console.h"
#include <Windows.h>
#include <sstream>
class ConsoleFramebufferPrivateImpl
{
public:
    ConsoleFramebufferPrivateImpl();
    void show();
    void display(const std::string& text, Color color);
    void displayLine(const std::string& text, Color color);
    std::string readLine();
    void setString(std::string text, Color color = White, Color backColor = Black);
    void updateSize();
    void writeConsol();
    void parseCommand(const std::string& command, std::string& action, std::vector<std::string>& args);
    std::string getLastCommand();
    WORD convertForegroundColorToWindows(Color foreground);
    WORD convertBackgroundColorToWindows(Color background);
    WORD convertColorToWindows(Color foreground, Color background);
private:
    void setCharacter(int row, int col, char car, Color foreground, Color background);
    void copyStringToEnd(std::string string);
    void changeIdxToEnd(std::string& string);
    void resize(int numRows, int numCols);
    void setString(int row, int i);
    void eraseEmtpyHistory();
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
    std::vector<std::string> m_history;
    std::vector <std::string> m_toWrite;
    std::vector <Color> m_colorToWrite;
    std::vector <Color> m_backColorToWrite;
};

void ConsoleFramebufferPrivateImpl::display(const std::string& text, Color color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE)
        throw std::runtime_error("Cannot get console handle");

    WORD attributes = convertColorToWindows(color, Color::Black);

    SetConsoleTextAttribute(hConsole, attributes);

    DWORD written = 0;
    WriteConsole(hConsole, text.c_str(), text.size(), &written, nullptr);

    SetConsoleTextAttribute(hConsole, convertColorToWindows(Color::White, Color::Black));
}

void ConsoleFramebufferPrivateImpl::displayLine(const std::string& text, Color color)
{
    display(text + "\n", color);
}

void ConsoleFramebufferPrivateImpl::updateSize()
{
    CONSOLE_SCREEN_BUFFER_INFO sbi;
    BOOL result = GetConsoleScreenBufferInfo(m_handleoutput, &sbi);
    windowWidth = sbi.srWindow.Right - sbi.srWindow.Left + 1;
    windowHeight = sbi.srWindow.Bottom - sbi.srWindow.Top + 1;
    resize(windowHeight, windowWidth);
    //remove empty commands
    eraseEmtpyHistory();
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
            m_lastCommand = m_history[m_idx];
            // Duplicate the last string
            if (m_idx != m_history.size() - 1)
                copyStringToEnd(m_history[m_idx]);
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
            if (m_idx == m_history.size() - 1)
                return;
            ++m_idx;
        }
        else if (key >= 32)
        {
            // Duplicate the last string
            if (m_idx != m_history.size() - 1)
                copyStringToEnd(m_history[m_idx]);
            m_history[m_idx] += key;
        }
        else if (key == '\b' && !m_history.back().empty())
        {
            // Duplicate the last string
            if (m_idx != m_history.size() - 1)
                copyStringToEnd(m_history[m_idx]);
            m_history[m_idx].pop_back();
        }
    }
}

void ConsoleFramebufferPrivateImpl::parseCommand(const std::string& command, std::string& action, std::vector<std::string>& args) 
{
    std::istringstream iss(command);
    iss >> action; 
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
    m_history.push_back(string);
    m_idx = m_history.size() - 1;
}




ConsoleFramebufferPrivateImpl::ConsoleFramebufferPrivateImpl() :m_handleoutput(GetStdHandle(STD_OUTPUT_HANDLE)), m_handleinput(::GetStdHandle(STD_INPUT_HANDLE)), m_idx(0)
{
    //prepare the first command
    m_history.reserve(1);
    m_history.resize(1);
    updateSize();
}


void ConsoleFramebufferPrivateImpl::resize(int numRows, int numCols)
{
    m_numRows = numRows;
    m_numCols = numCols;
    m_buffer.resize(m_numRows * m_numCols);
    ::ZeroMemory(&m_buffer[0], m_numRows * m_numCols * sizeof(CHAR_INFO));
}



WORD ConsoleFramebufferPrivateImpl::convertForegroundColorToWindows(Color foreground)
{
    switch (foreground)
    {
    case Red:
        return FOREGROUND_RED;

    case Green:
        return FOREGROUND_GREEN;

    case Blue:
        return FOREGROUND_BLUE;

    case Yellow:
        return FOREGROUND_RED + FOREGROUND_GREEN;

    case Cyan:
        return FOREGROUND_GREEN + FOREGROUND_BLUE;

    case Magenta:
        return FOREGROUND_RED + FOREGROUND_BLUE;

    case White:
        return FOREGROUND_RED + FOREGROUND_GREEN + FOREGROUND_BLUE;

    case Black:
        return 0;

    default:
        throw;
    }
}

WORD ConsoleFramebufferPrivateImpl::convertBackgroundColorToWindows(Color background)
{
    return convertForegroundColorToWindows(background) * 16;
}

WORD ConsoleFramebufferPrivateImpl::convertColorToWindows(Color foreground, Color background)
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
void ConsoleFramebufferPrivateImpl::eraseEmtpyHistory()
{
    for (auto i = 0; i < m_history.size() - 1; ++i)
    {
        if (m_history[i] != "")
            continue;
        auto it = std::find(m_history.begin(), m_history.end(), m_history[i]);
        if (it != m_history.end())
        {
            --m_idx;
            m_history.erase(it);
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
    for (int idx = 0; idx < m_history[m_idx].size(); ++idx)
    {
        setCharacter(row, idx, m_history[m_idx][idx], White, Black);
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

void ConsoleFramebuffer::display(const std::string& text, Color color)
{
    m_impl->display(text, color);
}

void ConsoleFramebuffer::displayLine(const std::string& text, Color color)
{
    m_impl->displayLine(text, color);
}

std::string ConsoleFramebuffer::readLine()
{
    return m_impl->readLine();
}