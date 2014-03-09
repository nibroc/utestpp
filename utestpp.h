#include <iostream>
#include <stdexcept>
#include <string>

namespace utestpp {
	
	static int NUM_TESTS;
	static int NUM_FAIL;
	static int NUM_PASS;
	
	inline void init()
	{ }
	
	inline bool test_assert(bool cond, const std::string& expr, const std::string& file, 
							const std::string& func, int line)
	{
		++NUM_TESTS;
		if (cond) {
			std::cout << "PASS: " << func << " in " << file
					  << " (" << std::to_string(line) << ")"
					  << " cond was true: " << expr << std::endl;
			++NUM_PASS;
		} else {
			std::cerr << "FAIL: " << func << " in " << file
					  << " (" << std::to_string(line) << ")"
					  << " cond was false: " << expr << std::endl;
			++NUM_FAIL;
		}
		return cond;
	}

	inline bool test_throws_exception(bool threw, const std::string& expr, const std::string& exception_type, 
									  const std::string& file, const std::string& func, int line)
	{
		++NUM_TESTS;
		if (threw) {
			++NUM_PASS;
			std::cout << "PASS: " << func << " in " << file
					  << " (" << std::to_string(line) << ")"
					  << " threw [" << exception_type
					  << "]. Expression: " << expr << "." 
					  << std::endl;
		} else {
			++NUM_FAIL;
			std::cerr << "FAIL: " << func << " in " << file
					  << " (" << std::to_string(line) << ")"
					  << " did not throw " << exception_type
					  << ". (" + expr + ")" 
					  << std::endl;
		}
		return threw;
	}
	
	inline int finish()
	{
		if (NUM_FAIL > 0) {
			std::cout << "FAILURE -- ";
		} else {
			std::cout << "SUCCESS -- ";
		}
		std::cout << "Of " << NUM_TESTS << " tests, " 
				  << NUM_PASS << " passed and " 
				  << NUM_FAIL << " failed." << std::endl;
		return (NUM_FAIL == 0);
	}

}

#define UTESTPP_INIT() utestpp::init();
#define UTESTPP_FINISH() utestpp::finish();

#define UTESTPP_ASSERT_TRUE(cond) utestpp::test_assert(cond, #cond, __FILE__, __func__, __LINE__)
#define UTESTPP_ASSERT_EQUAL(x, y) UTESTPP_ASSERT_TRUE(x == y)

#define UTESTPP_ASSERT_THROWS_EXCEPTION_HELPER(expr, type) \
	do {\
		bool threw = false;\
		try {\
			expr;\
		} catch (type) { threw = true; }\
		utestpp::test_throws_exception(threw, #expr, #type, __FILE__, __func__, __LINE__);\
	} while (0)

#define UTESTPP_ASSERT_THROWS_EXCEPTION(expr, type) UTESTPP_ASSERT_THROWS_EXCEPTION_HELPER(expr, type)

#define UTESTPP_ASSERT_THROWS(expr) UTESTPP_ASSERT_THROWS_EXCEPTION_HELPER(expr, ...)

#ifdef UTESTPP_SHORT_NAMES
#error "Short names are not yet implemented"
#endif
