/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_next_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:16:41 by luicasad          #+#    #+#             */
/*   Updated: 2023/10/23 10:45:38 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void	show_file(char *filename)
{
	int		fd;
	short	end_file;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Problems opening <%s> file \n", filename);
		return ;
	}
	end_file = 0;
	while (!end_file)
	{
		line = get_next_line(fd);
		if (line == NULL)
			end_file = 1;
		else
			printf("%s", line);
		free(line);
	}
	close(fd);
}

int	main(void)
{
	printf(">%d<\n", BUFFER_SIZE);
	show_file("uno.txt");
	show_file("giant_line_nl.txt");
	show_file("variable_nls.txt");
	show_file("giant_line.txt");
	show_file("one_line_no_nl.txt");
	show_file("dos.txt");
	show_file("1char.txt");
	return (0);
}
