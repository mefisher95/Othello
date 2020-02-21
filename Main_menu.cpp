#include "Main_menu.h"

void main_menu(Surface & surface, Event & event, KeyPressed & keypress,
               bool & play, bool & temp, bool & help, bool & exit)
{
    Image Background("images/wood.jpg");
    Rect backrect = Background.getRect();
    Font title_font("fonts/FreeMonoBold.ttf", 80);
    Image title(title_font.render("- Othello -", WHITE));
    Rect title_rect = title.getRect();
    title_rect.x = WIDTH / 2 - title_rect.w / 2;
    title_rect.y = title_rect.h;

    Font sig_f("fonts/FreeMonoBold.ttf", 30);
    Image sig(sig_f.render("Michael Fisher, 2019", GRAY));
    Rect sig_rect = sig.getRect();
    sig_rect.x = WIDTH / 2 - sig_rect.w / 2;
    sig_rect.y = HEIGHT - sig_rect.h;

    Rect sig_background;
    sig_background.x = sig_rect.x - 20;
    sig_background.y = sig_rect.y - 5;
    sig_background.w = sig_rect.w + 40;
    sig_background.h = HEIGHT;

    Rect sig_border;
    sig_border.x = sig_background.x - 3;
    sig_border.y = sig_background.y - 3;
    sig_border.w = sig_background.w + 6;
    sig_border.h = HEIGHT;

    Rect title_background;
    title_background.x = title_rect.x - 150;
    title_background.y = title_rect.y - 30;
    title_background.h = title_rect.h + 60;
    title_background.w = title_rect.w + 300;

    Rect title_border;
    title_border.x = title_background.x - 3;
    title_border.y = title_background.y - 3;
    title_border.w = title_background.w + 6;
    title_border.h = title_background.h + 6;

    Font options_font("fonts/FreeMonoBold.ttf", 50);
    Image play_gray(options_font.render("Single player", GRAY));
    Image temp_gray(options_font.render("Multiplayer", GRAY));
    Image help_gray(options_font.render("Tutorial", GRAY));
    Image exit_gray(options_font.render("Exit", GRAY));

    Image play_white(options_font.render("Single player", WHITE));
    Image temp_white(options_font.render("Multiplayer", WHITE));
    Image help_white(options_font.render("Tutorial", WHITE));
    Image exit_white(options_font.render("Exit", WHITE));
    
    Rect play_rect = play_white.getRect();
    Rect temp_rect = temp_gray.getRect();
    Rect help_rect = help_gray.getRect();
    Rect exit_rect = exit_gray.getRect();
    
    play_rect.x = WIDTH / 2 - play_rect.w / 2;
    play_rect.y = title_border.y + title_border.h + 80;
    temp_rect.x = WIDTH / 2 - temp_rect.w / 2;
    temp_rect.y = play_rect.y + play_rect.h;
    help_rect.x = WIDTH / 2 - help_rect.w / 2;
    help_rect.y = temp_rect.y + temp_rect.h;
    exit_rect.x = WIDTH / 2 - exit_rect.w / 2;
    exit_rect.y = help_rect.y + help_rect.h;

    Rect options_rect;
    options_rect.x = play_rect.x - 50;
    options_rect.y = play_rect.y - 10;
    options_rect.w = play_rect.w + 100;
    options_rect.h = play_rect.h + temp_rect.h + help_rect.h + exit_rect.h + 20;

    Rect options_background;
    options_background.x = options_rect.x - 3;
    options_background.y = options_rect.y - 3;
    options_background.h = options_rect.h + 6;
    options_background.w = options_rect.w + 6;

    int menu_option = 0;
    int key_press_delay = 0;
    bool trigger = false;
    
    while(1)
    {
        
        keypress = get_keypressed();
        
        if (event.poll() && event.type() == QUIT)
        {
            exit = true;
            return;
        }

        //======================================================================
        // -- HIGHLIGHT MENU OPTIONS WITH USER INPUT
        //======================================================================

        // highlight options using keyboard
        if (key_press_delay > 0 && key_press_delay < 10) ++key_press_delay;
        else key_press_delay = 0;
        
        if ((keypress[UPARROW] || keypress[w]) && menu_option > 0 &&
            key_press_delay == 0)
        {
            --menu_option;
            ++key_press_delay;
        }
        if ((keypress[DOWNARROW] || keypress[s]) && menu_option < 3 &&
            key_press_delay == 0)
        {
            ++menu_option;
            ++key_press_delay;
        }
        if (keypress[ESC]) menu_option = 3;

        // highlight options using mouse
        if (mouse_x() > play_rect.x && mouse_x() < play_rect.x + play_rect.w &&
            mouse_y() > play_rect.y && mouse_y() < play_rect.y + play_rect.h)
            menu_option = 0;
        if (mouse_x() > temp_rect.x && mouse_x() < temp_rect.x + temp_rect.w &&
            mouse_y() > temp_rect.y && mouse_y() < temp_rect.y + temp_rect.h)
            menu_option = 1;
        if (mouse_x() > help_rect.x && mouse_x() < help_rect.x + help_rect.w &&
            mouse_y() > help_rect.y && mouse_y() < help_rect.y + help_rect.h)
            menu_option = 2;
        if (mouse_x() > exit_rect.x && mouse_x() < exit_rect.x + exit_rect.w &&
            mouse_y() > exit_rect.y && mouse_y() < exit_rect.y + exit_rect.h)
            menu_option = 3;

        
        
        //======================================================================
        // -- SURFACE PRINTING
        //======================================================================
        
        surface.lock();
        surface.put_image(Background, backrect);
        surface.put_rect(title_border, WHITE);
        surface.put_rect(title_background, BLACK);
        surface.put_image(title, title_rect);

        surface.put_rect(options_background, WHITE);
        surface.put_rect(options_rect, BLACK);

        surface.put_rect(sig_border, WHITE);
        surface.put_rect(sig_background, BLACK);
        surface.put_image(sig, sig_rect);

        switch (menu_option)
        {
            case 0:
                surface.put_image(play_white, play_rect);
                surface.put_image(temp_gray, temp_rect);
                surface.put_image(help_gray, help_rect);
                surface.put_image(exit_gray, exit_rect);
                break;
            case 1:
                surface.put_image(play_gray, play_rect);
                surface.put_image(temp_white, temp_rect);
                surface.put_image(help_gray, help_rect);
                surface.put_image(exit_gray, exit_rect);
                break;
            case 2:
                surface.put_image(play_gray, play_rect);
                surface.put_image(temp_gray, temp_rect);
                surface.put_image(help_white, help_rect);
                surface.put_image(exit_gray, exit_rect);
                break;
            case 3:
                surface.put_image(play_gray, play_rect);
                surface.put_image(temp_gray, temp_rect);
                surface.put_image(help_gray, help_rect);
                surface.put_image(exit_white, exit_rect);
                break;
        }
        
        surface.flip();
        surface.unlock();

        delay(10);

        //======================================================================
        // -- SELECT MENU OPTIONS FROM USER INPUT
        //======================================================================
        
        // select using keyboard
        if ((keypress[SPACE] || keypress[ENTER]) && event.type() == KEYDOWN)
        {
            trigger = true;
        }
        
        if (event.type() == KEYUP && trigger)
        {
            switch(menu_option)
            {
                case 0:
                    play = true;
                    temp = false;
                    help = false;
                    exit = false;
                    return;
                case 1:
                    play = false;
                    temp = true;
                    help = false;
                    exit = false;
                    return;
                case 2:
                    play = false;
                    temp = false;
                    help = true;
                    exit = false;
                    return;
                case 3:
                    play = false;
                    temp = false;
                    help = false;
                    exit = true;
                    return;
            }
        }

        // select using mouse
        if (mouse_left() &&
            mouse_x() > play_rect.x && mouse_x() < play_rect.x + play_rect.w &&
            mouse_y() > play_rect.y && mouse_y() < play_rect.y + play_rect.h)
        {
            play = true;
            temp = false;
            help = false;
            exit = false;
            return;
        }
        if (mouse_left() &&
            mouse_x() > temp_rect.x && mouse_x() < temp_rect.x + temp_rect.w &&
            mouse_y() > temp_rect.y && mouse_y() < temp_rect.y + temp_rect.h)
        {
            play = false;
            temp = true;
            help = false;
            exit = false;
             return;
        }
        if (mouse_left() &&
            mouse_x() > help_rect.x && mouse_x() < help_rect.x + help_rect.w &&
            mouse_y() > help_rect.y && mouse_y() < help_rect.y + help_rect.h)
        {
            play = false;
            temp = false;
            help = true;
            exit = false;
            return;
        }
        if (mouse_left() &&
            mouse_x() > exit_rect.x && mouse_x() < exit_rect.x + exit_rect.w &&
            mouse_y() > exit_rect.y && mouse_y() < exit_rect.y + exit_rect.h)
        {
            play = false;
            temp = false;
            help = false;
            exit = true;
            return;
        }
    }
}
