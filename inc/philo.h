/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:37:42 by mcygan            #+#    #+#             */
/*   Updated: 2024/10/17 13:36:09 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

# define VM		"\x1b[1;38;5;203m"	// vermillion
# define RESET	"\x1b[0m"			// reset

# define PHILO_MAX	200

typedef struct s_philo
{
	int				*stop;
	int				id;
	int				meals_eaten;
	size_t			last_meal;

	int				n_philo;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				meals_to_eat;

	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*info_lock;
	pthread_mutex_t	*stop_lock;
}	t_philo;

typedef struct s_table
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				stop;

	int				n_philo;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				meals_to_eat;

	pthread_mutex_t	print_lock;
	pthread_mutex_t	info_lock;
	pthread_mutex_t	stop_lock;
}	t_table;

// routine.c
int			start_simulation(t_table *table);

// monitor.c
void		*monitor(void *table_ptr);

// utils.c
int			ft_atoi(const char *str);
size_t		time_ms(void);
void		sleep_ms(size_t ms);
int			stop_val(t_philo *philo, int option);
void		print_msg(t_philo *philo, char *s);

#endif
