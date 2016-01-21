//
// Created by julien athomas on 17/04/15.
//

#include "snake.h"

extern t_snake *snake;

bool    isSnakeAlive()
{
   display->get_direction();
    return (snake->alive);
}

void    left()
{
    snake->direction = LEFT;
}

void    right()
{
    snake->direction = RIGHT;
}

void    up()
{
    snake->direction = UP;
}

void    down()
{
    snake->direction = DOWN;
}

bool    check_collision()
{
    t_node  *tmp;

    if (snake->body->x < 0 || snake->body->x >= 50 ||
        snake->body->y < 0 || snake->body->y >= 50)
        return (true);
    tmp = snake->body->next;
    while (tmp)
    {
        if (tmp->x == snake->body->x && tmp->y == snake->body->y)
            return (true);
        tmp = tmp->next;
    }
    return (false);
}

bool    check_food()
{
    if (display->map[snake->body->y * 50 + snake->body->x] == FOOD)
    {
        display->map[snake->body->y * 50 + snake->body->x] = EMPTY;
        display->map[rand() % 2500] = FOOD;
        display->score += 1;
        return (true);
    }
    return (false);
}

void    change_coord(t_node *tmp, int x, int y)
{
    tmp->x = x;
    tmp->y = y;
}

void    increase_size()
{
    t_node  *tmp;
    t_node  *new;

    if ((tmp = snake->body) == NULL)
    {
        fprintf(stderr, "You can't increase the size on the snake if he is not initialized\n");
        exit(1);
    }
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    if ((new = malloc(sizeof(t_node))) == NULL)
    {
        perror("malloc");
        exit(1);
    }
    change_coord(new, tmp->dir == LEFT ? tmp->x + 1 : tmp->dir == RIGHT ? tmp->x - 1 : tmp->x,
        tmp->dir == UP ? tmp->y + 1 : tmp->dir == DOWN ? tmp->y - 1 : tmp->y);
    new->next = NULL;
    new->dir = tmp->dir;
    tmp->next = new;
}

void    decrease_size()
{
    t_node  *tmp;
    t_node  *prev;

    if ((tmp = snake->body) == NULL)
    {
        fprintf(stderr, "You can't increase the size on the snake if he is not initialized\n");
        exit(1);
    }
    if (!tmp->next)
    {
        fprintf(stderr, "You suppressed the head of your snake, and he didn't really liked it !\n");
        exit(1);
    }
    while (tmp->next)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    free(tmp);
    prev->next = NULL;
}

void    init_snake_core()
{
    if ((snake->body = malloc(sizeof(t_node))) == NULL)
    {
        perror("malloc");
        exit(1);
    }
    snake->body->x = 10;
    snake->body->y = 10;
    snake->body->dir = RIGHT;
    snake->body->next = NULL;
}

void	speed(t_speed speed)
{
  if (speed == SLOW)
    usleep(100000);
  else if (speed == MEDIUM)
    usleep(50000);
  else if (speed == FAST)
    usleep(20000);
  else
    usleep(10000);
}

void    move(int direction)
{
    t_dir   dir;
    t_dir   prev_dir;
    t_dir   tmp_dir;
    t_node  *tmp;

    dir = (t_dir)direction;
    tmp = snake->body;
    prev_dir = (dir ? dir : tmp->dir);
    while (tmp)
    {
        tmp->x += (prev_dir == RIGHT ? 1 : prev_dir == LEFT ? -1 : 0);
        tmp->y += (prev_dir == DOWN ? 1 : prev_dir == UP ? -1 : 0);
        tmp_dir = prev_dir;
        prev_dir = tmp->dir;
        tmp->dir = tmp_dir;
        tmp = tmp->next;
    }
}

void    *init_snake()
{
  int	i;

    if ((snake = malloc(sizeof(t_snake))) == NULL)
    {
        perror("malloc");
        return (NULL);
    }
    snake->direction = DOWN;
    snake->alive = true;
    snake->check_collision = &check_collision;
    snake->check_food = &check_food;
    snake->increase_size = &increase_size;
    snake->decrease_size = &decrease_size;
    snake->move = &move;
    snake->speed = &speed;
    init_snake_core();
    for (i = 0; i < 3; ++i)
        increase_size();
    return (snake);
}
