
#include "philosophers.h"

t_rules	*check_args(int argc, char **argv)
{
	t_rules	*rules;

	rules = NULL;
	if (argc != 5 && argc != 6)
		return (NULL);
	rules = (t_rules *)malloc(sizeof(*rules));
	if (!rules)
		return (NULL);
	rules->n_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]) * 1000;
	rules->time_to_eat = ft_atoi(argv[3]) * 1000;
	rules->time_to_sleep = ft_atoi(argv[4]) * 1000;
	rules->satiety = -1;
	if (argc == 6)
	{
		rules->satiety = ft_atoi(argv[5]);
		if (rules->satiety <= 0)
			return (NULL);
	}
	if (rules->n_philo <= 0 || rules->time_to_die <= 0 ||
		rules->time_to_eat <= 0 || rules->time_to_sleep <= 0)
		return (NULL);
	return (rules);
}

int	mem_alloc(t_data *data)
{
	data->phils = NULL;
	data->threads = NULL;
	data->forks = NULL;
	data->phils = (t_philo *)malloc(sizeof(*data->phils)
		* data->rules->n_philo);
	data->threads = (pthread_t *)malloc(sizeof(*data->threads)
		* data->rules->n_philo);
	data->forks = (pthread_mutex_t *)malloc(sizeof(*data->forks)
		* data->rules->n_philo);
	if (!data->phils || !data->threads || !data->forks)
		return (1);
	return (0);

}

int	prepare_dinner(t_data *data)
{
	int	i;

	i = -1;
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
