/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sminna <sminna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:42:24 by sminna            #+#    #+#             */
/*   Updated: 2021/11/23 18:26:28 by sminna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_man {
	pthread_t	t;
	int			eat_time;
	t_mutex		mutex;
	int			mut_e;
	int			count_eat;
	int			queue;
	int			count_queue;
}				t_man;

typedef struct s_philo {
	int		num;
	int		t_d;
	int		t_e;
	int		t_s;
	int		end;
	int		end_e;
	int		live;
	int		start_time;
	int		x;
	t_mutex	book;
	t_mutex	numbering;
	t_mutex	print;
	t_man	**man;
	int		n_man;
	int		mn;
}				t_philo;

int		chek_inf(int argc, char **argv);
int		handling(int argc, char **argv, t_philo *philo);
int		ft_atoi(const char *str);
int		create_man(t_philo *philo);
void	*creat_min(t_philo *philo);
void	eat_book(t_philo *philo, int n, int nn);
void	time_print(int n, char *comand, t_philo *philo);
void	philo_sleep(int time, t_philo *philo, int n);
void	eat_time(int n, t_philo *philo);
int		malloc_error(t_philo *philo, int i);
void	kill_everyone(t_philo *philo);
void	die_cheker(int n, t_philo *philo);
void	end_checker(t_philo *philo);
int		numering_program(t_philo *philo);
void	philo_destroy(t_philo *philo);

#endif