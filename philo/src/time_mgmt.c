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

unsigned long int	timeval_cmp(struct timeval tv_0, struct timeval tv_tmp)
{
	if (tv_tmp.tv_sec == tv_0.tv_sec)
		return (tv_tmp.tv_usec - tv_0.tv_usec);
	else
		return ((tv_tmp.tv_sec - tv_0.tv_sec) * 1000000\
				+ (tv_tmp.tv_usec - tv_0.tv_usec));
}
/*	1 sec
	1 000 ms (milli second)
	1 000 000 us (microsecond)
	--> if tv.usec >= 1M then tv.sec +=1 and tv.usec = 0	*/

void	ft_usleep(unsigned int usec)
{
	struct timeval		tv_0;
	struct timeval		tv_tmp;
	unsigned long int	delta;

	delta = 0;
	gettimeofday(&tv_0, NULL);
	while (delta < usec)
	{
		usleep(5);
		gettimeofday(&tv_tmp, NULL);
		printf("%lu\n", delta = timeval_cmp(tv_0, tv_tmp));
	}
	printf("delta:%lu\n", delta);
	/* vs vrai usleep !*/
	gettimeofday(&tv_0, NULL);
	usleep(10000);
	gettimeofday(&tv_tmp, NULL);
	printf("%lu\n", delta = timeval_cmp(tv_0, tv_tmp));
}
