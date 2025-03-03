/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:11:13 by licohen           #+#    #+#             */
/*   Updated: 2025/03/03 14:49:18 by licohen          ###   ########.fr       */
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

//agrs_utils
int		check_space(char c);
long	positive_atol(char *str);
int		check_format(char **inputs);
int		check_args(int argc, char **argv);

//dinner_innit
void	destroy_forks(t_dinner *dinner);
void	delete_dinner(t_dinner *dinner);
int		init_forks(t_dinner *dinner);
int		set_dinner(int argc, char **inputs, t_dinner **dinner);
int		init_dinner(int argc, char **inputs, t_dinner **dinner);

//dinner_monitor
int		init_set_end(t_dinner *dinner);
int		init_print(t_dinner *dinner);
void	set_dinner_end(t_dinner *dinner);
int		get_in_progress(t_dinner *dinner);
void	*monitor_dinner(t_philo *philos, t_dinner *dinner);

//dinner_status
int		init_is_full(t_dinner *dinner);
void	set_is_full(t_philo *philo);
int		init_meal_time(t_dinner *dinner);
void	set_meal_time(t_philo *philo);
long	get_meal_time(t_philo *philo);

//dinner_utils
int		get_is_full(t_philo *philo, t_dinner *dinner);
int		init_all_mutex(t_dinner *dinner);
void	free_all_mutex(t_dinner *dinner);
int		init_forks_var(t_dinner *dinner);
void	free_forks_var(t_dinner *dinner);

//error_utils
void	print_error(char *s);
void	print_error_mtx(char *s, t_philo *philo);
void	error_exit(char *error);

//mutex_utils
void	handle_lock_mutex(pthread_mutex_t *mutex, t_dinner *dinner);
void	handle_unlock_mutex(pthread_mutex_t *mutex, t_dinner *dinner);
void	print_died(t_philo *philo, char *str);
int		check_str(const char *s1, const char *s2, size_t size);

//philo_forks
void	lock_first_fork(t_dinner *dinner, t_philo *philo);
void	lock_second_fork(t_dinner *dinner, t_philo *philo);
void	unlock_first_fork(t_dinner *dinner, t_philo *philo);
void	unlock_second_fork(t_dinner *dinner, t_philo *philo);

//philo_init
int		init_philo_vars(t_philo *philo, t_dinner *dinner, int id);
int		init_meals(t_philo *philo);
void	delete_philosophers(t_philo *philos, t_dinner *dinner);
int		is_philo_dead(t_philo *philo, t_dinner *dinner);
int		init_philosophers(t_philo **philos, t_dinner *dinner);

//philo_routine
void	increase_meals_nb(t_philo *philo);
int		get_meals_nb(t_philo *philo);
void	handle_action(t_philo *philo, char *str);
void	one_philo_routine(t_philo *philo, t_dinner *dinner);
void	*philo_routine(void *arg);

//time_utils
long	get_current_time_ms(void);
long	get_time_from_start(long start_time);
long	get_current_time_usec(void);
void	safe_usleep(long sleep_time, t_dinner *dinner);
void	safe_quick_usleep(long sleep_time, t_dinner *dinner);

#endif