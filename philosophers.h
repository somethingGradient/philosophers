#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/time.h>

#include "libft/libft.h"

typedef struct s_rules
{
	int	n_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	satiety;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				n_dinner;
	long			last_dinner;
	struct s_data	*data;
}	t_philo;


typedef struct s_data
{
	long			start_time;
	t_rules			*rules;
	t_philo			*phils;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf_mutex;
}	t_data;


t_rules	*check_args(int argc, char **argv);
int	mem_alloc(t_data *data);
int	prepare_dinner(t_data *data);


#endif