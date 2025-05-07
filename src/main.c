/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:52:50 by mcygan            #+#    #+#             */
/*   Updated: 2024/11/04 12:24:09 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	check_input(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("philo error:\tinvalid argument count\n"), 1);
	if (ft_atoi(av[1]) < 1
		|| ft_atoi(av[2]) < 1
		|| ft_atoi(av[3]) < 1
		|| ft_atoi(av[4]) < 1
		|| (av[5] && ft_atoi(av[5]) < 1))
		return (printf("philo error:\targuments must be positive int\n"), 1);
	if (ft_atoi(av[1]) > PHILO_MAX)
		return (printf("philo error:\tmodify PHILO_MAX to go over "
				"%d philosophers\n", PHILO_MAX), 1);
	return (0);
}

static void	cleanup(t_table *table)
{
	while (table->n_philo--)
		pthread_mutex_destroy(&table->forks[table->n_philo]);
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->info_lock);
	pthread_mutex_destroy(&table->stop_lock);
}

static void	init_philos(t_table *table)
{
	int		i;

	i = -1;
	while (++i < table->n_philo)
		pthread_mutex_init(&table->forks[i], NULL);
	i = -1;
	while (++i < table->n_philo)
	{
		table->philos[i].stop = &table->stop;
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal = table->start_time;
		table->philos[i].start_time = table->start_time;
		table->philos[i].time_to_die = table->time_to_die;
		table->philos[i].time_to_eat = table->time_to_eat;
		table->philos[i].time_to_sleep = table->time_to_sleep;
		table->philos[i].meals_to_eat = table->meals_to_eat;
		table->philos[i].l_fork = &table->forks[i];
		table->philos[i].r_fork = &table->forks[(i + 1) % table->n_philo];
		table->philos[i].print_lock = &table->print_lock;
		table->philos[i].info_lock = &table->info_lock;
		table->philos[i].stop_lock = &table->stop_lock;
	}
}

static void	init_table(t_table *table, char **av)
{
	table->stop = 0;
	table->n_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->meals_to_eat = ft_atoi(av[5]);
	else
		table->meals_to_eat = 0;
	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->info_lock, NULL);
	pthread_mutex_init(&table->stop_lock, NULL);
	table->start_time = time_ms();
	init_philos(table);
}

int	main(int ac, char **av)
{
	t_table			table;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (check_input(ac, av))
		return (1);
	table.philos = philos;
	table.forks = forks;
	init_table(&table, av);
	if (start_simulation(&table))
		return (printf("philosophers: thread error\n"), cleanup(&table), 1);
	return (cleanup(&table), 0);
}
