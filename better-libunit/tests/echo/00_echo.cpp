#include "Routine.hpp"
#include "Test.hpp"
#include "echo.hpp"

int	echo_routine( void )
{
	Libunit::Routine	routine("echo");

	/* ================ ADD TESTS HERE ================ */
	routine.AddNewTest(Libunit::Test("ECHO", "echo", &echo_01));
	routine.AddNewTest(Libunit::Test("ECHO", "echo -n", &echo_02));
	routine.AddNewTest(Libunit::Test("ECHO", "echo Test", &echo_03));
	routine.AddNewTest(Libunit::Test("ECHO", "echoHola", &echo_04));
	routine.AddNewTest(Libunit::Test("ECHO", "echo-nHola", &echo_05));
	routine.AddNewTest(Libunit::Test("ECHO", "echo -n test", &echo_07));
	routine.AddNewTest(Libunit::Test("ECHO", "echo \"-n\" Test", &echo_08));
	routine.AddNewTest(Libunit::Test("ECHO", "echo -ntest", &echo_09));
	routine.AddNewTest(Libunit::Test("ECHO", "echo test -n", &echo_10));
	routine.AddNewTest(Libunit::Test("ECHO", "echo test1 test2 test3", &echo_11));
	routine.AddNewTest(Libunit::Test("ECHO", "echo                test", &echo_12));
	routine.AddNewTest(Libunit::Test("ECHO", "echo test1     test2    test3", &echo_13));
//	routine.AddNewTest(Libunit::Test("ECHO", "echo    \\n test", &echo_14));
	routine.AddNewTest(Libunit::Test("ECHO", "echo \"         \" | cat -e", &echo_15));
	routine.AddNewTest(Libunit::Test("ECHO", "echo           | cat -e", &echo_16));
	routine.AddNewTest(Libunit::Test("ECHO", "\"\"\'\'echo hola\"\"\'\'\'\' que\"\"\'\' tal\"\"\'\'", &echo_17));
	routine.AddNewTest(Libunit::Test("ECHO", "echo -n -n", &echo_18));
	routine.AddNewTest(Libunit::Test("ECHO", "echo -n -n test oui", &echo_19));
	routine.AddNewTest(Libunit::Test("ECHO", "echo -p", &echo_20));
	routine.AddNewTest(Libunit::Test("ECHO", "echo -nnnnnnnn", &echo_21));
	routine.AddNewTest(Libunit::Test("ECHO", "echo -nnnn -n -nnnn", &echo_22));
	routine.AddNewTest(Libunit::Test("ECHO", "echo -nnnn-n -nnnn", &echo_23));
	routine.AddNewTest(Libunit::Test("ECHO", "echo -n -nnn test -n -nnnn", &echo_24));
	routine.AddNewTest(Libunit::Test("ECHO", "echo -n -nnn-nnnn", &echo_25));
	routine.AddNewTest(Libunit::Test("ECHO", "echo -----n", &echo_26));
	routine.AddNewTest(Libunit::Test("ECHO", "echo -nnn -----n", &echo_27));
	routine.AddNewTest(Libunit::Test("ECHO", "echo -nnn -----nn---nnnn", &echo_28));
	routine.AddNewTest(Libunit::Test("ECHO", "echo $", &echo_29));
	routine.AddNewTest(Libunit::Test("ECHO", "echo $?", &echo_30));
	routine.AddNewTest(Libunit::Test("ECHO", "echo $?$", &echo_31));
	routine.AddNewTest(Libunit::Test("ECHO", "echo $? | echo $? | echo $?", &echo_32));
	routine.AddNewTest(Libunit::Test("ECHO", "echo $:$= | cat -e", &echo_33));
	routine.AddNewTest(Libunit::Test("ECHO", "echo \" $ \" | cat -e", &echo_34));
	routine.AddNewTest(Libunit::Test("ECHO", "echo \' $ \' | cat -e", &echo_35));
//	routine.AddNewTest(Libunit::Test("ECHO", "echo $DESKTOP_SESSION", &echo_36));
//	routine.AddNewTest(Libunit::Test("ECHO", "echo \\$DESKTOP_SESSION", &echo_37));

	// ==================================================

	routine.Run();
	return (routine.TestsOK());
}