#include <iostream>
#include <fstream>
#include "nlohamnn/json.hpp"
#include <utility> // For std::pair
#include "headers/readConfig.hpp"

using json = nlohmann::json;
using namespace std;

namespace FullScreenDisplay
{

    std::vector<int> readConfig(int option)
    {
        ifstream configfile("C:\\Users\\de509865\\Documents\\Tools\\FullScreenExpansion\\config.json");
        if (!configfile.is_open())
        {
            cerr << "Error: Could not open the file config.json" << endl;
            return {};
        }

        // parse the json file into a json object
        json config;
        configfile >> config;

        // Declare variables to store the arrays
        vector<int> fullscreenParams;
        vector<int> normalScreenParams;

        // Extract the "fullscreenParams" array from the JSON and store it in the variable
        if (config.contains("fullscreenParams") && config["fullscreenParams"].is_array())
        {
            fullscreenParams = config["fullscreenParams"].get<vector<int>>(); // Convert JSON array to vector
        }
        else
        {
            cerr << "Error: fullscreenParams not found or is not an array." << endl;
        }

        // Extract the "normalScreenParams" array from the JSON and store it in the variable
        if (config.contains("normalScreenParams") && config["normalScreenParams"].is_array())
        {
            normalScreenParams = config["normalScreenParams"].get<vector<int>>(); // Convert JSON array to vector
        }
        else
        {
            cerr << "Error: normalScreenParams not found or is not an array." << endl;
        }

        configfile.close();

        if (option == 1)
            return fullscreenParams;
        if (option == 2)
            return normalScreenParams;
    }

}
