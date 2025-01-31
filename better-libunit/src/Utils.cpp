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
#include <iostream>
#include <string.h>
#include <sys/wait.h>

#include <fcntl.h>

namespace Libunit
{
	void	Redirect_log(void)
	{
		freopen("log.txt", "w", stdout);
		freopen("log.txt", "w", stderr);
	}

	int Check_output(std::string expected)
	{
		char *buffer[1000] = {0};
		int		fd;

		freopen("/dev/tty", "w", stdout);

		fd = open("log.txt", O_RDONLY, 0777);
		if (fd == -1)
			std::cerr << "cant read file" << std::endl;
		read(fd, buffer, expected.length());
		close(fd);
		// std::cout << expected.compare((const char *)buffer) << std::endl;
		// std::cout << buffer << std::endl;
		// std::cout << expected << std::endl;
		return (expected.compare((const char *)buffer));
	}

} // namespace Libunit

