#include "executor.hpp"
#include <Routine.hpp>
#include <Test.hpp>

t_command	example_cmd( void )
{
	t_command	cmd;

	cmd.args = ft_split("ls -l", ' ');
	cmd.n_args = 2;
	cmd.fd_in = 0;
	cmd.fd_out = 1;
	return cmd;
}

int	executor_routine( void )
{
	Libunit::Routine	routine("executor");

	/* ================ ADD TESTS HERE ================ */
	routine.AddNewTest(Libunit::Test("GET_PATH", "basic_test", &test_path));
	routine.AddNewTest(Libunit::Test("GET_PATH", "not found", &not_found));
	// ==================================================

	routine.Run();
	return (routine.TestsOK());
}