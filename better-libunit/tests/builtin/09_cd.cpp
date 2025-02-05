#include "builtin.hpp"
#include <dirent.h>

int	cd_relative( void )
{
	char	buffer[100];

	t_command_table	table;
	table.env = environ;
	init_table((char*)"cd ..", table.env, &table, 0);

	cd_command(&table, table.commands[0]);
	getcwd(buffer, 100);
	std::string line = buffer;

	Libunit::Redirect_log();
	pwd(table.env);
	if (Libunit::Check_output(line) == 0)
		return (0);
	else
		return (1);
}

int	cd_absolute( void )
{
	std::string	pwd;

	t_command_table	table;
	table.env = environ;
	init_table((char*)"cd /bin", table.env, &table, 0);

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
	table.env = environ;
	init_table((char*)"cd", table.env, &table, 0);

    run_pipeline(&table);
	pwd = getenv("PWD");
	if (pwd.compare(getenv("HOME")) == 0)
		return (0);
	else
		return (1);
}

