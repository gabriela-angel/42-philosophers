/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:14:54 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/22 21:49:29 by gangel-a         ###   ########.fr       */
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
	pthread_t		manager;
	int				n_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_each_eat;
	int				start_time;
	t_bool			stop_sim;
	t_bool			all_created;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	*fork_locks;
}	t_table;

// GARBAGE COLLECTOR -----------------
typedef struct s_malloc
{
	void			*ptr;
	struct s_malloc	*next;
}	t_malloc;

void		*ft_calloc(size_t nmemb, size_t size);
t_bool		ft_gc_add(void *ptr);
void		ft_gc_exit(void);
void		ft_gc_free(void *ptr);
void		ft_gc_free_matrix(char **matrix);
void		*ft_malloc(size_t size);
t_malloc	*get_malloc_item(void);

// INIT -------------------
void		init_table(int argc, char **argv);

// ROUTINE -------------------
void		*routine(void *arg);

// MANAGER -------------------
t_bool		stop_simulation(int stop_flag);
void		*manage_philos(void *arg);

// TIME -------------------
void		wait_for_start(t_table *table);
int			get_time_in_ms(void);
void		ft_usleep(int miliseconds);

// UTILS -------------------
void		print_action(t_philo *philo, t_action action);
long		ft_atol(const char *nptr);
int			ft_isdigit(int c);
t_table		*get_table(void);

// EXIT -------------------
void		destroy_stage_mutexes(int stop_index, int stage);
void		handle_error(char *error_msg, int stage, int stop_index);

#endif