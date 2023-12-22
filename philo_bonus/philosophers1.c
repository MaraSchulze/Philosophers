/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:36:21 by marschul          #+#    #+#             */
/*   Updated: 2023/12/19 02:45:38 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>
#include <unistd.h>

int	eat(t_data *data)
{
	struct timeval	timestamp;

	if (gettimeofday(&timestamp, NULL) != 0)
		return (0);
	pthread_mutex_lock(data->logger);
	data->eat_time = timestamp;
	pthread_mutex_unlock(data->logger);
	if (do_log(timestamp, data, "is eating") == 0)
		return (0);
	if (wesleep(data->time_to_eat, data) == 0)
		return (0);
	if (sem_post(data->sem) != 0)
		return (0);
	if (sem_post(data->sem) != 0)
		return (0);
	return (1);
}

int	do_sleep(t_data *data)
{
	struct timeval	timestamp1;
	struct timeval	timestamp2;

	if (gettimeofday(&timestamp1, NULL) != 0)
		return (0);
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
