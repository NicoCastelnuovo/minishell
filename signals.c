#include <signal.h>
#include <unistd.h>

void executor();

int main()
{

	while (1)
	{
		setup_parent_signals(); //handle signals in the parent process --> Ctrl-C = newline and Ctrl-\ = IGNORED
		char *line = readline("prompt");
		if (!line) // Ctrl-D
			break ;
		// lexer, parser, executor
		executor();
	}

}

void executor()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	int pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		// do child stuff
	}
	else
	{
		// do parent stuff
	}
}