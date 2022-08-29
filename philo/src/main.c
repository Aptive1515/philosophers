/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:11:29 by aptive            #+#    #+#             */
/*   Updated: 2022/08/29 15:18:36 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

int	check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (error_msg("Error : arguments number invalid\n"));
	i = 1;
	while (i <= argc - 1)
	{
		j = 0;
		if (argv[i][j] == '\0')
			return (error_msg("Error : Empty argument\n"));
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (error_msg("Error : Not digit arguments\n"));
			if (ft_atoi(argv[i]) <= 0)
				return (error_msg("Error : argument <= 0\n"));
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*(*data);
	int		i;
	int		time;

	if (check_arg(argc, argv))
		return (1);
	i = 0;
	data = NULL;
	data = philo_init(data, argv);
	init_mutex(data);
	i = -1;
	pthread_mutex_lock(data[0]->to_print);
	while (data[++i])
		pthread_create(&data[i]->philo->thread_philo_nb,
			NULL, routine, data[i]);
	time = gettime();
	i = -1;
	while (data[++i])
	{
		data[i]->philo->time_begin = time;
		data[i]->philo->last_meal = time;
	}
	pthread_mutex_unlock(data[0]->to_print);
	philo_dead(data, ft_atoi(argv[1]), ft_atoi(argv[2]));
	return (0);
}
