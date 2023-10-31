/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:58:39 by luicasad          #+#    #+#             */
/*   Updated: 2023/10/31 12:17:44 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE
#endif

/* gnl_strlen_and_nl() returns s'lenght and the pos of a newline char in s    */
/*                                                                            */
/* GETS                                                                       */
/*  *read_buf : the buffer to find newline in and to return it length         */
/*  *pos      : integer to return newline posiiton inside read_buf            */
/*                                                                            */
/* RETURNS                                                                    */
/*   read_buf's length                                                        */
/*                                                                            */
/*   THRU passed by reference pos, the position of the newline,-1 otherwise   */
/*                                                                            */
/* OPERATES                                                                   */
/*                                                                            */
/*   set pos to -1  s it is no newline found                                  */
/*                                                                            */
/*                                                                            */
/*   Loops buffer till the end.                                               */
/*                                                                            */
/*   Inside each loop, while not newline found, checks for a newline          */
/*                                                                            */
/*   when the new line was found, recor its posiiton in pos.                  */
/*                                                                            */
/*   returns read_buf's length                                                */
/*                                                                            */
/*                                                                            */
size_t	gnl_strlen_and_nl(ssize_t *pos, char	*read_buf)
{
	ssize_t	i;

	*pos = -1;
	i = 0;
	if (read_buf)
	{
		while (read_buf[i] != '\0')
		{
			if ((read_buf[i] == '\n') && (*pos == -1))
				*pos = i;
			i++;
		}
	}
	return (i);
}

/*                                                                            */
/* gnl_strlen() returns s'lenght                                              */
/*                                                                            */
size_t	gnl_strlen(char	*s)
{
	size_t	i;

	i = 0;
	if (s)
		while (s[i] != '\0')
			i++;
	return (i);
}

/* gnl_join() joins preffix(buf) with suffix(raw). Both null terminated       */
/*                                                                            */
/* Buf can be empty. The function handles this situation.                     */
/*   A) do not request start in a position bigger than str's length           */
/*   B) do not request len character greater than the difference between      */
/*      str's length minus start position.                                    */
/* GETS                                                                       */
/*  *buf  : The preffix string.                                               */
/*  *raw  : the suffix  string.                                               */
/*                                                                            */
/* RETURNS                                                                    */
/*  preffix + suffix + null-terminator is the normal behaviour                */
/*  NULL     : When ENOMEM.                                                   */
/*                                                                            */
/* OPERATION                                                                  */
/*  set buf_size to zero and navigated it if exists to know its lenght        */
/*  set raw_size to zero and navigated it to know its lenght                  */
/*  allocate memory for resulting string                                      */
/*  use idx to index new, buf and raw. the index in raw is subtractes by      */
/*      buf size                                                              */
/*  copy buf over new                                                         */
/*  copy raw over new after buf                                               */
/*  free both raw and former buf                                              */
/*                                                                            */
char	*gnl_join(char *buf, char *raw)
{
	size_t	buf_size;
	size_t	raw_size;
	size_t	idx;
	char	*newbuf;

	buf_size = gnl_strlen(buf);
	raw_size = gnl_strlen(raw);
	newbuf = (char *)malloc(buf_size + raw_size + 1);
	if (newbuf == NULL)
		return (my_free(&buf));
	idx = 0;
	while (idx < (buf_size))
	{
		newbuf[idx] = buf[idx];
		idx++;
	}
	while ((idx - buf_size) < raw_size)
	{
		newbuf[idx] = raw[idx - buf_size];
		idx++;
	}
	newbuf[idx] = '\0';
	return (newbuf);
}

/* gnl_substr () returns a substring of size len from a string starting in    */
/* the start position                                                         */
/*                                                                            */
/* It is a simplification form FT_substr. Calling function is responsible for */
/*   A) do not request start in a position bigger than str's length           */
/*   B) do not request len character greater than the difference between      */
/*      str's length minus start position.                                    */
/* GETS                                                                       */
/*  *read_buf : The string to extract from.                                   */
/*  start : Substring initial position.                                       */
/*  len   : Size of string to return.                                         */
/*                                                                            */
/* RETURNS                                                                    */
/*  Substring: correct behavior.                                              */
/*  NULL     : When ENOMEM or len = 0.                                        */
/*                                                                            */
/* OPERATES                                                                   */
/*   When len = 0 returns NULL as there are no requires chars to extract.     */
/*                                                                            */
/*   Allocates memory for chars to extract and return in a null terminated    */
/*   string.                                                                  */
/*                                                                            */
/*   Copies len chars from read_buf to line and null terminate it.            */
/*                                                                            */
/*   returns line.                                                            */
/*                                                                            */
char	*gnl_substr(char *read_buf, unsigned int start, size_t len)
{
	char	*line;
	size_t	idx;

	if (len == 0)
		return (NULL);
	line = (char *)malloc(len + 1);
	if (!line)
		return (my_free(&line));
	idx = 0;
	while (idx < len)
	{
		line[idx] = read_buf[start + idx];
		idx++;
	}
	line[idx] = '\0';
	return (line);
}

/* my_free() releases memory, sets pointer to null ans returns null.          */
/*                                                                            */
/* It is a helper function that saves me lines of code to pass norminette     */
/*                                                                            */
char	*my_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}
