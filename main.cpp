#include <windows.h>
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <cstdlib> // For std::stoi

const char *searchSubstring;

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

int main(int argc, char *argv[])
{
    // Check if the user passed the search substring and window position/size arguments
    if (argc != 6)
    {
        std::cerr << "Usage: " << argv[0] << " <search-substring> <x> <y> <width> <height>" << std::endl;
        return -1;
    }

    // Get the search substring (e.g., "Notepad", "Chrome", etc.)
    searchSubstring = argv[1];

    // Get the position and dimensions
    int x = std::stoi(argv[2]);
    int y = std::stoi(argv[3]);
    int width = std::stoi(argv[4]);
    int height = std::stoi(argv[5]);

    std::cout << "Searching for windows with titles containing: " << searchSubstring << std::endl;
    std::cout << "Moving windows to (" << x << ", " << y << ") with size (" << width << "x" << height << ")" << std::endl;

    // Pass the position and dimensions to the EnumWindowsProc callback function
    int params[4] = {x, y, width, height};
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(params));

    return 0;
}
