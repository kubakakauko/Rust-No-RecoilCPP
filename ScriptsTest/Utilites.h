#pragma once
#include <consoleapi2.h>

class Utilities
{

public:
    float fov;
    float sens;
	
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

   
