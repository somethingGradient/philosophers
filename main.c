
#include "philosophers.h"

void	free_data(t_general *general)
{
	if (general)
	{
		free(general);
		general = NULL;
	}
}

void	init_threads(t_general *general)
{
	t_philo				*philosophers;
	pthread_t			*philo_threads;
	pthread_mutex_t		*forks;

	
	pthread_mutex_t 	*printf_mutex;
	printf_mutex = NULL;
	printf_mutex = malloc(sizeof(*printf_mutex));
	pthread_mutex_init(printf_mutex, NULL);


	philo_threads = (pthread_t *)malloc(sizeof(*philo_threads) * general->n_philo);
	philosophers = (t_philo *)malloc(sizeof(*philosophers) * general->n_philo);
	forks = (pthread_mutex_t *)malloc(sizeof(*forks) * general->n_philo);
	int i = -1;
	while (++i < general->n_philo)
	{
		philosophers[i].printf_mutex = printf_mutex;

		philosophers[i].id = i + 1;
		philosophers[i].left_fork = i;
		if (i == general->n_philo - 1)
			philosophers[i].right_fork = 0;
		else
			philosophers[i].right_fork = i + 1;	
		pthread_mutex_init(&forks[i], NULL);
		


		philosophers[i].time_to_die = general->time_to_die;
		philosophers[i].time_to_eat = general->time_to_eat;
		philosophers[i].time_to_sleep = general->time_to_sleep;
		philosophers[i].satiety = general->satiety;

	}
	i = -1;
	while (++i < general->n_philo)
		philosophers[i].forks = forks;
	general->philosophers = philosophers;
	philosophers = NULL;
	forks = NULL;
}

long	timer()
{
	struct timeval temp;
	gettimeofday(&temp, NULL);
	long result = (long)(temp.tv_sec * 1000 + temp.tv_usec / 1000);
	return result;
}

void	printf_mod(pthread_mutex_t *printf_mutex, long time, int id, char *msg)
{
	pthread_mutex_lock(printf_mutex);
	printf("%ld %d %s", time, id, msg);
	pthread_mutex_unlock(printf_mutex);
}

void *philo_life(void *arg)
{
	t_philo *philosopher = (t_philo *)arg;

	long last_dinner = timer();
	long first_time = last_dinner;
	if (philosopher->id % 2 == 0)
		usleep(50);
	long time_status;

	while (1)
	{
		// printf("|%ld|*%ld*\n", (long)philosopher->time_to_die / 1000, time_status);	
		time_status = timer() - last_dinner;
		pthread_mutex_lock(&philosopher->forks[philosopher->left_fork]);
		pthread_mutex_lock(&philosopher->forks[philosopher->right_fork]);
		if ((long)philosopher->time_to_die / 1000 - time_status < 0)
		{
			pthread_mutex_unlock(&philosopher->forks[philosopher->left_fork]);
			pthread_mutex_unlock(&philosopher->forks[philosopher->right_fork]);
			printf("%ld %d IS DIED\n", timer() - first_time, philosopher->id);
			return (NULL);
		}
		printf_mod(philosopher->printf_mutex, timer() - first_time, philosopher->id, "is eating\n");
		last_dinner = timer();
		usleep(philosopher->time_to_eat);
		pthread_mutex_unlock(&philosopher->forks[philosopher->left_fork]);
		pthread_mutex_unlock(&philosopher->forks[philosopher->right_fork]);
		
		printf_mod(philosopher->printf_mutex, timer() - first_time, philosopher->id, "is thiking\n");
		

		printf_mod(philosopher->printf_mutex, timer() - first_time, philosopher->id, "is sleeping\n");
		

		usleep(philosopher->time_to_sleep);
		printf_mod(philosopher->printf_mutex, timer() - first_time, philosopher->id, "is thiking\n");
		

		if (philosopher->satiety > -1)
		{
			if (philosopher->satiety == 1)
			{
				printf("%ld %d IS SATIETY.\n", timer() - first_time, philosopher->id);
				return (NULL);
			}
			philosopher->satiety--;
		}
	}
}







int main(int argc, char **argv)
{
	t_general	*general;
	char *error = NULL;

	general = NULL;
	general = (t_general *)malloc(sizeof(*general));
	if (check_args(general, argc, argv) < 0)
	{
		ft_putstr_fd("Invalid arguments.", 1);
		free_data(general);
		return (-1);
	}

	init_threads(general);


	int i = -1;
	while (++i < general->n_philo)
		pthread_create(&general->philosophers[i].p_index, NULL, philo_life, &general->philosophers[i]);

	
	i = -1;
	while (++i < general->n_philo)
		pthread_join(general->philosophers[i].p_index, (void *)&error);

	// pthread_join(general->philosophers[0].p_index, NULL);
	printf("\n|%s|", error);
	printf("\n=========================\n%d", errno);
	return (0);
}