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
#include <stdlib.h>
#include "philosophe.h"

void		rest(t_data *data)
{
  usleep(10000);
  printf("[%d] rests\n", data->id);
}

void		eat(t_data *data, int *count)
{
  *count = *count + 1;
  data->phi_st->food--;
  printf("[%d] eats\n", data->id);
  usleep(10000);
  pthread_mutex_unlock(&data->phi_st[data->id % N_PHI].chopstick);
  pthread_mutex_unlock(&data->phi_st[(data->id + 1) % N_PHI].chopstick);
  rest(data);
}

void		think(t_data *data, int pos, int *count)
{
  printf("[%d] think\n", data->id);
  usleep(10000);
  pthread_mutex_lock(&data->phi_st[pos].chopstick);
  eat(data, count);
}


void		*start_diner(void *arg)
{
  t_data	*data;
  int		count;

  count = 0;
  data = (t_data *)arg;
  printf("[%d] enters in your ass\n", data->id);
  while (data->phi_st->food > 0)
    {
      if (!pthread_mutex_trylock(&data->phi_st[data->id % N_PHI].chopstick))
	{
	  if (!pthread_mutex_trylock(&data->phi_st[(data->id + 1) % N_PHI].chopstick))
	    eat(data, &count);
	  else
	    think(data, (data->id + 1) % N_PHI, &count);
	}
      else if (!pthread_mutex_trylock(&data->phi_st[(data->id + 1) % N_PHI].chopstick))
	{
	  if (!pthread_mutex_trylock(&data->phi_st[data->id % N_PHI].chopstick))
	    eat(data, &count);
	  else
	    think(data, data->id % N_PHI, &count);
	}
    }
  printf("Philosopher [%d] has eaten %d time\n", data->id, count);
}

int		main(void)
{
  t_data	data[N_PHI];
  int		i;

  data->food = 100;
  i = -1;
  printf("%d\n", N_PHI);
  while (++i != N_PHI)
    {
      data[i].id = i;
      data[i].phi_st = data;
      if (pthread_mutex_init(&data[i].chopstick, NULL))
	return (EXIT_FAILURE);
    }
  i = -1;
  while (++i != N_PHI)
    if (pthread_create(&data[i].thread, NULL, start_diner, &data[i]))
      return (EXIT_FAILURE);
  i = -1;
  while (++i != N_PHI)
    pthread_join(data[i].thread, NULL);
  return (EXIT_SUCCESS);
}
