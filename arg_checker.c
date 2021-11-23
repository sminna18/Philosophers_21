/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminna <sminna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:10:40 by sminna            #+#    #+#             */
/*   Updated: 2021/11/19 17:51:11 by sminna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	big_cheker3(char argv, char num)
{
	if (num < argv)
		return (0);
	return (1);
}

int	big_cheker2(char *argv)
{
	if (argv[0] != '2')
		return (big_cheker3(argv[0], '2'));
	if (argv[1] != '1')
		return (big_cheker3(argv[1], '1'));
	if (argv[2] != '4')
		return (big_cheker3(argv[2], '4'));
	if (argv[3] != '7')
		return (big_cheker3(argv[3], '7'));
	if (argv[4] != '4')
		return (big_cheker3(argv[4], '4'));
	if (argv[5] != '8')
		return (big_cheker3(argv[5], '8'));
	if (argv[6] != '3')
		return (big_cheker3(argv[6], '3'));
	if (argv[7] != '6')
		return (big_cheker3(argv[7], '6'));
	if (argv[8] != '4')
		return (big_cheker3(argv[8], '4'));
	if (argv[9] != '8')
		return (big_cheker3(argv[9], '8'));
	return (0);
}

int	big_cheker(int argc, char **argv)
{
	int	i;
	int	l;

	i = 1;
	while (i < argc)
	{
		l = 0;
		if (argv[i][0] && argv[i][0] == '0')
			return (0);
		while (argv[i][l])
		{
			l++;
			if (l > 10)
				return (0);
		}
		if (l == 10)
			return (big_cheker2(argv[i]));
		i++;
	}
	return (1);
}

int	handling(int argc, char **argv, t_philo *philo)
{
	philo->end_e = 0;
	if (argc == 5 || argc == 6)
	{
		philo->num = atoi(argv[1]);
		philo->t_d = atoi(argv[2]);
		philo->t_e = atoi(argv[3]);
		philo->t_s = atoi(argv[4]);
	}
	if (argc == 6)
	{
		philo->end = atoi(argv[5]);
		philo->end_e = 1;
	}
	if (argc == 5 || argc == 6)
		return (1);
	return (0);
}

int	chek_inf(int argc, char **argv)
{
	int	i;
	int	l;

	i = 1;
	while (i < argc)
	{
		l = 0;
		while (argv[i][l])
		{
			if (argv[i][l] < 48 || argv[i][l] > 57)
				return (0);
			l++;
		}
		i++;
	}
	return (big_cheker(argc, argv));
}
