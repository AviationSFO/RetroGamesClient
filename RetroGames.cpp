#include <iostream>
#include <string>
#include <filesystem>
#include <cstring>
#include <fstream>

using namespace std;
using filesystem::current_path;
using filesystem::directory_iterator;

// gets list of installed packages
bool check_game_installed(string game)
{
    for (directory_iterator it(current_path()); it != directory_iterator(); ++it)
    {
        if (it->path().filename().string() == game)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    cout << "Retro Games Client v1.0.0" << endl;
    // get list of installed games
    string installed_games[2];
    bool snake = check_game_installed("SnakeGame");
    bool dodger = check_game_installed("DodgerGame");

    // check if any games are installed
    if (snake && dodger)
    {
        installed_games[0] = "SnakeGame";
        installed_games[1] = "DodgerGame";
    }
    else if (snake && !dodger)
    {
        installed_games[0] = "SnakeGame";
        installed_games[1] = "";
    }
    else if (!snake && dodger)
    {
        installed_games[0] = "";
        installed_games[1] = "DodgerGame";
    }
    else
    {
        installed_games[0] = "";
        installed_games[1] = "";
    }

    cout << "Installed Games: \n"
         << "- " << installed_games[0] << endl
         << "- " << installed_games[1] << endl;

    // user interfacing
    string options = "1 - Play Game\n2 - Install Game\n3 - Uninstall Game\n4 - Refresh installed list\n5 - Exit";
    int choice;
    bool running = true;

    while (running)
    {
        cout << options << endl;
        cin >> choice;

        // play game
        switch (choice)
        {
        case 1:
            if (installed_games[0] == "" && installed_games[1] == "")
            {
                cout << "You have no installed games." << endl;
            }
            else
            {
                cout << "Your game slots: \n"
                     << "1 - " << installed_games[0] << endl
                     << "2 - " << installed_games[1] << endl;
                cout << "Enter game number: ";
                int game_choice;
                cin >> game_choice;

                if (game_choice == 1 && installed_games[0] != "")
                {
                    string version;
                    ifstream version_txt("SnakeGame/version.txt");
                    getline(version_txt, version);
                    cout << "Launching " << version << endl;
                    system("python ./SnakeGame/turtlesnake.py");
                }
                else if (game_choice == 2 && installed_games[1] != "")
                {
                    system("python ./DodgerGame/dodger.py");
                }
                else
                {
                    cout << "Invalid game choice" << endl;
                }
            }
            break;
        case 2:
            cout << "Your game slots: \n"
                 << "1 - " << installed_games[0] << endl
                 << "2 - " << installed_games[1] << endl;
            cout << "Enter game to install: ";
            cout << "\n1 - SnakeGame\n2 - DodgerGame" << endl;
            int slot_choice;
            cin >> slot_choice;
            if (slot_choice == 1)
            {
                if (installed_games[0] == "")
                {
                    system("git clone https://github.com/AviationSFO/SnakeGame.git");
                    cout << endl
                         << endl
                         << "Restart client for changes to take effect" << endl;
                }
                else
                {
                    cout << "Game slot 1 is already occupied" << endl;
                }
            }
            else if (slot_choice == 2)
            {
                if (installed_games[1] == "")
                {
                    system("git clone https://github.com/AviationSFO/DodgerGame.git");
                    cout << endl
                         << endl
                         << "Restart client for changes to take effect" << endl;
                }
                else
                {
                    cout << "Game slot 2 is already occupied" << endl;
                }
            }
            else
            {
                cout << "Invalid game choice" << endl;
            }
            break;
        case 3:
            if (installed_games[0] == "" && installed_games[1] == "")
            {
                cout << "You have no installed games." << endl;
            }
            else
            {
                cout << "Installed Games: \n"
                     << installed_games[0] << endl
                     << installed_games[1] << endl;
                cout << "Enter slot game to uninstall: ";
                if (snake)
                {
                    cout << "1 - SnakeGame" << endl;
                }
                if (dodger)
                {
                    cout << "2 - DodgerGame" << endl;
                }
                int uninstall_choice;
                cin >> uninstall_choice;
                if (uninstall_choice == 1 && snake)
                {
                    system("rmdir /s SnakeGame");
                    cout << endl
                         << endl
                         << "Restart client for changes to take effect" << endl;
                }
                else if (uninstall_choice == 2 && dodger)
                {
                    system("rmdir /s DodgerGame");
                    cout << endl
                         << endl
                         << "Restart client for changes to take effect" << endl;
                }
                else
                {
                    cout << "Invalid game choice" << endl;
                }
            }
            break;
        case 4:
            snake = check_game_installed("SnakeGame");
            dodger = check_game_installed("DodgerGame");
            if (snake && dodger)
            {
                installed_games[0] = "SnakeGame";
                installed_games[1] = "DodgerGame";
            }
            else if (snake && !dodger)
            {
                installed_games[0] = "SnakeGame";
                installed_games[1] = "";
            }
            else if (!snake && dodger)
            {
                installed_games[0] = "";
                installed_games[1] = "DodgerGame";
            }
            else
            {
                installed_games[0] = "";
                installed_games[1] = "";
            }
            break;
        case 5:
            running = false;
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }

    return 0;
}