#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "mainIncludes.h"

void main_menu(Surface &, Event &, KeyPressed &, bool &, bool &, bool &, bool &);
void set_images(Image & turn, Image & point, Image & point_empty,
                Image & point_black, Image & point_white, Rect & turn_rect,
                Rect & turn_background, Rect & turn_border,
                Rect & point_background, Rect & point_border, Rect & point_rect,
                Rect & point_white_rect, Rect & point_black_rect,
                Rect & point_empty_rect);

#endif
