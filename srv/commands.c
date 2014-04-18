/*
** commands.c for commands in /home/apollo/rendu/my_ftp
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Wed Apr  2 23:39:15 2014 ribeaud antonin
** Last update Fri Apr 11 23:27:59 2014 ribeaud antonin
*/

#include "ftp.h"

void	my_delete(t_ftp *ftp, char **arg)
{
  if (arg[1] == NULL)
    {
      send_message("Missing Argument.", ftp);
      printf("ERROR: delete needs arguments");
    }
  else if (remove(arg[1]) == -1)
    {
      send_message("Cannot delete file", ftp);
      printf("ERROR: Cannot delete %s\n", arg[1]);
    }
  else
    {
      send_message("File successfully deleted\n", ftp);
      printf("SUCCESS: File %s successfully deleted\n", arg[1]);
    }
}

void	my_pwd(t_ftp *ftp)
{
  char	cwd[4096];

  memset(cwd, 0, sizeof(cwd));
  if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
      printf("SUCCESS: pwd\n");
      ftp->pwd = cwd;
      send_message(cwd, ftp);
    }
  else
    {
      send_message("Impossible to get current working directory\n", ftp);
      printf("ERROR: pwd: impossible to get current working directory\n");
    }
}

void		my_ls(t_ftp *ftp)
{
  FILE		*file;
  char		buffer[4096];
  size_t       	ret;
  int		cont;

  cont = 1;
  if ((file = popen("ls -l --color", "r")) == NULL)
    send_message("Impossible to list directory.\n", ftp);
  else
    {
      memset(buffer, 0, sizeof(buffer));
      while (cont == 1 && (ret = fread(buffer, 1, sizeof(buffer), file)) > 0)
	{
	  if (ret < sizeof(buffer))
	    cont = 0;
	  send_message(buffer, ftp);
	  memset(buffer, 0, sizeof(buffer));
	}
      printf("SUCCESS: ls\n");
    }
}

void	check_args(t_ftp *ftp, char **args, char *buf)
{
  if (strcmp(args[0], "delete") == 0)
    my_delete(ftp, args);
  else if (strcmp(args[0], "cd") == 0 && args[1] != NULL)
    my_chdir(ftp, args[1]);
  else if (strcmp(args[0], "get") == 0)
    get_file(ftp, args);
  else
    {
      printf("ERROR: Command not found: %s\n", buf);
      send_message("Error: Command not founnd\n", ftp);
    }
}

void	exec_cmd(t_ftp *ftp, char *buf)
{
  char	**args;

  args = my_str_to_wordtab(buf, ' ');
  if (strcmp(buf, "ls") == 0)
    my_ls(ftp);
  else if (strcmp(buf, "pwd") == 0)
    my_pwd(ftp);
  else
    check_args(ftp, args, buf);
}
