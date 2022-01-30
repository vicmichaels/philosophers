/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 12:58:27 by crobot            #+#    #+#             */
/*   Updated: 2022/01/29 12:58:28 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long	get_time(void)
{
	struct timeval	tp;
	long			ms;
	static long		start_time;

	gettimeofday(&tp, NULL);
	ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	if (!start_time)
		start_time = ms;
	return (ms - start_time);
}

void	ft_msleep(int msec)
{
	long	start;

	if (msec <= 0)
		return ;
	start = get_time();
	if (msec > 5)
		usleep(msec * 1000 - 5000);
	while (get_time() - start < msec)
		;
}

int	ft_isnum(char *str)
{
	while (str && *str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

long	ft_atoi(const char *str)
{
	long			res;
	long			sign;
	unsigned int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}
