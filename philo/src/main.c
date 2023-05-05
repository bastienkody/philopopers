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

/*	only positive nb (no '+' sign)
	no underflow possible
	atoi returns -1 if overflow */
int	arg_checker(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (write(2, "Arg nb pb\n", 10), 1);
	while (*argv)
	{
		if (**argv == '-' || ft_atoi(*argv) < 0)
			return (write(2, "Arg < 0 (or int over/under flow)\n", 33), 1);
		while (**argv)
		{
			if (**argv < '0' || **argv > '9')
				return (write(2, "Arg with non digit val\n", 23), 1);
			(*argv)++;
		}
		argv++;
	}
	return (0);	
}

int	main(int argc, char **argv)
{
	if (arg_checker(argc, ++argv))
		return (1);	
}

