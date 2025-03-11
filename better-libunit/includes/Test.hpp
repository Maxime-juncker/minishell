#pragma once

namespace Libunit
{
	class Routine;

	class Test
	{
	private:
		std::string	m_function_name;
		std::string	m_test_name;
		int			(*f)( void );

	private:
		std::string	CodeToString(int code);
		void		PrintResult(std::string	res);
		int			EndTest(int code);
	public:
		Test(std::string f_name, std::string t_name, int (*f)( void ));
		~Test() {}
		int	RunTest( Routine *caller );
	};
} // namespace Libunit
