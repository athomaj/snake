#include "display.h"

int main()
{
  int direction;
  bool alive = true;

  init();
  while (alive == true)
    {
      display_map();
      display_snake();
      direction = get_direction();
      move(direction);
      if (check_collision() == true)
    	{
    	  alive = false;
    	}
      if (check_food() == true)
    	{
    	  increase_size();
    	}
      speed(SLOW);
    }
  return (0);
}
