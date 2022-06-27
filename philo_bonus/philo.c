/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:09:40 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/27 22:34:39 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_global	*glb;
	int			i;

	if (philo_usageerror(argc, argv))
		return (22);
	glb = philo_setglb(argc, argv);
	i = 0;
	philo_setstart(&glb->starttime, 1000);
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
