/*
** main.c for main in /home/apollo/rendu/my_ftp
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Wed Mar 26 19:22:40 2014 ribeaud antonin
** Last update Wed Apr 16 22:54:41 2014 ribeaud antonin
*/

#include "ftp.h"

void	read_client(t_ftp *ftp)
{
  int	len;
  int	loop;
  char	buf[4096];

  loop = 1;
  memset(buf, 0, sizeof(buf));
  while (loop == 1 && (len = read(ftp->cs, buf, sizeof(buf))) > 0)
    {
      buf[len] = '\0';
      printf("Client@%s:\n", ftp->ipclient);
      if (strcmp(buf, "quit") == 0)
	{
	  send_message("Goodbye...\n", ftp);
	  printf("*Client disconnected*\n");
	  loop = 0;
	}
      else
	exec_cmd(ftp, buf);
      memset(buf, 0, sizeof(buf));
    }
}

void	loop_server(t_ftp *ftp)
{
  int	client_len;
  int	pid;

  client_len = sizeof(ftp->sin_client);
  while (42)
    {
      ftp->cs = accept(ftp->s, (struct sockaddr*)
		       &ftp->sin_client, (socklen_t*)&client_len);
      if (ftp->cs == -1)
	{
	  close(ftp->s);
	  my_error("Error on accepting incoming communications");
	}
      if ((pid = fork()) == 0)
	{
	  ftp->ipclient = inet_ntoa(ftp->sin_client.sin_addr);
	  printf("Client connected from %s\n", ftp->ipclient);
	  send_message(WELCOME, ftp);
	  if (read_user(ftp) == 1)
	    {
	      if (read_password(ftp) == 1)
		read_client(ftp);
	    }
	}
    }
}

void	send_message(char *str, t_ftp *ftp)
{
  write(ftp->cs, str, strlen(str));
}

int	main(int argc, char **argv)
{
  t_ftp	ftp;

  if (argc == 2)
    {
      signal(SIGINT, my_sighandler);
      init_server(atoi(argv[1]), &ftp);
    }
  else
    return (1);
  return (0);
}
