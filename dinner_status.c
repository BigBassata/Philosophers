/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:16:30 by licohen           #+#    #+#             */
/*   Updated: 2025/03/03 14:49:03 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_is_full(t_dinner *dinner)
{
	dinner->is_full = malloc(sizeof(pthread_mutex_t));
	if (!dinner->is_full)
		return (FALSE);
	if (pthread_mutex_init(dinner->is_full, NULL) != 0)
	{
		free(dinner->is_full);
		dinner->is_full = NULL;
		return (print_error("Error: init is_full\n"), ERROR);
	}
	return (TRUE);
}

void	set_is_full(t_philo *philo)
{
	handle_lock_mutex(philo->dinner->is_full, philo->dinner);
	philo->full = 1;
	handle_unlock_mutex(philo->dinner->is_full, philo->dinner);
}

int	init_meal_time(t_dinner *dinner)
{
	dinner->meal_time = malloc(sizeof(pthread_mutex_t));
	if (!dinner->meal_time)
		return (FALSE);
	if (pthread_mutex_init(dinner->meal_time, NULL) != 0)
	{
		free(dinner->meal_time);
		dinner->meal_time = NULL;
		return (print_error("Error: init meal_time\n"), ERROR);
	}
	return (TRUE);
}

void	set_meal_time(t_philo *philo)
{
	long	current_time;

	current_time = get_current_time_ms();
	if (current_time == ERROR)
	{
		print_error_mtx("Error: current_time in set_meal_time\n", philo);
		set_dinner_end(philo->dinner);
	}
	handle_lock_mutex(philo->dinner->meal_time, philo->dinner);
	philo->last_meal_time = current_time;
	handle_unlock_mutex(philo->dinner->meal_time, philo->dinner);
}

long	get_meal_time(t_philo *philo)
{
	long	meal_time;

	handle_lock_mutex(philo->dinner->meal_time, philo->dinner);
	meal_time = philo->last_meal_time;
	handle_unlock_mutex(philo->dinner->meal_time, philo->dinner);
	return (meal_time);
}
