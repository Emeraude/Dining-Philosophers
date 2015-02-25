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
}			t_stat;

typedef struct		s_data
{
  pthread_t		thread;
  pthread_mutex_t	chopstick;
  int			id;
  int			eaten_plates;
  struct s_data		*phi_st;
  struct s_stat		*stat;
}			t_data;

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS	0
# endif

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE	1
# endif

# define MAX(x, y)	(x < y ? y : x)

#endif /* !PHILOSOPHE_H_ */
