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
	routine.AddNewTest(Libunit::Test("ENV", "printing", &env_test));
	routine.AddNewTest(Libunit::Test("EXPORT", "basic", &export_test));
	routine.AddNewTest(Libunit::Test("UNSET", "basic", &unset_test));
	routine.AddNewTest(Libunit::Test("DIR", "pwd", &pwd_test));
	routine.AddNewTest(Libunit::Test("DIR", "cd rel", &cd_relative));
	routine.AddNewTest(Libunit::Test("DIR", "cd abs", &cd_absolute));
	routine.AddNewTest(Libunit::Test("DIR", "cd null", &cd_nothing));
	// ==================================================

	routine.Run();
	return (routine.TestsOK());
}