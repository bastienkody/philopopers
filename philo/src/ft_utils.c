/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:22:23 by bguillau          #+#    #+#             */
/*   Updated: 2023/05/05 15:57:04 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*	- only digits (except leading '-')
	- nb < 0 returned to arg_checker are reco as errors
	- returns -1 if overflow	*/
int	ft_atoi(const char *nptr)
{
	int		sign;
	int		res;
	int		old_res;

	sign = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	res = 0;
	old_res = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (res < old_res)
			return (-1);
		res = res * 10 + (*nptr++ - '0');
	}
	return (res * sign);
}
