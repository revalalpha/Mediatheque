#include "Console.h"
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    ConsoleFramebuffer framebuffer;

    std::vector<std::string> menuOptions = {
        "1. Add a client",
        "2. Delete a client",
        "3. List all clients",
        "4. Add a media",
        "5. Leave"
    };

    int selectedIndex = 0;
    bool isRunning = true;

    while (isRunning) {
        framebuffer.displayMenu(menuOptions, selectedIndex);

        char key;
        std::cin >> key;
        switch (key) {
        case 'w': 
            selectedIndex = (selectedIndex > 0) ? selectedIndex - 1 : menuOptions.size() - 1;
            break;
        case 's': 
            selectedIndex = (selectedIndex < menuOptions.size() - 1) ? selectedIndex + 1 : 0;
            break;
        case '\n': 
            if (selectedIndex == menuOptions.size() - 1) { 
                isRunning = false;
            }
            std::cout << "Selected option : " << menuOptions[selectedIndex] << "\n";
            break;
        default:
            break;
        }
    }

    return 0;
}
