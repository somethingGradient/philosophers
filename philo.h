/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 17:11:15 by akitty            #+#    #+#             */
/*   Updated: 2022/06/26 17:11:17 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/time.h>

# define DEFAULT "\001\033[0;39m\002"
# define GRAY "\001\033[1;90m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"
# define BLUE "\001\033[1;94m\002"
# define MAGENTA "\001\033[1;95m\002"
# define CYAN "\001\033[1;96m\002"
# define WHITE "\001\033[0;97m\002"
# define CLOSE "\001\033[0m\002"

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
	int				flag_for_checker;
	int				satiety_status;
	int				death_status;
	long			start_time;
	t_rules			*rules;
	t_philo			*phils;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf_mutex;
}	t_data;

int		philo_think(t_data *data, t_philo *philo);
int		philo_sleep(t_data *data, t_philo *philo);
int		philo_eat(t_data *data, t_philo *philo);
int		check_conditions(t_data *data, int i, int mode);
long	timer(void);
void	ft_error(t_data *data, char *msg, char *color);
void	free_data(t_data *data);
void	ft_destroy_mutex(t_data *data);
void	ft_sleep(long time);
int		check_args(t_data *data, int argc, char **argv);
int		prepare_dinner(t_data *data, int i);
int		birth_of_philosophy(t_data *data, int argc, char **argv);
int		ft_atoi(const char *str);
int		ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);

#endif