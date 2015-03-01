/*
** rect.c for  in /home/broggi_t/projet/Dining-Philosophers/src/gui
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Fri Feb 27 20:32:28 2015 broggi_t
** Last update Fri Feb 27 20:32:28 2015 broggi_t
*/

#ifdef BONUS
# include "philosophe.h"
# include "bonus.h"

int		display_rect(SDL_Surface *screen,
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

int	display_one_empty_bar(SDL_Surface *screen,
				      t_size *size,
				      SDL_Rect *pos)
{
  if (!display_rect(screen, size, pos, 0xffffff))
    return (0);
  size->h -= 2;
  size->w -= 2;
  ++pos->x;
  ++pos->y;
  return (display_rect(screen, size, pos, 0));
}

t_size	*init_size(t_size *size, int h, int w)
{
  size->h = h;
  size->w = w;
  return (size);
}

#endif
