#pragma once

#include <string>
extern "C"
{
	#include <minishell.h>
	#include <libft.h>
}

int	executor_routine( void );
t_command	example_cmd( void );


// tests:
int	test_path( void );
int null_path( void );
int	not_found( void );


