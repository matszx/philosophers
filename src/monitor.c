/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:01:14 by mcygan            #+#    #+#             */
/*   Updated: 2024/10/15 23:26:18 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	meals_eaten_check(t_philo *philos, int n_philo)
{
	int	i;

	if (philos->meals_to_eat < 1)
		return (0);
	i = -1;
	while (++i < n_philo)
	{
		pthread_mutex_lock(philos->info_lock);
		if (philos[i].meals_eaten < philos->meals_to_eat)
			return (pthread_mutex_unlock(philos->info_lock), 0);
		pthread_mutex_unlock(philos->info_lock);
	}
	return (stop_val(&philos[0], 1));
}

static int	starvation_check(t_philo *philos, int n_philo)
{
	int	i;

	i = -1;
	while (++i < n_philo)
	{
		pthread_mutex_lock(philos->info_lock);
		if (philos[i].time_to_die < time_ms() - philos[i].last_meal)
		{
			stop_val(&philos[0], 1);
			pthread_mutex_lock(philos->print_lock);
			printf("%ld\t%d %s\n", time_ms() - philos->start_time, i + 1, \
				VM "died" RESET);
			pthread_mutex_unlock(philos->print_lock);
			pthread_mutex_unlock(philos->info_lock);
			return (1);
		}
		pthread_mutex_unlock(philos->info_lock);
	}
	return (0);
}

void	*monitor(void *table_ptr)
{
	t_table	*table;

	table = table_ptr;
	while (1)
	{
		if (starvation_check(table->philos, table->n_philo))
			break ;
		if (meals_eaten_check(table->philos, table->n_philo))
			break ;
	}
	return (NULL);
}
