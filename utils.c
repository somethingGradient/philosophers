#include "philosophers.h"

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

long	timer()
{
	long			result;
	struct timeval	temp;

	gettimeofday(&temp, NULL);
	result = (long)(temp.tv_sec * 1000000 + temp.tv_usec);
	return (result);
}

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->rules->n_philo)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->printf_mutex);
}

void	ft_error(t_data *data, char *str)
{
	free_data(data);
	printf("%s\n", str);
}