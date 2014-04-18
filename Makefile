##
## Makefile for Makefile in /home/apollo/rendu/my_ftp
## 
## Made by ribeaud antonin
## Login   <ribeau_a@epitech.net>
## 
## Started on  Wed Mar 26 19:38:12 2014 ribeaud antonin
## Last update Sun Apr 13 15:33:09 2014 ribeaud antonin
##

SRV_NAME	= server

SRV_SRCS	= srv/server.c\
		srv/password.c\
		srv/commands.c\
		srv/init.c\
		srv/signal.c\
		srv/send_file.c\
		srv/send_file2.c\
		srv/str_to_wordtab.c\
		srv/chdir.c

SRV_OBJS	= $(SRV_SRCS:.c=.o)

CLI_NAME	= client

CLI_SRCS	= clt/client.c\
		clt/password.c\
		clt/commands.c\
		clt/error.c\
		clt/str_to_wordtab.c\
		clt/get_file.c\
		clt/basic.c \
		clt/get_file2.c

CLI_OBJS	= $(CLI_SRCS:.c=.o)

CC		= gcc

RM		= rm -f

CFLAGS		= -pedantic -ansi -Wextra

all		: $(CLI_NAME) $(SRV_NAME)

$(CLI_NAME)	: $(CLI_OBJS)
		$(CC) -o $(CLI_NAME) $(CLI_OBJS) $(CFLAGS) -lcrypt


$(SRV_NAME)	: $(SRV_OBJS)
		$(CC) -o $(SRV_NAME) $(SRV_OBJS) $(CFLAGS)

clean		: 
		$(RM) $(SRV_OBJS)
		$(RM) $(CLI_OBJS)

fclean		: clean
		$(RM) $(SRV_NAME)
		$(RM) $(CLI_NAME)

re		: fclean all
