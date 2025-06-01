// yarinkash1@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MyContainer.hpp"

using namespace my_cont_ns;

TEST_CASE("dummy test") 
{
    MyContainer container;
    CHECK(true); // This is a dummy test to ensure the test framework works
}