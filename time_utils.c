/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:12:07 by licohen           #+#    #+#             */
/*   Updated: 2025/03/03 14:49:20 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_current_time_ms(void)
{
	struct timeval	tv;
	long			current_time_ms;
	long			last_ms;

	if (gettimeofday(&tv, NULL) == 0)
	{
		current_time_ms = tv.tv_sec * 1000;
		last_ms = tv.tv_usec / 1000;
		return (current_time_ms + last_ms);
	}
	else
		return (ERROR);
}

long	get_time_from_start(long start_time)
{
	long	current_time;

	current_time = get_current_time_ms();
	if (current_time == ERROR)
		return (ERROR);
	else
		return (current_time - start_time);
}

long	get_current_time_usec(void)
{
	struct timeval	tv;
	long			current_time_usec;
	long			last_usec;

	if (gettimeofday(&tv, NULL) == 0)
	{
		current_time_usec = tv.tv_sec * 1000000;
		last_usec = tv.tv_usec;
		return (current_time_usec + last_usec);
	}
	else
		return (ERROR);
}

void	safe_usleep(long sleep_time, t_dinner *dinner)
{
	long	current_time;
	long	target_time_usec;
	long	remain_time_usec;

	if (!get_in_progress(dinner) || sleep_time == 0)
		return ;
	if (sleep_time < 1000000)
		return (safe_quick_usleep(sleep_time, dinner));
	current_time = get_current_time_usec();
	if (current_time == ERROR)
		return (set_dinner_end(dinner), print_error("Error: usleep#1\n"));
	target_time_usec = sleep_time + current_time;
	remain_time_usec = target_time_usec - current_time;
	while (remain_time_usec > 1000000 && get_in_progress(dinner))
	{
		if (usleep(500000) != 0)
			return (set_dinner_end(dinner), print_error("Error: usleep#2\n"));
		current_time = get_current_time_usec();
		if (current_time == ERROR)
			return (set_dinner_end(dinner), print_error("Error: usleep#3\n"));
		remain_time_usec = target_time_usec - current_time;
	}
	if (remain_time_usec > 0)
		safe_quick_usleep(remain_time_usec, dinner);
}

void	safe_quick_usleep(long sleep_time, t_dinner *dinner)
{
	long	current_time_usec;
	long	target_time_usec;
	long	rem_time_usec;

	current_time_usec = get_current_time_usec();
	if (current_time_usec == ERROR)
		return (set_dinner_end(dinner), print_error("Error: usleep#1\n"));
	if (sleep_time == 0 || !get_in_progress(dinner))
		return ;
	target_time_usec = sleep_time + current_time_usec;
	rem_time_usec = target_time_usec - current_time_usec;
	while (rem_time_usec > 1000)
	{
		if (usleep(1000) != 0)
			return (set_dinner_end(dinner), print_error("Error: usleep#2\n"));
		current_time_usec = get_current_time_usec();
		if (current_time_usec == ERROR)
			return (set_dinner_end(dinner), print_error("Error: usleep#3\n"));
		rem_time_usec = target_time_usec - current_time_usec;
		if (rem_time_usec <= 0)
			return ;
	}
	if (usleep(rem_time_usec) != 0)
		return (set_dinner_end(dinner), print_error("Error: usleep#4\n"));
}
