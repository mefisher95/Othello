#include "Gameover.h"

void game_over(Surface & surface, Event & event, Board & board,
               KeyPressed & keypress, bool & exit)
{
    Image Background("images/wood.jpg");
    Rect backrect = Background.getRect();

    Font menu_font("fonts/FreeMonoBold.ttf", 80);
    Image GAME_OVER(menu_font.render("Game Over!", WHITE));
    Rect GO_rect = GAME_OVER.getRect();
    GO_rect.x = WIDTH / 2 - GO_rect.w / 2;
    GO_rect.y = GO_rect.h;

    Rect title_background;
    title_background.x = GO_rect.x - 150;
    title_background.y = GO_rect.y - 30;
    title_background.h = GO_rect.h + 60;
    title_background.w = GO_rect.w + 300;

    Rect title_border;
    title_border.x = title_background.x - 3;
    title_border.y = title_background.y - 3;
    title_border.w = title_background.w + 6;
    title_border.h = title_background.h + 6;

    Rect final_score;
    final_score.x = title_background.x;
    final_score.y = title_background.y + title_background.h + 50;
    final_score.h = title_background.h + 20;
    final_score.w = title_background.w;

    Rect final_score_border;
    final_score_border.x = final_score.x - 3;
    final_score_border.y = final_score.y - 3;
    final_score_border.h = final_score.h + 6;
    final_score_border.w = final_score.w + 6;


    Font font("fonts/FreeMonoBold.ttf", 40);
    
    Image point(font.render("Points:", WHITE));
    Rect point_rect = point.getRect();
    point_rect.x = final_score.x + 20;
    point_rect.y = final_score.y;
    
    Image point_white(font.render("White: ", WHITE));
    Rect point_white_rect = point_white.getRect();
    point_white_rect.x = point_rect.x;
    point_white_rect.y = point_rect.y + point_rect.h;
    
    Image point_black(font.render("Black: ", WHITE));
    Rect point_black_rect = point_black.getRect();
    point_black_rect.x = point_white_rect.x;
    point_black_rect.y = point_white_rect.y + point_white_rect.h;

    int scr_white_int, scr_black_int;
    char str_white[3];
    char str_black[3];

    scr_black_int = board.num_count(1);
    scr_white_int = board.num_count(2);
    
    sprintf(str_black, "%d", scr_black_int);
    sprintf(str_white, "%d", scr_white_int);

    Image scr_black(font.render(str_black, WHITE));
    Rect scr_black_rect = scr_black.getRect();
    scr_black_rect.x = point_black_rect.x + point_black_rect.w;
    scr_black_rect.y = point_black_rect.y;

    Image scr_white(font.render(str_white, WHITE));
    Rect scr_white_rect = scr_white.getRect();
    scr_white_rect.x = point_white_rect.x + point_white_rect.w;
    scr_white_rect.y = point_white_rect.y;

    Image white_wins(font.render("White Wins!", WHITE));
    Image black_wins(font.render("Black Wins!", WHITE));
    Rect wins_rect = black_wins.getRect();
    wins_rect.x = final_score.x + final_score.w - wins_rect.w - 50;
    wins_rect.y = final_score.y + 50;

    Image cont_white(font.render("Continue", WHITE));
    Image cont_black(font.render("Continue", BLACK));
    Rect cont_rect = cont_black.getRect();
    cont_rect.x = WIDTH / 2 - cont_rect.w / 2;
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
    
    while(1)
    {
        keypress = get_keypressed();
        
        if (event.poll() && event.type() == QUIT)
        {
            exit = true;
            return;
        }
        if (keypress[ESC] || keypress[SPACE] || keypress[ENTER]) return;

        if (mouse_x() > cont_rect.x && mouse_x() < cont_rect.x + cont_rect.w &&
            mouse_y() > cont_rect.y && mouse_y() < cont_rect.y + cont_rect.h &&
            mouse_left())
            return;
        
        surface.lock();
        
        surface.put_image(Background, backrect);
        surface.put_rect(title_border, WHITE);
        surface.put_rect(title_background, BLACK);
        surface.put_image(GAME_OVER, GO_rect);
        surface.put_rect(final_score_border, WHITE);
        surface.put_rect(final_score, BLACK);
        surface.put_image(point, point_rect);
        surface.put_image(point_white, point_white_rect);
        surface.put_image(point_black, point_black_rect);
        surface.put_image(scr_white, scr_white_rect);
        surface.put_image(scr_black, scr_black_rect);

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
        
        if (scr_black_int > scr_white_int)
            surface.put_image(black_wins, wins_rect);
        else surface.put_image(white_wins, wins_rect);
        
        surface.flip();
        surface.unlock();
        delay(10);
    }

    board.make();
}

                
