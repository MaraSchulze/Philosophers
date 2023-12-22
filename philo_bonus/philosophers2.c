/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:58:52 by marschul          #+#    #+#             */
/*   Updated: 2023/12/22 09:35:09 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>
#include <unistd.h>

int	take_forks(t_data *data)
{
	struct timeval	timestamp;

	while (*data->stop != 1 && *data->token != data->number - 1)
		usleep(10);
	if (sem_wait(data->sem) != 0)
		return (0);
	if (gettimeofday(&timestamp, NULL) != 0)
		return (0);
	if (do_log(timestamp, data, "has taken a fork") == 0)
		return (0);
	if (sem_wait(data->sem) != 0)
		return (0);
	if (gettimeofday(&timestamp, NULL) != 0)
		return (0);
	if (do_log(timestamp, data, "has taken a fork") == 0)
		return (0);
	*data->token = ((*data->token + 1) % data->nr_philosophers);
	return (1);
}
