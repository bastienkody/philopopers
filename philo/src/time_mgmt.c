/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_mgmt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:45:18 by bguillau          #+#    #+#             */
/*   Updated: 2023/05/15 18:45:21 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*	returns timestamp (elapsed time since tv_0)	*/
unsigned long int	c_time(struct timeval t0)
{
	struct timeval	tmp;

	gettimeofday(&tmp, NULL);
	return ((tmp.tv_sec - t0.tv_sec) * 1000000 + tmp.tv_usec - t0.tv_usec);
}

/*	check simulation go_on while sleeping	*/
void	big_usleep(unsigned int usec, t_philo *philo)
{
	struct timeval		tv_0;

	gettimeofday(&tv_0, NULL);
	while (check_go_on(philo) && c_time(tv_0) < usec)
		usleep(1000);
}

void	ft_usleep(unsigned int usec, t_philo *philo)
{
	struct timeval		tv_0;

	if (usec > 1000000)
		return (big_usleep(usec, philo));
	gettimeofday(&tv_0, NULL);
	usleep(usec / 10 * 9);
	while (c_time(tv_0) < usec)
		usleep(2);
}

void	set_t0(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	data->t0 = tv;
}
