#include "RunningConsole.h"

#include <iostream>
#include <stdexcept>
#include <sstream>

Database::Database()
    : m_console(new ConsoleFramebuffer()),
    m_library(new LibrarySystem()),
    m_lastCommand("") {}

Database::~Database() {
    delete m_console;
    delete m_library;
}

void Database::addString(const std::string& str) {
    // Ajoute la commande dans l'historique si elle est différente de la précédente.
    if (isNewCommand(str)) {
        m_lastCommand = str;
    }
}

bool Database::isNewCommand(const std::string& str) const {
    return str != m_lastCommand;
}

void Database::Exe() {
    std::string input;

    while (true) {
        // Affiche le prompt.
        m_console->display("> ");

        // Récupère l'entrée utilisateur.
        input = m_console->readLine();

        if (input == "exit" || input == "quit") {
            break; // Quitte le programme si la commande est "exit".
        }

        // Ajoute la commande à l'historique.
        addString(input);

        // Interprète et exécute la commande.
        try {
            std::istringstream stream(input);
            std::string command;
            stream >> command;

            if (command == "addClient") {
                std::string name, firstname, address, phoneNumber, email;
                int age;

                stream >> name >> firstname >> age >> address >> phoneNumber >> email;
                m_library->addClient(name, firstname, age, address, phoneNumber, email);
                m_console->display("Client added successfully.\n");
            }
            else if (command == "listClient") {
                m_console->display(m_library->listClients() + "\n");
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
                m_console->display("Client removed successfully.\n");
            }
            else if (command == "addMedia") {
                std::string type, title, ISBN, support, studio, PEGI, genre;
                int ageLimit = 0;

                stream >> type >> title;
                if (type == "book") {
                    stream >> ISBN;
                    m_library->addBookMedia(type, title, ISBN);
                }
                else if (type == "film") {
                    stream >> support >> ageLimit; // Support, Age Limit
                    m_library->addFilmMedia(type, title, support, ageLimit);
                }
                else if (type == "game") {
                    stream >> studio >> genre >> PEGI; // Studio, Genre, PEGI
                    m_library->addGameMedia(type, title, studio, PEGI, genre);
                }
                m_console->display("Media added successfully.\n");
            }
            else if (command == "listMedia") {
                std::string state;
                if (stream >> state) {
                    m_console->display(m_library->listMediaByState(state) + "\n");
                }
                else {
                    m_console->display(m_library->listMedia() + "\n");
                }
            }
            else if (command == "stateMedia") {
                std::string type, name;
                stream >> type >> name;
                m_console->display(m_library->getMediaState(type, name) + "\n");
            }
            else if (command == "rent") {
                std::string clientName, type, name;
                stream >> clientName >> type >> name;
                m_library->rentMedia(clientName, type, name);
                m_console->display("Media rented successfully.\n");
            }
            else if (command == "returnMedia") {
                std::string type, name;
                stream >> type >> name;
                m_library->returnMedia(type, name);
                m_console->display("Media returned successfully.\n");
            }
            else if (command == "showMedia") {
                std::string clientName, firstName, email;
                stream >> clientName;
                if (stream >> firstName) {
                    m_console->display(m_library->showMediaBorrowedByClientWithNameAndFirstName(clientName, firstName) + "\n");
                }
                else if (stream >> email) {
                    m_console->display(m_library->showMediaBorrowedByClientWithMail(email) + "\n");
                }
            }
            else {
                m_console->display("Unknown command.\n");
            }
        }
        catch (const std::exception& e) {
            m_console->display(std::string("Error: ") + e.what() + "\n");
        }
    }
}
