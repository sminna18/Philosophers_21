/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminna <sminna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:43:16 by sminna            #+#    #+#             */
/*   Updated: 2021/11/23 14:47:41 by sminna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_live(t_philo *philo, int n, int nn)
{
	while (philo->live)
	{
		eat_book(philo, n, nn);
		if (philo->man[n]->mut_e == n + 1 && philo->man[nn]->mut_e == n + 1)
		{
			pthread_mutex_lock(&philo->man[n]->mutex);
			pthread_mutex_lock(&philo->man[nn]->mutex);
			time_print(n, "is eating", philo);
			philo->man[n]->count_eat++;
			eat_time(n, philo);
			philo->man[n]->count_queue += philo->num;
			philo_sleep(philo->t_e, philo, n);
			time_print(n, "is sleepling", philo);
			philo->man[n]->mut_e = 0;
			philo->man[nn]->mut_e = 0;
			pthread_mutex_unlock(&philo->man[n]->mutex);
			pthread_mutex_unlock(&philo->man[nn]->mutex);
			philo_sleep(philo->t_s, philo, n);
			time_print(n, "is thinking", philo);
		}
		die_cheker(n, philo);
	}
}

void	*creat_philo(t_philo *philo)
{
	int	n;
	int	nn;

	n = numering_program(philo);
	nn = (n + 1) % philo->num;
	pthread_mutex_init(&philo->man[n]->mutex, NULL);
	philo_live(philo, n, nn);
	return (NULL);
}

void	numbering_philo(t_philo *philo)
{
	int	i;
	int	q;

	i = 0;
	q = 1;
	while (i < philo->num)
	{
		philo->man[i]->queue = q;
		if (q == 1)
			q = 2;
		else
			q = 1;
		i++;
	}
	i--;
	if ((philo->num % 2) == 1)
	philo->man[i]->queue = 3;
}

void	prep_prog(t_philo *philo)
{
	struct timeval	tm;
	int				i;

	philo->n_man = 0;
	philo->x = 0;
	pthread_mutex_init(&philo->book, NULL);
	pthread_mutex_init(&philo->numbering, NULL);
	pthread_mutex_init(&philo->print, NULL);
	philo->live = 1;
	i = 0;
	numbering_philo(philo);
	while (i < philo->num)
	{
		philo->man[i]->mut_e = 0;
		philo->man[i]->count_eat = 0;
		philo->man[i]->count_queue = 0;
		eat_time(i, philo);
		i++;
	}
	gettimeofday (&tm, NULL);
	philo->start_time = ((tm.tv_sec * 1000) + (tm.tv_usec / 1000));
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof (t_philo));
	philo->live = 0;
	if (chek_inf(argc, argv) && handling(argc, argv, philo))
	{
		create_man(philo);
		prep_prog(philo);
		i = 0;
		pthread_create(&philo->man[philo->num]->t, NULL, \
		(void *)creat_min, philo);
		while (i < philo->num)
		{
			pthread_create(&philo->man[i]->t, NULL, (void *)creat_philo, philo);
			i++;
		}
	}
	else
		printf("Error\n");
	while (philo->live)
		if (philo->end_e)
			end_checker(philo);
	philo_destroy(philo);
	return (1);
}
