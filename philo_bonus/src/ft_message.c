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

int	ft_create_monitor(t_data *data)
{
	pthread_t	t;

	if (data->max_eat > 0)
	{
		if (pthread_create(&t, NULL, &monitor_count, (void *)data))
			return (1);
		pthread_detach(t);
	}
	return (0);
}

void	*monitor_count(void *arg)
{
	t_data	*data;
	int		had;

	data = (t_data *)arg;
	had = 0;
	while (had < data->n)
	{
		sem_wait(data->eaten);
		had++;
	}
	sem_post(data->starved);
	return ((void *)0);
}

void	*monitor(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo *)philo_v;
	while (1)
	{
		sem_wait(philo->mutex);
		sem_wait(philo->data->write_m);
		if (get_time() > philo->last + philo->data->time_to_die)
		{
			if (philo->stop)
			{
				sem_post(philo->data->write_m);
				ft_term_output(philo, STARVED);
			}
			sem_post(philo->data->write_m);
			sem_post(philo->mutex);
			sem_post(philo->data->starved);
			return ((void *)0);
		}
		sem_post(philo->data->write_m);
		sem_post(philo->mutex);
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
	sem_wait(philo->data->write_m);
	sem_wait(philo->data->write_dead);
	printf("%li ", get_time() - philo->data->start);
	if (msg != MAX)
		printf("%d ", philo->left + 1);
	printf("%s", ft_ret_status(msg));
	if (msg < STARVED)
		sem_post(philo->data->write_dead);
	sem_post(philo->data->write_m);
}
