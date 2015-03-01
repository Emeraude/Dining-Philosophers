/*
** diner.c for  in /home/broggi_t/projet/Dining-Philosophers
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Wed Feb 25 02:44:39 2015 broggi_t
** Last update Wed Feb 25 02:44:39 2015 broggi_t
*/

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "philosophe.h"

static void	rest(t_data *data)
{
  ++data->hours_slept;
  display_rest(data->stat, data->id);
  usleep(MAX(data->conf->time_action, 1) * MIN_TIME);
}

static void	eat(t_data *data, t_data *first, t_conf *conf, int id)
{
  int		ret;

  if (!(ret = pthread_mutex_lock(&data->stat->food_lock)))
    {
      if (!data->stat->food)
	{
	  if (pthread_mutex_unlock(&data->stat->food_lock)
	      || pthread_mutex_unlock(&first[id % conf->nb_philo].stick)
	      || pthread_mutex_unlock(&first[(id + 1) % conf->nb_philo].stick))
	    exit(EXIT_FAILURE);
	  pthread_exit(NULL);
	}
      --data->stat->food;
      pthread_mutex_unlock(&data->stat->food_lock);
    }
  else if (ret != EBUSY)
    exit(EXIT_FAILURE);
  ++data->eaten_plates;
  ++data->stat->total_eaten;
  display_eat(data->stat, id);
  usleep(MAX(TIME_ACTION, 1) * MIN_TIME);
  if (pthread_mutex_unlock(&first[id % conf->nb_philo].stick)
      || pthread_mutex_unlock(&first[(id + 1) % conf->nb_philo].stick))
    exit(EXIT_FAILURE);
  rest(data);
}

static void	think(t_data *data, int pos)
{
  int		ret;

  ++data->hours_thought;
  display_think(data->stat, data->id);
  usleep(MAX(TIME_ACTION, 1) * MIN_TIME);
  if ((ret = pthread_mutex_lock(&data->phi_st[pos].stick))
      && ret != EBUSY)
    exit(EXIT_FAILURE);
  eat(data, data->phi_st, data->conf, data->id);
}

static void	choose_action(t_data *data,
			      t_data *first,
			      t_conf *conf,
			      int id)
{
  int		ret;

  if (!(ret = pthread_mutex_trylock(&first[id % conf->nb_philo].stick)))
    {
      ret = pthread_mutex_trylock(&first[(id + 1) % conf->nb_philo].stick);
      if (!ret)
	eat(data, first, conf, id);
      else if (ret == EBUSY)
	think(data, (id + 1) % conf->nb_philo);
      else
	exit(EXIT_FAILURE);
    }
  else if (!(ret = pthread_mutex_trylock(&first[(id + 1) % conf->nb_philo].stick)))
    {
      ret = pthread_mutex_trylock(&first[id % conf->nb_philo].stick);
      if (!ret)
	eat(data, first, conf, id);
      else if (ret == EBUSY)
	think(data, id % conf->nb_philo);
      else
	exit(EXIT_FAILURE);
    }
  if (ret && ret != EBUSY)
    exit(EXIT_FAILURE);
}

void		*start_diner(void *arg)
{
  t_data	*data;

  data = (t_data *)arg;
  printf("\033[0;3%dmPhilosopher [%d] set around the table\033[0m\n",
	 data->id % 7 + 1, data->id);
  while (data->stat->food > 0)
    choose_action(data, data->phi_st, data->conf, data->id);
  return (NULL);
}
