# Steven Nunes
# afewmore Makefile
NAME = afewmore
SRC = afewmore.c
OBJ = $(SRC:.c=.o)
RM = rm -f

all: $(OBJ)
	cc $(OBJ) -o $(NAME)

clean: 
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.o
	-$(RM) *.swp
	-$(RM) *.core
