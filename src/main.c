/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:11:29 by aptive            #+#    #+#             */
/*   Updated: 2022/08/10 14:24:17 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*(*data);
	int		i;

	if (argc < 5 || argc > 6)
		return (1);
	i = 0;
	data = NULL;
	data = ft_philo_init(data, argv);
	ft_init_mutex(data);
	i = -1;
	pthread_mutex_lock(data[0]->to_print);
	while (data && data[++i])
		pthread_create(&data[i]->philo->thread_philo_nb,
			NULL, ft_test, data[i]);
	pthread_mutex_unlock(data[0]->to_print);
	while (data && ft_philo_dead(data))
		i = -1;
	i = -1;
	while (data && data[++i])
		pthread_join (data[i]->philo->thread_philo_nb, NULL);
	ft_free_all(data);
	return (1);
}
