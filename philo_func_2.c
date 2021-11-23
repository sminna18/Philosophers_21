/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminna <sminna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:43:22 by sminna            #+#    #+#             */
/*   Updated: 2021/11/23 14:08:54 by sminna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	malloc_error(t_philo *philo, int i)
{
	int	l;

	l = 0;
	while (l < i)
	{
		free(philo->man[l]);
		l++;
	}
	free(philo);
	return (0);
}

void	kill_everyone(t_philo *philo)
{
	int	n;

	n = 0;
	while (n <= philo->num)
	{
		pthread_detach(philo->man[n]->t);
		n++;
	}
}

void	end_checker(t_philo *philo)
{
	if (philo->x >= philo->num)
	{
		philo->live = 0;
		kill_everyone(philo);
	}
}

void	die_cheker(int n, t_philo *philo)
{
	_STRUCT_TIMEVAL	tm;
	int				now;

	gettimeofday (&tm, NULL);
	now = ((tm.tv_sec * 1000) + (tm.tv_usec / 1000));
	if (now >= philo->man[n]->eat_time + philo->t_d && philo->live)
	{
		philo->live = 0;
		printf("%d %d died\n", now - philo->start_time, n);
		kill_everyone(philo);
	}
}

int	numering_program(t_philo *philo)
{
	int	n;

	pthread_mutex_lock(&philo->numbering);
	n = philo->n_man;
	philo->n_man++;
	pthread_mutex_unlock(&philo->numbering);
	return (n);
}
