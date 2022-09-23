#include <iostream>
#include <string>
#include <filesystem>
#include <cstring>
#include <fstream>
#include <chrono>
#include <thread>

// detecting system type
#ifdef __APPLE__
    bool macos = true;
#endif

#ifdef __WIN64__
    bool macos = false;
#endif

#ifdef __WIN32__
    bool macos = false;
#endif



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
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono;      // nanoseconds, system_clock, seconds

    auto path = std::filesystem::current_path(); //getting path
    current_path(path); //setting path

    cout << "Retro Games Client v1.4.0";
    if (macos)
    {
        cout << " - MacOS" << endl;
    }
    else
    {
        cout << " - Windows" << endl;
    }

    // get list of installed games
    string installed_games[5];
    string game_exec[5];
    bool snake = check_game_installed("SnakeGame");
    bool dodger = check_game_installed("DodgerGame");
    bool tictactoe = check_game_installed("TicTacToe");
    bool wordle = check_game_installed("wordle");
    bool platformer = check_game_installed("Platformer2000");

    // check if any games are installed
    if (snake)
    {
        installed_games[0] = "SnakeGame";
        game_exec[0] = "python ./SnakeGame/turtlesnake.py";
    }
    else
    {
        installed_games[0] = "";
    }
    if (dodger)
    {
        installed_games[1] = "DodgerGame";
        game_exec[1] = "python ./DodgerGame/dodger.py";
    }
    else
    {
        installed_games[1] = "";
    }
    if (tictactoe)
    {
        installed_games[2] = "TicTacToe";
        game_exec[2] = "start ./TicTacToe/TicTacToe-vs-AI.exe";
    }
    else
    {
        installed_games[2] = "";
    }
    if (wordle)
    {
        installed_games[3] = "wordle";
        game_exec[3] = "lua ./wordle/main.lua";
    }
    else
    {
        installed_games[3] = "";
    }
    if (platformer)
    {
        installed_games[4] = "Platformer2000";
        game_exec[4] = "start ./Platformer2000/Hello-Unity_Win64.exe";
    }
    else
    {
        installed_games[4] = "";
    }

    cout << "Installed Games: \n"
         << "- " << installed_games[0] << endl
         << "- " << installed_games[1] << endl
         << "- " << installed_games[2] << endl
         << "- " << installed_games[3] << endl
         << "- " << installed_games[4] << endl;

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
            if (installed_games[0] == "" && installed_games[1] == "" && installed_games[2] == "" && installed_games[3] == "" && installed_games[4] == "")
            {
                cout << "You have no installed games." << endl;
            }
            else
            {
                cout << "Your game slots: \n"
                     << "1 - " << installed_games[0] << endl
                     << "2 - " << installed_games[1] << endl
                     << "3 - " << installed_games[2] << endl
                     << "4 - " << installed_games[3] << endl
                     << "5 - " << installed_games[4] << endl;
                cout << "Enter game number: ";
                int game_choice;
                cin >> game_choice;

                try
                {
                system(game_exec[game_choice - 1].c_str());
                }
                catch (...)
                {
                    cout << "Invalid game choice" << endl;
                }
                
            }
            break;
        case 2:
            cout << "Your game slots: \n"
                 << "1 - " << installed_games[0] << endl
                 << "2 - " << installed_games[1] << endl
                 << "3 - " << installed_games[2] << endl
                 << "4 - " << installed_games[3] << endl
                 << "5 - " << installed_games[4] << endl;
            cout << "Enter game to install: ";
            cout << "\n1 - SnakeGame\n2 - DodgerGame\n3 - TicTacToe\n4 - Wordle\n5 - Platformer 2000 (Windows Only)" << endl;
            int slot_choice;
            cin >> slot_choice;
            if (slot_choice == 1)
            {
                if (installed_games[0] == "")
                {
                    system("pip install pygame");
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
                    system("pip install pygame");
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
            else if (slot_choice == 3)
            {
                if (installed_games[2] == "")
                {
                    system("git clone https://github.com/AviationSFO/TicTacToe.git");
                }
                else
                {
                    cout << "Game slot 3 is already occupied" << endl;
                }
            }
            else if (slot_choice == 4)
            {
                if (installed_games[3] == "")
                {
                    system("git clone -b client-use https://github.com/AviationSFO/wordle");
                    cout << endl
                         << endl
                         << "WARNING: A Lua interpreter is required to run the game," << endl
                         << "please install one if you do not already!" << endl;
                }
                else
                {
                    cout << "Game slot 4 is already occupied" << endl;
                }
            }
            else if (slot_choice == 5)
            {
                if (!macos)
                {
                    if (installed_games[4] == "")
                    {
                        system("powershell -ExecutionPolicy Bypass -F installP2K.ps1");
                    }
                }
                else
                {
                    cout << "Platformer 2000 is not supported on MacOS" << endl;
                }
            }
            else
            {
                cout << "Invalid game choice" << endl;
            }

            break;
        case 3:
            if (installed_games[0] == "" && installed_games[1] == "" && installed_games[2] == "" && installed_games[3] == "" && installed_games[4] == "")
            {
                cout << "You have no installed games." << endl;
            }
            else
            {
                cout << "Installed Games: \n"
                     << installed_games[0] << endl
                     << installed_games[1] << endl
                     << installed_games[2] << endl
                     << installed_games[3] << endl
                     << installed_games[4] << endl;
                cout << "Enter slot game to uninstall: " << endl;
                if (snake)
                {
                    cout << "1 - SnakeGame" << endl;
                }
                if (dodger)
                {
                    cout << "2 - DodgerGame" << endl;
                }
                if (tictactoe)
                {
                    cout << "3 - TicTacToe" << endl;
                }
                if (wordle)
                {
                    cout << "4 - Wordle" << endl;
                }
                if (platformer)
                {
                    cout << "5 - Platformer 2000" << endl;
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
                else if (uninstall_choice == 3 && tictactoe)
                {
                    system("rmdir /s TicTacToe");
                    cout << endl
                         << endl
                         << "Restart client for changes to take effect" << endl;
                }
                else if (uninstall_choice == 4 && wordle)
                {
                    system("rmdir /s wordle");
                    cout << endl
                         << endl
                         << "Restart client for changes to take effect" << endl;
                }
                else if (uninstall_choice == 5 && platformer)
                {
                    system("rmdir /s Platformer2000");
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
            tictactoe = check_game_installed("TicTacToe");
            wordle = check_game_installed("wordle");
            platformer = check_game_installed("Platformer2000");
            if (snake)
            {
                installed_games[0] = "SnakeGame";
                game_exec[0] = "python ./SnakeGame/turtlesnake.py";
            }
            else
            {
                installed_games[0] = "";
            }
            if (dodger)
            {
                installed_games[1] = "DodgerGame";
                game_exec[1] = "python ./DodgerGame/dodger.py";
            }
            else
            {
                installed_games[1] = "";
            }
            if (tictactoe)
            {
                installed_games[2] = "TicTacToe";
                game_exec[2] = "start ./TicTacToe/TicTacToe-vs-AI.exe";
            }
            else
            {
                installed_games[2] = "";
            }
            if (wordle)
            {
                installed_games[3] = "wordle";
                game_exec[3] = "lua ./wordle/main.lua";
            }
            else
            {
                installed_games[3] = "";
            }
            if (platformer)
            {
                installed_games[4] = "Platformer2000";
                game_exec[4] = "start ./Platformer2000/Hello-Unity_Win64.exe";
            }
            else
            {
                installed_games[4] = "";
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