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
1) Export merge arguments && ascii order
2) Signals
	• give input and ctrl+c causes segfault
9) check open files
12) test 🤬
13) valid identifier for export and unset

# RANDOM QUESTIONS
1) Syntax err = 258 or 2 ?

# PROBLEMS
4) --- !!! What happened to '>outfile' !!! ---
1) expansion of $"String $USER hello"
2) export $HOME=USER
3) fucking quote removal ex. "ls"
5) quotes syntax error has to be anticipated ????
