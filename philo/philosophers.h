/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:34:37 by marschul          #+#    #+#             */
/*   Updated: 2023/12/18 22:04:59 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_forks {
	int				fork;
	pthread_mutex_t	fork_lock;
}	t_forks;

typedef struct s_main_data {
	int				nr_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nr_meals;
	int				stop;
	struct timeval	start_time;
	pthread_mutex_t	logger;
	t_forks			*forks;
}	t_main_data;

typedef struct s_data {
	int				number;
	int				nr_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nr_meals;
	int				*stop;
	struct timeval	start_time;
	struct timeval	eat_time;
	pthread_mutex_t	*logger;
	t_forks			*forks;
}	t_data;

int				get_args(t_main_data *main_data, int argc, char **argv);
int				init_locks(t_main_data *main_data);
int				create_datastructures(t_main_data *main_data, pthread_t \
	**threads, t_data **data);
int				start_threads(t_main_data *main_data, pthread_t *threads, \
	t_data *data);
int				join_threads(t_main_data *main_data, pthread_t *threads);
void			*philosopher(void *data);
int				ft_atoi(const char *str);
unsigned int	get_ms(struct timeval start_time, struct timeval timestamp);
unsigned int	get_us(struct timeval start_time, struct timeval timestamp);
int				do_log(struct timeval timestamp, t_data *data, char *text);
int				wesleep(unsigned int goal, t_data *data);
int				die(int time_since_last_meal, t_data *data);
int				try_right_and_free_left(t_data *data, int left, int right);
int				try_forks(t_data *data, int left);
int				take_forks(t_data *data);

#endif