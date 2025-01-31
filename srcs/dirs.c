#include "minishell.h"

#include <dirent.h>

int	test()
{
	struct dirent *de = NULL;
	DIR *dirp = opendir(".");

        // for readdir()
while ((de = readdir(dirp)) != NULL){

      //if (Executable){}
      //else if (File){}
      //else if (Directory){}
        printf("%s\n", de->d_name);
        }
}

