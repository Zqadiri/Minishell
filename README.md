# Minishell
The objective of this project is for you to create a simple shell. Yes, your
own little bash or zsh. You will learn a lot about processes and file descriptors.

## Overview :

[Tutorial - Write a Shell in C - Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/)

[Want to build a simple shell? Here's how you do it.](https://nickolasteixeira.medium.com/want-to-build-a-simple-shell-heres-how-you-do-it-75890647bae8)

## What is a shell?

The shell is a command line interface (CLI) program that takes commands from the keyboard and gives them to the operating system to perform.

## Man for the External functions :

`fork`  

creates a new process by duplicating the calling process. The new process is referred to as the child process. The calling process is referred to as the parent process. After a new child process is created, both processes will execute the next instruction following the fork() system call. A child process uses the same pc(program counter), same CPU registers, same open files which use in the parent process.

It takes no parameters and returns an integer value. Below are different values returned by fork().

***Negative Value***: the creation of a child process was unsuccessful. ***Zero***: Returned to the newly created child process.***Positive value***: Returned to parent or caller. The value contains the process ID of the newly created child process.

[Fork() system call tutorial](https://www.youtube.com/watch?v=xVSPv-9x3gk)

`wait` 

A call to wait() blocks the calling process until one of its child processes exits or a signal is received. After the child process terminates, the parent continues its execution after wait system call instruction.

We know if more than one child processes are terminated, then wait() reaps any arbitrarily child process but if we want to reap any specific child process, we use `waitpid` function.

`wait3`     `wait4`

The wait3() and wait4() system calls are similar to `waitpid`(2), but additionally, return resource usage information about the child in the structure pointed to by rusage.

The difference is  wait3() waits of any child, while wait4() can be used to select a specific child, or children, on which to wait.

`signal`

A signal is a software generated interrupt that is sent to a process by the OS because of when the user press ctrl-c or another process tells something to this process. There are fixed set of signals that can be sent to a process. signal are identified by integers.

```cpp
#include<stdio.h>
#include<signal.h>
**int** main()
{
	**signal**(SIGINT, handle_sigint);
	while(1)
	{
		**printf**(“hello world\n”);
		sleep(1);
	}
	return 0;
}
```

Output: Print hello world infinite times. If user presses ctrl-c to terminate the process because of SIGINT signal sent and its default handler to terminate the process.

`dup` `dup2`

[https://www.youtube.com/watch?v=EqndHT606Tw](https://www.youtube.com/watch?v=EqndHT606Tw)

`pipe`

Conceptually, a pipe is a connection between two processes, such that the standard output from one process becomes the standard input of the other process.

[Pipe() tutorial for linux](https://www.youtube.com/watch?v=uHH7nHkgZ4w)

- Enclosing characters in single quotes (‘’’) preserves the literal value of each character within the quotes. A single quote may not occur between single quotes, even when preceded by a backslash.
- Enclosing characters in double quotes (‘"’) preserves the literal value of all characters withinthe quotes, with the exception of ‘$’, ‘‘’, ‘\’ .  The characters ‘$’ and ‘‘’ retain their special meaning within double quotes.The backslash retains its special meaning only when followed by one of the following characters: ‘$’, ‘‘’, ‘"’, ‘\’, or newline. Within double quotes, backslashes that are followed by one of these characters are removed