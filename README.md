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
	- blank line
	- write a line without pressing 'return' and ctrl-c
	- single/multiple here_doc
	- single cmd cat/top/sleep
	- pipechain
2) Check if every file is closed -> update:
	- file are always closed when one or more child is forked,
		but it's not closed when a builtin is executed (because it doesn't go in child function)
	- here_doc in case of single command is not closed and sometimes executes (???)
	- separate pipechain from single cmd execution
3) export -> print in alphabetical order
4) What if example the expander makes error in the middle
5) Problem with odd number of $$$
6) Valgrind errors in case of expansion AND/OR quote removal
7) Check what happend if type planty new lines with commands or not
8) set $_ not export, modify when a cmd executes, need to do ?
9) What happens if something in the middle fails (like the expansion)? e_code cannot be set because it's smoething different

10) executor -> resolve_args need to returns -1 for err

## CHECK
1) /bin/echo 1 >/dev/null | /usr/bin/grep 1
2) "."
3) .ls different err msg ; /bin/cats
4) ""

## TESTS TO DO
1) scmds after correcting point 3 and 4
2) variables
3) correction
4) go_wild


_____________________________________________________________________


## TO Farshad...
1) Go in here_doc/here_doc and comment/uncomment the whole block of new/old version
2) basically what happens is:
	- example. <<eof <<hello | <<world | <<shit
	- I collect in char **eofs every eof ---> eof - hello - world - shit - (null)
	- I open/close the tmp files, storing their name in cmd->redir->f_name (I need them in the parent to unlink() otherwise is not possible to delete the files)
	- I fork a child which performs ALL the here_docs, in which i can use ctrl-c to interrupt
3) Problems:
	- double prompt is displayed, why!?
4) Why i did so:
	- Doing in the child was tooo much

## HOW I SOLVED problem (3)
First, which was the problem ????
Apparently readline() handles signals and there is an overlapping between signals.
Basically there are TWO handlers:
	- ONE BEFORE readline - the normal one which handles the new line
	- ONE RIGHT AFTER it - same but NO rl_redisplay()
