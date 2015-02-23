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

# define N_PHI 7

typedef struct		s_data
{
  pthread_t		thread;
  pthread_mutex_t	chopstick;
  int			id;
  struct s_data		*phi_st;
  int			food;
}			t_data;

#endif /* !PHILOSOPHE_H_ */
