#pragma once

#include <vector>
#include <string>
#include "libunit.hpp"

namespace Libunit
{
	class Test;

	class Routine
	{
	private:

		std::string 		m_routine_name = "default";
		std::vector<Test>	m_tests;
		size_t 				m_passed;

	public:
		static 				t_FinalResult	m_final_res;
		Routine(std::string name);
		~Routine() {}

		void			AddNewTest(Test new_test);
		int				Run();
		void			Clear();
		void 			PrintRes(void);

		int				GetNbTests();
		int				GetNbPassed();
		int				TestsOK();
		t_FinalResult	GetFinalRes() const { return m_final_res; }

	private:
		void	EndRoutine();
	};
} // namespace Libunit
