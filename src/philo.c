/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:09:32 by aptive            #+#    #+#             */
/*   Updated: 2022/03/13 16:21:04 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_data	**ft_philo_init(t_data *(*data), int nb_philo, pthread_mutex_t *(*fork))
{
	int	i;

	i = 0;
	data = malloc(sizeof(data) * nb_philo);

	while (i < nb_philo)
	{
		data[i] = malloc(sizeof(t_data));
		data[i]->philo = malloc(sizeof(t_philo));
		data[i]->philo->thread_philo_nb = i;
		data[i]->philo->nb = i + 1;
		data[i]->philo->num_fork = 1;
		data[i]->philo->is_eating = 1;
		data[i]->philo->is_thinking = 1;
		data[i]->philo->is_dead = 0;
		gettimeofday(&data[i]->philo->s_time_last, NULL);
		data[i]->fork_r = fork[i];

//		printf("%d\n", i + 1);
		if (i + 1 == nb_philo)
			data[i]->fork_l = fork[0];
		else
			data[i]->fork_l = fork[i + 1];
		i++;
	}
	data[i] = NULL;
	return (data);
}

int ft_philo_dead(t_data *(*data))
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i]->philo->is_dead == 1)
			return (0);
		i++;
	}
	return (1);
}
