/*
** commands.c for command in /home/apollo/rendu/my_ftp
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Wed Apr  2 23:34:47 2014 ribeaud antonin
** Last update Sun Apr 13 15:27:56 2014 ribeaud antonin
*/

#include "client.h"

int	check_command(char *buf)
{
  char	**command;

  command = my_str_to_wordtab(buf, ' ');
  if (strcmp(command[0], "get") == 0)
    {
      if (command[1] != NULL)
	return (1);
      else
	{
	  printf("Command get needs arguments\n");
	  return (2);
	}
    }
  else if (strcmp(command[0], "put") == 0)
    {
      if (command[1] != NULL)
	return (3);
      else
	{
	  printf("Command get needs arguments\n");
	  return (2);
	}
    }
  else
    return (0);
}
