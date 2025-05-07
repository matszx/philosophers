/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:46:19 by mcygan            #+#    #+#             */
/*   Updated: 2024/11/04 11:59:11 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_msg(philo, "has taken a fork");
	if (philo->l_fork == philo->r_fork)
	{
		sleep_ms(philo->time_to_die + 10);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(philo->info_lock);
	print_msg(philo, "is eating");
	philo->last_meal = time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->info_lock);
	sleep_ms(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static void	think(t_philo *philo)
{
	print_msg(philo, "is thinking");
}

static void	nap(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	sleep_ms(philo->time_to_sleep);
}

static void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = philo_ptr;
	if (philo->id % 2 == 0)
		sleep_ms(philo->time_to_eat / 2);
	while (!stop_val(philo, 0))
	{
		eat(philo);
		nap(philo);
		think(philo);
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	pthread_t	monitor_thread;
	int			i;

	if (pthread_create(&monitor_thread, NULL, &monitor, table))
		return (1);
	i = -1;
	while (++i < table->n_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, \
			&philo_routine, &table->philos[i]))
			return (1);
	}
	if (pthread_join(monitor_thread, NULL))
		return (1);
	i = -1;
	while (++i < table->n_philo)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			return (1);
	}
	return (0);
}
