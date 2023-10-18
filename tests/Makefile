#Votre Makefile ne doit pas relink. 
# That means that the Makefile should not rebuild all of the targets every time it is run.

NAME = test_get_next_line
CC = cc
CFLAGS = -Wall -Wextra  -Werror -D BUFFER_SIZE=42

# From 4.4.3 The Function wildcard gnu make manual....
# Althought wildcard exparnds automaticaly in rules
# I use the wildcard function to expand wildcards in variables. 
# SRCS = $(wildcard *.c)
#
# This technique is forbidden according to 42 Norm point III.11
#
# So I must explicitly enumerate files for the project.

SRCS = test_get_next_line.c \
       ../get_next_line.c \
       ../get_next_line_utils.c \


BONUS_SRCS = get_next_line_bonus.c \
			 get_next_line_utils_bonus.c \

# Generate a list of object files by replacing .c with .o

OBJS = $(patsubst %.c, %.o, $(SRCS))
BONUS_OBJS = $(patsubst %.c, %.o, $(BONUS_SRCS))

# The default goal is the first target of the first rule in the first makefile.
# This is the reason for writtting this rule the first one


all: $(NAME)


# Vous devez utiliser la commande ar pour créer votre bibliothèque
# NOTE rcs:
# - r  means that if the library already exists, replace the old files within the library with your new files. 
# - c means create the library if it did not exist. 
# - s can be seen to mean 'sort' (create a sorted index of) the library, so that it will be indexed and faster to access the functions in the library.
#   Therefore, rcs can be seen to mean replace, create, sort

$(NAME): $(OBJS)
	@echo "================ GATHERING ALL OBJECTS ====================="
	$(CC) $(OBJS) -o $@


# For each c file create its object file.

%.o: %.c Makefile ../get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@ 

# removes all generated object files
.PHONY: clean
clean:
	@echo "================ REMOVING ALL OBJECTS ======================"
	rm -f *.o
	rm -f *.gch

# removes target file and all generated object files
.PHONY: fclean
fclean: clean
	@echo "================ REMOVING TARGET =========================="
	rm -f $(NAME)

# rebuild all after removing all
.PHONY: re
re: fclean all
	@echo "================ REBUILDING ==============================="
norma: $(SRCS)
	@echo "================ CHECKING NORME ==========================="
	norminette $(SRCS)



# Pour rendre des bonus, vous devez inclure une règle bonus à votre Makefile qui 
# ajoutera les divers headers, librairies ou fonctions qui ne sont pas autorisées 
# dans la partie principale du projet. 
# Les bonus doivent être dans un fichier différent : _bonus.{c/h}.
# There is a contradiciton between french version and english version
# Add structure s_list  declaration to your libft.h file:
bonus:  $(BONUS_OBJS) 
	@echo "================ GATHERING BONUS OBJECTS ====================="
	ar rcs $(NAME) $? 


# FUMADA DE LMCD
#bonus: bonus_setup $(BONUS_OBJS) bonus_restore
#	ar rs $(NAME) $(BONUS_OBJS)
#bonus_setup:
#	@echo "======= ADDING STRUCT s_list DECLARATION TO libft.h ========"
#	head -14 libft.h > tirame.h
#	echo "typedef struct s_list\n{\n\tvoid\t\t\t*content;\n\tstruct s_list\t*next;\n}\t\t\tt_list;\n" >> tirame.h
#	tail -6 libft.h >> tirame.h
#	mv libft.h libft.h.bck
#	mv tirame.h libft.h
#
#bonus_restore:
#	@echo "======= RESTORING libft.h removes struct s_list  ========"
#	mv libft.h.bck libft.h

#%.o: %.c
#	$(CC) $(CFLAGS) -c $< -o $@ 

bonus_clean:
	@echo "================ REMOVING BONUS OBJECTS  ==================="
	rm -f ft_lst*.o

bonus_norma: $(BONUS_SRCS)
	@echo "================ CHECKING NORME FOR BONUS ================="
	norminette $(BONUS_SRCS)
