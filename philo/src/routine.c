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

static void	philo_sleep(t_philo *philo)
{
	t_table	*table;

	table = get_table();
	if (!stop_simulation(0))
	{
		print_action(philo, SLEEP);
		ft_usleep(table->time_to_sleep);
	}
}

static void	philo_think(t_philo *philo, t_bool silent)
{
	t_table	*table;
	int		time_to_think;

	table = get_table();
	time_to_think = table->time_to_die - table->time_to_eat - table->time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 5)
		time_to_think = 5;
	if (!stop_simulation(0))
	{
		if (!silent)
			print_action(philo, THINK);
		ft_usleep(time_to_think);
	}
	return ;
}

static void	philo_eat(t_philo	*philo)
{
	t_table	*table;

	table = get_table();
	pthread_mutex_lock(&(table->fork_locks[philo->forks[0]]));
	print_action(philo, TAKE_FORK);
	pthread_mutex_lock(&(table->fork_locks[philo->forks[1]]));
	print_action(philo, TAKE_FORK);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time_in_ms();
	philo->times_ate++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_action(philo, EAT);
	ft_usleep(table->time_to_eat);
	pthread_mutex_unlock(&(table->fork_locks[philo->forks[1]]));
	pthread_mutex_unlock(&(table->fork_locks[philo->forks[0]]));
}

static void	*lone_philo(t_philo *philo)
{
	t_table	*table;

	table = get_table();
	print_action(philo, TAKE_FORK);
	ft_usleep(table->time_to_die);
	print_action(philo, DIE);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = get_table();
	wait_for_start(table);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = table->start_time;
	pthread_mutex_unlock(&philo->meal_lock);
	if (table->n_of_philos == 1)
		return (lone_philo(philo));
	if (philo->id % 2)
		philo_think(philo, TRUE);
	while (!stop_simulation(0))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo, FALSE);
	}
	return (NULL);
}
