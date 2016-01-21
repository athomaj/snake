#include "display.h"

int main()
{
  t_snake     *snake;
  t_display   *display;
  int        dir;

  display = init_display();
  snake = init_snake();

  while (snake->alive == true)
    {
      display->display_map();
      display->display_snake(snake);
      dir = display->get_event();
      snake->move(dir);
      if (snake->check_collision() == true)
        snake->alive = false;
      if (snake->check_food() == true)
        snake->increase_size();
      snake->speed(SLOW);
    }
  return (0);
}
