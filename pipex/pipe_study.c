#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXLINE 64

int	main()
{
	int	n;					//byte letti in read
	int	fd[2];				//f[0] estremo di lettura - f[1] estremo di scrittura
	pid_t	pid;				//identificatore processo per distinguere padre e figlio
	char	line[MAXLINE];		//buffer per lettura

	if (pipe(fd) < 0)		//CREA LA PIPE
	{
		perror("pipe");
		exit(1);
	}
	if ((pid = fork()) < 0)		//CREA PARENT/CHILD CON FORK
	{
		perror("fork");
		exit(1);
	}
	else if (pid > 0)	//PADRE
	{
		close(fd[0]);	//chiude la lettura
		write(fd[1], "hello world\n", 12);	//scrive sull'estremo di scrittura della pipe
	}
	else				//FIGLIO
	{
		close(fd[1]);	//chiude la scrittura
		n = read(fd[0], line, MAXLINE);		//legge dall'estremo di lettura della pipe
		write(STDOUT_FILENO, line, n);		//scrive in output quello che legge dalla pipe
	}
	exit(0);
}