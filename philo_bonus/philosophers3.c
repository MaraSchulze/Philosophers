/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:58:48 by marschul          #+#    #+#             */
/*   Updated: 2023/12/22 09:37:04 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>
#include <unistd.h>

unsigned int	get_ms(struct timeval start_time, struct timeval timestamp)
{
	unsigned int	diff_sec;
	unsigned int	diff_usec;
	unsigned int	diff;

	diff_sec = (timestamp.tv_sec - start_time.tv_sec) * 1000;
	diff_usec = (timestamp.tv_usec - start_time.tv_usec) / 1000;
	diff = diff_sec + diff_usec;
	return (diff);
}

unsigned int	get_us(struct timeval start_time, struct timeval timestamp)
{
	unsigned int	diff_sec;
	unsigned int	diff_usec;
	unsigned int	diff;

	diff_sec = (timestamp.tv_sec - start_time.tv_sec) * 1000 * 1000;
	diff_usec = (timestamp.tv_usec - start_time.tv_usec);
	diff = diff_sec + diff_usec;
	return (diff);
}

int	do_log(struct timeval timestamp, t_data *data, char *text)
{
	if (*data->stop == 1)
	{
		sem_post(data->sem);
		sem_post(data->sem);
		return (0);
	}
	pthread_mutex_lock(data->logger);
	printf("%d %d %s\n", get_ms(data->start_time, timestamp), \
		data->number, text);
	pthread_mutex_unlock(data->logger);
	return (1);
}

int	wesleep(unsigned int goal, t_data *data)
{
	struct timeval	now;
	unsigned int	t;

	t = 0;
	while (t < (goal - 1) * 1000)
	{
		if (gettimeofday(&now, NULL) != 0)
			return (0);
		t = get_us(data->eat_time, now);
		usleep(50);
	}
	usleep(700);
	return (1);
}
