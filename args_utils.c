/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:10:53 by licohen           #+#    #+#             */
/*   Updated: 2025/03/03 14:48:58 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_space(char c)
{
	if (!c)
		return (FALSE);
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (TRUE);
	else
		return (FALSE);
}

long	positive_atol(char *str)
{
	long	n;
	int		len;

	n = 0;
	len = 0;
	while (check_space(*str))
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (len > 10)
			return (n);
		if (*str < '0' || *str > '9')
			return (-2);
		n = n * 10 + (*str - '0');
		str++;
		len++;
	}
	return (n);
}

int	check_format(char **inputs)
{
	long	check_n;
	int		i;

	i = 1;
	while (inputs[i])
	{
		check_n = positive_atol(inputs[i]);
		if (check_n == -1)
			return (print_error("Error: non-positive args\n"), FALSE);
		else if (check_n == -2)
			return (print_error("Error: non-integer args\n"), FALSE);
		else if (check_n > 2147483647)
			return (print_error("Error: INT_MAX overflow\n"), FALSE);
		i++;
	}
	return (TRUE);
}

int	check_args(int argc, char **argv)
{
	int	check;

	if (argc == 1)
		return (FALSE);
	if (argc != 5 && argc != 6)
	{
		print_error("bad args, use: <philos_n> <time_to_die>");
		print_error(" <time_to_eat> <time_to_sleep> optional<meals_n>\n");
		return (FALSE);
	}
	check = check_format(argv);
	return (check);
}
