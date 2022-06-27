/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:29:10 by akitty            #+#    #+#             */
/*   Updated: 2022/06/26 16:29:12 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_mod(t_data *data, int id, char *msg, char *color)
{
	char	*temp;
	long	time_status;

	temp = ft_strjoin(color, msg);
	msg = temp;
	temp = ft_strjoin(temp, CLOSE);
	free(msg);
	msg = temp;
	temp = NULL;
	time_status = timer() - data->start_time;
	pthread_mutex_lock(&data->printf_mutex);
	printf("%ld.%ld %d %s", time_status / 1000, time_status % 1000, id, msg);
	pthread_mutex_unlock(&data->printf_mutex);
	free(msg);
	msg = NULL;
}

void	*philo_life(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo[0].data;
	if (philo->id % 2 == 0)
		ft_sleep(50);
	philo->last_dinner = timer();
	while (!data->death_status)
	{
		if (philo_eat(data, philo))
			return (NULL);
		data->flag_for_checker = 1;
		if (philo_think(data, philo))
			return (NULL);
		if (philo_sleep(data, philo))
			return (NULL);
		if (philo_think(data, philo))
			return (NULL);
	}
}

void	*death_checker(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1337)
	{
		i = -1;
		if (!data->flag_for_checker)
			continue ;
		while (++i < data->rules->n_philo)
		{
			if ((timer() - data->phils[i].last_dinner)
				> (long)data->rules->time_to_die)
			{
				check_conditions(data, i, 0);
				return (NULL);
			}
			if (data->phils[i].n_dinner == 0)
			{
				if (check_conditions(data, i, 1))
					return (NULL);
			}
		}
	}
}

int	main(int argc, char **argv)
{
	pthread_t	checker;
	t_data		*data;
	int			i;

	data = NULL;
	data = (t_data *)malloc(sizeof(*data));
	if (!data)
		return (1);
	data->phils = NULL;
	data->forks = NULL;
	data->threads = NULL;
	data->rules = NULL;
	if (birth_of_philosophy(data, argc, argv))
		return (1);
	pthread_create(&checker, NULL, &death_checker, data);
	i = -1;
	while (++i < data->rules->n_philo)
		pthread_create(&data->threads[i], NULL, &philo_life, &data->phils[i]);
	i = -1;
	while (++i < data->rules->n_philo)
		pthread_join(data->threads[i], NULL);
	pthread_join(checker, NULL);
	ft_destroy_mutex(data);
	free_data(data);
	return (0);
}
