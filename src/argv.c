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
#include <stdio.h>
#include <stdlib.h>
#include "philosophe.h"

static int	check_argv_integrity(t_conf *conf)
{
  if (conf->nb_philo == 1)
    return (fprintf(stderr, MSG_ONE_PHILO) * 0);
  else if (conf->nb_philo < 1)
    return (fprintf(stderr, MSG_NO_PHILO) * 0);
  if (conf->nb_food < 1)
    return (fprintf(stderr, MSG_NO_FOOD) * 0);
  if (conf->time_action < 1)
    return (fprintf(stderr, MSG_INVALID_TIME) * 0);
  return (1);
}

static void	display_config()
{
  printf("========== CONFIG ==========\n");
  printf("Default number of philosophers : %d\n", NB_PHILO);
  printf("Default quantity of food : %d\n", NB_FOOD);
  printf("Default time of actions : %dms\n", TIME_ACTION);
#ifdef BONUS
  printf("Default output file : %s\n", OUT_FILE);
#endif
  printf("============================\n");
}

static void	arg_with_value(char **argv, int *i, t_conf *conf)
{
  if (!strcmp("--philo", argv[*i]) || !strcmp("-p", argv[*i]))
    conf->nb_philo = atoi(argv[++*i]);
  else if (!strcmp("--food", argv[*i]) || !strcmp("-f", argv[*i]))
    conf->nb_food = atoi(argv[++*i]);
  else if (!strcmp("--time", argv[*i]) || !strcmp("-t", argv[*i]))
    conf->time_action = atoi(argv[++*i]);
#ifdef BONUS
  else if (!strcmp("--out", argv[*i]) || !strcmp("-o", argv[*i]))
    conf->outfile = argv[++*i];
#endif
}

static void	arg_without_value(char *arg, t_conf *conf)
{
  if (!strcmp("--config", arg))
    {
      display_config();
      conf->exit = 1;
    }
  else
    conf->nb_philo = atoi(arg);
}

int	check_argv(int argc, char **argv, t_conf *conf)
{
  int	i;

  conf->nb_philo = NB_PHILO;
  conf->nb_food = NB_FOOD;
  conf->time_action = TIME_ACTION;
#ifdef BONUS
  conf->outfile = OUT_FILE;
#endif
  conf->exit = 0;
  i = 0;
  while (++i < argc)
    {
      if (i + 1 < argc)
	arg_with_value(argv, &i, conf);
      else
	arg_without_value(argv[i], conf);
    }
  return (check_argv_integrity(conf));
}
