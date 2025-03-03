/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:12:12 by licohen           #+#    #+#             */
/*   Updated: 2025/03/03 14:49:14 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo_vars(t_philo *philo, t_dinner *dinner, int id)
{
	if (!philo || !dinner)
		return (FALSE);
	philo->id = id;
	philo->meals_nb = 0;
	philo->full = 0;
	philo->last_meal_time = dinner->start_time;
	philo->dinner = dinner;
	return (TRUE);
}

int	init_meals(t_philo *philo)
{
	philo->meals = malloc(sizeof(pthread_mutex_t));
	if (!philo->meals)
		return (FALSE);
	if (pthread_mutex_init(philo->meals, NULL) != 0)
	{
		free(philo->meals);
		philo->meals = NULL;
		return (print_error("Error: init meals\n"), ERROR);
	}
	return (TRUE);
}

void	delete_philosophers(t_philo *philos, t_dinner *dinner)
{
	int	i;

	if (philos)
	{
		i = 0;
		while (i < dinner->philo_nb)
		{
			pthread_join(philos[i].thread, NULL);
			philos[i].dinner = NULL;
			if (philos[i].meals)
			{
				pthread_mutex_destroy(philos[i].meals);
				free(philos[i].meals);
			}
			i++;
		}
		free(philos);
	}
}

int	is_philo_dead(t_philo *philo, t_dinner *dinner)
{
	long	last_meal_time;
	long	current_time;

	last_meal_time = get_meal_time(philo);
	current_time = get_current_time_ms();
	if (current_time == ERROR)
		return (print_error_mtx("Error: time is_philo_dead\n", philo), ERROR);
	else if (current_time - last_meal_time >= dinner->time_to_die)
		return (set_dinner_end(dinner), TRUE);
	else
		return (FALSE);
}

int	init_philosophers(t_philo **philos, t_dinner *dinner)
{
	int	i;

	if (!*philos && dinner->philo_nb)
		*philos = (t_philo *)malloc(sizeof(t_philo) * dinner->philo_nb);
	if (!*philos)
		return (print_error("Error: init philos\n"), FALSE);
	i = 0;
	while (i < dinner->philo_nb)
	{
		if (!init_philo_vars(&(*philos)[i], dinner, i + 1))
			return (FALSE);
		if (!init_meals(&(*philos)[i]))
			return (FALSE);
		if (pthread_create(&(*philos)[i].thread, NULL,
			philo_routine, &(*philos)[i]) != 0)
		{
			while (--i <= 0)
				pthread_join((*philos)[i].thread, NULL);
			free(*philos);
			return (*philos = NULL, print_error("Error: init philo\n"), FALSE);
		}
		i++;
	}
	return (TRUE);
}
