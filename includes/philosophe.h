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

# ifndef NB_PHILO
#  define NB_PHILO	7
# endif

# ifndef NB_FOOD
#  define NB_FOOD	1000
# endif

# define MIN_TIME	1000

# ifndef TIME_ACTION
#  define TIME_ACTION	20
# endif

# ifndef OUT_FILE
#  define OUT_FILE	"out.csv"
# endif

# define MSG_ONE_PHILO	"There is only one philosopher, which \
is playing alone with his chopstick\n"
# define MSG_NO_PHILO	"There is no philosopher\n"
# define MSG_NO_FOOD	"There is no food\n"
# define MSG_INVALID_TIME	"Time is too short\n"
# define MSG_ERROR_OPEN_FILE	"Unable to open the file %s\n"

typedef struct		s_stat
{
  pthread_mutex_t	food_lock;
  int			food;
  int			total_eaten;
# ifdef BONUS
  int			outfd;
# endif
}			t_stat;

typedef struct		s_conf
{
  int			nb_philo;
  int			nb_food;
  int			time_action;
  int			exit;
# ifdef BONUS
  char			*outfile;
# endif
}			t_conf;

typedef struct		s_data
{
  pthread_t		thread;
  pthread_mutex_t	stick;
  int			id;
  int			eaten_plates;
  int			hours_slept;
  int			hours_thought;
  struct s_data		*phi_st;
  struct s_stat		*stat;
  struct s_conf		*conf;
}			t_data;

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS	0
# endif

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE	1
# endif

# define UNUSED		__attribute__((unused))

# define MAX(x, y)	(x < y ? y : x)

int	check_argv(int argc, char **argv, t_conf *conf);
void	*start_diner(void *arg);
void	display_rest(t_stat *stat, int id);
void	display_eat(t_stat *stat, int id);
void	display_think(t_stat *stat, int id);
# ifdef BONUS
void    write_header_csv(t_stat *stat);
#endif

#endif /* !PHILOSOPHE_H_ */
