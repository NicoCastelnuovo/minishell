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

# FARSHAD
1) Signals
3) Check if every file is closed -> update:
	- file are always closed when one or more child is forked,
		but it's not closed when a builtin is executed (because it doesn't go in child function)
	- here_doc in case of single command is not closed and sometimes executes (???)
	- separate pipechain from single cmd execution
4) export -> print in alphabetical order
6) Which is status of syntax error? 258 or 2?
7) What if example the expander makes error in the middle
<!-- 8) export and unset invalid identifier done't work properly -->
<!-- 9) Not sure about env->to_export variable, which told if the variable has to be exported -->
<!-- 11) expot var+=something add omething to the existing variable or creates a new one -->
<!-- 12)	export "" AND unset "" // export "" hello=1 '' world=2 -->

# LEAKS/VALGRIND
<!-- 1) NOT existing commands (not happens in pipechain) -->
2) Valgrind errors in case of expansion AND/OR quote removal

# REALLY TO DO ??
5) Check what happend if type planty new lines with commands or not
10) set $_ not export, modify when a cmd executes, need to do ?
