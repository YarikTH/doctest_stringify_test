#include "doctest/doctest.h"
#include "ApprovalTests.hpp"
#include <sstream>

using namespace ApprovalTests;

TEST_CASE("doctest::toString")
{
    std::ostringstream ss;

    ss << "bool: " << doctest::toString( true ) << '\n';

    Approvals::verify(ss.str());
}
