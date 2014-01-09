#include <stdexcept>
#include <string>

namespace utestpp {

	class test_failed : public std::runtime_error 
	{
	public:
		explicit test_failed(const char* what_arg) : std::runtime_error(what_arg)
		{ }
		
		explicit test_failed(std::string what) : std::runtime_error(what)
		{ }
	};
	
	inline void test_assert(bool cond, const std::string& file, const std::string& func, int line)
	{
		if (!cond) {
			throw test_failed("Failed test in "
									+ file + " in " + func 
									+ " on line " + std::to_string(line));

		}
	}

	inline void test_throws_exception(bool threw, const char* expr, const char* exception_type, 
									  const char* file, const char* func, int line)
	{
		if (!threw) {
			throw test_failed(std::string("FAILED: ") + func + " in " + file + 
									 " (" + std::to_string(line) + ") " +
									 " did not throw " + exception_type + 
									 ". (" + expr + ")");
		}
	}

}

#define ASSERT_TRUE(cond) utestpp::test_assert(cond, __FILE__, __func__, __LINE__)
#define ASSERT_EQUAL(x, y) ASSERT_TRUE(x == y)

#define ASSERT_THROWS_EXCEPTION_HELPER(expr, type) \
	do {\
		bool threw = false;\
		try {\
			expr;\
		} catch (type) { threw = true; }\
		utestpp::test_throws_exception(threw, #expr, #type, __FILE__, __func__, __LINE__);\
	} while (0)

#define ASSERT_THROWS_EXCEPTION(expr, type) ASSERT_THROWS_EXCEPTION_HELPER(expr, type)

#define ASSERT_THROWS(expr) ASSERT_THROWS_EXCEPTION_HELPER(expr, ...)
