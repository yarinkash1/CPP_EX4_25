// yarinkash1@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MyContainer.hpp"

using namespace my_cont_ns;

TEST_CASE("Constructor test")
{
    MyContainer<> container; // Default int type
    CHECK(container.size() == 0);
    CHECK(container.isEmpty() == true);
}

TEST_CASE("Add function test")
{
    MyContainer<int> container;

    // Test adding single element
    container.add(10);
    CHECK(container.size() == 1);
    CHECK(container.isEmpty() == false);

    // Test adding multiple elements
    container.add(20);
    container.add(30);
    CHECK(container.size() == 3);

    // Test adding duplicate elements
    container.add(10);
    CHECK(container.size() == 4);
}

TEST_CASE("Size function test")
{
    MyContainer<> container;

    // Empty container
    CHECK(container.size() == 0);

    // Add elements and check size
    container.add(1);
    CHECK(container.size() == 1);

    container.add(2);
    container.add(3);
    CHECK(container.size() == 3);
}

TEST_CASE("isEmpty function test")
{
    MyContainer<> container;

    // Initially empty
    CHECK(container.isEmpty() == true);

    // After adding element
    container.add(42);
    CHECK(container.isEmpty() == false);

    // After removing element
    container.remove(42);
    CHECK(container.isEmpty() == true);
}

TEST_CASE("Remove function test - valid element")
{
    MyContainer<int> container;

    // Add elements
    container.add(10);
    container.add(20);
    container.add(30);
    CHECK(container.size() == 3);

    // Remove existing element
    container.remove(20);
    CHECK(container.size() == 2);
}

TEST_CASE("Remove function test - multiple occurrences")
{
    MyContainer<int> container;

    // Add elements with duplicates
    container.add(5);
    container.add(10);
    container.add(5); // duplicate
    container.add(15);
    container.add(5); // another duplicate
    CHECK(container.size() == 5);

    // Remove element that appears multiple times
    container.remove(5);
    CHECK(container.size() == 2); // Should remove all 3 occurrences of 5
}

TEST_CASE("Remove function test - non-existent element")
{
    MyContainer<int> container;
    container.add(10);
    container.add(20);

    // Try to remove element that doesn't exist
    CHECK_THROWS_AS(container.remove(123), std::invalid_argument);

    // Size should remain unchanged
    CHECK(container.size() == 2);
}

TEST_CASE("Remove function test - empty container")
{
    MyContainer<int> container;

    // Try to remove from empty container
    CHECK_THROWS_AS(container.remove(10), std::invalid_argument);
}

TEST_CASE("Template functionality test - string type")
{
    MyContainer<std::string> stringContainer;

    // Test with strings
    stringContainer.add("Hello");
    stringContainer.add("World");
    stringContainer.add("C++");
    CHECK(stringContainer.size() == 3);
    CHECK(stringContainer.isEmpty() == false);

    // Remove string
    stringContainer.remove("World");
    CHECK(stringContainer.size() == 2);

    // Try to remove non-existent string
    CHECK_THROWS_AS(stringContainer.remove("Python"), std::invalid_argument);

    // Remove string
    stringContainer.remove("C++");
    CHECK(stringContainer.size() == 1);

    // Remove string
    stringContainer.remove("Hello");
    CHECK(stringContainer.size() == 0);
    CHECK(stringContainer.isEmpty() == true);
}

TEST_CASE("Template functionality test - double type")
{
    MyContainer<double> doubleContainer;

    // Test with doubles
    doubleContainer.add(3.14);
    doubleContainer.add(14.53);
    doubleContainer.add(6.9);
    CHECK(doubleContainer.size() == 3);

    // Remove double
    doubleContainer.remove(3.14);
    CHECK(doubleContainer.size() == 2);
}