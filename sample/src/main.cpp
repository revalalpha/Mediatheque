#include "LibrarySystem.h"
#include "Console.h"

#include <iostream>
#include <sstream>

int main(int argc, char** argv)
{
    LibrarySystem library;
    ConsoleFramebuffer console;  // Crée une instance de ConsoleFramebuffer
    bool isRunning = true;

    while (isRunning)
    {
        console.setString("\nChoix : ", White, Black);
        // Nettoyer l'écran pour une interface propre
        console.setString("", Black, Black);  // Efface l'écran en définissant la couleur de fond noire

        // Afficher le menu avec des couleurs
        console.setString("\n=== Gestion de la Médiathèque ===\n", Blue, Black);

        std::vector<std::string> menuOptions = {
            "Créer un compte client",
            "Supprimer un compte client",
            "Voir la liste des clients",
            "Ajouter un média",
            "Supprimer un média",
            "Voir la liste des médias",
            "Voir l'état d'un média",
            "Savoir qui a emprunté un média",
            "Emprunter un média",
            "Retourner un média",
            "Voir les médias empruntés par un client",
            "Quitter"
        };

        // Affichage du menu
        for (size_t i = 0; i < menuOptions.size(); ++i)
        {
            console.setString(std::to_string(i + 1) + ". " + menuOptions[i] + "\n", White, Black);
        }

        console.setString("\nChoix : ", White, Black);

        // Lire l'entrée de l'utilisateur
        int choice;
        std::cin >> choice;

        // Traitement des choix avec gestion des exceptions
        try
        {
            switch (choice)
            {
            case 1:
            {
                std::string name = console.readLine("Client name : ");
                int age = console.readInt("Client age : ");
                library.addClient(name, age);
                console.setString("Client account successfully created.\n", Green, Black);
                break;
            }
            case 2:
            {
                std::string name = console.readLine("Client name to delete : ");
                int age = console.readInt("Client age to delete : ");
                library.removeClient(name, age);
                console.setString("Client account successfully deleted.\n", Green, Black);
                break;
            }
            case 3:
            {
                console.setString("Client list :\n", Cyan, Black);
                console.setString(library.listClients(), White, Black);
                break;
            }
            case 4:
            {
                std::string type = console.readLine("Media type (book, film, game) : ");
                console.setString("Arguments separated by spaces: ", White, Black);
                std::string argsLine = console.readLine();
                std::istringstream iss(argsLine);
                std::vector<std::string> args((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
                library.addMedia(type, args);
                console.setString("Média ajouté avec succès.\n", Green, Black);
                break;
            }

            case 5:
            {
                std::string type = console.readLine("Media type : ");
                std::string title = console.readLine("Media title : ");
                library.removeMedia(type, title);
                console.setString("Media successfully deleted.\n", Green, Black);
                break;
            }
            case 6:
            {
                console.setString("Liste des médias :\n", Cyan, Black);
                console.setString(library.listMedia(), White, Black);
                break;
            }
            case 7:
            {
                std::string type = console.readLine("Media type : ");
                std::string title = console.readLine("Media title : ");
                console.setString("Media state : " + library.getMediaState(type, title) + "\n", Cyan, Black);
                break;
            }
            case 8:
            {
                std::string type = console.readLine("Media type : ");
                std::string title = console.readLine("Media title : ");
                console.setString("Borrowed by : " + library.getWhoBorrowedMedia(type, title) + "\n", Cyan, Black);
                break;
            }
            case 9:
            {
                std::string clientName = console.readLine("Client name : ");
                std::string type = console.readLine("Media type : ");
                std::string title = console.readLine("Media title : ");
                library.rentMedia(clientName, type, title);
                console.setString("Media successfully borrowed.\n", Green, Black);
                break;
            }
            case 10:
            {
                std::string type = console.readLine("Media type : ");
                std::string title = console.readLine("Media title : ");
                library.returnMedia(type, title);
                console.setString("Media successfully returned.\n", Green, Black);
                break;
            }
            case 11:
            {
                std::string clientName = console.readLine("Client name : ");
                console.setString("Media borrowed by " + clientName + " :\n", Cyan, Black);
                console.setString(library.showMediaBorrowedByClient(clientName), White, Black);
                break;
            }
            case 0:
            {
                isRunning = false;
                break;
            }
            default:
                console.setString("Invalid option. Please retry.\n", Red, Black);
            }
        }
        catch (const std::exception& e)
        {
            console.setString("Error : " + std::string(e.what()) + "\n", Red, Black);
        }

        console.setString("\nPress ENTER to continue...", White, Black);
        console.waitForEnter();
    }

    console.setString("Thank you for using the media library. See you soon!\n", Yellow, Black);

    return 0;
}