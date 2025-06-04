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
    for (auto it = ascending.begin(); it != ascending.end(); ++it) 
    {
        result.push_back(*it);
    }
    
    // Verify we got sorted values
    std::vector<int> expected = {10, 20, 30};
    CHECK(result == expected);
    
    // Container should still be unchanged
    CHECK(container.size() == 3);
}

//////////////////////////////////////////////////////////

// == DescendingOrder Iterator Tests ==

TEST_CASE("DescendingOrder iterator - basic functionality") 
{
    MyContainer<int> container;
    
    // Add elements in random order
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);
    
    // Get descending order iterator
    auto descending = container.getDescendingOrder();
    auto it = descending.begin();
    auto end_it = descending.end();
    
    // Test iterator traversal
    CHECK(it != end_it);
    CHECK(*it == 15);  // First element should be largest
    
    ++it;
    CHECK(*it == 7);
    
    ++it;
    CHECK(*it == 6);
    
    ++it;
    CHECK(*it == 2);
    
    ++it;
    CHECK(*it == 1);   // Last element should be smallest
    
    ++it;
    CHECK(it == end_it);  // Should reach end
}

TEST_CASE("DescendingOrder iterator - for loop") 
{
    MyContainer<int> container;
    container.add(30);
    container.add(10);
    container.add(20);
    container.add(5);
    
    auto descending = container.getDescendingOrder();
    std::vector<int> result;
    
    for (auto it = descending.begin(); it != descending.end(); ++it) 
    {
        result.push_back(*it);
    }
    
    // Should be in descending order
    std::vector<int> expected = {30, 20, 10, 5};
    CHECK(result == expected);
}

TEST_CASE("DescendingOrder iterator - with duplicates") 
{
    MyContainer<int> container;
    container.add(5);
    container.add(3);
    container.add(5);
    container.add(1);
    container.add(3);
    container.add(5);
    
    auto descending = container.getDescendingOrder();
    std::vector<int> result;
    
    for (auto it = descending.begin(); it != descending.end(); ++it) {
        result.push_back(*it);
    }
    
    // Should include all duplicates in descending order
    std::vector<int> expected = {5, 5, 5, 3, 3, 1};
    CHECK(result == expected);
}

TEST_CASE("DescendingOrder iterator - empty container") 
{
    MyContainer<int> container;
    
    auto descending = container.getDescendingOrder();
    auto it = descending.begin();
    auto end_it = descending.end();
    
    // Empty container - begin should equal end
    CHECK(it == end_it);
}

// == SideCrossOrder Iterator Tests ==

TEST_CASE("SideCrossOrder iterator - basic functionality") 
{
    MyContainer<int> container;
    
    // Add elements: [7,15,6,1,2]
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);
    
    auto sideCross = container.getSideCrossOrder();
    std::vector<int> result;
    
    for (auto it = sideCross.begin(); it != sideCross.end(); ++it) {
        result.push_back(*it);
    }
    
    // Expected: smallest, largest, second smallest, second largest, middle
    // Sorted: [1,2,6,7,15] -> SideCross: [1,15,2,7,6]
    std::vector<int> expected = {1, 15, 2, 7, 6};
    CHECK(result == expected);
}

TEST_CASE("SideCrossOrder iterator - even number of elements") 
{
    MyContainer<int> container;
    container.add(10);
    container.add(5);
    container.add(15);
    container.add(20);
    
    auto sideCross = container.getSideCrossOrder();
    std::vector<int> result;
    
    for (auto it = sideCross.begin(); it != sideCross.end(); ++it) {
        result.push_back(*it);
    }
    
    // Sorted: [5,10,15,20] -> SideCross: [5,20,10,15]
    std::vector<int> expected = {5, 20, 10, 15};
    CHECK(result == expected);
}

TEST_CASE("SideCrossOrder iterator - single element") 
{
    MyContainer<int> container;
    container.add(42);
    
    auto sideCross = container.getSideCrossOrder();
    auto it = sideCross.begin();
    
    CHECK(*it == 42);
    ++it;
    CHECK(it == sideCross.end());
}

// == ReverseOrder Iterator Tests ==

TEST_CASE("ReverseOrder iterator - basic functionality") 
{
    MyContainer<int> container;
    
    // Add elements: [7,15,6,1,2]
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);
    
    auto reverse = container.getReverseOrder();
    std::vector<int> result;
    
    for (auto it = reverse.begin(); it != reverse.end(); ++it) {
        result.push_back(*it);
    }
    
    // Should be in reverse insertion order: [2,1,6,15,7]
    std::vector<int> expected = {2, 1, 6, 15, 7};
    CHECK(result == expected);
}

TEST_CASE("ReverseOrder iterator - string type") 
{
    MyContainer<std::string> container;
    container.add("first");
    container.add("second");
    container.add("third");
    
    auto reverse = container.getReverseOrder();
    std::vector<std::string> result;
    
    for (auto it = reverse.begin(); it != reverse.end(); ++it) {
        result.push_back(*it);
    }
    
    std::vector<std::string> expected = {"third", "second", "first"};
    CHECK(result == expected);
}

TEST_CASE("ReverseOrder iterator - empty container") 
{
    MyContainer<int> container;
    
    auto reverse = container.getReverseOrder();
    CHECK(reverse.begin() == reverse.end());
}

// == Order Iterator Tests ==

TEST_CASE("Order iterator - basic functionality") 
{
    MyContainer<int> container;
    
    // Add elements: [7,15,6,1,2]
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);
    
    auto order = container.getOrder();
    std::vector<int> result;
    
    for (auto it = order.begin(); it != order.end(); ++it) {
        result.push_back(*it);
    }
    
    // Should be in original insertion order: [7,15,6,1,2]
    std::vector<int> expected = {7, 15, 6, 1, 2};
    CHECK(result == expected);
}

TEST_CASE("Order iterator - with duplicates") 
{
    MyContainer<int> container;
    container.add(5);
    container.add(5);
    container.add(3);
    container.add(5);
    
    auto order = container.getOrder();
    std::vector<int> result;
    
    for (auto it = order.begin(); it != order.end(); ++it) {
        result.push_back(*it);
    }
    
    // Should maintain original order including duplicates
    std::vector<int> expected = {5, 5, 3, 5};
    CHECK(result == expected);
}

// == MiddleOutOrder Iterator Tests ==

TEST_CASE("MiddleOutOrder iterator - basic functionality") 
{
    MyContainer<int> container;
    
    // Add elements: [7,15,6,1,2]
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);
    
    auto middleOut = container.getMiddleOutOrder();
    std::vector<int> result;
    
    for (auto it = middleOut.begin(); it != middleOut.end(); ++it) {
        result.push_back(*it);
    }
    
    // Middle index = (5-1)/2 = 2, so start with element at index 2 (6)
    // Then alternate: left(15), right(1), left(7), right(2)
    std::vector<int> expected = {6, 15, 1, 7, 2};
    CHECK(result == expected);
}

TEST_CASE("MiddleOutOrder iterator - even number of elements") 
{
    MyContainer<int> container;
    // Add elements: [10,20,30,40]
    container.add(10);  // index 0
    container.add(20);  // index 1 (left middle for even count)
    container.add(30);  // index 2
    container.add(40);  // index 3
    
    auto middleOut = container.getMiddleOutOrder();
    std::vector<int> result;
    
    for (auto it = middleOut.begin(); it != middleOut.end(); ++it) {
        result.push_back(*it);
    }
    
    // Middle index = (4-1)/2 = 1, so start with element at index 1 (20)
    // Then: left(10), right(30), right(40)
    std::vector<int> expected = {20, 10, 30, 40};
    CHECK(result == expected);
}

TEST_CASE("MiddleOutOrder iterator - single element") 
{
    MyContainer<int> container;
    container.add(100);
    
    auto middleOut = container.getMiddleOutOrder();
    auto it = middleOut.begin();
    
    CHECK(*it == 100);
    ++it;
    CHECK(it == middleOut.end());
}

TEST_CASE("MiddleOutOrder iterator - three elements") 
{
    MyContainer<int> container;
    // Add elements: [1,2,3]
    container.add(1);  // index 0
    container.add(2);  // index 1 (middle)
    container.add(3);  // index 2
    
    auto middleOut = container.getMiddleOutOrder();
    std::vector<int> result;
    
    for (auto it = middleOut.begin(); it != middleOut.end(); ++it) {
        result.push_back(*it);
    }
    
    // Start with middle (2), then left (1), then right (3)
    std::vector<int> expected = {2, 1, 3};
    CHECK(result == expected);
}

// == Iterator Bounds Checking Tests ==

TEST_CASE("All iterators - bounds checking") 
{
    MyContainer<int> container;
    container.add(10);
    container.add(20);
    
    // Test that all iterators throw when dereferencing past end
    auto ascending = container.getAscendingOrder();
    auto desc = container.getDescendingOrder();
    auto sideCross = container.getSideCrossOrder();
    auto reverse = container.getReverseOrder();
    auto order = container.getOrder();
    auto middleOut = container.getMiddleOutOrder();
    
    // Move all iterators to end
    auto asc_end = ascending.end();
    auto desc_end = desc.end();
    auto side_end = sideCross.end();
    auto rev_end = reverse.end();
    auto ord_end = order.end();
    auto mid_end = middleOut.end();
    
    // All should throw when dereferenced
    CHECK_THROWS_AS(*asc_end, std::out_of_range);
    CHECK_THROWS_AS(*desc_end, std::out_of_range);
    CHECK_THROWS_AS(*side_end, std::out_of_range);
    CHECK_THROWS_AS(*rev_end, std::out_of_range);
    CHECK_THROWS_AS(*ord_end, std::out_of_range);
    CHECK_THROWS_AS(*mid_end, std::out_of_range);
}

// == Mixed Iterator Operations Test ==

TEST_CASE("Multiple iterators on same container") 
{
    MyContainer<int> container;
    container.add(5);
    container.add(1);
    container.add(3);
    
    // Get different iterator types
    auto ascending = container.getAscendingOrder();
    auto descending = container.getDescendingOrder();
    auto reverse = container.getReverseOrder();
    auto order = container.getOrder();
    
    // Collect results from each
    std::vector<int> asc_result, desc_result, rev_result, ord_result;
    
    for (auto it = ascending.begin(); it != ascending.end(); ++it) {
        asc_result.push_back(*it);
    }
    
    for (auto it = descending.begin(); it != descending.end(); ++it) {
        desc_result.push_back(*it);
    }
    
    for (auto it = reverse.begin(); it != reverse.end(); ++it) {
        rev_result.push_back(*it);
    }
    
    for (auto it = order.begin(); it != order.end(); ++it) {
        ord_result.push_back(*it);
    }
    
    // Verify each iterator type
    CHECK(asc_result == std::vector<int>{1, 3, 5});      // Ascending
    CHECK(desc_result == std::vector<int>{5, 3, 1});     // Descending  
    CHECK(rev_result == std::vector<int>{3, 1, 5});      // Reverse insertion
    CHECK(ord_result == std::vector<int>{5, 1, 3});      // Original order
    
    // Container should be unchanged
    CHECK(container.size() == 3);
}


// Add this test case to your tests.cpp file

TEST_CASE("Operator<< streaming functionality") 
{
    MyContainer<int> container;
    
    // Test empty container
    std::ostringstream empty_stream;
    empty_stream << container;
    CHECK(empty_stream.str() == "");
    
    // Add elements and test streaming
    container.add(10);
    container.add(20);
    container.add(30);
    
    std::ostringstream stream;
    stream << container;
    
    // Should output elements separated by spaces
    CHECK(stream.str() == "10 20 30 ");
    
    // Test with string container
    MyContainer<std::string> stringContainer;
    stringContainer.add("Hello");
    stringContainer.add("World");
    stringContainer.add("C++");
    
    std::ostringstream string_stream;
    string_stream << stringContainer;
    CHECK(string_stream.str() == "Hello World C++ ");
    
    // Test with single element
    MyContainer<int> singleContainer;
    singleContainer.add(5);
    
    std::ostringstream single_stream;
    single_stream << singleContainer;
    CHECK(single_stream.str() == "5 ");
    
    // Test that streaming doesn't modify container
    CHECK(container.size() == 3);
    CHECK(stringContainer.size() == 3);
    CHECK(singleContainer.size() == 1);
}

TEST_CASE("Operator<< with duplicates") 
{
    MyContainer<int> container;
    container.add(5);
    container.add(3);
    container.add(5);
    container.add(1);
    container.add(5);
    
    std::ostringstream stream;
    stream << container;
    
    // Should preserve all duplicates in original order
    CHECK(stream.str() == "5 3 5 1 5 ");
}

TEST_CASE("Operator<< integration with other operations") 
{
    MyContainer<int> container;
    container.add(100);
    container.add(50);
    container.add(75);
    
    // Stream before removal
    std::ostringstream before_stream;
    before_stream << container;
    CHECK(before_stream.str() == "100 50 75 ");
    
    // Remove element and stream again
    container.remove(50);
    
    std::ostringstream after_stream;
    after_stream << container;
    CHECK(after_stream.str() == "100 75 ");
    
    // Verify size is correct
    CHECK(container.size() == 2);
}

TEST_CASE("Operator<< with chaining") 
{
    MyContainer<int> container1;
    MyContainer<int> container2;
    
    container1.add(1);
    container1.add(2);
    
    container2.add(10);
    container2.add(20);
    
    std::ostringstream stream;
    stream << "Container 1: " << container1 << "| Container 2: " << container2 << "| End";
    
    CHECK(stream.str() == "Container 1: 1 2 | Container 2: 10 20 | End");
}

TEST_CASE("Template functionality test - char type")
{
    MyContainer<char> charContainer;

    // Test basic operations with chars
    charContainer.add('Z');
    charContainer.add('A');
    charContainer.add('M');
    charContainer.add('B');
    charContainer.add('Y');
    CHECK(charContainer.size() == 5);
    CHECK(charContainer.isEmpty() == false);

    // Test char removal
    charContainer.remove('M');
    CHECK(charContainer.size() == 4);

    // Test char duplicates
    charContainer.add('A'); // Duplicate
    charContainer.add('A'); // Another duplicate
    CHECK(charContainer.size() == 6);

    // Remove all occurrences of 'A'
    charContainer.remove('A'); // Should remove all 3 A's
    CHECK(charContainer.size() == 3); // Z, B, Y remaining

    // Try to remove non-existent char
    CHECK_THROWS_AS(charContainer.remove('X'), std::invalid_argument);

    // Size should remain unchanged after failed removal
    CHECK(charContainer.size() == 3);
}

TEST_CASE("Char container - all iterator types")
{
    MyContainer<char> charContainer;
    
    // Add characters: ['Z', 'A', 'M', 'B', 'Y']
    charContainer.add('Z');
    charContainer.add('A');
    charContainer.add('M');
    charContainer.add('B');
    charContainer.add('Y');

    // Test AscendingOrder with chars
    auto ascending = charContainer.getAscendingOrder();
    std::vector<char> asc_result;
    for (auto it = ascending.begin(); it != ascending.end(); ++it) {
        asc_result.push_back(*it);
    }
    // Should be alphabetical: A, B, M, Y, Z
    std::vector<char> expected_asc = {'A', 'B', 'M', 'Y', 'Z'};
    CHECK(asc_result == expected_asc);

    // Test DescendingOrder with chars
    auto descending = charContainer.getDescendingOrder();
    std::vector<char> desc_result;
    for (auto it = descending.begin(); it != descending.end(); ++it) {
        desc_result.push_back(*it);
    }
    // Should be reverse alphabetical: Z, Y, M, B, A
    std::vector<char> expected_desc = {'Z', 'Y', 'M', 'B', 'A'};
    CHECK(desc_result == expected_desc);

    // Test SideCrossOrder with chars
    auto sideCross = charContainer.getSideCrossOrder();
    std::vector<char> side_result;
    for (auto it = sideCross.begin(); it != sideCross.end(); ++it) {
        side_result.push_back(*it);
    }
    // Sorted: [A,B,M,Y,Z] -> SideCross: [A,Z,B,Y,M]
    std::vector<char> expected_side = {'A', 'Z', 'B', 'Y', 'M'};
    CHECK(side_result == expected_side);

    // Test ReverseOrder with chars
    auto reverse = charContainer.getReverseOrder();
    std::vector<char> rev_result;
    for (auto it = reverse.begin(); it != reverse.end(); ++it) {
        rev_result.push_back(*it);
    }
    // Should be reverse insertion: Y, B, M, A, Z
    std::vector<char> expected_rev = {'Y', 'B', 'M', 'A', 'Z'};
    CHECK(rev_result == expected_rev);

    // Test Order with chars
    auto order = charContainer.getOrder();
    std::vector<char> ord_result;
    for (auto it = order.begin(); it != order.end(); ++it) {
        ord_result.push_back(*it);
    }
    // Should be original insertion: Z, A, M, B, Y
    std::vector<char> expected_ord = {'Z', 'A', 'M', 'B', 'Y'};
    CHECK(ord_result == expected_ord);

    // Test MiddleOutOrder with chars
    auto middleOut = charContainer.getMiddleOutOrder();
    std::vector<char> mid_result;
    for (auto it = middleOut.begin(); it != middleOut.end(); ++it) {
        mid_result.push_back(*it);
    }
    // Middle index = (5-1)/2 = 2, so start with 'M'
    // Then alternate: left('A'), right('B'), left('Z'), right('Y')
    std::vector<char> expected_mid = {'M', 'A', 'B', 'Z', 'Y'};
    CHECK(mid_result == expected_mid);

    // Container should remain unchanged
    CHECK(charContainer.size() == 5);
}

TEST_CASE("Char container - operator<< streaming")
{
    MyContainer<char> charContainer;
    
    // Test empty char container
    std::ostringstream empty_stream;
    empty_stream << charContainer;
    CHECK(empty_stream.str() == "");
    
    // Add chars and test streaming
    charContainer.add('H');
    charContainer.add('i');
    charContainer.add('!');
    
    std::ostringstream stream;
    stream << charContainer;
    
    // Should output chars separated by spaces
    CHECK(stream.str() == "H i ! ");
    
    // Test with single char
    MyContainer<char> singleChar;
    singleChar.add('X');
    
    std::ostringstream single_stream;
    single_stream << singleChar;
    CHECK(single_stream.str() == "X ");
    
    // Test that streaming doesn't modify container
    CHECK(charContainer.size() == 3);
    CHECK(singleChar.size() == 1);
}

TEST_CASE("Char container - with duplicates and special characters")
{
    MyContainer<char> charContainer;
    
    // Add various chars including duplicates and special characters
    charContainer.add('a');
    charContainer.add('@');
    charContainer.add('a');  // duplicate
    charContainer.add('5');  // digit
    charContainer.add('!');  // special
    charContainer.add('a');  // another duplicate
    
    CHECK(charContainer.size() == 6);
    
    // Test ascending order with mixed character types
    auto ascending = charContainer.getAscendingOrder();
    std::vector<char> result;
    for (auto it = ascending.begin(); it != ascending.end(); ++it) {
        result.push_back(*it);
    }
    
    // Should be sorted by ASCII values: !, 5, @, a, a, a
    std::vector<char> expected = {'!', '5', '@', 'a', 'a', 'a'};
    CHECK(result == expected);
    
    // Remove all 'a' characters
    charContainer.remove('a');
    CHECK(charContainer.size() == 3);  // Should have !, 5, @ remaining
    
    // Test streaming after removal
    std::ostringstream stream;
    stream << charContainer;
    CHECK(stream.str() == "@ 5 ! ");  // Original order minus the 'a's
}

TEST_CASE("Char container - bounds checking")
{
    MyContainer<char> charContainer;
    charContainer.add('A');
    charContainer.add('B');
    
    // Test that char iterators also throw when dereferencing past end
    auto ascending = charContainer.getAscendingOrder();
    auto it = ascending.begin();
    
    // Valid access
    CHECK(*it == 'A');
    ++it;
    CHECK(*it == 'B');
    ++it;
    
    // Should be at end now - dereferencing should throw
    CHECK_THROWS_AS(*it, std::out_of_range);
}

TEST_CASE("Char container - empty container operations")
{
    MyContainer<char> charContainer;
    
    // Test empty container with chars
    CHECK(charContainer.size() == 0);
    CHECK(charContainer.isEmpty() == true);
    
    // All iterators should work with empty char container
    auto ascending = charContainer.getAscendingOrder();
    auto descending = charContainer.getDescendingOrder();
    auto sideCross = charContainer.getSideCrossOrder();
    auto reverse = charContainer.getReverseOrder();
    auto order = charContainer.getOrder();
    auto middleOut = charContainer.getMiddleOutOrder();
    
    // All should have begin == end
    CHECK(ascending.begin() == ascending.end());
    CHECK(descending.begin() == descending.end());
    CHECK(sideCross.begin() == sideCross.end());
    CHECK(reverse.begin() == reverse.end());
    CHECK(order.begin() == order.end());
    CHECK(middleOut.begin() == middleOut.end());
    
    // Try to remove from empty char container
    CHECK_THROWS_AS(charContainer.remove('Z'), std::invalid_argument);
}