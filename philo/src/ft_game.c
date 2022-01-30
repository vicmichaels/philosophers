/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 12:58:05 by crobot            #+#    #+#             */
/*   Updated: 2022/01/29 12:58:07 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_create_players(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n)
	{
		data->philo[i].left = i;
		data->philo[i].right = (i + 1) % data->n;
		data->philo[i].had = 0;
		data->philo[i].data = data;
		data->philo[i].stop = 1;
		pthread_mutex_init(&data->philo[i].mutex, NULL);
	}
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->last = get_time();
	ft_term_output(philo, DINNER);
	ft_msleep(philo->data->time_to_eat);
	philo->had++;
	pthread_mutex_unlock(&philo->mutex);
}

void	*ft_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	t;

	philo = (t_philo *)(arg);
	philo->last = get_time();
	if (pthread_create(&t, NULL, &monitor, arg))
		return ((void *)1);
	pthread_detach(t);
	while (philo->had < philo->data->max_eat)
	{
		ft_take_forks(philo);
		ft_eat(philo);
		ft_put_forks(philo);
		ft_term_output(philo, THINK);
	}
	pthread_mutex_lock(&philo->data->write_m);
	philo->stop = 0;
	pthread_mutex_unlock(&philo->data->write_m);
	return ((void *)0);
}

int	ft_start_game(t_data *data)
{
	int			i;
	pthread_t	t;
	void		*philo;

	data->start = get_time();
	if (data->max_eat > -1)
	{
		if (pthread_create(&t, NULL, &monitor_count, (void *)data))
			return (1);
		pthread_detach(t);
	}
	i = 0;
	while (i < data->n)
	{
		philo = (void *)(&data->philo[i]);
		if (pthread_create(&t, NULL, &ft_routine, (void *)philo))
			return (1);
		pthread_detach(t);
		usleep(100);
		i++;
	}
	return (0);
}
