#include "Tutorial.h"

void tutorial(Surface & surface, Event & event, Board & board,
              KeyPressed & keypress, bool & exit)
{
    Font font("fonts/FreeMonoBold.ttf", 40);
    Image turn(font.render("Turn: ", WHITE));
    Rect turn_rect = turn.getRect();
    Rect turn_background;
    Rect turn_border;

    Image Background("images/wood.jpg");
    Rect backrect = Background.getRect();

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

    Font explain("fonts/FreeMonoBold.ttf", 30);

    
    Image rules(font.render("- Rules -", WHITE));
    Rect rules_rect = rules.getRect();
    rules_rect.x = WIDTH - rules_rect.h - 220;
    rules_rect.y = board.board_y();
    
    Image rule0(explain.render("1.Place a piece to ", WHITE));
    Rect rule0_rect = rule0.getRect();
    rule0_rect.x = WIDTH - rule0_rect.w;
    rule0_rect.y = rules_rect.y + rules_rect.h + 20;

    Image rule1(explain.render("  capture another", WHITE));
    Rect rule1_rect = rule1.getRect();
    rule1_rect.x = rule0_rect.x;
    rule1_rect.y = rule0_rect.y + rule0_rect.h;
    board.make();

    Image rule2(explain.render("2.Every move must", WHITE));
    Rect rule2_rect = rule2.getRect();
    rule2_rect.x = rule1_rect.x;
    rule2_rect.y = rule1_rect.y + rule1_rect.h + 20;

    Image rule3(explain.render("  make a caputre", WHITE));
    Rect rule3_rect = rule3.getRect();
    rule3_rect.x = rule2_rect.x;
    rule3_rect.y = rule2_rect.y + rule2_rect.h;

    Image rule4(explain.render("3.If you can't", WHITE));
    Rect rule4_rect = rule4.getRect();
    rule4_rect.x = rule3_rect.x;
    rule4_rect.y = rule3_rect.y + rule3_rect.h + 20;

    Image rule5(explain.render("  move, you skip", WHITE));
    Rect rule5_rect = rule5.getRect();
    rule5_rect.x = rule4_rect.x;
    rule5_rect.y = rule4_rect.y + rule4_rect.h;

    Image rule6(explain.render("  your turn", WHITE));
    Rect rule6_rect = rule6.getRect();
    rule6_rect.x = rule5_rect.x;
    rule6_rect.y = rule5_rect.y + rule5_rect.h;

    Image rule7(explain.render("4.Who ever has the", WHITE));
    Rect rule7_rect = rule7.getRect();
    rule7_rect.x = rule6_rect.x;
    rule7_rect.y = rule6_rect.y + rule6_rect.h + 20;

    Image rule8(explain.render("  most pieces", WHITE));
    Rect rule8_rect = rule8.getRect();
    rule8_rect.x = rule7_rect.x;
    rule8_rect.y = rule7_rect.y + rule7_rect.h;

    Image rule9(explain.render("  wins the game!", WHITE));
    Rect rule9_rect = rule9.getRect();
    rule9_rect.x = rule8_rect.x;
    rule9_rect.y = rule8_rect.y + rule8_rect.h;

    Rect rules_background;
    rules_background.x = rule0_rect.x - 10;
    rules_background.y = rules_rect.y;
    rules_background.w = WIDTH;
    rules_background.h = rules_rect.h + rule0_rect.h + rule1_rect.h +
        rule2_rect.h + rule3_rect.h + rule4_rect.h + rule5_rect.h + rule5_rect.h
        + rule6_rect.h + rule7_rect.h + rule8_rect.h + rule9_rect.h + 60;

    Rect rules_border;
    rules_border.x = rules_background.x - 2;
    rules_border.y = rules_background.y - 2;
    rules_border.h = rules_background.h + 4;
    rules_border.w = WIDTH;

    Image cont_white(explain.render("Return", WHITE));
    Image cont_black(explain.render("Return", BLACK));
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

        surface.lock();
        surface.put_image(Background, backrect);
        board.draw();
        surface.put_rect(turn_border, WHITE);
        surface.put_rect(turn_background, BLACK);

        
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

        surface.put_rect(rules_border, WHITE);
        surface.put_rect(rules_background, BLACK);

        surface.put_image(rules, rules_rect);
        surface.put_image(rule0, rule0_rect);
        surface.put_image(rule1, rule1_rect);
        surface.put_image(rule2, rule2_rect);
        surface.put_image(rule3, rule3_rect);
        surface.put_image(rule4, rule4_rect);
        surface.put_image(rule5, rule5_rect);
        surface.put_image(rule6, rule6_rect);
        surface.put_image(rule7, rule7_rect);
        surface.put_image(rule8, rule8_rect);
        surface.put_image(rule9, rule9_rect);

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
        
        if (ai_count == 70 && board.turn() == 1 && board.is_moveable(1))
        {
            board.ai(1);
            ai_count = 0;
        }
        if (ai_count == 70 && board.turn() == 2 && board.is_moveable(2))
        {
            board.ai(2);
            ai_count = 0;
        }

        ++ai_count;
    }
}
