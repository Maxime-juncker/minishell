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

	/// @param filename: the path to the file to open.
	/// @param expected_line: an array of C-strings, each representing the expected content of a line.
	/// @param number_of_line: the number of lines to check.
	int CheckFile(const std::string &filename, const char *expected_line[], const int number_of_line)
	{
		std::ifstream infile(filename);
		if (!infile.is_open())
		{
			std::cerr << "Error: Unable to open file " << filename << std::endl;
			return 1;
		}

		std::string line;
		// Loop over the expected number of lines
		for (int i = 0; i < number_of_line; ++i)
		{
			// Read a line from the file.
			if (!std::getline(infile, line)) {
				std::cerr << "Error: File " << filename << " contains fewer than " << number_of_line << " lines." << std::endl;
				return 1;
			}
			// Compare the read line with the expected line.
			if (line != expected_line[i])
			{
				return 1;
			}
		}

		return 0; // All lines matched.
	}
} // namespace Libunit

