/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:03:03 by licohen           #+#    #+#             */
/*   Updated: 2025/03/03 14:49:16 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	increase_meals_nb(t_philo *philo)
{
	int		meals_nb;

	handle_lock_mutex(philo->meals, philo->dinner);
	philo->meals_nb += 1;
	meals_nb = philo->meals_nb;
	handle_unlock_mutex(philo->meals, philo->dinner);
	if (philo->dinner->meals_nb != -1 && meals_nb >= philo->dinner->meals_nb)
		set_is_full(philo);
}

int	get_meals_nb(t_philo *philo)
{
	int	meals_nb;

	handle_lock_mutex(philo->meals, philo->dinner);
	meals_nb = philo->meals_nb;
	handle_unlock_mutex(philo->meals, philo->dinner);
	return (meals_nb);
}

void	handle_action(t_philo *philo, char *str)
{
	long	time;
	int		time_to_think;

	time = philo->dinner->start_time;
	handle_lock_mutex(philo->dinner->print, philo->dinner);
	if (get_in_progress(philo->dinner))
	{
		if (check_str(str, EAT, 9) == 0)
			set_meal_time(philo);
		printf("%ld %d %s\n", get_time_from_start(time),
			philo->id, str);
	}
	handle_unlock_mutex(philo->dinner->print, philo->dinner);
	if (check_str(str, EAT, 9) == 0)
		safe_usleep(philo->dinner->time_to_eat * 1000, philo->dinner);
	else if (check_str(str, SLEEP, 11) == 0)
		safe_usleep(philo->dinner->time_to_sleep * 1000, philo->dinner);
	if (philo->dinner->philo_nb % 2 == 1 && check_str(str, THINK, 11) == 0)
	{
		time = philo->dinner->time_to_sleep;
		time_to_think = philo->dinner->time_to_eat * 2 - time;
		if (time_to_think < 0)
			time_to_think = 3;
		safe_usleep(time_to_think * 1000, philo->dinner);
	}
}

void	one_philo_routine(t_philo *philo, t_dinner *dinner)
{
	long	time_to_sleep;

	lock_first_fork(dinner, philo);
	handle_action(philo, TAKE_FORK);
	unlock_first_fork(dinner, philo);
	time_to_sleep = philo->dinner->time_to_die;
	safe_usleep(time_to_sleep * 1000, dinner);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	t_dinner	*dinner;

	philo = (t_philo *)arg;
	dinner = philo->dinner;
	if (dinner->philo_nb < 2)
		one_philo_routine(philo, dinner);
	while (dinner->philo_nb > 1 && get_in_progress(dinner))
	{
		lock_first_fork(dinner, philo);
		handle_action(philo, TAKE_FORK);
		if (!get_in_progress(dinner))
			return (unlock_first_fork(dinner, philo), NULL);
		lock_second_fork(dinner, philo);
		handle_action(philo, TAKE_FORK);
		handle_action(philo, EAT);
		increase_meals_nb(philo);
		unlock_first_fork(dinner, philo);
		unlock_second_fork(dinner, philo);
		handle_action(philo, SLEEP);
		handle_action(philo, THINK);
	}
	return (NULL);
}
