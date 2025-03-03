/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:03:57 by licohen           #+#    #+#             */
/*   Updated: 2025/03/03 14:49:01 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_set_end(t_dinner *dinner)
{
	dinner->set_end = malloc(sizeof(pthread_mutex_t));
	if (!dinner->set_end)
		return (FALSE);
	if (pthread_mutex_init(dinner->set_end, NULL) != 0)
	{
		free(dinner->set_end);
		dinner->set_end = NULL;
		return (print_error("Error: init set_end\n"), ERROR);
	}
	return (TRUE);
}

int	init_print(t_dinner *dinner)
{
	dinner->print = malloc(sizeof(pthread_mutex_t));
	if (!dinner->print)
		return (FALSE);
	if (pthread_mutex_init(dinner->print, NULL) != 0)
	{
		free(dinner->print);
		dinner->print = NULL;
		return (print_error("Error: init print\n"), ERROR);
	}
	return (TRUE);
}

void	set_dinner_end(t_dinner *dinner)
{
	handle_lock_mutex(dinner->set_end, dinner);
	dinner->in_progress = 0;
	handle_unlock_mutex(dinner->set_end, dinner);
}

int	get_in_progress(t_dinner *dinner)
{
	int	in_progress;

	handle_lock_mutex(dinner->set_end, dinner);
	in_progress = dinner->in_progress;
	handle_unlock_mutex(dinner->set_end, dinner);
	return (in_progress);
}

void	*monitor_dinner(t_philo *philos, t_dinner *dinner)
{
	int		i;
	int		meals_completed;

	while (get_in_progress(dinner))
	{
		i = 0;
		meals_completed = TRUE;
		while (i < dinner->philo_nb)
		{
			if (is_philo_dead(&philos[i], dinner) != FALSE)
				return (print_died(&philos[i], DIED), NULL);
			if (dinner->meals_nb != -1 && !get_is_full(&philos[i], dinner))
				meals_completed = FALSE;
			i++;
		}
		if (dinner->meals_nb != -1 && meals_completed == TRUE)
			return (set_dinner_end(dinner), NULL);
		if (dinner->philo_nb < 10)
			usleep(1000);
	}
	return (NULL);
}
