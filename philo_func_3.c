/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminna <sminna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:17:47 by sminna            #+#    #+#             */
/*   Updated: 2021/11/23 14:48:04 by sminna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_destroy(t_philo *philo)
{
	int	n;

	n = 0;
	while (n < philo->num)
	{
		pthread_mutex_destroy(&philo->man[n]->mutex);
		n++;
	}
	if (philo->num > 0)
	{
		pthread_mutex_destroy(&philo->book);
		pthread_mutex_destroy(&philo->numbering);
		pthread_mutex_destroy(&philo->print);
	}
}

void	*creat_min(t_philo *philo)
{
	int	i;
	int	min;

	philo->mn = 0;
	while (philo->live)
	{
		i = 0;
		min = philo->man[i]->count_queue + philo->man[i]->queue;
		while (i < philo->num)
		{
			if ((philo->man[i]->count_queue + philo->man[i]->queue) < min)
					min = philo->man[i]->count_queue + philo->man[i]->queue;
			i++;
		}
		if (philo->mn != min)
			philo->mn = min;
	}
	return (NULL);
}
