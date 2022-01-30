/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_message.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 12:58:16 by crobot            #+#    #+#             */
/*   Updated: 2022/01/29 12:58:17 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*monitor_count(void *arg)
{
	t_data	*data;
	int		i;
	int		count;

	data = (t_data *)arg;
	count = 0;
	while (count < data->n)
	{
		count = 0;
		i = 0;
		while (i < data->n)
		{
			pthread_mutex_lock(&data->write_m);
			if (data->philo[i].stop == 0)
				count++;
			pthread_mutex_unlock(&data->write_m);
			i++;
		}
	}
	pthread_mutex_unlock(&data->starved);
	return ((void *)0);
}

void	*monitor(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo *)philo_v;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		pthread_mutex_lock(&philo->data->write_m);
		if (get_time() > philo->last + philo->data->time_to_die)
		{
			if (philo->stop)
			{
				pthread_mutex_unlock(&philo->data->write_m);
				ft_term_output(philo, STARVED);
			}
			pthread_mutex_unlock(&philo->data->write_m);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->data->starved);
			return ((void *)0);
		}
		pthread_mutex_unlock(&philo->data->write_m);
		pthread_mutex_unlock(&philo->mutex);
		ft_msleep(1);
	}
}

char	*ft_ret_status(int type)
{
	if (type == DINNER)
		return ("is eating\n");
	else if (type == SLEEP)
		return ("is sleeping\n");
	else if (type == FORK1 || type == FORK2)
		return ("has taken fork\n");
	else if (type == THINK)
		return ("is thinking\n");
	else if (type == MAX)
		return ("max eats reached\n");
	return ("died\n");
}

void	ft_term_output(t_philo *philo, int msg)
{
	static int	game_over = 0;

	pthread_mutex_lock(&philo->data->write_m);
	if (!game_over)
	{
		printf("%li ", get_time() - philo->data->start);
		if (msg != MAX)
			printf("%d ", philo->left + 1);
		if (msg >= STARVED)
			game_over = 1;
		printf("%s", ft_ret_status(msg));
	}
	pthread_mutex_unlock(&philo->data->write_m);
}
