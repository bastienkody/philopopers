/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:58:53 by bguillau          #+#    #+#             */
/*   Updated: 2023/05/08 19:58:56 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* default fct to threads */
void	*do_smthg(void *t)
{
	printf("salut from philo %i\n", *(int *)t);
	return (NULL);
}

/*	create a thread per philo + assigns th_id	*/
void	launcher(t_philo **philo)
{
	pthread_t	thread;
	int			i;

	i = -1;
	while (philo[++i])
	{
		thread = 0;
		if (pthread_create(&thread, NULL, &do_smthg, &philo[i]->nb))
			printf("pb creation thread philo %i\n", philo[i]->nb);
		else
		{
			printf("ok creation thread philo %i\n", philo[i]->nb);
			philo[i]->th_id = thread;
		}
	}
	return (printf("launcher returned\n"), (void) 0);
}
