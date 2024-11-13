#include <windows.h>
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

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
    const char *searchSubstring = reinterpret_cast<const char *>(lParam);

    // Convert search substring to lowercase
    std::string searchLower(searchSubstring);
    toLowerCase(searchLower);

    // Check if the window title contains the search substring (case-insensitive)
    if (titleLower.find(searchLower) != std::string::npos)
    {
        std::cout << "Found a window with title: " << windowTitle << std::endl;

        // Move or resize the window if needed
        MoveWindow(hwnd, 100, 100, 800, 600, TRUE); // Example: Move and resize
    }

    return TRUE; // Continue enumerating windows
}

int main(int argc, char *argv[])
{
    // Check if the user passed the search substring as an argument
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <search-substring>" << std::endl;
        return -1;
    }

    // Get the search substring (e.g., "Notepad", "Chrome", etc.)
    const char *searchSubstring = argv[1];

    std::cout << "Searching for windows with titles containing: " << searchSubstring << std::endl;

    // Enumerate all windows and look for those with titles containing the search substring
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(searchSubstring));

    return 0;
}
