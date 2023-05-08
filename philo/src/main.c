/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:17:03 by bguillau          #+#    #+#             */
/*   Updated: 2023/05/05 16:30:35 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_philo	**philo;
	t_data	*data;

	data = arg_to_data(argc, ++argv);
	if (!data)
		return (1);
	philo = init_philo(data);
	if (!philo)
		return (free(data), 1);
	print_data(data);
	print_philo(philo);

	launcher(philo);
	usleep(1000);
// phtread_join instead of usleep in main ?

	print_philo(philo);

	return (end_free(data, philo), 0);
}
