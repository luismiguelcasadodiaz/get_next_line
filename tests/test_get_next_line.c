/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_next_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:16:41 by luicasad          #+#    #+#             */
/*   Updated: 2023/10/18 09:56:53 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../get_next_line.h"
#include <stdio.h>

int	main(void)
{
	printf(">%d<\n", BUFFER_SIZE);
	get_next_line(12);
	get_next_line(12);
	get_next_line(15);
	get_next_line(12);
	get_next_line(12);
	get_next_line(12);
	return (0);
}
