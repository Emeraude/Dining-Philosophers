/*
** gui.c for  in /home/broggi_t/projet/Dining-Philosophers
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Wed Feb 25 06:27:11 2015 broggi_t
** Last update Wed Feb 25 07:50:11 2015 duques_g
*/

#ifdef BONUS
# include <SDL/SDL.h>
# include "philosophe.h"

static int	display_rect(SDL_Surface *screen,
			     t_size *size,
			     SDL_Rect *pos,
			     Uint32 color)
{
  SDL_Surface	*rect;

  if (!(rect = SDL_CreateRGBSurface(SDL_HWSURFACE, size->w, size->h,
				    32, 0, 0, 0, 0))
      || SDL_FillRect(rect, NULL, color) != 0
      || SDL_BlitSurface(rect, NULL, screen, pos))
    return (0);
  SDL_FreeSurface(rect);
  return (1);
}

static t_size	*init_size(t_size *size, int h, int w)
{
  size->h = h;
  size->w = w;
  return (size);
}

static int	display_philo(SDL_Surface *screen,
			      t_data *data,
			      t_data *first,
			      t_conf *conf)
{
  SDL_Rect	pos;
  int		i;
  int		bar_size;
  t_size	size;
  const Uint32	colors[] = {0xff0000, 0x00ff00, 0xffff00, 0x0000ff,
			    0xff00ff, 0x00ffff, 0xaaaaaa, 0xffffff};

  i = -1;
  while (++i < conf->nb_philo && (pos.x = 150 + 20 * (i + 1)) <= 640)
    {
      pos.y = 10;
      if (!display_rect(screen, init_size(&size, 460, 20), &pos, 0xffffff))
	return (0);
      ++pos.x;
      ++pos.y;
      if (!display_rect(screen, init_size(&size, 458, 18), &pos, 0))
	return (0);
      bar_size = (conf->nb_food - first[i].eaten_plates) * 458;
      bar_size = (458 - bar_size / MAX(conf->nb_food, 1)) * conf->nb_philo;
      pos.y = 469 - bar_size * 2 / 3;
      if (!display_rect(screen, init_size(&size, bar_size * 2 / 3, 18), &pos,
			colors[data->phi_st[i].id % COUNT_ARRAY(colors)]))
	return (0);
    }
  return (1);
}


static int	fill_gui(SDL_Surface *screen,
			 t_data *data,
			 t_conf *conf,
			 t_stat *stat)
{
  t_size	size;
  SDL_Rect	pos;

  pos.x = 10;
  pos.y = 10;
  size.h = 460;
  size.w = 20;
  if (!display_rect(screen, &size, &pos, 0xffffff))
    return (0);
  pos.x = 11;
  pos.y = 11;
  size.h = 458 - (conf->nb_food - stat->total_eaten) * 458 / conf->nb_food;
  size.w = 18;
  if (!display_rect(screen, &size, &pos, 0))
    return (0);
  return (display_philo(screen, data, data->phi_st, conf));
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
	  || !fill_gui(screen, data, data->conf, data->stat)
	  || SDL_Flip(screen) == -1)
	break ;
      SDL_Delay(20);
    }
  SDL_FreeSurface(screen);
  SDL_Quit();
  return (NULL);
}

#endif
