/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:11:56 by licohen           #+#    #+#             */
/*   Updated: 2025/03/03 14:49:06 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_error(char *s)
{
	int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(2, &s[i], sizeof(char));
		i++;
	}
}

void	print_error_mtx(char *s, t_philo *philo)
{
	int	i;

	if (s == NULL)
		return ;
	handle_lock_mutex(philo->dinner->print, philo->dinner);
	i = 0;
	while (s[i] != '\0')
	{
		write(2, &s[i], sizeof(char));
		i++;
	}
	handle_unlock_mutex(philo->dinner->print, philo->dinner);
}

void	error_exit(char *error)
{
	if (!error)
	{
		error = "Error\n";
		print_error(error);
	}
	else
	{
		print_error("Error: ");
		print_error(error);
		print_error("\n");
	}
	exit(1);
}
