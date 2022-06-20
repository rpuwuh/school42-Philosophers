/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:09:40 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/20 18:31:16 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_b_process(sem_t *sem, pid_t id)
{
	printf("hello from the process, pid is %d\n", id);
	sem_wait (sem);
	sem_wait (sem);
	usleep (1000000);
	printf("i have eaten\n");
	sem_post(sem);
	sem_post(sem);
	exit (0);
}

int	main(int argc, char **argv)
{
	pid_t	*x;
	sem_t	*sem;
	int		i;

	if (philo_usageerror(argc, argv))
		return (22);
	sem_unlink("/philosophers");
	sem = sem_open("/philosophers", O_CREAT, 0666, ft_atoi(argv[1]));
	x = (pid_t *) malloc (sizeof(pid_t) * ft_atoi(argv[1]));
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		x[i] = fork();
		if (x[i])
			philo_b_process(sem, x[i]);
		usleep (1000);
		i++;
	}
	sem_close(sem);
	free (x);
	sem_unlink("/philosophers");
	return (0);
}
