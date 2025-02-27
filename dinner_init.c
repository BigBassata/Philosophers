/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:03:12 by licohen           #+#    #+#             */
/*   Updated: 2025/02/27 19:27:43 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_forks(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->philo_nb)
	{
		pthread_mutex_destroy(&dinner->forks[i]);
		i++;
	}
}

void	delete_dinner(t_dinner *dinner)
{
	if (dinner)
	{
		free_all_mutex(dinner);
		free_forks_var(dinner);
		free(dinner);
	}
}

int	init_forks(t_dinner *dinner)
{
	int	i;
	int	j;

	if (!dinner->philo_nb)
		return (FALSE);
	if (init_forks_var(dinner) == FALSE)
		return (FALSE);
	dinner->forks = malloc((dinner->philo_nb) * sizeof(pthread_mutex_t));
	if (!dinner->forks)
		return (FALSE);
	i = 0;
	while (i < dinner->philo_nb)
	{
		if (pthread_mutex_init(&dinner->forks[i], NULL) != 0)
		{
			j = 0;
			while (j < i)
				pthread_mutex_destroy(&dinner->forks[j++]);
			free(dinner->forks);
			dinner->forks = NULL;
			return (print_error("Error: init mutex fork\n"), ERROR);
		}
		i++;
	}
	return (TRUE);
}

int	set_dinner(int argc, char **inputs, t_dinner **dinner)
{
	if (!*dinner)
		*dinner = (t_dinner *)malloc(sizeof(t_dinner));
	if (!*dinner)
		return (FALSE);
	(*dinner)->philo_nb = positive_atol(inputs[1]);
	(*dinner)->time_to_die = positive_atol(inputs[2]);
	(*dinner)->time_to_eat = positive_atol(inputs[3]);
	(*dinner)->time_to_sleep = positive_atol(inputs[4]);
	if (argc == 6)
		(*dinner)->meals_nb = positive_atol(inputs[5]);
	else
		(*dinner)->meals_nb = -1;
	if (init_all_mutex(*dinner) != TRUE)
		return (delete_dinner(*dinner), FALSE);
	(*dinner)->in_progress = 1;
	(*dinner)->start_time = get_current_time_ms();
	if ((*dinner)->start_time == ERROR)
		return (delete_dinner(*dinner), FALSE);
	return (TRUE);
}

int	init_dinner(int argc, char **inputs, t_dinner **dinner)
{
	if (argc == 6)
	{
		if (positive_atol(inputs[5]) < 1)
		{
			print_error("Error: if meals_nb < 1, no dinner\n");
			return (FALSE);
		}
	}
	if (positive_atol(inputs[1]) < 1)
		return (print_error("Error: no philosophers, no dinner\n"), FALSE);
	else if (positive_atol(inputs[2]) < 1)
		return (print_error("Error: time_to_death < 1\n"), FALSE);
	else if (positive_atol(inputs[1]) > 0)
		return (set_dinner(argc, inputs, dinner));
	return (FALSE);
}
