#include <windows.h>
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <cstdlib> // For std::stoi
#include <vector>
#include "headers/windowDisplay.hpp"

namespace FullScreenDisplay
{
    static char *searchSubstring;

    // Helper function to convert a string to lowercase
    void toLowerCase(std::string &str)
    {
        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c)
                       { return std::tolower(c); });
    }

    BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
    {
        char windowTitle[256];
        GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));

        // Convert window title to lowercase for case-insensitive comparison
        std::string titleLower(windowTitle);
        toLowerCase(titleLower);

        // Retrieve the search substring from the lParam (passed argument)
        // const char *searchSubstring = reinterpret_cast<const char *>(lParam);

        // Convert search substring to lowercase
        std::string searchLower(searchSubstring);
        toLowerCase(searchLower);

        // Check if the window title contains the search substring (case-insensitive)
        if (titleLower.find(searchLower) != std::string::npos)
        {
            std::cout << "Found a window with title: " << windowTitle << std::endl;

            // Get position and dimensions from lParam
            int *params = reinterpret_cast<int *>(lParam);
            int x = params[0];
            int y = params[1];
            int width = params[2];
            int height = params[3];

            // Move or resize the window as specified by the user
            MoveWindow(hwnd, x, y, width, height, TRUE); // Example: Move and resize
        }

        return TRUE; // Continue enumerating windows
    }

    int processWindowChanges(std::vector<int> dimensions, char *substring)
    {
        // Check if the user passed the search substring and window position/size arguments
        if (dimensions.size() != 4)
        {
            std::cerr << "Usage: " << substring << " <search-substring> <x> <y> <width> <height>" << std::endl;
            return -1;
        }

        // Get the search substring (e.g., "Notepad", "Chrome", etc.)
        searchSubstring = substring;

        // Get the position and dimensions
        int x = dimensions[0];
        int y = dimensions[1];
        int width = dimensions[2];
        int height = dimensions[3];

        std::cout << "Searching for windows with titles containing: " << searchSubstring << std::endl;
        std::cout << "Moving windows to (" << x << ", " << y << ") with size (" << width << "x" << height << ")" << std::endl;

        // Pass the position and dimensions to the EnumWindowsProc callback function
        int params[4] = {x, y, width, height};
        EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(params));

        return 0;
    }

}
