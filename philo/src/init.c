/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:29:14 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/23 00:33:17 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_forks(t_table *table)
{
	int	i;

	table->fork_locks = (pthread_mutex_t *)ft_malloc(sizeof(pthread_mutex_t) \
		* table->n_of_philos);
	if (!table->fork_locks)
		handle_error(MALLOC_ERROR, 0, table->n_of_philos - 1);
	i = 0;
	while (i < table->n_of_philos)
	{
		if (pthread_mutex_init(&table->fork_locks[i], NULL) != 0)
			handle_error(MUTEX_ERROR, 1, i - 1);
		i++;
	}
}

static void	init_table_mutexes(t_table *table)
{
	init_forks(table);
	if (pthread_mutex_init(&table->stop_lock, NULL) != 0)
		handle_error(MUTEX_ERROR, 2, -1);
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		handle_error(MUTEX_ERROR, 3, -1);
	if (pthread_mutex_init(&table->start_lock, NULL) != 0)
		handle_error(MUTEX_ERROR, 4, -1);
}

static void	init_threads(t_table *table)
{
	int		i;

	i = 0;
	table->threads = (t_philo *)ft_malloc(sizeof(t_philo) * table->n_of_philos);
	if (!table->threads)
		handle_error(MALLOC_ERROR, -1, -1);
	while (i < table->n_of_philos)
	{
		if (pthread_mutex_init(&(table->threads[i]).meal_lock, NULL) != 0)
			handle_error(MUTEX_ERROR, 0, (i - 1));
		table->threads[i].id = i;
		table->threads[i].times_ate = 0;
		table->threads[i].forks[0] = table->threads[i].id;
		table->threads[i].forks[1] = \
			(table->threads[i].id + 1) % table->n_of_philos;
		if (i % 2 == 0)
		{
			table->threads[i].forks[0] = \
				(table->threads[i].id + 1) % table->n_of_philos;
			table->threads[i].forks[1] = table->threads[i].id;
		}
		i++;
	}
}

void	init_table(int argc, char **argv)
{
	t_table	*table;

	table = get_table();
	table->all_created = FALSE;
	table->n_of_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->times_each_eat = ft_atol(argv[5]);
	else
		table->times_each_eat = -1;
	table->stop_sim = FALSE;
	init_threads(table);
	if (!table->threads)
		handle_error(THREAD_ERROR, 0, table->n_of_philos - 1);
	init_table_mutexes(table);
}
