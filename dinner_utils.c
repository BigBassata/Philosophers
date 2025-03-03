/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:04:30 by licohen           #+#    #+#             */
/*   Updated: 2025/03/03 14:49:04 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_is_full(t_philo *philo, t_dinner *dinner)
{
	int	is_full;

	handle_lock_mutex(dinner->is_full, dinner);
	is_full = philo->full;
	handle_unlock_mutex(dinner->is_full, dinner);
	return (is_full);
}

int	init_all_mutex(t_dinner *dinner)
{
	if (init_forks(dinner) != TRUE)
		return (FALSE);
	if (init_print(dinner) != TRUE)
		return (FALSE);
	if (init_set_end(dinner) != TRUE)
		return (FALSE);
	if (init_meal_time(dinner) != TRUE)
		return (FALSE);
	if (init_is_full(dinner) != TRUE)
		return (FALSE);
	return (TRUE);
}

void	free_all_mutex(t_dinner *dinner)
{
	if (dinner->set_end)
	{
		pthread_mutex_destroy(dinner->set_end);
		free(dinner->set_end);
	}
	if (dinner->print)
	{
		pthread_mutex_destroy(dinner->print);
		free(dinner->print);
	}
	if (dinner->meal_time)
	{
		pthread_mutex_destroy(dinner->meal_time);
		free(dinner->meal_time);
	}
	if (dinner->is_full)
	{
		pthread_mutex_destroy(dinner->is_full);
		free(dinner->is_full);
	}
	if (dinner->forks)
	{
		destroy_forks(dinner);
		free(dinner->forks);
	}
}

int	init_forks_var(t_dinner *dinner)
{
	int	i;

	if (!dinner->philo_nb)
		return (FALSE);
	dinner->forks_var = (int *)malloc(sizeof(int) * dinner->philo_nb);
	if (!dinner->forks_var)
	{
		dinner->forks_var = NULL;
		return (print_error("Error: init forks var\n"), FALSE);
	}
	i = 0;
	while (i < dinner->philo_nb)
	{
		dinner->forks_var[i] = 0;
		i++;
	}
	return (TRUE);
}

void	free_forks_var(t_dinner *dinner)
{
	if (dinner->forks_var)
		free(dinner->forks_var);
}
