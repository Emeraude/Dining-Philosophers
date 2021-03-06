/*
** gui.c for  in /home/broggi_t/projet/Dining-Philosophers
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Wed Feb 25 06:27:11 2015 broggi_t
** Last update Sun Mar  1 23:05:49 2015 duques_g
*/

#ifdef BONUS
# include <SDL/SDL.h>
# include "philosophe.h"
# include "bonus.h"

static int	display_philo_bar(SDL_Surface *screen,
				  t_data *data,
				  int bar_size,
				  Uint32 color)
{
  SDL_Rect	pos;
  t_size	size;
  float		size_rest;
  float		size_eat;
  float		size_think;
  float		total;

  pos.y = WIN_HEIGHT - bar_size - 11 + 3;
  pos.x = 100 + BAR_WIDTH * (data->id + 1) + 1;
  if (!(total = data->eaten_plates + data->hours_slept + data->hours_thought))
    total = 0.1;
  size_rest = bar_size / (total / data->hours_slept);
  size_think = bar_size / (total / data->hours_thought);
  size_eat = bar_size / (total / data->eaten_plates);
  if (!display_rect(screen, init_size(&size, size_rest, BAR_WIDTH - 2),
		    &pos, color & 0x555555))
    return (0);
  pos.y = WIN_HEIGHT - bar_size - 11 + size_rest + 2;
  if (!display_rect(screen, init_size(&size, size_think, BAR_WIDTH - 2),
		    &pos, color & 0xaaaaaa))
    return (0);
  pos.y = WIN_HEIGHT - bar_size - 11 + size_rest + size_think + 1;
  return (!display_rect(screen, init_size(&size, size_eat, BAR_WIDTH - 2),
			&pos, color));
}

static int	display_one_philo(SDL_Surface *screen,
				  t_data *data,
				  int i,
				  Uint32 color)
{
  SDL_Rect	pos;
  t_size	size;
  int		bar_size;
  float		food;
  float		philo;

  philo = data->conf->nb_philo;
  food = data->conf->nb_food;
  pos.y = 10;
  pos.x = 100 + BAR_WIDTH * (i + 1);
  if (!display_one_empty_bar(screen,
			     init_size(&size, BAR_HEIGHT + 2, BAR_WIDTH),
			     &pos))
    return (0);
  bar_size = data->phi_st[i].eaten_plates * (BAR_HEIGHT / (food / philo));
  display_philo_bar(screen, &data->phi_st[i], bar_size, color);
  return (1);
}

static int	display_philos(SDL_Surface *screen,
			       t_data *data,
			       t_conf *conf)
{
  SDL_Rect	pos;
  int		i;
  const Uint32	colors[] = {0xff0000, 0x00ff00, 0xffff00, 0x0000ff,
  			    0xff00ff, 0x00ffff, 0xffffff};

  i = -1;
  while (++i < conf->nb_philo && (pos.x = 150 + BAR_WIDTH * (i + 1)) <= 640)
    if (!display_one_philo(screen, data, i, colors[i % COUNT_ARRAY(colors)]))
      return (0);
  return (1);
}

static int	fill_gui(SDL_Surface *screen, t_data *data)
{
  t_size	size;
  int		food;
  int		eaten;
  SDL_Rect	pos;

  food = MAX(data->conf->nb_food, 1);
  eaten = data->stat->total_eaten;
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
  return (display_philos(screen, data, data->conf));
}

void		*launch_gui(void *arg)
{
  SDL_Event	event;
  SDL_Surface	*screen;

  if (SDL_Init(SDL_INIT_VIDEO) == -1
      || !(screen = SDL_SetVideoMode(WIN_WIDTH, WIN_HEIGHT,
				     32, SDL_HWSURFACE))
      || SDL_FillRect(screen, NULL, 0))
    return (NULL);
  SDL_WM_SetCaption(WIN_TITLE, NULL);
  while (1)
    {
      SDL_PollEvent(&event);
      if (event.type == SDL_QUIT
	  || (event.type == SDL_KEYDOWN
	      && event.key.keysym.sym == SDLK_ESCAPE)
	  || !fill_gui(screen, (t_data *)arg)
	  || SDL_Flip(screen) == -1)
	break ;
      else if (event.type == SDL_KEYDOWN)
	manage_event(&event, (t_data *)arg);
      SDL_Delay(20);
    }
  SDL_FreeSurface(screen);
  SDL_Quit();
  return (NULL);
}

#endif
