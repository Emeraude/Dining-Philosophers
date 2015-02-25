/*
** philosophe.c for  in /home/duques_g/Programming/Philosophe
**
** Made by duques_g
** Login   <duques_g@epitech.net>
**
** Started on  Mon Feb 23 16:50:12 2015 duques_g
** Last update Mon Feb 23 23:22:51 2015 duques_g
*/

#include <unistd.h>
#include <stdio.h>
#include "philosophe.h"

static void	rest(t_data *data)
{
  printf("\033[0;3%dm[%d] rests\033[0m\n", data->id % 8 + 1, data->id);
  usleep(MAX(TIME_ACTION, 1) * MIN_TIME);
}

static void	eat(t_data *data)
{
  if (!pthread_mutex_lock(&data->stat->food_lock))
    {
      if (!data->stat->food)
	{
	  pthread_mutex_unlock(&data->stat->food_lock);
	  pthread_mutex_unlock(&data->phi_st[data->id % NB_PHILO].chopstick);
	  pthread_mutex_unlock(&data->phi_st[(data->id + 1) % NB_PHILO].chopstick);
	  pthread_exit(NULL);
	}
      --data->stat->food;
      pthread_mutex_unlock(&data->stat->food_lock);
    }
  ++data->eaten_plates;
  ++data->stat->total_eaten;
  printf("\033[0;3%dm\t\t[%d] eats\033[0m\n", data->id % 8 + 1, data->id);
  usleep(MAX(TIME_ACTION, 1) * MIN_TIME);
  pthread_mutex_unlock(&data->phi_st[data->id % NB_PHILO].chopstick);
  pthread_mutex_unlock(&data->phi_st[(data->id + 1) % NB_PHILO].chopstick);
  rest(data);
}

static void	think(t_data *data, int pos)
{
  printf("\033[0;3%dm\t\t\t\t[%d] think\033[0m\n", data->id % 8 + 1, data->id);
  usleep(MAX(TIME_ACTION, 1) * MIN_TIME);
  pthread_mutex_lock(&data->phi_st[pos].chopstick);
  eat(data);
}

static void	choose_action(t_data *data)
{
  if (!pthread_mutex_trylock(&data->phi_st[data->id % NB_PHILO].chopstick))
    {
      if (!pthread_mutex_trylock(&data->phi_st[(data->id + 1) % NB_PHILO].chopstick))
	eat(data);
      else
	think(data, (data->id + 1) % NB_PHILO);
    }
  else if (!pthread_mutex_trylock(&data->phi_st[(data->id + 1) % NB_PHILO].chopstick))
    {
      if (!pthread_mutex_trylock(&data->phi_st[data->id % NB_PHILO].chopstick))
	eat(data);
      else
	think(data, data->id % NB_PHILO);
    }
}

static void	*start_diner(void *arg)
{
  t_data	*data;

  data = (t_data *)arg;
  printf("\033[0;3%dmPhilosopher [%d] set around the table\033[0m\n", data->id % 8 + 1, data->id);
  while (data->stat->food > 0)
    choose_action(data);
  return (NULL);
}

int		main(void)
{
  t_data	data[NB_PHILO];
  t_stat	stat;
  int		i;

  stat.food = NB_FOOD;
  stat.total_eaten = 0;
  if (pthread_mutex_init(&stat.food_lock, NULL))
    return (EXIT_FAILURE);
  i = -1;
  printf("%d\n", NB_PHILO);
  while (++i != NB_PHILO)
    {
      data[i].id = i;
      data[i].phi_st = data;
      data[i].stat = &stat;
      data[i].eaten_plates = 0;
      if (pthread_mutex_init(&data[i].chopstick, NULL))
	return (EXIT_FAILURE);
    }
  i = -1;
  while (++i != NB_PHILO)
    if (pthread_create(&data[i].thread, NULL, start_diner, &data[i]))
      return (EXIT_FAILURE);
  i = -1;
  while (++i != NB_PHILO)
    {
      pthread_join(data[i].thread, NULL);
      printf("\033[0;3%dmPhilosopher [%d] has eaten %d time\033[0m\n", i % 8 + 1, i, data[i].eaten_plates);
    }
  printf("Total eaten plates : %d\n", stat.total_eaten);
  return (EXIT_SUCCESS);
}
