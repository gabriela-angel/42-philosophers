/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:14:54 by gangel-a          #+#    #+#             */
/*   Updated: 2025/04/03 20:30:12 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define WRONG_USAGE "Error: Wrong format. Try: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]"
# define INVALID_CHARACTER "Error: invalid number or character."
# define INVALID_PHILO_NO "Error: there must be at least 1 philosopher."
# define THREAD_ERROR "Error: could not create thread."
# define JOIN_ERROR "Error: could not join thread."
# define MALLOC_ERROR "Error: could not allocate memory."


typedef struct s_table
{
	t_philo			*threads;
	int				n_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_each_eat;
}	t_table;

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_each_eat;
	int				*forks;
	pthread_mutex_t	fork_lock;
	t_philo			*previous;
	t_philo			*next;
}	t_philo;

typedef struct s_malloc
{
	void	*list[1000];
	size_t	i;
}	t_malloc;

//FT_MALLOC -----------------
void	*ft_malloc(size_t size);
void	ft_free_all(void);

//UTILS -------------------
int		ft_atol(const char *nptr);

//INIT -------------------
t_philo	*init_threads(int argc, char **argv);
void	init_philos(int argc, char **argv, t_philo *threads, int pos);

//EXIT -------------------
void	destroy_mutexes(t_philo *threads, int n_of_philos);

#endif