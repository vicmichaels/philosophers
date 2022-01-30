/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 11:49:05 by crobot            #+#    #+#             */
/*   Updated: 2022/01/29 11:49:08 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_clear(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->n)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	if (data->philo)
	{
		i = 0;
		while (i < data->n)
		{
			pthread_mutex_destroy(&data->philo[i].mutex);
			i++;
		}
		free(data->philo);
	}
	pthread_mutex_destroy(&data->write_m);
	pthread_mutex_destroy(&data->starved);
	return (1);
}

int	ft_init_mutex(t_data *data)
{
	int	i;

	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->n);
	if (!(data->forks))
		return (1);
	pthread_mutex_init(&data->write_m, NULL);
	pthread_mutex_init(&data->starved, NULL);
	pthread_mutex_lock(&data->starved);
	i = 0;
	while (i < data->n)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL))
			return (1);
	}
	return (0);
}

int	ft_data_in(t_data *data, int ac, char **av)
{
	data->n = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->max_eat = INT_MAX;
	if (ac == 6)
		data->max_eat = ft_atoi(av[5]);
	if (data->n < 1 || data->max_eat < 0)
		return (1);
	data->forks = NULL;
	data->philo = (t_philo *)malloc(sizeof(*(data->philo)) * data->n);
	if (!data->philo)
		return (1);
	ft_init_mutex(data);
	return (0);
}

int	ft_set_data(t_data *data, int ac, char **av)
{
	int			i;
	long int	value;

	if (!(ac == 5 || ac == 6))
		return (1);
	i = 0;
	while (++i < ac)
	{
		if (!ft_isnum(av[i]))
			return (1);
		value = ft_atoi(av[i]);
		if (value > INT_MAX || value < INT_MIN)
			return (1);
	}
	if (ft_data_in(data, ac, av))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ft_set_data(&data, ac, av))
	{
		printf("watch your args\n");
		return (1);
	}
	ft_create_players(&data);
	if (ft_start_game(&data))
		return (1);
	pthread_mutex_lock(&data.starved);
	pthread_mutex_unlock(&data.starved);
	ft_clear(&data);
	return (0);
}
