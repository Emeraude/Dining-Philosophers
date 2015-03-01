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
# include "bonus.h"

static int	display_one_philo(SDL_Surface *screen,
				  t_data *data,
				  int i,
				  Uint32 color)
{
  SDL_Rect	pos;
  t_size	size;
  int		bar_size;
  int		food;
  int		philo;

  philo = data->conf->nb_philo;
  food = data->conf->nb_food;
  pos.y = 10;
  pos.x = 150 + BAR_WIDTH * (i + 1);
  if (!display_one_empty_bar(screen,
			     init_size(&size, WIN_HEIGHT - 20, BAR_WIDTH),
			     &pos))
    return (0);
  bar_size = (food - data->phi_st[i].eaten_plates) * (WIN_HEIGHT - 22);
  bar_size = (WIN_HEIGHT - 22 - bar_size / MAX(food, 1)) * philo;
  pos.y = WIN_HEIGHT - 11 - bar_size * 2 / 3;
  return (display_rect(screen,
		       init_size(&size, bar_size * 2 / 3, BAR_WIDTH - 2)
		       , &pos, color));
}

static int	display_philos(SDL_Surface *screen,
			       t_data *data,
			       t_conf *conf)
{
  SDL_Rect	pos;
  int		i;
  const Uint32	colors[] = {0xff0000, 0x00ff00, 0xffff00, 0x0000ff,
  			    0xff00ff, 0x00ffff, 0xaaaaaa, 0xffffff};

  i = -1;
  while (++i < conf->nb_philo && (pos.x = 150 + BAR_WIDTH * (i + 1)) <= 640)
    if (!display_one_philo(screen, data, i, colors[i % COUNT_ARRAY(colors)]))
      return (0);
  return (1);
}

static int	fill_gui(SDL_Surface *screen,
			 t_data *data,
			 t_conf *conf,
			 t_stat *stat)
{
  t_size	size;
  int		food;
  int		eaten;
  SDL_Rect	pos;

  food = conf->nb_food;
  eaten = stat->total_eaten;
  pos.x = 10;
  pos.y = 10;
  size.h = WIN_HEIGHT - 20;
  size.w = BAR_WIDTH;
  if (!display_rect(screen, &size, &pos, 0xffffff))
    return (0);
  pos.x++;
  pos.y++;
  size.h = WIN_HEIGHT - 22 - (food - eaten) * (WIN_HEIGHT - 22) / food;
  size.w = BAR_WIDTH - 2;
  if (!display_rect(screen, &size, &pos, 0))
    return (0);
  return (display_philos(screen, data, conf));
}

void		*launch_gui(void *arg)
{
  SDL_Event	event;
  SDL_Surface	*screen;
  t_data	*data;

  data = (t_data *)arg;
  if (SDL_Init(SDL_INIT_VIDEO) == -1
      || !(screen = SDL_SetVideoMode(WIN_WIDTH, WIN_HEIGHT,
  				     32, SDL_HWSURFACE)))
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
