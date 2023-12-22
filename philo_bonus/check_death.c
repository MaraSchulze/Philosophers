/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:52:50 by marschul          #+#    #+#             */
/*   Updated: 2023/12/19 05:55:02 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

void	*execute_death(t_data *data, struct timeval timestamp)
{
	int	i;

	do_log(timestamp, data, "died");
	pthread_mutex_lock(data->logger);
	*data->stop = 1;
	pthread_mutex_unlock(data->logger);
	i = 0;
	while (i++ < 2 * data->nr_philosophers)
		sem_post(data->sem);
	return (NULL);
}

void	*check_death(void *data)
{
	t_data			*data_array;
	int				detected_death;
	int				i;
	struct timeval	timestamp;
	struct timeval	t;

	data_array = (t_data *) data;
	detected_death = 0;
	while (detected_death != 1)
	{
		i = 0;
		while (i < data_array[0].nr_philosophers)
		{
			if (gettimeofday(&timestamp, NULL) != 0)
				return (NULL);
			pthread_mutex_lock(data_array[i].logger);
			t = data_array[i].eat_time;
			pthread_mutex_unlock(data_array[i].logger);
			if (get_ms(t, timestamp) > (unsigned int) data_array[i].time_to_die)
				return (execute_death(&data_array[i], timestamp));
		}
	}
	return (NULL);
}
