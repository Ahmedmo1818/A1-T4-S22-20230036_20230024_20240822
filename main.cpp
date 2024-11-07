#include <iostream>
#include "Machine.h"
using namespace std;

void displayMenu()
{
    std::cout << "\n=========== Vole Machine simulator ===========\n";
    std::cout << "1. Load Instructions File\n";
    std::cout << "2. Print Register and Memory Values\n";
    std::cout << "3. Exit\n";
    std::cout << "============================\n";
    std::cout << "Enter your choice: ";
}

int main()
{

    int memoryIndex;
    std::cout << "Enter the starting memory index: ";
    std::cin >> memoryIndex;
    Machine machine(memoryIndex);
    bool isFileLoaded = false;
    std::string filename;

    while (true)
    {
        displayMenu();

        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        { // Load Instructions File
            std::cout << "Enter the filename to load instructions: ";
            std::cin >> filename;
            std::fstream file(filename);
            if (file.is_open())
            {
                std::cout << "File Loaded Successfuly";
            }
            isFileLoaded = true;
            break;
        }

        case 2:
        { // Print Register and Memory Values
            if (isFileLoaded)
            {
                machine.loadInstruct(filename);
                machine.Display_Registers();
                machine.Display_Memory();
            }
            else
            {
                std::cout << "Please load a file first.\n";
            }
            break;
        }

        case 3:
        { // Exit
            std::cout << "Exiting program...\n";
            return 0;
        }

        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}
