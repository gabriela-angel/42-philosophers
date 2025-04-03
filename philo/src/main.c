/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:14:32 by gangel-a          #+#    #+#             */
/*   Updated: 2025/04/03 20:51:36 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo	*philo)
{
	pthread_mutex_t	fork_1;
	pthread_mutex_t	fork_2;

	fork_1 = philo->fork_lock;
	fork_2 = philo->next->fork_lock;
	if (philo->next->forks[0] == 0)
	{
		pthread_mutex_lock(&fork_1);
		philo->forks[0] = 1;
		pthread_mutex_lock(&fork_2);
		philo->forks[1] = 1;
		printf("timestamp_in_ms %d has taken a fork\n", philo->id);
		philo->times_each_eat--;
		printf("timestamp_in_ms %d is eating\n", philo->id);
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(&fork_1);
		philo->forks[0] = 0;
		pthread_mutex_unlock(&fork_2);
		philo->forks[1] = 0;
	}
}

void	*routine(void *data)
{
	int		i;
	int		loop_times;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)data;
	loop_times = philo->times_each_eat;
	while (loop_times != 0)
	{
		eat(philo);
		printf("Philosopher %d is sleeping\n", philo->id);
		usleep(philo->time_to_sleep * 1000);
		printf("Philosopher %d is thinking\n", philo->id);
		// how to check if the philosopher is dead/can eat?
		usleep(philo->time_to_die * 1000);
		loop_times--;
	}
}

void	start_routine(t_philo *threads, int n_of_philos)
{
	int		i;

	i = 0;
	while (i < n_of_philos)
	{
		if (pthread_create(&threads[i].philo, NULL,
				&routine, &threads[i]) != 0)
			handle_error(THREAD_ERROR);
		i++;
	}
	i = 0;
	while (i < n_of_philos)
	{
		if (pthread_join(&threads[i].philo, NULL) != 0)
			handle_error(JOIN_ERROR);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc != 5 && argc != 6)
	{
		printf("Error: invalid number of arguments\n");
		return (1);
	}
	validate_args(argc, argv);
	//deal with only one pilosopher
	table = get_table();
	init_threads(argc, argv);
	start_routine(table->threads, table->n_of_philos);
	destroy_mutexes(table->threads, table->n_of_philos);
	ft_free_all();
	return (0);
}

void	validate_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!isdigit(argv[i][j]))
				handle_error(INVALID_CHARACTER);
			j++;
		}
		if (i == 1 && ft_atol(argv[1]) <= 0)
			handle_error(INVALID_PHILO_NO);
		else if (ft_atol(argv[i]) <= 0)
			handle_error(INVALID_CHARACTER);
		i++;
	}
}
