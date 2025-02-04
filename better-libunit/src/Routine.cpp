#include <Routine.hpp>
#include <Test.hpp>
#include <sys/wait.h>
#include <iomanip>
#include <stdlib.h>

namespace Libunit
{
	t_FinalResult	Routine::m_final_res = {0, 0, 0, 0};

	/* -------------------------------------------------------------------------- */
	/*                                   getters                                  */
	/* -------------------------------------------------------------------------- */

	int Routine::GetNbTests()
	{
		return (m_tests.size());
	}

	int Routine::GetNbPassed()
	{
		return (m_passed);
	}

	int Routine::TestsOK()
	{
		return (m_passed == m_tests.size());
	}

	/* -------------------------------------------------------------------------- */

	Routine::Routine(std::string name)
			: m_routine_name{name}
	{
	}

	void Routine::AddNewTest(Test new_test)
	{
		m_tests.push_back(new_test);
	}

	/*
	* @brief Run all tests in the routine
	* @return number of tests passed
	*/
	int Routine::Run()
	{
		size_t	i = 0;
		m_passed = 0;

		std::cout << RESET << "==== " << BOLD << m_routine_name << RESET << " ====" << std::endl;
		while (i < m_tests.size())
		{
			m_passed += m_tests[i].RunTest(this);
			usleep(100 * 1000);
			i++;
		}
		EndRoutine();
		return (m_passed);
	}

	void Routine::Clear()
	{
		m_tests.clear();
	}

	void	Routine::PrintRes(void)
	{
		std::cout << m_routine_name << " result: ";
		std::cout << "[" << m_passed << "/" << m_tests.size() << "]";

		std::cout << std::setfill('.') << std::setw(35 - m_routine_name.size() - 13);

		if (m_passed != m_tests.size())
			std::cout << "[" << RED << "FAILED" << RESET << "]" << std::endl;
		else
			std::cout << "[" << GREEN << "PASSED" << RESET << "]" << std::endl;
		std::cout << RESET << "\n";
	}

	/*
	 * @brief Print the result of the routine
	*/
	void Routine::EndRoutine()
	{
		Routine::m_final_res.total_tests += GetNbTests();
		Routine::m_final_res.tests_passed += GetNbPassed();
		if (TestsOK())
			Routine::m_final_res.routine_passed++;
		Routine::m_final_res.total_routine++;
		PrintRes();
		Clear();
	}

}
