/********************************************************************************
/ Project: Othello
/-------------------------------------------------------------------------------
/ By: Michael Fisher, 2019
/================================================================================
/ File: Board.h
/
/ Class File Header for the Board class. The Board Class contains the majority
/ of the logic and exection for the main program. All actions are taken on a
/ main array of objects created by the seperate Square class, which is only
/ accesable either by or through the Board Class.
********************************************************************************/

#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include "mainIncludes.h"

//===============================================================================
// - Square class-
//===============================================================================

class Square
{
public:
    Square()
        :size_(80), state_(0)
    {
        rect_out.x = 10;
        rect_out.y = 10;
        rect_out.h = size_;
        rect_out.w = size_;

        rect_in.x = rect_out.x + 2;
        rect_in.y = rect_out.y + 2;
        rect_in.h = rect_out.h - 4;
        rect_in.w = rect_out.w - 4;
    }

    Rect get_rect_out() const { return rect_out; }
    Rect get_rect_in() const { return rect_in; }

    int x() const { return rect_in.x; }
    int y() const { return rect_in.y; }
    int h() const { return rect_in.h; }
    int w() const { return rect_in.w; }

    int & state() { return state_; }
    int state() const { return state_; }
    
    int size_;
    int state_;
    Rect rect_out;
    Rect rect_in;
};

//===============================================================================
// - Board Class -
//===============================================================================

class Board
{
public:
    Board(Surface & surface)
        :surface_(surface), size_(8), turn_(1)
    {}

    int board_x() const { board_arr[0][8].x(); }
    int board_y() const { board_arr[0][8].y(); }
    
    void change_turn();

    int board_state(int x, int y) const;
    void select();
    void make();
    void draw();
    int turn() const { return turn_; }
    int & turn() { return turn_; }

    int num_black() const;
    int num_white() const;
    int num_empty() const;

    int num_count(int) const;

    void ai(int player);

    bool north(int x, int y);
    bool south(int x, int y);
    bool east(int x, int y);
    bool west(int x, int y);
    bool northwest(int x, int y);
    bool northeast(int x, int y);
    bool southwest(int x, int y);
    bool southeast(int x, int y);
    bool valid(int x, int y);
    bool is_moveable();
    bool is_moveable(int turn);

    void flip(int x, int y);
    
private:
    int size_;
    int turn_;
    Surface & surface_;
    Square board_arr[8][8];

    static Sound sound;
};


#endif
