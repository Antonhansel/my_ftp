/*
** error.c for include in /home/apollo/rendu/my_ftp
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Wed Apr  2 23:35:28 2014 ribeaud antonin
** Last update Wed Apr  2 23:35:36 2014 ribeaud antonin
*/

#include "client.h"

void	my_error(char *error)
{
  printf("%s\n", error);
  exit(EXIT_FAILURE);
}
