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

/*	returns timestamp (current time since simulation start in ms)	*/
unsigned long int	c_time(struct timeval t0)
{
	struct timeval	tmp;

	gettimeofday(&tmp, NULL);
	return ((tmp.tv_sec - t0.tv_sec) * 1000000 + tmp.tv_usec - t0.tv_usec);
}

void	ft_usleep(unsigned int usec)
{
	struct timeval		tv_0;

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
