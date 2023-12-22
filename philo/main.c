/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:35:52 by marschul          #+#    #+#             */
/*   Updated: 2023/12/18 22:12:49 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	pthread_t	*threads;
	t_main_data	main_data;
	t_data		*data;

	if (argc < 5 || argc > 6)
		return (-1);
	if (get_args(&main_data, argc, argv) == 0)
		return (-1);
	if (create_datastructures(&main_data, &threads, &data) == 0)
		return (-1);
	if (init_locks(&main_data) == 0)
		return (-1);
	if (start_threads(&main_data, threads, data) == 0)
		return (-1);
	join_threads(&main_data, threads);
	free(threads);
	free(main_data.forks);
	free(data);
}
