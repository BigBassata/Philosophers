/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:04:39 by licohen           #+#    #+#             */
/*   Updated: 2025/03/03 14:49:12 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	handle_lock_mutex(pthread_mutex_t *mutex, t_dinner *dinner)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		print_error("Error: pthread_mutex_lock\n");
		set_dinner_end(dinner);
	}
}

void	handle_unlock_mutex(pthread_mutex_t *mutex, t_dinner *dinner)
{
	if (pthread_mutex_unlock(mutex) != 0)
	{
		print_error("Error: pthread_mutex_unlock\n");
		set_dinner_end(dinner);
	}
}

void	print_died(t_philo *philo, char *str)
{
	long	time;

	time = philo->dinner->start_time;
	handle_lock_mutex(philo->dinner->print, philo->dinner);
	printf("%ld %d %s\n", get_time_from_start(time), philo->id, str);
	handle_unlock_mutex(philo->dinner->print, philo->dinner);
}

int	check_str(const char *s1, const char *s2, size_t size)
{
	size_t			i;
	unsigned char	*s1_temp;
	unsigned char	*s2_temp;

	i = 0;
	s1_temp = (unsigned char *)s1;
	s2_temp = (unsigned char *)s2;
	while (i < size)
	{
		if (s1_temp[i] != s2_temp[i]
			|| s1_temp[i] == '\0' || s2_temp[i] == '\0')
			return ((int)s1_temp[i] - s2_temp[i]);
		i++;
	}
	return (0);
}
