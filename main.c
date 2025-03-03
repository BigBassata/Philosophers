/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:10:37 by licohen           #+#    #+#             */
/*   Updated: 2025/03/03 14:49:08 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_all(t_philo *philos, t_dinner *dinner)
{
	if (philos)
		delete_philosophers(philos, dinner);
	if (dinner)
		delete_dinner(dinner);
}

int	main(int argc, char **argv)
{
	t_dinner	*dinner;
	t_philo		*philos;
	int			check_step;

	dinner = NULL;
	philos = NULL;
	check_step = check_args(argc, argv);
	if (!check_step)
		return (1);
	check_step = init_dinner(argc, argv, &dinner);
	if (!check_step)
		return (1);
	check_step = init_philosophers(&philos, dinner);
	if (!check_step)
		return (delete_dinner(dinner), 1);
	monitor_dinner(philos, dinner);
	clean_all(philos, dinner);
	return (0);
}
