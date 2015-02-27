/*
** argv.c for  in /home/broggi_t/projet/Dining-Philosophers
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Wed Feb 25 01:58:37 2015 broggi_t
** Last update Wed Feb 25 01:58:37 2015 broggi_t
*/

#include <string.h>
#include <stdlib.h>
#include "philosophe.h"

static int	check_argv_integrity(t_conf *conf)
{
  return (conf->nb_philo >= 2
	  && conf->nb_food >= 0
	  && conf->time_action >= 1);
}

int	check_argv(int argc, char **argv, t_conf *conf)
{
  int	i;

  conf->nb_philo = NB_PHILO;
  conf->nb_food = NB_FOOD;
  conf->time_action = TIME_ACTION;
  i = 0;
  while (++i < argc)
    {
      if (i + 1 < argc)
	{
	  if (!strcmp("--philo", argv[i]) || !strcmp("-p", argv[i]))
	    conf->nb_philo = atoi(argv[++i]);
	  else if (!strcmp("--food", argv[i]) || !strcmp("-f", argv[i]))
	    conf->nb_food = atoi(argv[++i]);
	  else if (!strcmp("--time", argv[i]) || !strcmp("-t", argv[i]))
	    conf->time_action = atoi(argv[++i]);
	}
      else
	conf->nb_philo = atoi(argv[i]);
    }
  return (check_argv_integrity(conf));
}
