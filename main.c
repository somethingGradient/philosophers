
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

void	printf_mod(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&data->printf_mutex);
	printf("%ld %d %s", (timer() - data->start_time) / 1000, id, msg);
	pthread_mutex_unlock(&data->printf_mutex);
}

int	philo_eat(t_data *data, t_philo *philo)
{
	if (data->death_status)
		return (1);
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	if (data->death_status)
		return (1);
	printf_mod(data, philo->id, "has taken a fork\n");
	usleep(data->rules->time_to_eat);
	philo->last_dinner = timer();
	philo->n_dinner--;
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	return (0);
}

int philo_think(t_data *data, t_philo *philo)
{
	if (data->death_status)
		return (1);
	printf_mod(data, philo->id, "is thinking\n");
	return (0);
}

int philo_sleep(t_data *data, t_philo *philo)
{
	if (data->death_status)
		return (1);
	printf_mod(data, philo->id, "is sleeping\n");
	usleep(data->rules->time_to_sleep);
	return (0);
}

void *philo_life(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo[0].data;
	if (philo->id % 2 == 0)
		usleep(10);
	philo->last_dinner = timer();
	while (!data->death_status)
	{
		if (philo_eat(data, philo))
			return (NULL);
		if (philo_think(data, philo))
			return (NULL);
		if (philo_sleep(data, philo))
			return (NULL);
		if (philo_think(data, philo))
			return (NULL);
		if (data->death_status)
			return (NULL);
	}
}

int	birth_of_philosophy(t_data *data, int argc, char **argv)
{
	if (check_args(data, argc, argv))
	{
		ft_error(data, "Invalid arguments.");
		return (1);
	}
	if (prepare_dinner(data, -1))
	{
		ft_error(data, "Dinner will not take place.");
		return (1);
	}
	data->start_time = timer();
	return (0);
}

void	*death_checker(void *arg)
{
	int		i;
	t_data	*data;
	int flag;

	usleep(10);
	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->rules->n_philo)
		{
			if (data->phils[i].n_dinner == 0)
			{
				data->phils[i].n_dinner = -1;
				data->satiety_status += 1;
				if (data->satiety_status == data->rules->n_philo)
				{
					data->death_status = 1;
					return (NULL);
				}
			}
			if (timer() - data->phils[i].last_dinner > (long)data->rules->time_to_die)
			{
				pthread_mutex_unlock(&data->forks[data->phils[i].left_fork]);
				pthread_mutex_unlock(&data->forks[data->phils[i].right_fork]);
				printf_mod(data, data->phils[i].id, "is died\n");
				data->death_status = 1;
				return (NULL);
			}
		}
	}
}

int main(int argc, char **argv)
{
	pthread_t checker;
	t_data	*data;
	int		i;

	data = NULL;
	data = (t_data *)malloc(sizeof(*data));
	if (!data)
		return (1);
	data->phils = NULL;
	data->forks = NULL;
	data->threads = NULL;
	data->rules = NULL;
	data->death_status = 0;
	if (birth_of_philosophy(data, argc, argv))
		return (1);
	i = -1;
	while (++i < data->rules->n_philo)
		pthread_create(&data->threads[i], NULL, philo_life, &data->phils[i]);
	pthread_create(&checker, NULL, death_checker, data);
	pthread_join(checker, NULL);
	i = -1;
	while (++i < data->rules->n_philo)
		pthread_join(data->threads[i], NULL);
	ft_destroy_mutex(data);
	free_data(data);
	return (0);
}