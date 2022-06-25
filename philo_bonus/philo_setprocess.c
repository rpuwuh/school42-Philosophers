/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setprocess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 22:41:44 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/25 20:37:11 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_set_process(t_global *glb)
{
	glb->eatencount = 0;
	glb->philo_sem = philo_createsemaphor("/philo_sem", 1);
	glb->sem_eatentime = philo_createsemaphor("/philo_eatentime", 1);
	glb->death_sem = philo_createsemaphor("/philo_death_sem", 1);
	sem_wait(glb->philo_sem);
	pthread_create(&(glb->id_eatenchecker), 0, philo_eatenchecksem, glb);
	pthread_detach(glb->id_eatenchecker);
	pthread_create(&(glb->id_hungerchecker), 0, philo_hungerchecker, glb);
	pthread_detach(glb->id_hungerchecker);
	sem_post(glb->philo_sem);
}
