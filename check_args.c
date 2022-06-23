
#include "philosophers.h"

int	check_args(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	data->rules = (t_rules *)malloc(sizeof(*data->rules));
	if (!data->rules)
		return (1);
	data->rules->n_philo = ft_atoi(argv[1]);
	data->rules->time_to_die = ft_atoi(argv[2]) * 1000;
	data->rules->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->rules->time_to_sleep = ft_atoi(argv[4]) * 1000;
	data->rules->satiety = -1;
	if (argc == 6)
	{
		data->rules->satiety = ft_atoi(argv[5]);
		if (data->rules->satiety <= 0)
			return (1);
	}
	if (data->rules->n_philo <= 1 || data->rules->time_to_die <= 0 ||
		data->rules->time_to_eat <= 0 || data->rules->time_to_sleep <= 0)
		return (1);
	return (0);
}

int	prepare_dinner(t_data *data, int i)
{
	data->phils = (t_philo *)malloc(sizeof(*data->phils)
		* data->rules->n_philo);
	data->threads = (pthread_t *)malloc(sizeof(*data->threads)
		* data->rules->n_philo);
	data->forks = (pthread_mutex_t *)malloc(sizeof(*data->forks)
		* data->rules->n_philo);
	if (!data->phils || !data->threads || !data->forks)
		return (1);
	while (++i < data->rules->n_philo)
	{
		data->phils[i].id = i + 1;
		data->phils[i].left_fork = i;
		if (i == data->rules->n_philo - 1)
			data->phils[i].right_fork = 0;
		else
			data->phils[i].right_fork = i + 1;
		pthread_mutex_init(&data->forks[i], NULL);
		data->phils[i].data = data;
		data->phils[i].n_dinner = 0;
	}
	if (pthread_mutex_init(&data->printf_mutex, NULL))
		return (1);
	return (0);
}
