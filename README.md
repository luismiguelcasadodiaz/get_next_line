# Get next line
This project is about programming a function that returns a line
read from a file descriptor.

It will also make you learn a highly interesting new concept in C programming: static variables.

## Function prototype:

``` python
char	*get_next_line(int fd);
```

## Arguments
Gets a integer number that refers to the file descriptor to read from.

Having a correct behavior, returns, read line, one line at a time. otherwise retunrs NULL if ther is nothing else to read, or an error occurred.

Only read, malloc, and free functions are allowed.


We consider that get_next_line() has an undefined behavior if the file pointed to by the file descriptor changed since the last call whereas read() didn’t reach the end of file.

We also consider that get_next_line() has an undefined behavior when reading
a binary file. However, you can implement a logical way to handle this behavior if you want to.

## Bonus
A) Develop get_next_line() using only one static variable.

B) Your get_next_line() can manage multiple file descriptors at the same time.  For example, if you can read from the file descriptors 3, 4 and 5, you should be able to read from a different fd per call without losing the reading thread of each file descriptor or returning a line from another fd.  It means that you should be able to call get_next_line() to read from fd 3, then fd 4, then 5, then once again 3, once again 4, and so forth.

## Compilation

Because you will have to read files in get_next_line(), add this option to your compiler call: -D BUFFER_SIZE=n

It will define the buffer size for read().  The buffer size value will be modified by your peer-evaluators and the Moulinette in order to test your code.

**We must be able to compile this project WITH and WITHOUT** the -D BUFFER_SIZE flag in addition to the usual flags. You can choose the default value of your choice. I defined the BUFFER_SIZE in get_next_line.h file just in case the compiler does note defient it for me.

```Makefile
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 43
# endif /* BUFFER_SIZE */
```

You will compile your code as follows (a buffer size of 42 is used as an example): cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c

To have more flexibility defining buffer size at compilation time i figured out how to invoke `make` with an argument:

```bash
make SIZE=100
```

Then inside `Makefile` my `CFLAGS` definition becomes:

```Makefile
ifeq ($(SIZE),)
	CFLAGS = -Wall -Wextra  -Werror
else
 	CFLAGS = -Wall -Wextra  -Werror -D BUFFER_SIZE=$(SIZE)
endif
```

With a file `size.txt` and an additional variable `PREVIOUS_SIZE` I check if buffer size has changed, so i need to recompile.

```Makefile

PREVIOUS_SIZE=$(shell cat size.txt)

all: $(NAME) 
ifeq ($(SIZE),$(PREVIOUS_SIZE))
	@echo "No size change"
else
	@echo "size change"
	@echo $(SIZE) > size.txt
	@make re
endif
```

