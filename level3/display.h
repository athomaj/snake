//
// Created by julien athomas on 17/04/15.
//

#ifndef SNAKE_JD_DISPLAY_H
# define SNAKE_JD_DISPLAY_H

# include "snake.h"
# define EMPTY 0
# define FOOD 1

void    *init_display();
t_dir     get_event();
void    display_map();

typedef struct  s_display
{
  bool		initMap;
  t_dir       (*get_event)();
  void        (*display_map)();
  void        (*display_snake)(t_snake *);
  SDL_Surface		*screen;
  SDL_Surface   *objet;
  SDL_Surface   *body;
  SDL_Rect      pos;
  size_t			score;
  char			*map;
}               t_display;

t_display   *display;

#endif //SNAKE_JD_DISPLAY_H
