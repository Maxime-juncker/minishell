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
	routine.AddNewTest(Libunit::Test("REDIR", "redir * 4", &mutiple_redir));
	routine.AddNewTest(Libunit::Test("VAR", "expanded var", &expanded_var));
	routine.AddNewTest(Libunit::Test("QUOTE", "single basic", &single_quote_basic));
	routine.AddNewTest(Libunit::Test("QUOTE", "single hard", &single_quote_hard));
	routine.AddNewTest(Libunit::Test("QUOTE", "double basic", &double_quote_basic));
	routine.AddNewTest(Libunit::Test("QUOTE", "double hard", &double_quote_hard));
	routine.AddNewTest(Libunit::Test("LS", "ls_basic", &ls_basic));
	routine.AddNewTest(Libunit::Test("REDIR", "cat < out", &redir_in));
	routine.AddNewTest(Libunit::Test("REDIR", "< out cat", &redir_in_hard));
	routine.AddNewTest(Libunit::Test("REDIR", "echo test | wc > tmp -c", &redir_middle_cmd));
	// ==================================================

	routine.Run();
	return (routine.TestsOK());
}