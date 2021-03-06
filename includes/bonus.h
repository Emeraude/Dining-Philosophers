/*
** bonus.h for  in /home/broggi_t/projet/Dining-Philosophers/includes
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Sun Mar  1 14:51:16 2015 broggi_t
** Last update Sun Mar  1 14:51:16 2015 broggi_t
*/

#ifndef BONUS_H_
# define BONUS_H_

# ifdef BONUS
#  include <SDL/SDL.h>
#  include "philosophe.h"
#  define COUNT_ARRAY(x)	(sizeof(x) / sizeof(*x))

#  define WIN_TITLE	"Dining Philosophers"
#  define WIN_WIDTH	640
#  define WIN_HEIGHT	480
#  define BAR_WIDTH	40
#  define BAR_HEIGHT	(WIN_HEIGHT - 22)

typedef struct	s_size
{
  int		h;
  int		w;
}		t_size;

void	*launch_gui(void *arg);

int	display_rect(SDL_Surface *screen,
		     t_size *size,
		     SDL_Rect *pos,
		     Uint32 color);
int	display_one_empty_bar(SDL_Surface *screen,
			      t_size *size,
			      SDL_Rect *pos);
t_size	*init_size(t_size *size, int h, int w);
void	manage_event(SDL_Event *event, t_data *data);

# endif
#endif /* !BONUS_H_ */
