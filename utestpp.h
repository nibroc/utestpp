namespace utestpp {

inline void test_assert(bool cond, const std::string& msg, const std::string& file, const std::string& func, int line)
{
	if (!cond) {
		if (msg.empty()) {
			throw std::runtime_error("Failed test in "
									+ file + " in " + func 
									+ " on line " + std::to_string(line));
		} else {
			throw std::runtime_error("Failed test: " + msg + ". " 
									+ file + " in " + func 
									+ " on line " + std::to_string(line));
		}
	}
}

inline void throw_fail(const std::string& msg, const std::string& file, const std::string& func, int line)
{
	test_assert(false, msg, file, func, line);
}

}

#define ASSERT_TRUE_MSG(cond, msg) utestpp::test_assert(cond, msg, __FILE__, __func__, __LINE__)
#define ASSERT_EQUAL_MSG(x, y, msg) ASSERT_TRUE_MSG(x == y, msg)

#define ASSERT_TRUE(cond) ASSERT_TRUE_MSG(cond, "")
#define ASSERT_EQUAL(x, y) ASSERT_EQUAL_MSG(x, y, "")

#define ASSERT_THROWS_HELPER(expr, msg, file, func, line) \
	do {\
		bool threw = false;\
		try {\
			expr;\
		} catch (...) { threw = true; }\
		utestpp::test_assert(threw, msg, file, func, line);\
	} while (0)
#define ASSERT_THROWS_MSG(expr, msg) ASSERT_THROWS_HELPER(expr, msg, __FILE__, __func__, __LINE__)
#define ASSERT_THROWS(expr) ASSERT_THROWS_MSG(expr, "")



