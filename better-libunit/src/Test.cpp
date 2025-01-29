#include <unistd.h>
#include <sys/wait.h>
#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <fcntl.h>
#include <stdio.h>

#include <Test.hpp>
#include <Routine.hpp>

namespace Libunit
{
	/*
	* @brief Convert the code to a string
	* @param code the code to convert
	* @return the string corresponding to the code
	*/
	std::string Test::CodeToString(int code)
	{
		if (WTERMSIG(code) == SIGSEGV)
			return ("SIGSEGV");
		if (WTERMSIG(code) == SIGBUS)
			return ("SIGBUS");
		if (WTERMSIG(code) == SIGABRT)
			return ("SIGABRT");
		if (WTERMSIG(code) == SIGFPE)
			return ("SIGFPE");
		if (WTERMSIG(code) == SIGPIPE)
			return ("SIGPIPE");
		if (WTERMSIG(code) == SIGILL)
			return ("SIGILL");
		if (WEXITSTATUS(code) == 0)
			return ("OK");
		return ("KO");
	}

	/*
	* @brief Print the result of the test
	* @param res the result to print
	*/
	void Test::PrintResult(std::string res)
	{
		std::cout << "[" << GRAY << m_function_name << RESET << "]:";
		std::cout << m_test_name;

		// print dot
		std::cout << std::setfill('.') << std::setw(35 - m_function_name.size() - m_test_name.size() - 2);
		std::cout << std::right;

		if (res == "OK")
			std::cout << "[" << GREEN << res << RESET << "]" << std::endl;
		else if (res == "KO")
			std::cout << "[" << RED << res << RESET << "]" << std::endl;
		else
			std::cout << "[" << B_RED << res << RESET << "]" << std::endl;
	}


	/*
	* @brief End the test
	* @param code the code to end the test
	* @return 1 if the test passed, 0 otherwise
	*/
	int Test::EndTest(int code)
	{
		std::string	code_str;

		code_str = CodeToString(code);
		PrintResult(code_str);
		if (code_str == "OK")
			return (1);
		return (0);
	}

	Test::Test(std::string f_name, std::string t_name, int (*_f)(void))
		: m_function_name{f_name}, m_test_name{t_name}, f{_f}
	{
	}

	/*
	* @brief Run the test
	* @param caller the routine that called the test
	* @return 1 if the test passed, 0 otherwise
	*/
	int Test::RunTest(Routine *caller)
	{
		int	pid;
		int	code;

		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0) // Child process
		{
			caller->Clear();
			code = f();

			exit(code);
		}
		// parent process
		wait(&code);
		return (EndTest(code));
	}
}
