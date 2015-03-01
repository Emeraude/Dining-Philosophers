/*
** philosophe.c for  in /home/duques_g/Programming/Philosophe
**
** Made by duques_g
** Login   <duques_g@epitech.net>
**
** Started on  Mon Feb 23 16:50:12 2015 duques_g
** Last update Wed Feb 25 07:36:14 2015 duques_g
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
#include "philosophe.h"
#include "bonus.h"

static int	init_philosophers(t_data *data, t_stat *stat, t_conf *conf)
{
  int		i;

#ifdef BONUS
  stat->outfd = creat(conf->outfile, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (stat->outfd == -1)
    fprintf(stderr, MSG_ERROR_OPEN_FILE, conf->outfile);
  write_header_csv(stat);
#endif
  stat->food = conf->nb_food;
  stat->total_eaten = 0;
  printf("%d philosophers enter in the room\n", conf->nb_philo);
  i = -1;
  while (++i != conf->nb_philo)
    {
      data[i].id = i;
      data[i].phi_st = data;
      data[i].stat = stat;
      data[i].conf = conf;
      data[i].eaten_plates = 0;
      data[i].hours_slept = 0;
      data[i].hours_thought = 0;
      if (pthread_mutex_init(&data[i].stick, NULL))
	return (0);
    }
  return (1);
}

static int	launch_threads(t_data *data)
{
  int		i;

  i = -1;
  while (++i != data->conf->nb_philo)
    if (pthread_create(&data[i].thread, NULL, start_diner, &data[i]))
      return (0);
  i = -1;
  while (++i != data->conf->nb_philo)
    {
      if (pthread_join(data[i].thread, NULL))
	return (0);
      printf("\033[0;3%dmPhilosopher [%d] has eaten %d times\033[0m\n",
	     i % 8 + 1, i, data[i].eaten_plates);
    }
  return (1);
}

int		main(int argc, char **argv)
{
  t_data	*data;
  t_stat	stat;
  t_conf	conf;
#ifdef BONUS
  pthread_t	gui;
#endif

  if (!check_argv(argc, argv, &conf))
    return (EXIT_FAILURE);
  if (conf.exit)
    return (EXIT_SUCCESS);
  if (!(data = malloc(conf.nb_philo * sizeof(t_data)))
      || pthread_mutex_init(&stat.food_lock, NULL)
      || !init_philosophers(data, &stat, &conf)
#ifdef BONUS
      || pthread_create(&gui, NULL, launch_gui, data)
#endif
      || !launch_threads(data))
    return (EXIT_FAILURE);
  printf("Total eaten plates : %d\n", stat.total_eaten);
#ifdef BONUS
  close(stat.outfd);
#endif
  free(data);
  return (EXIT_SUCCESS);
}
