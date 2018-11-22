#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#define PROMPT "TYPE>"
#define R 0
#define W 1

#define N 0x100
#define MAXIN 0x100000

/* Ejemplo básico de lectura y escritura para un proceso ssh que no necesite password. */
/* Se podría completar poniendo un manejador de SIGCHLD */
/* Sólo es un ejemplo. Que nadie se vuelva loco haciendo suposiciones */
int
main (int argc, char *argv[])
{
  int writing[2], reading[2];	/* Reading and writing from parent point of view */
  pid_t ssh_ps = 0;


  char user[N] = "fquintana";
  char host[N] = "localhost";
  char input[N];

  char arg[N];
  const char *command = "ssh";


  system ("clear");
  printf ("This program pipes an ssh connection.\n\n");

  printf ("Please provide some data for establishing the connection.\n");

  sprintf (arg, "%s@%s", user, host);
  printf ("Proceeding to: %s %s\n", command, arg);

  pipe (writing);		/* Writing to ssh */
  pipe (reading);		/* Reading from ssh */
  // error checking for fcntl
  if (fcntl (reading[R], F_SETFL, O_NONBLOCK) < 0) /* Para que las operaciones de lectura no se bloqueen cuando no hay nada. */
    exit (2);

  ssh_ps = fork ();
  if (ssh_ps)
    {				/* Parent process */
      int nread;
      bool quit = false, writtime = false;
      char pipein[N];
      close (writing[R]);
      close (reading[W]);

      sleep (2);

      do
	{

	  printf ("[RECEIVED MSSG]: ");
	  writtime = false;
	  while ((nread = read (reading[R], pipein, MAXIN)) && !writtime)
	    {
	      switch (nread)
		{
		case -1:
		  if (errno == EAGAIN)
		    {		/* Tubería vacía */
		      writtime = true;
		      break;
		    }
		  else
		    {
		      perror ("Error de lectura.");
		      exit (4);
		    }
		  break;
		case 0:
		  /* EOF */
		  quit = true;
		  break;
		default:
		  printf ("%s", pipein);
		}
	    }
	  printf ("[END MSSG]: ");
	  __fpurge (stdin);
	  printf ("\n%s ", PROMPT);
	  fgets (input, N, stdin);
	  quit = strcasestr (input, "quit");
	  if (!quit)
              write(writing[W], input, strlen(input) + 1);
          else
              write(writing[W], "exit", strlen("exit") + 1);
	}
      while (!quit);

      close (writing[W]);
      close (reading[R]);

    }
  else
    {
      close (writing[W]);
      close (reading[R]);

      dup2 (writing[R], STDIN_FILENO);
      dup2 (reading[W], STDOUT_FILENO);
      dup2 (reading[W], STDERR_FILENO);
      execlp (command, command, "-tt", arg, (char *) NULL);

      fprintf (stderr, "Couldn't open ssh.\n");
      close (writing[R]);
      close (reading[W]);
    }

  return EXIT_SUCCESS;
}
