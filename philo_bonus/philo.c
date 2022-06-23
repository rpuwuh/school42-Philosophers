/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:09:40 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/23 21:20:22 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_global	*philo_setglb(int argc, char **argv)
{
	t_global	*glb;

	glb = (t_global *) malloc(sizeof(t_global));
	if (!glb)
		exit (0);
	glb->guys = (pid_t *) malloc (sizeof(pid_t) * ft_atoi(argv[1]));
	if (!glb->guys)
		exit (0);
	glb->count = ft_atoi(argv[1]);
	glb->ttd = ft_atoi(argv[2]);
	glb->tte = ft_atoi(argv[3]);
	glb->tts = ft_atoi(argv[4]);
	if (argc == 6)
		glb->numoftimes = ft_atoi(argv[5]);
	else
		glb->numoftimes = 0;
	glb->sem_printf = philo_createsemaphor("/philo_print", 1);
	glb->sem_start = philo_createsemaphor("/philo_start", 1);
	glb->sem_forks_access = philo_createsemaphor("/philo_forks_access", 1);
	glb->sem_forks = philo_createsemaphor("/philo_forks", ft_atoi(argv[1]));
	return (glb);
}

void	philo_end(t_global *glb)
{
	int	i;

	i = 0;
	while (i < glb->count)
		kill (glb->guys[i++], SIGTERM);
	philo_killsemaphor(glb->sem_printf, "/philo_print");
	philo_killsemaphor(glb->sem_start, "/philo_start");
	philo_killsemaphor(glb->sem_forks_access, "/philo_forks_access");
	philo_killsemaphor(glb->sem_forks, "/philo_forks");
	free (glb->guys);
	free(glb);
	exit (0);
}

void	philo_b_process(t_global *glb, pid_t id)
{
	philo_waitstart(&glb->starttime, (1 + glb->count / 100) * 1000);
	while (1)
	{
		sem_wait (glb->sem_forks_access);
		sem_wait (glb->sem_forks);
		philo_print(glb, "has taken a fork\n", id);
		sem_wait (glb->sem_forks);
		philo_print(glb, "has taken a fork\n", id);
		sem_post (glb->sem_forks_access);
		philo_print(glb, "is eating\n", id);
		philo_sleep (glb->tte);
		sem_post(glb->sem_forks);
		sem_post(glb->sem_forks);
		philo_print(glb, "is sleeping\n", id);
		philo_sleep (glb->tts);
		philo_print(glb, "is thinking\n", id);
	}
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
	usleep (100000000);
	philo_end(glb);
}
