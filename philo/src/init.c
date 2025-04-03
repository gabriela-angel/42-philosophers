/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:29:14 by gangel-a          #+#    #+#             */
/*   Updated: 2025/04/03 20:29:30 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(int argc, char **argv, t_philo *threads, int pos)
{
	threads[pos].id = pos + 1;
	threads[pos].time_to_die = ft_atol(argv[2]);
	threads[pos].time_to_eat = ft_atol(argv[3]);
	threads[pos].time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		threads[pos].times_each_eat = ft_atol(argv[5]);
	else
		threads[pos].times_each_eat = -1;
	if (pos != 0)
		threads[pos].previous = &threads[pos - 1];
	if (pos != ft_atol(argv[1]) - 1)
		threads[pos].next = &threads[pos + 1];
	else
	{
		threads[pos].next = &threads[0];
		threads[0].previous = &threads[pos];
	}
	threads[pos].forks = (int *)ft_malloc(sizeof(int) * 2);
	if (!threads[pos].forks)
		handle_error(MALLOC_ERROR);
	threads[pos].forks[0] = 0;
	threads[pos].forks[1] = 0;
	pthread_mutex_init(&threads[pos].fork_lock, NULL);
}

void	init_threads(int argc, char **argv)
{
	int		i;
	int		n_of_philos;
	t_table	*table;
	t_philo	*threads;

	i = -1;
	n_of_philos = ft_atol(argv[1]);
	table = get_table();
	threads = (t_philo *)ft_malloc(sizeof(t_philo) * n_of_philos);
	if (!threads)
		handle_error(MALLOC_ERROR);
	while (++i < n_of_philos)
		init_philos(argc, argv, threads, i);
	table->threads = threads;
	table->n_of_philos = n_of_philos;
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->times_each_eat = ft_atol(argv[5]);
	else
		table->times_each_eat = -1;
}
