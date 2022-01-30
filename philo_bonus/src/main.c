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

	sem_unlink("/fork_sem");
	sem_unlink("/write_sem");
	sem_unlink("/starved_sem");
	sem_unlink("/write_dead_sem");
	sem_unlink("/eaten");
	if (data->philo)
	{
		i = -1;
		while (++i < data->n)
		{
			sem_unlink("/philo");
			sem_unlink("/counter");
		}
		free(data->philo);
	}
	return (1);
}

int	ft_init_sem(t_data *data)
{
	sem_unlink("/forks_sem");
	sem_unlink("/write_sem");
	sem_unlink("/starved_sem");
	sem_unlink("/write_dead_sem");
	sem_unlink("/eaten");
	data->forks = sem_open("/forks_sem", O_CREAT, S_IRWXU, data->n);
	data->write_m = sem_open("/write_sem", O_CREAT, S_IRWXU, 1);
	data->starved = sem_open("/starved_sem", O_CREAT, S_IRWXU, 0);
	data->write_dead = sem_open("/write_dead_sem", O_CREAT, S_IRWXU, 1);
	data->eaten = sem_open("/eaten", O_CREAT, S_IRWXU, 0);
	if ((data->forks < 0) || (data->write_m < 0) || (data->starved < 0)
		|| (data->write_dead < 0))
		return (1);
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
	ft_init_sem(data);
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
	int		i;

	if (ft_set_data(&data, ac, av))
	{
		printf("watch your args\n");
		return (1);
	}
	if (ft_create_players(&data) || ft_create_monitor(&data)
		|| ft_start_game(&data))
	{
		ft_clear(&data);
		return (1);
	}
	sem_wait(data.starved);
	i = -1;
	while (++i < data.n)
		kill(data.philo[i].pid, SIGKILL);
	ft_clear(&data);
	return (0);
}
