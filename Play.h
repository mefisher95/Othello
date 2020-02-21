#ifndef PLAY_H
#define PLAY_H

#include "mainIncludes.h"
#include "Board.h"
#include "Gameover.h"

void Play(Surface &, Event &, Board &, KeyPressed &, bool, bool &);
void set_images(Image & turn, Image & point, Image & point_empty,
                Image & point_black, Image & point_white, Rect & turn_rect,
                Rect & turn_background, Rect & turn_border,
                Rect & point_background, Rect & point_border, Rect & point_rect,
                Rect & point_white_rect, Rect & point_black_rect,
                Rect & point_empty_rect);

#endif
