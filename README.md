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

# PROBLEMS
2) export $HOME=USER

# NICO
1) Leaks - expander and quote removal
2) env/export notes
3) export and unset validation

# FARSHAD
1) Signals
2) Use tests
3) Check if every file is closed
4) Export has to print out in ascii order (not alphabetical)
5) echo (now minishell uses the /bin/echo)
