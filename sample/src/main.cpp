//#include <iostream>
//#include "LibrarySystem.h"
//
//int main() {
//    LibrarySystem librarySystem;
//
//    while (true) {
//        std::cout << "Library System Menu:\n";
//        std::cout << "1. Add client\n";
//        std::cout << "2. Remove client\n";
//        std::cout << "3. List clients\n";
//        std::cout << "4. Add media (book, film, game)\n";
//        std::cout << "5. Remove media\n";
//        std::cout << "6. Rent media\n";
//        std::cout << "7. Return media\n";
//        std::cout << "8. List all media\n";
//        std::cout << "9. List borrowed media by client\n";
//        std::cout << "10. Show media state\n";
//        std::cout << "0. Exit\n";
//        std::cout << "Enter your choice: ";
//
//        int choice;
//        std::cin >> choice;
//
//        // Vérifier si la saisie est valide
//        if (std::cin.fail()) {
//            std::cin.clear();  // Clear the error flag
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
//            std::cout << "Invalid choice. Please enter a number between 0 and 10.\n";
//            continue;
//        }
//
//        // Consommer le reste de la ligne (nettoyer le buffer)
//        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//        if (choice == 0) {
//            break;  // Exit the loop and end the program
//        }
//
//        switch (choice) {
//        case 1: {
//            std::string name;
//            int age;
//            std::cout << "Enter client's name: ";
//            std::getline(std::cin, name);
//            std::cout << "Enter client's age: ";
//            std::cin >> age;
//            std::cin.ignore();  // Clear the input buffer
//            librarySystem.addClient(name, age);
//            break;
//        }
//        case 2: {
//            std::string name;
//            int age;
//            std::cout << "Enter client's name to remove: ";
//            std::getline(std::cin, name);
//            std::cout << "Enter client's age: ";
//            std::cin >> age;
//            std::cin.ignore();  // Clear the input buffer
//            librarySystem.removeClient(name, age);
//            break;
//        }
//        case 3:
//            std::cout << librarySystem.listClients() << std::endl;
//            break;
//        case 4: {
//            std::string mediaType;
//            std::cout << "Enter media type (book, film, game): ";
//            std::getline(std::cin, mediaType);
//            std::vector<std::string> args;
//            if (mediaType == "book") {
//                std::string title, isbn;
//                std::cout << "Enter book title: ";
//                std::getline(std::cin, title);
//                std::cout << "Enter ISBN: ";
//                std::getline(std::cin, isbn);
//                args.push_back(title);
//                args.push_back(isbn);
//            }
//            else if (mediaType == "film") {
//                std::string title, format;
//                int ageLimit;
//                std::cout << "Enter film title: ";
//                std::getline(std::cin, title);
//                std::cout << "Enter film format: ";
//                std::getline(std::cin, format);
//                std::cout << "Enter age limit: ";
//                std::cin >> ageLimit;
//                std::cin.ignore();  // Clear the input buffer
//                args.push_back(title);
//                args.push_back(format);
//                args.push_back(std::to_string(ageLimit));
//            }
//            else if (mediaType == "game") {
//                std::string title, studio, genre;
//                int pegi;
//                std::cout << "Enter game title: ";
//                std::getline(std::cin, title);
//                std::cout << "Enter studio: ";
//                std::getline(std::cin, studio);
//                std::cout << "Enter genre: ";
//                std::getline(std::cin, genre);
//                std::cout << "Enter PEGI rating: ";
//                std::cin >> pegi;
//                std::cin.ignore();  // Clear the input buffer
//                args.push_back(title);
//                args.push_back(studio);
//                args.push_back(genre);
//                args.push_back(std::to_string(pegi));
//            }
//            librarySystem.addMedia(mediaType, args);
//            break;
//        }
//        case 5: {
//            std::string mediaType, title;
//            std::cout << "Enter media type (book, film, game): ";
//            std::getline(std::cin, mediaType);
//            std::cout << "Enter media title: ";
//            std::getline(std::cin, title);
//            librarySystem.removeMedia(mediaType, title);
//            break;
//        }
//        case 6: {
//            std::string clientName, mediaType, title;
//            std::cout << "Enter client's name: ";
//            std::getline(std::cin, clientName);
//            std::cout << "Enter media type (book, film, game): ";
//            std::getline(std::cin, mediaType);
//            std::cout << "Enter media title: ";
//            std::getline(std::cin, title);
//            try {
//                librarySystem.rentMedia(clientName, mediaType, title);
//            }
//            catch (const std::exception& e) {
//                std::cerr << e.what() << std::endl;
//            }
//            break;
//        }
//        case 7: {
//            std::string mediaType, title;
//            std::cout << "Enter media type (book, film, game): ";
//            std::getline(std::cin, mediaType);
//            std::cout << "Enter media title: ";
//            std::getline(std::cin, title);
//            try {
//                librarySystem.returnMedia(mediaType, title);
//            }
//            catch (const std::exception& e) {
//                std::cerr << e.what() << std::endl;
//            }
//            break;
//        }
//        case 8:
//            std::cout << librarySystem.listMedia() << std::endl;
//            break;
//        case 9: {
//            std::string clientName;
//            std::cout << "Enter client's name: ";
//            std::getline(std::cin, clientName);
//            std::cout << librarySystem.showMediaBorrowedByClient(clientName) << std::endl;
//            break;
//        }
//        case 10: {
//            std::string mediaType, title;
//            std::cout << "Enter media type (book, film, game): ";
//            std::getline(std::cin, mediaType);
//            std::cout << "Enter media title: ";
//            std::getline(std::cin, title);
//            try {
//                std::cout << librarySystem.getMediaState(mediaType, title) << std::endl;
//            }
//            catch (const std::exception& e) {
//                std::cerr << e.what() << std::endl;
//            }
//            break;
//        }
//        default:
//            std::cout << "Invalid choice. Please try again.\n";
//        }
//    }
//
//    return 0;
//}

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "LibrarySystem.h"  

using namespace std;

int main(int argc, char** argv) {
    LibrarySystem librarySystem;
    string input;

    while (true) {
        cout << "\nLibrary System Menu:\n";
        cout << "1. Add client\n";
        cout << "2. Remove client\n";
        cout << "3. List clients\n";
        cout << "4. Add media (book, film, game)\n";
        cout << "5. Remove media\n";
        cout << "6. List all media\n";
        cout << "7. List media by state\n";
        cout << "8. Show media state\n";
        cout << "9. Who borrowed a media\n";
        cout << "10. Rent media\n";
        cout << "11. Return media\n";
        cout << "12. Show media borrowed by client\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        getline(cin, input);

        if (input == "1") {  // Add client
            string name, firstname, address, phoneNumber, mail;
            int age;
            cout << "Enter client details (name, firstname, age, address, phoneNumber, mail):\n";
            getline(cin, name);
            getline(cin, firstname);
            cin >> age;
            cin.ignore();  // Pour ignorer la nouvelle ligne après l'âge
            getline(cin, address);
            getline(cin, phoneNumber);
            getline(cin, mail);

            librarySystem.addClient(name, firstname, age, address, phoneNumber, mail);
            cout << "Client added successfully.\n";
        }
        else if (input == "2") {  // Remove client
            string clientName, firstname, mail;
            cout << "Enter the name of the client to remove:\n";
            getline(cin, clientName);

            if (clientName.empty()) {
                cout << "Enter the firstname of the client to remove:\n";
                getline(cin, firstname);
                librarySystem.removeClientByNameAndFirstName(clientName, firstname);
            }
            else {
                cout << "Enter the mail of the client to remove:\n";
                getline(cin, mail);
                librarySystem.removeClientByMail(mail);
            }
            cout << "Client removed successfully.\n";
        }
        else if (input == "3") {  // List clients
            librarySystem.listClients();
        }
        else if (input == "4") {  // Add media
            string mediaType;
            cout << "Enter media type (book, film, game): ";
            getline(cin, mediaType);

            if (mediaType == "book") {
                string title, ISBN;
                cout << "Enter book details (title, ISBN):\n";
                getline(cin, title);
                getline(cin, ISBN);
                librarySystem.addMedia("book", title, ISBN);
            }
            else if (mediaType == "film") {
                string title, support, ageLimit;
                cout << "Enter film details (title, support (blu ray/DVD), age limit):\n";
                getline(cin, title);
                getline(cin, support);
                getline(cin, ageLimit);
                librarySystem.addMedia("film", title, support, ageLimit);
            }
            else if (mediaType == "game") {
                string title, studio, PEGI, genre;
                cout << "Enter game details (title, studio, PEGI, genre):\n";
                getline(cin, title);
                getline(cin, studio);
                getline(cin, PEGI);
                getline(cin, genre);
                librarySystem.addMedia("game", title, studio, PEGI, genre);
            }
            cout << "Media added successfully.\n";
        }
        else if (input == "5") {  // Remove media
            std::string mediaType, title;
            cout << "Enter media type (book, film, game): ";
            getline(cin, mediaType);
            cout << "Enter media title:\n";
            getline(cin, title);
            librarySystem.removeMedia(mediaType, title);
            cout << "Media removed successfully.\n";
        }
        else if (input == "6") {  // List all media
            librarySystem.listMedia();
        }
        else if (input == "7") {  // List media by state (available/borrowed)
            string state;
            cout << "Enter media state (available/borrowed):\n";
            getline(cin, state);
            librarySystem.listMediaByState(state);
        }
        else if (input == "8") {  // Show media state
            string mediaType, name;
            cout << "Enter media type (book, film, game):\n";
            getline(cin, mediaType);
            cout << "Enter media name:\n";
            getline(cin, name);
            librarySystem.getMediaState(mediaType, name);
        }
        else if (input == "9") {  // Who borrowed a media
            string mediaType, name;
            cout << "Enter media type (book, film, game):\n";
            getline(cin, mediaType);
            cout << "Enter media name:\n";
            getline(cin, name);
            librarySystem.getWhoBorrowedMedia(mediaType, name);
        }
        else if (input == "10") {  // Rent media
            string clientName, mediaType, name;
            cout << "Enter client name:\n";
            getline(cin, clientName);
            cout << "Enter media type (book, film, game):\n";
            getline(cin, mediaType);
            cout << "Enter media name:\n";
            getline(cin, name);
            librarySystem.rentMedia(clientName, mediaType, name);
        }
        else if (input == "11") {  // Return media
            string mediaType, name;
            cout << "Enter media type (book, film, game):\n";
            getline(cin, mediaType);
            cout << "Enter media name:\n";
            getline(cin, name);
            librarySystem.returnMedia(mediaType, name);
        }
        else if (input == "12") {  // Show media borrowed by client
            string clientName, firstClientName, mail;
            cout << "Enter client name:\n";
            getline(cin, clientName);

            if (clientName.empty()) {
                cout << "Enter the first client name:\n";
                getline(cin, firstClientName);
                librarySystem.showMediaBorrowedByClientWithNameAndFirstName(clientName, firstClientName);
            }
            else {
                cout << "Enter client mail:\n";
                getline(cin, mail);
                librarySystem.showMediaBorrowedByClientWithMail(mail);
            }
        }
        else if (input == "0") {
            break;  // Exit
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
