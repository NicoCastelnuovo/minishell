# minishell
Implementation of Bash and some of its functionalities using C as programming language.

# EXECUTION PRIORITY
1) here_doc are the first processed, in the order they are in the pipe chain.

# EXECUTION PRECEDENCE
1) < > << >> explicit redirections wins over pipe
2) and between multiple, the last one wins

char *s1 = "Fuck " [******] 0x123 --> 0x145
char *s2 = "You"   [****]	0x124
char *tmp = s1; 0x123

s1 = ft_strjoin(s1, s2);
free(tmp);

# WHAT TO DO

# NICO
8) Error handling
6) export: need to merge arguments abd sort

7) cd: maybe add c dwithout arguments which goes to home
1) Adjust add_history() -> no empty line, no after ctrl-C
5) Signals
2) echo
3) exit (see eval sheet)

# FARSHAD
4) Executor:
	- exit code
	- abs/rel path
	- Try with ../../../../../../../../../../ and ../../
	- understand hoe behaves ./custom_program
	- check for case sensitive
	- check for dquotes/squotes
	- unset $PATH and test
	- set $PATH with something else: /minishell/custom_path_1:/minishell/custom_path_2
	- check for permissions when creating files
