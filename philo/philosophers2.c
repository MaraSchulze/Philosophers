/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:58:52 by marschul          #+#    #+#             */
/*   Updated: 2023/12/18 22:02:17 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>
#include <unistd.h>

int	die(int time_since_last_meal, t_data *data)
{
	struct timeval	timestamp;
	int				dying_time;

	dying_time = data->time_to_die - time_since_last_meal - 1;
	if (dying_time > 0)
		usleep(dying_time * 1000);
	if (gettimeofday(&timestamp, NULL) != 0)
		return (0);
	if (do_log(timestamp, data, "died") == 0)
		return (0);
	pthread_mutex_lock(data->logger);
	*data->stop = 1;
	pthread_mutex_unlock(data->logger);
	return (0);
}

int	try_right_and_free_left(t_data *data, int left, int right)
{
	int	old;

	old = data->forks[left].fork;
	data->forks[left].fork = data->number;
	pthread_mutex_unlock(&data->forks[left].fork_lock);
	pthread_mutex_lock(&data->forks[right].fork_lock);
	if (data->forks[right].fork == 0 || (data->forks[right].fork < 0 \
		&& data->forks[right].fork != -data->number))
	{
		data->forks[right].fork = data->number;
		pthread_mutex_unlock(&data->forks[right].fork_lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[right].fork_lock);
		pthread_mutex_lock(&data->forks[left].fork_lock);
		data->forks[left].fork = old;
		pthread_mutex_unlock(&data->forks[left].fork_lock);
		return (0);
	}
}

int	try_forks(t_data *data, int left)
{
	int	right;

	right = data->number % data->nr_philosophers;
	pthread_mutex_lock(&data->forks[left].fork_lock);
	if (data->forks[left].fork == 0 || (data->forks[left].fork < 0 && \
		data->forks[left].fork != -data->number))
		return (try_right_and_free_left(data, left, right));
	else
	{
		pthread_mutex_unlock(&data->forks[left].fork_lock);
		return (0);
	}
}

int	take_forks(t_data *data)
{
	int				success;
	struct timeval	timestamp;
	unsigned int	time_since_last_meal;

	success = 0;
	while (success != 1)
	{
		if (gettimeofday(&timestamp, NULL) != 0)
			return (0);
		time_since_last_meal = get_us(data->eat_time, timestamp);
		if (time_since_last_meal > (unsigned int) data->time_to_die * 1000)
			return (die(time_since_last_meal, data));
		success = try_forks(data, data->number - 1);
	}
	if (gettimeofday(&timestamp, NULL) != 0)
		return (0);
	if (do_log(timestamp, data, "has taken a fork") == 0)
		return (0);
	return (1);
}
