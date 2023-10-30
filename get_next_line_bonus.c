/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:58:39 by luicasad          #+#    #+#             */
/*   Updated: 2023/10/30 13:24:16 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE
#endif

/* read_to_buff()  joins existing buffer and read bytes from file descriptor  */
/*                                                                            */
/* GETS                                                                       */
/*  fd : The file descriptor to read from                                     */
/*  *read_buf : A buffer to concat in the read bytes from fd                  */
/*  *read_bytes: a by reference integer to return file end condition          */
/*                                                                            */
/* RETURNS                                                                    */
/*  The new_buf resulting from the join of read_buf + read_raw                */
/*                                                                            */
/* RETURNS THRU ARGUMENTS                                                     */
/*  The number of bytes read.                                                 */
/*  - A positive integer >0 normal behaviour.                                 */
/*  - Zero when end of file and no more bytes to read remain in fd.           */
/*  - Negative when other problems with fd.                                   */
/*                                                                            */
/* OPERATION                                                                  */
/*                                                                            */
/* Automatic Variables                                                        */
/*  *new_buf keeps read_buf + read_raw and returns it.                        */
/*  *read_raw to keep read bytes from file descriptor.                        */
/*                                                                            */
/* Allocates memory to fill in with bytes read from file.                     */
/*                                                                            */
/* when reading from file fails cause end or file (read_bytes == 0)           */
/*     deallocates memory used for reading read_raw                           */
/*     returns unchanged read_buf.                                            */
/*                                                                            */
/* when reading from file fails cause other error (read_bytes == -1)          */
/*     deallocates memory used for reading read_raw                           */
/*     returns NULL                                                           */
/*                                                                            */
/* when reading from file is OK                   (read_bytes > 0  )          */
/*     null terminated read_raw                                               */
/*     append it to read_buf                                                  */
/*                                                                            */
/*     deallocate memory used for reading read_raw                            */
/*                                                                            */
/*     when Join fails return NULL                                            */
/*                                                                            */
/*     Deallocate obsolete read_buf                                           */
/*                                                                            */
/*     Retunrs Join read_buf + read_raw                                       */
/*                                                                            */

char	*read_to_buff(int fd, char	*read_buf, ssize_t *read_bytes)
{
	char		*read_raw;
	char		*new_buf;

	read_raw = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (read_raw == NULL)
		return (my_free(&read_buf));
	*read_bytes = read(fd, read_raw, BUFFER_SIZE);
	if (*read_bytes <= 0)
	{
		my_free(&read_raw);
		if (*read_bytes == -1)
			return (my_free(&read_buf));
		return (read_buf);
	}
	read_raw[*read_bytes] = '\0';
	new_buf = gnl_join(read_buf, read_raw);
	my_free(&read_raw);
	if (new_buf == NULL)
		return (NULL);
	my_free(&read_buf);
	return (new_buf);
}

/* buff_analisis() joins existing buffer and read bytes from file descriptor  */
/*                                                                            */
/* GETS                                                                       */
/*  fd : The file descriptor to read from                                     */
/*  *read_buf : A buffer to concat in the read bytes from fd                  */
/*  *read_bytes: a by reference integer to return file end condition          */
/*                                                                            */
/* RETURNS                                                                    */
/*  The new_buf resulting from the join of read_buf + read_raw                */
char	*buff_analisis(char	**read_buf)
{
	char	*line;
	char	*new_buf;
	ssize_t	buf_len;
	ssize_t	ret;

	if (*read_buf == NULL)
		return (NULL);
	buf_len = gnl_strlen_and_nl(&ret, read_buf[0]);
	if (ret == -1)
		return (NULL);
	line = gnl_substr(*read_buf, 0, (ret + 1));
	if (!line)
		return (NULL);
	new_buf = gnl_substr(*read_buf, (ret + 1), (buf_len - (ret + 1)));
	if (!new_buf)
		return (my_free(&line));
	free(*read_buf);
	*read_buf = new_buf;
	return (line);
}

char	*buff_flush(char **read_buf)
{
	char	*line;
	size_t	i;

	if (*read_buf == NULL)
		return (my_free(read_buf));
	i = gnl_strlen(read_buf[0]);
	line = (char *)malloc(i + 1);
	if (!line)
		return (my_free(read_buf));
	i = 0;
	while (read_buf[0][i] != '\0')
	{
		line[i] = read_buf[0][i];
		i++;
	}
	line[i] = '\0';
	my_free(read_buf);
	return (line);
}

/* get_next_line() returns a line from a file descriptor.                     */
/*                                                                            */
/* GETS                                                                       */
/*  fd : The file descriptor to read from                                     */
/*                                                                            */
/* RETURNS                                                                    */
/*  Read line: correct behavior.                                              */
/*  NULL     : there is nothing else to read, or an error occurred            */
/*                                                                            */
/* OPERATION                                                                  */
/*                                                                            */
/* Automatic Variables                                                        */
/*  read_raw to keep bytes as they come from file.                            */
/*  read_buf to keep read bytes not yet delivered.                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*  If i have not bytes to deliver (read_buf == NULL) then i read more        */
/*                                                                            */
char	*get_next_line(int fd)
{
	static char	*read_buf[OPEN_MAX];
	ssize_t		read_bytes;
	char		*line;

	if (0 <= fd && fd < OPEN_MAX)
	{
		while (1)
		{
			line = buff_analisis(&read_buf[fd]);
			if (line)
				return (line);
			read_buf[fd] = read_to_buff(fd, read_buf[fd], &read_bytes);
			if (!read_buf[fd] && (read_bytes == -1))
			{
				free(line);
				return (my_free(&read_buf[fd]));
			}
			if (!read_buf[fd] && (read_bytes == 0))
				return (my_free(&read_buf[fd]));
			if (read_buf[fd] && (read_bytes == 0))
				return (buff_flush(&read_buf[fd]));
		}
	}
	else
		return (NULL);
}
