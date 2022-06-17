/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:00:59 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/17 00:01:18 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_global *glb, char *s, int n)
{
	t_time	timenow;

	gettimeofday(&timenow, 0);
	pthread_mutex_lock(&(glb->print_mutex));
	printf("%d %d %s", (int)(philo_gettimeinms(timenow)
			- philo_gettimeinms(glb->starttime)), n + 1, s);
	pthread_mutex_unlock(&(glb->print_mutex));
}
