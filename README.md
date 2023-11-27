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


# RANDOM QUESTIONS
1) Syntax err = 258 or 2 ?
2) echo $99Nico: original is 9Nico, our is empty, because it searches for a var called 99Nico
	but with export and unset, starting with a number is not a valid identifier
3) Not sure about env->to_export variable, which told if the variable has to be exported

# NICO
<!-- 1) Leaks - expander and quote removal -->
2) env
	- export -> multiple args, <!-- invalid identifier -->
	<!-- - unset -> invalid identifier -->
	- what if env -i
	- set $_ variable and understand what it does
	- initialize OLDPWD but set to NULL
3) Why hello$?$? executed for two times is first -> hello00 and then hello$?$?

# FARSHAD
1) Signals
2) Use tests
3) Check if every file is closed
4) export -> print in alphabetical order
5) echo (now minishell uses the /bin/echo)
