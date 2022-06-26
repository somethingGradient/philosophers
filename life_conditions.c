/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_conditions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 17:20:50 by akitty            #+#    #+#             */
/*   Updated: 2022/06/26 17:20:53 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_think(t_data *data, t_philo *philo)
{
	if (data->death_status)
		return (1);
	printf_mod(data, philo->id, "is thinking\n", BLUE);
	return (0);
}

int	philo_sleep(t_data *data, t_philo *philo)
{
	if (data->death_status)
		return (1);
	printf_mod(data, philo->id, "is sleeping\n", GRAY);
	ft_sleep(data->rules->time_to_sleep);
	return (0);
}

int	philo_eat(t_data *data, t_philo *philo)
{
	if (data->death_status)
		return (1);
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	printf_mod(data, philo->id, "has taken a fork\n", CYAN);
	if (data->rules->n_philo == 1)
	{
		data->flag_for_checker = 1;
		return (pthread_mutex_unlock(&data->forks[philo->left_fork]), 1);
	}
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	printf_mod(data, philo->id, "has taken a fork\n", CYAN);
	printf_mod(data, philo->id, "is eating\n", GREEN);
	ft_sleep(data->rules->time_to_eat);
	philo->last_dinner = timer();
	philo->n_dinner--;
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	return (0);
}

int	check_conditions(t_data *data, int i, int mode)
{
	if (!mode)
	{
		pthread_mutex_unlock(&data->forks[data->phils[i].left_fork]);
		pthread_mutex_unlock(&data->forks[data->phils[i].right_fork]);
		data->death_status = 1;
		printf_mod(data, data->phils[i].id, "is died\n", RED);
		pthread_mutex_lock(&data->printf_mutex);
		usleep(10);
		pthread_mutex_unlock(&data->printf_mutex);
	}
	else
	{
		data->phils[i].n_dinner = -1;
		data->satiety_status += 1;
		if (data->satiety_status == data->rules->n_philo)
		{
			data->death_status = 1;
			return (1);
		}
	}
	return (0);
}
