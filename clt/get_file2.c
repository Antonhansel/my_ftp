/*
** get_file2.c for include in /home/apollo/rendu/PSU_2013_myftp
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Fri Apr 11 20:29:20 2014 ribeaud antonin
** Last update Sun Apr 13 15:27:19 2014 ribeaud antonin
*/

#include "client.h"

char	*getfilename(char *str)
{
  char	**commands;
  int	i;
  char	*slash;

  i = 0;
  commands = my_str_to_wordtab(str, '/');
  while (commands[i] != NULL)
    i++;
  return (commands[i - 1]);
}

FILE	*open_file(char *str)
{
  FILE	*file;
  char	*test;

  file = fopen(getfilename(str), "r");
  if (file == NULL)
    {
      file = fopen(getfilename(str), "w+");
      if (file == NULL)
	printf("Error on creating file\n");
      if (fseek(file, 0, SEEK_END) == -1)
	file = NULL;
      return (file);
    }
  return (file);
}
