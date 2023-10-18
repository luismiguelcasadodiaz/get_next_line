/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_next_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:16:41 by luicasad          #+#    #+#             */
/*   Updated: 2023/10/18 14:01:59 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void	show_file(char *filename)
{
	int	fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Problems opening <%s> file \n", filename);
		return; 
	}
	while (get_next_line(fd))
			;
	close(fd);
}

int	main(void)
{
	printf(">%d<\n", BUFFER_SIZE);
	show_file("uno.txt");
//	show_file("dos.txt");
//	show_file("tres.txt");
	return (0);
}
