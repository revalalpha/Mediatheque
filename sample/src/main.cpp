#include "Console.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int main(int argc, char** argv) 
{
    try 
    {
        ConsoleFramebuffer console;

        console.updateConsoleSize();

        console.setString("Welcome to the interactive console of the mediatheque !", White, Black);
        console.show();

        bool running = true;
        while (running) 
        {
            console.processInputEvents();
            std::string command = console.getLastCommand();

            if (!command.empty()) 
            {
                if (command == "exit") 
                {
                    console.setString("By !", Green, Black);
                    console.show();
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    running = false;
                }
                else 
                    console.setString("Received command : " + command, White, Black);
                console.show();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
    
}

