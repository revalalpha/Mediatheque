#include "RunningConsole.h"

Database::Database()
    : m_console(new ConsoleFramebuffer()),
    m_library(new LibrarySystem()),
    m_lastCommand("") {}

Database::~Database() {
    delete m_console;
    delete m_library;
}

void Database::addString(const std::string& str) {
    if (isNewCommand(str)) {
        m_lastCommand = str;
    }
}

bool Database::isNewCommand(const std::string& str) const {
    return str != m_lastCommand;
}

void Database::Exe() {
    m_console->displayLine(
        "   ------------------------------------------------\n"
        "   ------> Welcome to the god Media Library <------\n"
        "   ------------------------------------------------\n\n", Yellow);
    m_console->displayLine(
        "Write the command: 'help' to see a list of all commands\n",
        Magenta);

    std::string input;

    while (true) {
        m_console->display("> ", Cyan);
        input = m_console->readLine();

        if (input == "exit" || input == "quit") {
            break;
        }

        addString(input);

        try {
            std::istringstream stream(input);
            std::string command;
            stream >> command;

            if (command == "help") {
                m_console->displayLine(
                    "Available commands:\n"
                    "  addClient <name> <firstname> <age> <address> <phoneNumber> <email>\n"
                    "      Add a new client to the library system.\n"
                    "  listClient\n"
                    "      List all registered clients.\n"
                    "  removeClient <name> [<firstname> | <email>]\n"
                    "      Remove a client by name, name and firstname, or email.\n"
                    "  addMedia <type> <title> [<args>]\n"
                    "      Add a new media to the library. Supported types: book, film, game.\n"
                    "      For books: <title> <ISBN>\n"
                    "      For films: <title> <support> <ageLimit>\n"
                    "      For games: <title> <studio> <genre> <PEGI>\n"
                    "  listMedia [<state>]\n"
                    "      List all media, optionally filtered by state ('available' or 'borrowed').\n"
                    "  stateMedia <type> <title>\n"
                    "      Show the state ('Available' or 'Borrowed') of a specific media.\n"
                    "  rent <clientName> <type> <title>\n"
                    "      Rent a media to a client.\n"
                    "  returnMedia <type> <title>\n"
                    "      Return a borrowed media.\n"
                    "  showMedia <clientName> [<firstname> | <email>]\n"
                    "      Show media borrowed by a specific client.\n"
                    "  exit | quit\n"
                    "      Exit the application.\n", Blue);
            }
            else if (command == "addClient") {
                std::string name, firstname, address, phoneNumber, email;
                int age;

                stream >> name >> firstname >> age >> address >> phoneNumber >> email;
                m_library->addClient(name, firstname, age, address, phoneNumber, email);
                m_console->displayLine("Client added successfully.\n", Green);
            }
            else if (command == "listClient") {
                m_console->displayLine(m_library->listClients() + "\n", White);
            }
            else if (command == "removeClient") {
                std::string name, firstname, email;
                stream >> name;

                if (stream >> firstname) {
                    m_library->removeClientByNameAndFirstName(name, firstname);
                }
                else if (stream >> email) {
                    m_library->removeClientByMail(email);
                }
                else {
                    m_library->removeClientByName(name);
                }

                m_console->displayLine("Client removed successfully.\n", Green);
            }
            else if (command == "addMedia") {
                std::string type, title;
                stream >> type >> title;

                if (type.empty() || title.empty()) {
                    m_console->displayLine("Error: Media type and title are required.\n", Red);
                    continue;
                }

                if (type == "book") {
                    std::string ISBN;
                    stream >> ISBN;
                    if (ISBN.empty()) {
                        m_console->display("Error: ISBN is required for books.\n", Red);
                        continue;
                    }
                    m_library->addBookMedia(title, ISBN);
                }
                else if (type == "film") {
                    std::string support;
                    int ageLimit = 0;
                    stream >> support >> ageLimit;
                    if (support.empty() || ageLimit <= 0) {
                        m_console->displayLine("Error: Support and age limit are required for films.\n", Red);
                        continue;
                    }
                    m_library->addFilmMedia(title, support, ageLimit);
                }
                else if (type == "game") {
                    std::string studio, genre;
                    int PEGI = 0;
                    stream >> studio >> genre >> PEGI;
                    if (studio.empty() || genre.empty() || PEGI <= 0) {
                        m_console->displayLine("Error: Studio, genre, and PEGI rating are required for games.\n", Red);
                        continue;
                    }
                    m_library->addGameMedia(title, studio, genre, PEGI);
                }
                else {
                    m_console->displayLine("Error: Unsupported media type.\n", Red);
                    continue;
                }

                m_console->displayLine("Media added successfully.\n", Green);
            }

            else if (command == "listMedia") {
                std::string state;
                if (stream >> state) {
                    m_console->displayLine(m_library->listMediaByState(state) + "\n", White);
                }
                else {
                    m_console->displayLine(m_library->listMedia() + "\n", White);
                }
            }
            else if (command == "stateMedia") {
                std::string type, name;
                stream >> type >> name;
                m_console->displayLine(m_library->getMediaState(type, name) + "\n", White);
            }
            else if (command == "rent") {
                std::string clientName, type, name;
                stream >> clientName >> type >> name;
                m_library->rentMedia(clientName, type, name);
                m_console->displayLine("Media rented successfully.\n", Green);
            }
            else if (command == "returnMedia") {
                std::string type, name;
                stream >> type >> name;
                m_library->returnMedia(type, name);
                m_console->displayLine("Media returned successfully.\n", Green);
            }
            else if (command == "showMedia") {
                std::string clientName, firstName, email;
                stream >> clientName;

                if (stream >> firstName) {
                    m_console->displayLine(m_library->showMediaBorrowedByClientWithNameAndFirstName(clientName, firstName) + "\n", White);
                }
                else if (stream >> email) {
                    m_console->displayLine(m_library->showMediaBorrowedByClientWithMail(email) + "\n", White);
                }
            }
            else {
                m_console->displayLine("Unknown command. Type 'help' to see the list of available commands.\n", Red);
            }
        }
        catch (const std::exception& e) {
            m_console->displayLine(std::string("Error: ") + e.what() + "\n", Red);
        }
    }
}
