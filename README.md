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

## Suggestions if you are doing the project 
Here is a list of common suggestions in case you're starting the project. If I had known this before, I would have saved myself some time.
- First thing ever: use BASH! Verify that you are testing the behavior of bash and not other shells like _zsh_ or other stuff. Why? Because they behaves differently. If you want to test something, test this in bash and zsh:
```bash
echo "Hello Bash!?" >file1 >file2 >file3;
cat file1 file2 file3;
```
- Try to really understand each step of bash, having in mind that you have to implement them a bit simplified (for example, no unenclosed quotes). The main steps could be resumed in: creation of an environment, waiting for the user's input, lexing, parsing, expanding, quote removal, execution and so on waiting for the next input. It is a big while loop which never dies and never exits excepts in 2 cases: when you use the built-in `exit` and when you send `EOF` through _control + D_ (check what it makes in the context of bash).
- Once you get the meaning of each step, try to arrange the job with your team mate. This doesn't mean only dividing the steps, but trying to anticipate what each step need from the previous one. For example, the parser will produce an output: what expects the next step? Which kind of structure it needs? Is the output of the parser holding enough information, or while processing the input data, are we losing some importante information? You can repeat this kind of approach for each step. A side note: a lot of people recommend to use an [Abstract Syntax Tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree) to parse the data. After doing it, I could say that it is nice to use it to gain some knowledge about it and it is nice to have in your curriculum, but you don't need it. This is just a personal and questionable opinion. Free to do like you think.
- Test your minishell as soon as possible. You really don't know how much can be done wrong, so it is better to run a tester, to get rid of some structur problems before they get too deep in your code. You can find a lot of valid testers online, made by students of 42. Try them out soon!

## Try it out
```bash

```

## Useful resources
