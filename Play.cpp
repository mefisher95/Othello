#include "Play.h"

void Play(Surface & surface, Event & event, Board & board, KeyPressed & keypress,
          bool single, bool & exit)
{
    Font font("fonts/FreeMonoBold.ttf", 40);
    Image turn(font.render("Turn: ", WHITE));
    Rect turn_rect = turn.getRect();
    Rect turn_background;
    Rect turn_border;
    Rect point_background;
    Rect point_border;

    Image point(font.render("Points:", WHITE));
    Rect point_rect = point.getRect();
    Image point_white(font.render("White: ", WHITE));
    Rect point_white_rect = point_white.getRect();
    Image point_black(font.render("Black: ", WHITE));
    Rect point_black_rect = point_black.getRect();
    Image point_empty(font.render("Empty: ", WHITE));
    Rect point_empty_rect = point_empty.getRect();
    
    int scr_white_int, scr_black_int, scr_empty_int;
    char str_white[3];
    char str_black[3];
    char str_empty[3];

    Image Background("images/wood.jpg");
    Rect backrect = Background.getRect();

    Font exit_f("fonts/FreeMonoBold.ttf", 30);
    Image cont_white(exit_f.render("Exit", WHITE));
    Image cont_black(exit_f.render("Exit", BLACK));
    Rect cont_rect = cont_black.getRect();
    cont_rect.x = WIDTH - cont_rect.w - 100;
    cont_rect.y = HEIGHT - cont_rect.h - 20;

    Rect cont_background;
    cont_background.x = cont_rect.x - 30;
    cont_background.y = cont_rect.y ;
    cont_background.w = cont_rect.w + 60;
    cont_background.h = cont_rect.h + 5;

    Rect cont_border;
    cont_border.x = cont_background.x - 3;
    cont_border.y = cont_background.y - 3;
    cont_border.w = cont_background.w + 6;
    cont_border.h = cont_background.h + 6;

    set_images(turn, point, point_empty, point_black, point_white,turn_rect,
               turn_background, turn_border, point_background, point_border,
               point_rect, point_white_rect, point_black_rect, point_empty_rect);
 
    board.make();
    int ai_count = 0;

    while(1)
    {
        keypress = get_keypressed();
        if ((event.poll() && event.type() == QUIT) || keypress[ESC])
        {
            exit = true;
            return;
        }

        if (mouse_x() > cont_rect.x && mouse_x() < cont_rect.x + cont_rect.w &&
            mouse_y() > cont_rect.y && mouse_y() < cont_rect.y + cont_rect.h &&
            mouse_left())
            return;
        
        int player_turn = board.turn();
        if (!board.is_moveable(1) && !board.is_moveable(2))
        {
            game_over(surface, event, board, keypress, exit);
            return;
        }
        board.turn() = player_turn;

        scr_empty_int = board.num_count(0);
        scr_black_int = board.num_count(1);
        scr_white_int = board.num_count(2);

        sprintf(str_empty, "%d", scr_empty_int);
        sprintf(str_black, "%d", scr_black_int);
        sprintf(str_white, "%d", scr_white_int);

        Image scr_empty(font.render(str_empty, WHITE));
        Rect scr_empty_rect = scr_empty.getRect();
        scr_empty_rect.x = point_empty_rect.x + point_empty_rect.w;
        scr_empty_rect.y = point_empty_rect.y;

        Image scr_black(font.render(str_black, WHITE));
        Rect scr_black_rect = scr_black.getRect();
        scr_black_rect.x = point_black_rect.x + point_black_rect.w;
        scr_black_rect.y = point_black_rect.y;

        Image scr_white(font.render(str_white, WHITE));
        Rect scr_white_rect = scr_white.getRect();
        scr_white_rect.x = point_white_rect.x + point_white_rect.w;
        scr_white_rect.y = point_white_rect.y;

        

        // make board actions
        
        if (board.turn() == 1) { ai_count = 1; board.select(); }
        if ( ++ai_count > 0) ++ai_count;

 
        if (ai_count >= 70 && board.turn() == 2 && board.is_moveable())
        {
            board.ai(2);
            ai_count = 0;
        }
        

        surface.lock();
        surface.put_image(Background, backrect);
        board.draw();
        surface.put_rect(turn_border, WHITE);
        surface.put_rect(point_border, WHITE);
        surface.put_rect(turn_background, BLACK);
        surface.put_rect(point_background, BLACK);
        surface.put_image(point_white, point_white_rect);
        surface.put_image(scr_white, scr_white_rect);
        surface.put_image(point_black, point_black_rect);
        surface.put_image(scr_black, scr_black_rect);
        surface.put_image(point_empty, point_empty_rect);
        surface.put_image(scr_empty, scr_empty_rect);
        surface.put_image(point, point_rect);
        
        if (board.turn() == 1)
        {
            Image turn_player(font.render("BLACK", WHITE));
            Rect turn_player_rect = turn_player.getRect();
            turn_player_rect.x = turn_rect.x + turn_rect.w;
            turn_player_rect.y = turn_rect.y;
            surface.put_image(turn, turn_rect);
            surface.put_image(turn_player, turn_player_rect);
            
        }
        if (board.turn() == 2)
        {
            Image turn_player(font.render("WHITE", WHITE));
            Rect turn_player_rect = turn_player.getRect();
            turn_player_rect.x = turn_rect.x + turn_rect.w;
            turn_player_rect.y = turn_rect.y;
            surface.put_image(turn, turn_rect);
            surface.put_image(turn_player, turn_player_rect);
        }

        if (mouse_x() > cont_rect.x && mouse_x() < cont_rect.x + cont_rect.w &&
            mouse_y() > cont_rect.y && mouse_y() < cont_rect.y + cont_rect.h)
        {
            surface.put_rect(cont_border, BLACK);
            surface.put_rect(cont_background, WHITE);
            surface.put_image(cont_black, cont_rect);
        }
        else
        {
            surface.put_rect(cont_border, WHITE);
            surface.put_rect(cont_background, BLACK);
            surface.put_image(cont_white, cont_rect);
        }
        
        
        surface.flip();
        surface.unlock();

        delay(10);
    }
}


void set_images(Image & turn, Image & point, Image & point_empty,
                Image & point_black, Image & point_white, Rect & turn_rect,
                Rect & turn_background, Rect & turn_border,
                Rect & point_background, Rect & point_border, Rect & point_rect,
                Rect & point_white_rect, Rect & point_black_rect,
                Rect & point_empty_rect)
{
    //turn stuff
    turn_rect.x = 10;
    turn_rect.y = HEIGHT - turn_rect.h - 20;

    // turn background
    turn_background.x = 0;
    turn_background.y = turn_rect.y - 10;
    turn_background.h = turn_rect.h + 20;
    turn_background.w = turn_rect.w + 150;

    // turn_border
    turn_border.x = turn_background.x;
    turn_border.y = turn_background.y - 2;
    turn_border.h = turn_background.h + 4;
    turn_border.w = turn_background.w + 2;

    // point_background
    point_background.x = WIDTH - turn_background.w - 20;
    point_background.y = 15;
    point_background.h = turn_background.h * 4;
    point_background.w = turn_background.w;

    // point_border
    point_border.x = point_background.x - 2;
    point_border.y = point_background.y - 2;
    point_border.h = point_background.h + 4;
    point_border.w = point_background.w + 4;

    // point_rect
    point_rect.x = WIDTH - turn_background.w;
    point_rect.y = 25;

    // point_white_rect
    point_white_rect.x = point_rect.x;
    point_white_rect.y = point_rect.y + point_rect.h + 40;

    // point_black_rect
    point_black_rect.x = point_white_rect.x;
    point_black_rect.y = point_white_rect.y + point_white_rect.h;

    // point_empby_rect
    point_empty_rect.x = point_black_rect.x;
    point_empty_rect.y = point_black_rect.y + point_black_rect.h;
    
}
