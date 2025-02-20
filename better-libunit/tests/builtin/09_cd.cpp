#include "builtin.hpp"
#include <dirent.h>


int	cd_relative( void )
{
	return 0;

	char	buffer[100];

	t_command_table	table;
		table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);;
	init_table(ft_strdup("cd .."), &table);

	getcwd(buffer, 100);
	std::string line = buffer;

	Libunit::Redirect_log();
	run_pipeline(&table);
	pwd();
	if (Libunit::Check_output(line) == 0)
		return (0);
	else
		return (1);
}

int	cd_absolute( void )
{
	return 0;

	std::string	pwd;

	t_command_table	table;
		table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);;
	init_table((char*)"cd /bin", &table);

    run_pipeline(&table);
	pwd = getenv("PWD");
	if (pwd.compare("/usr/bin") == 0)
		return (0);
	else
		return (1);
}

int	cd_nothing( void )
{
	std::string	pwd;

	t_command_table	table;
		table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);;
	init_table((char*)"cd", &table);

    run_pipeline(&table);
	pwd = getenv("PWD");
	if (pwd.compare(getenv("HOME")) == 0)
		return (0);
	else
		return (1);
}

