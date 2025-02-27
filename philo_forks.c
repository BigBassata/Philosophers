/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:03:34 by licohen           #+#    #+#             */
/*   Updated: 2025/02/27 19:15:24 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lock_first_fork(t_dinner *dinner, t_philo *philo)
{
	int	philo_id;

	if (philo->id % 2 == 1)
	{
		philo_id = philo->id % dinner->philo_nb;
		handle_lock_mutex(&dinner->forks[philo_id], dinner);
		dinner->forks_var[philo_id] = 1;
	}
	else
	{
		handle_lock_mutex(&dinner->forks[philo->id - 1], dinner);
		dinner->forks_var[philo->id - 1] = 1;
	}
}

void	lock_second_fork(t_dinner *dinner, t_philo *philo)
{
	int	philo_id;

	if (philo->id % 2 == 1)
	{
		handle_lock_mutex(&dinner->forks[philo->id - 1], dinner);
		dinner->forks_var[philo->id - 1] = 1;
	}
	else
	{
		philo_id = philo->id % dinner->philo_nb;
		handle_lock_mutex(&dinner->forks[philo_id], dinner);
		dinner->forks_var[philo_id] = 1;
	}
}

void	unlock_first_fork(t_dinner *dinner, t_philo *philo)
{
	int	philo_id;

	if (philo->id % 2 == 1)
	{
		philo_id = philo->id % dinner->philo_nb;
		if (dinner->forks_var[philo_id] == 1)
		{
			dinner->forks_var[philo_id] = 0;
			handle_unlock_mutex(&dinner->forks[philo_id], philo->dinner);
		}
	}
	else
	{
		if (dinner->forks_var[philo->id - 1] == 1)
		{
			dinner->forks_var[philo->id - 1] = 0;
			handle_unlock_mutex(&dinner->forks[philo->id - 1], philo->dinner);
		}
	}
}

void	unlock_second_fork(t_dinner *dinner, t_philo *philo)
{
	int	philo_id;

	if (philo->id % 2 == 1)
	{
		if (dinner->forks_var[philo->id - 1] == 1)
		{
			dinner->forks_var[philo->id - 1] = 0;
			handle_unlock_mutex(&dinner->forks[philo->id - 1], dinner);
		}
	}
	else
	{
		philo_id = philo->id % dinner->philo_nb;
		if (dinner->forks_var[philo_id] == 1)
		{
			dinner->forks_var[philo_id] = 0;
			handle_unlock_mutex(&dinner->forks[philo_id], dinner);
		}
	}
}