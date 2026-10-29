
#include <iostream>
#include <fstream> // for reading jokes from a file
#include <string> // for reading jokes from a file
#include <vector> // for storing jokes
#include <cstdlib> // for rand() and srand()
#include <ctime>  // for time()
using namespace std;

int main() {
    ifstream file("randomJokes.txt"); // Open the file containing jokes
    vector<string> jokes; // Vector to store jokes
    string line; // Variable to hold each line read from the file

    if (!file.is_open()) { // Check if the file was opened successfully
        cout << "Error: Could not open randomJokes.txt" << endl;
        return 1;
    }

    while (getline(file, line)) { // Read each line from the file
        if (!line.empty()) { // Check if the line is not empty
            jokes.push_back(line); // Add the joke to the vector
        }
    }
    file.close(); // Close the file after reading

    if (jokes.empty()) { // Check if any jokes were read from the file
        cout << "No jokes found in the file." << endl; // If no jokes were found, print an error message
        return 1;
    }

    srand(time(0)); // Seed the random number generator with the current time
    string prompt; // Variable to hold user input

    while (true) { // Infinite loop to keep asking for user input
        cout << "\nType 'Alexa, tell me a joke' or 'quit': "; // Prompt the user for input
        getline(cin, prompt);

        if (prompt == "quit" || prompt == "Quit") { // Check if the user wants to quit
            cout << "Goodbye!" << endl;
            break;
        }

        if (prompt == "Alexa, tell me a joke") { // Check if the user wants to hear a joke
            int index = rand() % jokes.size(); // Generate a random index to select a joke
            string joke = jokes[index]; // Get the joke at the random index

            size_t separator = joke.find('?'); // Find the position of the question mark in the joke

            if (separator != string::npos) { // Check if a question mark was found in the joke
                cout << joke.substr(0, separator + 1) << endl; // Print the question part of the joke
                cout << "Press Enter to reveal the punchline...";
                getline(cin, prompt); // Wait for the user to press Enter
                cout << joke.substr(separator + 1) << endl; // Print the punchline part of the joke
            } else {
                cout << "Invalid joke format." << endl;
            }
        } else { // If the user input is not recognized, prompt them again
            cout << "Please enter 'Alexa, tell me a joke' or 'quit'."
                 << endl;
        }
    }

    return 0;
}
