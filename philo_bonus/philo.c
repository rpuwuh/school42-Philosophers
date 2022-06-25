/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:09:40 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/25 20:13:20 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_action(t_global *glb, char *s, pid_t id)
{
	sem_wait(glb->death_sem);
	philo_print(glb, s, id);
	sem_post(glb->death_sem);
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
	glb->eatencount ++;
	sem_post(glb->philo_sem);
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

int	main(int argc, char **argv)
{
	t_global	*glb;
	int			i;

	if (philo_usageerror(argc, argv))
		return (22);
	glb = philo_setglb(argc, argv);
	i = 0;
	gettimeofday(&glb->starttime, 0);
	while (i < ft_atoi(argv[1]))
	{
		glb->guys[i] = fork();
		if (!glb->guys[i])
			philo_b_process(glb, i);
		i++;
	}
	waitpid(0, &i, WUNTRACED);
	philo_end(glb);
}
