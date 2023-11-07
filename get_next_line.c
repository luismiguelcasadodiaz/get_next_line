/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:58:39 by luicasad          #+#    #+#             */
/*   Updated: 2023/11/07 10:33:49 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

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
/* TAKE AWAYS                                                                 */
/*                                                                            */
/*   if something fails release strings passed by value like char *read_buf   */
/*                                                                            */
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

/* buff_analisis() splits buffer by first newline  in line and new_buf        */
/*                                                                            */
/* GETS                                                                       */
/*  **read_buf : A passed by reference buffer to split it by first newline    */
/*                                                                            */
/* RETURNS                                                                    */
/*  line : string containing read_buf initial chars till newline included     */
/*                                                                            */
/* RETURNS THRU by reference ARGUMENTS                                        */
/*  **read_buf : buffer where initial chars and newline included were removed */
/*                                                                            */
/*  OPERATES                                                                  */
/*                                                                            */
/*  When read_buf is empty ,nothing to analyze,  return null.                 */
/*                                                                            */
/*  Calculate read_buf lenght and find first new line.                        */
/*                                                                            */
/*  When no newline exist (ret == -1) returns NULL.                           */
/*                                                                            */
/*  Extract line to return from buffer init to newline position included.     */
/*                                                                            */
/*  When malloc fails returns NULL.                                           */
/*                                                                            */
/*  Extract remaining buffer to new_buf.                                      */
/*                                                                            */
/*  ATTENTION: gnl_substr returns NULL in two situations:                     */
/*     Malloc fails.                                                          */
/*     New line is at buffer end so new_buffer has to be empty                */
/*     This is the reason for !new_buf && (buf_len - (ret + 1))               */
/*                                        |--------v-----------|              */
/*                                        if != 0 malloc fails                */
/*                                        if == 0 empty new_buf               */
/*                                                                            */
/*  when malloc fails free previous extracted line and returns NULL.          */
/*                                                                            */
/*  Frees older buffer and assign to buffer new buffer.                       */
/*                                                                            */
/*  returns extractes line including a new line.                              */
/*                                                                            */
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
	if (!new_buf && (buf_len - (ret + 1)))
		return (my_free(&line));
	free(*read_buf);
	*read_buf = new_buf;
	return (line);
}

/* buff_flush() Empties the buffer                                            */
/*                                                                            */
/* GETS                                                                       */
/*  **read_buf : A passed by reference buffer to empty it and return leftover */
/*                                                                            */
/* RETURNS                                                                    */
/*  line : string containing read_buf letfovers                               */
/*                                                                            */
/* RETURNS THRU by reference ARGUMENTS                                        */
/*  **read_buf : buffer settle to NULL after empty the buffe                  */
/*                                                                            */
/*  OPERATES                                                                  */
/*                                                                            */
/*  When read_buf is empty ,nothing to analyze,  return null.                 */
/*                                                                            */
/*  Calculate read_buf lenght.                                                */
/*                                                                            */
/*                                                                            */
/*  allocate memory for a returning line wiht buffer content.                 */
/*                                                                            */
/*  When malloc fails returns NULL after releasing buffer.                    */
/*                                                                            */
/*  Copies buffer content into returning line.                                */
/*                                                                            */
/*  null terminate retunrning line.                                           */
/*                                                                            */
/*  Frees older buffer.                                                       */
/*                                                                            */
/*  returns extracted line.                                                   */
/*                                                                            */
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
/*  STATIC read_buf to keep read bytes not yet delivered from call to call    */
/*  read_bytes to keep amount of bytes read from file.                        */
/* *line to partially return buffer as long a newline is found.               */
/*                                                                            */
/*  A infinite loop starts analysing the buffer trying to find a newline      */
/*  inside.                                                                   */
/*                                                                            */
/*  if a newline is found retunrs the line.                                   */
/*  if not reads from the file.                                               */
/*                                                                            */
/*  Reading file retursn 3 possible situation diferenciated thru read_bytes   */
/*                                                                            */
/*  when read_bytes == -1 an error reading file happened:                     */
/*            release line                                                    */
/*            release buffer                                                  */
/*            returns NULL                                                    */
/*                                                                            */
/*  when read_bytes == 0, nothing else to read. wha have two cases:           */
/*                                                                            */
/*    buffer is empty:                                                        */
/*    		 release buffer                                                   */
/*    		 return NULL                                                      */
/*                                                                            */
/*    buffer with leftovers                                                   */
/*           flush the buffer                                                 */
/*                                                                            */
char	*get_next_line(int fd)
{
	static char	*read_buf;
	ssize_t		read_bytes;
	char		*line;

	while ((0 <= fd && fd <= FOPEN_MAX) && (BUFFER_SIZE > 0))
	{
		line = buff_analisis(&read_buf);
		if (line)
			return (line);
		read_buf = read_to_buff(fd, read_buf, &read_bytes);
		if (!read_buf && (read_bytes == -1))
		{
			free(line);
			return (my_free(&read_buf));
		}
		if (!read_buf && (read_bytes == 0))
			return (my_free(&read_buf));
		if (read_buf && (read_bytes == 0))
			return (buff_flush(&read_buf));
	}
	return (NULL);
}
