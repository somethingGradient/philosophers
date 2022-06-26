/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:30:03 by akitty            #+#    #+#             */
/*   Updated: 2022/06/26 16:30:04 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *data)
{
	int	i;

	if (data)
	{
		i = -1;
		if (data->phils)
		{
			while (++i < data->rules->n_philo)
				data->phils[i].data = NULL;
			free(data->phils);
		}
		if (data->rules)
			free(data->rules);
		if (data->threads)
			free(data->threads);
		if (data->forks)
			free(data->forks);
		data->phils = NULL;
		data->rules = NULL;
		data->threads = NULL;
		data->forks = NULL;
		free(data);
		data = NULL;
	}
}

long	timer(void)
{
	struct timeval	temp;
	long			result;

	gettimeofday(&temp, NULL);
	result = (long)(temp.tv_sec * 1000 + temp.tv_usec / 1000);
	return (result);
}

void	ft_sleep(long time)
{
	long	current_time;

	current_time = timer();
	while (time > current_time - timer())
	{
		usleep(100);
		current_time = timer();
	}
}

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->rules->n_philo)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->printf_mutex);
}

void	ft_error(t_data *data, char *msg, char *color)
{
	char	*temp;

	temp = ft_strjoin(color, msg);
	msg = temp;
	temp = ft_strjoin(temp, CLOSE);
	free(msg);
	msg = temp;
	temp = NULL;
	printf("%s\n", msg);
	free(msg);
	msg = NULL;
	free_data(data);
}
