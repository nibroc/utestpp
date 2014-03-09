#include "utestpp.h"

#include <stdexcept>
#include <vector>

int main() {
    UTESTPP_INIT();

    std::vector<int> v;

    UTESTPP_ASSERT_TRUE(v.empty());

    v.push_back(3);
    v.push_back(3);
    
    UTESTPP_ASSERT_EQUAL(v.size(), 2);

    UTESTPP_ASSERT_EQUAL(v[0], v[1]);

    UTESTPP_ASSERT_THROWS(v.at(5));

    UTESTPP_ASSERT_THROWS_EXCEPTION(v.at(5), std::out_of_range);

    return UTESTPP_FINISH();
}
