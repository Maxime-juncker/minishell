#include <stdio.h>
#include <wait.h>
#include <unistd.h>

int	main( void )
{
	while (1)
	{
		printf("I'm still alive\n");
		usleep(100 * 1000);
	}
}
