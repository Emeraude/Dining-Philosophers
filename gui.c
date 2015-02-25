/*
** gui.c for  in /home/broggi_t/projet/Dining-Philosophers
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Wed Feb 25 06:27:11 2015 broggi_t
** Last update Wed Feb 25 07:47:09 2015 duques_g
*/

#ifdef BONUS
# include <SDL/SDL.h>
# include "philosophe.h"

static int	display_philo(SDL_Surface *screen, t_data *data)
{
  SDL_Surface	*rect;
  SDL_Rect	pos;
  int		i;
  int		bar_size;
  Uint32	colors[] = {0xff0000,
			    0x00ff00,
			    0xffff00,
			    0x0000ff,
			    0xff00ff,
			    0x00ffff,
			    0xaaaaaa,
			    0xffffff};

  i = -1;
  while (++i < data->conf->nb_philo
	 && (pos.x = 150 + 20 * (i + 1)) <= 640)
    {
      pos.y = 10;
      if (!(rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 20, 460, 32, 0, 0, 0, 0))
	  || SDL_FillRect(rect, NULL, 0xffffffff) != 0
	  || SDL_BlitSurface(rect, NULL, screen, &pos))
	return (0);
      SDL_FreeSurface(rect);
      ++pos.x;
      pos.y = 11;
      if (!(rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 18, 458, 32, 0, 0, 0, 0))
	  || SDL_FillRect(rect, NULL, 0) != 0
	  || SDL_BlitSurface(rect, NULL, screen, &pos))
	return (0);
      int total_food = data->stat->total_eaten;
      int food_philo = data->phi_st[i].eaten_plates;
      SDL_FreeSurface(rect);
      bar_size = total_food / food_philo;
      /* bar_size = (458 - (data->conf->nb_food - data->phi_st[i].eaten_plates) * 458 / data->conf->nb_food) * data->conf->nb_philo * 2 / 3; */
      /* bar_size = (458 / (data->stat->total_eaten / data->phi_st[i].eaten_plates || 1)) /\* * (data->stat->total_eaten / data->phi_st[i].eaten_plates || 1))*\/ * (data->phi_st[i].eaten_plates);// * data->phi_st[i].eaten_plates; */
      pos.y = 469 - bar_size;
      if (!(rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 18, bar_size, 32, 0, 0, 0, 0))
	  || SDL_FillRect(rect, NULL, colors[data->phi_st[i].id % (sizeof(colors) / sizeof(Uint32))]) != 0
	  || SDL_BlitSurface(rect, NULL, screen, &pos))
	return (0);
      SDL_FreeSurface(rect);
    }
  return (1);
}


static int	fill_gui(SDL_Surface *screen, t_data *data)
{
  SDL_Surface	*rect;
  SDL_Rect	pos;

  pos.x = 10;
  pos.y = 10;
  if (!(rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 20, 460, 32, 0, 0, 0, 0))
      || SDL_FillRect(rect, NULL, 0xffffffff) != 0
      || SDL_BlitSurface(rect, NULL, screen, &pos))
    return (0);
  SDL_FreeSurface(rect);
  pos.x = 11;
  pos.y = 11;
  if (!(rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 18, 458 - (data->conf->nb_food - data->stat->total_eaten) * 458 / data->conf->nb_food, 32, 0, 0, 0, 0))
      || SDL_FillRect(rect, NULL, 0) != 0
      || SDL_BlitSurface(rect, NULL, screen, &pos))
    return (0);
  SDL_FreeSurface(rect);
  return (display_philo(screen, data));
}

void		*launch_gui(void *arg)
{
  SDL_Event	event;
  SDL_Surface	*screen;
  t_data	*data;

  data = (t_data *)arg;
  if (SDL_Init(SDL_INIT_VIDEO) == -1
      || !(screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE)))
    return (NULL);
  SDL_WM_SetCaption("Dining Philosophers", NULL);
  while (1)
    {
      SDL_PollEvent(&event);
      if (event.type == SDL_QUIT
	  || (event.type == SDL_KEYDOWN
	      && event.key.keysym.sym == SDLK_ESCAPE)
	  || !fill_gui(screen, data)
	  || SDL_Flip(screen) == -1)
	break ;
      SDL_Delay(20);
    }
  SDL_FreeSurface(screen);
  SDL_Quit();
  return (NULL);
}

#endif
