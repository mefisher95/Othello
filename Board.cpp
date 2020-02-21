/********************************************************************************
/ Project: Othello
/-------------------------------------------------------------------------------
/ By: Michael Fisher, 2019
/================================================================================
/ File: Board.cpp
/
/ Sorce file for the Board Class
********************************************************************************/

#include "Board.h"
#include <ctime>

Sound Board::sound("sounds/toggle.wav");

// manually changes the turn for the players
void Board::change_turn()
{
    if (turn_ == 1) turn_ = 2;
    else turn_ = 1;
}

// returns what the player state of a square is (empty = 0, black = 1, white = 2)
int Board::board_state(int x, int y) const
{
    return (board_arr[x][y].state());
}

// allows moves by human players
void Board::select()
{
    if (!is_moveable())
    {
        change_turn();
        return;
    }
    for(int i = 0; i < size_; ++i)
    {
        for (int j = 0; j < size_; ++j)
        {
            if (mouse_left() &&
                mouse_x() > board_arr[i][j].x() &&
                mouse_x() < board_arr[i][j].x() + board_arr[i][j].w() &&
                mouse_y() > board_arr[i][j].y() &&
                mouse_y() < board_arr[i][j].y() + board_arr[i][j].h())
            {
                if (board_arr[i][j].state() == 0 && valid(i, j))
                {                    
                    flip(i, j);
                    sound.play();
                    change_turn();
                }
            }
        }
    }
}

// sets the positions of all squares, and sets all states to 0, except for center
void Board::make()
{
    for (int i = 0; i < size_; ++i)
    {
        for (int j = 0; j < size_; ++j)
        {
            board_arr[i][j].rect_out.x = 80 * i + 2;
            board_arr[i][j].rect_in.x = 80 * i + 4;
            board_arr[i][j].rect_out.y = 80 * j + 2;
            board_arr[i][j].rect_in.y = 80 * j + 4;
            board_arr[i][j].state() = 0;

            int mid = 8 / 2;
            board_arr[mid - 1][mid - 1].state() = 1;
            board_arr[mid - 1][mid].state() = 2;
            board_arr[mid][mid - 1].state() = 2;
            board_arr[mid][mid].state() = 1;
        }
    }
}

// draws the board with pieces corresponding to the square state
void Board::draw()
{
    for (int i = 0; i < size_; ++i)
    {
        for (int j = 0; j < size_; ++j)
        {
            surface_.put_rect(board_arr[i][j].get_rect_out(), BLACK);
            
            surface_.put_rect(board_arr[i][j].get_rect_in(), FORREST_GREEN);

            if (board_arr[i][j].state_ == 1)
                surface_.put_circle(board_arr[i][j].rect_out.x + board_arr[i][j].rect_out.w / 2,
                                    board_arr[i][j].rect_out.y + board_arr[i][j].rect_out.h / 2,
                                    10, BLACK);
            if (board_arr[i][j].state_ == 2)
                surface_.put_circle(board_arr[i][j].rect_out.x + board_arr[i][j].rect_out.w / 2,
                                    board_arr[i][j].rect_out.y + board_arr[i][j].rect_out.h / 2,
                                    10, WHITE);
        }
    }
}

// returns the number of total squares with the requested state
int Board::num_count(int state) const
{
    int ret = 0;
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            if (board_arr[x][y].state() == state) ++ret;
        }
    }
    return ret;
}

// ai player;
void Board::ai(int player)
{
    srand((unsigned int) time(NULL));
    
    if (!is_moveable())
    {
        change_turn();
        return;
    }
    if (turn() != player) return;

    
    while(1)
    {
        
        int x = rand() % 8;
        int y = rand() % 8;

        if (valid(x, y))
        {
            board_arr[x][y].state() = player;
            flip(x, y);
            change_turn();
     
            return;
        }
    }
}

//==============================================================================
// boolean checks for position
//==============================================================================

// cardinal positions
bool Board::north(int x, int y)
{
    int player, enemy;

    if (turn_ == 1) { player = 1; enemy = 2; }
    else { player = 2; enemy = 1; }

    if (board_arr[x][y - 1].state() == enemy)
        for (int i = 0; i < y; ++i)
        {
            if (board_arr[x][y - i].state() == enemy &&
                board_arr[x][y - i - 1].state() != 0 &&
                board_arr[x][y - i - 1].state() == player)
                return true;
        }
    return false;
}

bool Board::south(int x, int y)
{
    int player, enemy;

    if (turn_ == 1) { player = 1; enemy = 2; }
    else { player = 2; enemy = 1; }

    if (board_arr[x][y + 1].state() == enemy)
        for (int i = 0; i < 8 - y - 1; ++i)
        {
            if (board_arr[x][y + i].state() == enemy &&
                board_arr[x][y + i + 1].state() != 0 &&
                board_arr[x][y + i + 1].state() == player)
                return true;
        }
    return false;
}

bool Board::east(int x, int y)
{
    int player, enemy;

    if (turn_ == 1) { player = 1; enemy = 2; }
    else { player = 2; enemy = 1; }

    if (board_arr[x + 1][y].state() == enemy)
        for (int i = 0; i < 8 - x - 1; ++i)
        {
            if (board_arr[x + i][y].state() == enemy &&
                board_arr[x + i + 1][y].state() != 0 &&
                board_arr[x + i + 1][y].state() == player)
                return true;
        }
    return false;
}

bool Board::west(int x, int y)
{
    int player, enemy;

    if (turn_ == 1) { player = 1; enemy = 2; }
    else { player = 2; enemy = 1; }

    if (board_arr[x - 1][y].state() == enemy)
        for (int i = 0; i < x; ++i)
        {
            if (board_arr[x - i][y].state() == enemy &&
                board_arr[x - i - 1][y].state() != 0 &&
                board_arr[x - i - 1][y].state() == player)
                return true;
        }
    return false;
}

// oblique positions

bool Board::northeast(int x, int y)
{
    int player, enemy;

    if (turn_ == 1) { player = 1; enemy = 2; }
    else { player = 2; enemy = 1; }

    if (board_arr[x + 1][y - 1].state() == enemy)
        for (int i = 0; i < y && i < 8 - x - 1; ++i)
        {
            if (board_arr[x + i][y - i].state() == enemy &&
                board_arr[x + i + 1][y - i - 1].state() != 0 &&
                board_arr[x + i + 1][y - i - 1].state() == player)
                return true;
        }
    return false;
}

bool Board::northwest(int x, int y)
{
    int player, enemy;

    if (turn_ == 1) { player = 1; enemy = 2; }
    else { player = 2; enemy = 1; }

    if (board_arr[x - 1][y - 1].state() == enemy)
        for (int i = 0; i < y && i < x; ++i)
        {
            if (board_arr[x - i][y - i].state() == enemy &&
                board_arr[x - i - 1][y - i - 1].state() != 0 &&
                board_arr[x - i - 1][y - i - 1].state() == player)
                return true;
        }
    return false;
}

bool Board::southeast(int x, int y)
{
    int player, enemy;

    if (turn_ == 1) { player = 1; enemy = 2; }
    else { player = 2; enemy = 1; }

    if (board_arr[x + 1][y + 1].state() == enemy)
        for (int i = 0; i < 8 - y - 1 && i < 8 - x - 1; ++i)
        {
            if (board_arr[x + i][y + i].state() == enemy &&
                board_arr[x + i + 1][y + i + 1].state() != 0 &&
                board_arr[x + i + 1][y + i + 1].state() == player)
                return true;
        }
    return false;
}

bool Board::southwest(int x, int y)
{
    int player, enemy;

    if (turn_ == 1) { player = 1; enemy = 2; }
    else { player = 2; enemy = 1; }

    if (board_arr[x - 1][y + 1].state() == enemy)
        for (int i = 0; i < 8 - y - 1 && i < x; ++i)
        {
            if (board_arr[x - i][y + i].state() == enemy &&
                board_arr[x - i - 1][y + i + 1].state() != 0 &&
                board_arr[x - i - 1][y + i + 1].state() == player)
                return true;
        }
    return false;
}



bool Board::valid(int x, int y)
{
    if ((north(x, y) || south(x, y) || west(x, y) || east(x, y) ||
         northwest(x, y) || northeast(x, y) || southwest(x, y) || southeast(x, y)) &&
        board_arr[x][y].state() == 0)
        return true;
    
    return false;
}

bool Board::is_moveable()
{
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            if (valid(x, y)) return true;
        }
    }
    return false;
}

bool Board::is_moveable(int turn)
{
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            if (valid(x, y)) return true;
        }
    }
    return false;
}

void Board::flip(int x, int y)
{
    int player, enemy, end;

    if (turn_ == 1) { player = 1; enemy = 2; }
    else { player = 2; enemy = 1; }

    if (north(x, y))
    {
        end = 0;
        for (int i = 1; i <= y; ++i)
        {
            if (board_arr[x][y - i].state() == player) { end = i; break; }
        }
        for (int i = 0; i <= end; ++i)
        {
            board_arr[x][y - i].state() = player;
        }
    }

    if (south(x, y))
    {
        end = 0;
        for (int i = 1; i <= 8 - y; ++i)
        {
            if (board_arr[x][y + i].state() == player) {end = i; break; }
        }
        for (int i = 0; i <= end; ++i)
        {
            board_arr[x][y + i].state() = player;
        }
    }

    if (east(x, y))
    {
        end = 0;
        for (int i = 1; i <= 8 - x; ++i)
        {
            if (board_arr[x + i][y].state() == player) {end = i; break; }
        }
        for (int i = 0; i <= end; ++i)
        {
            board_arr[x + i][y].state() = player;
        }
    }

    if (west(x, y))
    {
        end = 0;
        for (int i = 1; i <= 8; ++i)
        {
            if (board_arr[x - i][y].state() == player) {end = i; break; }
        }
        for (int i = 0; i <= end; ++i)
        {
            board_arr[x - i][y].state() = player;
        }
    }

    if (northeast(x, y))
    {
        end = 0;
        for (int i = 1; i <= 8; ++i)
        {
            if (board_arr[x + i][y - i].state() == player) {end = i; break; }
        }
        for (int i = 0; i <= end; ++i)
        {
            board_arr[x + i][y - i].state() = player;
        }
    }

    if (northwest(x, y))
    {
        end = 0;
        for (int i = 1; i <= 8; ++i)
        {
            if (board_arr[x - i][y - i].state() == player) {end = i; break; }
        }
        for (int i = 0; i <= end; ++i)
        {
            board_arr[x - i][y - i].state() = player;
        }
    }

    if (southwest(x, y))
    {
        end = 0;
        for (int i = 1; i <= 8; ++i)
        {
            if (board_arr[x - i][y + i].state() == player) {end = i; break; }
        }
        for (int i = 0; i <= end; ++i)
        {
            board_arr[x - i][y + i].state() = player;
        }
    }

    if (southeast(x, y))
    {
        end = 0;
        for (int i = 1; i <= 8; ++i)
        {
            if (board_arr[x + i][y + i].state() == player) {end = i; break; }
        }
        for (int i = 0; i <= end; ++i)
        {
            board_arr[x + i][y + i].state() = player;
        }
    }
}
