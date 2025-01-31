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
	char	buffer[1000];

	t_command_table	table;
	table.env = environ;
	init_table((char*)"cd /bin", table.env, &table, 0);

	cd_command(&table, table.commands[0]);
	getcwd(buffer, 1000);
	std::string line = buffer;

	// Libunit::Redirect_log();
	std::cout << line << std::endl;
	pwd(table.env);
	if (Libunit::Check_output(line) == 0)
		return (0);
	else
		return (1);
}

int	cd_nothing( void )
{
	char	buffer[100];

	t_command_table	table;
	table.env = environ;
	init_table((char*)"cd", table.env, &table, 0);

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

