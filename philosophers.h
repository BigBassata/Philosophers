/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:11:13 by licohen           #+#    #+#             */
/*   Updated: 2025/02/27 14:36:10 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define DIED "died"
# define EAT "is eating"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define TAKE_FORK "has taken a fork"

enum	e_states
{
	ERROR = -1,
	FALSE,
	TRUE,
};

enum e_error
{
    ERR_ARGS = 1,
    ERR_MALLOC,
    ERR_THREAD,
    ERR_MUTEX_INIT,
    ERR_MUTEX_DESTROY,
    ERR_JOIN_THREAD,
    ERR_INVALID_ARGS,
    ERR_NON_POSITIVE,
    ERR_NON_INTEGER,
    ERR_INT_OVERFLOW,
    ERR_NO_PHILOS,
    ERR_TIME_TO_DIE,
    ERR_MEALS_NB,
    ERR_MUTEX_LOCK,
    ERR_MUTEX_UNLOCK,
    ERR_TIME,
    ERR_USLEEP
};

typedef struct s_philo
{
	int					id;
	int					full;
	int					meals_nb;
	long				last_meal_time;
	pthread_mutex_t		*meals;
	pthread_t			thread;
	struct s_dinner		*dinner;
}	t_philo;

typedef struct s_dinner
{
	long			philo_nb;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_nb;
	int				*forks_var;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*is_full;
	pthread_mutex_t	*set_end;
	pthread_mutex_t	*meal_time;
	int				in_progress;
	long			start_time;
}	t_dinner;

// check_args.c
int		check_args(int argc, char **argv);
int		check_format(char **inputs);
long	positive_atol(char *str);
int		check_space(char c);

// display_errors.c
void	error_exit(char *error);
void	print_error(char *s);
void	print_error_mtx(char *s, t_philo *philo);

// get_time.c
long	get_current_time_ms(void);
long	get_time_from_start(long start_time);
long	get_current_time_usec(void);

// handle_dinner_1.c
int		init_dinner(int argc, char **inputs, t_dinner **dinner);
int		set_dinner(int argc, char **inputs, t_dinner **dinner);
int		init_forks(t_dinner *dinner);
void	delete_dinner(t_dinner *dinner);
void	destroy_forks(t_dinner *dinner);

// handle_dinner_2.c
int		init_set_end(t_dinner *dinner);
int		init_print(t_dinner *dinner);
void	set_dinner_end(t_dinner *dinner);
int		get_in_progress(t_dinner *dinner);
void	*monitor_dinner(t_philo *philos, t_dinner *dinner);

// handle_dinner_3.c
int		init_meal_time(t_dinner *dinner);
void	set_meal_time(t_philo *philo);
long	get_meal_time(t_philo *philo);
int		init_forks_var(t_dinner *dinner);
void	free_forks_var(t_dinner *dinner);

// handle_dinner_4.c
int		init_is_full(t_dinner *dinner);
void	set_is_full(t_philo *philo);
int		get_is_full(t_philo *philo, t_dinner *dinner);
int		init_all_mutex(t_dinner *dinner);
void	free_all_mutex(t_dinner *dinner);

// handle_philo_1.c
int		init_philosophers(t_philo **philos, t_dinner *dinner);
void	*philo_routine(void *arg);
void	one_philo_routine(t_philo *philo, t_dinner *dinner);
int		is_philo_dead(t_philo *philo, t_dinner *dinner);
void	delete_philosophers(t_philo *philos, t_dinner *dinner);

// handle_philo_2.c
void	handle_action(t_philo *philo, char *str);
void	lock_first_fork(t_dinner *dinner, t_philo *philo);
void	lock_second_fork(t_dinner *dinner, t_philo *philo);
void	unlock_first_fork(t_dinner *dinner, t_philo *philo);
void	safe_usleep(long sleep_time, t_dinner *dinner);

// handle_philo_3.c
void	unlock_second_fork(t_dinner *dinner, t_philo *philo);
int		check_str(const char *s1, const char *s2, size_t size);
int		init_meals(t_philo *philo);
void	increase_meals_nb(t_philo *philo);
int		get_meals_nb(t_philo *philo);

// handle_philo_4.c
void	print_died(t_philo *philo, char *str);
void	handle_lock_mutex(pthread_mutex_t *mutex, t_dinner *dinner);
void	handle_unlock_mutex(pthread_mutex_t *mutex, t_dinner *dinner);
void	safe_quick_usleep(long sleep_time, t_dinner *dinner);
int		init_philo_vars(t_philo *philo, t_dinner *dinner, int id);


#endif