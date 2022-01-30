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

int	ft_create_players(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n)
	{
		data->philo[i].left = i;
		data->philo[i].had = 0;
		data->philo[i].stop = 1;
		data->philo[i].data = data;
		sem_unlink("/philo");
		data->philo[i].mutex = sem_open("/philo", O_CREAT, S_IRWXU, 1);
		if (!data->philo[i].mutex)
			return (1);
		sem_unlink("/counter");
		data->philo[i].counter = sem_open("/counter", O_CREAT,
				S_IRWXU, 1);
		if ((data->philo[i].counter) < 0)
			return (1);
	}
	return (0);
}

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->mutex);
	philo->last = get_time();
	ft_term_output(philo, DINNER);
	ft_msleep(philo->data->time_to_eat);
	philo->had++;
	sem_post(philo->mutex);
}

int	ft_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	t;
	int			i;

	philo = (t_philo *)(arg);
	philo->last = get_time();
	if (pthread_create(&t, NULL, &monitor, arg))
		return (1);
	pthread_detach(t);
	i = -1;
	while (++i < philo->data->max_eat)
	{
		ft_take_forks(philo);
		ft_eat(philo);
		ft_put_forks(philo);
		ft_term_output(philo, THINK);
	}
	sem_post(philo->data->eaten);
	return (0);
}

int	ft_start_game(t_data *data)
{
	int			i;
	void		*philo;

	data->start = get_time();
	i = -1;
	while (++i < data->n)
	{
		philo = (void *)(&data->philo[i]);
		data->philo[i].pid = fork();
		if (data->philo[i].pid < 0)
			return (1);
		else if ((data->philo[i].pid) == 0)
		{
			ft_routine(&data->philo[i]);
			exit (0);
		}
		usleep(100);
	}
	return (0);
}
