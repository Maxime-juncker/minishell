#pragma once

#include <string>
extern "C"
{
	#include <minishell.h>
	#include <libft.h>
}
#include "libunit.hpp"

int	commands_routine( void );


// tests
int	ls_basic( void );
int	create_cmd( void );
int	create_redir( void );
int	create_pipe( void );
int	create_mulitple_pipes( void );
int redir_after_pipe( void );
int	pipe_after_redir( void );
int	expanded_var( void );