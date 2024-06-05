# 42-minishell

42 Heilbronn school project about the re-implementation of a mini version of Bash.

## Keywords
C programming - bash - shell - process - fork - pipe - signal handling

## Subject
In this team-based project we had to rewrite a mini-version of _bash_. The program has to replicate some features of the shell, including redirection, piping, signal handling, exit codes, use of an internal environment and more. No memory leaks are allowed, along with forbidden functions like `realloc()`, and most important thing: for any reason, minishell has not to crash, otherwise the project would be failed. For more info check out the original [subject](./en.subject.pdf) of the school.

## Brief explanation
The project covers the following topics:

### 1. Bash knowledge
To build it, you have to know it. Understanding the steps performed by bash once it recieves an input, is fundamental to make a clean structure with less surprises as possible. Doing a mistake on the structure could force the developer to restructure the whole project.

### 2. Data structures
The structures implemented to hold the data is very important to give consistency to the program. Using a weak data structure could result, like mentioned in the previous point, in re-doing big part of the project. Since the project is in C, there are no containers like in C++ or classes which we could use to well-organize the data, therefore multiple `struct` were used.

### 3. Fork, pipe and wait
Like bash, we had to implement the fork of new child processes, and the pipe to make them communicate with each others. We also need make the main parent process, wait for the children and, as well as bash does, store the exit code of the last one. Don't let the children process to become [orphans or zombies](https://stackoverflow.com/questions/20688982/zombie-process-vs-orphan-process)!

### 4. Leaks free
Like in any other project of 42, the memory allocated by has to be properly freed. No leaks are tolerated during evaluation. In this project we used [valgrind](https://valgrind.org/) to check memory laks and memory inconsistences.

---

## Our approach
By reading [minishell.c](./src/minishell.c) file, you'll notice that we decide to divide a much as possible the performed steps: lexing, parsing, expansion, quote removal and execution. We divided the job, and we tried to communicate as much as possible so that each step had to expect the data from the previous in a certain structure, but obviously this was the first big project at 42 and we made some mistakes, but hey, from mistakes we learn!

The decision of the data structures was a key point of the whole project. The main problem was how organize the data in the various steps:
- **Environment**. The first mistake we did, was to not have a clear idea on what we had to do exactly with the environment. The first approach was to use double-linked lists to hold the data, but at the end they were too much. We didn't need so much complexity to organize the environment variables, so we changed to plain linked list, which we also easier to handle in terms of removing a node and modifying its content.
- **Lexer**. After taking the input from the user, the string is reduced to minimum lexing parts (the tokens), which are organized together in some kind of structure. A potential problem could be to divide the string too much and losing some important information, like spaces between arguments or quoted part of string. So we realized that more information is better, also when maybe we would't have to use them.
- **Parser and so on**. After lexing, we had to give a meaning to the tokens and, as already said, we had to pay attention to don't lose any important information. We decided to organize the data in a syntax tree, in which each node was either a pipe or a table holding the arguments and _ALL_ the redirections.

After the data structure organization we had to understand how exactly the expansion and the quote removal actually work in Bash, so that we could expand the variables of our environment correctly. One tricky point of this step was to know too late about the [locale-specific translation](https://www.gnu.org/software/bash/manual/bash.html#Locale-Translation), which made us to refactor the code multiple times.

Once the data is ready, it had to be sent to the executor. We had to re-implement some builtin commands (_cd, echo, exit, env, pwd, unset, export_) and we had to implement the pipechain. Understanding on how do it correctly was also an important part of the project, along with how `fork()` works, with parent, child, zombie processes and wait of exit codes.

The executor had also to handle the one or multiple redirection. That said, the main behavior is that if we have multiple redirection, each of them has to be performed, so that in case od error, the pipechain is not executed anymore. So given this example:
```bash
echo "Hello World" > infile-1;
< infile-1 < infile-2 cat -e > outfile-1 > outfile-2; #bash: infile-2: No such file or directory
```
Bash tries to take input from _infile-1_, then tries from _infile-2_. If one of these two doesn't exist, the error _No such file or directory_ is thrown, and nothing else is executed. If the two files exist, bash will only take the input from the last one _infile-2_. Regarding the redirection of the output, it will be redirected only to the last one, but if an output file has not write permissions, bash will return an error and nothing more is executed:
```bash
echo "Hello World" > infile-1;
touch outfile-not-writable;
chmod 444 outfile-not-writable; # sets only read permissions
< infile-1 cat -e >outfile-not-writable >outfile-2; #bash: outfile-not-writable: Permission denied
```
That said, since we have to replicate Bash, every redirection has to be performed to get the same behavior and results.

As last step of the whole project, we did the signal handling as request by the subject.

## If you are going to start the project
Here is a list of suggestions in case you're starting the project at 42. If I had known this before, I would have saved myself some time.
- First thing ever: use BASH! Verify that you are testing the behavior of bash and not other shells like _zsh_ or other stuff. Why? Because they behaves differently. If you want to test something, test this in bash and zsh:
```bash
echo "Hello Bash!?" >file1 >file2 >file3;
cat file1 file2 file3;
```
- Try to really understand each step of bash, having in mind that you have to implement them a bit simplified (for example, unenclosed quotes has not to handled, therefore decide what to do, throw an error or what you prefer). The main steps could be resumed in: creation of an environment, waiting for the user's input, lexing, parsing, expanding, quote removal, execution and so on waiting for the next input. It is a big while loop which never dies and never exits excepts in **only 2 cases**: when you use the built-in `exit` and when you send `EOF` through _control+D_ (check what it makes in the context of bash).
- Once you get the meaning of each step, try to arrange the job with your team mate. This doesn't only mean assignation of each step to me and you, but trying to anticipate what each step needs from the previous one. For example, the parser will produce an output: what expects the next step? Which kind of structure it needs? Is the output of the parser holding enough information, or while processing the input data, are we losing some importante information? You can repeat this kind of approach for each step. A side note: I heard a lot of people recommend to use an [Abstract Syntax Tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree) to parse the data. After doing it, I could say that it is nice to use it to gain some knowledge about it and it is nice to have in your curriculum, but you don't need it. This is just a personal and questionable opinion. Feel free to do what you think.
- Environment. Your minishell has not to crash. Since a user could potentially remove all the environment variables, try to prevent any crash related to the initialization of an empty environment, or the deletion of every environment variable.
- Test your minishell as soon as possible. You really don't know how much can be done wrong, so it is better to run a tester, to get rid of some structur problems before they get too deep in your code. You can find a lot of valid testers online, made by 42 students. Try them out soon!

## Try it out
```bash

```

## Useful resources
- https://www.gnu.org/software/bash/manual/html_node/index.html and https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html are the official Shell and Bash documentations. Sometimes it's hard to read them, but sometimes are more clear then a thousand of other tutorials.
- https://mywiki.wooledge.org/BashParser explains the steps performed by the parser.
- https://www.codequoi.com/en/pipe-an-inter-process-communication-method/ pipes really well explained.
- https://www.explainshell.com if you need to know the meaning of a certain command and its flags.
