/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:35:26 by mkling            #+#    #+#             */
/*   Updated: 2025/01/14 00:16:20 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <errno.h>

typedef struct s_waiter	t_waiter;

enum e_argv
{
	NUMBER_OF_PHILOSOPHER	= 1,
	TIME_TO_DIE				= 2,
	TIME_TO_EAT				= 3,
	TIME_TO_SLEEP			= 4,
	NUMBER_OF_MEALS			= 5
};

enum e_philo_states
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
};

enum e_time
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS,
};

enum e_errors
{
	SUCCESS,
	ERR_GENERAL,
	ERR_MALLOC,
	ERR_MUTEX,
	ERR_THREAD,
};

typedef struct s_philo
{
	int				id;
	int				is_sated;
	int				meal_count;
	int				last_meal_time;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	philo_mutex;
	pthread_t		thread;
	t_waiter		*waiter;
}	t_philo;

typedef struct s_waiter
{
	int				is_dinner_ongoing;
	int				is_ready;
	int				philo_total;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				start_time;
	t_philo			**philo_array;
	pthread_mutex_t	waiter_mutex;
	pthread_mutex_t	write_mutex;
}	t_waiter;

/* PARSING */

int		parse_for_waiter(int argc, char **argv, t_waiter *waiter);

/* INITIALIZATION */

int		set_table(t_waiter *waiter);
void	wait_until_philo_are_seated(t_waiter *waiter);
int		start_dinner(t_waiter *waiter);

/* MONITORING */

int		write_status(int status, t_philo *philo, bool debug);
size_t	get_actual_time(void);
size_t	get_miliseconds(void);
void	micro_usleep(size_t wait_time, t_waiter *waiter);
bool	dinner_has_ended(t_waiter *waiter);

/* UTILS */

int		setter(pthread_mutex_t *mutex, int *destination, int value);
int		getter(pthread_mutex_t *mutex, int *value);

/* ERROR HANDLING */

int		print_error(int error_code);

/* CLEAN UP */

void	clean_up(t_waiter *waiter);

#endif
