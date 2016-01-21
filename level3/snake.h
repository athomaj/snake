//
// Created by julien athomas on 16/04/15.
//

#ifndef SNAKE_JD_SNAKE_H
# define SNAKE_JD_SNAKE_H

# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include <SDL/SDL_main.h>
# include <stdbool.h>
# include <time.h>
# include <unistd.h>

# define UNUSED __attribute__((unused))

typedef enum	e_speed
  {
    SLOW,
    MEDIUM,
    FAST,
    EXTREME
  }		t_speed;

typedef enum e_dir
{
    UNKNOWN,
    LEFT,
    RIGHT,
    UP,
    DOWN
}           t_dir;

typedef struct      s_node
{
    int             x;
    int             y;
    t_dir           dir;
    struct s_node   *next;
}                   t_node;

typedef struct  s_snake
{
  bool        (*check_collision)();
  bool        (*check_food)();
  void        (*increase_size)();
  void        (*decrease_size)();
  void        (*move)(t_dir);
  void		(*speed)(t_speed);
  t_dir       direction;
  bool        alive;
  t_node      *body;
}               t_snake;

void    *init_snake();
void    speed(t_speed speed);

t_snake *snake;

# include "display.h"

#endif //SNAKE_JD_SNAKE_H
