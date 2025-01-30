#include "Routine.hpp"
#include "Test.hpp"
#include "commands.hpp"

int	commands_routine( void )
{
	Libunit::Routine	routine("commands");

	/* ================ ADD TESTS HERE ================ */
	routine.AddNewTest(Libunit::Test("CMD", "cmd_basic", &create_cmd));
	routine.AddNewTest(Libunit::Test("CMD", "redirection", &create_redir));
	routine.AddNewTest(Libunit::Test("PIPE", "pipe", &create_pipe));
	routine.AddNewTest(Libunit::Test("PIPE", "mutiple pipes", &create_mulitple_pipes));
	routine.AddNewTest(Libunit::Test("PIPE", "pipes -> redir", &redir_after_pipe));
	routine.AddNewTest(Libunit::Test("PIPE", "redir -> pipe", &pipe_after_redir));
	routine.AddNewTest(Libunit::Test("VAR", "expanded var", &expanded_var));
	routine.AddNewTest(Libunit::Test("LS", "ls_basic", &ls_basic));
	// ==================================================

	routine.Run();
	return (routine.TestsOK());
}