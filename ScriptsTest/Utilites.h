#pragma once
#include <consoleapi2.h>
#include "Weapons.h"


class Utilities
{

public:
    //Clears the console
    static void clear() {
        COORD topLeft = { 0, 0 };
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO screen;
        DWORD written;

        GetConsoleScreenBufferInfo(console, &screen);
        FillConsoleOutputCharacterA(
            console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        FillConsoleOutputAttribute(
            console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
            screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        SetConsoleCursorPosition(console, topLeft);
    }
};
class names
{
    //Returns names of items as strings
    static std::string weaponName()
    {
        switch (selectedWeapon)
        {
        case 0:
            return "None";
        case 1:
            return "Assault-Rifle";
        case 2:
            return "LR300";
        case 3:
            return "Semi-Automatic-Rifle";
        case 4:
            return "Thompson";
        case 5:
            return "Custom-SMG";
        case 6:
            return "MP5";
        case 7:
            return "M249";
        case 8:
            return "M39";
        case 9:
            return "M92";
        case 10:
            return "Python";
        case 11:
            return "Revolver";
        case 12:
            return "Semi-Auto-Pistol";
        case 13:
            return "Nail-Gun";

            default:
                return "None";
        }
    }
    static std::string scopeName()
    {
        switch (selectedScope)
        {
        case 0:
            return "None";
        case 1:
            return "Holographic";
        case 2:
            return "Home-Made";
        case 3:
            return "x8";
        case 4:
            return "x16";
        default:
            return "None";
        }
    }
    static std::string attachmentName( )
    {
        switch (selectedAttachment)
        {
        case 0:
            return "None";
        case 1:
            return "Muzzle-Boost";
        case 2:
            return "Muzzle-Brake";
        case 3:
            return "Silencer";
            default:
                return "None";
        }
    }

public:
    //Prints the menu
    static void mainText()
    {
        Utilities::clear();
        std::cout << "Welcome to COMBO-X\n";
        std::cout << "------------------\n";
        std::cout << "AK-47    = NUMPAD_0\n";
        std::cout << "LR-300   = 2\n";
        std::cout << "SAR      = 3\n";
        std::cout << "THOMPSON = 4\n";
        std::cout << "-------------------" << std::endl;
        std::cout << "Activated: " << scriptActive << std::endl;
        std::cout << "-------------------" << std::endl;

        std::cout << "LEFT ARROW / RIGHT ARROW - Change Attachment" <<std::endl;
        std::cout << "UP ARROW / DOWN ARROW - Change Scope" << std::endl;
        std::cout << "-------------------" << std::endl;

        std::cout << "Weapon: " << weaponName() << std::endl;
        std::cout << "Scope: " << scopeName() << std::endl;
        std::cout << "Attachment: " << attachmentName() << std::endl;

    }
};
    class Timer
    {
    public:
        /**
         * Used to initialize the class - the time of instantiation is stored here.
         */
        Timer()
        {
            // Store the time at which this timer was instantiated.
            QueryPerformanceCounter(&starting_time);

        }

        /**
         * Used to get the time elapsed (in milliseconds) since the timer was instantiated.
         */
        float Elapsed()
        {
            // Will contain the current performance counter value
            LARGE_INTEGER current_time;

            // Used for b1g matematic
            LARGE_INTEGER elapsed_pc;

            // Used to store the performance frequency for math
            LARGE_INTEGER frequency;

            // Update performance frequency
            QueryPerformanceFrequency(&frequency);

            // Get the current performance counter value
            QueryPerformanceCounter(&current_time);

            // Get elapsed time in seconds
            elapsed_pc.QuadPart = current_time.QuadPart - starting_time.QuadPart;

            // Calculate the elapsed time (in ms)
            float elapsed = (
                (static_cast<float>(elapsed_pc.QuadPart) * 1000.0f) /
                (static_cast<float>(frequency.QuadPart))
                );

            // Return elapsed time
            return elapsed;
        }

        // Used to determine when the function was instantiated
        LARGE_INTEGER starting_time;
    };

   
