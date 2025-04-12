# MINISHELL
> As beautiful as a shell 
 

## About
minishell is an attemps a recreate a smaller version of bash

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
| `\|\|`   | run next command if the previous failed |
| `$var`   |  replace `$var` by it's env variable if it exist|

-- buildin
| operator        | option / args | description      |
| --------------- | ----------------|------------------------------------|
|`echo`|`-n` (remove line break)|print line to stdout |
|`cd`|`~` (go to /home) or `-` (revert last cd)|change the current working directory |
|`pwd` | none | show current working directory |
|`export`| `id=var` or `none` (show export table)| export / override var to the env |
|`unset`|`id` | export env var if it exist|
|`unset`|`id` | export env var if it exist|
|`env`|none | show the environement |
|`exit`| `exit code` or none | exit with `exit code` or the last error code if nothing is given |


