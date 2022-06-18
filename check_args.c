
#include "philosophers.h"

int	check_args(t_general *general, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (-1);
	general->n_philo = ft_atoi(argv[1]);
	general->time_to_die = ft_atoi(argv[2]) * 1000;
	general->time_to_eat = ft_atoi(argv[3]) * 1000;
	general->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
	{
		general->satiety = ft_atoi(argv[5]);
		if (general->satiety <= 0)
		{
			printf("%s\n", "Philosophers isn't hungry.");
			return (-1);
		}
	}
	else
		general->satiety = -1;
	if (general->n_philo <= 1 || general->time_to_die <= 0 ||
		general->time_to_eat <= 0 || general->time_to_sleep <= 0)
		return (-1);
}
