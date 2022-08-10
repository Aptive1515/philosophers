/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:10:26 by tdelauna          #+#    #+#             */
/*   Updated: 2022/08/10 20:07:02 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_all(t_data *(*data))
{
	int	i;

	i = 0;
	pthread_mutex_destroy(data[i]->to_print);
	pthread_mutex_destroy(data[i]->mutex_dead);
	free(data[i]->to_print);
	free(data[i]->mutex_dead);
	while (data[i])
	{
		free(data[i]->fork_l);
		free(data[i]->philo);
		free(data[i]);
		i++;
	}
	free(data);
}

void	ft_exit(t_data *(*data), int j)
{
	int	i;

	i = -1;
	pthread_mutex_unlock(data[j]->mutex_dead);
	while (data[++i])
		pthread_join (data[i]->philo->thread_philo_nb, NULL);
	free_all(data);
	exit(1);
}

void	philo_dead(t_data *(*dt), int nb_philo, int time_to_dead)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	usleep((time_to_dead) * 1000);
	while (dt[i])
	{
		pthread_mutex_lock(dt[i]->mutex_dead);
		if ((gettime() - dt[i]->philo->last_meal) >= dt[i]->philo->time_to_die)
		{
			if (dt[i]->philo->have_meal == dt[i]->philo->nb_philo_must_eat)
				ft_exit(dt, i);
			msg(gettime() - dt[i]->philo->time_begin, dt[i]->philo->nb, "died");
			while (dt[++j])
				dt[j]->dead_philo = 1;
			ft_exit(dt, i);
		}
		i++;
		if (nb_philo == i)
			i = 0;
		pthread_mutex_unlock(dt[i]->mutex_dead);
	}
}

void	ft_died(t_philo *philo, t_data *data)
{
	msg(gettime() - philo->time_begin, philo->nb, "died");
	data->dead_philo = 1;
}

void	msg(int time, int philo_nb, char *str)
{
	ft_putnbr_fd((int)time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo_nb, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
}
