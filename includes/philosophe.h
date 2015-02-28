/*
** philosophe.h for  in /home/duques_g
** 
** Made by duques_g
** Login   <duques_g@epitech.net>
** 
** Started on  Mon Feb 23 16:50:48 2015 duques_g
** Last update Mon Feb 23 23:23:11 2015 duques_g
*/

#ifndef PHILOSOPHE_H_
# define PHILOSOPHE_H_

# include <pthread.h>

# ifndef NB_PHILO
#  define NB_PHILO	7
# endif

# ifndef NB_FOOD
#  define NB_FOOD	1000
# endif

# define MIN_TIME	1000

# ifndef TIME_ACTION
#  define TIME_ACTION	20
# endif

typedef struct		s_stat
{
  pthread_mutex_t	food_lock;
  int			food;
  int			total_eaten;
# ifdef BONUS
  int			outfd;
# endif
}			t_stat;

typedef struct		s_conf
{
  int			nb_philo;
  int			nb_food;
  int			time_action;
}			t_conf;

typedef struct		s_data
{
  pthread_t		thread;
  pthread_mutex_t	stick;
  int			id;
  int			eaten_plates;
  int			hours_slept;
  int			hours_thought;
  struct s_data		*phi_st;
  struct s_stat		*stat;
  struct s_conf		*conf;
}			t_data;

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS	0
# endif

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE	1
# endif

# define UNUSED		__attribute__((unused))

# define MAX(x, y)	(x < y ? y : x)

int	check_argv(int argc, char **argv, t_conf *conf);
void	*start_diner(void *arg);
void	display_rest(t_stat *stat, int id);
void	display_eat(t_stat *stat, int id);
void	display_think(t_stat *stat, int id);

# ifdef BONUS
#  include <SDL/SDL.h>
#  define COUNT_ARRAY(x)	(sizeof(x) / sizeof(*x))

#  define BAR_WIDTH	40
#  define WIN_WIDTH	640
#  define WIN_HEIGHT	480

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

# endif

#endif /* !PHILOSOPHE_H_ */
