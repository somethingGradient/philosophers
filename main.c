
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
	struct timeval temp;
	gettimeofday(&temp, NULL);
	long result = (long)(temp.tv_sec * 1000 + temp.tv_usec / 1000);
	return result;
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

void	printf_mod(pthread_mutex_t *printf_mutex, long time, int id, char *msg)
{
	pthread_mutex_lock(printf_mutex);
	printf("%ld %d %s", time, id, msg);
	pthread_mutex_unlock(printf_mutex);
}

void *philo_life(void *arg)
{
	long		time_status;
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo[0].data;
	philo->last_dinner = timer();
	if (philo->id % 2 == 0)
		usleep(50);
	while (1)
	{
		time_status = timer() - philo->last_dinner;
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		if ((long)data->rules->time_to_die / 1000 - time_status < 0)
		{
			pthread_mutex_unlock(&data->forks[philo->left_fork]);
			pthread_mutex_unlock(&data->forks[philo->right_fork]);
			printf("%ld %d is dead\n", timer() - data->start_time, philo->id);
			return (NULL);
		}
		printf_mod(&data->printf_mutex, timer() - data->start_time, philo->id, "is eating\n");
		philo->last_dinner = timer();
		usleep(data->rules->time_to_eat);
		philo->n_dinner++;
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
		printf_mod(&data->printf_mutex, timer() - data->start_time, philo->id, "is thiking\n");
		printf_mod(&data->printf_mutex, timer() - data->start_time, philo->id, "is sleeping\n");
		usleep(data->rules->time_to_sleep);
		printf_mod(&data->printf_mutex, timer() - data->start_time, philo->id, "is thiking\n");
		if (data->rules->satiety > -1)
		{
			if (philo->n_dinner > data->rules->satiety)
			{
				printf("%ld %d IS SATIETY.\n", timer() - data->start_time, philo->id);
				return (NULL);
			}
			data->rules->satiety--;
		}
	}
}

int main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	data = NULL;
	data = (t_data *)malloc(sizeof(*data));
	data->phils = NULL;
	data->forks = NULL;
	data->threads = NULL;
	data->rules = NULL;
	data->rules = check_args(argc, argv);
	if (!data->rules)
	{
		ft_error(data, "Invalid arguments.");
		return (-1);
	}
	if (mem_alloc(data))
	{
		ft_error(data, "Error allocation memory.");
		return (-1);
	}
	if (prepare_dinner(data))
	{
		ft_error(data, "Table is broken.");
		return (-1);
	}
	data->start_time = timer();
	i = -1;
	while (++i < data->rules->n_philo)
		pthread_create(&data->threads[i], NULL, philo_life, &data->phils[i]);
	
	i = -1;
	while (++i < data->rules->n_philo)
		pthread_join(data->threads[i], NULL);

	ft_destroy_mutex(data);
	free_data(data);

	// printf("\n=========================\n%d", errno);
	return (0);
}