utestpp
=======

utest++ is a small, simple, procedural unit testing suite with a focus on of use and simple tests. It is not very sophisticated or powerful compared to more featureful testing frameworks, but it has no installation (just one header), and it is very easy with which to get started.

Requirements
=======

utestpp requires C++11 or more recent.

With a few minor tweaks (getting rid of `std::to_string`), it could easily be modified to use C++03.

Usage
=======

Before using any testing functionalities, the book-keeping code must be inserted before the first test and after the last one. If this is not done, there will be no output for testing totals and overall outcome.

    UTESTPP_INIT();
    
    // Tests here
    
    UTESTPP_FINISH();
    
Four testing macros are provided:

`UTESTPP_ASSERT_TRUE` is used to express that something must be truthy.

`UTESTPP_ASSERT_EQUAL` is used to verify equality.

`UTESTPP_ASSERT_THROWS` is used to verify that an exception (any exception) is thrown.

`UTESTPP_ASSERT_THROWS_EXCEPTION` is used to verify that a specific exception (and only that exception) is thrown.

Example
=======

	#include "utestpp.h"

	#include <vector>
	
	int main() {
		UTESTPP_INIT();

		std::vector<int> v;
		
		UTESTPP_ASSERT_TRUE(v.empty());
		
		v.push_back(3);
		v.push_back(3);
		
		UTEST_ASSERT_EQUAL(v[0], v[1]);
		
		UTESTPP_ASSERT_THROWS(v.at(5));
		
		UTESTPP_ASSERT_THROWS_EXCEPTION(v.at(5), std::out_of_range);
		
		return UTESTPP_FINISH();
	}

Short Names
=======

If you don't care about maintaining the `UTESTPP_` psuedo-namespace on the macros, you can define `UTESTPP_SHORT_NAMES` before including `utestpp.h`. In addition to the prefixed names, this defines equivalent macros without the `UTESTPP_` prefix (e.g. `ASSERT_EQUAL`). Note that `UTESTPP_INIT` and `UTESTPP_FINISH` will still have the `UTESTPP_` prefix.

