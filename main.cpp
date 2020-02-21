/********************************************************************************
/ Project: Othello
/-------------------------------------------------------------------------------
/ By: Michael Fisher, 2019
================================================================================
/ File: main.cpp
/
/ Main executable for the game "Othello". Main loop serves as a hub for the
/ execution of the main source files for the Program. These includes:
/ - Board.cpp/h, a class file that controls the primary game logic and execution
/ - Main_menu.cpp/h, a source file that contains the main menu for the game and
/   serves as the activity hub for the end user
/ - Play.cpp/h, a source file that contains the primary play loop for the game
/ - Tutorial.cpp/h, a source file that contains a modified play loop for
/   educating end users on how to use the program
/ - mainIncludes.h, a header file that contains the majority of all needed SDL
/   default librarys, which includes:
/     - Includes.h
/     - Constants.h
/     - compgeom.h
/     - Surface.h
/     - Event.h
********************************************************************************/
#include <ctime>
#include "mainIncludes.h"
#include "Board.h"
#include "Main_menu.h"
#include "Play.h"
#include "Tutorial.h"


int main()
{
    KeyPressed keypress;
    Surface surface;
    Event event;
    Board board(surface);
    Music game_music("sounds/classical.ogg");
    //game_music.play();

    

    while(1)
    {
        bool single = false;
        bool multi = false;
        bool help = false;
        bool exit = false;

        // main menu
        if (!exit) main_menu(surface, event, keypress, single, multi, help, exit);
        // single player game
        if (single) Play(surface, event, board, keypress, single, exit);
        // multi player game
        if (multi) Play(surface, event, board, keypress, single, exit);
        // tutorial
        if (help) tutorial(surface, event, board, keypress, exit);
        // terminates program
        if (exit) break;
    }
    return 0;
}

