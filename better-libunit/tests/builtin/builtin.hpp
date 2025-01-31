#pragma once

#include <string>
extern "C"
{
	#include <minishell.h>
	#include <libft.h>
}
#include "libunit.hpp"

// routine
int	built_in_routine( void );

// echo tests
int	echo_basic( void );
int	echo_multiple( void );
int	echo_no_br( void );
int	echo_multiple_no_br( void );

// env tests
int	env_test( void );
int	export_test( void );
int	unset_test( void );

// directories tests
int	pwd_test( void );