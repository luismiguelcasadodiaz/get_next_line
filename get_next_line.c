/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:58:39 by luicasad          #+#    #+#             */
/*   Updated: 2023/10/13 11:26:27 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

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
/*  If any of the three argument is null, returns null doing nothing          */
/*                                                                            */
/*  Inits new list to null.                                                   */
/*                                                                            */
/*   Loops the list while there is a node to loop throu                       */
/*                                                                            */
/*   Apply f to actual node's content, keeping the result in a buffer `buf.   */
/*                                                                            */
/*   Create a new node having by content 'buf'.                               */
/*                                                                            */
/*   When it does not succed, liberates 'buf' and clean from the new list     */
/*   previously added nodes. When ft_lstclear end, returns null, so ft_lstmap */
/*   at this point returns null.                                              */
/*                                                                            */
/*   When it suceed, add the new node to new_list last node.                  */
/*                                                                            */
/*   I prefer track last node to avoid looping thru the full list each time   */
/*   i call ft_lstadd_back                                                    */
/*                                                                            */
/*   Finally, advance the pointer in lst to the next node.                    */
/*                                                                            */
/*   At while end, retunrns the pointer to new list                           */
/*                                                                            */
char	*get_next_line(int fd)
{
	return (NULL);
}
