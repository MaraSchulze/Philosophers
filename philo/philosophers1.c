/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:36:21 by marschul          #+#    #+#             */
/*   Updated: 2023/12/18 22:02:07 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>
#include <unistd.h>

void	unlock_forks(t_data *data, int left, int right)
{
	pthread_mutex_lock(&data->forks[left].fork_lock);
	data->forks[left].fork = -data->number;
	pthread_mutex_unlock(&data->forks[left].fork_lock);
	pthread_mutex_lock(&data->forks[right].fork_lock);
	data->forks[right].fork = -data->number;
	pthread_mutex_unlock(&data->forks[right].fork_lock);
}

int	eat(t_data *data)
{
	struct timeval	timestamp;
	int				left;
	int				right;
	int				time_since_last_meal;

	if (gettimeofday(&timestamp, NULL) != 0)
		return (0);
	left = data->number - 1;
	right = data->number % data->nr_philosophers;
	data->eat_time = timestamp;
	time_since_last_meal = get_ms(data->eat_time, timestamp);
	if (!(time_since_last_meal + data->time_to_eat > data->time_to_die))
	{
		if (do_log(timestamp, data, "is eating") == 0)
			return (0);
		if (wesleep(data->time_to_eat, data) == 0)
			return (0);
	}
	unlock_forks(data, left, right);
	if (time_since_last_meal + data->time_to_eat > data->time_to_die)
		return (die(time_since_last_meal, data));
	return (1);
}

int	do_sleep(t_data *data)
{
	struct timeval	timestamp1;
	struct timeval	timestamp2;
	int				time_since_last_meal;

	if (gettimeofday(&timestamp1, NULL) != 0)
		return (0);
	time_since_last_meal = get_ms(data->eat_time, timestamp1);
	if (time_since_last_meal + data->time_to_sleep > data->time_to_die)
		return (die(time_since_last_meal, data));
	if (do_log(timestamp1, data, "is sleeping") == 0)
		return (0);
	if (wesleep(data->time_to_eat + data->time_to_sleep, data) == 0)
		return (0);
	if (gettimeofday(&timestamp2, NULL) != 0)
		return (0);
	if (do_log(timestamp2, data, "is thinking") == 0)
		return (0);
	return (1);
}

void	*philosopher(void *data)
{
	t_data	*this_data;
	int		loops;

	this_data = (t_data *) data;
	loops = this_data->nr_meals;
	while (loops != 0)
	{
		if (take_forks(this_data) == 0)
			return (NULL);
		if (eat(this_data) == 0)
			return (NULL);
		if (do_sleep(this_data) == 0)
			return (NULL);
		loops--;
	}
	return (NULL);
}
