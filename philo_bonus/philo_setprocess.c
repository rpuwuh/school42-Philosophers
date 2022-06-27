/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setprocess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 22:41:44 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/27 22:34:35 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_action(t_global *glb, char *s, pid_t id)
{
	sem_wait(glb->death_sem);
	sem_post(glb->death_sem);
	philo_print(glb, s, id);
}

void	philo_actions(t_global *glb, pid_t id)
{
	sem_wait (glb->sem_forks_access);
	sem_wait (glb->sem_forks);
	philo_action(glb, "has taken a fork\n", id);
	sem_wait (glb->sem_forks);
	philo_action(glb, "has taken a fork\n", id);
	sem_post (glb->sem_forks_access);
	philo_action(glb, "is eating\n", id);
	philo_sleep (glb->tte);
	sem_post(glb->sem_forks);
	sem_post(glb->sem_forks);
	sem_wait(glb->philo_sem);
	gettimeofday(&glb->eatentime, 0);
	sem_post(glb->philo_sem);
	glb->eatencount ++;
	if (glb->numoftimes && !glb->eatenstatus
		&& glb->eatencount >= glb->numoftimes)
	{
		sem_wait (glb->sem_eaten);
		glb->eatenstatus ++;
	}
	philo_action(glb, "is sleeping\n", id);
	philo_sleep (glb->tts);
	philo_action(glb, "is thinking\n", id);
}

void	philo_b_process(t_global *glb, pid_t id)
{
	glb->philo_id = id;
	philo_set_process(glb);
	while (1)
		philo_actions(glb, id);
	exit (0);
}

void	philo_set_process(t_global *glb)
{
	glb->eatencount = 0;
	glb->eatenstatus = 0;
	glb->philo_sem = philo_createsemaphor_num(1, glb->philo_id, 0);
	glb->sem_eatentime = philo_createsemaphor_num(1, glb->philo_id, 1);
	glb->eatentime = glb->starttime;
	pthread_create(&(glb->id_eatenchecker), 0, philo_eatenchecksem, glb);
	pthread_detach(glb->id_eatenchecker);
	pthread_create(&(glb->id_hungerchecker), 0, philo_hungerchecker, glb);
	pthread_detach(glb->id_hungerchecker);
	philo_waitstart(glb->starttime, 0);
}
