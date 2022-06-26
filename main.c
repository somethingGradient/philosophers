
#include "philosophers.h"

void	printf_mod(t_data *data, int id, char *msg, int mode)
{
	char	*temp;
	long	time_status;
	
	// if (mode == 0)
	// 	temp = ft_strjoin(RED, msg);
	// else if (mode == 1)
	// 	temp = ft_strjoin(CYAN, msg);
	// else if (mode == 2)
	// 	temp = ft_strjoin(BLUE, msg);
	// else if (mode == 3)
	// 	temp = ft_strjoin(GRAY, msg);
	// else if (mode == 4)
	// 	temp = ft_strjoin(GREEN, msg);
	// msg = temp;
	// temp = ft_strjoin(temp, CLOSE);
	// free(msg);
	// msg = temp;
	// temp = NULL;
	pthread_mutex_lock(&data->printf_mutex);
	time_status = (timer() - data->start_time) / 1000;
	printf("%ld %d %s", time_status, id, msg);
	// printf("%ld.%ld %d %s", time_status / 1000, time_status % 1000 , id, msg);
	pthread_mutex_unlock(&data->printf_mutex);
	// free(msg);
	msg = NULL;
}

int philo_think(t_data *data, t_philo *philo)
{
	if (data->death_status)
		return (1);
	printf_mod(data, philo->id, "is thinking\n", 2);
	return (0);
}

int philo_sleep(t_data *data, t_philo *philo)
{
	if (data->death_status)
		return (1);
	printf_mod(data, philo->id, "is sleeping\n", 3);
	usleep(data->rules->time_to_sleep);
	return (0);
}

int	philo_eat(t_data *data, t_philo *philo)
{
	if (data->death_status)
		return (1);
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	printf_mod(data, philo->id, "has taken a fork\n", 1);
	if (data->rules->n_philo == 1)
		return(pthread_mutex_unlock(&data->forks[philo->left_fork]), 1);
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	printf_mod(data, philo->id, "has taken a fork\n", 1);
	printf_mod(data, philo->id, "is eating\n", 4);
	usleep(data->rules->time_to_eat);
	philo->last_dinner = timer();
	philo->n_dinner--;
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	return (0);
}

void *philo_life(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo[0].data;
	if (philo->id % 2 == 0)
	{
		usleep(30);
	printf("\nALO\n");
	}
	philo->last_dinner = timer();
	while (!data->death_status)
	{
		// printf("\n|%ld|\n", philo->last_dinner);
		if (philo_eat(data, philo))
			return (NULL);
		// if (philo_think(data, philo))
		// 	return (NULL);
		if (philo_sleep(data, philo))
			return (NULL);
		if (philo_think(data, philo))
			return (NULL);
		if (data->death_status)
			return (NULL);
	}
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
		i = -1;
		while (++i < data->rules->n_philo)
		{
			if (timer() - data->phils[i].last_dinner > (long)data->rules->time_to_die)
			{

			// printf("\n=========\n|%d %ld %ld|\n", data->phils[i].id, timer() - data->phils[i].last_dinner, (long)data->rules->time_to_die);
				
				pthread_mutex_unlock(&data->forks[data->phils[i].left_fork]);
				pthread_mutex_unlock(&data->forks[data->phils[i].right_fork]);
				data->death_status = 1;
				printf_mod(data, data->phils[i].id, "is died\n", 0);
				pthread_mutex_lock(&data->printf_mutex);
				usleep(10);
				pthread_mutex_unlock(&data->printf_mutex);
				return (NULL);
			}
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
		}
	}
}

int main(int argc, char **argv)
{
	pthread_t checker;
	t_data		*data;
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
	i = -1;
	while (++i < data->rules->n_philo)
		pthread_join(data->threads[i], NULL);
	pthread_join(checker, NULL);
	ft_destroy_mutex(data);
	free_data(data);
	return (0);
}