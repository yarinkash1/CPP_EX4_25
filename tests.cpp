// yarinkash1@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MyContainer.hpp"

using namespace my_cont_ns;

// ==Test cases for MyContainer class==

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

// == Test cases for iterators ==

TEST_CASE("AscendingOrder iterator - basic functionality") 
{
    MyContainer<int> container;
    
    // Add elements in random order
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);
    
    // Get ascending order iterator
    auto ascending = container.getAscendingOrder();
    auto it = ascending.begin();
    auto end_it = ascending.end();
    
    // Test iterator traversal
    CHECK(it != end_it);
    CHECK(*it == 1);  // First element should be smallest
    
    ++it;
    CHECK(*it == 2);
    
    ++it;
    CHECK(*it == 6);
    
    ++it;
    CHECK(*it == 7);
    
    ++it;
    CHECK(*it == 15);  // Last element should be largest
    
    ++it;
    CHECK(it == end_it);  // Should reach end
}

TEST_CASE("AscendingOrder iterator - for loop") 
{
    MyContainer<int> container;
    container.add(30);
    container.add(10);
    container.add(20);
    container.add(5);
    
    auto ascending = container.getAscendingOrder();
    std::vector<int> result;
    
    // Collect elements using for loop
    for (auto it = ascending.begin(); it != ascending.end(); ++it) 
    {
        result.push_back(*it);
    }
    
    // Should be in ascending order
    std::vector<int> expected = {5, 10, 20, 30};
    CHECK(result == expected);
}

TEST_CASE("AscendingOrder iterator - with duplicates") 
{
    MyContainer<int> container;
    container.add(5);
    container.add(3);
    container.add(5);
    container.add(1);
    container.add(3);
    container.add(5);
    
    auto ascending = container.getAscendingOrder();
    std::vector<int> result;
    
    for (auto it = ascending.begin(); it != ascending.end(); ++it) {
        result.push_back(*it);
    }
    
    // Should include all duplicates in ascending order
    std::vector<int> expected = {1, 3, 3, 5, 5, 5};
    CHECK(result == expected);
}

TEST_CASE("AscendingOrder iterator - empty container") 
{
    MyContainer<int> container;
    
    auto ascending = container.getAscendingOrder();
    auto it = ascending.begin();
    auto end_it = ascending.end();
    
    // Empty container - begin should equal end
    CHECK(it == end_it);
}

TEST_CASE("AscendingOrder iterator - single element") 
{
    MyContainer<int> container;
    container.add(42);
    
    auto ascending = container.getAscendingOrder();
    auto it = ascending.begin();
    auto end_it = ascending.end();
    
    CHECK(it != end_it);
    CHECK(*it == 42);
    
    ++it;
    CHECK(it == end_it);
}

TEST_CASE("AscendingOrder iterator - post increment") 
{
    MyContainer<int> container;
    container.add(10);
    container.add(5);
    container.add(15);
    
    auto ascending = container.getAscendingOrder();
    auto it = ascending.begin();
    
    // Test post-increment
    auto old_it = it++;
    CHECK(*old_it == 5);   // Old iterator points to first element
    CHECK(*it == 10);      // New iterator points to second element
}

TEST_CASE("AscendingOrder iterator - string type") 
{
    MyContainer<std::string> container;
    container.add("zebra");
    container.add("apple");
    container.add("banana");
    container.add("cat");
    
    auto ascending = container.getAscendingOrder();
    std::vector<std::string> result;
    
    for (auto it = ascending.begin(); it != ascending.end(); ++it) {
        result.push_back(*it);
    }
    
    // Should be in alphabetical order
    std::vector<std::string> expected = {"apple", "banana", "cat", "zebra"};
    CHECK(result == expected);
}

TEST_CASE("AscendingOrder iterator - bounds checking") 
{
    MyContainer<int> container;
    container.add(10);
    container.add(20);
    
    auto ascending = container.getAscendingOrder();
    auto it = ascending.begin();
    
    // Valid access
    CHECK(*it == 10);
    ++it;
    CHECK(*it == 20);
    ++it;
    
    // Should be at end now - dereferencing should throw
    CHECK_THROWS_AS(*it, std::out_of_range);
}

TEST_CASE("AscendingOrder iterator - iterator equality") 
{
    MyContainer<int> container;
    container.add(1);
    container.add(2);
    container.add(3);
    
    auto ascending1 = container.getAscendingOrder();
    auto ascending2 = container.getAscendingOrder();
    
    auto it1 = ascending1.begin();
    auto it2 = ascending2.begin();
    
    // Different iterator objects but same position should be equal
    CHECK(it1 == it2);
    
    ++it1;
    CHECK(it1 != it2);
    
    ++it2;
    CHECK(it1 == it2);
}

TEST_CASE("AscendingOrder iterator - doesn't modify original container") 
{
    MyContainer<int> container;
    container.add(30);
    container.add(10);
    container.add(20);
    
    CHECK(container.size() == 3);
    
    // Create and use ascending iterator
    auto ascending = container.getAscendingOrder();
    std::vector<int> result;
    
    // Actually collect the values (more realistic usage)
    for (auto it = ascending.begin(); it != ascending.end(); ++it) {
        result.push_back(*it);
    }
    
    // Verify we got sorted values
    std::vector<int> expected = {10, 20, 30};
    CHECK(result == expected);
    
    // Container should still be unchanged
    CHECK(container.size() == 3);
    
}