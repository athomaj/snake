//
// Created by julien athomas on 17/04/15.
//

#include "snake.h"

t_dir     get_event()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                printf("The game has ended\n");
                SDL_Quit();
                exit(0);
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    printf("The game has ended\n");
                    SDL_Quit();
                    exit(0);
                }
                else if (event.key.keysym.sym == SDLK_RIGHT)
                    return (RIGHT);
                else if (event.key.keysym.sym == SDLK_LEFT)
                    return (LEFT);
                else if (event.key.keysym.sym == SDLK_DOWN)
                    return (DOWN);
                else if (event.key.keysym.sym == SDLK_UP)
                    return (UP);
                break;
        }
    }
    return (UNKNOWN);
}

void    display_snake(t_snake *snake)
{
    t_node  *tmp;

    tmp = snake->body;
    while (tmp)
    {
        display->pos.x = tmp->x * 10;
        display->pos.y = tmp->y * 10;
        SDL_BlitSurface(display->body, NULL, display->screen, &(display->pos));
        tmp = tmp->next;
    }
    SDL_Flip(display->screen);
}

void    display_map()
{
    int i;

    SDL_FillRect(display->screen, NULL, 0x000000);
    if (display->initMap == true)
    {
        display->initMap = false;
        if ((display->map = malloc(2500)) == NULL)
        {
            perror("malloc");
            exit(1);
        }
        memset(display->map, EMPTY, 2500);
        display->map[rand() % 2500] = FOOD;
    }
    for (i=0; i < 2500; ++i)
        if (display->map[i] == FOOD)
        {
            display->pos.x = i % 50 * 10;
            display->pos.y = i / 50 * 10;
            SDL_BlitSurface(display->objet, NULL, display->screen, &(display->pos));
        }
    display_snake(snake);
    SDL_Flip(display->screen);
}

void    *init_display()
{
    srand(time(NULL));
    if ((display = malloc(sizeof(t_display))) == NULL)
    {
        perror("malloc");
        return (NULL);
    }
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        printf("Can't init SDL:  %s\n", SDL_GetError());
        return (NULL);
    }
    display->screen = SDL_SetVideoMode(500, 500, 16, SDL_HWSURFACE);
    if (display->screen == NULL)
    {
        printf("Can't set video mode: %s\n", SDL_GetError());
        return (NULL);
    }
    display->get_event = &get_event;
    display->display_map = &display_map;
    display->display_snake = &display_snake;
    display->initMap = true;
    display->objet = SDL_CreateRGBSurface(0, 10, 10, 32, 255, 0, 0, 0);
    display->body = SDL_CreateRGBSurface(0, 10, 10, 32, 0, 255, 0, 0);
    display->score = 0;
    SDL_FillRect(display->objet, NULL, SDL_MapRGB(display->objet->format, 255, 255, 255));
    SDL_FillRect(display->body, NULL, SDL_MapRGB(display->objet->format, 255, 255, 255));
    return (display);
}
