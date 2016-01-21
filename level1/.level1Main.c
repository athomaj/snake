#include "display.h"

int main()
{
  init();
  while (isSnakeAlive() == true)
    {
      display_map();
      display_snake();
      move();
      check_collision();
      check_food();
      speed(SLOW);
    }
  return (0);
}