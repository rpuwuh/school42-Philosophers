/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:09:40 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/23 19:09:18 by bpoetess         ###   ########.fr       */
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
	exit (0);
	printf("hello from the process, pid is %d\t%x\n", id, (unsigned int)glb);
	sem_wait (glb->sem_forks_access);
	sem_wait (glb->sem_forks);
	sem_wait (glb->sem_forks);
	sem_post (glb->sem_forks_access);
	philo_sleep (glb->tte);
	printf("i have eaten\n");
	sem_post(glb->sem_forks);
	sem_post(glb->sem_forks);
	while (1)
		usleep(100);
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
	while (i < ft_atoi(argv[1]))
	{
		glb->guys[i] = fork();
		if (!glb->guys[i])
			exit (0);
		(void) (i);
		sem_wait(glb->sem_printf);
		fflush(0);
		printf("%d\t", i);
		sem_post(glb->sem_printf);
		if (!(i % 3))
		{
			sem_wait(glb->sem_printf);
			printf("\n");
			sem_post(glb->sem_printf);
		}
		i++;
		// printf("this is %d process\n", getpid());
	}
	exit (0);
	// philo_end(glb);
}
