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
1) Export merge arguments
2) Signals
	• give input and ctrl+c causes segfault
<!-- 3) add_history() -->
<!-- 4) executor leaks & refactor
	• unlink() here docs -->
5) general refactor
6) test 🤬
<!-- 7) syntax error format? -->
<!-- 8) echo -> not right print -->
9) check open files
10) modify trim funciton in here_doc

# RANDOM QUESTIONS
1) /bin/echo should run builtin or program ?
