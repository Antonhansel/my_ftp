/*
** signal.c for signal in /home/apollo/rendu/my_ftp/srv
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Wed Apr  2 23:56:16 2014 ribeaud antonin
** Last update Thu Apr 17 13:18:56 2014 ribeaud antonin
*/

#include "ftp.h"

void	my_sighandler(int sig)
{
  sig = sig;
  printf("\033[31;1m SERVER SHUTTING DOWN \033[0m\n");
  exit(EXIT_SUCCESS);
}

void	my_error(char *error)
{
  printf("%s\n", error);
  exit(EXIT_FAILURE);
}
