/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_next_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:16:41 by luicasad          #+#    #+#             */
/*   Updated: 2023/10/24 10:29:31 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	my_open(char *name)
{
	int	fd;

	fd = open(filename1, O_RDONLY);
	if (fd < 0)
	{
		printf("Problems opening <%s> file \n", name);
		return (-1);
	}
	return (fd);
}

void	show_file(char *filename1, char *filename2, char *filename3)
{
	int		fd[3];
	short	end_file[3];
	char	*line;

	fd[0] = my_open(filename1);
	fd[1] = my_open(filename2);
	fd[2] = my_open(filename3);
	end_fil[0] = end_fil[1] = end_fil[2] = 0;
	while (!end_file[0] && !end_file[1] &&!end_file[2])
	{
		end_file[0] = ((line = get_next_line(fd[0])) == NULL);
		printf("%s", line);
		free(line);
		end_file[1] = ((line = get_next_line(fd[1])) == NULL);
		printf("%s", line);
		free(line);
		end_file[2] = ((line = get_next_line(fd[2])) == NULL);
		printf("%s", line);
		free(line);
	}
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
}

int	main(void)
{
	printf(">%d<\n", BUFFER_SIZE);
	show_file("uno.txt", "dos.txt", "tres.txt");
	return (0);
}
