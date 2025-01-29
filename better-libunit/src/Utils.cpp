// #include "Routine.hpp"


// namespace Libunit
// {
// 	void PrintFinalRes(void)
// 	{
// 		std::cout << "==== " << BOLD << "FINAL RESULT" << RESET << " ====" << std::endl;
// 		std::cout << "Total tests: " << Routine::m_final_res.total_tests << std::endl;
// 		std::cout << "Tests passed: " << Routine::m_final_res.tests_passed << std::endl;
// 		std::cout << "Routines passed: " << Routine::m_final_res.routine_passed << std::endl;
// 		std::cout << "Total routines: " << Routine::m_final_res.total_routine << std::endl;
// 		std::cout << std::endl;
// 	}
// } // namespace Libunit

// namespace Libunit
// {
// 	void	Redirect_out
// } // namespace Libunit

#include <stdio.h>
#include <string>
#include <fstream>

namespace Libunit
{
	void	Redirect_log(void)
	{
		freopen("log.txt", "w", stdout);
		freopen("log.txt", "w", stderr);
	}

	int Check_output(std::string expected)
	{

		std::string line;
		std::ifstream file("filename.txt");
		getline(file, line);

		return (line == expected);
	}

	// void	Check_output(void)
	// {
	// 	freopen("/dev/tty", "w", stdout);
	// 	freopen("/dev/tty", "w", stderr);
	// }
} // namespace Libunit

