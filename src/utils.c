/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:04:20 by mcygan            #+#    #+#             */
/*   Updated: 2024/10/17 00:05:59 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;
	long	last;

	res = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		last = res;
		res = res * 10 + (*str - '0');
		if (res < last)
			return (~sign >> 1);
		str++;
	}
	return (res * sign);
}

size_t	time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	sleep_ms(size_t ms)
{
	size_t	start;

	start = time_ms();
	while ((time_ms() - start) < ms)
		usleep(500);
}

int	stop_val(t_philo *philo, int option)
{
	int	val;

	pthread_mutex_lock(philo->stop_lock);
	if (option)
		*philo->stop = 1;
	val = *philo->stop;
	pthread_mutex_unlock(philo->stop_lock);
	return (val);
}

void	print_msg(t_philo *philo, char *s)
{
	pthread_mutex_lock(philo->print_lock);
	if (!stop_val(philo, 0))
		printf("%ld\t%d %s\n", time_ms() - philo->start_time, philo->id, s);
	pthread_mutex_unlock(philo->print_lock);
}
