#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <string.h>
#include <sys/wait.h>

#include"libunit.hpp"

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
		if (expected.compare((const char *)buffer) == 0)
			return (0);
		//  std::cout << GRAY << "  diff:" << std::endl;
		//  std::cout << "\t" << (const char *)buffer << std::endl;
		//  std::cout << "\t" << expected << RESET << std::endl;
		return (1);
	}

	/// @param filename: the path to the file to open.
	/// @param expected_line: an array of C-strings, each representing the expected content of a line.
	/// @param number_of_line: the number of lines to check.
	int CheckFile(const std::string &filename, const char *expected_line[], const int number_of_line)
	{
		freopen("/dev/tty", "w", stdout);

		std::ifstream infile(filename);
		if (!infile.is_open())
		{
			std::cout << "Error: Unable to open file " << filename << std::endl;
			return 1;
		}

		std::string line;
		// Loop over the expected number of lines
		for (int i = 0; i < number_of_line; ++i)
		{
			// Read a line from the file.
			if (!std::getline(infile, line)) {
				std::cout << "Error: File " << filename << " contains fewer than " << number_of_line << " lines." << std::endl;
				return 1;
			}
			// Compare the read line with the expected line.
			if (line != expected_line[i])
			{
				std::cout << GRAY << "  diff:" << std::endl;
				std::cout << "\t" << "usr:" << line << std::endl;
				std::cout << "\t" << "res:" << expected_line[i] << RESET << std::endl;
				return 1;
			}
		}

		return 0; // All lines matched.
	}
} // namespace Libunit

