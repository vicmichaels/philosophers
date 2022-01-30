/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 12:57:32 by crobot            #+#    #+#             */
/*   Updated: 2022/01/29 12:57:34 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	ft_term_output(philo, FORK1);
	sem_wait(philo->data->forks);
	ft_term_output(philo, FORK2);
}

void	ft_put_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	ft_term_output(philo, SLEEP);
	ft_msleep(philo->data->time_to_sleep);
}
