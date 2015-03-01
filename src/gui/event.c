/*
** event.c for  in /home/broggi_t/projet/Dining-Philosophers/src/gui
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Sun Mar  1 21:45:14 2015 broggi_t
** Last update Sun Mar  1 21:45:14 2015 broggi_t
*/

#ifdef BONUS
# include <SDL/SDL.h>
# include "philosophe.h"

void	manage_event(SDL_Event *event, t_data *data)
{
  if (event->key.keysym.sym == SDLK_f)
    {
      pthread_mutex_lock(&data->stat->food_lock);
      data->stat->food += data->conf->nb_food / 20;
      pthread_mutex_unlock(&data->stat->food_lock);
    }
  else if (event->key.keysym.sym == SDLK_s)
    {
      pthread_mutex_lock(&data->stat->food_lock);
      data->stat->food -= data->conf->nb_food / 20;
      pthread_mutex_unlock(&data->stat->food_lock);
    }
}

#endif
