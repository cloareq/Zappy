NAME	= zappy_serveur

CC	= gcc
RM	= rm -f

SRC	=
INC	= -I ./includes
###############
#### SOCKRD ####
SOCKRD	= src/getline/getline.c

#### ARGUES ####
ARGUES	= src/args/parse.c

#### ERRROR ####
ERROR	= src/err/lerror.c

#### BUFFER ####
BUFFER	= src/circularBuffer/factory.c

####MONITOR ####
MONITOR	= src/monitor/cmds.c src/monitor/avertCase.c src/monitor/avertTeam.c src/monitor/avertPlayer.c

#### IA CMD ####
CMDS	= src/cmds/movement.c src/cmds/voir.c src/cmds/ressource.c src/cmds/take.c src/cmds/expulse.c src/cmds/broadcast.c src/cmds/fork.c src/cmds/connect_nbr.c src/cmds/incantation.c src/cmds/incantaionPlayerTest.c src/cmds/incantationRessourceTest.c

#### SERVER ####
SERVER	= src/serveur/factory.c src/serveur/destroy.c src/serveur/actualize.c src/serveur/unaff.c src/serveur/client.c src/serveur/waiting.c src/serveur/manageTeam.c src/serveur/iaManagement.c src/serveur/monitor.c src/serveur/iaBuffering.c src/serveur/iaProcess.c src/serveur/treating.c

####  MAIN  ####
MAIN	= src/main/main.c
###############
SRC = $(ARGUES) $(MONITOR) $(SOCKRD) $(ERROR) $(BUFFER) $(CMDS) $(SERVER) $(MAIN)

FLAGS	= -W -Wall -Wextra $(INC)             -g3
CFLAGS	= $(FLAGS)
LDFLAGS	= -O2

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
