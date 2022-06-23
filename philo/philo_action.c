/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:36:03 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/23 20:17:52 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_takefork(t_global *glb, t_guy *guy, t_fork *fork)
{
	if (philo_checkstop(glb))
		return (0);
	pthread_mutex_lock(&(fork->mutex));
	if (philo_checkstop(glb))
		return (0);
	philo_print(glb, "has taken a fork\n", guy->num);
	return (1);
}

static void	philo_updateeattime(t_guy *guy)
{
	pthread_mutex_lock(&(guy->mutexforlasttime));
	gettimeofday(&(guy->lasttimeeat), 0);
	pthread_mutex_unlock(&(guy->mutexforlasttime));
}

static int	philo_takeforks(t_guy *guy)
{
	if (!philo_takefork(guy->glb, guy, guy->l_fork))
		return (0);
	if (!philo_takefork(guy->glb, guy, guy->r_fork))
	{
		pthread_mutex_unlock(&(guy->l_fork->mutex));
		return (0);
	}
	return (1);
}

int	philo_eat(t_guy *guy)
{
	if (!philo_takeforks(guy))
		return (0);
	if (philo_checkstop(guy->glb))
	{
		pthread_mutex_unlock(&(guy->l_fork->mutex));
		pthread_mutex_unlock(&(guy->r_fork->mutex));
		return (0);
	}
	philo_print(guy->glb, "is eating\n", guy->num);
	philo_sleep(guy->glb->tte);
	pthread_mutex_lock(&(guy->mutexforcounteats));
	guy->counteats ++;
	pthread_mutex_unlock(&(guy->mutexforcounteats));
	philo_updateeattime(guy);
	pthread_mutex_unlock(&(guy->r_fork->mutex));
	pthread_mutex_unlock(&(guy->l_fork->mutex));
	return (1);
}

void	*philo_thread(void *data)
{
	t_guy	*guy;

	guy = (t_guy *) data;
	philo_waitstart(guy->glb);
	if (guy->num % 2)
	{
		philo_print(guy->glb, "is sleeping\n", guy->num);
		philo_sleep(guy->glb->tts);
		if (philo_checkstop(guy->glb))
			return (0);
		philo_print(guy->glb, "is thinking\n", guy->num);
	}
	while (!philo_checkstop(guy->glb))
	{
		if (!philo_eat(guy))
			return (0);
		if (philo_checkstop(guy->glb))
			return (0);
		philo_print(guy->glb, "is sleeping\n", guy->num);
		philo_sleep(guy->glb->tts);
		if (philo_checkstop(guy->glb))
			return (0);
		philo_print(guy->glb, "is thinking\n", guy->num);
	}
	return (0);
}
