# MINISHELL
> As beautiful as a shell 
 

## About
minishell is an attemps at recreating a smaller version of bash

## Features

-- operators
| operator        | description                                         |
| --------------- | ----------------------------------------------------|
| `>`   | write output to file (file created if needed) |
| `>>`   | append output to file (file created if needed) |
| `<`   | redirect file to input |
| ` << 'delemiter' `   | create a new heredoc |
| `\|`   | create pipe |
| `&&`   | run next command if the previous succeed |
| `(` `)`   | for commands priorities |
| `\|\|`   | run next command if the previous failed |
| `$var`   |  replace `$var` by it's env variable if it exist|
| `*`   |  wildcard, will be replace by every file conforming to the patern|
| `$?`   | will be replace by the last error code |


-- buildin
| command        | option / args | description      |
| --------------- | ----------------|------------------------------------|
|`echo`|`-n` (remove line break)|print line to stdout |
|`cd`|`~` (go to /home) or `-` (revert last cd)|change the current working directory |
|`pwd` | none | show current working directory |
|`export`| `id=var` or `none` (show export table)| export / override var to the env |
|`unset`|`id` | export env var if it exist|
|`env`|none | show the environement |
|`exit`| `exit code` or none | exit with `exit code` or the last error code if nothing is given |

-- signals
| signal        | effect  |
| --------------- | ---------------------------------------------------|
| `ctrl-c` | stop the command and display new prompt |
| `ctrl-d` | close the stdin (if waiting for cmd shell will close) |
| `ctrl-\` | stop process (do nothing if shell waiting for cmd)  |

## Run it yourself
install dependencies: readline
```
sudo apt-get install libreadline6 libreadline6-dev
```


clone the repo
```
git clone https://github.com/Maxime-juncker/minishell.git minishell
cd minishell
```
then build it using make
```
make
```

finally run the shell
```
./minishell
```

## How does it work
1. lexer: format the user prompt for easier parsing and replace `$var` / `*` 
2. checker: check if the prompt syntax is correct
3. parser: return a command table that will be given to the command pipeline, every file / pipe is open here
4. pipeline: will create every child process to run command (if it exist) et manage std out / in redirection
\
\
[![Project-20250412054030.jpg](https://i.postimg.cc/Qd32MdgJ/Project-20250412054030.jpg)](https://postimg.cc/tYBSSyMs)
## Contributors
[@abidolet](https://github.com/Alexis42lyon)

[@mjuncker](https://github.com/Maxime-juncker)

## Resources used 
[code_quoi](https://www.codequoi.com/categories/c/)

[Introduction to Systems Programming](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
