/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 20:35:06 by crobot            #+#    #+#             */
/*   Updated: 2022/01/29 20:35:08 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>

# define THINK		41
# define DINNER		42
# define SLEEP		43
# define FORK1		44
# define FORK2		45
# define STARVED	46
# define MAX		47

typedef struct s_philo
{
	int					left;
	int					had;
	int					stop;
	long				last;
	pid_t				pid;
	struct s_data		*data;
	sem_t				*mutex;
	sem_t				*counter;
}	t_philo;

typedef struct s_data
{
	int					n;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_eat;
	int					start;
	t_philo				*philo;
	sem_t				*forks;
	sem_t				*write_m;
	sem_t				*write_dead;
	sem_t				*starved;
	sem_t				*eaten;
}	t_data;

/*		ft_message	*/

int		ft_create_monitor(t_data *data);
void	*monitor_count(void *data_v);
void	*monitor(void *philo_v);
char	*ft_ret_status(int type);
void	ft_term_output(t_philo *philo, int type);

/*		utilz		*/

long	get_time(void);
void	ft_msleep(int msec);
int		ft_isnum(char *str);
long	ft_atoi(const char *str);

/*		ft_forks	*/

void	ft_put_forks(t_philo *philo);
void	ft_take_forks(t_philo *philo);

/*		ft_game		*/

int		ft_create_players(t_data *data);
void	ft_eat(t_philo *philo);
void	ft_think(t_philo *philo);
int		ft_routine(void *arg);
int		ft_start_game(t_data *data);

/*		main		*/

int		ft_clear(t_data *data);
int		ft_init_sem(t_data *data);
int		ft_data_in(t_data *data, int ac, char **av);
int		ft_set_data(t_data *data, int ac, char **av);
int		main(int ac, char **av);

#endif
