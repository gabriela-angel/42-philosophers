/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:44:59 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/21 15:44:59 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sleep(t_philo *philo)
{
	t_table	*table;

	table = get_table();
	if (!stop_simulation())
	{
		print_action(philo, SLEEP);
		ft_usleep(table->time_to_sleep);
	}
}

static void	think(t_philo *philo, t_bool silent)
{
	t_table	*table;
	int		time_to_think;

	table = get_table();
	time_to_think = (table->time_to_die - (get_time_in_ms() - philo->last_meal)\
			- table->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent)
		time_to_think = 1;
	if (time_to_think > 500)
		time_to_think = 200;
	if (!stop_simulation())
	{
		if (!silent)
			print_action(philo, THINK);
		ft_usleep(time_to_think);
	}
}

static void	eat(t_philo	*philo)
{
	t_table	*table;

	table = get_table();
	pthread_mutex_lock(&(table->fork_locks[philo->forks[0]]));
	print_action(philo, TAKE_FORK);
	pthread_mutex_lock(&(table->fork_locks[philo->forks[1]]));
	print_action(philo, TAKE_FORK);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time_in_ms();
	print_action(philo, EAT);
	philo->times_ate++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(table->time_to_eat);
	pthread_mutex_unlock(&(table->fork_locks[philo->forks[1]]));
	pthread_mutex_unlock(&(table->fork_locks[philo->forks[0]]));
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = get_table();
	philo->last_meal = table->start_time;
	while (get_time_in_ms() < table->start_time)
		continue;
	if (table->n_of_philos == 1)
	{
		print_action(philo, TAKE_FORK);
		ft_usleep(table->time_to_die);
		return (NULL);
	}
	if (philo->id % 2)
		think(philo, true);
	while (!stop_simulation())
	{
		eat(philo);
		sleep(philo);
		think(philo, false);
	}
	return (NULL);
}
