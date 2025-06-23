/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:14:32 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/22 22:40:37 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, t_action action)
{
	t_table	*table;
	int		timestamp;

	table = get_table();
	pthread_mutex_lock(&table->print_lock);
	timestamp = get_time_in_ms() - table->start_time;
	if (!stop_simulation(0))
	{
		if (action == TAKE_FORK)
			printf("%d %d has taken a fork\n", timestamp, (philo->id + 1));
		else if (action == EAT)
			printf("%d %d is eating\n", timestamp, (philo->id + 1));
		else if (action == SLEEP)
			printf("%d %d is sleeping\n", timestamp, (philo->id + 1));
		else if (action == THINK)
			printf("%d %d is thinking\n", timestamp, (philo->id + 1));
		else if (action == DIE)
			printf("%d %d died\n", timestamp, (philo->id + 1));
	}
	pthread_mutex_unlock(&table->print_lock);
}

static void	join_threads(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->n_of_philos)
	{
		if (pthread_join(table->threads[i].thread, NULL) != 0)
			handle_error(JOIN_ERROR, 4, -1);
		i++;
	}
	if (table->n_of_philos > 1)
	{
		if (pthread_join(table->manager, NULL) != 0)
			handle_error(JOIN_ERROR, 4, -1);
	}
}

static void	start_simulation(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->n_of_philos)
	{
		if (pthread_create(&(table->threads[i].thread), NULL,
				&routine, &(table->threads[i])) != 0)
			handle_error(THREAD_ERROR, 4, -1);
		i++;
	}
	if (table->n_of_philos > 1)
	{
		if (pthread_create(&(table->manager), NULL,
				&manage_philos, table) != 0)
			handle_error(THREAD_ERROR, 4, -1);
	}
	pthread_mutex_lock(&table->start_lock);
	table->start_time = get_time_in_ms();
	table->all_created = TRUE;
	pthread_mutex_unlock(&table->start_lock);
	join_threads(table);
}

static void	validate_args(int argc, char **argv)
{
	int		i;
	int		j;
	long	num;

	i = 1;
	num = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				handle_error(INVALID_CHARACTER, -1, -1);
			j++;
		}
		num = ft_atol(argv[i]);
		if (i == 1 && num <= 0)
			handle_error(INVALID_PHILO_NO, -1, -1);
		else if (num <= 0 || num > INT_MAX)
			handle_error(INVALID_CHARACTER, -1, -1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc != 5 && argc != 6)
	{
		printf("%s\n", WRONG_USAGE);
		return (1);
	}
	validate_args(argc, argv);
	table = get_table();
	init_table(argc, argv);
	start_simulation(table);
	destroy_stage_mutexes(-1, 3);
	ft_gc_exit();
	return (0);
}
