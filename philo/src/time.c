/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:58:06 by aptive            #+#    #+#             */
/*   Updated: 2022/08/29 15:15:11 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	gettime(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return ((int)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	msg(int time, int philo_nb, char *str)
{
	char	*tmp;
	char	*tmp_2;

	tmp = ft_itoa(time);
	tmp_2 = ft_strjoin_gnl(tmp, " ");
	tmp = ft_itoa(philo_nb);
	tmp_2 = ft_strjoin_gnl(tmp_2, tmp);
	free(tmp);
	tmp_2 = ft_strjoin_gnl(tmp_2, " ");
	tmp_2 = ft_strjoin_gnl(tmp_2, str);
	tmp_2 = ft_strjoin_gnl(tmp_2, "\n");
	ft_putstr_fd(tmp_2, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	ft_exit_free(t_data *(*data))
{
	int	i;

	i = -1;
	while (data && data[++i])
	{
		if (data[i]->mutex_dead)
			free(data[i]->mutex_dead);
		if (data[i]->to_print)
			free(data[i]->to_print);
		if (data[i]->fork_r)
			free(data[i]->fork_r);
		if (data[i]->philo)
			free(data[i]->philo);
		free(data[i]);
	}
	if (data)
		free(data);
}
