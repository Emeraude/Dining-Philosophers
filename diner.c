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
#include "philosophe.h"

static void	rest(t_data *data)
{
  printf("\033[0;3%dm[%d] rests\033[0m\n", data->id % 8 + 1, data->id);
  usleep(MAX(data->conf->time_action, 1) * MIN_TIME);
}

static void	eat(t_data *data, t_data *first, t_conf *conf, int id)
{
  if (!pthread_mutex_lock(&data->stat->food_lock))
    {
      if (!data->stat->food)
	{
	  pthread_mutex_unlock(&data->stat->food_lock);
	  pthread_mutex_unlock(&first[id % conf->nb_philo].stick);
	  pthread_mutex_unlock(&first[(id + 1) % conf->nb_philo].stick);
	  pthread_exit(NULL);
	}
      --data->stat->food;
      pthread_mutex_unlock(&data->stat->food_lock);
    }
  ++data->eaten_plates;
  ++data->stat->total_eaten;
  printf("\033[0;3%dm\t\t[%d] eats\033[0m\n", id % 8 + 1, id);
  usleep(MAX(TIME_ACTION, 1) * MIN_TIME);
  pthread_mutex_unlock(&first[id % conf->nb_philo].stick);
  pthread_mutex_unlock(&first[(id + 1) % conf->nb_philo].stick);
  rest(data);
}

static void	think(t_data *data, int pos)
{
  printf("\033[0;3%dm\t\t\t\t[%d] think\033[0m\n",
  	 data->id % 8 + 1, data->id);
  usleep(MAX(TIME_ACTION, 1) * MIN_TIME);
  pthread_mutex_lock(&data->phi_st[pos].stick);
  eat(data, data->phi_st, data->conf, data->id);
}

static void	choose_action(t_data *data,
			      t_data *first,
			      t_conf *conf,
			      int id)
{
  if (!pthread_mutex_trylock(&first[id % conf->nb_philo].stick))
    {
      if (!pthread_mutex_trylock(&first[(id + 1) % conf->nb_philo].stick))
	eat(data, first, conf, id);
      else
	think(data, (id + 1) % conf->nb_philo);
    }
  else if (!pthread_mutex_trylock(&first[(id + 1) % conf->nb_philo].stick))
    {
      if (!pthread_mutex_trylock(&first[id % conf->nb_philo].stick))
	eat(data, first, conf, id);
      else
	think(data, id % conf->nb_philo);
    }
}

void		*start_diner(void *arg)
{
  t_data	*data;

  data = (t_data *)arg;
  printf("\033[0;3%dmPhilosopher [%d] set around the table\033[0m\n",
	 data->id % 8 + 1, data->id);
  while (data->stat->food > 0)
    choose_action(data, data->phi_st, data->conf, data->id);
  return (NULL);
}
