#pragma once

#include <string>
extern "C"
{
	#include "minishell.h"
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
int	mutiple_redir( void );

// vars
int	expanded_var( void );

// quotes
int	single_quote_basic( void );
int	single_quote_hard( void );
int	double_quote_basic( void );
int	double_quote_hard( void );

// redir
int	redir_in( void );
int redir_after_pipe( void );
int	pipe_after_redir( void );