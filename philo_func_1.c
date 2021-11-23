/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminna <sminna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:43:25 by sminna            #+#    #+#             */
/*   Updated: 2021/11/23 18:27:16 by sminna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_man(t_philo *philo)
{
	int	i;

	i = 0;
	philo->man = malloc((philo->num + 1) * sizeof(void **));
	if (!philo->man)
		free(philo);
	if (!philo->man)
		return (0);
	else
	{
		while (i <= philo->num)
		{
			philo->man[i] = malloc(sizeof(t_man));
			if (!(philo->man[i]))
				return (malloc_error(philo, i));
			i++;
		}
	}
	return (1);
}

void	eat_book(t_philo *philo, int n, int nn)
{
	if (philo->num > 1 && philo->man[n]->count_queue + \
	philo->man[n]->queue <= philo->mn)
	{
		pthread_mutex_lock(&philo->book);
		if (philo->man[n]->mut_e == 0 && philo->man[nn]->mut_e == 0)
		{
			philo->man[n]->mut_e = n + 1;
			philo->man[nn]->mut_e = n + 1;
		}
		pthread_mutex_unlock(&philo->book);
	}
}

void	time_print(int n, char *comand, t_philo *philo)
{
	_STRUCT_TIMEVAL	tm;
	int				now;

	pthread_mutex_lock(&philo->print);
	gettimeofday (&tm, NULL);
	now = ((tm.tv_sec * 1000) + (tm.tv_usec / 1000));
	if (philo->live)
		printf("%d %d %s\n", now - philo->start_time, n + 1, comand);
	pthread_mutex_unlock(&philo->print);
}

void	philo_sleep(int time, t_philo *philo, int n)
{
	_STRUCT_TIMEVAL	tm;
	int				t;
	int				start;
	int				now;

	t = 1;
	gettimeofday (&tm, NULL);
	start = ((tm.tv_sec * 1000) + (tm.tv_usec / 1000));
	while (t)
	{
		die_cheker(n, philo);
		gettimeofday (&tm, NULL);
		now = ((tm.tv_sec * 1000) + (tm.tv_usec / 1000));
		if (now >= start + time)
			t = 0;
		usleep(10);
	}
}

void	eat_time(int n, t_philo *philo)
{
	_STRUCT_TIMEVAL	tm;
	int				now;

	gettimeofday (&tm, NULL);
	now = ((tm.tv_sec * 1000) + (tm.tv_usec / 1000));
	philo->man[n]->eat_time = now;
	if (philo->man[n]->count_eat == philo->end)
		philo->x++;
}
