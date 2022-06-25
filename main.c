
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

void *philo_life(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo[0].data;
	if (philo->id % 2 == 0)
		usleep(5);
	philo->last_dinner = timer();
	while (1)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		if (data->rules->n_philo == 1)
			return (NULL);
		printf_mod(data, philo->id, "is eating\n");
		usleep(data->rules->time_to_eat);
		philo->last_dinner = timer();
		philo->n_dinner++;
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
		printf_mod(data, philo->id, "is thiking\n");
		printf_mod(data, philo->id, "is sleeping\n");
		usleep(data->rules->time_to_sleep);
		printf_mod(data, philo->id, "is thiking\n");
		if (data->death_status || philo->satiety_status)
			return (NULL);
		if (data->rules->satiety > -1)
		{
			if (!philo->satiety_status)
			{
				if (philo->n_dinner >= data->rules->satiety)
				{
					printf_mod(data, philo->id, "is satiety\n");
					return (NULL);
				}
			}
		}
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

	usleep(50);
	data = (t_data *)arg;
	while (1)
	{
		flag = 0;
		i = -1;
		while (++i < data->rules->n_philo)
		{
			if (data->phils[i].satiety_status)
			{
				flag++;
				continue ;
			}
			if (timer() - data->phils[i].last_dinner > (long)data->rules->time_to_die)
			{
				pthread_mutex_unlock(&data->forks[data->phils[i].left_fork]);
				pthread_mutex_unlock(&data->forks[data->phils[i].right_fork]);
				printf_mod(data, data->phils[i].id, "is died\n");
				usleep(1000);
				data->death_status = 1;
				return (NULL);
			}
		}
		if (flag == data->rules->n_philo)
			return (NULL);
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