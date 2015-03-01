/*
** csv.c for  in /home/broggi_t/projet/Dining-Philosophers/src
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Sat Feb 28 22:31:41 2015 broggi_t
** Last update Sat Feb 28 22:31:41 2015 broggi_t
*/

#include <sys/time.h>
#include <stdio.h>
#include "philosophe.h"

#ifdef BONUS
void	write_header_csv(t_stat *stat)
{
  if (stat->outfd != -1)
    dprintf(stat->outfd, "timestamp,philosopher,action\n");
}

static unsigned long int	get_timestamp()
{
  struct timeval		time;

  gettimeofday(&time, NULL);
  return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
#endif

void	display_rest(t_stat *stat UNUSED, int id)
{
  printf("\033[0;3%dm[%d] rests\033[0m\n", id % 7 + 1, id);
#ifdef BONUS
  if (stat->outfd != -1)
    dprintf(stat->outfd, "%lu,%d,rest\n", get_timestamp(), id);
#endif
}

void	display_eat(t_stat *stat UNUSED, int id)
{
  printf("\033[0;3%dm\t\t[%d] eats\033[0m\n", id % 7 + 1, id);
#ifdef BONUS
  if (stat->outfd != -1)
    dprintf(stat->outfd, "%lu,%d,eat\n", get_timestamp(), id);
#endif
}

void	display_think(t_stat *stat UNUSED, int id)
{
  printf("\033[0;3%dm\t\t\t\t[%d] think\033[0m\n", id % 7 + 1, id);
#ifdef BONUS
  if (stat->outfd != -1)
    dprintf(stat->outfd, "%lu,%d,think\n", get_timestamp(), id);
#endif
}
