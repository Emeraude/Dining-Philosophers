/*
** philosophe.c for  in /home/duques_g/Programming/Philosophe
**
** Made by duques_g
** Login   <duques_g@epitech.net>
**
** Started on  Mon Feb 23 16:50:12 2015 duques_g
** Last update Mon Feb 23 21:59:48 2015 duques_g
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "philosophe.h"

void		eat(t_data *data, int id)
{
  printf("[%d] eats\n");
  usleep(10000);
  pthread_mutex_unlock(&data->chopstick[id % N_PHI]);
  pthread_mutex_unlock(&data->chopstick[(id + 1) % N_PHI]);
  rest(data, id);
}

void		think(t_data *data, int id, int pos)
{
  printf("[%d] think\n", id);
  usleep(10000);
  pthread_mutex_lock(&data->chopstick[pos % N_PHI]);
  eat(data, id);
}

void		rest(t_data *data, int id)
{
  usleep(10000);
  printf("[%d] rests\n", id);
}


void		*start_diner(void *arg)
{
  t_data	*data;
  int		id;
  int		count;
  data = (t_data *)arg;
  id = data->id++;
  count = 0;

  printf("[%d] enters in your ass\n", id);
  while (42)
    {
      if (!pthread_mutex_trylock(&data->chopstick[id % N_PHI]))
	{
	  if (!pthread_mutex_trylock(&data->chopstick[(id + 1) % N_PHI]))
	    {
	      eat(data, id);
	    }
	  else
	    {
	      think(data, id, (id + 1) % N_PHI);
	    }
	}

      else if (!pthread_mutex_trylock(&data->chopstick[(id + 1) % N_PHI]))
	{
	  if (!pthread_mutex_trylock(&data->chopstick[id % N_PHI]))
	    {
	      eat(data, id);
	    }
	  else
	    {
	      think(data, id, id % N_PHI);
	    }
	}
    }
}

int		main(void)
{
  t_data	data;
  pthread_t	thread[N_PHI];
  int		i;

  data.id = 0;
  i = -1;
  printf("%d\n", N_PHI);
  while (++i != N_PHI)
    if (pthread_mutex_init(&data.chopstick[i], NULL))
      return (EXIT_FAILURE);
  i = -1;
  while (++i != N_PHI)
    if (pthread_create(&thread[i], NULL, start_diner, &data))
      return (EXIT_FAILURE);
  i = -1;
  while (++i != N_PHI)
    {
      pthread_join(thread[i], NULL);
      usleep(1000);
    }
  return (EXIT_SUCCESS);
}
