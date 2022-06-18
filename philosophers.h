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

typedef struct s_data
{
	int i;
}	t_data;

typedef struct s_philo
{
	pthread_t	p_index;
	int			id;

	int	left_fork;
	int right_fork;

	int eating_status;
	int sleeping_status;
	int thinking_status;

	pthread_mutex_t *forks;

	pthread_mutex_t		*printf_mutex;

	int		n_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		satiety;

}	t_philo;


typedef struct s_general
{
	int		n_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		satiety;

	t_philo			*philosophers;
	pthread_mutex_t	*forks;
}	t_general;


int	check_args(t_general *general, int argc, char **argv);

#endif