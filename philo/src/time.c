/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:58:06 by aptive            #+#    #+#             */
/*   Updated: 2022/08/23 18:59:53 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	gettime(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return ((int)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}
