/*
** send_file2.c for send_file2 in /home/apollo/rendu/oldftp
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Fri Apr 11 21:39:57 2014 ribeaud antonin
** Last update Sun Apr 13 15:12:45 2014 ribeaud antonin
*/

#include "ftp.h"

void	transfer_failed(t_ftp *ftp, int fd)
{
  printf("Transfer failed\n");
  send_message("Fail.\n", ftp);
  close(fd);
}

void	send_size(t_ftp *ftp)
{
  char	buffer[128];

  printf("Total filesize %i\n", ftp->filesize);
  memset(buffer, 0, sizeof(buffer));
  sprintf(buffer, "%i", ftp->filesize);
  send_message(buffer, ftp);
}

