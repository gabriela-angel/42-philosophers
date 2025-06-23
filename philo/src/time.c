/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:47:47 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/22 21:47:47 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_start(t_table *table)
{
	while (TRUE)
	{
		pthread_mutex_lock(&table->start_lock);
		if (table->all_created)
		{
			pthread_mutex_unlock(&table->start_lock);
			break ;
		}
		pthread_mutex_unlock(&table->start_lock);
		usleep(10);
	}
}

long	get_time_in_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long miliseconds)
{
	long	start_time;

	start_time = get_time_in_ms();
	while ((get_time_in_ms() - start_time) < miliseconds)
		usleep(10);
	return ;
}
