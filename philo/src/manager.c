/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:56:07 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/21 15:56:07 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	stop_simulation(int stop_flag)
{
	t_table	*table;
	t_bool	flag;

	table = get_table();
	pthread_mutex_lock(&table->stop_lock);
	if (stop_flag)
		table->stop_sim = TRUE;
	flag = table->stop_sim;
	pthread_mutex_unlock(&table->stop_lock);
	return (flag);
}

static t_bool	starvation(void)
{
	t_table	*table;
	int		i;

	table = get_table();
	i = 0;
	while (i < table->n_of_philos && !stop_simulation(0))
	{
		pthread_mutex_lock(&(table->threads[i]).meal_lock);
		if ((get_time_in_ms() - table->threads[i].last_meal) \
			> table->time_to_die + 1)
		{
			print_action(&(table->threads[i]), DIE);
			stop_simulation(1);
			pthread_mutex_unlock(&(table->threads[i]).meal_lock);
			return (TRUE);
		}
		pthread_mutex_unlock(&(table->threads[i]).meal_lock);
		i++;
	}
	return (FALSE);
}

static t_bool	all_full(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->n_of_philos && !stop_simulation(0))
	{
		pthread_mutex_lock(&(table->threads[i]).meal_lock);
		if (table->threads[i].times_ate < table->times_each_eat)
		{
			pthread_mutex_unlock(&(table->threads[i]).meal_lock);
			return (FALSE);
		}
		pthread_mutex_unlock(&(table->threads[i]).meal_lock);
		i++;
	}
	return (TRUE);
}

void	*manage_philos(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	wait_for_start(table);
	while (!stop_simulation(0))
	{
		if (starvation())
			stop_simulation(1);
		if (table->times_each_eat > 0 && all_full(table))
			stop_simulation(1);
		usleep(100);
	}
	return (NULL);
}
