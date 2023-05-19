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

/*	si philo n'est pas en train de manger
	et que last_meal ++ tt_die >= current_time
	-> Death*/
void	check_death(t_philo **philo)
{
	int	i;

	i = -1;
	while (philo[++i])
	{
		//mutex lock?
		if (!philo[i]->state == E && philo[i]->last_meal + philo[i]->data->tt_die > c_time(philo[i]->data->t0))
		{
			philo[i]->state = DEAD;
			ft_printer(c_time(philo[i]->data->t0), philo[i]->nb, D, philo[i]->data->wutex);
			philo[i]->data->go_on = FALSE; // mutex on go_on?
		}
		//mutex unlock?
	}
}

/*	check que tous les philos ont mange les n fois
	si un seul a nb_meal == -1 -> on return
	si un seul a nb_meal > 0 -> return
	sinon ils sont tous a zero : c fini	*/
void	check_meal(t_philo **philo)
{
	int	i;

	i = -1;
	while (philo[++i])
	{
		if (philo[i]->meal_nb != 0)
			return ;
	}
	philo[0]->data->go_on = FALSE; // mutex go_on? 
}

/*	gives activity to each philo
	hould i set t0 here? how?	*/
void	*routine(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *) phil;
	//printf("salut from philo %i\n", ((t_philo *) philo)->nb);
	//if (!philo->data->t0)
		//gettimeofday(philo->data->t0, NULL);
	philo->last_meal = 0;
	if (!(philo->nb & 1)) //pairs
		eatp(philo);
	else 
		thinkp(philo);
	return (printf("routine returned philo %i\n", philo->nb), NULL);
}

void	launcher(t_philo **philo)
{
	pthread_t	thread;
	int			i;

	
	i = -1;
	while (philo[++i])
	{
		if (pthread_create(&thread, NULL, &routine, philo[i]))
			return (phcreate_failure_mgmt(philo, i + 1), (void) 0);
		else
			philo[i]->t_id = thread;
	}

	// main thread must check deaths + nb_meals here

	i = -1;
	while (philo[++i])
	{
		if (pthread_join(philo[i]->t_id, NULL))
			printf("pb joining t_id %luWhat can i do??\n", philo[i]->t_id);
		else
			printf("joined t_id %lu\n", philo[i]->t_id);
	}
	return (printf("launcher returned\n"), (void) 0);
}
