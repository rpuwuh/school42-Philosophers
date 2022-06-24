/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 20:40:20 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/24 21:35:12 by bpoetess         ###   ########.fr       */
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
	glb->sem_eaten = philo_createsemaphor("/philo_eaten", ft_atoi(argv[1]));
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
	philo_killsemaphor(glb->sem_eaten, "/philo_eaten");
	philo_killsemaphor(glb->sem_forks_access, "/philo_forks_access");
	philo_killsemaphor(glb->sem_forks, "/philo_forks");
	free (glb->guys);
	free(glb);
	exit (0);
}
