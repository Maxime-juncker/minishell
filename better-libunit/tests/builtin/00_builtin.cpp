#include "Routine.hpp"
#include "Test.hpp"
#include "builtin.hpp"

int	built_in_routine( void )
{
	Libunit::Routine	routine("built-in");

	/* ================ ADD TESTS HERE ================ */
	routine.AddNewTest(Libunit::Test("ECHO", "echo_basic", &echo_basic));
	routine.AddNewTest(Libunit::Test("ECHO", "echo_mutiple", &echo_multiple));
	routine.AddNewTest(Libunit::Test("ECHO", "echo_no_br", &echo_no_br));
	routine.AddNewTest(Libunit::Test("ECHO", "echo_no_br_multiple", &echo_multiple_no_br));
	// ==================================================

	routine.Run();
	return (routine.TestsOK());
}