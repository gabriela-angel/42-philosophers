/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:14:54 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/19 23:39:59 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define WRONG_USAGE "Error: Wrong format. Try: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]"
# define INVALID_CHARACTER "Error: invalid number or character."
# define INVALID_PHILO_NO "Error: there must be at least 1 philosopher."
# define THREAD_ERROR "Error: could not create thread."
# define MUTEX_ERROR "Error: could not initialize mutex."
# define JOIN_ERROR "Error: could not join thread."
# define MALLOC_ERROR "Error: could not allocate memory."

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				times_ate;
	int				last_meal;
	int				forks[2];
	pthread_mutex_t	meal_lock;
}	t_philo;

typedef struct s_table
{
	t_philo			*threads;
	int				n_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_each_eat;
	int				start_time;
	t_bool			stop_sim;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	*fork_locks;
}	t_table;

typedef enum e_action
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
}	t_action;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

// GARBAGE COLLECTOR -----------------

typedef struct s_malloc
{
	void			*ptr;
	struct s_malloc	*next;
}	t_malloc;

t_malloc	*get_malloc_item(void);
void		*ft_malloc(size_t size);
void		ft_gc_free(void *ptr);
void		ft_gc_exit(void);
t_bool		ft_gc_add(void *ptr);
void		ft_gc_free_matrix(char **matrix);

//UTILS -------------------
t_table		*get_table(void);
long		ft_atol(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_isdigit(int c);

//INIT -------------------
void	init_table(int argc, char **argv);
void	init_threads();

//EXIT -------------------
void	destroy_mutexes(t_philo *threads, int n_of_philos);
void	handle_error(char *error_msg);

#endif