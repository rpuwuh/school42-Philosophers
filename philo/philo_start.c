/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:33:16 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/19 13:11:10 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_checkstart(t_global *glb)
{
	int	res;

	pthread_mutex_lock(&glb->start_mutex);
	res = glb->start;
	pthread_mutex_unlock(&glb->start_mutex);
	return (res);
}

void	philo_waitstart(t_global *glb)
{
	while (!philo_checkstart(glb))
		usleep (10);
}

void	philo_start(t_global *glb)
{
	pthread_mutex_lock(&glb->start_mutex);
	glb->start = 1;
	pthread_mutex_unlock(&glb->start_mutex);
}
