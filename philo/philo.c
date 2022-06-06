/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:09:40 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/06 19:36:16 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*philo_createforks(t_global *glb);

t_global	*philo_setglb(int argc, char **argv)
{
	t_global	*glb;

	glb = malloc(sizeof(t_global));
	if (!glb)
		return (0);
	glb->count = ft_atoi(argv[1]);
	glb->ttd = ft_atoi(argv[2]);
	glb->tte = ft_atoi(argv[3]);
	glb->tts = ft_atoi(argv[4]);
	if (argc == 6)
		glb->numoftimes = ft_atoi(argv[5]);
	else
		glb->numoftimes = 0;
	glb->forks = philo_createforks(glb);
	if (!glb->forks)
	{
		free (glb);
		return (0);
	}
	return (glb);
}

t_fork	*philo_createforks(t_global *glb)
{
	t_fork	*forks;
	int		i;

	forks = malloc (glb->count * sizeof(t_fork));
	if (!forks)
		return (0);
	i = 0;
	while (i < glb->count)
	{
		forks[i].num = i;
		forks[i].state = 0;
		pthread_mutex_init(&(forks[i].mutex), 0);
		pthread_mutex_destroy(&(forks[i].mutex));
		printf("loop number = %d\n", i);
		i++;
	}
	return (forks);
}

int	main(int argc, char **argv)
{
	t_global	*glb;

	if (philo_usageerror(argc, argv))
		return (22);
	printf("%d\n", argc);
	glb = philo_setglb(argc, argv);
	if (!glb)
		return (22);
	free(glb->forks);
	free(glb);
	return (0);
}
