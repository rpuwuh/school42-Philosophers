/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:02:29 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/21 19:04:01 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long int	philo_gettimeinms(t_time time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	philo_sleep(int time)
{
	t_time	start;
	t_time	now;

	gettimeofday(&start, 0);
	gettimeofday(&now, 0);
	while (philo_gettimeinms(now) - philo_gettimeinms(start) < time)
	{
		gettimeofday(&now, 0);
		usleep (127);
	}
}
