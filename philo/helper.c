/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:01:14 by marschul          #+#    #+#             */
/*   Updated: 2023/12/18 21:40:47 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

int	get_args(t_main_data *main_data, int argc, char **argv)
{
	main_data->nr_philosophers = ft_atoi(argv[1]);
	main_data->time_to_die = ft_atoi(argv[2]);
	main_data->time_to_eat = ft_atoi(argv[3]);
	main_data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		main_data->nr_meals = ft_atoi(argv[5]);
	else
		main_data->nr_meals = -1;
	if (gettimeofday(&main_data->start_time, NULL) != 0)
		return (0);
	return (1);
}

int	init_locks(t_main_data *main_data)
{
	int	i;

	if (pthread_mutex_init(&main_data->logger, NULL) != 0)
		return (0);
	i = 0;
	while (i < main_data->nr_philosophers)
	{
		if (pthread_mutex_init(&main_data->forks[i].fork_lock, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	fill_in_data(t_data *data, int i, t_main_data *main_data)
{
	data[i].number = i + 1;
	data[i].nr_philosophers = main_data->nr_philosophers;
	data[i].time_to_die = main_data->time_to_die;
	data[i].time_to_eat = main_data->time_to_eat;
	data[i].time_to_sleep = main_data->time_to_sleep;
	data[i].nr_meals = main_data->nr_meals;
	data[i].start_time = main_data->start_time;
	data[i].eat_time = main_data->start_time;
	data[i].logger = &main_data->logger;
	data[i].forks = main_data->forks;
	data[i].stop = &main_data->stop;
}

int	create_datastructures(t_main_data *main_data, pthread_t **threads, \
	t_data **data)
{
	int	i;

	*data = (t_data *) malloc(main_data->nr_philosophers * sizeof(t_data));
	if (*data == NULL)
		return (0);
	*threads = (pthread_t *) malloc(main_data->nr_philosophers * \
		sizeof(pthread_t));
	if (*threads == NULL)
		return (0);
	main_data->forks = (t_forks *) malloc(main_data->nr_philosophers * \
		sizeof(t_forks));
	if (main_data->forks == NULL)
		return (0);
	i = 0;
	while (i < main_data->nr_philosophers)
	{
		main_data->forks[i].fork = 0;
		fill_in_data(*data, i, main_data);
		i++;
	}
	main_data->stop = 0;
	return (1);
}
